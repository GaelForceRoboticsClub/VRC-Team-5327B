//This header file contains the necessary functions to be run throughout the competition


/*
Function governing the movement of the base. Takes 4 parameters:
@X_comp : How much we want to strafe
@Y_comp : How much we want to drive forwards/backwards
@rot_comp : How much we want to rotate the robot CW/CCW
@duration : How long to drive
*/
void BaseControl(int X_comp, int Y_comp, int rot_comp, int slow = 0, int duration = LOOP_DELAY)
{
	/*
	Assuming the following control scheme:
	X-Drive Base, where all motors drive forward when set to 127
	X and Y are as they are defined in the Cartesian coordinate plane
	Rotation is positive for CW, negative for CCW
	*/
	rot_comp = rot_comp * (1 - (0.75 * slow));
	int RF = Y_comp - X_comp - rot_comp;
	int LF = Y_comp + X_comp + rot_comp;
	int RB = Y_comp + X_comp - rot_comp;
	int LB = Y_comp - X_comp + rot_comp;
	motor[RFBase] = TrueSpeed[abs(RF)] * sgn(RF);
	motor[LFBase] = TrueSpeed[abs(LF)] * sgn(LF);
	motor[RBBase] = TrueSpeed[abs(RB)] * sgn(RB);
	motor[LBBase] = TrueSpeed[abs(LB)] * sgn(LB);
	wait1Msec(duration);
	motor[RFBase] = 0;
	motor[LFBase] = 0;
	motor[RBBase] = 0;
	motor[LBBase] = 0;
}


/*
Function governing the launcher firing. Takes 3 parameters:
@direction : Direction in which to fire
@duration : How long to fire
@slow : Whether we should shoot slow
*/
void LauncherControl(int direction, int duration = 500, bool slow = false)
{
	if(direction != 0)
	{
		if(slow)
		{
			motor[Out1] = LAUNCHER_SLOW_SPEED * direction;
		}
		else
		{
			motor[Out1] = 127 * direction;
		}
		wait1Msec(duration);
	}
	else if(launchHoldToggle && SensorValue[LauncherSet] != 1)
	{
		motor[Out1] = 127;
	}
	else
	{
		motor[Out1] = LAUNCHER_HOLD;
	}
}


/*
Function governing the launcher angle. Takes 3 parameters:
@auto_angle : automatic angle setting we wish to use
@angle_adjust : direction in which to change the angle
@absolute_angle : absolute angle we wish the launcher to be at
*/
void AngleControl(int auto_angle, int angle_adjust = 0, int absolute_angle = 0)
{
	if(angle_adjust == 1)
	{
		motor[Angle] = ANGLE_ADJUST_SPEED_UP;
	}
	else if(angle_adjust == -1)
	{
		motor[Angle] = -ANGLE_ADJUST_SPEED_DOWN;
	}
	else
	{
		motor[Angle] = ANGLE_HOLD;
	}
}


/*
Function governing the intake system. Takes 2 parameters:
@direction : whether to intake or outtake balls
@autoIntakeOn : whether we should enable automatic ball sensing and intaking
*/
void IntakeControl(int direction, bool autoIntakeOn = false)
{
	if(autoIntakeOn)
	{
		if((SensorValue[BallFinder1] - SensorValue[BallFinder2]) < 2 && getUltras() > 5) //If we see the ball straight ahead
		{
			BaseControl(0, 127, 0);
		}
		else if(SensorValue[BallFinder1] > SensorValue[BallFinder2] + 2) //If we see the ball more on the right
		{
			BaseControl(63, 63, 0);
		}
		else if(SensorValue[BallFinder2] > SensorValue[BallFinder1] + 2) //If we see the ball more on the left
		{
			BaseControl(-63, 63, 0);
		}
		else //If we don't see the ball
		{
			//Do nothing, we let the driver control intake and base now
		}
		if(getUltras() < 8) //If we are close enough, turn the intake on
		{
			IntakeControl(1);
		}
	}
	else
	{
		motor[Intake] = 127 * direction;
		if(elevatorOn)
		{
			motor[Elevator] = -127;
			waitUntil(ballInRamp() == 1);
			wait1Msec(250);
			motor[Elevator] = 0;
		}
		else
		{
			motor[Elevator] = 127 * direction;
		}
	}
}

/*
Function governing the autoloading system. Takes 2 parameters:
@overrideIn : override autoloading in
@overrideOut : override autoloading out
*/
void AutoLoadControl(int overrideIn, int overrideOut)
{
	if(overrideIn == 0 && overrideOut == 0)
	{
		if(ballInElevator() == 1)
		{
			if(ballInRamp() == 1)
			{
				if(ballInLauncher() == 1)
				{
					if(ballLauncherReady() == 1)
					{
						//Everything is full, so repel balls
						elevatorOn = false;
						motor[AutoLoader] = -127;
					}
					else
					{
						//Everything is full, so do nothing
						elevatorOn = false;
						motor[AutoLoader] = -127;
					}
				}
				else
				{
					if(ballLauncherReady() == 1)
					{
						//Launcher is empty and ready
						motor[AutoLoader] = 127;
						//Bring in next ball
						elevatorOn = true;
					}
					else
					{
						//Launcher not ready, so repel balls
						motor[AutoLoader] = -127;
						elevatorOn = false;
					}
				}
			}
			else
			{
				if(ballInLauncher() == 1)
				{
					if(ballLauncherReady() == 1)
					{
						//Ramp is empty, so bring up from elevator
						elevatorOn = true;
						motor[AutoLoader] = 0;
					}
					else
					{
						//Ramp is empty, so bring up from elevator
						elevatorOn = true;
						motor[AutoLoader] = 0;
					}
				}
				else
				{
					if(ballLauncherReady() == 1)
					{
						//Launcher is empty and ready
						motor[AutoLoader] = 127;
						//Bring in next ball
						elevatorOn = true;
					}
					else
					{
						//Ramp is empty, so bring up from elevator
						elevatorOn = true;
						motor[AutoLoader] = 0;
					}
				}
			}
		}
		else
		{
			if(ballInRamp() == 1)
			{
				if(ballInLauncher() == 1)
				{
					if(ballLauncherReady() == 1)
					{
						//Pushed all the way up so repel balls
						motor[AutoLoader] = -127;
						elevatorOn = false;
					}
					else
					{
						//Pushed all the way up so repel balls
						motor[AutoLoader] = -127;
						elevatorOn = false;
					}
				}
				else
				{
					if(ballLauncherReady() == 1)
					{
						//Launcher is empty and ready
						motor[AutoLoader] = 127;
						//Bring in next ball
						elevatorOn = false;
					}
					else
					{
						//Launcher not ready, so repel balls
						motor[AutoLoader] = -127;
						elevatorOn = false;
					}
				}
			}
			else
			{
				if(ballInLauncher() == 1)
				{
					if(ballLauncherReady() == 1)
					{
						//Everything has been pushed forward, so do nothing
						motor[AutoLoader] = 0;
						elevatorOn = false;
					}
					else
					{
						//Everything has been pushed forward, so do nothing
						motor[AutoLoader] = 0;
						elevatorOn = false;
					}
				}
				else
				{
					if(ballLauncherReady() == 1)
					{
						//Launcher is empty and ready
						motor[AutoLoader] = 0;
						//Bring in next ball
						elevatorOn = false;
					}
					else
					{
						//Launcher not ready, so do nothing
						motor[AutoLoader] = 0;
						elevatorOn = false;
					}
				}
			}
		}
	}
	else
	{
		motor[AutoLoader] = 127 * (overrideIn - overrideOut);
	}
}
