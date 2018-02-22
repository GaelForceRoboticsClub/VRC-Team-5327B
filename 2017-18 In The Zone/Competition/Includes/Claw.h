int lastState = 0;

void clawControl(int state)
{
	SensorValue[IntakeP] = state;
	if(state == lastState + 1)
	{
		actuationsLeft -= 0.25;
	}
	lastState = state;
}

task driverClawTask()
{
	while(true)
	{
		clawControl(CLAW_RELEASE_BTN);
		EndTimeSlice();
	}
}
