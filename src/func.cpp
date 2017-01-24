#include "func.h"

void WriteHeader(Ising ising, FILE * datafile) {
  fprintf(datafile, "# L= %d , T= %.9f \n", ising.L(), ising.T());
}
