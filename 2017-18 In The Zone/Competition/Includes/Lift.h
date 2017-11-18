task driverLiftTask()
{
	while(true)
	{
		int driverLiftAdjust = LIFT_UP_BTN - LIFT_DOWN_BTN;
		if(driverLiftAdjust != 0)
		{
			motor[LiftM] = 127 * driverLiftAdjust;
		}
		else if(abs(SensorValue[LiftPot] - LIFT_MIN) < LIFT_THRESHOLD)
		{
			motor[LiftM] = -LIFT_HOLD;
		}
		else
		{
			motor[LiftM] = 0;
		}
		EndTimeSlice();
	}
}

int autonLiftRequested = SensorValue[LiftPot];
int autonLiftActual = autonLiftRequested;

void liftUp(int target)
{
	motor[LiftM] = 127;
	waitUntil(SensorValue[LiftPot] > target);
	motor[LiftM] = 0;
}

void liftDown(int target)
{
	motor[LiftM] = -127;
	waitUntil(SensorValue[LiftPot] < target);
	motor[LiftM] = 0;
}

void autonLiftMove(int target, bool block = false)
{
	autonLiftRequested = target;
	waitUntil(!block || autonLiftActual == target);
}

void autonLiftUp(int target = LIFT_MAX, bool block = false)
{
	autonLiftMove(target, block);
}

void autonLiftUp(bool block)
{
	autonLiftUp(LIFT_MAX, block);
}

void autonLiftDown(int target = LIFT_MIN, bool block = false)
{
	autonLiftMove(target, block);
}

void autonLiftDown(bool block)
{
	autonLiftDown(LIFT_MIN, block);
}

task autonLiftTask()
{
	while(true)
	{
		if(autonLiftRequested > autonLiftActual)
		{
			liftUp(autonLiftRequested);
			autonLiftActual = autonLiftRequested;
		}
		else if(autonLiftRequested < autonLiftActual)
		{
			liftDown(autonLiftRequested);
			autonLiftActual = autonLiftRequested;
		}
		if(abs(SensorValue[LiftPot] - LIFT_MIN) < LIFT_THRESHOLD)
		{
			motor[LiftM] = -LIFT_HOLD;
		}
		EndTimeSlice();
	}
}
