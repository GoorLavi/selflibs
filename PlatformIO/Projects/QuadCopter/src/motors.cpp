#include <Arduino.h>
#include <Servo.h>

Servo rearRightESC, frontLeftESC, frontRightESC, rearLeftESC; //My 4 Motors
int esc_1, esc_2, esc_3, esc_4;

void setMotorsSpeed(int frontRightM ,int rearLeftM ,int frontLeftM ,int rearRightM) {

  if (frontRightM < 1000) frontRightM = 1000;
  if (rearLeftM < 1000) rearLeftM = 1000;
  if (frontLeftM < 1000) frontLeftM = 1000;
  if (rearRightM < 1000) rearRightM = 1000;

  if (frontRightM > 2000) frontRightM = 2000;
  if (rearLeftM > 2000) rearLeftM = 2000;
  if (frontLeftM > 2000) frontLeftM = 2000;
  if (rearRightM > 2000) rearRightM = 2000;

  frontRightESC.writeMicroseconds(frontRightM);
  rearLeftESC.writeMicroseconds(rearLeftM);
  frontLeftESC.writeMicroseconds(frontLeftM);
  rearRightESC.writeMicroseconds(rearRightM);
}


void armeMotors() {

 setMotorsSpeed(2000, 2000, 2000, 2000);
 delay(2000);

 setMotorsSpeed(1000, 1000, 1000, 1000);
 delay(1000);

 setMotorsSpeed(1000,1000,1000,1000);
 Serial.println("Motors armed");
}


void motorsSetup() {

  rearRightESC.attach(4);
  frontRightESC.attach(5);
  frontLeftESC.attach(6);
  rearLeftESC.attach(7);

  armeMotors();
}
