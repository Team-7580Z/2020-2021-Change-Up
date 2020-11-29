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
	Drive::TurnSlide(10,10,0, 50, 0, 0, 2, 2, 0, 0);
	Drive::TurnSlide(0,0,90, 0, 100, 0, 100, 10, 5, 5);
}
