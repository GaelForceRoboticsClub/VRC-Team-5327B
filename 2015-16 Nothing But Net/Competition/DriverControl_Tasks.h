//This header file contains the necessary tasks to run the major components of the robot simultaneously during Driver Control

/*
Task that governs all code related to the base
*/
task Drive()
{
	while(true)
	{
		BaseControl(X_Joy, Y_Joy, rot_Joy, toggleSlowBtn);
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
		if(intakeModifierBtn == 1)
		{
			IntakeControl(inBtn - outBtn);
		}
		else if(outtakeModifierBtn == 1)
		{
			ElevatorControl(inBtn - outBtn);
		}
		else
		{
			IntakeControl(inBtn - outBtn);
			ElevatorControl(inBtn - outBtn);
		}
		autoLoad();
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
		LauncherControl(0, launchFast, launchSlow);
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
		clearLCDLine(0);
		setLCDPosition(0, 0);
		displayNextLCDString("AngleValue: ");
		displayNextLCDNumber(getAngle());
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
			stopTask(Drive);
			stopTask(Intaking);
			stopTask(Launch);
			stopTask(Aim);
			emergenStop = true;
			stopAlways();
			AngleControl(0);
			LauncherControl(0);
			IntakeControl(0);
			ElevatorControl(0);
			BaseControl(0, 0, 0);
			for(int i = 1; i <= 10; i++)
			{
				motor[i] = 0;
			}
			wait1Msec(2000);
			emergenStop = false;
			Always();
			startTask(Drive);
			startTask(Intaking);
			startTask(Launch);
			startTask(Aim);
		}
		wait1Msec(1000);
		EndTimeSlice();
	}
}
