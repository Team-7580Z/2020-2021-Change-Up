#include "main.h"

int frontRightPort = 9;
int frontLeftPort = 1;
int backRightPort = 10;
int backLeftPort = 2;

Motor FrontRight(frontRightPort, true);
Motor FrontLeft(frontLeftPort);
Motor BackRight(backRightPort, true);
Motor BackLeft(backLeftPort);

namespace Drive{
  void DriveForward(float inches) {

  }
  
  void Turn(float degrees) {

  }

  void DriveSideWays(float inches) {

  }

  void opcontrol() {
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