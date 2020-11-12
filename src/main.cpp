#include "main.h"

pros::Controller master(CONTROLLER_MASTER);

void opcontrol() {
    while (true) {
		BallSystem::opcontrol();
		Drive::opcontrol(); 
		pros::delay(20);

	}    }

