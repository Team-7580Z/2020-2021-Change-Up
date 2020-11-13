//Ports on the ball system
#include "main.h"

//Varables with the ports for the ball System
int leftIntakePort=5; // Left Intake Port
int RightIntakePort=6; //Right Intake Port
int SharedRollersPort=8; //Shared Roller Port
int SinglePort=3; //Single Roller Port
int OpticalSensorPort=4; //Optical Sensor Port

namespace BallSystem { //Namespace so these functions can be used outside of this file 

//Seting up the motors
Motor LeftIntake(leftIntakePort, true); //The Left Intake Motor is reversed
Motor RightIntake(RightIntakePort, false); 
Motor SharedRollers(SharedRollersPort, false);
Motor SingleRoller(SinglePort, true); //The Single Roller is also reversed
Optical optical_sensor(OpticalSensorPort);

void StartRoller(int speed) {
    SharedRollers.move_velocity(speed);
} 
//The controlls for driver control

void opcontrol() {
    if (master.get_digital(DIGITAL_R1)) {
      //  if (SharedRollers.get_actual_velocity() > 0 || SharedRollers.get_actual_velocity() < 0) {
        //    SharedRollers.move_velocity(0);
        //}
        //else{
         //   SharedRollers.move_velocity(100);
       // }
    }
}
}