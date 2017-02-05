#include <cstdio>
#include <string>
#include <vector>
#include <cmath>

#include "ising.h"
#include "func.h"

using namespace std;

#define NELEMS(x)  (sizeof(x) / sizeof((x)[0])) // length of an array

int L[5] = {20, 40, 60, 80, 100};
double T_min = 0.5, T_max = 4.0, n_T = 50, T = T_min;
double n_trans = 20000;
double n_sweeps = 10000;
int n_bootstrap = 1000;
string folder = "result/data/";


double Average(const vector<double>& data, void* params) {
  double mean = 0;
  for (int i = 0; i < data.size(); ++i) {
    mean += data[i];
  }
  return mean/double(data.size());
}

int main() {
  double T_step = (T_max - T_min)/(n_T - 1);
  string filename = folder + "T_crit.dat";
  FILE * datafile = fopen(filename.c_str(), "w");

  for (int l = 0; l < NELEMS(L); ++l) {
    T = T_min;
    Ising ising(L[l], T);
    ising.SetUniformState();


    for (int t = 0; t < n_T; ++t) {
      ising.SetT(T);
      T += T_step;
      vector<double> M;
      for (int i = 0; i < n_trans; ++i) {
        for (int j = 0; j < ising.L()*ising.L(); ++j) {
          ising.Flip();
        }
      }
      for (int i = 0; i < n_sweeps; ++i) {
        for (int j = 0; j < ising.L()*ising.L(); ++j) {
          ising.Flip();
        }
        M.push_back(fabs(ising.M()/(double(ising.L())*double(ising.L()))));
      }
      double mean = Average(M, NULL);
      double stdev = sqrt(Bootstrap(n_bootstrap, M, Average, NULL));
      fprintf(datafile, "%d %d %.9f %.9f %.9f\n", l, ising.L(), ising.T(), mean,
                                                stdev);
      fflush(datafile);
    }
  }
  fclose(datafile);
}
