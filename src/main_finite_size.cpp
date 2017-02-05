#include <cstdio>
#include <string>
#include <vector>
#include "ising.h"
#include "func.h"

using namespace std;

#define NELEMS(x)  (sizeof(x) / sizeof((x)[0])) // length of an array

int L[5] = {20, 40, 60, 80, 100};
double n_T = 50, T, T_c = 2.269;
double n_trans = 50000;
double n_sweeps = 50000;
int n_bootstrap = 1000;
string folder = "result/data/";


double Variance(const vector<double>& data) {
  double mean = 0, var = 0;
  for (int i = 0; i < data.size(); ++i) {
    mean += data[i];
  }
  mean /= double(data.size());
  for (int i = 0; i < data.size(); ++i) {
    var += (data[i] - mean)*(data[i] - mean);
  }
  return var/double(data.size());
}


double Susceptibility(const vector<double>& data, void* params) {
  // cons[0] = T, cons[1] = L
  double* cons = (double *) params;
  double var = Variance(data);
  return cons[1]*cons[1]/cons[0]*var;
}


int main() {
  string filename = folder + "finite.dat";
  FILE * datafile = fopen(filename.c_str(), "w");

  for (int l = 0; l < NELEMS(L); ++l) {
    double T_max = T_c + 10*T_c/L[l];
    double T_min = T_c - 10*T_c/L[l];
    double T_step = (T_max - T_min)/(n_T - 1);
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
      double cons[] = {ising.T(), double(ising.L())};
      void* params = &cons;
      double susc = Susceptibility(M, params);
      double stdev = sqrt(Bootstrap(n_bootstrap, M, Susceptibility,params));
      fprintf(datafile, "%d %d %.9f %.9f %.9f\n", l, ising.L(), ising.T(), susc,
                                                stdev);
      fflush(datafile);
    }
  }
  fclose(datafile);
}
