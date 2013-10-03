// Generate a cumulative mass distribution of a Hernquist model at N points
// with a=1 and M=1.

#include <cmath>
#include <cstdlib>
#include <iostream>

int main(int argc, char **argv) {
  int N;
  if(argc != 2 || (N = atoi(argv[1])) <= 0) {
    std::cerr << "Usage: HernquistProfile N" << std::endl;
    return 1;
  }

  std::cout.precision(16);
  for(int i=1;i<=N;i++) {
    const double mass = (2. * i - 1.)/(2. * N);
    const double radius = 1/(sqrt(1/mass) - 1);
    std::cout << radius << "\t" << mass << "\n";
  }

  return 0;
}
