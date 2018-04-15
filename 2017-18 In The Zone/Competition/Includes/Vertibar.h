//This file contains all of the code to control the vertibar of the robot

/*
 * Checks if the lift has exceeded the higher limit
 * @return : true if we are past the limit
 */
bool vbarTooUp()
{
	//Compare the potentiometer to the max value
	return SensorValue[VbarPot] > VBAR_MAX;
}

/*
 * Checks if the lift has exceeded the lower limit
 * @return : true if we are past the limit
 */
bool vbarTooDown()
{
	//Compare the potentiometer to the min value
	return SensorValue[VbarPot] < VBAR_MIN;
}

/*
 * Moves the lift based on driver input
 * @param state : the direction in which to adjust the lift
 */
void vbarControl(int driverVbarAdjust)
{
	//Confirm that we wish to go up AND haven't hit top limit
	if(driverVbarAdjust == 1 && !vbarTooUp())
	{
		//If so, lift moves up
		motor[VbarL] = 127;
	}
	//Confirm that we wish to go down AND haven't hit bottom limit
	else if(driverVbarAdjust == -1 && !vbarTooDown())
	{
		//If so, lift moves down
		motor[VbarL] = -127;
	}
	//Otherwise, stop moving the lift
	else
	{
		motor[VbarL] = 0;
	}
}

//Governs the vertibar during Driver Control
float kP = 2.4; //Proportional coefficient
float kD = 0.35;//Derivative coefficient

int target = 1500; //Target value for the PD loop
int error = target - SensorValue[VbarPot]; //Current error
int lastError = error; //Previous error
int derivative = 0; //Calculated instantaneous derivative
int output = 0; //Final output power to the lift

task driverVbarTask()
{
	slaveMotor(VbarR, VbarL);
	while(true)
	{
		//Determine how the driver wants to adjust the lift
		int driverVbarAdjust = VBAR_UP_ADJ_BTN - VBAR_DOWN_ADJ_BTN;
		int driverVbarSet = VBAR_UP_BTN - VBAR_DOWN_BTN;
		//If the driver is actively manipulating lift
		if(driverVbarAdjust != 0)
		{
			//Adjust the lift
			vbarControl(driverVbarAdjust);
			//Correspondingly update target value to current sensor
			target = SensorValue[VbarPot];
		}
		//Otherwise, "hold" the lift at the previous height
		else
		{
			if(driverVbarSet == 1)
			{
				target = VBAR_UP;
			}
			else if(driverVbarSet == -1)
			{
				target = VBAR_DOWN;
			}
			//Determine what the error is
			error = target - SensorValue[VbarPot];
			//Determine how fast the error is changing
			derivative = error - lastError;
			//Update last error
			lastError = error;
			//Determine output by combining the two PD components
			output = error * kP + derivative * kD;
			//Assign value to the motors
			motor[VbarL] = output;
		}
		//Timed delay to ensure that derivative is calculated properly
		wait1Msec(15);
	}
}
