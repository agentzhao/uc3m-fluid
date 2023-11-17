// Particle class implementation
#include "particle.hpp"
#include "constants.hpp"
// Constructor
Particle::Particle(float px, float py, float pz, float hvx, float hvy,
                   float hvz, float vx, float vy, float vz) {
  // Initialize position, half-velocity, and velocity vectors
  position = {px, py, pz};
  hv = {hvx, hvy, hvz};
  velocity = {vx, vy, vz};

  // Initialize other member variables
  density = 0.0;
  acceleration = Constants::externalAcceleration;

  // Find the initial home block
  homeBlock = findBlock(px, py, pz);
}

// Determining which block a particle belongs in...
// ** NEED TO ACCOUNT FOR EDGE CASES OF SURPASSING BOUNDARIES
std::vector<int> Particle::findBlock(float px, float py, float pz) {
  // Need to check to see if these are within the bounds
  // x-coordinate...
  if (px > Constants::boxUpperBound[0]) {
    px = static_cast<float>(Constants::boxUpperBound[0]);
  } else if (px < Constants::boxLowerBound[0]) {
    px = static_cast<float>(Constants::boxLowerBound[0]);
  }

  // y-coordinate...
  if (py > Constants::boxUpperBound[1]) {
    py = static_cast<float>(Constants::boxUpperBound[1]);
  } else if (py < Constants::boxLowerBound[1]) {
    py = static_cast<float>(Constants::boxLowerBound[1]);
  }

  // z-coordinate...
  if (pz > Constants::boxUpperBound[2]) {
    pz = static_cast<float>(Constants::boxUpperBound[2]);
  } else if (pz < Constants::boxLowerBound[2]) {
    pz = static_cast<float>(Constants::boxLowerBound[2]);
  }

  // Now, px, py, and pz should all be within the bounds of the grid
  // So, we can now find the specific block a particle occupies
  // This is done by finding which block index the particle has in all three
  // dimensions
  int bI = static_cast<int>((px - Constants::boxLowerBound[0]) / sizeX);
  int bJ = static_cast<int>((py - Constants::boxLowerBound[1]) / sizeY);
  int bK = static_cast<int>((pz - Constants::boxLowerBound[2]) / sizeZ);

  // We must now check that these block coordinates obey their own boundaries
  // (or otherwise are fixed) x-coordinate...
  if (bI < 0) {
    bI = 0;
  } else if (bI > (numberX - 1)) {
    bI = static_cast<int>(numberX - 1);
  }

  // y-coordinate...
  if (bJ < 0) {
    bJ = 0;
  } else if (bJ > (numberY - 1)) {
    bJ = static_cast<int>(numberY - 1);
  }

  // z-coordinate...
  if (bK < 0) {
    bK = 0;
  } else if (bJ > (numberZ - 1)) {
    bK = static_cast<int>(numberZ - 1);
  }

  // These can then be stored in a vector to represent the specific block a
  // particle is in
  std::vector<int> partBlock = {bI, bJ, bK};
  return partBlock;
};

// Block updater
void Particle::updateBlock(float px, float py, float pz)
{
  homeBlock = findBlock(px, py, pz);
}

// Particle destructor implementation
Particle::~Particle() {
  // Destructor code, if needed
}
