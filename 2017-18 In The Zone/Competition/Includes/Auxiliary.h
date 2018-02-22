float actuationsLeft = MAX_ACTUATIONS;

task driverActuationMonitorTask()
{
	while(true)
	{
		if(actuationsLeft > MID_ACTUATIONS)
		{
			SensorValue[ActuationsLED] = 1;
		}
		else if(actuationsLeft > LOW_ACTUATIONS)
		{
			SensorValue[ActuationsLED] = abs(1 - SensorValue[ActuationsLED]);
			wait1Msec(200);
		}
		else
		{
			SensorValue[ActuationsLED] = 0;
		}
		EndTimeSlice();
	}
}

int lastBrakeToggle = 0;

void brakeControl(int toggle, int assertState = -1)
{
	if(assertState == -1)
	{
		if(toggle == lastBrakeToggle + 1)
		{
			SensorValue[BrakeP] = abs(1 - SensorValue[BrakeP]);
			lastBrakeToggle = toggle;
			actuationsLeft -= 0.5;
		}
	}
	else
	{
		SensorValue[BrakeP] = assertState;
	}
}

task driverBrakeTask()
{
	while(true)
	{
		brakeControl(BRAKE_TOGGLE_BTN);
		EndTimeSlice();
	}
}
