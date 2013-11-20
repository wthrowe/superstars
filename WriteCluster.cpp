#include "WriteCluster.hpp"

#include "Superstar.hpp"
#include "SuperstarCluster.hpp"

#include <fstream>
#include <vector>

void WriteCluster(const SuperstarCluster& cluster,
		  std::ostream& stream) {
  stream << "# mass\tangmom\tradius\tvelocity\n";

  for(std::vector<Superstar>::const_iterator starit =
	cluster.Superstars().begin();
      starit != cluster.Superstars().end();
      ++starit) {
    stream << starit->Mass() << "\t"
	   << starit->AngularMomentum() << "\t"
	   << starit->Radius() << "\t"
	   << starit->Velocity() << "\n";
  }
}
