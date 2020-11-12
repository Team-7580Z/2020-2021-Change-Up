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

float SharedKP=.9; //The P value of PID
float SharedKI; //The I value of PID
float SharedKD; //The D value of PID

float SharedP; //Intializing the P that will be added to get the power
float SharedI; //Intializing the I that will be added to get the power
float SharedD; //Intializing the D that will be added to get the power

//Intialize the rest of the PID values
float SharedTarget;
float SharedError;
float SharedDerritive;
float SharedPrevError;
float Sharedcurrentvoltage;
float SharedIntergal;
float SharedRoomOfError = 1;
float SharedPIDLimit = 8;
float SharedTotalError;
float RollersPower;

void SharedRollerPID(int speed) {
    SharedTarget = speed*120; //Getting the Target power
    Sharedcurrentvoltage = SharedRollers.get_voltage(); //Getting the current voltage
    SharedError = SharedTarget - Sharedcurrentvoltage; //We find the error by subtracting the target with the current voltage
    SharedDerritive = SharedError - SharedPrevError; //Find the Derritive by subtracting the error with the error less than a second ago

    //Use a if statment so Intergal is only set in a controlable range 
    if (std::abs(SharedError) < SharedRoomOfError) {
        SharedIntergal = 0;
    } 
    else if (std::abs(SharedError) >= SharedRoomOfError && std::abs(SharedError) < SharedPIDLimit) {
        SharedIntergal = SharedIntergal + SharedError;
       
    }
    else {
        SharedIntergal = 0;
    }

     SharedPrevError = SharedError;
        
    SharedP = SharedError*SharedKP;
    SharedI = SharedIntergal*SharedKI;
    SharedD = SharedDerritive*SharedKD;

    SharedPrevError = SharedError;//Set Prev Error for next run to the current error

    SharedP = SharedError*SharedKP; //Find the p
    SharedI = SharedIntergal*SharedKI; //Find the I
    SharedD = SharedDerritive*SharedKD; //Find the D

    RollersPower = SharedP + SharedI + SharedD; //Get the VOltage we are going to set the motor at

    SharedRollers.move_voltage(RollersPower+Sharedcurrentvoltage);

}

//PID for intakes

void intakePID() {

}

void StartRoller(int speed) {
    SharedRollerPID(speed);
} 
//The controlls for driver control
bool BallSystemOn = false;

void opcontrol() {
    if (master.get_digital(DIGITAL_R1) && BallSystemOn==false){
          StartRoller(100);
            BallSystemOn = true;
        }
    else if (master.get_digital(DIGITAL_R1) && BallSystemOn==true) {
        StartRoller(0);
        BallSystemOn = false;
        }
    }
}
