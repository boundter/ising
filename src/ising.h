#ifndef __ISING__
#define __ISING__

#include <vector>
#include <map>
#include <random> /* mt19937, uniform_real/int_distribution */
#include <cmath> /* exp*/
// Debug
#include <iostream>


class Ising {
  // Parameters and Variables
  double T_;
  int M_;
  int E_;
  int L_;
  std::vector<std::vector<int> > lattice_;
  std::map<int, double> accept_;
  std::mt19937_64 RNG_;
  std::uniform_real_distribution<double> prob_;
  std::uniform_int_distribution<int> pos_;

  // Functions
  double DeltaE(int i, int j);
  double DeltaM(int i, int j);
  void CalcE();
  void CalcM();

public:
  // Acces to private
  double T() { return T_; }
  int M() { return M_; }
  int E() { return E_; }
  int L() { return L_ - 2; }
  std::vector<std::vector<int> > lattice();

  // Functions
  Ising(int L, double T, long seed=600);
  void Flip();
  // Debug!
  void PrintLattice();
};

#endif
