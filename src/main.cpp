#include "main.h"
//Varables with the ports for the ball System

int SharedRollersPort=8; //Shared Roller Port
int SinglePort=3; //Single Roller Port
int OpticalSensorPort=4; //Optical Sensor Port

pros::Controller master(CONTROLLER_MASTER);
//Seting up the motors


void autonomous() {
Drive::TurnSlide(0,12,0, 100, 60, 0, 6, 0, 5, 0);
Drive::TurnSlide(0,0,-125, 0, 75, 0, 7, 0, 3, 2);
Drive::TurnSlide(0,25,0, 100, 60, 0, 6, 0, 5, 0);

}
void opcontrol() {
}
