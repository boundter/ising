#include "func.h"

void WriteHeader(Ising ising, FILE * datafile) {
  fprintf(datafile, "# L= %d , T= %.9f \n", ising.L(), ising.T());
}


void UpdateStat(const double& value, double& mean, double& M2, double& n) {
  n += 1;
  double delta = value - mean;
  mean += delta/n;
  double delta_2 = value - mean;
  M2 += delta*delta_2;
}
