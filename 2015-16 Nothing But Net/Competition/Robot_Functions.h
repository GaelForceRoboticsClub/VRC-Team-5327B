//This header file contains the necessary functions to be run throughout the competition

/*
Function governing the movement of the base. Takes 3 parameters:
@X_comp : How much we want to strafe
@Y_comp : How much we want to drive forwards/backwards
@rot_comp : How much we want to rotate the robot CW/CCW
@duration : How long to drive
*/
void BaseControl(int X_comp, int Y_comp, int rot_comp, int duration = LOOP_DELAY)
{
	/*
	Assuming the following control scheme:
	X-Drive Base, where all motors drive forward when set to 127
	X and Y are as they are defined in the Cartesian coordinate plane
	Rotation is positive for CW, negative for CCW
	*/
	motor[RFBase] = Y_comp - X_comp;// + rot_comp;
	motor[LFBase] = Y_comp + X_comp;// + rot_comp;
	motor[RBBase] = Y_comp + X_comp;// + rot_comp;
	motor[LBBase] = Y_comp - X_comp;// + rot_comp;
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
@ball_ount : number of balls we wish to fire
@launcher_adjust : adjust launcher manually
*/
void LauncherControl(int ball_count, int launcher_adjust = 0)
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
	else
	{
		motor[Out1] = launcher_adjust * LAUNCHER_ADJUST_SPEED;
		motor[Out2] = launcher_adjust * LAUNCHER_ADJUST_SPEED;
	}
}

/*
Function that returns a single value for the angle of the launcher based on the combined sensor values. Takes no parameters.
*/
int getAngle()
{
	return (SensorValue[AnglePot1] + SensorValue[AnglePot2] - POT_SCALE) / 2;
}

/*
Function governing the launcher angle. Takes 2 parameters:
@absolute_angle : absolute angle we wish the launcher to be at.
@angle_adjust : direction in which to change the angle.
*/
void AngleControl(int absolute_angle, int angle_adjust = 0)
{
	if(absolute_angle > 0)
	{
		repeatUntil(closeEnough(getAngle(), absolute_angle, ANGLE_TOLERANCE))
		{
			motor[Angle] = 127 * sgn(absolute_angle - getAngle());
		}
	}
	else
	{
		motor[Angle] = ANGLE_ADJUST_SPEED * angle_adjust;
	}
}

/*
Function governing the intake system. Takes 1 parameter:
@direction : whether to intake or outtake balls
*/
void IntakeControl(int direction)
{
	motor[Intake] = 127 * direction;
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
	if(reset)
	{
		Ball_Count = 0;
	}
	if(SensorValue[Turnstile] >= BALL_OUTTOOK)
	{
		Ball_Count++;
	}
	else if(SensorValue[Turnstile] <= BALL_INTOOK)
	{
		Ball_Count--;
	}
	int LED_array[4];
	for(int i = 0; i < Ball_Count; i++)
	{
		LED_array[i] = 1;
	}
	SensorValue[Green1] = LED_array[0];
	SensorValue[Green2] = LED_array[1];
	SensorValue[Green3] = LED_array[2];
	SensorValue[Red] = LED_array[3];
}

int getUltras()
{
	return (SensorValue[BallFinder1] + SensorValue[BallFinder2]) / 2;
}
