#include "main.h"

pros::Controller master(CONTROLLER_MASTER);

void opcontrol() {
    Drive::DrivePID(6, 5);
}