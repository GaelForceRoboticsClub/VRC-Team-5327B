//This header file contains all code for controlling the claw intake.

//Enum clawStates stores the various presets and their corresponding numerical value
#define CLOSED 0
#define OPEN 1
#define FULL_WIDTH 2
#define BACK 3

//Stores previous toggle state to prevent accidental rapid switching
int previousToggle = 0;

//Determines whether driver or PD loop should be in control
bool driverControllingClaw = false;

//Stores target claw state for PD loop
int clawPDTarget = PD_BACK;

//PD loop constants
//(Not defined as constants so they can be modified in debugger)
float clawPDKp = 0.2;
float clawPDKd = 0.05;

//Determines if we need to give full control to driver
bool clawActivateFailsafe = false;

/*
Function that checks if we need to activate failsafe.
Has no inputs or outputs.
*/
void clawFailsafeCheck()
{
	int counter = 0;
	repeat(10)
	{
		counter += (abs(SensorValue[ClawPot] - 255) < 15) ? 1 : 0;
		wait1Msec(1);
		if(counter >= 3)
		{
			motor[Claw] = 25;
			wait1Msec(250);
		}
	}
	clawActivateFailsafe = counter >= 7;
	if(clawActivateFailsafe)
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
void setClawPDTarget(int target)
{
	target = target > CLAW_MAX ? CLAW_MAX - CLAW_TOLERANCE : target;
	target = target < CLAW_MIN ? CLAW_MIN + CLAW_TOLERANCE : target;
	clawPDTarget = target;
}

/*
Function that controls the speed of the claw motors.
Takes the following inputs:
- @speed : The speed the claw should turn at
Has no outputs.
*/
void setClaw(int speed)
{
	motor[Claw] = speed;
}

/*
Function that helps ensure claw doesn't close too much.
Has no inputs.
Returns the following outputs:
- @return : True if we are too closed, False if we are safe.
*/
bool clawTooClosed()
{
	if(clawActivateFailsafe)
	{
		return false;	//If failsafe is active, disable sensor control
	}
	return (SensorValue[ClawPot] < CLAW_MIN - CLAW_TOLERANCE);
}

/*
Function that helps ensure claw doesn't open too much.
Has no inputs.
Returns the following outputs:
- @return : True if we are too wide, False if we are safe.
*/
bool clawTooOpen()
{
	if(clawActivateFailsafe)
	{
		return false;	//If failsafe is active, disable sensor control
	}
	return (SensorValue[ClawPot] > CLAW_MAX + CLAW_TOLERANCE);
}

/*
Function that controls the opening and closing of the claw intake.
Takes the following inputs:
- @clawAdjust : The direction the claw should be adjusted
- @toggle			: The input toggle between open and closed
- @fencePreset: The desired preset width for the claw
Has no outputs.
*/
void driverClawControl(float clawAdjust, int toggle = 0, int fencePreset = 0)
{
	if(clawAdjust != 0)
	{
		driverControllingClaw = true;						//Give full control to driver
		//Make sure claw doesn't go beyond limits
		if((clawAdjust > 0 && !clawTooClosed()) || (clawAdjust < 0 && !clawTooOpen()))
		{
			setClaw(clawAdjust * 127);
		}
	}
	else
	{
		driverControllingClaw = false;					//Allow PD to control claw
		if(toggle == 1 && previousToggle == 0)
		{
			if(SensorValue[LiftPot] > LIFT_THRESHOLD)
			{
				setClawPDTarget(PD_OPEN);
			}
			else
			{
				setClawPDTarget(PD_CLOSED);
			}
		}
		else if(fencePreset == 1)
		{
			setClawPDTarget(PD_FULL_WIDTH);
		}
	}
	previousToggle = toggle;
}

/*
Task that controls intaking.
*/
task intake()
{
	while(true)
	{
		driverClawControl((ClawOpen + CLAW_SLOW_ADJUST * ClawOpenSlow - ClawClose - CLAW_SLOW_ADJUST * ClawCloseSlow), ClawToggle, ClawFenceKnock);
		EndTimeSlice();
	}
}

/*
Task that controls PD for claw.
*/
task clawPD()
{
	setClawPDTarget(PD_BACK);
	int clawPDCurr = 0;
	int clawPDError = 0;
	int clawPDLastError = 0;
	int clawPDDerivative = 0;
	while(true)
	{
		if(driverControllingClaw)	//If driver is moving claw, give him full control
		{
			//Keep target for PD loop updated, so loop is always ready when driver lets go
			setClawPDTarget(SensorValue[ClawPot]);
			//Reset all variables
			clawPDError = 0;
			clawPDLastError = 0;
			clawPDDerivative = 0;
		}
		else	//Otherwise, let PD take care of it
		{
			//Find current value
			clawPDCurr = SensorValue[ClawPot];
			//Calculate current error
			clawPDError = clawPDCurr - clawPDTarget;
			//Check if error is big enough to bother fixing
			if(abs(clawPDError) > CLAW_TOLERANCE)
			{
				//Calculate derivative; since delta time is ~constant,
				//it can be safely ignored and just factored into Kd
				clawPDDerivative = clawPDError - clawPDLastError;
				//Update last error for next loop
				clawPDLastError = clawPDError;
				//Finally, combine P and D to determine output
				setClaw(-(clawPDKp * clawPDLastError + clawPDKd * clawPDDerivative));
			}
		}
		if(clawActivateFailsafe)
		{
			break;
		}
		wait1Msec(15);
		EndTimeSlice();
	}
}
