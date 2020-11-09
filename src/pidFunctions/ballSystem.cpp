//Ports on the ball system
#include "main.h"

//Varables with the ports for the ball System
int leftIntakePort=5;
int RightIntakePort=6;
int SharedRollersPort=8;
int SinglePort=3;
int OpticalSensorPort=4;

namespace BallSystem {

Motor LeftIntake(leftIntakePort, true);
Motor RightIntake(RightIntakePort, false);
Motor SharedRollers(SharedRollersPort, false);
Motor SingleRoller(SinglePort, true);
Optical optical_sensor(OpticalSensorPort);

void TurnOnIntake(int speed) {
    LeftIntake.move_voltage(speed*120);
    RightIntake.move_voltage(speed*120);
}

void TurnOnRollerSystem(int sharedSpeed, int singleSpeed) {
    SharedRollers.move_voltage(sharedSpeed*120);
    SingleRoller.move_voltage(sharedSpeed*120);
}

void TurnBallSystemOn(int rollerSpeed, int speed) {
    TurnOnIntake(speed);
    TurnOnRollerSystem(rollerSpeed, rollerSpeed);
}
void TurnOffBallSystem(){
    TurnOnIntake(0);
    TurnOnRollerSystem(0, 0);
}
bool IntakeOn = false;
bool RollerOn = false;
void descore(char color) {
    if (color = 'b') {
        printf("h");
    }
    else if (color = 'r') {
        printf("h");
    }
}

bool ballSystemOn = false;
bool OnlyIntake = false;
void opcontrol() {
   

    if (master.get_digital(DIGITAL_R1)) {
        if (ballSystemOn == true) {
            TurnOffBallSystem();
            ballSystemOn = false;
        }
        else if (ballSystemOn == false) {
            TurnBallSystemOn(100, 100);
            ballSystemOn = true;
        }

    }
    else if (master.get_digital(DIGITAL_L1) && OnlyIntake == false  ) {
        TurnOnIntake(100);
        TurnOnRollerSystem(0, 0);
        bool OnlyIntake = true;
        ballSystemOn = false;
    }
    else if (master.get_digital(DIGITAL_L1) && OnlyIntake == true) {
        ballSystemOn = true;
        TurnBallSystemOn(100, 100);
        RollerOn = true;
        IntakeOn = true;
    }
}
}
