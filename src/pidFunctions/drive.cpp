#include "main.h"
#include <iostream>
#include<string>
#include <cstdio>
#include <ctime>
using namespace std;

int frontRightPort = 9;
int frontLeftPort = 1;
int backRightPort = 10;
int backLeftPort = 2;

Motor FrontRight(frontRightPort, true);
Motor FrontLeft(frontLeftPort);
Motor BackRight(backRightPort, true);
Motor BackLeft(backLeftPort);

float Straightkp;
float Straightki;
float Straightkd;
void DrivePID(float distance) {

}

int prevRightPostion;
int prevLeftPostion;

int changeRightEncoder;
int changeLeftEncoder;
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
namespace Drive{
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
      globalOffset = gyro.z/changeRightEncoder;
      
    
     }
     else {
       globalOffset = 2*sin(gyro.z);
     }
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


     FrontRight.move(rf);
     FrontLeft.move(lf);
     BackRight.move(rb);
     BackLeft.move(lb);
  }
}