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
ADIEncoder Stracking('C', 'D', false);


Imu imu(imuPort);
//Intiilze Drive Vex equipment done


//Create a namespace to allow code to be used in other spot
namespace Drive{
  bool runOdemtry = true;
    //We intialze the deltas for the left, right, and back endoers.
    float Ldelta = 0;
    float Rdelta = 0;
    float Sdelta = 0;

    //We intilize the variable for the prevous value of left delta, right delta, and back delta
    float LRaw = 0;
    float RRaw = 0;
    float SRaw = 0;

    //Intilize the variable that will be used to to caluclate the distance travled
    float LDeltaDist = 0;
    float RDeltaDist = 0;
    float SDeltaDist = 0;

    //Just to make multypiling by pi easier
    float pi = 3.14159;

    //Distance between the left and right encoder in millimeters
    float LeftRightmm= 257;

    //Distance between the left and right encoder in inches
    float LeftRightIN = 10;

    //Millimeters between the back wheel and the tracking center in millimeters
    float Centermm = 152;
    //Distance between the the back wheel and the tracking center in inches
    float Centerin = 152/25.4;

    //The diamter of the wheels used to make the odemtry tracking units for the jelft and the right
    float leftRightDIamter = 2.75;
    float backDiamter = 3.25;

    //The cicmfurance of the wheels used in the left right tracking units
    float leftRightCin = leftRightDIamter* pi;
    //The cicmfurance of the back wheel
    float backCin = backDiamter * pi;

    //We calculate how far a the Left Wheel would move when the Left Enocder rotates 1 degree
    float LWheelDistance = leftRightCin/360;
    //Caluclate how far the back wheel would move when the encoder roates 1 degree
    float SWheelDistance = backCin/ 360;

    //We intilize some variables that will be used in the code
    float rad = 0;
    float circ =0;
    float absoluteOrientationRadian = 0;
    float localPolarAngle;
    float localPolarLength;
    float ic = 0;
    float ct = 0;

    float localX;
    float localY;

    float absGlobalX;
    float absGolbalY;
    float absoluteOrientationDegrees;
    //Variables for the positon
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
  //Function that will run in the background to find current postion
  void postion(void* param) {
    lcd::initialize(); //We inilize the brain screen

    //This loop is needed to make the the the thread always run in the background 
    while (true) {
      
      LPos = Ltraking.get_value();//We get the value of the left encoder
      SPos = Stracking.get_value();//We get the value of the back encoder
      RPos = Rtraking.get_value();//We get the value of the right encoder


      Ldelta = LPos - LRaw; //We caluclate the Left Delta by substracting the current left encoder by the the previous encoder postion
      Rdelta = RPos- RRaw; //We caluclate the Right Delta by substracting the current right enocder postion by the previous encoder postion
      Sdelta = SPos - SRaw; //We caluclate the Back Delta by substracting the current back encoder postion by the prevous encoder postion

      //The total change in distance is caluclated by multiplying the deltas by the constant lwheeldistance we set up earlier 
      LDeltaDist = Ldelta*LWheelDistance; 
      RDeltaDist = Rdelta* LWheelDistance;
      SDeltaDist = Sdelta*SWheelDistance;
      
      //We set the previous encocer value to the current encoder value
      LRaw = LPos;
      RRaw = RPos;
      SRaw = SPos;

      absoluteOrientationRadian = (LPos-RPos)/432;

       absoluteOrientationDegrees = (absoluteOrientationRadian*(180/pi));
      std::string Angle = std::to_string(absoluteOrientationDegrees);
      lcd::initialize();
      lcd::set_text(1, Angle);
 
      float deltaA = absoluteOrientationRadian;
     
     
      if (deltaA == 0) {
        localX = SDeltaDist;
        localY = RDeltaDist;
      } else {
        localX = (2*sin(deltaA/2)) * ((SDeltaDist/deltaA)+Centerin);
        localY = (2*sin(deltaA/2)) * ((RDeltaDist/deltaA)+(LeftRightIN/2));
      }

      float localPolarAngle = 0;
      float localPolarLength= 0;

      if (localX == 0 && localY ==0) {
         localPolarAngle = 0;
         localPolarLength = 0;
      }
      else {
         localPolarAngle = atan2(localY, localX);
         localPolarLength = sqrt(pow(localX, 2) + pow(localY, 2));
      }
      //Calculate Absolute Postions

      float globalPolarLength = localPolarLength;
      float globalPolarAngle = localPolarAngle - prevOrientationRad - (deltaA/2);

       globalX = globalPolarLength*cos(globalPolarAngle);
       golbalY = globalPolarLength*sin(globalPolarAngle);

      absGlobalX = prevGlobalX + globalX;
      absGolbalY = prevGlobalY + golbalY;

      prevGlobalY = absGolbalY;
      prevGlobalX = absGlobalX;
      
      prevOrientationRad = absoluteOrientationRadian;

     
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

        while ( TurnError > 20 || TurnError < -20 || driveError > 1 || driveError < -1) {
          TurnError = (EndRoatoin-absoluteOrientationDegrees);
          driveError = sqrt(pow((endX - absGlobalX) ,2) + pow((endY - absGolbalY),2));

          deltaTurnError = TurnError - prevTurnError;
          deltaDriveError = driveError - prevDriveError;

          float finalTurn = TurnError*TurnP - deltaTurnError*TurnD;
          float finalDrive = driveError*DriveP - deltaDriveError*DriveD;

          prevTurnError= TurnError;
          prevDriveError = driveError;
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
          FrontLeft.move_velocity(finalDrive*(cos(absoluteOrientationRadian + atan2(endY- absGolbalY, endX - absGlobalX) - pi/4)) + finalTurn);
          BackLeft.move_velocity(finalDrive*(cos(3*pi/4-atan2(endY- absGolbalY, endX - absGlobalX)-absoluteOrientationRadian)) + finalTurn);
          FrontRight.move_velocity(finalDrive*(cos(absoluteOrientationRadian + atan2(endY- absGolbalY, endX - absGlobalX) - pi/4)) - finalTurn);
          BackRight.move_velocity(finalDrive*(cos(3*pi/4-atan2(endY- absGolbalY, endX - absGlobalX)-absoluteOrientationRadian)) - finalTurn);
        }
        FrontLeft.move_velocity(0);
        BackLeft.move_velocity(0);
        FrontRight.move_velocity(0);
        BackRight.move_velocity(0);
      }
      void dri() {
        int power = master.get_analog(ANALOG_LEFT_Y);

        int turn = master.get_analog(ANALOG_RIGHT_X);


      }
}