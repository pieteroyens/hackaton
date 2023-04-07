#include "Vehicle.h"
#include "Motor.h"

///////////////////////////
///   Currently we have tested rotating the bot
///   Based on milliseconds 450ms == 90*
///
///   If the rotation speed is constant we can use
///    use this for other angles 450/90=5ms
///////////////////////////

const float degrees_to_milliseconds = .2;

Vehicle::Vehicle(Motor leftMotor, Motor rightMotor, int speed)
{
  _leftMotor = leftMotor;
  _rightMotor = rightMotor;

  _leftMotor.setPower(speed);
  _rightMotor.setPower(speed);

  _isSetup = false;
}

void Vehicle::setup()
{
  if (_isSetup)
    return;

  _leftMotor.setup();
  _rightMotor.setup();

  _isSetup = true;

  Serial.println("Vehicle is setup");
}

void Vehicle::forward()
{
  if (!_isSetup)
    setup();

  _leftMotor.forward();
  _rightMotor.forward();
}

void Vehicle::forward(int milliseconds)
{
  if (!_isSetup)
    setup();

  forward();

  delay(milliseconds);
  stop();
}

void Vehicle::backward()
{
  if (!_isSetup)
    setup();

  _leftMotor.backward();
  _rightMotor.backward();
}

void Vehicle::backward(int milliseconds)
{
  if (!_isSetup)
    setup();

  backward();
  delay(milliseconds);
  stop();
}

void Vehicle::left()
{
  if (!_isSetup)
    setup();

  _leftMotor.backward();
  _rightMotor.forward();

  Serial.println("Left 90 degrees");

  delay(450);

  stop();
}

void Vehicle::leftAngle(int angle)
{
  if(!_isSetup)
    setup();

  angle %= 360;

  _leftMotor.backward();
  _rightMotor.forward();

  delay(angle * degrees_to_milliseconds);

  stop();
}

void Vehicle::leftMilliseconds(int milliseconds)
{
  if(!_isSetup)
    setup();

  _leftMotor.backward();
  _rightMotor.forward();

  delay(milliseconds);

  stop();
}

void Vehicle::right()
{
  if (!_isSetup)
    setup();

  _leftMotor.forward();
  _rightMotor.backward();

  delay(450);

  stop();
}

void Vehicle::rightAngle(int angle)
{
  if(!_isSetup)
    setup();

  angle %= 360;

  _leftMotor.forward();
  _rightMotor.backward();

  delay(angle * degrees_to_milliseconds);

  stop();
}

void Vehicle::rightMilliseconds(int milliseconds)
{
  if(!_isSetup)
    setup();

  _leftMotor.forward();
  _rightMotor.backward();

  delay(milliseconds);

  stop();
}

void Vehicle::stop()
{
  if(!_isSetup)
    setup();

  _leftMotor.stop();
  _rightMotor.stop();
}

void Vehicle::setPower(int power)
{
  _leftMotor.setPower(power);
  _rightMotor.setPower(power);
}
