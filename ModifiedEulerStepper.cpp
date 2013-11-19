#include "ModifiedEulerStepper.hpp"

namespace Steppers {

  void ModifiedEuler::Step(SuperstarCluster& cluster, double dt) const {
    mpStep1->Step(cluster, dt);
    mpStep2->Step(cluster, dt);
  }

}
