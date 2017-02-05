#ifndef __FUNC__
#define __FUNC__

#include <cstdio>
#include <vector>
#include <random>
#include "ising.h"

// Write a header to the datafile containing L and T.
void WriteHeader(Ising ising, FILE * datafile);


// Calculate the moving average and variance using the Welford-algorithm.
// Var = M2/n
void UpdateStat(const double& value, double& mean, double& M2, double& n);

double Bootstrap(const int& n, std::vector<double>& values,
                 double (*func)(const std::vector<double>&, void* params),
                 void* params);
                 
double AverageVec(const std::vector<double>& data);
#endif
