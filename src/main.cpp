#include "ising.h"
#include <cstdio>
#include <string>

using namespace std;

#define NELEMS(x)  (sizeof(x) / sizeof((x)[0])) // length of an array

int L[9] = {20, 30, 40, 50, 60, 70, 80, 90, 100};
double T[10] = {0.5, 0.75, 1, 1.25, 1.5, 1.75, 2., 2.25, 2.5, 2.75};
double n_sweeps = 100000;
string folder = "result/data/";


// ----------------------------------------------------------------------------
// Functions
// ----------------------------------------------------------------------------

void WriteHeader(Ising ising, FILE * datafile) {
  fprintf(datafile, "# L= %d , T= %.9f \n", ising.L(), ising.T());
}

// ----------------------------------------------------------------------------
// Main
// ----------------------------------------------------------------------------

int main() {
  for (int l = 0; l < NELEMS(L); ++l) {
    for (int t = 0; t < NELEMS(T); ++t) {
      Ising ising (L[l], T[t]);
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
