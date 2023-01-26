// robot-config.h
#ifndef robot-config_h
#define robot-config_h

#include <Arduino.h>

class Motor
{
private:
    int directionPin;
    int pwmPin;
    int brakePin;

public:
    Motor(int directionPin, int pwmPin, int brakePin);
    void spin(bool direction,int power);
    void stop();
};

class DistSensor
{
private:
    int EchoPIN;
    int TrigPIN;

public:
    DistSensor(int EchoPin, int TrigPin);
    float getDistance();
};

#endif
