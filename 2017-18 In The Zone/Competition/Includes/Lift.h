//This header file contains all the code for the lift

//Enables slew rate control
int liftSlewTarget = 0;

//Determines whether driver or PD loop should be in control
bool driverControllingLift = false;

//Stores target lift position
int liftPDTarget = LIFT_MIN;

//PD loop constants
//(Not defined as constants so they can be modified in debugger)
float liftPDKp = 0.0;
float liftPDKd = 0.0;

/*
Function that sets the PD feedback loop's target value.
Takes the following inputs:
- @target	: The desired target value
Has no outputs.
*/
void setLiftPDTarget(int target)
{
	target = target > CLAW_MAX ? CLAW_MAX - CLAW_TOLERANCE : target;
	target = target < CLAW_MIN ? CLAW_MIN + CLAW_TOLERANCE : target;
	clawPDTarget = target;
}

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
		driverControllingLift = true;						//Give full control to driver
		//Make sure lift doesn't go beyond limits
		if((adjustDir > 0 && !liftTooHigh()) || (adjustDir < 0 && !liftTooLow()))
		{
			setLift(adjustDir * 127);
		}
	}
	else
	{
		driverControllingLift = false;					//Allow PD to control lift
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
Task that controls PD for lift.
*/
task liftPD()
{
	int liftPDCurr = SensorValue[LiftPot];
	int liftPDError = 0;
	int liftPDLastError = 0;
	int liftPDDerivative = 0;
	while(true)
	{
		if(driverControllingLift)	//If driver is moving lift, give him full control
		{
			//Reset all variables
			liftPDError = 0;
			liftPDLastError = 0;
			liftPDDerivative = 0;
			//Keep target for PD loop updated, so loop is always ready when driver lets go
			setLiftPDTarget(SensorValue[LiftPot]);
		}
		else	//Otherwise, let PD take care of it
		{
			//Find current value
			liftPDCurr = SensorValue[LiftPot];
			//Calculate current error
			liftPDError = liftPDCurr - liftPDTarget;
			//Check if error is big enough to bother fixing
			if(abs(liftPDError) > LIFT_TOLERANCE)
			{
				//Calculate derivative; since delta time is ~constant,
				//it can be safely ignored and just factored into Kd
				liftPDDerivative = liftPDError - liftPDLastError;
				//Update last error for next loop
				liftPDLastError = liftPDError;
				//Finally, combine P and D to determine output
				setLift(liftPDKp * liftPDLastError + liftPDKd * liftPDDerivative);
			}
		}
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
		if(abs(motor[LiftR12] - liftSlewTarget) > SLEW_RATE_INCREMENT)
		{
			motor[LiftR12] += SLEW_RATE_INCREMENT * sgn(liftSlewTarget - motor[LiftR12]);
		}
		else
		{
			motor[LiftR12] = liftSlewTarget;
		}
	}
}
