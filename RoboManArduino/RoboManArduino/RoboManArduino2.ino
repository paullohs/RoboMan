#include <Servo.h>
#define SERIAL_BAUD 9600
#define PIN_SERVOA 8
#define PIN_SERVOB 9
#define PIN_LASER 11

 
String cmd;
double angleA, angleB;
Servo servoA, servoB;

void setup(void) {
  Serial.begin(SERIAL_BAUD);
  servoA.attach(PIN_SERVOA, 800, 2400);
  servoB.attach(PIN_SERVOB, 800, 2400);
  servoA.write(START_ANGLE);
  servoB.write(START_ANGLE);
  digitalWrite(PIN_LASER, LOW);
}

void loop(void) {
  if (Serial.available() > 0) {
    cmd = Serial.readStringUntil('\n');
    if (isAlpha(cmd[0])) {
      if (cmd == "ON")
        digitalWrite(PIN_LASER, HIGH);
      else
        if (cmd == "NO")
          digitalWrite(PIN_LASER, LOW);
        else
          if (cmd[0] == 'P' && !isAlpha(cmd[1]))
            delay(strtol(&cmd[1], NULL, 10));
    }
    else {
      static int i;
      for (i = 0; i < cmd.length(); ++i) {
        if (cmd[i] == ';')
          break;
      }
      angleA = strtod(&cmd[0], NULL);
      angleB = strtod(&cmd[i+1], NULL);
      servoA.write(angleA);
      servoB.write(angleB);
    }
  }
}