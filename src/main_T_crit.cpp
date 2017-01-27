#include <cstdio>
#include <string>
#include <vector>
#include "ising.h"
#include "func.h"

using namespace std;

#define NELEMS(x)  (sizeof(x) / sizeof((x)[0])) // length of an array

int L[5] = {20, 40, 60, 80, 100};
double T_min = 0.5, T_max = 4.0, n_T = 60, T = T_min;
double n_trans = 60000;
double n_sweeps = 100000;
string folder = "result/data/";

int main() {
  double T_step = (T_max - T_min)/(n_T - 1);
  string filename = folder + "T_crit.dat";
  FILE * datafile = fopen(filename.c_str(), "w");

  for (int l = 0; l < NELEMS(L); ++l) {
    T = T_min;
    Ising ising(L[l], T);

    for (int t = 0; t < n_T; ++t) {
      double mean = 0, M2 = 0, n = 0;
      ising.SetT(T);
      T += T_step;
      for (int i = 0; i < n_sweeps; ++i) {
        for (int j = 0; j < ising.L()*ising.L(); ++j) {
          ising.Flip();
        }
        if (i >= n_trans) {
          UpdateStat(ising.M(), mean, M2, n);
        }
      }
      fprintf(datafile, "%d %d %.9f %.9f %.9f\n", l, ising.L(), ising.T(), mean,
                                                M2/n);
      fflush(datafile);
    }
  }
  fclose(datafile);
}
