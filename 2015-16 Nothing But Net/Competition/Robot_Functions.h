//This header file contains the necessary functions to be run throughout the competition

/*
Function governing the movement of the base. Takes 3 parameters:
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
	Rotation is posi0tive for CW, negative for CCW
	*/
	motor[RFBase] = Y_comp - X_comp - (rot_comp * (1 - 0.75 * slow));
	motor[LFBase] = Y_comp + X_comp + (rot_comp * (1 - 0.75 * slow));
	motor[RBBase] = Y_comp + X_comp - (rot_comp * (1 - 0.75 * slow));
	motor[LBBase] = Y_comp - X_comp + (rot_comp * (1 - 0.75 * slow));
	wait1Msec(duration);
	motor[RFBase] = 0;
	motor[LFBase] = 0;
	motor[RBBase] = 0;
	motor[LBBase] = 0;
}

void ABase(int X_comp, int Y_comp, int rot_comp, int duration)
{
	waitUntil(Auton_Drive_Array[3] == 0);
	Auton_Drive_Array[0] = X_comp;
	Auton_Drive_Array[1] = Y_comp;
	Auton_Drive_Array[2] = rot_comp;
	Auton_Drive_Array[3] = duration;
}

/*
Function governing the launcher firing. Takes 1 parameter:
@ball_count : number of balls we wish to fire
@launcher_adjust : adjust launcher manually
*/
void LauncherControl(int ball_count, int launcher_fast = 0, int launcher_slow = 0)
{
	if(ball_count > 0)
	{
		repeat(ball_count)
		{
			motor[Out1] = 127;
			motor[Out2] = 127;
			waitUntil(SensorValue[LauncherSet] == 1);
			motor[Out1] = 0;
			motor[Out2] = 0;
			wait1Msec(DELAY_BETWEEN_BALLS);
		}
	}
	else if(launcher_fast == 1)
	{
		motor[Out1] = launcher_fast * LAUNCHER_ADJUST_SPEED;
		motor[Out2] = launcher_fast * LAUNCHER_ADJUST_SPEED;
	}
	else if(launcher_slow == 1)
	{
		motor[Out1] = launcher_slow * LAUNCHER_SLOW_SPEED;
		motor[Out2] = launcher_slow * LAUNCHER_SLOW_SPEED;
	}
	else
	{
		motor[Out1] = LAUNCHER_HOLD;
		motor[Out2] = LAUNCHER_HOLD;
	}
}

/*
Function that returns a single value for the angle of the launcher based on the combined sensor values. Takes no parameters.
*/
int getAngle()
{
	return -SensorValue[AnglePot];
}

bool stopAngle()
{
	return emergenStop || closeEnough(getAngle(), ANGLE_MAX_VAL, ANGLE_TOLERANCE) || closeEnough(getAngle(), ANGLE_MIN_VAL, ANGLE_TOLERANCE);
}

/*
Function governing the launcher angle. Takes 2 parameters:
@absolute_angle : absolute angle we wish the launcher to be at.
@angle_adjust : direction in which to change the angle.
*/
void AngleControl(int absolute_angle, int angle_adjust = 0, int auto_angle = 0)
{
	if(absolute_angle != 0)
	{
	}
	else if(auto_angle == -1)
	{
			repeatUntil(getAngle() >= ANGLE_SHORT_RANGE || stopAngle())
			{
				motor[Angle] = 127;
				clearLCDLine(0);
				clearLCDLine(1);
				displayLCDNumber(0, 0, getAngle());
				displayLCDNumber(1, 0, ANGLE_SHORT_RANGE);
				wait1Msec(1);
			}
			repeatUntil(getAngle() <= ANGLE_SHORT_RANGE || stopAngle())
			{
				motor[Angle] = -127;
				clearLCDLine(0);
				clearLCDLine(1);
				displayLCDNumber(0, 0, getAngle());
				displayLCDNumber(1, 0, ANGLE_SHORT_RANGE);
				wait1Msec(1);
			}
			motor[Angle] = 0;
		}
		else if(auto_angle == 1)
		{
			motor[RFBase] = 100;
			motor[LFBase] = 100;
			motor[RBBase] = 100;
			motor[LBBase] = 100;
			wait1Msec(1000);
			motor[RFBase] = 0;
			motor[LFBase] = 0;
			motor[RBBase] = 0;
			motor[LBBase] = 0;
			repeatUntil(getAngle() >= ANGLE_LONG_RANGE || stopAngle())
			{
				motor[Angle] = 127;
				clearLCDLine(0);
				clearLCDLine(1);
				displayLCDNumber(0, 0, getAngle());
				displayLCDNumber(1, 0, ANGLE_LONG_RANGE);
				wait1Msec(1);
			}
			repeatUntil(getAngle() <= ANGLE_LONG_RANGE || stopAngle())
			{
				motor[Angle] = -127;
				clearLCDLine(0);
				clearLCDLine(1);
				displayLCDNumber(0, 0, getAngle());
				displayLCDNumber(1, 0, ANGLE_LONG_RANGE);
				wait1Msec(1);
			}
			motor[Angle] = 0;
		}
	else
	{
		if(angle_adjust == 1 && getAngle() < ANGLE_MIN_VAL)
		{
			motor[Angle] = ANGLE_ADJUST_SPEED;
		}
		else if(angle_adjust == -1 && getAngle() > ANGLE_MAX_VAL)
		{
			motor[Angle] = -ANGLE_ADJUST_SPEED;
		}
		else
		{
			motor[Angle] = 0;
		}
	}
}

/*
Function governing the intake system. Takes 1 parameter:
@direction : whether to intake or outtake balls
*/
void IntakeControl(int direction)
{
	motor[Intake] = 127 * direction;
}

void ElevatorControl(int direction)
{
	motor[Elevator] = 127 * direction;
}

void AIntake(int direction)
{
	Auton_Intake_Array[0] = direction;
}
/*
Function in charge of determining whether a ball has entered or exited the intake system
*/
void TurnstileControl(bool reset = false)
{
	//TBD
}

int getUltras()
{
	return (SensorValue[BallFinder1] + SensorValue[BallFinder2]) / 2;
}

void autoLoad()
{
	if(SensorValue[BallSensorLauncher] <= BALL_SENSED_LAUNCHER)
	{
		motor[AutoLoader] = 127;
	}
	else //if(SensorValue[BallSensorLauncher] >= BALL_SENSED_LAUNCHER && SensorValue[BallSensor1] >= BALL_SENSED_RAMP)
	{
		motor[AutoLoader] = -127;
	}
}
