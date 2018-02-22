void vbarControl(int state)
{
	SensorValue[VbarP] = state;
	if(state == lastState + 1)
	{
		actuationsLeft--;
	}
	lastState = state;
}

task driverVbarTask()
{
	while(true)
	{
		vbarControl(VBAR_UP_BTN - VBAR_DOWN_BTN);
		EndTimeSlice();
	}
}
