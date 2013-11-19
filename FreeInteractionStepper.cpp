#include "FreeInteractionStepper.hpp"

#include "Superstar.hpp"
#include "SuperstarCluster.hpp"
#include "Utils.hpp"

#include <cmath>
#include <vector>

namespace Steppers {

  void Free::Step(SuperstarCluster& cluster, double dt) const {
    std::vector<Superstar>& stars = cluster.Superstars();

    for(std::vector<Superstar>::iterator starit = stars.begin();
	starit != stars.end();
	++starit) {
      const double r = starit->Radius();
      const double v = starit->Velocity();
      const double sqrLbymr =
	sqr(starit->AngularMomentum() / (starit->Mass() * r));

      starit->Radius() = sqrt(sqr(r + v*dt) + sqrLbymr * sqr(dt));
      starit->Velocity() =
	(r * v + (sqr(v) + sqrLbymr) * dt) / starit->Radius();
    }
  }

  void Interaction::Step(SuperstarCluster& cluster, double dt) const {
    cluster.PrepareStep();
    std::vector<Superstar>& stars = cluster.Superstars();

    for(std::vector<Superstar>::size_type i = 0;i<stars.size();i++) {
      stars[i].Velocity() += cluster.Forces()[i] * dt;
    }
  }

}
