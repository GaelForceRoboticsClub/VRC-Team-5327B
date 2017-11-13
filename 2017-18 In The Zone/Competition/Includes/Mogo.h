pos_PID mogoPID;
int kPMogo = 1;
int kIMogo = 0;
int kDMogo = 0;

void configMogo()
{
	pos_PID_InitController(&mogoPID, MogoPot, kPMogo, kIMogo, kDMogo);
}

task driverMogoTask()
{
	int mogoPIDTarget = SensorValue[MogoPot];
	while(true)
	{
		if(MOGO_IN_BTN == 1)
		{
			mogoPIDTarget = MOGO_IN;
		}
		else if(MOGO_OUT_BTN == 1)
		{
			mogoPIDTarget = MOGO_OUT;
		}
		pos_PID_SetTargetPosition(&mogoPID, mogoPIDTarget);
		motor[MogoM] = pos_PID_StepController(&mogoPID);
		EndTimeSlice();
	}
}
