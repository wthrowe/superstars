#ifndef Stepper_hpp
#define Stepper_hpp

class SuperstarCluster;

// Generic class to evolve a SuperstarCluster
class Stepper {
public:
  virtual ~Stepper() { }

  virtual void Step(SuperstarCluster& cluster, double dt) const = 0;
};

#endif
