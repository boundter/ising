#include "ising.h"


Ising::Ising(int L, double T, long seed /*=600*/) {
  RNG_ = std::mt19937_64(seed);
  prob_ = std::uniform_real_distribution<double> (0., 1.);
  pos_ = std::uniform_int_distribution<int> (1, L);
  L_ = L + 2;
  T_ = T;
  // Fill vector of all possible probs to accept a flip to save computation time
  accept_[2] = exp(-2/T_);
  accept_[4] = exp(-4/T_);
  accept_[6] = exp(-6/T_);
  accept_[8] = exp(-8/T_);
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
  // It doesn't save directly to E_, so it can be called everytime
  double E = 0;
  for (int i = 1; i < L_ - 1; ++i) {
    for (int j = 1; j < L_ - 1; ++j) {
      E -= lattice_[i][j] * (lattice_[i + 1][j] + lattice_[i][j + 1]);
    }
  }
  E_ = E;
}


void Ising::CalcM() {
  // It doesn't save directly to M_, so it can be called everytime
  double M = 0;
  for (int i = 1; i < L_ - 1; ++i) {
    for (int j = 1; j < L_ - 1; ++j) {
      M += lattice_[i][j];
    }
  }
  M_ = M;
}


double Ising::DeltaE(int i, int j) {
  // The energy_after a flip is -energy_before the flip, so the change in energy
  // is
  // energy_after - energy_before = energy_after + energy_after = 2 energy_after
  // The used latice is the one before the flip, because the energy is measured
  // with reversed sign. Two equal spins give +1, not the needed -1, but this
  // just means, that energy_after is the energy of the lattice before the flip.
  double E_after = lattice_[i][j]*(lattice_[i+1][j] + lattice_[i-1][j] +
                                   lattice_[i][j+1] + lattice_[i][j-1]);
  return 2*E_after;
}


double Ising::DeltaM(int i, int j) {
  // The magnetization_after a flip is -magnetization_before the flip, so the
  // change in magnetization is
  // M_after - M_before = - M_before - M_before = -2 M_before
  double M_before = lattice_[i][j];
  return -2*M_before;
}


void Ising::Flip() {
  // Make one flip using the metropolis-algorithm. All possible acceptance
  // probabilities are saved in a map accept_ to reduce the computing time
  // needded to calculate the exp-function.
  int i = pos_(RNG_), j = pos_(RNG_);
  double delta_E = DeltaE(i, j);
  if (delta_E <= 0) {
    E_ += delta_E;
    M_ += DeltaM(i, j);
    lattice_[i][j] *= -1;
  }
  else {
    double ran = prob_(RNG_);
    if (ran < accept_[delta_E]) {
      E_ += delta_E;
      M_ += DeltaM(i, j);
      lattice_[i][j] *= -1;
    }
  }
}


std::vector<std::vector<int> > Ising::lattice() {
  std::vector<std::vector<int> > lattice;
  for (int i = 1; i < L_ - 1; ++i) {
    std::vector<int> row;
    for (int j = 1; j < L_- 1; ++j) {
      row.push_back(lattice_[i][j]);
    }
    lattice.push_back(row);
  }
  return lattice;
}
