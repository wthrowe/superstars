#ifndef WriteCluster_hpp
#define WriteCluster_hpp

class SuperstarCluster;

#include <ostream>

// Writes a cluster to a file.
void WriteCluster(const SuperstarCluster& cluster,
		  std::ostream& stream);

#endif
