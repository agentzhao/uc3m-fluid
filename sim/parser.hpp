#ifndef PARSER_H
#define PARSER_H

#include "constants.hpp"
#include "grid.hpp"
#include "particle.hpp"
#include "simulation.hpp"
#include <fstream>
#include <iostream>
#include <locale>
#include <vector>

int parser(char **argv);

// read binary value from file
Grid readInput(std::string inputfile);

// print parameters
int printParameters(Grid &grid);

// write binary value to file
void writeOutput(std::string outputfile, Grid &grid);

// mergesort for particles array
void merge(std::vector<Particle> &particles, int left, int middle, int right);

void mergeSort(std::vector<Particle> &particles, int left, int right);

#endif // PARSER_H
