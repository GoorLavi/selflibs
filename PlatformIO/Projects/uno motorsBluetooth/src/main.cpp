#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Servo.h>

Servo m1, m2, m3, m4; //1030 - 1440

SoftwareSerial btSerial(10, 11); // RX, TX

void setMotorsSpeed(int m1s ,int m2s ,int m3s ,int m4s) {
    m1.writeMicroseconds(m1s);
    m2.writeMicroseconds(m2s);
    m3.writeMicroseconds(m3s);
    m4.writeMicroseconds(m4s);
}

void setup() {
  // Open serial communications and wait for port to open:
 Serial.begin(57600);

 Serial.print("Waiting for usb connection");

 while (!Serial) {
   Serial.print(".");
 }

 Serial.println("");
 Serial.println("Connected!");

 btSerial.begin(9600);


 m1.attach(4);
 m2.attach(5);
 m3.attach(6);
 m4.attach(7);

 setMotorsSpeed(2000,2000,2000,2000);
 delay(2000);
 setMotorsSpeed(1000,1000,1000,1000);
 delay(1000);
}


void loop() {

  if (btSerial.available()) {
      String btString;
      btString = btSerial.readString();
      Serial.println(btString);
      int speed = atoi(btString.c_str());
      setMotorsSpeed(speed, speed, speed, speed);
    }
    if (Serial.available()) {
      btSerial.print(Serial.readString());
    }

}
