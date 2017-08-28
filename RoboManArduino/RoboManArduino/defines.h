#pragma once
#define SERIAL_BAUD 115200
#define SERIAL_TIMEOUT 50
#define PIN_SERVOA 8
#define PIN_SERVOB 9
#define PIN_LASER 11
#define MIN_ANGLE 0
#define START_ANGLE 145/2
#define MAX_ANGLE 145
#define PWM_MIN 800
#define PWM_MAX 2400
#define PIN_CONTROLLER_L 18
#define PIN_CONTROLLER_R 19
#define PIN_CONTROLLER_U 20
#define PIN_CONTROLLER_D 21
#define PIN_CONTROLLER_LASER 2

extern String cmd;
extern Servo servoA, servoB;
extern char i1;
extern char i2;

void inline keyLeft() {
  servoA.write(servoA.read() + 5 <= MAX_ANGLE ? servoA.read() + 5 : MAX_ANGLE);
  delayMicroseconds(1000);
}

void inline keyRight() {
  servoA.write(servoA.read() - 5 >= MIN_ANGLE ? servoA.read() - 5 : MIN_ANGLE);
  delayMicroseconds(1000);
}

void inline keyUp() {
  servoB.write(servoB.read() + 5 <= MAX_ANGLE ? servoB.read() + 5 : MAX_ANGLE);
  delayMicroseconds(1000);
}

void inline keyDown() {
  servoB.write(servoB.read() - 5 >= MIN_ANGLE ? servoB.read() - 5 : MIN_ANGLE);
  delayMicroseconds(1000);
}

void inline keyLaser() {
  digitalWrite(PIN_LASER, !digitalRead(PIN_LASER));
}

int inline translateAngle(double _angle) {
  return static_cast<int>(_angle + START_ANGLE);
}

int inline checkTranslateAngle(double _angle) {
  return (_angle >= -START_ANGLE) && (_angle <= START_ANGLE) ? _angle : MIN_ANGLE;
}