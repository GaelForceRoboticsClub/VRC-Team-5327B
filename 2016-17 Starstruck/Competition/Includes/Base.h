//This header file contains all of the code necessary to run the base during the match

enum slewSides {
	RIGHT_SLEW = 0,
	LEFT_SLEW = 1
};

int baseSlew[] = { 0, 0 };

/*
Function enabling TrueSpeed control, allowing for linear motion despite the motor power curve.
Takes the following inputs:
 - @rawValue : The desired lookup value
Returns the following outputs:
 - @return : The corresponding TrueSpeed scaled value
*/
int trueSpeed(int rawValue){
	int newRawValue = rawValue >= 127 ? 127 : rawValue <= -127 ? -127 : rawValue; //Ensure value is within bounds
	return (newRawValue > 0 ? 1 : -1) * TS_ARRAY[abs(newRawValue)]; //Return correctly scaled and signed value
}

/*
Function controlling the base.
Takes the following inputs:
 - @L_speed	: The speed at which to turn the left side of the base
 - @R_speed	: The speed at which to turn the right side of the base
Has no outputs.
*/
void driverBaseControl(int rSpeed, int lSpeed)
{
	baseSlew[RIGHT_SLEW] = trueSpeed(rSpeed);
	baseSlew[LEFT_SLEW] = trueSpeed(lSpeed);
}

/*
Task controlling user-controlled base.
*/
task base()
{
	while(true)
	{
		driverBaseControl(RBase, LBase);
		EndTimeSlice();
	}
}

task baseSlewControl()
{
	while(true)
	{
		if(abs(motor[RFBase] - baseSlew[RIGHT_SLEW]) > SLEW_RATE_INCREMENT)
		{
			motor[RFBase] += SLEW_RATE_INCREMENT * sgn(baseSlew[RIGHT_SLEW] - motor[RFBase]);
		}
		else
		{
			motor[RFBase] = baseSlew[RIGHT_SLEW];
		}
		if(abs(motor[LFBase] - baseSlew[LEFT_SLEW]) > SLEW_RATE_INCREMENT)
		{
			motor[LFBase] += SLEW_RATE_INCREMENT * sgn(baseSlew[LEFT_SLEW] - motor[LFBase]);
		}
		else
		{
			motor[LFBase] = baseSlew[LEFT_SLEW];
		}
		wait1Msec(SLEW_RATE_WAIT);
	}
}
