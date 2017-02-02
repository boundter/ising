#include <cstdio>
#include <string>
#include "ising.h"
#include "func.h"

using namespace std;

#define NELEMS(x)  (sizeof(x) / sizeof((x)[0])) // length of an array

int L[1] = {100};
double T[7] = {1.0, 2.0, 2.2, 2.3, 2.5, 3.0, 4.0};
double n_sweeps = 100000;
string folder = "result/data/";


// ----------------------------------------------------------------------------
// Main
// ----------------------------------------------------------------------------

int main() {
  for (int l = 0; l < NELEMS(L); ++l) {
    Ising ising (L[l], 0);
    ising.SetUniformState();
    for (int t = 0; t < NELEMS(T); ++t) {
      ising.SetT(T[t]);
      
      char file[128];
      sprintf(file, "M_%d_%.3f.dat", ising.L(), ising.T());
      string filename = folder + file;
      FILE * datafile = fopen(filename.c_str(), "w");
      WriteHeader(ising, datafile);

      for (int i = 1; i <= n_sweeps; ++i) {
        for (int j = 0; j < ising.L()*ising.L(); ++j) {
          ising.Flip();
        }
        fprintf(datafile, "%d %d %d\n", i, ising.E(), ising.M());
        fflush(datafile);
      }
      fclose(datafile);

      // snapshot
      sprintf(file, "snap_%d_%.3f.dat", ising.L(), ising.T());
      filename = folder + file;
      datafile = fopen(filename.c_str(), "w");
      WriteHeader(ising, datafile);
      vector<vector<int> > lattice = ising.lattice();

      for (int i = 0; i < ising.L(); ++i) {
        for (int j = 0; j < ising.L(); ++j) {
          fprintf(datafile, "%.d ", lattice[i][j]);
        }
        fprintf(datafile, "\n");
      }

      fclose(datafile);
    }
  }
  return 0;
}
