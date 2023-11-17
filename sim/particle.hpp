#ifndef FLUID_PARTICLE_HPP
#define FLUID_PARTICLE_HPP

#include <vector>

// Particle class
class Particle {
  public:
    // Member variables
    std::vector<float> position;
    std::vector<float> hv;
    std::vector<float> velocity;
    double density;
    std::vector<double> acceleration;
    std::vector<int> homeBlock;

    // Constructor
    Particle(float px, float py, float pz, float hvx, float hvy, float hvz,
             float vx, float vy, float vz);

    // Determining which block a particle belongs in...
    std::vector<int> findBlock(float px, float py, float pz);

    // Block updater
    void updateBlock(float px, float py, float pz);

    // Destructor
    ~Particle();
};

#endif  // FLUID_PARTICLE_HPP
