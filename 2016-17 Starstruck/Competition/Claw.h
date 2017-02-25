//This header file contains all code for controlling the claw intake.

//Define OPEN and CLOSED to make code more readable
#define OPEN 1
#define CLOSED 0

//Store previous toggle state to prevent accidental rapid switching
int previousToggle = 0;

void claw(int state)
{
	SensorValue[ClawP] = state;
}

/*
Function that controls the opening and closing of the claw intake.
Takes the following inputs:
 - @toggle : The input toggle used to determine whether claw should be closed/opened
Has no outputs.
*/
void driverClawControl(int toggle)
{
	if(toggle == 1)
	{
		if(SensorValue[ClawP] == OPEN)
		{
			claw(CLOSED);
		}
		else if(SensorValue[ClawP] == CLOSED)
		{
			claw(OPEN);
		}
	}
}
void driverBandsControl(int toggle)
{
	if(toggle == 1)
	{
		if(SensorValue[Bands] == 1)
		{
			SensorValue[Bands] = 0;
		}
		else if(SensorValue[Bands] == 0)
		{
			SensorValue[Bands] = 1;
		}
	}
}

/*
Task that controls intaking.
*/
task intake()
{
	while(true)
	{
		if(vexRT[Btn8U] == 1)
		{
			driverClawControl(1);
			waitUntil(vexRT[Btn8U] == 0);
		}
		if(vexRT[Btn8L] == 1 && vexRT[Btn7R] == 1)
		{
			driverBandsControl(1);
			wait1Msec(500);
		}
		EndTimeSlice();
	}
}
