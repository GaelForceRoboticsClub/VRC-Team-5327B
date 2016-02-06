//This header file contains the necessary tasks to run the major components of the robot simultaneously at ALL TIMES

/*
Task that governs the continuous management of the ball entry and exit during autonomous and driver periods
*/

task ballCounter()
{
	while(true)
	{
		TurnstileControl();
		EndTimeSlice();
	}
}

void Always()
{
	startTask(ballCounter);
}

void stopAlways()
{
	stopTask(ballCounter);
}
