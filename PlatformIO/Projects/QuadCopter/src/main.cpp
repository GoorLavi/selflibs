#include <Arduino.h>

#define SERIAL_PORT_SPEED 57600

extern void receiverSetup();
extern void gyroSetup();
extern void gyroRun();
extern void motorsSetup();
extern void receiverSetup();
extern void armeMotors();
extern void setMotorsSpeed(int frontRightM ,int rearLeftM ,int frontLeftM ,int rearRightM);
extern void printValues();

void setup() {

    Serial.begin(SERIAL_PORT_SPEED);
    receiverSetup();
    gyroSetup();
    motorsSetup();
    armeMotors();
}

void loop() {
    // put your main code here, to run repeatedly:
    delay(100);
    printValues();
    gyroRun();
    for (int i = 1000; i < 2000; i++) {
      setMotorsSpeed(i,i,i,i);
      delay(50);
    }
    for (int i = 2000; i >1000; i--) {
      setMotorsSpeed(i,i,i,i);
      delay(50);
    }
}
