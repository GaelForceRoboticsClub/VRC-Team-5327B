void mogoIn()
{
	motor[MogoM] = -127;
	waitUntil(SensorValue[MogoPot] < MOGO_IN);
	motor[MogoM] = 0;
}

void mogoOut()
{
	motor[MogoM] = 127;
	waitUntil(SensorValue[MogoPot] > MOGO_OUT);
	motor[MogoM] = 0;
}

task driverMogoTask()
{
	while(true)
	{
		if(MOGO_IN_BTN == 1)
		{
			mogoIn();
			waitUntil(MOGO_IN_BTN == 0);
		}
		else if(MOGO_OUT_BTN == 1)
		{
			mogoOut();
			waitUntil(MOGO_OUT_BTN == 0);
		}
		EndTimeSlice();
	}
}

int autonMogoRequested = MOGO_IN;
int autonMogoActual = MOGO_IN;

void autonMogoOut(bool block = false)
{
	autonMogoRequested = MOGO_OUT;
	waitUntil(!block || autonMogoActual == MOGO_OUT);
}

void autonMogoIn(bool block = false)
{
	autonMogoRequested = MOGO_IN;
	waitUntil(!block || autonMogoActual == MOGO_IN);
}

task autonMogoTask()
{
	while(true)
	{
		if(autonMogoRequested == MOGO_IN && autonMogoActual == MOGO_OUT)
		{
			mogoIn();
			autonMogoActual = autonMogoRequested;
		}
		else if(autonMogoRequested == MOGO_OUT && autonMogoActual == MOGO_IN)
		{
			mogoOut();
			autonMogoActual = autonMogoRequested;
		}
		EndTimeSlice();
	}
}
