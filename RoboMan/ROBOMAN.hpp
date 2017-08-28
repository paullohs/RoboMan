#pragma once
#include "FILEHANDLER.hpp"
#include "ARDU.hpp"
#include "CMD.hpp"

class __declspec(dllexport) RoboMan {
public:
  static int RoboMain(int argc, char* argv[]);
  static ARDU *ardu;
  static FILEHANDLER *commandFile;
  static CMD_DEQUE *commandDeque;
  static FILEHANDLER *settingsFile;
};