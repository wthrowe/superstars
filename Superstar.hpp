#ifndef Superstar_hpp
#define Superstar_hpp

// A spherical shell of stars
class Superstar {
public:
  Superstar(double mass, double radius) : mMass(mass), mRadius(radius) { }

  // default copy constructor, operator=, destructor ok

  double Mass() const { return mMass; }
  double Radius() const { return mRadius; }
private:
  double mMass;
  double mRadius;
  // velocity, angular momentum...
};

#endif
