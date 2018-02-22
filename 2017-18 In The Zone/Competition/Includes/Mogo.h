task driverMogoTask()
{
	while(true)
	{
		motor[MogoM] = 127 * (MOGO_IN_BTN - MOGO_OUT_BTN);
		EndTimeSlice();
	}
}

int autonMogoRequested = MOGO_IN;
int autonMogoActual = MOGO_IN;

void mogoIn(int target)
{
	motor[MogoM] = 127;
	waitUntil(SensorValue[MogoPot] < target);
	motor[MogoM] = 0;
}

void mogoOut(int target)
{
	motor[MogoM] = -127;
	waitUntil(SensorValue[MogoPot] > target);
	motor[MogoM] = 0;
}

void autonMogoMove(int target, bool block = false)
{
	autonMogoRequested = target;
	waitUntil(!block || autonMogoActual == target);
}

void autonMogoIn(int target = MOGO_IN, bool block = false)
{
	autonMogoMove(target, block);
}

void autonMogoIn(bool block)
{
	autonMogoIn(MOGO_IN, block);
}

void autonMogoOut(int target = MOGO_OUT, bool block = false)
{
	autonMogoMove(target, block);
}

void autonMogoOut(bool block)
{
	autonMogoOut(MOGO_OUT, block);
}

task autonMogoTask()
{
	while(true)
	{
		if(autonMogoRequested < autonMogoActual)
		{
			mogoIn(autonMogoRequested);
			autonMogoActual = autonMogoRequested;
		}
		else if(autonMogoRequested > autonMogoActual)
		{
			mogoOut(autonMogoRequested);
			autonMogoActual = autonMogoRequested;
		}
		if(abs(SensorValue[MogoPot] - MOGO_OUT) < MOGO_THRESHOLD)
		{
			motor[MogoM] = -MOGO_HOLD;
		}
		EndTimeSlice();
	}
}
