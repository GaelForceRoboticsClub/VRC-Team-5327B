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
Function governing the movement of the base during Autonomous. Takes 4 parameters:
@X_comp : How much we want to strafe
@Y_comp : How much we want to drive forwards/backwards
@rot_comp : How much we want to rotate the robot CW/CCW
@duration : How long to drive
*/
void ABase(int X_comp, int Y_comp, int rot_comp, int duration=10)
{
	//Waits until previous duration is 0 (command finished), then adds a new command to the drive array
	waitUntil(Auton_Drive_Array[3] == 0);
	Auton_Drive_Array[0] = X_comp;
	Auton_Drive_Array[1] = Y_comp;
	Auton_Drive_Array[2] = rot_comp;
	Auton_Drive_Array[3] = duration;
}

int ballInLauncher()
{
	if(SensorValue[BallSensorLauncher] < BALL_SENSED_LAUNCHER)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

bool turnGyro(int speed, int change, int tolerance = 50)
{
	int initialGyro = 0;
	repeat(10)
	{
		initialGyro += SensorValue[Gyro]
	}
	initialGyro /= 10;
	repeatUntil(closeEnough(initialGyro, initialGyro + change, tolerance))
	{
		ABase(0, 0, speed);
	}
	ABase(0, 0, 0);
}

int ballInRamp()
{
	if(SensorValue[BallSensorRamp] < BALL_SENSED_RAMP)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int ballInElevator()
{
	if(SensorValue[BallSensorElevator] < BALL_SENSED_ELEVATOR)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/*
Function governing the launcher firing. Takes 3 parameters:
@ball_count : number of balls we wish to fire
@launcher_fast : fire launcher at full speed
@launcher_slow : fire launcher at medium speed
*/
void LauncherControl(int direction, int duration = 0, bool slow = false)
{
	//Shoot a fixed number of balls if specified to do so
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
	}
	else
	{
		motor[Out1] = LAUNCHER_HOLD;
	}
	wait1Msec(duration);
}
/*
Function that returns a single value for the angle of the launcher based on the combined sensor values. Takes no parameters.
*/
int getAngle()
{
	return -SensorValue[AnglePot];
}

/*
Function that returns a single boolean for whether or not we should stop the angle changing mechanism
*/
bool stopAngle()
{
	return emergenStop || closeEnough(getAngle(), ANGLE_MAX_VAL, ANGLE_TOLERANCE) || closeEnough(getAngle(), ANGLE_MIN_VAL, ANGLE_TOLERANCE);
}

/*
Function governing the launcher angle. Takes 3 parameters:
@absolute_angle : absolute angle we wish the launcher to be at.
@angle_adjust : direction in which to change the angle.
@auto_angle : automatic angle setting we wish to use
*/
void AngleControl(int absolute_angle, int angle_adjust = 0, int auto_angle = 0)
{
	if(auto_angle == -1)
	{
		//This portion of the code works 100%
		//First go up until the short constant setting
		repeatUntil(getAngle() >= ANGLE_SHORT_RANGE + 3 || stopAngle())
		{
			motor[Angle] = 127;
		}
		//Then go down until the short constant setting (prevents skip)
		repeatUntil(getAngle() <= ANGLE_SHORT_RANGE - 3 || stopAngle())
		{
			motor[Angle] = -127;
		}
		motor[Angle] = 0;
	}
	else if(auto_angle == 1)
	{
		//This portion of the code needs to work 100%
		//First go up until the long constant setting
		repeatUntil(getAngle() >= ANGLE_LONG_RANGE + 3 || stopAngle())
		{
			motor[Angle] = 65;
		}
		//Then go down until the long constant setting
		repeatUntil(getAngle() <= ANGLE_LONG_RANGE - 3 || stopAngle())
		{
			motor[Angle] = -65;
		}
		motor[Angle] = 0;
	}
	else
	{
		//If we are using manual control, modify the angle accordingly
		if(angle_adjust != 0)
		{
			motor[Angle] = ANGLE_ADJUST_SPEED * angle_adjust;
		}
		else
		{
			motor[Angle] = ANGLE_HOLD;
		}
	}
}
int getUltras()
{
	return (SensorValue[BallFinder1] + SensorValue[BallFinder2]) / 2;
}
/*
Function governing the intake system. Takes 1 parameter:
@direction : whether to intake or outtake balls
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

void ElevatorControl(int direction, int super = 0)
{
	if(direction != 0)
	{
		motor[Elevator] = 127 * direction;
	}
	else if(super == 2)
	{
		motor[Elevator] = 0;
	}
	else if(elevatorOn)
	{
		motor[Elevator] = -127;
	}
	else
	{
		motor[Elevator] = 0;
	}
}

void AIntake(int direction)
{
	Auton_Intake_Array[0] = direction;
}

void autoLoad(int direction1, int direction2)
{
	if(direction1 + direction2 != 0 && sfxShiftBtn == 1)
	{
		motor[AutoLoader] = 127 * (direction1 - direction2);
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
