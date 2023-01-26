// robot-config.cpp
#include "robot-config.h"

Motor::Motor(int directionPin, int pwmPin, int brakePin)
{
    pinMode(directionPin, OUTPUT);
    pinMode(pwmPin, OUTPUT);
    pinMode(brakePin, OUTPUT);
}

void Motor::spin(bool directionState,int power)
{
    if (directionState == false)
    {
        digitalWrite(directionPin, LOW);
    }

    // write a high state to the direction pin (13)
    else
    {
        digitalWrite(directionPin, HIGH);
    }

    // release breaks
    digitalWrite(brakePin, LOW);

    // set work duty for the motor
    analogWrite(pwmPin, power);
}

void Motor::stop()
{
    // activate breaks
    digitalWrite(brakePin, HIGH);

    // set work duty for the motor to 0 (off)
    analogWrite(pwmPin, 0);
}

DistSensor::DistSensor(int EchoPin, int TrigPin)
{
    pinMode(TrigPIN, OUTPUT); // Sets the trigPin as an OUTPUT
    pinMode(EchoPIN, INPUT);  // Sets the echoPin as an INPUT
}
float DistSensor::getDistance()
{
    int trigPin;
    int echoPin;
    long duration; // variable for the duration of sound wave travel
    int distance;  // variable for the distance measurement

    // Clears the trigPin condition
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    // Calculating the distance
    distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
    // Displays the distance on the Serial Monitor
    // Serial.print("Distance: ");
    // Serial.print(distance);
    // Serial.println(" cm");
    return distance;
}