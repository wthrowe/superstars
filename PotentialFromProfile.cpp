#include "Superstar.hpp"
#include "SuperstarCluster.hpp"

#include <cerrno>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

int main(int argc, char **argv) {
  if(argc != 2) {
    std::cerr << "Usage: PotentialFromProfile file\n";
    return 1;
  }

  std::istream *profileStream = &std::cin;
  if(argv[1] != std::string("-")) {
    profileStream = new std::ifstream(argv[1]);
    const int errno_save = errno;
    if(!profileStream) {
      std::cerr << "could not open " << argv[1] << ": "
		<< strerror(errno_save) << "\n";
      return 1;
    }
  }

  SuperstarCluster cluster(1);

  {
    double totalMass = 0;
    while(true) {
      std::string line;
      std::getline(*profileStream, line);
      if(profileStream->eof()) break;

      std::istringstream lineStream(line);

      double radius, mass;
      if(!(lineStream >> radius >> mass)) {
	std::cerr << "Error processing input line: " << line << "\n";
	return 1;
      }

      // we're reading in a cumulative mass profile, but we need a shell mass
      cluster.insert(Superstar(mass - totalMass, radius));
      totalMass = mass;
    }
  }
  if(profileStream != &std::cin) {
    delete profileStream;
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
