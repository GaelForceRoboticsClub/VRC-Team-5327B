//This file contains all of the code that controls the base of the robot

//Governs the base during Driver Control
task driverBaseTask()
{
	while(true)
	{
		//Back base motors are directly powered by joysticks
		motor[RBase] = R_JOY;
		motor[LBase] = L_JOY;
		//Determine how mogo needs to be adjusted
		int mogoAdjust = MOGO_OUT_BTN - MOGO_IN_BTN;
		if(mogoAdjust == 0)
		{
			//In case we only want to drive, ignore the mobile goal
			motor[LFDMD] = L_JOY;
			motor[LBDMD] = -L_JOY;
			motor[RFDMD] = -R_JOY;
			motor[RBDMD] = R_JOY;
		}
		else
		{
			//If we need to move the mobile goal, control it now
			motor[LFDMD] = 127 * mogoAdjust;
			motor[LBDMD] = 127 * mogoAdjust;
			motor[RFDMD] = -127 * mogoAdjust;
			motor[RBDMD] = -127 * mogoAdjust;
		}
		//Slight delay to avoid hogging
		EndTimeSlice();
	}
}
