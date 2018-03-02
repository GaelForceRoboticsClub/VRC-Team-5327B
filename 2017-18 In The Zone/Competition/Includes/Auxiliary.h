//This file contains auxiliary code, for the various additional subsystems present on the robot

//Variable that tracks the remaining pneumatic actuations
float actuationsLeft = MAX_ACTUATIONS;

//Governs the LED monitoring remaining actuations
task driverActuationMonitorTask()
{
	while(true)
	{
		//If we are comfortably safe
		if(actuationsLeft > MID_ACTUATIONS)
		{
			//Keep the LED on constantly
			SensorValue[ActuationsLED] = 1;
		}
		//If we are in the warning range
		else if(actuationsLeft > LOW_ACTUATIONS)
		{
			//Begin blinking the LED
			SensorValue[ActuationsLED] = abs(1 - SensorValue[ActuationsLED]);
			wait1Msec(200);
		}
		//If we are near empty
		else
		{
			//Turn the LED completely off
			SensorValue[ActuationsLED] = 0;
		}
		//Delay to avoid hogging
		EndTimeSlice();
	}
}

//Variable to track last state of the brake
int lastBrakeToggle = 0;

/*
 * Controls the toggling of the brake
 * @param toggle : 1 to toggle, 0 to do nothing
 * @param assertState : if we need to set the state of brake directly
 */
void brakeControl(int toggle, int assertState = -1)
{
	//Check if we don't want to assert
	if(assertState == -1)
	{
		//Make sure this is not a re-press of button
		if(toggle == lastBrakeToggle + 1)
		{
			//Toggle the brake
			SensorValue[BrakeP] = abs(1 - SensorValue[BrakeP]);
			lastBrakeToggle = toggle;
			//Decrement actuations accordingly for monitor
			actuationsLeft -= 0.5;
		}
	}
	else
	{
		//Otherwise, simply go the asserted state
		SensorValue[BrakeP] = assertState;
	}
}

//Governs the brake during Driver Control
task driverBrakeTask()
{
	while(true)
	{
		//Toggle the brake based on the driver input
		brakeControl(BRAKE_TOGGLE_BTN);
		//Delay to avoid hogging
		EndTimeSlice();
	}
}
