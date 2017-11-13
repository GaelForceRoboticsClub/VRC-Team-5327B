void configBase()
{
	slaveMotor(RMBBase, RFBase);
	slaveMotor(LMBBase, LFBase);
	addMotor(RFBase);
	addMotor(LFBase);
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
