#define CLAW_OPEN 0
#define CLAW_CLOSED 1

void clawOperate(int direction)
{
	motor[ClawM] = 127 * direction;
	wait1Msec(CLAW_MOVE_DURATION);
	motor[ClawM] = CLAW_HOLD * direction;
}

task driverClawTask()
{
	int intakeToggle = 1;
	while(true)
	{
		if(CLAW_TOGGLE_BTN == 1)
		{
			intakeToggle *= -1;
			clawOperate(intakeToggle);
			waitUntil(CLAW_TOGGLE_BTN == 0);
		}
		EndTimeSlice();
	}
}

int autonClawRequested = CLAW_CLOSED;
int autonClawActual = CLAW_CLOSED;

void autonClawClose(bool block = false)
{
	autonClawRequested = CLAW_CLOSED;
	waitUntil(!block || autonClawActual == CLAW_CLOSED);
}

void autonClawOpen(bool block = false)
{
	autonClawRequested = CLAW_OPEN;
	waitUntil(!block || autonClawActual == CLAW_OPEN);
}

task autonClawTask()
{
	while(true)
	{
		if(autonClawRequested == CLAW_CLOSED && autonClawActual == CLAW_OPEN)
		{
			clawOperate(-1);
			autonClawActual = autonClawRequested;
		}
		else if(autonClawRequested == CLAW_OPEN && autonClawActual == CLAW_CLOSED)
		{
			clawOperate(1);
			autonClawActual = autonClawRequested;
		}
		EndTimeSlice();
	}
}
