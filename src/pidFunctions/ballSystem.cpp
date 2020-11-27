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
        float SharedVelocity;

        while (true) {
            SharedError = sharedVelocity-SharedRollers.get_actual_velocity();
            SharedPrevError=SharedError;

            SharedDeltaError=SharedError-SharedPrevError;

            SharedVelocity=SharedError*SharedKP+SharedDeltaError*SharedKD;
        }  
    }
}