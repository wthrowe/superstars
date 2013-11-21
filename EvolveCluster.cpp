#include "FreeInteractionStepper.hpp"
#include "LeapfrogStepper.hpp"
#include "ModifiedEulerStepper.hpp"
#include "ReadCluster.hpp"
#include "SuperstarCluster.hpp"
#include "WriteCluster.hpp"

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <unistd.h>

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
	std::cerr << "Usage: EvolveCluster [-l] file t dt\n";
	return 1;
      }
    }
  }

  if(argc - optind != 3) {
    std::cerr << "Usage: EvolveCluster [-l] file t dt\n";
    return 1;
  }

  const double tmax = atof(argv[optind+1]);
  const double dt = atof(argv[optind+2]);
  const unsigned nsteps = static_cast<unsigned>(round(tmax/dt));

  SuperstarCluster cluster(1);
  ReadCluster(cluster, argv[optind]);

  Stepper *const stepper = use_leapfrog ?
    static_cast<Stepper*>(new Steppers::Leapfrog(new Steppers::Free,
						 new Steppers::Interaction)) :
    static_cast<Stepper*>(new
			  Steppers::ModifiedEuler(new Steppers::Free,
						  new Steppers::Interaction));

  for(unsigned step=0;step<nsteps;step++) {
    stepper->Step(cluster, dt);
  }
  cluster.PrepareStep();
  std::cout.precision(16);
  WriteCluster(cluster, std::cout);
  return 0;
}
