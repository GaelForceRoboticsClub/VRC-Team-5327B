//This header file contains the necessary tasks to run the major components of the robot simultaneously during Driver Control

/*
Task that governs all code related to the base
*/
task Drive()
{
	while(true)
	{
		BaseControl(X_Joy, Y_Joy, rot_Joy);
		EndTimeSlice();
	}
}

/*
Task that governs all code related to the intake
*/
task Intaking()
{
	while(true)
	{
		IntakeControl(intakeBtn - outtakeBtn);
		ElevatorControl(elevateBtn - delevatebtn);
		EndTimeSlice();
	}
}

/*
Task that governs all code related to the launcher
*/
task Launch()
{
	while(true)
	{
		LauncherControl(launchBtn, launchAdjBk);
		EndTimeSlice();
	}
}

/*
Task that governs all code related to the angle changing
*/
task Aim()
{
	while(true)
	{
		AngleControl(0, angleUpBtn - angleDownBtn, angleLongBtn - angleShortBtn);
		EndTimeSlice();
	}
}

task EmergencyOverride()
{
	while(true)
	{
		if(overrideBtn == 1)
		{
			stopAllTasks();
			for(int i = 1; i <= 10; i++)
			{
				motor[i] = 0;
			}
			waitUntil(overrideBtn == 0);
			Always();
			startTask(Drive);
			startTask(Intaking);
			startTask(Launch);
			startTask(Aim);
			startTask(EmergencyOverride);
		}
		EndTimeSlice();
	}
}
