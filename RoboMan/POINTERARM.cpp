#include "NUM.hpp"
#include "MAT.hpp"
#include "VEC.hpp"
#include <cmath>
#include "POINTERARM.hpp"
#include "FILEHANDLER.hpp"
#include <boost\algorithm\string\trim.hpp>
#include <boost\algorithm\string\split.hpp>

CMD POINTERARM::InterpretLine(std::string &line) {
  std::vector<std::string> splitVec;
  CMD command;
  boost::split(splitVec, line, boost::is_any_of("();"), boost::token_compress_on);
  if (splitVec[0] == "MOVE") {
    command.command = MOVE;
    command.coords = VEC(strtod(splitVec[1].c_str(), nullptr), strtod(splitVec[2].c_str(), nullptr), strtod(splitVec[3].c_str(), nullptr));
  }
  else
    if (splitVec[0] == "LASER") {
      command.command = LASER;
      command.val = splitVec[1] == "1" ? 1 : 0;
    }
  else
    if (splitVec[0] == "WAIT") {
      command.command = WAIT;
      command.value = strtol(splitVec[1].c_str(), nullptr, 10);
    }
  return command;
}

std::string POINTERARM::CommandToBuffer(CMD &cmd) {
  std::string buffer;
  CMD command;
  switch (cmd.command) {
    case MOVE:
      buffer = ConvertCoordinatesToAngles(cmd.coords).a.ToString() + ";" + ConvertCoordinatesToAngles(cmd.coords).b.ToString();
      break;
    case LASER:
      buffer = cmd.val ? "ON" : "NO";
      break;
    case WAIT:
      buffer = "P";
      buffer.append(std::to_string(command.value));
  }
  return buffer;
}

CMD_DEQUE POINTERARM::GenerateCommandDeque(std::vector<std::string> &lines) {
  CMD_DEQUE deque;
  for (int i = 0; i < lines.size(); ++i) {
    deque.push_back(InterpretLine(lines[i]));
  }
  return deque;
}

VEC POINTERARM::ConvertCoordinatesToAngles(VEC &coords) {
  VEC angles(
    coords.a != 0.0 ? atan(coords.a / coords.c) * 180 / M_PI : 0.0,
    coords.b != 0.0 ? atan(coords.b / coords.c) * 180 / M_PI : 0.0,
    0
  );
  return angles;
}