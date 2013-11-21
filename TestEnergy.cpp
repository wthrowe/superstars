#include "FreeInteractionStepper.hpp"
#include "LeapfrogStepper.hpp"
#include "ModifiedEulerStepper.hpp"
#include "ReadCluster.hpp"
#include "SuperstarCluster.hpp"

#include <cstdlib>
#include <iostream>
#include <unistd.h>

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
  bool use_leapfrog = false;
  {
    int opt;
    while((opt = getopt(argc, argv, "l")) != -1) {
      switch(opt) {
      case 'l':
	use_leapfrog = true;
	break;
      default:
	std::cerr << "Usage: TestEnergy [-l] dt nsteps file\n";
	return 1;
      }
    }
  }

  if(argc - optind != 3) {
    std::cerr << "Usage: TestEnergy [-l] dt nsteps file\n";
    return 1;
  }

  const double dt = atof(argv[optind]);
  const unsigned nsteps = atoi(argv[optind+1]);

  SuperstarCluster cluster(1);

  ReadCluster(cluster, argv[optind+2]);

  Stepper *const stepper = use_leapfrog ?
    static_cast<Stepper*>(new Steppers::Leapfrog(new Steppers::Free,
						 new Steppers::Interaction)) :
    static_cast<Stepper*>(new
			  Steppers::ModifiedEuler(new Steppers::Free,
						  new Steppers::Interaction));

  std::cout.precision(16);
  std::cout << "# time\tenergy\n";

  double t = 0;
  cluster.PrepareStep();
  PrintCluster(t, cluster);
  for(unsigned step=0;step<nsteps;step++) {
    t += dt;
    stepper->Step(cluster, dt);
    cluster.PrepareStep();
    PrintCluster(t, cluster);
  }
  return 0;
}
