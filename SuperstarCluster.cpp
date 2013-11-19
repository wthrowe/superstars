#include "SuperstarCluster.hpp"

#include "Utils.hpp"

#include <algorithm>

void SuperstarCluster::insert(const Superstar& star) {
  mStars.push_back(star);

  // mark calculated data as invalid - this does not deallocate the storage
  mForces.resize(0);
  mPotentials.resize(0);
}

namespace {
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
    mForces[i] =
      - mG * (enclosedMass + 0.5*mStars[i].Mass()) / sqr(mStars[i].Radius());

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

double SuperstarCluster::Energy() const {
  assert(mPotentials.size() == mStars.size()); // not calculated

  double energy = 0;
  for(std::vector<Superstar>::size_type i = 0;i<mStars.size();i++) {
    const Superstar& star = mStars[i];
    energy += 0.5 * (star.Mass() * sqr(star.Velocity())
		     + sqr(star.AngularMomentum()/star.Radius())/star.Mass()
		     + star.Mass() * mPotentials[i]);
  }
  return energy;
}
