#include "main.h"
using namespace std;
namespace ballSystem {
    int sharedRollerPort = 8;
    int singleRollerPort = 3;
    
    int leftIntakePort = 5;
    int rightIntakePort = 6;

    Motor SharedRollers(sharedRollerPort, E_MOTOR_GEARSET_36 ,false);
    Motor SingleRoller(singleRollerPort, E_MOTOR_GEARSET_36, true);

    Motor LeftIntake(leftIntakePort, E_MOTOR_GEARSET_18, false);
    Motor RightIntake(rightIntakePort, E_MOTOR_GEARSET_18, true);

    
    void spinRollers(int sharedVelocity, int singleVelocity) {
        float SharedError=sharedVelocity-SharedRollers.get_actual_velocity();

        float SharedPrevError=SharedError;
        float SharedDeltaError=SharedError-SharedPrevError;
        float SharedKP;
        float SharedKD;
        float SharedSetVelocity;

        float SingleError=singleVelocity-SingleRoller.get_actual_velocity();
        
        float SinglePrevError = SingleError;

        float SingleDeltaError = SingleError-SinglePrevError;
        float SingleKP;
        float SingleKD;
        float singleSetVelocity;
        while (true) {
            SharedError = sharedVelocity-SharedRollers.get_actual_velocity();
            SharedPrevError=SharedError;

            SharedDeltaError=SharedError-SharedPrevError;

            SharedSetVelocity=SharedError*SharedKP+SharedDeltaError*SharedKD;

            SingleError=singleVelocity-SingleRoller.get_actual_velocity();
            SinglePrevError = SingleError;

            SingleDeltaError = SingleError-SinglePrevError;

            singleSetVelocity = SingleError*SingleKP+SinglePrevError*SingleKD;

            SharedRollers.move_velocity(SharedSetVelocity);
            SingleRoller.move_velocity(singleSetVelocity);
        }  
    }

    void IntakeSpeed() {
        
    }
}