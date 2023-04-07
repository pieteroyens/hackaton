#include "HUSKYLENS.h"
#include "SoftwareSerial.h"
#include "Motor.h"
#include "Vehicle.h"

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

Vehicle vehicle(motorlLeft, motorRight, power);

bool full_rotation = false;
bool ball_was_seen = false;
bool ball_is_collected = false;

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




void loop() {
    if (!huskylens.request()) Serial.println(F("Fail to request data from HUSKYLENS, recheck the connection!"));
//    else if(!huskylens.isLearned()) Serial.println(F("Nothing learned, press learn button on HUSKYLENS to learn one!"));
    if(!huskylens.available()) Serial.println(F("No block or arrow appears on the screen!"));
//    else
//    {
//        Serial.println(F("###########"));
//        while (huskylens.available())
//        {
//            HUSKYLENSResult result = huskylens.read();
//            printResult(result);
//        }    
//    }

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
    while (huskylens.available()) 
    {      
      HUSKYLENSResult result = huskylens.read();
      if(result.ID == 0)
      {
        //motor command;
        Serial.println("we are scanning");
        //the motor should rotate..
        vehicle.rightAngle(360);
        full_rotation = true
      }
      else if(result.ID == 0 && fullRotation) 
      {
        degrees = random(0,360);
        vehicle.rightAngle(degrees);
        vehicle.forward(500);
        vehicle.stop();
        full_rotation = false;
      }
      else 
      {
        //initiate tracking behaviour
        Serial.println("we have found something, start tracking and tracing");
        vehicle.forward(500);
        vehicle.stop();
      }
    }
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
