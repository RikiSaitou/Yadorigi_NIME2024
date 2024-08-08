#include <M5Stack.h>
#include <ArduinoOSCWiFi.h>
#include <ESP32Servo.h>

Servo verticalServo;
Servo horizontalServo;

float v_servo; float h_servo;

const IPAddress ip(192, 168, 3, 8);
const IPAddress gateway(192, 168, 3, 1);
const IPAddress subnet(255, 255, 255, 0);

void setup() {
  M5.begin();
  Serial.begin(9600);
  M5.Speaker.write(0); // スピーカーをオフする
  M5.lcd.setBrightness(20);  // LCDバックライトの輝度を下げる

  verticalServo.attach(18);
  horizontalServo.attach(5);
  
  WiFi.begin("5C6199C256EB-2G", "d58apfs8d4c2r0");
  WiFi.config(ip, gateway, subnet);

    
  OscWiFi.subscribe(6666, "/servo1", v_servo, h_servo);

  verticalServo.write(90);
  horizontalServo.write(90);
  delay(50);
}

void loop() {
  M5.update();

  M5.Lcd.clear(BLACK);
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.printf("vertivcal =  %.2f, ", v_servo);
  M5.Lcd.printf("horizontal =  %.2f\n", h_servo);

  verticalServo.write(v_servo);
  horizontalServo.write(h_servo);

  OscWiFi.update();
  delay(100);
}
