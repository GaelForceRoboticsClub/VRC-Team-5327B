//This header file contains all code for controlling the claw intake.

#define CLOSED 0
#define OPEN 1

//Stores previous toggle state to prevent accidental rapid switching
int previousToggle = 0;
int intakeToggle = 0;

/*
Function that controls the opening and closing of the claw intake.
Takes the following inputs:
- @toggle			: The input toggle between open and closed
Has no outputs.
*/

void driverClawControl(int toggle)
{
	if(toggle == 1 && previousToggle == 0) //Ensure that this isn't a repeat toggle
	{
		motor[Claw] = (motor[Claw] == CLAW_CLOSED) ? CLAW_OPEN : CLAW_CLOSED; //Set claw to OPEN if CLOSED and vice versa
	}
	previousToggle = toggle;
}

//void driverMogoControl(int adjustDir)
//{
//	motor[MogoM] = adjustDir * 127;
//}

/*
Task that controls intaking.
*/
task intake()
{
	while(true)
	{
		driverClawControl(VexRT[btn8u]);
		EndTimeSlice();
	}
}

task mobile_goal()
{
	while(true)
	{
		driverMogoControl(MogoIn - MogoOut);
		EndTimeSlice();
	}
}
