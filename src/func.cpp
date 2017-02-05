#include "func.h"

void WriteHeader(Ising ising, FILE * datafile) {
  fprintf(datafile, "# L= %d , T= %.9f \n", ising.L(), ising.T());
}


void UpdateStat(const double& value, double& mean, double& M2, double& n) {
  n += 1;
  double delta = value - mean;
  mean += delta/n;
  double delta_2 = value - mean;
  M2 += delta*delta_2;
}


double AverageVec(const std::vector<double>& data) {
  double mean = 0;
  for (int i = 0; i < data.size(); ++i) {
    mean += data[i];
  }
  return mean/double(data.size());
}


double AverageSquareVec(const std::vector<double>& data) {
  double mean = 0;
  for (int i = 0; i < data.size(); ++i) {
    mean += data[i]*data[i];
  }
  return mean/double(data.size());
}


double Bootstrap(const int& n, std::vector<double>& values,
                 double (*func)(const std::vector<double>&, void* params),
                 void* params) {
  std::mt19937_64 RNG(time(NULL));
  std::uniform_int_distribution<int> dist(0, values.size() - 1);
  std::vector<double> pick(values.size());
  std::vector<double> quantity;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < values.size(); ++j) {
      pick[j] = values[dist(RNG)];
    }
    quantity.push_back(func(pick, params));
  }
  double mean = AverageVec(quantity);
  double mean_sqr = AverageSquareVec(quantity);
  return mean_sqr - mean*mean;
}
