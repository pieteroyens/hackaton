/*
  Motor.h - a class for controlling a motor
*/

#ifndef Motor_h
#define Motor_h
#include <Arduino.h>

class Motor
{
public:
  Motor();
  Motor(int pwm_pin, int dir_pin);
  Motor(int pwm_pin, int dir_pin, int power);
  void setup();
  void forward();
  void backward();
  void move(int power, bool forward);
  void stop();
  void setPower(int power);

private:
  bool _isSetup;
  int _pwm_pin;
  int _dir_pin;
  int _power;
};
#endif