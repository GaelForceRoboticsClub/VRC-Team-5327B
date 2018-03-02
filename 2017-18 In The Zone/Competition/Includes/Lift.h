//This file contains all of the code that controls the lift of the robot

/*
 * Checks if the lift has exceeded the higher limit
 * @return : true if we are past the limit
 */
bool liftTooHigh()
{
	//Compare the potentiometer to the max value
	return SensorValue[LiftPotL] > LIFT_MAX;
}

/*
 * Checks if the lift has exceeded the lower limit
 * @return : true if we are past the limit
 */
bool liftTooLow()
{
	//Compare the potentiometer to the min value
	return SensorValue[LiftPotL] < LIFT_MIN;
}

/*
 * Moves the lift based on driver input
 * @param state : the direction in which to adjust the lift
 */
void liftControl(int driverLiftAdjust)
{
	//Confirm that we wish to go up AND haven't hit top limit
	if(driverLiftAdjust == 1 && !liftTooHigh())
	{
		//If so, lift moves up
		motor[LiftL] = 127;
	}
	//Confirm that we wish to go down AND haven't hit bottom limit
	else if(driverLiftAdjust == -1 && !liftTooLow())
	{
		//If so, lift moves down
		motor[LiftL] = -127;
	}
	//Otherwise, stop moving the lift
	else
	{
		motor[LiftL] = 0;
	}
}

//These constants control the PD loop
float kP = 2.4; //Proportional coefficient
float kD = 0.35;//Derivative coefficient

int target = 1500; //Target value for the PD loop
int error = target - SensorValue[LiftL]; //Current error
int lastError = error; //Previous error
int derivative = 0; //Calculated instantaneous derivative
int output = 0; //Final output power to the lift

//Governs the lift control during driver mode
task driverLiftTask()
{
	//Slave motors together to avoid backdriving
	slaveMotor(LiftR, LiftL);
	while(true)
	{
		//Determine how the driver wants to adjust the lift
		int driverLiftAdjust = LIFT_UP_BTN - LIFT_DOWN_BTN;
		//If the driver is actively manipulating lift
		if(driverLiftAdjust != 0)
		{
			//Adjust the lift
			liftControl(driverLiftAdjust);
			//Correspondingly update target value to current sensor
			target = SensorValue[LiftL];
		}
		//Otherwise, "hold" the lift at the previous height
		else
		{
			//Determine what the error is
			error = target - SensorValue[LiftL];
			//Determine how fast the error is changing
			derivative = error - lastError;
			//Update last error
			lastError = error;
			//Determine output by combining the two PD components
			output = error * kP + derivative * kD;
			//Assign value to the motors
			motor[LiftL] = output;
		}
		//Timed delay to ensure that derivative is calculated properly
		wait1Msec(15);
	}
}
