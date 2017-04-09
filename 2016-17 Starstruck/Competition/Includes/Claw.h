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
int clawPDKp = 0.0;
int clawPDKd = 0.0;

/*
Function that sets the PD feedback loop's target value.
Takes the following inputs:
- @target	: The desired target value
Has no outputs.
*/
void setClawPDTarget(int target)
{
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

bool clawTooClosed()
{
	return (SensorValue[ClawPot] < CLAW_MIN - CLAW_THRESHOLD);
}

bool clawTooOpen()
{
	return (SensorValue[ClawPot] > CLAW_MAX + CLAW_THRESHOLD);
}

/*
Function that controls the opening and closing of the claw intake.
Takes the following inputs:
- @clawAdjust : The direction the claw should be adjusted
- @toggle			: The input toggle between open and closed
- @preset			: The desired preset width for the claw
Has no outputs.
*/
void driverClawControl(int clawAdjust, int toggle = 0, int preset = 0)
{
	if(clawAdjust != 0)
	{
		driverControllingClaw = true;						//Give full control to driver
		//Make sure claw doesn't go beyond limits
		if(clawAdjust > 0 && !clawTooClosed() || clawAdjust < 0 && !clawTooOpen())
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
		else
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
		(ClawOpen + SLOW_CLAW_ADJUST * ClawOpenSlow - ClawClose - SLOW_CLAW_ADJUST * ClawCloseSlow) * 127,
		ClawToggle, (FenceKnock * (int)FULL_WIDTH));
		EndTimeSlice();
	}
}

/*
Task that controls PD for claw.
*/
task clawPD()
{
	int clawPDCurr = SensorValue[ClawPot];
	int clawPDError = 0;
	int clawPDLastError = 0;
	int clawPDDerivative = 0;
	while(true)
	{
		if(driverControllingClaw)	//If driver is moving claw, give him full control
		{
			//Reset all constants
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
			if(clawPDError > CLAW_THRESHOLD)
			{
				//Calculate derivative; since delta time is ~constant,
				//it can be safely ignored and just factored into Kd
				clawPDDerivative = clawPDError - clawPDLastError;
				//Update last error for next loop
				clawPDLastError = clawPDError;
				//Finally, combine P and D to determine output
				motor[Claw] = clawPDKp * clawPDLastError + clawPDKd * clawPDDerivative;
			}
		}
		EndTimeSlice();
	}
}
