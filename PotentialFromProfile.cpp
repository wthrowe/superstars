#include "LineStream.hpp"
#include "Superstar.hpp"
#include "SuperstarCluster.hpp"

#include <iostream>
#include <sstream>
#include <string>

int main(int argc, char **argv) {
  if(argc != 2) {
    std::cerr << "Usage: PotentialFromProfile file\n";
    return 1;
  }

  SuperstarCluster cluster(1);

  {
    double totalMass = 0;

    LineStream profileStream(argv[1]);
    std::istringstream lineStream;
    while(profileStream.getlinestream(lineStream)) {
      double radius, mass;
      if(!(lineStream >> radius >> mass)) {
	std::cerr << "Error processing input\n";
	return 1;
      }

      // We're reading in a cumulative mass profile, but we need a shell mass.
      // We don't are about dynamics for this, so set velocities to zero.
      cluster.insert(Superstar(mass - totalMass, 0, radius, 0));
      totalMass = mass;
    }
  }

  cluster.PrepareStep();

  const std::vector<Superstar>& stars = cluster.Superstars();
  const std::vector<double>& forces = cluster.Forces();
  const std::vector<double>& potentials = cluster.Potentials();

  std::cout.precision(16);
  for(std::vector<Superstar>::size_type i=0;i<stars.size();i++) {
    std::cout << stars[i].Radius() << "\t" << forces[i] << "\t"
	      << potentials[i] << "\n";
  }

  return 0;
}
