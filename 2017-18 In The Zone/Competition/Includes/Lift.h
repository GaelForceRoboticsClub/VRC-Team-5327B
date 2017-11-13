pos_PID liftPID;
int kPLift = 1;
int kILift = 0;
int kDLift = 0;

void configLift()
{
	pos_PID_InitController(&liftPID, LiftPot, kPLift, kILift, kDLift);
}

bool liftReached()
{
	return abs(pos_PID_GetError(&liftPID)) < LIFT_FUZZY;
}

task driverLiftTask()
{
	int liftPIDTarget = SensorValue[LiftPot];
	while(true)
	{
		switch(asLift)
		{
		case AS_LIFT_REST:
			float driverInput = LIFT_UP_BTN + LIFT_UP_SLOW_BTN - LIFT_DOWN_BTN - LIFT_DOWN_SLOW_BTN;
			liftPIDTarget += LIFT_DRIVER_INCREMENT * driverInput;
			break;
		case AS_LIFT_START:
			break;
		case AS_LIFT_DOWN:
			liftPIDTarget = LIFT_MIN;
			if(liftReached())
			{
				asLift = AS_LIFT_REST;
			}
			break;
		}

		pos_PID_SetTargetPosition(&liftPID, liftPIDTarget);
		motor[LiftM] = pos_PID_StepController(&liftPID);
		EndTimeSlice();
	}
}
