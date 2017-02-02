#include <cstdio>
#include <string>
#include <vector>
#include "ising.h"
#include "func.h"

using namespace std;

#define NELEMS(x)  (sizeof(x) / sizeof((x)[0])) // length of an array

int L[5] = {20, 60, 100};
double T[6] = {1., 2., 2.2, 2.3, 3., 4.} ;
double n_trans = 20000;
double n_sweeps = 100000;
string folder = "result/data/";

int main() {
  for (int l = 0; l < NELEMS(L); ++l) {

    Ising ising(L[l], 0);
    ising.SetUniformState();

    char file[128];
    sprintf(file, "corr_%d.dat", ising.L());
    string filename = folder + file;
    FILE * datafile = fopen(filename.c_str(), "w");
    WriteHeader(ising, datafile);

    for (int t = 0; t < NELEMS(T); ++t) {
      ising.SetT(T[t]);

      for (int i = 0; i < n_trans; ++i) {
        for (int j = 0; j < ising.L()*ising.L(); ++j) {
          ising.Flip();
        }
      }

      for (int i = 0; i < n_sweeps; ++i) {
        for (int j = 0; j < ising.L()*ising.L(); ++j) {
          ising.Flip();
        }
        fprintf(datafile, "%d %d %.9f %d\n", t, i, ising.T(), ising.M());
      }
      fflush(datafile);
    }
    fclose(datafile);
  }
}
