
//Arduino Mega2560 
// pins : int = 1, sda = sda, scl = scl,  



#include <Wire.h> //Include the Wire.h library so we can communicate with the gyro.


int cal_int;
double gyro_pitch, gyro_roll, gyro_yaw;
double gyro_roll_cal, gyro_pitch_cal, gyro_yaw_cal;

// Pitch, Roll and Yaw values
float pitch = 0;
float roll = 0;
float yaw = 0;


float timeStep = 0.01;


const int MPU_addr = 0x68; // I2C address of the MPU-6050
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;

void setup() {
  
 Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Serial.begin(9600);
  Serial.println("InitializeSensor");



  //Let's take multiple gyro data samples so we can determine the average gyro offset (calibration).
  for (cal_int = 0; cal_int < 2000 ; cal_int ++) {             //Take 2000 readings for calibration.

    gyro_signalen();                                           //Read the gyro output.

    gyro_roll_cal += gyro_roll;                                //Ad roll value to gyro_roll_cal.
    gyro_pitch_cal += gyro_pitch;                              //Ad pitch value to gyro_pitch_cal.
    gyro_yaw_cal += gyro_yaw;                                  //Ad yaw value to gyro_yaw_cal.
  }


  //Now that we have 2000 measures, we need to devide by 2000 to get the average gyro offset.
  gyro_roll_cal /= 2000;                                       //Divide the roll total by 2000.
  gyro_pitch_cal /= 2000;                                      //Divide the pitch total by 2000.
  gyro_yaw_cal /= 2000;                                        //Divide the yaw total by 2000.


  Serial.println("end InitializeSensor");
}

void loop() {
gyro_signalen();

calculatGyroInputs();
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Subroutine for reading the gyro
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void gyro_signalen() {
  
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x43);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);

  Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers
  
  while(Wire.available() < 14);                       //Wait until the 6 bytes are received
  
 
  gyro_roll = Wire.read()<<8|Wire.read();               //Multiply highByte by 256 and ad lowByte
  if(cal_int == 2000)gyro_roll -= gyro_roll_cal;     //Only compensate after the calibration

  gyro_pitch = Wire.read()<<8|Wire.read();              //Multiply highByte by 256 and ad lowByte
  gyro_pitch *= -1;                                  //Invert axis
  if(cal_int == 2000)gyro_pitch -= gyro_pitch_cal;   //Only compensate after the calibration
  
  gyro_yaw = Wire.read()<<8|Wire.read();                //Multiply highByte by 256 and ad lowByte
  gyro_yaw *= -1;                                    //Invert axis
  if(cal_int == 2000)gyro_yaw -= gyro_yaw_cal;       //Only compensate after the calibration
}

void calculatGyroInputs() {

Serial.print("gyro_roll_input : ");Serial.print(((gyro_roll / 57.14286) * 0.2));
Serial.print(", gyro_pitch_input : ");Serial.print(((gyro_pitch / 57.14286) * 0.2));
Serial.print(", gyro_yaw_input : ");Serial.println( ((gyro_yaw / 57.14286) * 0.2));

//  gyro_roll_input = (gyro_roll_input * 0.8) + ((gyro_roll / 57.14286) * 0.2);            //Gyro pid input is deg/sec.
//  gyro_pitch_input = (gyro_pitch_input * 0.8) + ((gyro_pitch / 57.14286) * 0.2);         //Gyro pid input is deg/sec.
//  gyro_yaw_input = (gyro_yaw_input * 0.8) + ((gyro_yaw / 57.14286) * 0.2);               //Gyro pid input is deg/sec.

}



