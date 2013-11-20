#include "FreeInteractionStepper.hpp"
#include "LeapfrogStepper.hpp"
#include "ReadCluster.hpp"
#include "SuperstarCluster.hpp"

#include <cstdlib>
#include <iostream>

void PrintCluster(double t, const SuperstarCluster& cluster) {
  std::cout << t << "\t" << cluster.Energy();
  for(std::vector<Superstar>::const_iterator starit =
	cluster.Superstars().begin();
      starit != cluster.Superstars().end();
      ++starit) {
    std::cout << "\t" << starit->Radius();
  }
  std::cout << "\n";
}

int main(int argc, char **argv) {
  if(argc != 4) {
    std::cerr << "Usage: TestEnergy dt nsteps file\n";
    return 1;
  }

  const double dt = atof(argv[1]);
  const unsigned nsteps = atoi(argv[2]);

  SuperstarCluster cluster(1);

  ReadCluster(cluster, argv[3]);

  Steppers::Leapfrog stepper(new Steppers::Free, new Steppers::Interaction);

  std::cout.precision(16);
  std::cout << "# time\tenergy\n";

  double t = 0;
  cluster.PrepareStep();
  PrintCluster(t, cluster);
  for(unsigned step=0;step<nsteps;step++) {
    t += dt;
    stepper.Step(cluster, dt);
    cluster.PrepareStep();
    PrintCluster(t, cluster);
  }
  return 0;
}
