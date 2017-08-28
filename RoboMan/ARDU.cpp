#pragma warning(disable : 4267)
#include "ARDU.hpp"
#include "ROBOMAN.hpp"
#include "POINTERARM.hpp"
#include "libs\Serial.h"
#include "NUM.hpp"
#include "libs\SerialPort.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>

ARDU::ARDU() : isOpen(false) {
}

ARDU::ARDU(NUM _comPort) {
  Open(_comPort);
}

bool ARDU::Open(NUM port) {
  return isOpen = serial.Open(port.ToInt(), 115200);
}

bool ARDU::SendBuffer(std::string &buffer) {
  return isOpen ? serial.SendData(buffer.c_str(), strlen(buffer.c_str())) == strlen(buffer.c_str()) : false;
}

bool ARDU::SendBuffer(const char* buffer) {
  std::string stringBuffer(buffer);
  return isOpen ? serial.SendData(stringBuffer.c_str(), strlen(stringBuffer.c_str())) == strlen(stringBuffer.c_str()) : false;
}

bool ARDU::SendCommand(CMD &cmd) {
  return SendBuffer(POINTERARM::CommandToBuffer(cmd));
}

std::string ARDU::ReadBuffer() {
  unsigned char i = 0;
  if (isOpen) {
    while (!serial.ReadDataWaiting()) {
      Sleep(50);
      i++;
      if (i > 20)
        return std::string("");
    }
    int end = serial.ReadData(readBuffer, MAX_BUFFER);
    readBuffer[end] = '\0';
    return std::string(readBuffer);
  }
  return std::string("");
}

NUM ARDU::SetStaticComPort(NUM &_comPort) {
  return comPort = _comPort;
}

NUM ARDU::GetStaticComPort() {
  return comPort;
}