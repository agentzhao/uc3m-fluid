#ifndef BLOCK_CPP
#define BLOCK_CPP

#include <vector>

namespace Constants {
  // Information from initial file
  extern float ppm;
  extern int np;

  // Simulation scalar constants
  extern double radiusMultiplier;
  extern double fluidDensity;
  extern double stiffnessPressure;
  extern double stiffnessCollisions;
  extern double damping;
  extern double viscosity;
  extern double particleSize;
  extern double timeStep;

  // Simulation vector constants
  extern std::vector<double> externalAcceleration;
  extern std::vector<double> boxUpperBound;
  extern std::vector<double> boxLowerBound;

  // Simulation parameters
  extern double particleMass;
  extern double smoothingLength;
};

class Particle {
  public:
    float px, py, pz, hvx, hvy, hvz, vx, vy, vz;
    double density;
    double acceleration;
};

namespace Box {
  // Calculating the number of blocks in each dimension...
  extern double numberX;
  extern double numberY;
  extern double numberZ;

  // Calculating the size of grid blocks in each dimension...
  extern double sizeX;
  extern double sizeY;
  extern double sizeZ;

  // Determining which block a particle belongs in...
  std::vector<int> findBlock(Particle part);
};

namespace Formulas {
  // Repositioning particles...
    // ........

  // Increasing density...
  void incDensity(Particle iPart, Particle jPart);

  double findDistance(Particle iPart, Particle jPart);

  void accelerationTransfer(Particle iPart, Particle jPart);

  void particleMotion(Particle iPart);

  void boxCollisions(Particle iPart);

  void boundaryCollisions(Particle iPart);
};

#endif
