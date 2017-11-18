task driverVbarTask()
{
	while(true)
	{
		int driverVbarAdjust = VBAR_UP_BTN - VBAR_DOWN_BTN;
		if(driverVbarAdjust != 0)
		{
			motor[VbarM] = 127 * driverVbarAdjust;
		}
		else if(abs(SensorValue[VbarPot] - VBAR_DOWN) < VBAR_THRESHOLD)
		{
			motor[VbarM] = -VBAR_HOLD;
		}
		else
		{
			motor[VbarM] = 0;
		}
		EndTimeSlice();
	}
}

int autonVbarRequested = SensorValue[VbarPot];
int autonVbarActual = autonVbarRequested;

void vbarUp(int target)
{
	motor[VbarM] = 127;
	waitUntil(SensorValue[VbarPot] > target);
	motor[VbarM] = 0;
}

void vbarDown(int target)
{
	motor[VbarM] = -127;
	waitUntil(SensorValue[VbarPot] < target);
	motor[VbarM] = 0;
}

void autonVbarMove(int target, bool block = false)
{
	autonVbarRequested = target;
	waitUntil(!block || autonVbarActual == target);
}

void autonVbarUp(int target = VBAR_UP, bool block = false)
{
	autonVbarMove(target, block);
}

void autonVbarDown(int target = VBAR_DOWN, bool block = false)
{
	autonVbarMove(target, block);
}

task autonVbarTask()
{
	while(true)
	{
		if(autonVbarRequested > autonVbarActual)
		{
			vbarUp(autonVbarRequested);
			autonVbarActual = autonVbarRequested;
		}
		else if(autonVbarRequested < autonVbarActual)
		{
			vbarDown(autonVbarRequested);
			autonVbarActual = autonVbarRequested;
		}
		if(abs(SensorValue[VbarPot] - VBAR_DOWN) < VBAR_THRESHOLD)
		{
			motor[VbarM] = -VBAR_HOLD;
		}
		EndTimeSlice();
	}
}
