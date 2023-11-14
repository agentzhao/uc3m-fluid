#include "block.hpp"
#include <cmath>

namespace Constants {
  // Information from initial file
  float ppm = 0.0;
  int np = 0.0;

  // Simulation scalar constants
  double radiusMultiplier = 1.695;
  double fluidDensity = pow(10, 3);
  double stiffnessPressure = 3.0;
  double stiffnessCollisions = 3 * pow(10, 4);
  double damping = 128.0;
  double viscosity = 0.4;
  double particleSize = 2 * pow(10, -4);
  double timeStep = pow(10, -3);

  // Simulation vector constants
  std::vector<double> externalAcceleration = {0.0, -9.8, 0.0};
  std::vector<double> boxUpperBound = {0.065, 0.1, 0.065};
  std::vector<double> boxLowerBound = {-0.065, -0.08, -0.065};

  // Simulation parameters
  double particleMass = fluidDensity / pow(ppm, 3);
  double smoothingLength = radiusMultiplier / ppm;
  double slSq = pow(smoothingLength, 2);
  double slCu = pow(smoothingLength, 3);
  double slSixth = pow(smoothingLength, 6);
  double slNinth = pow(smoothingLength, 9);

  double densTransConstant = (315 / 64 * M_PI * slNinth) * particleMass;
  double accTransConstant1 = (15 / M_PI * slSixth) * ((3 * particleMass * stiffnessPressure) / 2);
  double accTransConstant2 =  (45 / M_PI * slSixth) * viscosity * particleMass;
};

Particle::Particle {
  public:
    float px, py = 0.0;
    double density =
};

namespace Box {
  // Calculating the number of blocks in each dimension...
  double numberX = (Constants::boxUpperBound[0] - Constants::boxLowerBound[0]) / Constants::smoothingLength;
  double numberY = (Constants::boxUpperBound[1] - Constants::boxLowerBound[1]) / Constants::smoothingLength;
  double numberZ = (Constants::boxUpperBound[2] - Constants::boxLowerBound[2]) / Constants::smoothingLength;

  // Calculating the size of grid blocks in each dimension...
  double sizeX = (Constants::boxUpperBound[0] - Constants::boxLowerBound[0]) / numberX;
  double sizeY = (Constants::boxUpperBound[1] - Constants::boxLowerBound[1]) / numberY;
  double sizeZ = (Constants::boxUpperBound[2] - Constants::boxLowerBound[2]) / numberZ;

  // Determining which block a particle belongs in...
      // ** NEED TO ACCOUNT FOR EDGE CASES OF SURPASSING BOUNDARIES
  std::vector<int> findBlock(Particle part) {
    // First, get the coordinates of the particle...
    double px = part.px;
    double py = part.py;
    double pz = part.pz;

    // Now, need to check to see if these are within the bounds
      // x-coordinate...
    if (px > Constants::boxUpperBound[0])
    {px = static_cast<float>(Constants::boxUpperBound[0]);}
    else if (px < Constants::boxLowerBound[0])
    {px = static_cast<float>(Constants::boxLowerBound[0]);}

      // y-coordinate...
    if (py > Constants::boxUpperBound[1])
    {py = static_cast<float>(Constants::boxUpperBound[1]);}
    else if (py < Constants::boxLowerBound[1])
    {py = static_cast<float>(Constants::boxLowerBound[1]);}

      // z-coordinate...
    if (pz > Constants::boxUpperBound[2])
    {pz = static_cast<float>(Constants::boxUpperBound[2]);}
    else if (pz < Constants::boxLowerBound[2])
    {pz = static_cast<float>(Constants::boxLowerBound[2]);}

    // Now, px, py, and pz should all be within the bounds of the grid
    // So, we can now find the specific block a particle occupies
      // This is done by finding which block index the particle has in all three dimensions
    int bI = static_cast<int>((px - Constants::boxLowerBound[0]) / sizeX);
    int bJ = static_cast<int>((py - Constants::boxLowerBound[1]) / sizeY);
    int bK = static_cast<int>((pz - Constants::boxLowerBound[2]) / sizeZ);

    // We must now check that these block coordinates obey their own boundaries (or otherwise are fixed)
      // x-coordinate...
    if (bI < 0)
    {bI = 0;}
    else if (bI > (numberX - 1))
    {bI = static_cast<int>(numberX - 1);}

      // y-coordinate...
    if (bJ < 0)
    {bJ = 0;}
    else if (bJ > (numberY - 1))
    {bJ = static_cast<int>(numberY - 1);}

      // z-coordinate...
    if (bK < 0)
    {bK = 0;}
    else if (bJ > (numberZ - 1))
    {bK = static_cast<int>(numberZ - 1);}

    // These can then be stored in a vector to represent the specific block a particle is in
    std::vector<int> partBlock = {bI, bJ, bK};
    return partBlock;
  }
};

namespace Formulas {

  // Increasing density...
  void incDensity(Particle iPart, Particle jPart){
    float ix = iPart.px;
    float iy = iPart.py;
    float iz = iPart.pz;
    float jx = jPart.px;
    float jy = jPart.py;
    float jz = jPart.pz;

    // Avoid nesting, possible future hotspot
      // Sqrt and ^2 cancel
    double vecNorm = pow(sqrt(pow((ix - jx), 2) + pow((iy - jy), 2) + pow((iz - jz), 2)), 2);
    if (vecNorm < Constants::slSq)
    {
      double densityChange = pow((Constants::slSq - vecNorm), 3);
      iPart.density += densityChange;
      iPart.density = (iPart.density + Constants::slSixth) * Constants::densTransConstant;
    }
    else if (vecNorm >= Constants::slSq)
    {iPart.density += 0;}
  };

  // Formula to calculate the distance between two particles
  double findDistance(Particle iPart, Particle jPart)
  { float ix = iPart.px;
    float iy = iPart.py;
    float iz = iPart.pz;
    float jx = jPart.px;
    float jy = jPart.py;
    float jz = jPart.pz;
    double vecNorm = pow(sqrt(pow((ix - jx), 2) + pow((iy - jy), 2) + pow((iz - jz), 2)), 2);

    double distance  = sqrt(fmax(vecNorm, pow(10, -12)));
    return distance;};

  // Need to make sure acceleration transfers aren't double counted...
  void accelerationTransfer(Particle iPart, Particle jPart)
  {
  double distance = findDistance(iPart, jPart);

  for (int i = 0; i < 3; i++)
  {
      double accChange = ((((iPart.positions[i] - jPart.positions[j]) * Constants::accTransConstant1 * (pow((Constants::smoothingLength - distance), 2)) / distance) * (iPart.density + jPart.density - (2 * Constants::fluidDensity)) * Constants::accTransConstant2) / (iPart.density * jPart.density));
      iPart.acceleration[i] += accChange;
      jPart.acceleration[i] -= accChange;
  }
  };

  void particleMotion(Particle iPart)
  {
  for (int i = 0; i < 3; i++)
  {
      iPart.position[i] = iPart.position[i] + iPart.hv[i] * 1 + iPart.acceleration[i] * pow(1, 2);
      iPart.velocity[i]= iPart.hv[i] + ((iPart.acceleration.[i] * 1)/2);
      iPart.hv[i] = iPart.hv[i] + iPart.acceleration[i] * 1;
  }
  };

  void boxCollisions(Particle iPart)
  {
        // Checking x-boundary collisions...
        float newX = iPart.position[0] + iPart.hv[0] * 1;

        // Check for both bounds...
        double changeXLower = Constants::particleSize - (newX - Constants::boxLowerBound[0]);
        double changeXUpper = Constants::particleSize - (newX - Constants::boxUpperBound[0]);

        if (changeXLower > pow(10, -10))
        {
          iPart.acceleration[0] += Constants::stiffnessCollisions * changeXLower - Constants::damping * iPart.velocity[0];
        }
        else if (changeXUpper > pow(10, -10))
        {
          iPart.acceleration[0] -= Constants::stiffnessCollisions * changeXLower + Constants::damping * iPart.velocity[0];
        };

        // Checking y-boundary collisions...
        float newY = iPart.position[1] + iPart.hv[1] * 1;

        // Check for both bounds...
        double changeYLower = Constants::particleSize - (newY - Constants::boxLowerBound[1]);
        double changeYUpper = Constants::particleSize - (newY - Constants::boxUpperBound[1]);

        if (changeYLower > pow(10, -10))
        {
          iPart.acceleration[1] += Constants::stiffnessCollisions * changeYLower - Constants::damping * iPart.velocity[1];
        }
        else if (changeYUpper > pow(10, -10))
        {
          iPart.acceleration[1] -= Constants::stiffnessCollisions * changeYLower + Constants::damping * iPart.velocity[1];
        };

        // Checking z-boundary collisions...
        float newZ = iPart.position[2] + iPart.hv[2] * 1;

        // Check for both bounds...
        double changeZLower = Constants::particleSize - (newZ - Constants::boxLowerBound[2]);
        double changeZUpper = Constants::particleSize - (newZ - Constants::boxUpperBound[2]);

        if (changeZLower > pow(10, -10))
        {
          iPart.acceleration[2] += Constants::stiffnessCollisions * changeZLower - Constants::damping * iPart.velocity[2];
        }
        else if (changeZUpper > pow(10, -10))
        {
          iPart.acceleration[2] -= Constants::stiffnessCollisions * changeZLower + Constants::damping * iPart.velocity[2];d
        };
  };

  void boundaryCollisions(Particle iPart)
  {
        // X-boundary...
        float dXLower = iPart.position[0] - Constants::boxLowerBound[0];
        float dXUpper = Constants::boxUpperBound[0] - iPart.position[0];

        if (dXLower < 0)
        {
          iPart.position[0] = Constants::boxLowerBound[0] - dXLower;
          iPart.velocity[0] = -1 * iPart.velocity[0];
          iPart.hv[0] = -1 * iPart.hv[0];
        }
        else if (dXUpper < 0)
        {
          iPart.position[0] = Constants::boxUpperBound[0] + dXUpper;
          iPart.velocity[0] = -1 * iPart.velocity[0];
          iPart.hv[0] = -1 * iPart.hv[0];
        }

        // Y-boundary...
        float dYLower = iPart.position[1] - Constants::boxLowerBound[1];
        float dYUpper = Constants::boxUpperBound[1] - iPart.position[1];

        if (dYLower < 0)
        {
          iPart.position[1] = Constants::boxLowerBound[1] - dYLower;
          iPart.velocity[1] = -1 * iPart.velocity[1];
          iPart.hv[1] = -1 * iPart.hv[1];
        }
        else if (dYUpper < 0)
        {
          iPart.position[1] = Constants::boxUpperBound[1] + dYUpper;
          iPart.velocity[1] = -1 * iPart.velocity[1];
          iPart.hv[1] = -1 * iPart.hv[1];
        }

        // Z-boundary...
        float dZLower = iPart.position[2] - Constants::boxLowerBound[2];
        float dZUpper = Constants::boxUpperBound[2] - iPart.position[2];

        if (dZLower < 0)
        {
          iPart.position[2] = Constants::boxLowerBound[2] - dZLower;
          iPart.velocity[2] = -1 * iPart.velocity[2];
          iPart.hv[2] = -1 * iPart.hv[2];
        }
        else if (dZUpper < 0)
        {
          iPart.position[2] = Constants::boxUpperBound[2] + dZUpper;
          iPart.velocity[2] = -1 * iPart.velocity[2];
          iPart.hv[2] = -1 * iPart.hv[2];
        }
  };
  };
