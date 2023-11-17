#include "grid.hpp"
#include "constants.hpp"

// Implementing the grid class...
Grid::Grid()
{
  public:
          ppm = 0.0;
          np = 0;

          particleMass = Constants::fluidDensity / pow(ppm, 3);
          smoothingLength = Constants::radiusMultiplier / ppm;

          slSq = pow(smoothingLength, 2);
          slCu = pow(smoothingLength, 3);
          slSixth = pow(smoothingLength, 6);
          slNinth = pow(smoothingLength, 9);

          densTransConstant = (315.0 / 64 * M_PI * slNinth) * particleMass;
          accTransConstant1 =
              (15 / M_PI * slSixth) * ((3 * particleMass * Constants::stiffnessPressure) / 2);
          accTransConstant2 = (45 / M_PI * slSixth) * Constants::viscosity * particleMass;

          // update simulation parameters
          void Grid::update_sim_params()
          {
            particleMass = Constants::fluidDensity / pow(Constants::ppm, 3);
            smoothingLength = Constants::radiusMultiplier / Constants::ppm;
            Constants::slSq = pow(Constants::smoothingLength, 2);
            Constants::slCu = pow(Constants::smoothingLength, 3);
            Constants::slSixth = pow(Constants::smoothingLength, 6);
            Constants::slNinth = pow(Constants::smoothingLength, 9);
          }

          void Grid::update_box_params(){
            numberX = (Constants::boxUpperBound[0] - Constants::boxLowerBound[0]) /
                           Constants::smoothingLength;
            numberY = (Constants::boxUpperBound[1] - Constants::boxLowerBound[1]) /
                           Constants::smoothingLength;
            numberZ = (Constants::boxUpperBound[2] - Constants::boxLowerBound[2]) /
                           Constants::smoothingLength;
            numBlocks = Box::numberX * Box::numberY * Box::numberZ;
            sizeX =
                (Constants::boxUpperBound[0] - Constants::boxLowerBound[0]) / numberX;
            sizeY =
                (Constants::boxUpperBound[1] - Constants::boxLowerBound[1]) / numberY;
            sizeZ =
                (Constants::boxUpperBound[2] - Constants::boxLowerBound[2]) / numberZ;
          }

};