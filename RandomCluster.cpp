#include "Superstar.hpp"
#include "SuperstarCluster.hpp"
#include "Utils.hpp"
#include "WriteCluster.hpp"

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <random>

int main(int argc, char **argv) {
  if(argc != 6) {
    std::cerr << "Usage: RandomCluster M R T N seed\n";
    return 1;
  }

  const double totalMass = atof(argv[1]);
  const double radius = atof(argv[2]);
  const double temperature = atof(argv[3]);
  const unsigned nstars = atoi(argv[4]);
  const unsigned seed = atoi(argv[5]);

  const double mass = totalMass / nstars;

  std::mt19937_64 random_engine(seed);
  std::uniform_real_distribution<double> rcubed_dist(0,radius*radius*radius);
  std::normal_distribution<double> velocity_dist(0, sqrt(temperature/mass));

  SuperstarCluster cluster(1);

  for(unsigned n=0;n<nstars;n++) {
    const double r = std::cbrt(rcubed_dist(random_engine));
    cluster.insert(Superstar(mass,
			     mass*r*sqrt(sqr(velocity_dist(random_engine))
					 + sqr(velocity_dist(random_engine))),
			     r,
			     velocity_dist(random_engine)));
  }
  // sort
  cluster.PrepareStep();
  std::cout.precision(16);
  WriteCluster(cluster, std::cout);
}
