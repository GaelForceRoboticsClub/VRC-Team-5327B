//This file contains all of the code that controls the lift of the robot

/*
 * Checks if the lift has exceeded the higher limit
 * @return : true if we are past the limit
 */
bool mogoTooOut()
{
	//Compare the potentiometer to the max value
	return SensorValue[MogoPot] > MOGO_MAX;
}

/*
 * Checks if the lift has exceeded the lower limit
 * @return : true if we are past the limit
 */
bool mogoTooIn()
{
	//Compare the potentiometer to the min value
	return SensorValue[MogoPot] < MOGO_MIN;
}

/*
 * Moves the lift based on driver input
 * @param state : the direction in which to adjust the lift
 */
void mogoControl(int driverMogoAdjust)
{
	//Confirm that we wish to go up AND haven't hit top limit
	if(driverMogoAdjust == 1 && !mogoTooOut())
	{
		//If so, lift moves up
		motor[MogoM] = 127;
	}
	//Confirm that we wish to go down AND haven't hit bottom limit
	else if(driverMogoAdjust == -1 && !mogoTooIn())
	{
		//If so, lift moves down
		motor[MogoM] = -127;
	}
	//Otherwise, stop moving the lift
	else
	{
		motor[MogoM] = 0;
	}
}

//These constants control the PD loop
float mogokP = 0; //Proportional coefficient
float mogokD = 0;//Derivative coefficient

int mogoTarget = 1500; //Target value for the PD loop
int mogoError = mogoTarget - SensorValue[MogoPot]; //Current error
int mogoLastError = mogoError; //Previous error
int mogoDerivative = 0; //Calculated instantaneous derivative
int mogoOutput = 0; //Final output power to the lift

//Governs the lift control during driver mode
task driverMogoTask()
{
	int lastToggle = 0;
	while(true)
	{
		//Determine how the driver wants to adjust the lift
		int driverMogoAdjust = MOGO_OUT_ADJ_BTN - MOGO_IN_ADJ_BTN;
		int driverMogoToggle = MOGO_TOGGLE_BTN;
		//If the driver is actively manipulating lift
		if(driverMogoAdjust != 0)
		{
			//Adjust the lift
			mogoControl(driverMogoAdjust);
			//Correspondingly update target value to current sensor
			mogoTarget = SensorValue[MogoPot];
		}
		//Otherwise, "hold" the lift at the previous height
		else
		{
			if(driverMogoToggle == lastToggle + 1)
			{
				if(abs(SensorValue[MogoPot] - MOGO_MAX) < abs(SensorValue[MogoPot] - MOGO_MIN))
				{
					mogoTarget = MOGO_MIN;
				}
				else
				{
					mogoTarget = MOGO_MAX;
				}
			}
			lastToggle = driverMogoToggle;
			//Determine what the error is
			mogoError = mogoTarget - SensorValue[MogoPot];
			//Determine how fast the error is changing
			mogoDerivative = mogoError - mogoLastError;
			//Update last error
			mogoLastError = mogoError;
			//Determine output by combining the two PD components
			mogoOutput = mogoError * mogokP + mogoDerivative * mogokD;
			//Assign value to the motors
			motor[MogoM] = mogoOutput;
		}
		//Timed delay to ensure that derivative is calculated properly
		wait1Msec(15);
	}
}
