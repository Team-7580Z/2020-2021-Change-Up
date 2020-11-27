#include "main.h"
//Varables with the ports for the ball System

int SharedRollersPort=8; //Shared Roller Port
int SinglePort=3; //Single Roller Port
int OpticalSensorPort=4; //Optical Sensor Port

pros::Controller master(CONTROLLER_MASTER);
//Seting up the motors


void autonomous() {
	
}
void opcontrol() {

	//Drive::StraightPID(24);
	Drive::TurnSlide(1,1,0, 100, 150, 0, 80, 60, 70, 50);
}
