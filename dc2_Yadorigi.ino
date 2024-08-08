#include <M5Stack.h>
#include <Arduino.h>
#include <ArduinoOSCWiFi.h>

const int DC_MOTOR_PIN = 5;   // Assuming servo1 is connected to pin 2
const int DIRECTION_PIN = 21; // Assuming a direction pin for the motor
const int START_DEGREE_VALUE = 0;
const int DEFAULT_MICROSECONDS_FOR_0_DEGREE = 1000;
const int DEFAULT_MICROSECONDS_FOR_180_DEGREE = 2000;

float dc_speed; float previousSpeed;

const IPAddress ip(192, 168, 3, 9);
const IPAddress gateway(192, 168, 3, 1);
const IPAddress subnet(255, 255, 255, 0);

// Define a timer variable
unsigned long lastOscDataTime = 0;
unsigned long previousMillis = 0;

void setup() {
    M5.begin();
    M5.Power.begin();
    Serial.begin(9600);
    pinMode(DC_MOTOR_PIN, OUTPUT);

    WiFi.begin("5C6199C256EB-2G", "d58apfs8d4c2r0");
    WiFi.config(ip, gateway, subnet);

    OscWiFi.subscribe(6667, "/dc2", dc_speed);

    analogWrite(DC_MOTOR_PIN, 255);
}


void nonBlockingDelay(unsigned long interval) {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
  }
}

void renda(){
  const int numIterations = 20; // Change this value as needed
  Serial.print("renda");

  for (int i = 0; i < numIterations; ++i) {
      analogWrite(DC_MOTOR_PIN, 250);
      delay(50);
      analogWrite(DC_MOTOR_PIN, 0);
      delay(100);
  }
}

//backup
void DCmotorWithUpDown() {
  int randomRepeats = random(2, 7);  // Generate a random number of repeats between 5 and 20

  for (int i = 0; i < randomRepeats; ++i) {
    analogWrite(DC_MOTOR_PIN, (random(100, 255)));
    delay(random(500, 4000));
    analogWrite(DC_MOTOR_PIN, 160);
    delay(1000);
    analogWrite(DC_MOTOR_PIN, 140);
    delay(1000);
    analogWrite(DC_MOTOR_PIN, 100);
    delay(1000);
    analogWrite(DC_MOTOR_PIN, 100);
    delay(random(500, 4000));
  }
  renda();
}

void loop() {
      OscWiFi.update();
  
      if(previousSpeed != dc_speed)
      {
        analogWrite(DC_MOTOR_PIN, dc_speed);
        previousSpeed = dc_speed;
        delay(100);
      }
      else
      {
        delay(100);
      }
}
