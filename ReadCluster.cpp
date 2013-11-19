#include "ReadCluster.hpp"

#include "LineStream.hpp"
#include "SuperstarCluster.hpp"

#include <sstream>

void ReadCluster(SuperstarCluster& cluster, const std::string& filename) {
  LineStream fileStream(filename);
  std::istringstream lineStream;
  while(fileStream.getlinestream(lineStream)) {
    // Skip comments
    if(lineStream.peek() == '#') continue;
    double mass, angularMomentum, radius, velocity;
    if(!(lineStream >> mass >> angularMomentum >> radius >> velocity)) {
      throw std::exception();
    }

    cluster.insert(Superstar(mass, angularMomentum, radius, velocity));
  }
}
