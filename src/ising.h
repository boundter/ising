#ifndef __ISING__
#define __ISING__

#include <vector>
#include <random>
#include <cmath>
// Debug
#include <iostream>


class Ising {
  // Parameters and Variables
  double T_;
  int M_;
  int E_;
  int L_;
  std::vector<std::vector<int> > lattice_;
  std::vector<double> accept_;
  std::mt19937_64 RNG_;
  std::uniform_real_distribution<double> prob_;
  std::uniform_int_distribution<int> pos_;

  // Functions
  void DeltaE(int i, int j);
  void DeltaM(int i, int j);
  void CalcE();
  void CalcM();

public:
  // Acces to private
  double T() { return T_; }
  int M() { return M_; }
  int E() { return E_; }
  int L() { return L_ - 1; }
  std::vector<std::vector<int> > lattice();

  // Functions
  Ising(int L, double T, long seed=600);
  void Flip();
  void PrintLattice();
};

#endif
