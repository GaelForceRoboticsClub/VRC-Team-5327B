//This header file contains all the code for the lift

//Enables slew rate control
int liftSlewTarget = 0;

//Determines whether driver or PD loop should be in control
bool driverControllingLift = false;

//Stores target lift position
int liftPDTarget = LIFT_MIN;

//PD loop constants
//(Not defined as constants so they can be modified in debugger)
float liftPDKp = 0.25;
float liftPDKd = 0.5;

//Determines if we need to give full control to driver
bool liftActivateFailsafe = false;

/*
Function that checks if we need to activate failsafe.
Has no inputs or outputs.
*/
void liftFailsafeCheck()
{
	int counter = 0;
	repeat(10)
	{
		counter += (abs(SensorValue[LiftPot] - 255) < 5) ? 1 : 0;
		wait1Msec(1);
		if(counter >= 3)
		{
			motor[LiftR12] = 45;
			wait1Msec(250);
		}
	}
	liftActivateFailsafe = (counter >= 7);
	if(liftActivateFailsafe)
	{
		playSound(soundLowBuzz);
	}
}

/*
Function that sets the PD feedback loop's target value.
Takes the following inputs:
- @target	: The desired target value
Has no outputs.
*/
void setLiftPDTarget(int target)
{
	target = target > LIFT_MAX ? LIFT_MAX - LIFT_TOLERANCE : target;
	target = target < LIFT_MIN ? LIFT_MIN + LIFT_TOLERANCE : target;
	liftPDTarget = target;
}

/*
Function that helps ensure we don't go above max height.
Has no inputs.
Returns the following outputs:
- @return : True if we are too high, False if we are at a safe height.
*/
bool liftTooHigh()
{
	if(liftActivateFailsafe)
	{
		return false;	//If failsafe is active, disable sensor control
	}
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
	if(liftActivateFailsafe)
	{
		return false;	//If failsafe is active, disable sensor control
	}
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
int lift_hold = 0;
int desiredValue = LIFT_MIN;
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
		lift_hold = 0;
		//Make sure lift doesn't go beyond limits
		if((adjustDir > 0 && !liftTooHigh()) || (adjustDir < 0 && !liftTooLow()))
		{
			setLift(adjustDir * 127);
		}
		desiredValue = SensorValue[LiftPot];
	}
	else
	{
		if(SensorValue[LiftPot] < 290)
		{
			setLift(-10);
		}
		else if(SensorValue[LiftPot] < 850)
		{
			setLift(15);
		}
		else if(SensorValue[LiftPot] < 2000)
		{
			setLift(5);
		}
		else if(SensorValue[LiftPot] < 2500)
		{
			setLift(-15);
		}
		else
		{
			setLift(-25);
		}
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

			//Check if error is big enough to bother fixing

			//Calculate derivative; since delta time is ~constant,
			//it can be safely ignored and just factored into Kd
			liftPDDerivative = liftPDError - liftPDLastError;
			//Update last error for next loop
			liftPDLastError = liftPDError;
			//Finally, combine P and D to determine output
			setLift(-(liftPDKp * liftPDLastError + liftPDKd * liftPDDerivative));
		}
		if(liftActivateFailsafe)
		{
			break;	//No PD loop if failsafe is active
		}
		wait1Msec(15);
	}
}

/*
Task limiting rate of change of base to prevent damage to internal gears.
*/
task liftSlewControl()
{
	while(true)
	{
		if(abs(motor[LiftR12] - liftSlewTarget) > SLEW_RATE_INCREMENT_LIFT)
		{
			motor[LiftR12] += SLEW_RATE_INCREMENT_LIFT * sgn(liftSlewTarget - motor[LiftR12]);
		}
		else
		{
			motor[LiftR12] = liftSlewTarget;
		}
		wait1Msec(SLEW_RATE_WAIT);
	}
}
