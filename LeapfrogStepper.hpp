#ifndef LeapfrogStepper_hpp
#define LeapfrogStepper_hpp

#include "Stepper.hpp"

namespace Steppers {

  class Leapfrog: public Stepper {
  public:
    Leapfrog(const Stepper *step1, const Stepper *step2)
      : mpStep1(step1), mpStep2(step2) { }

    ~Leapfrog() {
      delete mpStep1;
      delete mpStep2;
    }

    void Step(SuperstarCluster& cluster, double dt) const;

  private:
    const Stepper *const mpStep1, *const mpStep2;
  };

}

#endif
