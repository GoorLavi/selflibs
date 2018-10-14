

void MotorsSetup() {


  rearRightESC.attach(4);
  frontRightESC.attach(5);
  frontLeftESC.attach(6);
  rearLeftESC.attach(7);


  armeMotors();
}

void armeMotors() {
  // arme the motors
  frontRightESC.writeMicroseconds(2000);
  rearLeftESC.writeMicroseconds(2000);
  frontLeftESC.writeMicroseconds(2000);
  rearRightESC.writeMicroseconds(2000);
  delay(2000);
  
Serial.println("first armed ok");

  frontRightESC.writeMicroseconds(700);
  rearLeftESC.writeMicroseconds(700);
  frontLeftESC.writeMicroseconds(700);
  rearRightESC.writeMicroseconds(700);
  delay(1000);

  
Serial.println("secound armed ok");
}

void PowerToMotors(int frontRight , int rearRight , int rearLeft , int frontLeft)
{


  frontRightESC.writeMicroseconds(frontRight);
  rearLeftESC.writeMicroseconds(rearLeft);
  frontLeftESC.writeMicroseconds(frontLeft);
  rearRightESC.writeMicroseconds(rearRight);

}

