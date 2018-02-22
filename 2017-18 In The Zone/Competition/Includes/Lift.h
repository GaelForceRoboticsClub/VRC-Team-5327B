bool liftTooHigh()
{
	return SensorValue[LiftPotL] > LIFT_MAX;
}

bool liftTooLow()
{
	return SensorValue[LiftPotL] < LIFT_MIN;
}

void liftControl(int driverLiftAdjust)
{
	if(driverLiftAdjust == 1 && !liftTooHigh())
	{
		motor[LiftL] = 127;
	}
	else if(driverLiftAdjust == -1 && !liftTooLow())
	{
		motor[LiftL] = -127;
	}
	else
	{
		motor[LiftL] = 0;
	}
}

float kP = 0;
float kD = 0;
int target = 1500;
int error = target - SensorValue[LiftL];
int lastError = error;
int derivative = 0;
int output = 0;

task driverLiftTask()
{
	slaveMotor(LiftR, LiftL);
	while(true)
	{
		int driverLiftAdjust = LIFT_UP_BTN - LIFT_DOWN_BTN;
		if(driverLiftAdjust != 0)
		{
			liftControl(driverLiftAdjust);
			target = SensorValue[LiftL];
		}
		else
		{
			error = target - SensorValue[LiftL];
			derivative = error - lastError;
			lastError = error;
			output = error * kP + derivative * kD;
			motor[LiftL] = output;
		}
		wait1Msec(15);
	}
}
