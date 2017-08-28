#pragma once
#include <string>
#include "CMD.hpp"
#include "libs\Serial.h"
#define MAX_BUFFER 128

class __declspec(dllexport) ARDU {
public:
  ARDU();
  ARDU(NUM _comPort);
  bool Open(NUM port);
  bool SendBuffer(std::string &buffer);
  bool SendBuffer(const char* buffer);
  bool SendCommand(CMD &cmd);
  std::string ReadBuffer();
  static NUM SetStaticComPort(NUM &_comPort);
  static NUM ARDU::GetStaticComPort();

  bool isOpen;
  CSerial serial;
  char readBuffer[MAX_BUFFER];
  static NUM comPort;
};