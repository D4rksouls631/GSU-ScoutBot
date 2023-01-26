#include "robot-config.h"

// which pins to connect to Distance sensor 1
const int Sensor1_EchoPIN = 12;
const int Sensor1_TrigPIN = 11;
DistSensor Sensor1(Sensor1_EchoPIN, Sensor1_TrigPIN);

// which pins to connect to Distance sensor 2
const int Sensor2_EchoPIN = 8;
const int Sensor2_TrigPIN = 9;
DistSensor Sensor2(Sensor2_EchoPIN, Sensor2_TrigPIN);

// which pins to connect to Distance sensor 3
const int Sensor3_EchoPIN = 7;
const int Sensor3_TrigPIN = 6;
DistSensor Sensor3(Sensor3_EchoPIN, Sensor3_TrigPIN);

// Drive motor Left
const int Left_directionPin = 12;
const int Left_pwmPin = 3;
const int Left_brakePin = 9;
Motor Left(Left_directionPin, Left_pwmPin, Left_brakePin);

// Drive motor Right
const int Right_directionPin = 13;
const int Right_pwmPin = 11;
const int Right_brakePin = 8;
Motor Right(Right_directionPin, Right_pwmPin, Right_brakePin);



void setup()
{

  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
}
void loop()
{

}