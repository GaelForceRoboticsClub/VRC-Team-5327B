//This header file contains all the code for the lift

int tolerance = 100;

/*
Function that helps ensure we don't go above max height.
Has no inputs.
Returns the following outputs:
- @return : True if we are too high, False if we are at a safe height.
*/
bool liftTooHigh()
{
	return (SensorValue[LiftPot] >= MAX_LIFT_HEIGHT + tolerance * 2);
}

/*
Function that helps ensure we don't go below min height.
Has no inputs.
Returns the following outputs:
- @return : True if we are too low, False if we are at a safe height.
*/
bool liftTooLow()
{
	return (SensorValue[LiftPot] <= MIN_LIFT_HEIGHT - tolerance * 2);
}

/*
Function that allows for easy lift speed setting.
Takes the following inputs:
- @speed : The speed at which the lift should be set.
Has no outputs.
*/
void liftSpeed(int speed)
{
	motor[LiftR12] = speed; //Use slew rate control to prevent wearing down of internal gears
}

//Define this value before function definition
float pdTargetSensor = MIN_LIFT_HEIGHT;

/*
Function that sets target for PD Controller
Takes the following inputs:
- @target : The target setting for PD Controller (defaults to sensor value)
Has the following outputs:
- @pdTargetSensor : Returns the input value for further use
*/
int pdTargetSet(int target = pdTargetSensor)
{
	target = target > MAX_LIFT_HEIGHT ? MAX_LIFT_HEIGHT - tolerance : target;
	target = target < MIN_LIFT_HEIGHT ? MIN_LIFT_HEIGHT + tolerance : target;
	pdTargetSensor = target;
	return pdTargetSensor;
}

/*
Function that controls the lift movement.
Takes the following inputs:
- @adjustDir : The direction we need to adjust the lift in, either 1 (up), -1 (down), or 0 (no adjust)
Has no outputs.
*/
int lift_hold = 15;
bool driverModifyingLift = false;
void driverLiftControl(float adjustDir)
{
	if(adjustDir != 0.0)
	{
	liftSpeed(127 * adjustDir);
	}
	else
	{
/*		if(SensorValue[LiftPot] > 800 && SensorValue[LiftPot] < 1300)
		{
			liftSpeed(15);
		}
		else if(SensorValue[LiftPot] >= 1300 && SensorValue[LiftPot] < 2200)
		{
			liftSpeed(25);
		}
		else if(SensorValue[LiftPot] >= 2200 && SensorValue[LiftPot] < 3000)
		{*/
			liftSpeed(0);
		/*}
		else if(SensorValue[LiftPot] >= 3000)
		{
			liftSpeed(-15);
		}*/
	}
	//Set pdTarget for controlled movement
	/*if(adjustDir > 0 && !liftTooHigh())
	{
		liftSpeed(127 * adjustDir);
	}
	//Make sure in bounds
	if(adjustDir < 0 && !liftTooLow())
	{
		liftSpeed(127 * adjustDir);
	}*/
}


/*
Task that controls lifting.
*/
task lift()
{
	while(true)
	{
		driverLiftControl(LiftUp - LiftDown + LiftUpSlow * 0.5 - LiftDownSlow * 0.3);
		EndTimeSlice();
	}
}

//Initialize PD controller variables
float pdError = 0.0;
float pdLastError = 0.0;
float pdDerivative = 0.0;
float pdOutput = 0.0;

//Coefficients defined here for easy adjustment
float kP = 0.04;
float kD = 0.00;//0.05;

float pdCurrentSensor = SensorValue[LiftPot];
int newTarget = pdCurrentSensor;

task pdController()
{
	while(true)
	{
		pdCurrentSensor = SensorValue[LiftPot];

		//Calculate error
		pdError = -pdCurrentSensor + pdTargetSensor;
		if(abs(pdError) > tolerance)
		{
			//Calculate the derivative
			pdDerivative = pdError - pdLastError;
			pdLastError  = pdError;

			// calculate drive

			pdOutput = (kP * pdError) + (kD * pdDerivative);
		}
		// send to motor
		liftSpeed(pdOutput);
	}
}
