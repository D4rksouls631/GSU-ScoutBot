#include "include.h"
#include "pins.h"

DualVNH5019MotorShield md;
Adafruit_MPU6050 mpu;

float getDistance(int sensor_pins[2])
{
  int trigPin = sensor_pins[0];
  int echoPin = sensor_pins[1];
  long duration;
  float distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  return distance;
}

void gyroValues()
{
  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  /* Print out the values */
  Serial.print("Acceleration X: ");
  Serial.print(a.acceleration.x);
  Serial.print(", Y: ");
  Serial.print(a.acceleration.y);
  Serial.print(", Z: ");
  Serial.print(a.acceleration.z);
  Serial.println(" m/s^2");

  Serial.print("Rotation X: ");
  Serial.print(g.gyro.x);
  Serial.print(", Y: ");
  Serial.print(g.gyro.y);
  Serial.print(", Z: ");
  Serial.print(g.gyro.z);
  Serial.println(" rad/s");

  Serial.print("Temperature: ");
  Serial.print(temp.temperature);
  Serial.println(" degC");

  Serial.println("");
  delay(500);
}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  // Dual VNH5019 Motor Shield
  Serial.println("Dual VNH5019 Motor Shield Initializing...");
  md.init();
  delay(10);
  Serial.println("Dual VNH5019 Motor Shield Initialized");
  delayMicroseconds(100);
  // Adafruit MPU6050
  Serial.println("Adafruit MPU6050 Initializing...");
  delayMicroseconds(100);
  mpu.begin();
  if (!mpu.begin())
  {
    Serial.println("Failed to find MPU6050 chip");
    while (1)
    {
      delay(10);
    }
  }
  // set accelerometer range to +-8G
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);

  // set gyro range to +- 500 deg/s
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);

  // set filter bandwidth to 21 Hz
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  delay(100);
  Serial.println("Adafruit MPU6050 Initialized");
  // Ultrasonic Sensor HC-SR04
  pinMode(trigPin_Sensor1, OUTPUT); // Sets the trigPin as an Output Sensor 1
  pinMode(echoPin_Sensor1, INPUT);  // Sets the echoPin as an Input Sensor 1
  pinMode(trigPin_Sensor2, OUTPUT); // Sets the trigPin as an Output Sensor 2
  pinMode(echoPin_Sensor2, INPUT);  // Sets the echoPin as an Input Sensor 2
  pinMode(trigPin_Sensor3, OUTPUT); // Sets the trigPin as an Output Sensor 3
  pinMode(echoPin_Sensor3, INPUT);  // Sets the echoPin as an Input Sensor 3
}

void loop()
{
  while (1)
  {
    // gyroValues();

    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
  
      Serial.print(a.acceleration.x);Serial.print(",");Serial.print(a.acceleration.y);Serial.print(",");Serial.print(a.acceleration.z);Serial.print(",");

      Serial.print(g.gyro.x);Serial.print(",");Serial.print(g.gyro.y);Serial.print(",");Serial.print(g.gyro.z);Serial.print(",");

      Serial.print(temp.temperature);Serial.print(",");

      Serial.print(getDistance(Sensor1));Serial.print(",");Serial.print(getDistance(Sensor2));Serial.print(",");Serial.print(getDistance(Sensor3));Serial.print(",");

      Serial.print(md.getM1CurrentMilliamps());Serial.print(",");Serial.print(md.getM2CurrentMilliamps());Serial.println(",");
      delay(100);

      // read the oldest byte in the serial buffer:
      String incomingByte;
      incomingByte = Serial1.read();
      int split = incomingByte.indexOf(',');
      int LeftMotor = incomingByte.substring(0, split).toInt();
      int RightMotor = incomingByte.substring(split, incomingByte.length()).toInt();
      md.setM1Speed(LeftMotor);
      md.setM2Speed(-RightMotor);

    /*
    if(getDistance(Sensor1)<=50){
    md.setM1Speed(50);
    md.setM2Speed(0);
    }
    if(getDistance(Sensor3)<=50){
    md.setM1Speed(0);
    md.setM2Speed(50);
    }
    if(getDistance(Sensor2)<=50){
    md.setM1Speed(-50);
    md.setM2Speed(-50);
    }
    md.setM1Speed(50);
    md.setM2Speed(50);

    */
  }
}
