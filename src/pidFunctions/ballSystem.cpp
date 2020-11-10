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

float SharedKP;
float SharedKI;
float SharedKD;
float SharedP;
float SharedI;
float SharedD;
float SharedTarget;
float SharedError;
float SharedDerritive;
float SharedPrevError;
float Sharedcurrentvoltage;
float SharedIntergal;
float SharedIntergalBond;
float SharedTotalError;
float RollersPower;

void SharedRollerPID(int speed) {
    SharedTarget = speed*120;
    Sharedcurrentvoltage = SharedRollers.get_voltage();
    SharedError = SharedTarget - Sharedcurrentvoltage;
    SharedDerritive = SharedError - SharedPrevError;

    if (std::abs(SharedError) < SharedIntergalBond) {
        SharedIntergal = SharedIntergal + SharedError;
    } 
    else {
        SharedIntergal = 0;
    }

    SharedPrevError = SharedError;

    SharedP = SharedError*SharedKD;
    SharedI = SharedIntergal*SharedKI;
    SharedD = SharedDerritive*SharedKD;

    RollersPower = SharedP + SharedI + SharedD;
    
    SharedRollers.move_voltage(RollersPower);

}

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

bool ballSystemOn = false;
bool OnlyIntake = false;
void opcontrol() {
    if (master.get_digital(DIGITAL_L1)) {
        if (ballSystemOn == true) {
            TurnOffBallSystem();
            ballSystemOn = false;
        }
        else if (ballSystemOn == false) {
            TurnBallSystemOn(100, 100);
            ballSystemOn = true;
        }

    }
    else if (master.get_digital(DIGITAL_L2)) {
        if (OnlyIntake == false ){
            TurnBallSystemOn(0,100);
            OnlyIntake = true;
            ballSystemOn = false;
        }
        else if (OnlyIntake = true) {
            TurnBallSystemOn(100, 100);
            OnlyIntake = false;
            ballSystemOn = true;
        }
    }
}
}
