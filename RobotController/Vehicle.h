/*
    vehicle.h - class for controlling a vehicle with two motors    
*/

#ifndef Vehicle_h
#define Vehicle_h
#include "Motor.h"
class Vehicle
{
  public:
      Vehicle(Motor leftMotor, Motor rightMotor, int speed);
      void setup();
      void forward();
      void forward(int milliseconds);
      void backward();
      void backward(int milliseconds);
      void left();
      void leftAngle(int angle);
      void leftMilliseconds(int milliseconds);
      void right();
      void rightAngle(int angle);
      void rightMilliseconds(int milliseconds);      
      void stop();
      void setPower(int speed);

  private:
      bool _isSetup;
      Motor _leftMotor;
      Motor _rightMotor;
};
#endif