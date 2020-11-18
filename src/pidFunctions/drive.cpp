#include "main.h"
#include <iostream>
#include<string>
#include <cstdio>
#include <ctime>
using namespace std;


//IntializltionStep
int frontRightPort = 9; //Variable with the front right motor port
int frontLeftPort = 1; //Variable with the front left motor port
int backRightPort = 10; //Variable with the back right motor port
int backLeftPort = 2; //Variable with the back left motor port

int imuPort=6;

Motor FrontRight(frontRightPort, E_MOTOR_ENCODER_DEGREES); //Setting Up the Front Right Motor
Motor FrontLeft(frontLeftPort, E_MOTOR_ENCODER_DEGREES);  //Setting Up the Front Left Motor
Motor BackRight(backRightPort, E_MOTOR_ENCODER_DEGREES);  //Setting Up the Back Right Motor
Motor BackLeft(backLeftPort, E_MOTOR_ENCODER_DEGREES); //Setting Up the Back Left Motor

ADIEncoder Ltraking ('G', 'H', false);
ADIEncoder Rtraking ('A', 'B', true);
ADIEncoder Stracking('C', 'D', false);

Imu imu(imuPort);
//Intiilze Drive Vex equipment done


//Create a namespace to allow code to be used in other spot
namespace Drive{

//SetUping Variable for IMU loop  
float ImuError;
float ImuDerritive;
float ImuIntergal;

float ImuKP;
float ImuKI;
float ImuKD;

float ImuP;
float IMUI;
float IMUD;

float currentDegree;

float ImuPrevError;
bool targretReached = false;

//Function for Turn PID with IMU
void IMUTurn(int targetDegree) {
  while(targretReached == false) {
    currentDegree = imu.get_rotation();
    ImuError =  targetDegree - currentDegree;

    ImuDerritive = ImuError-ImuPrevError;

    ImuP = ImuError * ImuKP;
    IMUD = ImuDerritive * ImuKD;

  }
}
//IMU PID done

//Setting up the variable for Odemtry
int LeftPos;
int BackPos;
int RightPos;
float SmallDistance= 1.375/360;
float BigDistance= 10/360;

int PrevLeft;
int PrevBack;
int PrevRight;

float deltaLeft;
float deltaRight;
float deltaBack;

float totalDeltaDistR;
float totalDeltaDistL;

float currentAbsoluteOrriantion;
float StratTheta=0;

float LeftTrakingRadius=5.5;
float RightTrakinRadius=5.5;

float prevTheta;
float ThetaDelta;

float sTrakingRadius = 5.5;

float deltaXLocal;
float deltaYLocal;

float deltaXGlobal;
float deltaYGlobal;

float XPostionGlobal;
float YPostionGlobal;

float averageThetaArk;
//Varaibles intilzation for Odemtry Done

//Inilzing Varibalbes and Constants for PID

//Variables for PID set
float XError;
float XDerritive;
float XPrevError;


int target=0;

//Constants for PID
float XKP = 200;
float XkD;

//Back for Variables for PID
float XP;
float XD;

//Will be used to exit the PID loop
bool reached;
float Power;
float currentPostion;

//Function for Odemtry
 void Odemtry() {
   LeftPos = Ltraking.get_value();
   RightPos = Rtraking.get_value();
   BackPos = Stracking.get_value();

   deltaLeft = (LeftPos-PrevLeft)*SmallDistance;
   deltaRight = (RightPos-PrevRight)*SmallDistance;
   deltaBack = (BackPos-PrevBack)*BigDistance;
   PrevBack=BackPos;
   PrevLeft=LeftPos;
   PrevRight=RightPos;

  totalDeltaDistL += deltaLeft;
  totalDeltaDistR += deltaRight;

  currentAbsoluteOrriantion = StratTheta - ( (totalDeltaDistL-totalDeltaDistR)/(LeftTrakingRadius+RightTrakinRadius));  //Radians

  ThetaDelta = currentAbsoluteOrriantion - prevTheta;

  prevTheta = currentAbsoluteOrriantion;

  if (ThetaDelta == 0) {
    deltaXLocal = deltaBack;
    deltaYLocal = deltaRight;
  }

  else {
    deltaXLocal = sin(ThetaDelta/2)*((deltaBack/ThetaDelta)+sTrakingRadius);
    deltaYLocal = sin(ThetaDelta/2)*((deltaLeft/ThetaDelta)+LeftTrakingRadius);
  }

  averageThetaArk = currentAbsoluteOrriantion - (ThetaDelta/2);

  deltaXGlobal = (deltaYLocal*cos(averageThetaArk))-(deltaXLocal*sin(averageThetaArk));
   deltaYGlobal = (deltaYLocal * sin(averageThetaArk)) + (deltaXLocal * cos(averageThetaArk));

   XPostionGlobal += deltaXGlobal;
   YPostionGlobal += deltaYGlobal;

  
  std::string X = std::to_string(XPostionGlobal);
  std::string Y = std::to_string(YPostionGlobal);
  lcd::initialize();
  lcd::set_text(1,"Current Postion (" + X + ", "  + Y +")");

  if (FrontLeft.get_actual_velocity() > 0 && LeftPos == 0 ) {
    lcd::clear_line(1);
    lcd::set_text(1, "Odemtry is now inaccurate");
  }
  currentPostion = XPostionGlobal+YPostionGlobal;
  std::string Reach = std::to_string(reached);
  lcd::set_text(6, Reach);
    XError = currentPostion - target;

    std::string error =std::to_string(XError);
    lcd::set_text(2, "error: "+ error);
    XDerritive = XPrevError - XError;


    XP = XError*XKP;
    std::string p = std::to_string(XP);
    lcd::set_text(3, p);
    XD = XDerritive*XkD;

    Power = XP + XD;

    std::string power = std::to_string(Power);
    lcd::set_text(4, "Power: " + power);
  
      FrontLeft.move(Power);
      FrontRight.move(-Power);
      BackLeft.move(Power);
      BackRight.move(-Power);
      XPrevError = XError;
 }
float StraightKP=100;
float StraightKI;
float StraightKD;
float StraightError;
float StraightPrevError;
float StraightDerritive;
float leftTracking;
float RightTracking;

float average;
float distanceTravled;

float StraightP;
float StraightI;
float StraightD;

float StraightPower;
bool StraightPIDRun = true;

//Function for Straight PID
void StraightPID(float inches) {
  while (StraightPIDRun == true){
  leftTracking = Ltraking.get_value();
  RightTracking = Rtraking.get_value();
  average = (leftTracking+RightTracking)/2;

  distanceTravled = (SmallDistance/2)*average;
  
  StraightError = inches-distanceTravled;

  StraightDerritive = StraightPrevError-StraightError;
  StraightPrevError = StraightError;

  StraightP = StraightError*StraightKP;
  StraightD = StraightDerritive*StraightKD;

  StraightPower = StraightP + StraightD;
  if (StraightError > 1 || StraightError < -1 ){
    FrontLeft.move_velocity(StraightPower);
    FrontRight.move_velocity(-StraightPower);
    BackLeft.move_velocity(StraightPower);
    BackRight.move_velocity(-StraightPower);
  }

  else if (StraightError < 1 || StraightError > -1){
    FrontLeft.move_velocity(0);
    FrontRight.move_velocity(0);
    BackLeft.move_velocity(0);
    BackRight.move_velocity(0);
    StraightPIDRun = false;
  }
  }
}


  void opcontrol() {
    //Odemtry();

    int power = master.get_analog(ANALOG_LEFT_Y);
	    //Turning is set to the x axis of the right joystick
	  int turn = master.get_analog(ANALOG_RIGHT_X);
	   // Strafe is set to the x axis of the left joystick
   	int strafe = master.get_analog(ANALOG_LEFT_X);
	  // We set the power of the Left Front Motor to the postion of the varaible power postion + the turn postion + the strafe postion
    int lf = power + turn - strafe;
    int lb = power + turn + strafe;
    int rf = power - turn - strafe;
    int rb = power - turn + strafe;


    //FrontRight.move(-rf);
    //FrontLeft.move(lf);
    //BackRight.move(-rb);
    //BackLeft.move(lb);
  }
}