#include "Motor.h"
#include "Vehicle.h"

const int pwm_a = 3;  //PWM control for motor outputs 1 and 2
const int pwm_b = 9;  //PWM control for motor outputs 3 and 4
const int dir_a = 2;  //direction control for motor outputs 1 and 2
const int dir_b = 8;  //direction control for motor outputs 3 and 4


int power = 75;

// pwm, dir, speed
Motor motorLeft(3,2);
Motor motorRight(9,8);

Vehicle vehicle(motorLeft, motorRight, power);

void setup() {
  Serial.begin(9600);

  vehicle.setup();
}

void loop() {
  
  vehicle.forward(2000);
  vehicle.rightAngle(180, 60);
  vehicle.forward(2000);
  vehicle.leftAngle(180, 60);
  vehicle.stop();
  delay(2000);
}
