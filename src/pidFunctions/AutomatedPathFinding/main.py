import numpy as np

FrontLeftCorridnate = np.array(-69.96, 0)
print(FrontLeftCorridnate[0])
ceneredScored = False
centerLeftScored = False
centerRightScored = False

FrontRightScored = False
FrontCenterScored = False
FrontLeftScored = False

BackRight = False
BackCenter = False
BackLeft = False

BallShotInFrontRight = True
BallInFrontRightGoal = 0

BallShotInFrontLeft = True
BallInFrontLeftGoal = 0
def IsFrontRightScored():
    if BallShotInFrontRightGoal == True:
        BallInFrontRightGoal =+ 1

    elif BallShotInFrontRight == False:
        BallShotInFrontRight = BallShotInFrontRight

    else:
        BallInFrontRightGoal = BallInFrontRightGoal
    if BallInFrontRight > 0 :
        FrontRightScored = True
    elif BallInFrontRight == 0:
        FrontRightScored == 0
    
    return BallInFrontRightGoal
def IsFrontLeftScored():
    if BallShotInFrontLeft == True:
        BallInFrontLeftGoal =+ 1
    elif BallShotInFrontLeft == False:
        BallInFrontLeftGoal == BallInFrontLeftGoal
    else:
        BallInFrontLeftGoal == BallInFrontLeftGoal
    if BallInFrontLeftGoal > 0:
        FrontLeftScored = True
    elif BallInFrontLeftGoal == 0:
        FrontLeftScored = False
    else:
        FrontLeftScored = False
    
    return BallInFrontLeftGoal


