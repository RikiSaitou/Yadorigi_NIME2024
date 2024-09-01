/*
 * Ultrasonic Simple
 * Prints the distance read by an ultrasonic sensor in
 * centimeters. They are supported to four pins ultrasound
 * sensors (liek HC-SC04) and three pins (like PING)))
 * and Seeed Studio sensors).
 *
 * The circuit:
 * * Module HR-SC04 (four pins) or PING))) (and other with
 *   three pins), attached to digital pins as follows:
 * ---------------------    --------------------
 * | HC-SC04 | Arduino |    | 3 pins | Arduino |
 * ---------------------    --------------------
 * |   Vcc   |   5V    |    |   Vcc  |   5V    |
 * |   Trig  |   12    | OR |   SIG  |   13    |
 * |   Echo  |   13    |    |   Gnd  |   GND   |
 * |   Gnd   |   GND   |    --------------------
 * ---------------------
 */
#include <M5Stack.h>
#include <Ultrasonic.h>
#include <ArduinoOSCWiFi.h>

/*
 * Pass as a parameter the trigger and echo pin, respectively,
 * or only the signal pin (for sensors 3 pins), like:
 * Ultrasonic ultrasonic(13);
 */
Ultrasonic ultrasonic1(2);
Ultrasonic ultrasonic2(5);
Ultrasonic ultrasonic3(19);
int distance1, distance2, distance3;

const IPAddress ip(192, 168, 3, 7);
const IPAddress gateway(192, 168, 3, 1);
const IPAddress subnet(255, 255, 255, 0);
const char* host = "192.168.3.6";

void setup() {
  M5.begin();
  Serial.begin(9600);
  M5.Speaker.write(0); // スピーカーをオフする
  M5.Lcd.begin();             // 画面初期化
  M5.Lcd.setRotation(1);      // 画面向き設定（0～3で設定、4～7は反転)※初期値は1
  M5.Lcd.setTextWrap(false);  // 画面端での改行の有無（true:有り[初期値], false:無し）※print関数のみ有効

  WiFi.begin("5C6199C256EB-2G", "d58apfs8d4c2r0");
  WiFi.config(ip, gateway, subnet);

  OscWiFi.publish(host, 12001, "/distance", distance1, distance2, distance3);
}

void loop() {
  M5.update();
  // Pass INC as a parameter to get the distance in inches
  distance1 = ultrasonic1.read();
  distance2 = ultrasonic2.read();
  distance3 = ultrasonic3.read();
  
  //Serial.print(distance1);
  //Serial.print(" ");
  //Serial.print(distance2);
  //Serial.print(" ");
  //Serial.println(distance3);
  
  OscWiFi.update(); 
  delay(100);
}
