//This header file contains useful functions that can be used for calculations and processes throughout the robot code

/*
Function that can be used to determine if a value is "close enough" to the desired value. Takes 3 parameters:
@current_value : The current value
@desired_value : The desired value
@tolerance : How much above or below the desired value we can be and still be satisfied

Returns 1 value:
@return : True if we are close enough, False if not
*/
bool closeEnough(int current_value, int desired_value, int tolerance)
{
	return (abs(current_value - desired_value) <= tolerance);
}


/*
Function that determines if there is currently a ball in the launcher. Returns 1 value:
@return : 1 if there is a ball present, 0 if there is no ball present in the launcher
*/
int ballInLauncher() //NOT for use with current robot, sensor positioning and constant tweaking required
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


/*
Function that determines if there is currently a ball on the ramp. Returns 1 value:
@return : 1 if there is a ball present, 0 if no ball present on the ramp
*/
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

/*
Function that determines if there is currently a ball in the elevator. Returns 1 value:
@return : 1 if there is a ball present, 0 if no ball present in the elevator
*/
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
Function that determines the current angle of the launcher. Returns 1 value:
@return : 0-1023 based on potentiometer values
*/
int getAngle()
{
	return SensorValue[AnglePot];
}


/*
Function that determines whether or not we should stop the angle changing mechanism. Returns 1 value:
@return : True if we need to stop the movement, False if we should continue moving
*/
bool stopAngle()
{
	return emergenStop || closeEnough(getAngle(), ANGLE_MAX_VAL, ANGLE_TOLERANCE) || closeEnough(getAngle(), ANGLE_MIN_VAL, ANGLE_TOLERANCE);
}

/*
Function that determines what the ultrasonic sensors are seeing. Returns 1 value:
@return : 0-~30 based on average Ball Finder readings
*/
int getUltras()
{
	return (SensorValue[BallFinder1] + SensorValue[BallFinder2]) / 2;
}
