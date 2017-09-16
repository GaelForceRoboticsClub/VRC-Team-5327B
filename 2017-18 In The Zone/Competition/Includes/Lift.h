//This header file contains all the code for the lift

//Enables slew rate control
int liftSlewTarget = 0;


/*
Function that helps ensure we don't go above max height.
Has no inputs.
Returns the following outputs:
- @return : True if we are too high, False if we are at a safe height.
*/
bool liftTooHigh()
{
	return (SensorValue[LiftPot] > LIFT_MAX + LIFT_TOLERANCE);
}

/*
Function that helps ensure we don't go below min height.
Has no inputs.
Returns the following outputs:
- @return : True if we are too low, False if we are at a safe height.
*/
bool liftTooLow()
{
	return (SensorValue[LiftPot] < LIFT_MIN - LIFT_TOLERANCE);
}

/*
Function that allows for easy lift speed setting.
Takes the following inputs:
- @speed : The speed at which the lift should be set.
Has no outputs.
*/
void setLift(int speed)
{
	liftSlewTarget = speed; //Use slew rate control to prevent wearing down of internal gears
}

/*
Function that controls the lift movement.
Takes the following inputs:
- @adjustDir : The direction we need to adjust the lift in
Has no outputs.
*/
void driverLiftControl(float adjustDir)
{
	if(adjustDir != 0.0)
	{
		if((adjustDir > 0 && !liftTooHigh()) || (adjustDir < 0 && !liftTooLow()))
		{
			setLift(adjustDir * 127);
		}
	}
	else
	{
		setLift(LIFT_HOLD);
	}
}

/*
Task that controls lifting.
*/
task lift()
{
	while(true)
	{
		driverLiftControl(LiftUp - LiftDown + LiftUpSlow * LIFT_SLOW_UP - LiftDownSlow * LIFT_SLOW_DOWN);
		EndTimeSlice();
	}
}

/*
Task limiting rate of change of base to prevent damage to internal gears.
*/
task liftSlewControl()
{
	while(true)
	{
		if(abs(motor[LiftR] - liftSlewTarget) > SLEW_RATE_INCREMENT)
		{
			motor[LiftR] += SLEW_RATE_INCREMENT * sgn(liftSlewTarget - motor[LiftR]);
		}
		else
		{
			motor[LiftR] = liftSlewTarget;
		}
	}
}
