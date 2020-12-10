import numpy as np

rows = 0
def score(FrontLeftGoal, FrontRightGoal,FrontCenterGoal, CenterGoal, CenterRightGoal, CenterLeftGoal, BackRightGoal, BackLeftGoal, BackCenterGoal, OurBallsInFrontLeftGoal, OurBallsInFrontCenterGoal, OurBallsInFrontRightGoal, OurBallsInBackLeftGoal, OUrBallsInBackRightGoal, OUrBallsInBackCenterGoal, OurBallsinCenterRightGoal, OurBallsInCenterGoal, OurBallsIncenterLeftGoal, BallsDesocredinFrontLeft, BallsDescoredInFrontCenter, BallsDescoredInFrontRight, BallsDescoredInCenterLeft, BallsDescoredInCenter, BallsDescoredInCenterRight, BallsDescoredInBackLeft, BallsDescoredInBackCenter, BallsDescoredInBackRight):
    if (FrontLeftGoal==True and FrontRightGoal==True and FrontCenterGoal==True):
        rows = rows + 1
    if (CenterGoal==True and CenterLeftGoal==True and CenterRightGoal==True):
        rows += 1
    if (BackCenterGoal==True and BackLeftGoal==True and BackRightGoal==True):
        rows += 1
    if (CenterGoal==True):
        if(FrontLeftGoal==True and BackRightGoal==True):
            rows += 1
        if(FrontRightGoal==True and BackLeftGoal==True):
            rows += 1
    if(FrontLeftGoal==True and CenterLeftGoal==True and BackLeftGoal==True):
        rows += 1
    if(FrontCenterGoal==True and CenterGoal==True and BackCenterGoal==True):
        rows += 1
    if(FrontRightGoal==True and CenterRightGoal==True and BackRightGoal==True):
        rows += 1
    else:
        rows = rows
    