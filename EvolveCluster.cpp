#include "FreeInteractionStepper.hpp"
#include "LeapfrogStepper.hpp"
#include "ReadCluster.hpp"
#include "SuperstarCluster.hpp"
#include "WriteCluster.hpp"

#include <cmath>
#include <cstdlib>
#include <iostream>

int main(int argc, char **argv) {
  if(argc != 4) {
    std::cerr << "Usage: EvolveCluster file t dt\n";
    return 1;
  }

  const double tmax = atof(argv[2]);
  const double dt = atof(argv[3]);
  const unsigned nsteps = static_cast<unsigned>(round(tmax/dt));

  SuperstarCluster cluster(1);
  ReadCluster(cluster, argv[1]);

  Steppers::Leapfrog stepper(new Steppers::Free, new Steppers::Interaction);

  for(unsigned step=0;step<nsteps;step++) {
    stepper.Step(cluster, dt);
  }
  cluster.PrepareStep();
  std::cout.precision(16);
  WriteCluster(cluster, std::cout);
  return 0;
}
