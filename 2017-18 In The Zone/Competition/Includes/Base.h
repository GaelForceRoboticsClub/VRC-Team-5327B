void configBase()
{
	slaveMotor(RMBBase, RFBase);
	slaveMotor(LMBBase, LFBase);
	addMotor(RFBase, 127);
	addMotor(LFBase, 127);
	startTask(motorSlewRateTask);
}

task driverBaseTask()
{
	while(true)
	{
		sm(RFBase, R_JOY);
		sm(LFBase, L_JOY);
		EndTimeSlice();
	}
}

void aFd(int rPower, int lPower, int ticks, int timeout = 5000, bool brake = true)
{
	sm(RFBase, abs(rPower));
	sm(LFBase, abs(lPower));
	SensorValue[RBaseEnc] = 0;
	SensorValue[LBaseEnc] = 0;
	clearTimer(T1);
	waitUntil(abs(SensorValue[RBaseEnc]) >= ticks || time1[T1] > timeout);
	if(time1[T1] > timeout)
	{
		playImmediateTone(750, 20);
	}
	if(brake)
	{
		sm(RFBase, 0);
		sm(LFBase, 0);
	}
}

void aBk(int rPower, int lPower, int ticks, int timeout = 5000, bool brake = true)
{
	sm(RFBase, -abs(rPower));
	sm(LFBase, -abs(lPower));
	SensorValue[RBaseEnc] = 0;
	SensorValue[LBaseEnc] = 0;
	clearTimer(T1);
	waitUntil(abs(SensorValue[RBaseEnc]) >= ticks || time1[T1] > timeout);
	if(time1[T1] > timeout)
	{
		playImmediateTone(750, 20);
	}
	waitUntil(abs(SensorValue[RBaseEnc]) >= ticks);
	if(brake)
	{
		sm(RFBase, 0);
		sm(LFBase, 0);
	}
}

void aTn(int rPower, int lPower, int ticks, int timeout = 5000, bool brake = true)
{
	sm(RFBase, rPower);
	sm(LFBase, lPower);
	SensorValue[RBaseEnc] = 0;
	SensorValue[LBaseEnc] = 0;
	clearTimer(T1);
	waitUntil(abs(SensorValue[RBaseEnc]) >= ticks || time1[T1] > timeout);
	if(time1[T1] > timeout)
	{
		playImmediateTone(750, 20);
	}
	if(rPower < lPower)
	{
		waitUntil(abs(SensorValue[LBaseEnc]) >= ticks);
	}
	else
	{
		waitUntil(abs(SensorValue[RBaseEnc]) >= ticks);
	}
	if(brake)
	{
		sm(RFBase, 0);
		sm(LFBase, 0);
	}
}


//int autonRBaseSpeed = 0;
//int autonLBaseSpeed = 0;
//int autonRBaseTarget = 0;
//int autonLBaseTarget = 0;
//bool autonBaseReached = true;

//void autonDrive(int rPower, int lPower, int tickCount, bool block = false)
//{
//	waitUntil(autonBaseReached);
//	autonBaseReached = false;
//	autonRBaseSpeed = rPower;
//	autonLBaseSpeed = lPower;
//	if(rPower < lPower)
//	{
//		autonLBaseTarget = tickCount;
//	}
//	else
//	{
//		autonRBaseTarget = tickCount;
//	}
//	waitUntil(!block || autonBaseReached);
//}

//task autonBaseTask()
//{
//	while(true)
//	{
//		if(!autonBaseReached)
//		{
//			SensorValue[RBaseEnc] = 0;
//			SensorValue[LBaseEnc] = 0;
//			motor[RBase] = rPower;
//			motor[LBbase] = lpower;
//			waitUntil(abs(SensorValue[RBaseEnc]) >= autonRBaseTarget && abs(SensorValue[LBaseEnc]) >= autonLBaseTarget);
//		}
//		EndTimeSlice();
//	}
//}
