#include "SuperstarCluster.hpp"

#include <algorithm>

void SuperstarCluster::insert(const Superstar& star) {
  mStars.push_back(star);

  // mark calculated data as invalid - this does not deallocate the storage
  mForces.resize(0);
  mPotentials.resize(0);
}

namespace {
  template <class T> T sqr(const T& t) { return t*t; }

  // compare superstars based on radius
  class SuperstarComparator {
  public:
    bool operator()(const Superstar& a, const Superstar& b) const {
      return a.Radius() < b.Radius();
    }
  };
}

void SuperstarCluster::PrepareStep() {
  const std::vector<Superstar>::size_type nstars = mStars.size();
  std::sort(mStars.begin(), mStars.end(), SuperstarComparator());

  // preallocate arrays for efficiency
  mEnclosedMasses.resize(mStars.size());
  mForces.resize(mStars.size());
  mPotentials.resize(mStars.size());

  // calculate enclosed masses and forces - inside to out
  double enclosedMass = 0;
  for(std::vector<Superstar>::size_type i=0;i<nstars;i++) {
    mEnclosedMasses[i] = enclosedMass;
    mForces[i] = - mG * enclosedMass / sqr(mStars[i].Radius());

    enclosedMass += mStars[i].Mass();
  }

  // calculate potentials - outside to in
  // The space between superstars is vacuum, so the potential varies as menc/r.
  if(nstars > 0) {
    // for the outermost star we integrate to infinity
    mPotentials[nstars-1] = - mG * enclosedMass / mStars[nstars-1].Radius();

    for(std::vector<Superstar>::size_type i=nstars-1;i>0;i--) {
      mPotentials[i-1] = mPotentials[i]
	- mG * mEnclosedMasses[i]
	* (1/mStars[i-1].Radius() - 1/mStars[i].Radius());
    }
  }
}
