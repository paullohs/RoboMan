#pragma once
#include "defines.h"
#include <Servo.h>
class MyServo : public Servo {
public:
  void write(double value)
  {
    if (value < PWM_MIN)
    {  // treat values less than 544 as angles in degrees (valid values in microseconds are handled as microseconds)
      if (value < 0) value = 0;
      if (value > 180) value = 180;
      value = map(value, 0, 180, (PWM_MIN - this->min * 4), (PWM_MAX - this->max * 4));
    }
    this->writeMicroseconds(value);
  }
};