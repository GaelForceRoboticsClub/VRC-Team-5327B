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
		LauncherControl(launchBtn, launchAdj);
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
		AngleControl(0, angleUpBtn - angleDownBtn);
		EndTimeSlice();
	}
}
