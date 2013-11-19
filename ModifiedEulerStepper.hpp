#ifndef ModifiedEulerStepper_hpp
#define ModifiedEulerStepper_hpp

#include "Stepper.hpp"

namespace Steppers {

  class ModifiedEuler: public Stepper {
  public:
    ModifiedEuler(const Stepper *step1, const Stepper *step2)
      : mpStep1(step1), mpStep2(step2) { }

    ~ModifiedEuler() {
      delete mpStep1;
      delete mpStep2;
    }

    void Step(SuperstarCluster& cluster, double dt) const;

  private:
    const Stepper *const mpStep1, *const mpStep2;
  };

}

#endif
