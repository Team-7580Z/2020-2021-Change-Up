#include "main.h"

using namespace pros;


//IntializltionStep
int frontRightPort = 9; //Variable with the front right motor port
int frontLeftPort = 1; //Variable with the front left motor port
int backRightPort = 10; //Variable with the back right motor port
int backLeftPort = 2; //Variable with the back left motor port

int imuPort=6;


Motor FrontRight(frontRightPort, E_MOTOR_ENCODER_DEGREES); //Setting Up the Front Right Motor
Motor FrontLeft(frontLeftPort, E_MOTOR_ENCODER_DEGREES);  //Setting Up the Front Left Motor
Motor BackRight(backRightPort, E_MOTOR_ENCODER_DEGREES);  //Setting Up the Back Right Motor
Motor BackLeft(backLeftPort, E_MOTOR_ENCODER_DEGREES); //Setting Up the Back Left Motor

ADIEncoder Ltraking ('G', 'H', false);
ADIEncoder Rtraking ('A', 'B', true);
ADIEncoder Stracking('C', 'D', false);

Imu imu(imuPort);
//Intiilze Drive Vex equipment done


//Create a namespace to allow code to be used in other spot
namespace Drive{
  bool runOdemtry = true;
    float Ldelta = 0;
    float Rdelta = 0;
    float Sdelta = 0;
    
    float LRaw = 0;
    float RRaw = 0;
    float SRaw = 0;

    float LDeltaDist = 0;
    float RDeltaDist = 0;
    float SDeltaDist = 0;

    float pi = 3.14159;

    float LeftRightmm= 220;

    float LeftRightIN = LeftRightmm/25.4;

    float Centermm = 120;
    float Centerin = 120/25.4;
    float leftRightDIamter = 2.75;
    float backDiamter = 3.25;

    float leftRightCin = leftRightDIamter* pi;
    float backCin = backDiamter * pi;

    float rad = 0;
    float circ =0;
    float absoluteOrientationRadian = 0;
    
    float ic = 0;
    float ct = 0;

    float localX;
    float localY;

    float absGlobalX;
    float absGolbalY;
    float absoluteOrientationDegrees;

    float prevGlobalX;
    float prevGlobalY;
    float prevOrientationRad;
  void postion(void* param) {
    lcd::initialize();


    while (true) {
      lcd::set_text(2, "by");
      Ldelta = Ltraking.get_value() - LRaw;
      Rdelta = Rtraking.get_value() - RRaw;
      Sdelta = Stracking.get_value() - SRaw;

      LDeltaDist = (Ldelta*pi/180)  * leftRightCin;
      RDeltaDist = (Rdelta*pi/180) * leftRightCin;
      SDeltaDist = (Sdelta*pi/180) * backCin;
      
      LRaw = Ltraking.get_value();
      RRaw = Rtraking.get_value();
      SRaw = Stracking.get_value();

      absoluteOrientationRadian = (LDeltaDist-RDeltaDist)/LeftRightIN;

       absoluteOrientationDegrees = (absoluteOrientationRadian*(180/pi));

      float deltaA = absoluteOrientationRadian;
      if (deltaA == 0) {
        localX = SDeltaDist;
        localY = RDeltaDist;
      } else {
        localX = (2*sin(deltaA/2)) * ((Sdelta/deltaA)+Centerin);
        localY = (2*sin(deltaA/2)) * ((Rdelta/deltaA)+(LeftRightIN/2));
      }

      float localPolarAngle = 0;
      float localPolarLength = 0;

      if (localX == 0 && localY == 0) {
        localPolarAngle = 0;
        localPolarLength = 0;
      } else {
        localPolarAngle = atan2(localY, localX);
        localPolarLength = sqrt(pow(localX, 2) + pow(localY, 2));
      }

      float gobalPolarLength  = localPolarLength;
      float globalPolarAngle = localPolarAngle - prevOrientationRad - (deltaA/2);

      float golbalX = gobalPolarLength*cos(globalPolarAngle);
      float globalY = gobalPolarLength*sin(globalPolarAngle);

      //Calculate Absolute Postions

      absGlobalX = prevGlobalX + golbalX;
      absGolbalY = prevGlobalY + globalY;

      prevGlobalY = absGolbalY;
      prevGlobalX = absGlobalX;
      
      prevOrientationRad = absoluteOrientationRadian;

      printf("%.6f", absGolbalY);
     
      delay(20);
    
  }

    }
  
      Task CurrentPostion (postion, NULL, TASK_PRIORITY_DEFAULT,
                                  TASK_STACK_DEPTH_DEFAULT, "Notify me! Task");
      void TurnSlide(float endX, float endY, float EndRoatoin, float maxDriveValue, float maxTurnValue, float timeoutMsec, float DriveP, float DriveD, float TurnP, float TurnD){

        float TurnError = (EndRoatoin-absoluteOrientationDegrees);
        float driveError = sqrt(pow((endX - absGlobalX) ,2) + pow((endY - absGolbalY),2));
        float deltaTurnError;
        float deltaDriveError;

        float prevTurnError = TurnError;
        float prevDriveError = driveError;
        while ( TurnError > -1 || TurnError < -1 || driveError < 1 || driveError > -1) {
          TurnError = (EndRoatoin-absoluteOrientationDegrees);
          driveError = sqrt(pow((endX - absGlobalX) ,2) + pow((endY - absGolbalY),2));

          deltaTurnError = TurnError - prevTurnError;
          deltaDriveError = driveError - prevDriveError;

          float finalTurn = TurnError*TurnP+deltaTurnError*TurnD;
          float finalDrive = driveError*DriveP+deltaDriveError*DriveD;

          if (finalTurn > maxTurnValue) {
            finalTurn = maxTurnValue;
          }
          if (finalDrive > maxDriveValue) {
            finalDrive = maxDriveValue;
          }
          if (finalTurn < -maxTurnValue) {
            finalTurn = -maxTurnValue;
          }
          if (finalDrive < -maxDriveValue) {
            finalDrive = -maxDriveValue;
          }
          FrontLeft.move_velocity(finalDrive*(cos(absoluteOrientationRadian + atan2(endY- absGolbalY, endX - absGlobalX) - pi/4))) + finalTurn;
          FrontRight.move_velocity(finalDrive*(cos(3*pi/4-atan2(endY- absGolbalY, endX - absGlobalX)-absoluteOrientationRadian))) - finalTurn;
          BackRight.move_velocity(finalDrive*(cos(absoluteOrientationRadian + atan2(endY- absGolbalY, endX - absGlobalX) - pi/4))) - finalTurn;
          BackLeft.move_velocity(finalDrive*(cos(3*pi/4-atan2(endY- absGolbalY, endX - absGlobalX)-absoluteOrientationRadian))) - finalTurn;
        }
    }

}