#ifndef GRID_HPP
#define GRID_HPP
#include <unordered_map>
#include "block.hpp"

// Grid class
class Grid {
  public:
    std::unordered_map<std::vector<int>, Block> blocks;
    // Information from initial file
    float ppm;
    int np;

    double particleMass;
    double smoothingLength;

    // Calculating the number of blocks in each dimension...
    double numberX;
    double numberY;
    double numberZ;
    // Total number of blocks in the grid
    double numBlocks;

    // Calculating the size of grid blocks in each dimension...
    double sizeX;
    double sizeY;
    double sizeZ;

    // Simulation parameters
    double slSq;
    double slCu;
    double slSixth;
    double slNinth;

    double densTransConstant;
    double accTransConstant1;
    double accTransConstant2;

    void update_sim_params();

    // Update variables
    void update_box_params();
};

#endif // GRID_HPP
