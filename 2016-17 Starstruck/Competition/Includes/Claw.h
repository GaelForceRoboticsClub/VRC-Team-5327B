//This header file contains all code for controlling the claw intake.

//Enum clawStates stores the various presets and their corresponding numerical value
enum clawStates{
	CLOSED = 0,			//Pinched around objects
	OPEN = 1,				//Open at typical claw angle (~130 degrees)
	FULL_WIDTH = 2,	//Open at full width (180 degrees)
	BACK = 3				//Claw folded up for reset (360 degrees)
};

//Stores previous toggle state to prevent accidental rapid switching
int previousToggle = 0;

//Determines whether driver or PD loop should be in control
bool driverControllingClaw = false;

//Stores current claw state
int currClawState = BACK;

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
Function that translates preset states into PD target for the claw.
Takes the following inputs:
- @state : The desired preset state for the claw
Has no outputs.
*/
void presetClaw(int state)
{
	switch(state)
	{
	case CLOSED:
		setClawPDTarget(PD_CLOSED);
	case OPEN:
		setClawPDTarget(PD_OPEN);
	case FULL_WIDTH:
		setClawPDTarget(PD_FULL_WIDTH);
	case BACK:
		setClawPDTarget(PD_BACK);
	default:
	}
	currClawState = state;
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
- @preset			: The desired preset width for the claw
Has no outputs.
*/
void driverClawControl(float clawAdjust, int toggle = 0, int preset = -1)
{
	if(true)
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
		if(toggle == 1 && previousToggle == 0)	//Make sure this is a unique toggle
		{
			presetClaw(currClawState >= (int)OPEN ? CLOSED : OPEN);
		}
		else if(preset != -1)
		{
			presetClaw(preset);
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
		driverClawControl(
		(ClawOpen + CLAW_SLOW_ADJUST * ClawOpenSlow - ClawClose - CLAW_SLOW_ADJUST * ClawCloseSlow),
		ClawToggle, (FenceKnock * (int)FULL_WIDTH));
		EndTimeSlice();
	}
}

/*
Task that controls PD for claw.
*/
task clawPD()
{
	setClawPDTarget(1000);
	int clawPDCurr = 0;
	int clawPDError = 0;
	int clawPDLastError = 0;
	int clawPDDerivative = 0;
	while(true)
	{
		if(driverControllingClaw)	//If driver is moving claw, give him full control
		{
			//Reset all variables
			clawPDError = 0;
			clawPDLastError = 0;
			clawPDDerivative = 0;
			//Keep target for PD loop updated, so loop is always ready when driver lets go
			setClawPDTarget(SensorValue[ClawPot]);
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
				setClaw(clawPDKp * clawPDLastError + clawPDKd * clawPDDerivative);
			}
		}
		if(clawActivateFailsafe)
		{
			break;
		}
		EndTimeSlice();
	}
}
