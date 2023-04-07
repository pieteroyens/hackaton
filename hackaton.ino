#include "HUSKYLENS.h"
#include "SoftwareSerial.h"
#include "Motor.h"
#include "Vehicle.h"
#include <NewPing.h>

#define TRIGGER_PIN  9
#define ECHO_PIN     10
#define MAX_DISTANCE 400 // Maximum distance we want to measure (in centimeters).
#define MIN_DISTANCE_TO_VACCUM_WALL 20

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.


HUSKYLENS huskylens;
SoftwareSerial mySerial(10, 11); // RX, TX
//HUSKYLENS green line >> Pin 10; blue line >> Pin 11
void printResult(HUSKYLENSResult result);

const int pwm_a = 3;  //PWM control for motor outputs 1 and 2
const int pwm_b = 9;  //PWM control for motor outputs 3 and 4
const int dir_a = 2;  //direction control for motor outputs 1 and 2
const int dir_b = 8;  //direction control for motor outputs 3 and 4

int power = 75;

Motor motorLeft(3,2);
Motor motorRight(9,8);

Vehicle vehicle(motorLeft, motorRight, power);

bool full_rotation = false;
bool ball_was_seen = false;
bool ball_is_collected = false;

int degrees_rotated = 0;
const int degrees_delta = 20;

void setup() {
    Serial.begin(115200);
    mySerial.begin(9600);
    while (!huskylens.begin(mySerial))
    {
        Serial.println(F("Begin failed!"));
        Serial.println(F("1.Please recheck the \"Protocol Type\" in HUSKYLENS (General Settings>>Protocol Type>>Serial 9600)"));
        Serial.println(F("2.Please recheck the connection."));
        delay(100);
    }
    
    vehicle.setup();
}

//STRATEGY
    /**
     * Scan behaviour
     * while (result id == 0)
     *  rotate -> motorcommand
     */
    /**
     * random reposition
    */
     /**
      * Tracking&Tracing
      * Drive forward, DS1 -> suck
      */
void scanBehaviour() 
{
    Serial.println("we are scanning");
    //the motor should rotate..
    vehicle.rightAngle(degrees_delta,60);
    Serial.println("we are rotating");
    degrees_rotated += degrees_delta;
}

void repositionBehaviour() 
{
    int degrees = random(0,360);
    vehicle.rightAngle(degrees, 60);
    Serial.println("We are repositioning");
    vehicle.forward(500);
    vehicle.stop();
    full_rotation = false;
    degrees_rotated = 0;
}

void trackingBehaviour() 
{
    //initiate tracking behaviour
    Serial.println("we have found something, start tracking and tracing");
    vehicle.forward(500);
    vehicle.stop();
    degrees_rotated = 0;
}

void loop() {
    if (!huskylens.request()) Serial.println(F("Fail to request data from HUSKYLENS, recheck the connection!"));

//    if (!huskylens.available()) Serial.println(F("No block or arrow appears on the screen!"));

//    while (huskylens.available()) 
//    {      
      HUSKYLENSResult result = huskylens.read();
      int distance = sonar.ping_cm(); // Send ping, get distance in cm and print result (0 = outside set distance range)
      int distance_median = sonar.convert_cm(sonar.ping_median(10));
      
      full_rotation = degrees_rotated >= 360;

      if(result.ID == 0 && !full_rotation)
      {
        scanBehaviour();
      }
      else if(result.ID == 0 && full_rotation) 
      {
        repositionBehaviour();
      }
      else if (result.ID != 0)
      {
        trackingBehaviour();
      }
      else {
        Serial.println("Continue searching");
        Serial.println(String() + F("Total rotation ") + degrees_rotated);
        Serial.println(String() + F("The ball is seen") + ball_was_seen);
      }
//    }
}

void printResult(HUSKYLENSResult result){
    if (result.command == COMMAND_RETURN_BLOCK){
        Serial.println(String()+F("Block:xCenter=")+result.xCenter+F(",yCenter=")+result.yCenter+F(",width=")+result.width+F(",height=")+result.height+F(",ID=")+result.ID);
    }
    else if (result.command == COMMAND_RETURN_ARROW){
        Serial.println(String()+F("Arrow:xOrigin=")+result.xOrigin+F(",yOrigin=")+result.yOrigin+F(",xTarget=")+result.xTarget+F(",yTarget=")+result.yTarget+F(",ID=")+result.ID);
    }
    else{
        Serial.println("Object unknown!");
    }
}

bool isPingPongInRange(int current_distance, int min_distance_to_ball) {
  if (current_distance < min_distance_to_ball){
    return true;
  }

  return false;
}
