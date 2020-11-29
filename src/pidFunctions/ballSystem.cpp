#include "main.h"
using namespace std;

namespace ballSystem {
    static int sharedRollerPort = 8;
    static int singleRollerPort = 3;
    
    static int leftIntakePort = 5;
    static int rightIntakePort = 6;

    Motor SharedRollers(sharedRollerPort, E_MOTOR_GEARSET_36 ,false);
    Motor SingleRoller(singleRollerPort, E_MOTOR_GEARSET_36, true);

    Motor LeftIntake(leftIntakePort, E_MOTOR_GEARSET_18, false);
    Motor RightIntake(rightIntakePort, E_MOTOR_GEARSET_18, true);

    
    void spinRollers(int sharedVelocity, int singleVelocity) { //A function invovling a PD loop for the roller Speed
        float SharedError=sharedVelocity-SharedRollers.get_actual_velocity();

        float SharedPrevError=SharedError;
        float SharedDeltaError=SharedError-SharedPrevError;
        float SharedKP;
        float SharedKD;
        float SharedSetVelocity;

        float SingleError=singleVelocity-SingleRoller.get_actual_velocity();
        
        float SinglePrevError = SingleError;

        float SingleDeltaError = SingleError-SinglePrevError;
        float SingleKP=1;
        float SingleKD=1;
        float singleSetVelocity;
        while (true) {
            int SharedCurrentVelocity = SharedRollers.get_actual_velocity();
            SharedError = sharedVelocity-SharedRollers.get_actual_velocity();
            SharedPrevError=SharedError;

            SharedDeltaError=SharedError-SharedPrevError;

            SharedSetVelocity=SharedError*SharedKP+SharedDeltaError*SharedKD;
            int SingleCurrentVlocity = SingleRoller.get_actual_velocity();
            SingleError=singleVelocity-SingleRoller.get_actual_velocity();

            SingleDeltaError = SingleError-SinglePrevError;

            SinglePrevError = SingleError;

            singleSetVelocity = SingleError*SingleKP+SingleDeltaError*SingleKD;
            SharedRollers.move_velocity(SharedSetVelocity+SharedCurrentVelocity);
            SingleRoller.move_velocity(singleSetVelocity+SingleCurrentVlocity);
        }  
    }

            void IntakeSpeed(int Speed) { //A basic function to set the Intake Speed. It works with a PD loop though
                float LeftSpeed;
                float RightSpeed;
                float Average;

                float Error;
                float PrevError;
                
                float DeltaError;

                float kp;
                float kd;

                float Velocity;

            while(true) {
                LeftSpeed=LeftIntake.get_actual_velocity();
                RightSpeed=RightIntake.get_actual_velocity();

                Average = (LeftSpeed+RightSpeed)/2;

                Error = Speed-Average;

                DeltaError = Error-PrevError;

                PrevError= Error;

                Velocity = Error*kp+DeltaError*kd;

                RightIntake.move_velocity(Velocity);
                LeftIntake.move_velocity(Velocity);
            }
    }

            void TurnAllOn() { // A function that turns all the ball system motors on
                spinRollers(600, 600);
                IntakeSpeed(200);
            }
            void TurnAllOf() { //A function that turns off the motors
                spinRollers(0, 0);
                IntakeSpeed(0);
            }
            void EjectBall() { //Will get rid of the ball;
                spinRollers(600, -600);
            }
            void OnlyRoller() { //Will only have the rollers on
                spinRollers(600, 600);
                IntakeSpeed(0);
            }

            void OnlyIntake() { //Will only Have the Intake On
                IntakeSpeed(200);
                spinRollers(0, 0);
            }

            void KeepBall() { //Will keep the Ball
                spinRollers(600, 600);
            }
            void opcontrol() {
            }
    }