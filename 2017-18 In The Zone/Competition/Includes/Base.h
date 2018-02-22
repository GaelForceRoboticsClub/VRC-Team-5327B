task driverBaseTask()
{
	while(true)
	{
		motor[RBase] = R_JOY;
		motor[LBase] = L_JOY;
		int mogoAdjust = MOGO_OUT_BTN - MOGO_IN_BTN;
		if(mogoAdjust == 0)
		{
			motor[LFDMD] = L_JOY;
			motor[LBDMD] = -L_JOY;
			motor[RFDMD] = -R_JOY;
			motor[RBDMD] = R_JOY;
		}
		else
		{
			motor[LFDMD] = 127 * mogoAdjust;
			motor[LBDMD] = 127 * mogoAdjust;
			motor[RFDMD] = -127 * mogoAdjust;
			motor[RBDMD] = -127 * mogoAdjust;
		}
		//Sorry I'm a rebel, this code still exists but commented out. If my above if-else loop fails, just comment that out instead.

		/*motor[LBDMD] = (-L_JOY * (1 - vexRT[Btn8D]) * (1 - vexRT[Btn8U])) + 127 * (vexRT[Btn8U] - vexRT[Btn8D]);
		motor[RBDMD] = (R_JOY * (1 - vexRT[Btn8D]) * (1 - vexRT[Btn8U])) - 127 * (vexRT[Btn8U] - vexRT[Btn8D]);
		motor[LFDMD] = (L_JOY * (1 - vexRT[Btn8U]) * (1 - vexRT[Btn8D])) - 127 * (vexRT[Btn8D] - vexRT[Btn8U]);
		motor[RFDMD] = (-R_JOY * (1 - vexRT[Btn8U]) * (1 - vexRT[Btn8D])) + 127 * (vexRT[Btn8D] - vexRT[Btn8U]);*/
		EndTimeSlice();
	}
}
