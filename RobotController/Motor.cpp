#include <Arduino.h>
#include "Motor.h"

/////////////////////////////////////
/// digitalWrite for direction:
///   - LOW = forward
///   - HIGH = backward
///   - Example: digitalWrite(_dir_pin, LOW);
///
/// analogwrite for motorspeed:
///   - value/255 = % duty cycle
///   - Example: analogWrite(_pwm_pin, 100); is equeal to 39% duty
////////////////////////////////////

Motor::Motor() {
  _power = 0;
  _isSetup = false;
}

Motor::Motor(int pwm_pin, int dir_pin) {
  _pwm_pin = pwm_pin;
  _dir_pin = dir_pin;
  _power = 0;

  _isSetup = false;
}

Motor::Motor(int pwm_pin, int dir_pin, int power) {
  _pwm_pin = pwm_pin;
  _dir_pin = dir_pin;
  _power = power;

  _isSetup = false;
}

void Motor::setup() {
  if (_isSetup)
    return;

  pinMode(_pwm_pin, OUTPUT);
  pinMode(_dir_pin, OUTPUT);

  _isSetup = true;
}

void Motor::forward() {
  if (!_isSetup)
    setup();

  digitalWrite(_dir_pin, LOW);
  analogWrite(_pwm_pin, _power);
}

void Motor::backward() {
  if (!_isSetup)
    setup();

  digitalWrite(_dir_pin, HIGH);
  analogWrite(_pwm_pin, _power);
}

void Motor::move(int power, bool forward) {
  if (!_isSetup)
    setup();

  digitalWrite(_dir_pin, forward ? LOW : HIGH);
  analogWrite(_pwm_pin, power);
}

void Motor::stop() {
  if (!_isSetup)
    setup();

  analogWrite(_pwm_pin, 0);
}

int Motor::getPower() {
  return _power;
}

void Motor::setPower(int power) {
  if (power > 255)
    power = 255;
  else if (power < 0)
    power = 0;

  _power = power;
}