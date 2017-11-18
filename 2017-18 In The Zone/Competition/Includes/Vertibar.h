pos_PID vbarPID;
int kPVbar = 1;
int kIVbar = 0;
int kDVbar = 2;

void configVbar()
{
	pos_PID_InitController(&vbarPID, VbarPot, kPVbar, kIVbar, kDVbar);
}

bool vbarReached()
{
	return abs(pos_PID_GetError(&vbarPID)) < VBAR_FUZZY;
}

task driverVbarTask()
{
	int vbarPIDTarget = SensorValue[VbarPot];
	while(true)
	{
		switch(asVbar)
		{
		case AS_VBAR_REST:
			if(VBAR_UP_BTN == 1)
			{
				vbarPIDTarget = VBAR_UP;
			}
			else if(VBAR_DOWN_BTN == 1)
			{
				vbarPIDTarget = VBAR_DOWN;
			}
			else if(VBAR_STAGO_BTN == 1)
			{
				vbarPIDTarget = VBAR_STAGO;
			}
			break;
		case AS_VBAR_START:
			vbarPIDTarget = VBAR_UP;
			if(vbarReached())
			{
				asVbar = AS_VBAR_STACK;
			}
			break;
		case AS_VBAR_STACK:
			vbarPIDTarget = VBAR_DOWN;
			if(SensorValue[VbarPot] > VBAR_SAFE)
			{
				asVbar = AS_VBAR_SAFE;
			}
			break;
		case AS_VBAR_SAFE:
			if(vbarReached())
			{
				asVbar = AS_VBAR_REST;
			}
			break;
		}
		pos_PID_SetTargetPosition(&vbarPID, vbarPIDTarget);
		motor[VbarM] = pos_PID_StepController(&vbarPID);
		EndTimeSlice();
	}
}
