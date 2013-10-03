#include "LineStream.hpp"

#include <cerrno>
#include <cstring>
#include <fstream>

LineStream::LineStream(const std::string& file) : mpStream(&std::cin) {
  if(file != "-") {
    mpStream = new std::ifstream(file.c_str());
    const int errno_save = errno;
    if(!*mpStream) {
      std::cerr << "could not open " << file << ": "
		<< strerror(errno_save) << "\n";
      throw std::exception();
    }
  }
}

LineStream::~LineStream() {
  if(mpStream != &std::cin) {
    delete mpStream;
  }
}

bool LineStream::getline(std::string& line) {
  std::getline(*mpStream, line);
  return !mpStream->eof();
}

bool LineStream::getlinestream(std::istringstream& stream) {
  std::string line;
  if(!getline(line)) return false;

  stream.str(line);
  stream.clear();
  return true;
}
