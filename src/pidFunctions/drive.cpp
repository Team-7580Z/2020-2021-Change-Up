#include "main.h"


//Variable for Straight straight driving
float Straighterror;
float StraightprevError;
float Straightderritive;
//Will enter the loop and varible for leaving
bool DrivePID;

//constants for pd of driving straight
float Straightkp = 0;
float Straightkd = 0;

//Variable for Strafe Driving
float StrafeError;
float StrafePrevError;
float StrafeDerritive
bool StrafePD = true;

//constants for pd of strafe
float strafeKp
float strafeKD


//Set Up the motors straight Driving
void StraightMotorSetup() {
  pros::Motor leftFront(encoderUnits::degrees);
  pros::Motor leftBack(encoderUnits::degrees);
  pros::Motor RightFront(encoderUnits::degrees);
  pros::Motor RightBack(encoderUnits::degrees);
}

//Set Up the Motors for strafe driving
void StrafeMotorSetUp() {
  pros::Motor leftFront();
  pros::Motor leftBack();
  pros::Motor RightFront();
  pros::Motor RightBack();
}

//DriveStraight PID and Drive Straight X inches

void DriveStraight(float inches) {
  DrivePID = true;
  while (DrivePID) {
  }
}

//Strafe PID and Strafe distance
void Strafe(float inches) {
  while(StrafePD) {
    
  }
}
