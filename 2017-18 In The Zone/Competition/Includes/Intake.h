//This header file contains all code for controlling the claw intake.

#define CLOSED 0
#define OPEN 1

//Stores previous toggle state to prevent accidental rapid switching
int previousToggle = 0;

void setClaw(int state)
{
	SensorValue[ClawPiston] = state;
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
		setClaw(1 - SensorValue[ClawPiston]);
	}
	previousToggle = toggle;
}

void driverSlideControl(float adjustDir, int autoAdjust = 0)
{
	if(autoAdjust == 1)
	{
		motor[SlideM] = 127;
		waitUntil(SensorValue[SlideEnc] >= SLIDE_MAX || globalOverride);
		motor[SlideM] = 0;
	}
	else if (autoAdjust == -1)
	{
		motor[SlideM] = -127;
		waitUntil(SensorValue[SlideEnc] <= SLIDE_MIN || globalOverride);
		motor[SlideM] = 0;
	}
	else
	{
		motor[SlideM] = adjustDir * 127;
	}
}

void driverMogoControl(float adjustDir, int autoAdjust = 0)
{
	if(autoAdjust == 1)
	{
		motor[MogoM] = 127;
		waitUntil(SensorValue[MogoEnc] >= MOGO_MAX || globalOverride);
		motor[MogoM] = 0;
	}
	else if (autoAdjust == -1)
	{
		motor[MogoM] = -127;
		waitUntil(SensorValue[MogoEnc] <= MOGO_MIN || globalOverride);
		motor[MogoM] = 0;
	}
	else
	{
		motor[MogoM] = adjustDir * 127;
	}
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

task slide()
{
	while(true)
	{
		driverSlideControl(SlideUp - SlideDown, SlideAutoUp - SlideAutoDown);
		EndTimeSlice();
	}
}

task mogo()
{
	while(true)
	{
		driverMogoControl(MogoIn - MogoOut, MogoAutoIn - MogoAutoOut);
		EndTimeSlice();
	}
}
