//This file contains all of the code to control the vertibar of the robot

/*
 * Controls the movement of the vertibar
 * @param state : 1 if vbar up, 0 if vbar down
 */
void vbarControl(int state)
{
	//Actuate the vertibar piston based on state
	SensorValue[VbarP] = state;
	//Ensure that this is actually a change
	if(state == lastState + 1)
	{
		//If so, decrement actuations for tracker
		actuationsLeft--;
	}
	//Update last state variable
	lastState = state;
}

//Governs the vertibar during Driver Control
task driverVbarTask()
{
	while(true)
	{
		//Actuate the vertibar based on the up and down buttons
		vbarControl(VBAR_UP_BTN - VBAR_DOWN_BTN);
		EndTimeSlice();
	}
}
