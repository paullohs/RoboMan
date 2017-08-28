#pragma once
#include "NUM.hpp"
#include "CMD.hpp"
#include <string>
#include <vector>
#pragma warning( disable : 4251)  

class __declspec(dllexport) FILEHANDLER {
public:
  FILEHANDLER(void);
  FILEHANDLER(const char* _filename);
  ~FILEHANDLER();
  static bool IsFileReadable(const char* _filename);
  const char* GetFileName(void) const;
  std::vector<std::string> GetLines(void);
  bool ApplySettings(void);

private:
  std::string filename;
};