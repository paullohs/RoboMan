#include <Servo.h>
#include "defines.h"
String cmd;
Servo servoA, servoB;
char i1 = 0;
char i2 = 0;

void setup(void) {
  Serial.begin(SERIAL_BAUD);
  Serial.setTimeout(SERIAL_TIMEOUT);
  pinMode(PIN_LASER, OUTPUT);
  digitalWrite(PIN_LASER, HIGH);
  digitalWrite(PIN_SERVOA, OUTPUT);
  digitalWrite(PIN_SERVOB, OUTPUT);
  servoA.attach(PIN_SERVOA, PWM_MIN, PWM_MAX);
  servoB.attach(PIN_SERVOB, PWM_MIN, PWM_MAX);
  servoA.write(START_ANGLE);
  servoB.write(START_ANGLE);
  pinMode(PIN_CONTROLLER_R, INPUT_PULLUP);
  pinMode(PIN_CONTROLLER_L, INPUT_PULLUP);
  pinMode(PIN_CONTROLLER_U, INPUT_PULLUP);
  pinMode(PIN_CONTROLLER_D, INPUT_PULLUP);
  pinMode(PIN_CONTROLLER_LASER, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PIN_CONTROLLER_LASER), keyLaser, FALLING);
  attachInterrupt(digitalPinToInterrupt(PIN_CONTROLLER_L), keyLeft, FALLING);
  attachInterrupt(digitalPinToInterrupt(PIN_CONTROLLER_R), keyRight, FALLING);
  attachInterrupt(digitalPinToInterrupt(PIN_CONTROLLER_U), keyUp, FALLING);
  attachInterrupt(digitalPinToInterrupt(PIN_CONTROLLER_D), keyDown, FALLING);
}

void loop(void) {
  if (Serial.available() > NULL) {
    cmd = Serial.readStringUntil('\n');
    switch (cmd[0]) {
      case 'O': 
        switch (cmd[1]) {
          case 'N': 
            digitalWrite(PIN_LASER, LOW);
            break;
        }
        break;
      case 'N': 
        switch (cmd[1]) {
          case 'O': 
            digitalWrite(PIN_LASER, HIGH);
            break;
        }
        break;
      case 'P': 
        if (!isAlpha(cmd[1])) {
          delay(strtol(&cmd[1], nullptr, 10));
        }
        break;
      case 'Q': 
        Serial.write(String(String(servoA.read()) + ";" + String(servoB.read()) + ";" + String(!digitalRead(PIN_LASER) ? "1" : "0") + "\n").c_str());
        break;
      case '(': 
        i1 = cmd.indexOf(';');
        if (i1 > 0) {
          servoA.write(translateAngle(checkTranslateAngle(strtod(&cmd[1], nullptr))));
          servoB.write(translateAngle(checkTranslateAngle(strtod(&cmd[i1 + 1], nullptr))));
        }
        break;
      default: 
        i1 = cmd.indexOf(';');
        i2 = cmd.length() > i1+1 ? cmd.indexOf(';', i1+1) : -1;
        if (i1 > NULL) {
          if (cmd[0] == '-' || cmd[0] == '+') {
            servoA.write(checkTranslateAngle(servoA.read() + static_cast<int>(strtod(&cmd[0], nullptr))));
          } else {
            servoA.write(static_cast<int>(strtod(&cmd[0], nullptr)));
          }
          if (cmd[i1 + 1]== '-' || cmd[i1 + 1] == '+') {
            servoB.write(checkTranslateAngle(servoB.read() + static_cast<int>(strtod(&cmd[i1 + 1], nullptr))));
          } else {
            servoA.write(static_cast<int>(strtod(&cmd[i1 + 1], nullptr)));
          }
          if (i2 > NULL) {
            digitalWrite(PIN_LASER, strtol(&cmd[i2+1], nullptr, 0xA) ? HIGH : LOW);
          }
        }
        break;
    }
  }
}