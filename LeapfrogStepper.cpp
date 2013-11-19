#include "LeapfrogStepper.hpp"

namespace Steppers {

  void Leapfrog::Step(SuperstarCluster& cluster, double dt) const {
    mpStep1->Step(cluster, dt/2);
    mpStep2->Step(cluster, dt);
    mpStep1->Step(cluster, dt/2);
  }

}
