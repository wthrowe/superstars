// Perform interpolation on equally spaced data
// Use quadratic interpolation if we have at least 3 points

#include "LineStream.hpp"

#include <cmath>
#include <cstdlib>
#include <limits>
#include <vector>

int main(int argc, char **argv) {
  if(argc != 3) {
    std::cerr << "Usage: Interpolate file x" << std::endl;
    return 1;
  }

  const double x = atof(argv[2]);

  std::vector<std::vector<double> > data;
  std::vector<std::vector<double> >::size_type closest_entry = 0;

  {
    double closest_distance = std::numeric_limits<double>::max();
    std::vector<std::vector<double> >::size_type entry = 0;

    LineStream dataStream(argv[1]);
    std::istringstream lineStream;
    while(dataStream.getlinestream(lineStream)) {
      data.push_back(std::vector<double>());

      double v;
      while(lineStream >> v) {
	data.back().push_back(v);
      }
      if(data.back().empty()) {
	std::cerr << "No data on line " << entry << ": "
		  << lineStream.str() << "\n";
	return 1;
      }
      if(fabs(data.back().front() - x) < closest_distance) {
	closest_entry = entry;
	closest_distance = fabs(data.back().front() - x);
      }

      entry++;
    }
  }

  if(data.size() < 2) {
    std::cerr << "Not enough data\n";
    return 1;
  }

  std::cout.precision(16);
  if(data.size() == 2) {
    // linear interpolate
    if(data[0].size() != data[1].size()) {
      std::cerr << "Columns don't match\n";
      return 1;
    }

    std::vector<double> coeffs(2);
    coeffs[0] = (data[1][0] - x) / (data[1][0] - data[0][0]);
    coeffs[1] = (x - data[0][0]) / (data[1][0] - data[0][0]);

    for(std::vector<double>::size_type i=0;i<data[0].size();i++) {
      std::cout << coeffs[0]*data[0][i] + coeffs[1]*data[1][i]
		<< (i==data[0].size()-1 ? "\n" : "\t");
    }
  } else {
    // quadratic interpolation
    if(closest_entry == 0) closest_entry++;
    if(closest_entry == data.size()-1) closest_entry--;

    const std::vector<double>& row0 = data[closest_entry-1];
    const std::vector<double>& row1 = data[closest_entry];
    const std::vector<double>& row2 = data[closest_entry+1];

    if(row0.size() != row1.size() || row0.size() != row2.size()) {
      std::cerr << "Columns don't match\n";
      return 1;
    }

    const double offset = (x - row1[0]) / (row2[0] - row1[0]);

    std::vector<double> coeffs(3);
    coeffs[0] = 0.5 * offset * (offset - 1);
    coeffs[1] = 1 - offset * offset;
    coeffs[2] = 0.5 * offset * (offset + 1);

    for(std::vector<double>::size_type i=0;i<row0.size();i++) {
      std::cout << coeffs[0]*row0[i] + coeffs[1]*row1[i] + coeffs[2]*row2[i]
		<< (i==row0.size()-1 ? "\n" : "\t");
    }
  }

  return 0;
}
