#include "FreeInteractionStepper.hpp"
#include "LeapfrogStepper.hpp"
#include "ModifiedEulerStepper.hpp"
#include "ReadCluster.hpp"
#include "SuperstarCluster.hpp"
#include "WriteCluster.hpp"

#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
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
	std::cerr << "Usage: EvolveCluster [-l] file dt t...\n";
	return 1;
      }
    }
  }

  if(argc - optind < 3) {
    std::cerr << "Usage: EvolveCluster [-l] file dt t...\n";
    return 1;
  }

  const double dt = atof(argv[optind+1]);

  SuperstarCluster cluster(1);
  ReadCluster(cluster, argv[optind]);

  Stepper *const stepper = use_leapfrog ?
    static_cast<Stepper*>(new Steppers::Leapfrog(new Steppers::Free,
						 new Steppers::Interaction)) :
    static_cast<Stepper*>(new
			  Steppers::ModifiedEuler(new Steppers::Free,
						  new Steppers::Interaction));

  int argnum = optind + 2;
  double goal_t = atof(argv[argnum]);
  for(unsigned step=0;;step++) {
    stepper->Step(cluster, dt);
    if(step * dt >= goal_t) {
      cluster.PrepareStep();
      std::string filename = ".cluster";
      filename = argv[argnum] + filename;
      std::ofstream stream(filename.c_str());
      stream.precision(16);
      WriteCluster(cluster, stream);
      if(++argnum >= argc) {
	return 0;
      }
      goal_t = atof(argv[argnum]);
    }
  }
  return 0;
}
