#include "main.h"
//Varables with the ports for the ball System
int leftIntakePort=5; // Left Intake Port
int RightIntakePort=6; //Right Intake Port
int SharedRollersPort=8; //Shared Roller Port
int SinglePort=3; //Single Roller Port
int OpticalSensorPort=4; //Optical Sensor Port

pros::Controller master(CONTROLLER_MASTER);
//Seting up the motors
Motor LeftIntake(leftIntakePort, true); //The Left Intake Motor is reversed
Motor RightIntake(RightIntakePort, false); 
Motor SharedRollers(SharedRollersPort, false);
Motor SingleRoller(SinglePort, true); //The Single Roller is also reversed

void opcontrol() {

	Drive::StraightPID(24);
  //  while (true) {
		//pros::delay(20);

		//Drive::opcontrol(); 
//	}  
}
