#ifndef SuperstarCluster_hpp
#define SuperstarCluster_hpp

#include "Superstar.hpp"

#include <cassert>
#include <vector>

// a collection of superstars
class SuperstarCluster {
public:
  // supply Newton's constant (acts as a choice of units)
  SuperstarCluster(double G) : mG(G) { }

  // default destructor ok

  void insert(const Superstar& star);

  // calculate forces and potentials
  void PrepareStep();

  // Get the stars.  Modifying the list invalidates any previous calls to
  // PrepareStep().
  const std::vector<Superstar>& Superstars() const { return mStars; }
  std::vector<Superstar>& Superstars() { return mStars; }

  // Get the force per unit mass on each superstar, in the same order
  // as the stars returned by Superstars().  PrepareStep() must be
  // called first.
  const std::vector<double>& Forces() const {
    assert(mForces.size() == mStars.size()); // not calculated
    return mForces;
  }

  // Get the potentials, in the same order as the stars returned by
  // Superstars().  PrepareStep() must be called first.
  const std::vector<double>& Potentials() const {
    assert(mPotentials.size() == mStars.size()); // not calculated
    return mPotentials;
  }

private:
  const double mG;

  std::vector<Superstar> mStars;
  // For now we'll store everything.  Depending on where this project
  // goes we may want to reconsider that decision.
  std::vector<double> mEnclosedMasses, mForces, mPotentials;
};

#endif
