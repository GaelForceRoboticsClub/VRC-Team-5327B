#define AS_CLAW_REST 0
#define AS_CLAW_START 1
#define AS_CLAW_RELEASE 2
#define AS_LIFT_REST 0
#define AS_LIFT_START 1
#define AS_LIFT_DOWN 2
#define AS_VBAR_REST 0
#define AS_VBAR_START 1
#define AS_VBAR_STACK 2
#define AS_VBAR_SAFE 3

int asClaw = AS_CLAW_REST;
int asLift = AS_LIFT_REST;
int asVbar = AS_VBAR_REST;

task driverAutostackTask()
{
	while(true)
	{
		waitUntil(AS_BTN == 1);
		asClaw = AS_CLAW_START;
		asLift = AS_LIFT_START;
		asVbar = AS_VBAR_START;
		while(asClaw != AS_CLAW_REST || asLift != AS_LIFT_REST || asVbar != AS_VBAR_REST)
		{
			if(asVbar == AS_VBAR_STACK)
			{
				asClaw  = AS_CLAW_RELEASE;
			}
			if(asVbar == AS_VBAR_SAFE)
			{
				asLift = AS_LIFT_DOWN;
			}
			EndTimeSlice();
		}
		EndTimeSlice();
	}
}
