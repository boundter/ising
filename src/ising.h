#ifndef __ISING__
#define __ISING__


#include <vector>
#include <map>
#include <random> /* mt19937, uniform_real/int_distribution */
#include <cmath> /* exp, abs*/


class Ising {
  // Parameters and Variables
  double T_; // temperature
  int M_; // magnetization
  int E_; // energy
  int L_; // lattice-size
  std::vector<std::vector<int> > lattice_;
  std::map<int, double> accept_; // possible values for acceptance of flip
  std::mt19937_64 RNG_;
  std::uniform_real_distribution<double> prob_; // distribution for probability
  std::uniform_int_distribution<int> pos_; // distribution for picking position

  // Functions
  double DeltaE(int i, int j); // calculate change of energy after flip
  double DeltaM(int i, int j); // calculate change of magnetization after flip
  void CalcE(); // calculate energy of lattice
  void CalcM(); // calculate magnetization of lattice

public:
  // Acces to private
  double T() { return T_; } // get temperature
  int M() { return M_; } // get magnetization
  int E() { return E_; } // get energy
  int L() { return L_; } // get lattice-size
  std::vector<std::vector<int> > lattice() { return lattice_; } // get lattice

  // Functions
  Ising(int L, double T, long seed=600); // construct random lattice + E & M
  void Flip(); // do a flip for the metropolis-algorithm
};

#endif
