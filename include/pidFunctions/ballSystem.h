#ifndef _BALLSYSTEM_H_
#define _BALLSYSTEM_H_

namespace BallSystem {
    void setIntakeSpeed(int leftIntakeSpeed, int rightIntakeSpeed);
    void setRollerSpeed(int singleSpeed, int sharedSpeed);

    void opcontrol();
}
#endif 