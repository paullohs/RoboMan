#pragma once
#include "CMD.hpp"
#include "NUM.hpp"
#include "VEC.hpp"
#include <vector>

class __declspec(dllexport) POINTERARM {
public:
  static CMD InterpretLine(std::string &line);
  static std::string CommandToBuffer(CMD & cmd);
  static CMD_DEQUE GenerateCommandDeque(std::vector<std::string> &lines);
  static inline VEC ConvertCoordinatesToAngles(VEC & coords);

private:
};