//This header file contains all code for controlling the claw intake.

#define CLOSED 0
#define OPEN 1

//Stores previous toggle state to prevent accidental rapid switching
int previousToggle = 0;
 int state = 0;

void setClaw()
{
	if(state == 0)
	{
		motor[ClawM] = 127;
		waitUntil(SensorValue[ClawPot] >= CLAW_CLOSED || OverrideBtn);
		motor[ClawM] = 0;
	}
	else
	{
		motor[ClawM] = -127;
		waitUntil(SensorValue[ClawPot] <= CLAW_OPEN || OverrideBtn);
		motor[ClawM] = 0;
	}
}

/*
Function that controls the opening and closing of the claw intake.
Takes the following inputs:
- @toggle			: The input toggle between open and closed
Has no outputs.
*/
void driverClawControl(int toggle = 0)
{
	if(toggle == 1 && previousToggle == 0)
	{
		state = (1-state);
		setClaw();
	}
	previousToggle = toggle;
}


void driverMogoControl(int adjustDir)
{
	motor[MogoM] = adjustDir * 127;
}

/*
Task that controls intaking.
*/
task intake()
{
	while(true)
	{
		driverClawControl(ClawToggle);
		EndTimeSlice();
	}
}

task mogo()
{
	while(true)
	{
		driverMogoControl(MogoIn - MogoOut);
		EndTimeSlice();
	}
}
