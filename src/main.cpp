#include "main.h"

pros::Controller master(CONTROLLER_MASTER);

void init() {}
void opcontrol() {
	while (true) {
		BallSystem::opcontrol();
		delay(10);

	}
}
