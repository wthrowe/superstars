#ifndef ReadCluster_hpp
#define ReadCluster_hpp

class SuperstarCluster;

#include <string>

// Reads a cluster from a file.
void ReadCluster(SuperstarCluster& cluster, const std::string& filename);

#endif
