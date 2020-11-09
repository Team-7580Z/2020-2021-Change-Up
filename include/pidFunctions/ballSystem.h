#ifndef _BALLSYSTEM_H_
#define _BALLSYSTEM_H_

namespace  BallSystem {
void TurnOnIntake(int speed);
void TurnOnRollerSystem(int sharedSpeed, int singleSpeed);
void TurnBallSystemOn(int rollerSpeed, int speed);
void TurnOffBallSystem();



void opcontrol();
}
#endif 