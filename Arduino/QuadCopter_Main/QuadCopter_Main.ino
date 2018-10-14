#include <PID_v1.h>
#include <Wire.h>
#include <Servo.h>

// distance pins
#define trigPin 52
#define echoPin 53

Servo rearRightESC, frontLeftESC, frontRightESC, rearLeftESC; //My 4 Motors

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//PID gain and limit settings
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float pid_p_gain_roll = 0;               //Gain setting for the roll P-controller (1.3)  unyil shack then - 50%
float pid_i_gain_roll = 0;              //Gain setting for the roll I-controller (0.3) when its ausolat slowly -50%
float pid_d_gain_roll = 18;                //Gain setting for the roll D-controller (15) upgread until ruthless then - 25%   21- 25% =15
int pid_max_roll = 80;                    //Maximum output of the PID-controller (+/-)

float pid_p_gain_pitch = pid_p_gain_roll;  //Gain setting for the pitch P-controller.
float pid_i_gain_pitch = pid_i_gain_roll;  //Gain setting for the pitch I-controller.
float pid_d_gain_pitch = pid_d_gain_roll;  //Gain setting for the pitch D-controller.
int pid_max_pitch = pid_max_roll;          //Maximum output of the PID-controller (+/-)

float pid_p_gain_yaw = 3;                //Gain setting for the pitch P-controller. //4.0
float pid_i_gain_yaw = 0.02;               //Gain setting for the pitch I-controller. //0.02
float pid_d_gain_yaw = 0.0;                //Gain setting for the pitch D-controller.
int pid_max_yaw = 1;//400                     //Maximum output of the PID-controller (+/-)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Declaring Variables
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cal_int, start;
unsigned long loop_timer;
double gyro_pitch, gyro_roll, gyro_yaw;
double gyro_roll_cal, gyro_pitch_cal, gyro_yaw_cal;
byte highByte, lowByte;

float pid_error_temp;
float pid_i_mem_roll, pid_roll_setpoint, gyro_roll_input, pid_output_roll, pid_last_roll_d_error;
float pid_i_mem_pitch, pid_pitch_setpoint, gyro_pitch_input, pid_output_pitch, pid_last_pitch_d_error;
float pid_i_mem_yaw, pid_yaw_setpoint, gyro_yaw_input, pid_output_yaw, pid_last_yaw_d_error;


int BTzPower = 0;
int BTxPower = 0;
int BTyPower = 0;


bool QuadIsActive = false;

int startPower = 700;

void setup() {

  Serial.begin(9600);// PC

  Serial.println("Gerial is good");

  InitializeGyro();

  Serial.println("wire is good");


  //Serial.print("gyro_roll_cal "); Serial.print(gyro_roll_cal); Serial.print(" gyro_pitch_cal "); Serial.print(gyro_pitch_cal); Serial.print(" gyro_yaw_cal "); Serial.println(gyro_yaw_cal);

  MotorsSetup();

}


void loop() {

  // user unput
  pid_roll_setpoint = 0;
  pid_pitch_setpoint = 0;
  pid_yaw_setpoint = 0;

  //Let's get the current gyro data and scale it to degrees per second for the pid calculations.
  gyro_signalen();
  gyro_roll_input = (gyro_roll_input * 0.8) + ((gyro_roll / 57.14286) * 0.2);            //Gyro pid input is deg/sec.
  gyro_pitch_input = (gyro_pitch_input * 0.8) + ((gyro_pitch / 57.14286) * 0.2);         //Gyro pid input is deg/sec.
  gyro_yaw_input = (gyro_yaw_input * 0.8) + ((gyro_yaw / 57.14286) * 0.2);               //Gyro pid input is deg/sec.


  BlueTooth();


  if (QuadIsActive) {

    calculate_pid();

    int frontRight = startPower + pid_output_pitch - pid_output_roll + pid_output_yaw; //Calculate the pulse for esc 1 (front-right - CCW)
    int rearRight = startPower - pid_output_pitch - pid_output_roll - pid_output_yaw; //Calculate the pulse for esc 2 (rear-right - CW)
    int frontLeft = startPower + pid_output_pitch + pid_output_roll - pid_output_yaw; //Calculate the pulse for esc 3 (rear-left - CCW)
    int rearLeft = startPower - pid_output_pitch + pid_output_roll + pid_output_yaw; //Calculate the pulse for esc 4 (front-left - CW)

    //Serial.print("frontRight :"); Serial.print(frontRight); Serial.print(" frontLeft :"); Serial.print(frontLeft);
    //Serial.print(" rearRight :"); Serial.print(rearRight); Serial.print(" rearLeft :"); Serial.println(rearLeft);
    //Serial.print(" pid_output_yaw :"); Serial.println(pid_output_yaw);
    //delay(20);
    PowerToMotors(frontRight , rearRight , rearLeft , frontLeft);

  }
  else {
    pid_i_mem_roll = 0;
    pid_last_roll_d_error = 0;
    pid_i_mem_pitch = 0;
    pid_last_pitch_d_error = 0;
    pid_i_mem_yaw = 0;
    pid_last_yaw_d_error = 0;

    int stopMotor = 700;
    PowerToMotors(stopMotor , stopMotor , stopMotor , stopMotor);
  }

}




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Subroutine for reading the gyro
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


