#ifndef LineStream_hpp
#define LineStream_hpp

#include <iostream>
#include <sstream>

// A wrapper for istream to handle common data stuff.  Manages error
// handling on opening and reading from stdin.
class LineStream {
public:
  LineStream(const std::string& file);

  ~LineStream();

  // return false on eof, true otherwise
  bool getline(std::string& line);
  bool getlinestream(std::istringstream& stream);

private:
  std::istream *mpStream;
};

#endif
