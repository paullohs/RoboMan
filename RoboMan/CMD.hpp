#pragma once
#include "VEC.hpp"
#include <deque>

class CMD;
typedef std::deque<CMD> CMD_DEQUE;
typedef int BOOL;

enum CMD_ENUM {
  MOVE,
  LASER,
  WAIT
};

class __declspec(dllexport) CMD {
public:
  CMD();
  CMD(CMD &cpy);
  CMD(CMD_ENUM &e, BOOL &b);
  CMD(CMD_ENUM &e, VEC &v);
  CMD(CMD_ENUM &e, NUM &n);
  ~CMD();
  VEC coords;
  CMD_ENUM command;
  BOOL val;
  NUM value;

private:
};
