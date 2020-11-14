#include "main.h"
#include <iostream>
#include<string>
#include <cstdio>
#include <ctime>
using namespace std;

int frontRightPort = 9; //Variable with the front right motor port
int frontLeftPort = 1; //Variable with the front left motor port
int backRightPort = 10; //Variable with the back right motor port
int backLeftPort = 2; //Variable with the back left motor port

Motor FrontRight(frontRightPort, E_MOTOR_ENCODER_DEGREES); //Setting Up the Front Right Motor
Motor FrontLeft(frontLeftPort, E_MOTOR_ENCODER_DEGREES);  //Setting Up the Front Left Motor
Motor BackRight(backRightPort, E_MOTOR_ENCODER_DEGREES);  //Setting Up the Back Right Motor
Motor BackLeft(backLeftPort, E_MOTOR_ENCODER_DEGREES); //Setting Up the Back Left Motor





namespace Drive{
  float TotalX;

  bool XTargetReached = false;

  float averageLeftPostion;
  float averageRightPostion;

  float aveargeRightLeft;
  float DriveStraightDistance;

  float distanceTravledInDegree = 12.56637/360;

  float StraightError;
  float StraightPrevError;

  float StraightDerritive;

  float StraightP;
  float StraightD;

  float StraightkP;
  float StraightkD;

  float StraightVelocity;

  void DrivePD(float x) {

    while (XTargetReached == false) {
      averageLeftPostion = (FrontLeft.get_raw_position(&now)+BackLeftt.get_raw_position(&now))/2;
      averageRightPostion = (FrontRight.get_raw_position(&now)+BackRight.get_raw_position(&now))/2;
      aveargeRightLeft = (averageRightPostion+averageLeftPostion)/2;

      DriveStraightDistance = aveargeRightLeft*distanceTravledInDegree;

      StraightError = x-DriveStraightDistance;

      StraightDerritive = StraightError - StraightPrevError;

      StraightPrevError = StraightError;

      StraightP = StraightError*StraightkP;
      StraightD = StraightDerritive*StraightkD;

      StraightVelocity StraightP+StraightD
    }
    if (StraightError<1 && StraightError>-1) {
      XTargetReached = true;
    }
  }

float prevRightPostion;
float  prevLeftPostion;

float  changeRightEncoder;
float changeLeftEncoder;
float totalRightChange;
float totalLeftChage;

float newAbsoluteOrientation;
float newAbsoluteOrientationNum;
float newAbsoluteOrinetationDen;

float previousAbsoluteOrientation;
float SL = 5;
float SR = 5;

float globalOffset;
float GyroRate;
float changeInAngle;

float d1;
float localOffset;

float averageOriantion;
  void Odemtry() {
    pros::Imu imu_sensor(7);
    imu_sensor.reset();
    ADIEncoder RightEncoder ('A', 'B', true);
    ADIEncoder LeftEncoder ('G', 'H', false);
    lcd::initialize();
    int RightPostion = RightEncoder.get_value();
    int LeftPostion = LeftEncoder.get_value();

    changeRightEncoder = RightPostion - prevRightPostion;
    changeLeftEncoder = LeftPostion - prevLeftPostion;

    prevRightPostion = RightPostion;
    prevLeftPostion = LeftPostion;

    //.048 inches traveled evrey thick
    totalRightChange = changeRightEncoder*.048;
    totalLeftChage = changeLeftEncoder*.048;

    newAbsoluteOrientationNum = totalLeftChage-totalRightChange;
    newAbsoluteOrinetationDen = SL+SR;

    newAbsoluteOrientation = newAbsoluteOrientationNum/newAbsoluteOrinetationDen;

    changeInAngle = newAbsoluteOrientation-previousAbsoluteOrientation;  

    pros::c::imu_gyro_s_t gyro = imu_sensor.get_gyro_rate();
    
    if (changeInAngle = 0){
      localOffset = gyro.z/changeRightEncoder;
    
     }
     else {
       float localOffsetArray [2][1];
       
     }

    averageOriantion = previousAbsoluteOrientation + changeInAngle/2;




  }
  void opcontrol() {
    Odemtry();
    int power = master.get_analog(ANALOG_LEFT_Y);
	   // Turning is set to the x axis of the right joystick
	  int turn = master.get_analog(ANALOG_RIGHT_X);
	   // Strafe is set to the x axis of the left joystick
   	int strafe = master.get_analog(ANALOG_LEFT_X);
	   // We set the power of the Left Front Motor to the postion of the varaible power postion + the turn postion + the strafe postion
    int lf = power + turn - strafe;
    int lb = power + turn + strafe;
    int rf = power - turn - strafe;
    int rb = power - turn + strafe;


     FrontRight.move(-rf);
     FrontLeft.move(lf);
     BackRight.move(-rb);
     BackLeft.move(lb);
  }
}