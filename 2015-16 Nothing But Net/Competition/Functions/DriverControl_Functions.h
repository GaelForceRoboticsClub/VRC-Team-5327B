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
	motor[RFBase] = Y_comp - X_comp - rot_comp;
	motor[LFBase] = Y_comp + X_comp + rot_comp;
	motor[RBBase] = Y_comp + X_comp - rot_comp;
	motor[LBBase] = Y_comp - X_comp + rot_comp;
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
	if(duration != 0)
	{
		if(slow)
		{
			motor[Out1] = LAUNCHER_SLOW_SPEED * direction;
		}
		else
		{
			motor[Out1] = 127 * direction;
		}
	}
	wait1Msec(duration);
	if(launchHoldToggle)
	{
		motor[Out1] = LAUNCHER_HOLD;
	}
	else
	{
		motor[Out1] = 0;
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
	//TBD
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
	}
}

/*
Function governing the autoloading system. Takes 2 parameters:
@overrideActive : whether or not we should enable the override of autoloading
@overrideDirection : which direction we should override and enable autoloader
*/
void AutoLoadControl(int overrideActive, int overrideDirection)
{
	if(overrideActive == 1 && overrideDirection != 0)
	{
		motor[AutoLoader] = 127 * overrideDirection;
	}
	else
	{
		if(ballInLauncher()) //Ball in launcher
		{
			if(ballInRamp()) //Ball in Launcher and Ball on ramp
			{
				if(ballInElevator()) //Ball in Launcher and Ball on ramp and Ball in elevator
				{
					//Keep ball in ramp away
					motor[AutoLoader] = AUTOLOAD_BACK;
				}
				else //Ball in Launcher and Ball on ramp and Ball NOT in elevator
				{
					//Keep ball in ramp away
					motor[AutoLoader] = AUTOLOAD_BACK;
				}
			}
			else //Ball in Launcher and Ball NOT on ramp
			{
				if(ballInElevator()) //Ball in Launcher and Ball NOT on ramp and Ball in elevator
				{
					//Keep ramp away, and bring from elevator to ramp
					motor[AutoLoader] = AUTOLOAD_BACK;
					repeatUntil(ballInRamp())
					{
						elevatorOn = true;
					}
					elevatorOn = false;
				}
				else //Ball in Launcher and Ball NOT on ramp and Ball NOT in elevator
				{
					//Nothing to do
					motor[AutoLoader] = 0;
					elevatorOn = false;
				}
			}
		}
		else //Ball NOT in Launcher
		{
			if(ballInRamp()) //Ball NOT in Launcher and Ball on ramp
			{
				if(ballInElevator()) //Ball NOT in Launcher and Ball on ramp and Ball in elevator
				{
					//Bring the ball from the ramp to the launcher, then from the elevator to the ramp
					repeatUntil(ballInLauncher())
					{
						motor[AutoLoader] = AUTOLOAD_FORWARD;
					}
					motor[AutoLoader] = 0;
					repeatUntil(ballInRamp())
					{
						elevatorOn = true;
					}
					elevatorOn = false;
				}
				else //Ball NOT in Launcher and Ball on ramp and Ball NOT in elevator
				{
					//Bring the ball from the ramp to the Launcher
					repeatUntil(ballInLauncher())
					{
						motor[AutoLoader] = AUTOLOAD_FORWARD;
					}
					motor[AutoLoader] = 0;
				}
			}
			else //Ball NOT in Launcher and Ball NOT on ramp
			{
				if(ballInElevator()) //Ball NOT in Launcher and Ball NOT on ramp and Ball in elevator
				{
					//Bring the ball from elevator to the ramp
					repeatUntil(ballInRamp())
					{
						elevatorOn = true;
					}
					elevatorOn = false;
				}
				else //Ball NOT in Launcher and Ball NOT on ramp and Ball NOT in elevator
				{
					//Do nothing, because we have NO balls at all
					motor[AutoLoader] = 0;
					elevatorOn = false;
				}
			}
		}
	}
}
