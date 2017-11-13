#define CLAW_OPEN 0
#define CLAW_CLOSED 1

task driverClawTask()
{
	int previousToggle = 0;
	//This might cause spooky stuff if auton goes weird
	int clawTarget = CLAW_CLOSED;
	int clawCurrent = CLAW_CLOSED;
	while(true)
	{
		switch(asClaw)
		{
		case AS_CLAW_REST:
			int driverInput = CLAW_TOGGLE_BTN;
			if(driverInput - previousToggle == 1)
			{
				clawTarget = (clawTarget == CLAW_CLOSED) ? CLAW_OPEN : CLAW_CLOSED;
			}
			previousToggle = driverInput;
			break;
		case AS_CLAW_START:
			break;
		case AS_CLAW_RELEASE:
			clawTarget = CLAW_CLOSED;
			break;
		}
		if(clawTarget == CLAW_CLOSED && clawCurrent == CLAW_OPEN)
		{
			motor[ClawM] = 127;
			wait1Msec(CLAW_MOVE_DURATION);
			motor[ClawM] = 0;
			clawCurrent = CLAW_CLOSED;
		}
		else if(clawTarget == CLAW_OPEN && clawCurrent == CLAW_CLOSED)
		{
			motor[ClawM] = -127;
			wait1Msec(CLAW_MOVE_DURATION);
			motor[ClawM] = -CLAW_HOLD;
			clawCurrent = CLAW_OPEN;
		}
		EndTimeSlice();
	}
}
