//This header file contains all of the code necessary to run the base during the match

/*
Function controlling the base.
Takes the following inputs:
 - @L_speed : The speed at which to turn the left side of the base
 - @R_speed : The speed at which to turn the right side of the base
Has no outputs.
*/
void driverBaseControl(int L_speed, int R_speed)
{
	motor[LFBase] = trueSpeed(L_speed);
	motor[RFBase]= trueSpeed(R_speed);
}

/*
Task controlling user-controlled base.
*/
task base()
{
	while(true)
	{
		driverBaseControl(L_Joy, R_Joy);
		EndTimeSlice();
	}
}

task sfx()
{
	while(true)
	{
		if(vexRT[Btn7L] == 1)
		{
			playSoundFile("John so.wav");
			waitUntil(vexRT[Btn7L] == 0);
		}
		else if(vexRT[Btn7R] == 1)
		{
			playSoundFile("Yaya.wav");
			waitUntil(vexRT[Btn7R] == 0);
		}
		if(vexRT[Btn7D] == 1)
		{
			clearSounds();
			waitUntil(vexRT[Btn7D] == 0);
		}
		EndTimeSlice();
	}
}
