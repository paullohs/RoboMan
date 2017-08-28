#include "FILEHANDLER.hpp"
#include "NUM.hpp"
#include "CMD.hpp"
#include <fstream>
#include <ios>
#include <iostream>
#include <sstream>
#include <boost\algorithm\string\trim.hpp>
#include <boost\algorithm\string\split.hpp>
#include "ARDU.hpp"

FILEHANDLER::FILEHANDLER() {
}

FILEHANDLER::FILEHANDLER(const char* _filename) {
  if (!IsFileReadable(_filename)) {
    throw("File not readable.");
  } else {
    filename = _filename;
  }
}

FILEHANDLER::~FILEHANDLER() {
}

const char* FILEHANDLER::GetFileName() const {
  return filename.c_str();
}

bool FILEHANDLER::IsFileReadable(const char* _filename) {
  std::ifstream is;
  try {
    is.open(_filename, std::fstream::in);
    bool isopen = is.is_open();
    is.close();
    return isopen;
  }
  catch (std::ifstream::failure e) {
    return false;
  }
  return true;
}

std::vector<std::string> FILEHANDLER::GetLines() {
  std::ifstream is(filename.c_str());
  std::string line;
  std::stringstream ss;
  std::vector<std::string> splitVec;
  ss << is.rdbuf();
  boost::split(splitVec, ss.str(), boost::is_any_of("\n"), boost::token_compress_on);
  is.close();
  return splitVec;
}

bool FILEHANDLER::ApplySettings()
{
  std::vector<std::string> Lines = GetLines();
  std::vector<std::string> pairs;
  for (short i = 0; i < Lines.size(); ++i) {
    boost::split(pairs, Lines[i], boost::is_any_of("-"), boost::token_compress_on);
    if (pairs[0] == "comPort") {
      ARDU::comPort = strtod(pairs[1].c_str(), nullptr);
    }
  }
  return pairs.size() != NULL;
}