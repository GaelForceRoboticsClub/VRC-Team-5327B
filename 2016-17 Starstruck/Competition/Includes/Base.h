//This header file contains all of the code necessary to run the base during the match

/*
Function controlling the base.
Takes the following inputs:
 - @L_speed	: The speed at which to turn the left side of the base
 - @R_speed	: The speed at which to turn the right side of the base
Has no outputs.
*/
void driverBaseControl(int R_speed, int L_speed)
{
	motor[RFBase]= trueSpeed(R_speed);
	motor[LFBase] = trueSpeed(L_speed);
}

/*
Task controlling user-controlled base.
*/
task base()
{
	while(true)
	{
		driverBaseControl(R_Base, L_Base);
		EndTimeSlice();
	}
}
