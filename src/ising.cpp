#include "ising.h"

Ising::Ising(int L, double T, long seed /*=500*/) {
  RNG_ = std::mt19937_64(seed);
  prob_ = std::uniform_real_distribution<double> (0., 1.);
  pos_ = std::uniform_int_distribution<int> (1, L + 1);
  L_ = L + 2;
  T_ = T;
  E_ = 0;
  M_ = 0;
  // Fill vector of all possible probs
  accept_.resize(2, 0);
  accept_[0] = exp(-4/T_);
  accept_[1] = exp(-8/T_);
  // Generate a padded lattice
  std::vector<int> row;
  row.resize(L_, 0);
  lattice_.resize(L_, row);
  for (int i = 1; i < L_ - 1; ++i) {
    for (int j = 1; j < L_ - 1; ++j) {
      double ran = prob_(RNG_);
      if (ran < 0.5){
        lattice_[i][j] = -1;
      }
      else {
        lattice_[i][j] = 1;
      }
    }
  }
  // Calculate energy and magnetization of lattice
  CalcE();
  CalcM();
}

void Ising::CalcE() {
  for (int i = 1; i < L_ - 1; ++i) {
    for (int j = 1; j < L_ - 1; ++j) {
      E_ += lattice_[i][j] * (lattice_[i + 1][j] + lattice_[i][j + 1]);
    }
  }
}

void Ising::CalcM() {
  for (int i = 1; i < L_ - 1; ++i) {
    for (int j = 1; j < L_ - 1; ++j) {
      M_ += lattice_[i][j];
    }
  }
}

void Ising::PrintLattice() {
  for (int i = 0; i < lattice_.size(); ++i) {
    std::cout << "[";
    for (int j = 0; j < lattice_[i].size(); ++j) {
      std::cout << lattice_[i][j] << ", ";
    }
    if (i != lattice_.size() - 1) {
      std::cout << std::endl;
    }
  }
  std::cout << "]" << std::endl;
}
