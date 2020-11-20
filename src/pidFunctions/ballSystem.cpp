#include "main.h"
#include <iostream>
#include<string>
#include <cstdio>
#include <ctime>
using namespace std;

int leftIntakePort = 5;
int rightIntakePort = 6;
int singleRollerPort = 3;
int sharedRollerPort = 8;
int opticalSensorPort = 7;

Motor leftIntake(leftIntakePort);
Motor rightIntake(rightIntakePort);
Motor singleRoller(singleRollerPort);
Motor sharedRoller(sharedRollerPort);
Optical opticalSensor(opticalSensorPort);
namespace BallSystem {
    void setIntakeSpeed(int leftIntakeSpeed, int rightIntakeSpeed) {
        leftIntake.move_velocity(leftIntakeSpeed);
        rightIntake.move_velocity(rightIntakeSpeed);
    }
    void setRollerSpeed(int singleSpeed, int sharedSpeed) {
        singleRoller.move_velocity(singleSpeed);
        sharedRoller.move_velocity(sharedSpeed);
    }
    void autoSort(string Color, bool on) {
       if (on) {
           if (Color == "blue") {

           }
           else if (Color == "red") {

           }
       }
    }
  bool AllON = false;
  bool AutoSort = true;
  bool onlyRoller = false;
  void opcontrol() {
      if (master.get_digital(DIGITAL_R1)) {
          if (AllON) {
            setRollerSpeed(100, 100);
            setIntakeSpeed(-100, -100);
            AllON = true;
          }
          else if (!AllON) {
              setRollerSpeed(0, 0);
              setIntakeSpeed(0, 0);
          }
      }
      if (master.get_digital(DIGITAL_R2)) {
          if (!AutoSort) {
              autoSort("blue", true);
          }
          else if (AutoSort) {
              autoSort("blue", false);
          }
      }
      if (master.get_digital(DIGITAL_L1)) {
         if (!onlyRoller) {
            setRollerSpeed(100, 100);
            setIntakeSpeed(0, 0);
            onlyRoller = true;
         }
         else if (onlyRoller) {
             setRollerSpeed(0, 0);
             setIntakeSpeed(100, 100);
         }
      }
      if (master.get_digital(DIGITAL_L2)) {
          setRollerSpeed(-100, 100);
      }
  }
}