import numpy as np

rows = 0

def score(OurBallsInFrontLeftGoal, OurBallsInFrontCenterGoal, OurBallsInFrontRightGoal, OurBallsInBackLeftGoal, OUrBallsInBackRightGoal, OUrBallsInBackCenterGoal, OurBallsinCenterRightGoal, OurBallsInCenterGoal, OurBallsIncenterLeftGoal, BallsDesocredinFrontLeft, BallsDescoredInFrontCenter, BallsDescoredInFrontRight, BallsDescoredInCenterLeft, BallsDescoredInCenter, BallsDescoredInCenterRight, BallsDescoredInBackLeft, BallsDescoredInBackCenter, BallsDescoredInBackRight):
    rows = 0
    if(OurBallsInFrontLeftGoal > 0):
        FrontLeftGoal = True

    if(OurBallsInFrontRightGoal > 0):
        FrontRightGoal = True

    if(OurBallsInFrontCenterGoal > 0):
        FrontCenterGoal = True

    if(OurBallsinCenterRightGoal > 0):
        CenterRightGoal = True

    if(OurBallsInCenterGoal > 0):
        CenterGoal = True

    if(OurBallsIncenterLeftGoal > 0):
        CenterLeftGoal = True
    
    if(OurBallsInBackLeftGoal > 0):
        BackLeftGoal = True
    
    if(OUrBallsInBackCenterGoal > 0):
        BackCenterGoal = True

    if(OUrBallsInBackRightGoal >0):
        BackRightGoal = True

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


    totalBalls = OUrBallsInBackCenterGoal+OurBallsInBackLeftGoal+OUrBallsInBackRightGoal+OurBallsInFrontCenterGoal+OurBallsInFrontRightGoal+OurBallsInFrontLeftGoal+OurBallsInCenterGoal+OurBallsIncenterLeftGoal+OurBallsIncenterLeftGoal

    return totalBalls    