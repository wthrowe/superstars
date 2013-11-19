#ifndef FreeInteractionStepper_hpp
#define FreeInteractionStepper_hpp

#include "Stepper.hpp"

namespace Steppers {

  // Evolve a cluster under the free-particle Hamiltonian.
  class Free: public Stepper {
  public:
    void Step(SuperstarCluster& cluster, double dt) const;
  };

  // Evolve a cluster under the interaction Hamiltonian (the part
  // other than used by the Free Stepper).
  class Interaction: public Stepper {
  public:
    void Step(SuperstarCluster& cluster, double dt) const;
  };

}

#endif
