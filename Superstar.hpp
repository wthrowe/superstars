#ifndef Superstar_hpp
#define Superstar_hpp

// A spherical shell of stars
class Superstar {
public:
  Superstar(double mass, double angularMomentum,
	    double radius, double velocity)
    : mMass(mass), mAngularMomentum(angularMomentum),
      mRadius(radius), mVelocity(velocity) { }

  // default copy constructor, operator=, destructor ok

  double Mass() const { return mMass; }
  double AngularMomentum() const { return mAngularMomentum; }

  double Radius() const { return mRadius; }
  double& Radius() { return mRadius; }

  double Velocity() const { return mVelocity; }
  double& Velocity() { return mVelocity; }
private:
  double mMass, mAngularMomentum;
  double mRadius, mVelocity;
};

#endif
