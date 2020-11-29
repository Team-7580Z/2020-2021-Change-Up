#include "main.h"

using namespace pros;


//IntializltionStep
int frontRightPort = 9; //Variable with the front right motor port
int frontLeftPort = 1; //Variable with the front left motor port
int backRightPort = 10; //Variable with the back right motor port
int backLeftPort = 2; //Variable with the back left motor port

int imuPort=6;


Motor FrontRight(frontRightPort, true); //Setting Up the Front Right Motor
Motor FrontLeft(frontLeftPort);  //Setting Up the Front Left Motor
Motor BackRight(backRightPort, true);  //Setting Up the Back Right Motor
Motor BackLeft(backLeftPort); //Setting Up the Back Left Motor

ADIEncoder Ltraking ('G', 'H', false);
ADIEncoder Rtraking ('A', 'B', true);
ADIEncoder Stracking('C', 'D', true);


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
    float LPos;
    float RPos;
    float SPos;

    float deltaDistL;
    float DeltaDistR;

    float golbalY;
    float globalX;
  void postion(void* param) {
    lcd::initialize();


    while (true) {
      lcd::set_text(2, "by");
      LPos = Ltraking.get_value();
      SPos = Stracking.get_value();
      RPos = Rtraking.get_value();


      Ldelta = LPos - LRaw;
      Rdelta = RPos- RRaw;
      Sdelta = SPos - SRaw;

      LDeltaDist = (Ldelta*pi/180)  * (LeftRightIN/2);
      RDeltaDist = (Rdelta*pi/180) * (LeftRightIN/2);
      SDeltaDist = (Sdelta*pi/180) * Centerin;
      
      LRaw = LPos;
      RRaw = RPos;
      SRaw = SPos;

      deltaDistL += LDeltaDist;
      DeltaDistR += RDeltaDist;

        absoluteOrientationRadian = 0-((deltaDistL+DeltaDistR)/LeftRightIN);

       absoluteOrientationDegrees = (absoluteOrientationRadian*(180/pi));

      float deltaA = absoluteOrientationRadian;
      if (deltaA == 0) {
        localX = SDeltaDist;
        localY = RDeltaDist;
      } else {
        localX = (2*sin(deltaA/2)) * ((Sdelta/deltaA)-(Centerin));
        localY = (2*sin(deltaA/2)) * ((Rdelta/deltaA)+(LeftRightIN/2));
      }

      float avgThetaArc = absoluteOrientationRadian - (deltaA/2);

      //Calculate Absolute Postions

       globalX = (localY *cos(avgThetaArc)) - (localX * sin(avgThetaArc));
       golbalY = (localY * sin(avgThetaArc)) + (localX * cos(avgThetaArc));
      absGlobalX = prevGlobalX + globalX;
      absGolbalY = prevGlobalY + golbalY;

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
        float driveError = sqrt(pow((endX - absGlobalX) ,2 ) + pow((endY - absGolbalY),2));
        float deltaTurnError;
        float deltaDriveError;

        float prevTurnError = TurnError;
        float prevDriveError = driveError;
        while ( TurnError > -1 || TurnError < -1 || driveError < 1 || driveError > -1) {
          TurnError = (EndRoatoin-absoluteOrientationDegrees);
          driveError = sqrt(pow((endX - absGlobalX) ,2) + pow((endY - absGolbalY),2));

          deltaTurnError = TurnError - prevTurnError;
          deltaDriveError = driveError - prevDriveError;

          float finalTurn = TurnError*TurnP-deltaTurnError*TurnD;
          float finalDrive = driveError*DriveP-deltaDriveError*DriveD;

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
          BackLeft.move_velocity(finalDrive*(cos(absoluteOrientationRadian + atan2(endY- absGolbalY, endX - absGlobalX) - pi/4)) + finalTurn);
          FrontLeft.move_velocity(finalDrive*(cos(3*pi/4-atan2(endY- absGolbalY, endX - absGlobalX)-absoluteOrientationRadian)) + finalTurn);
          BackRight.move_velocity(finalDrive*(cos(absoluteOrientationRadian + atan2(endY- absGolbalY, endX - absGlobalX) - pi/4)) - finalTurn);
          FrontRight.move_velocity(finalDrive*(cos(3*pi/4-atan2(endY- absGolbalY, endX - absGlobalX)-absoluteOrientationRadian)) - finalTurn);
        }
    }
}