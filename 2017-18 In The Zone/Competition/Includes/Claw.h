//This file contains all of the code that controls the claw of the robot

//Variable to maintain the previous claw state for toggling
int lastState = 0;

/**
 * Controls claw toggling.
 * @param state : 1 to toggle, 0 otherwise
 */
void clawControl(int state)
{
	SensorValue[IntakeP] = state;
	if(state == lastState + 1)
	{
		actuationsLeft -= 0.25;
	}
	lastState = state;
}

//Governs the claw during Driver Control
task driverClawTask()
{
	while(true)
	{
		//Toggle based on the value of the joystick button
		clawControl(CLAW_RELEASE_BTN);
		//Slight delay to avoid hogging
		EndTimeSlice();
	}
}
