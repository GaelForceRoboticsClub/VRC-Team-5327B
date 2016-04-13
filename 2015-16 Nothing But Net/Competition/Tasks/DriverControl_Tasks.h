//This header file contains the necessary tasks to run the major components of the robot simultaneously during Driver Control

/*
Task that governs all code related to the base
*/
task Drive()
{
	while(true)
	{
		BaseControl(X_Joy * robotDirection, Y_Joy * robotDirection, rot_Joy, toggleSlowBtn);
		if(directionToggleBtn == 1)
		{
			robotDirection *= -1;
			SensorValue[DirectionLED] = abs(SensorValue[DirectionLED] - 1);
			waitUntil(directionToggleBtn != 1);
		}
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
		IntakeControl(intakeBtn - outtakeBtn, autoIntakeToggle);
		if(autoIntakeToggleBtn == 1)
		{
			waitUntil(autoIntakeToggleBtn == 0);
			autoIntakeToggle = !autoIntakeToggle;
		}
		EndTimeSlice();
	}
}

/*
Task that governs all code related to the AutoLoader
*/
task AutoLoading()
{
	while(true)
	{
		AutoLoadControl(autoLoadInBtn, autoLoadOutBtn);
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
		LauncherControl(launchFastBtn, 0, launchSlowBtn == 1);
		if(launchHoldToggleBtn == 1)
		{
			launchHoldToggle = !launchHoldToggle;
			waitUntil(launchHoldToggleBtn == 0);
		}
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
		if(angleShortBtn == 1 && angleSetBtn == 1) //Manually reset the desired value for short shooting, and confirm with driver
		{
			ANGLE_SHORT_RANGE = getAngle();
			playTone(500, 10);
		}
		else if(angleLongBtn == 1 && angleSetBtn == 1) //Manually reset the desired value for long shooting, and confirm with driver
		{
			ANGLE_LONG_RANGE = getAngle();
			playTone(1000, 10);
		}
		else //If no resetting is taking place, run the main control function instead
		{
			AngleControl(0, angleUpBtn - angleDownBtn, angleLongBtn - angleShortBtn);
		}
		EndTimeSlice();
	}
}

/*
Task that governs all code related to emergency stopping of the robot tasks and other code
*/
task EmergencyOverride()
{
	while(true)
	{
		if(overrideBtn == 1) //If override triggered by driver, stop only the tasks that need to be stopped (do not stop task Main()!!!)
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
			BaseControl(0, 0, 0);
			for(int i = 1; i <= 10; i++) //Reset all motors in motor array to 0
			{
				motor[i] = 0;
			}
			wait1Msec(2000); //Short 2 second delay to ensure everything has been reset
			emergenStop = false; //Restart all tasks and functions as appropriate
			Always();
			startTask(Drive);
			startTask(Intaking);
			startTask(Launch);
			startTask(Aim);
		}
		wait1Msec(1000); //Check the button only once per second, to prevent accidental rapid reset that can lead to errors
										 //in CPU timeslices
		EndTimeSlice();
	}
}

/*
Task that governs all code related to Sound Effects
*/
task SoundEffects()
{
	while(true)
	{
		if(sfxShiftBtn == 1) //If driver 1 is holding the shift button to trigger sound controls from main joystick
		{
			//Runs the corresponding sound function for each button, playing only once and stopping all sounds before it
			if(sfxJohnCenaBtn == 1)
			{
				waitUntil(sfxJohnCenaBtn == 0);
				clearSounds();
				JohnCena();
			}
			else if(sfxJeopardyBtn == 1)
			{
				waitUntil(sfxJeopardyBtn == 0);
				clearSounds();
				Jeopardy();
			}
			else if(sfxGreetingBtn == 1)
			{
				waitUntil(sfxGreetingBtn == 0);
				clearSounds();
				Greeting();
			}
			else if(sfxFriendBtn == 1)
			{
				waitUntil(sfxFriendBtn == 0);
				clearSounds();
				Friend();
			}
			else if(sfxYesBtn == 1)
			{
				waitUntil(sfxYesBtn == 0);
				clearSounds();
				Yes();
			}
			else if(sfxNoBtn == 1)
			{
				waitUntil(sfxNoBtn == 0);
				clearSounds();
				No();
			}
			else if(sfxGLBtn == 1)
			{
				waitUntil(sfxGLBtn == 0);
				clearSounds();
				GL();
			}
			else if(sfxGGBtn == 1)
			{
				waitUntil(sfxGGBtn == 0);
				clearSounds();
				GG();
			}
			else if(sfxExcuseBtn == 1)
			{
				waitUntil(sfxExcuseBtn == 0);
				clearSounds();
				Excuse();
			}
			else if(sfxOkBtn == 1)
			{
				waitUntil(sfxOkBtn == 0);
				clearSounds();
				Ok();
			}
			else if(sfxPlsBtn == 1)
			{
				waitUntil(sfxPlsBtn == 0);
				clearSounds();
				Pls();
			}
			else if(sfxThxBtn == 1)
			{
				waitUntil(sfxThxBtn == 0);
				clearSounds();
				Thx();
			}
			//Special case for "Anotha One": Since we sometimes play this while launching the preloads, we continue to play the sound
			//as long as the button is pressed via a while loop
			while(sfxAnothaOneBtn == 1)
			{
				waitUntil(!bSoundActive);
				AnothaOne();
				wait1Msec(200);
			}
			EndTimeSlice();
		}
		else if(sfxShift2Btn == 1)
		{
			if(sfxYesBtn == 1)
			{
				waitUntil(sfxYesBtn == 0);
				clearSounds();
				Yes();
			}
			else if(sfxNoBtn == 1)
			{
				waitUntil(sfxNoBtn == 0);
				clearSounds();
				No();
			}
			else if(sfxGLBtn == 1)
			{
				waitUntil(sfxGLBtn == 0);
				clearSounds();
				GL();
			}
			else if(sfxGGBtn == 1)
			{
				waitUntil(sfxGGBtn == 0);
				clearSounds();
				GG();
			}
		}
		else if(sfxAlpha2Btn == 1)
		{
			if(sfxPls2Btn == 1)
			{
				waitUntil(sfxPls2Btn == 0);
				clearSounds();
				Pls();
			}
			else if(sfxThxBtn == 1)
			{
				waitUntil(sfxThxBtn == 0);
				clearSounds();
				Thx();
			}
			else if(sfxOkBtn == 1)
			{
				waitUntil(sfxOkBtn == 0);
				clearSounds();
				Ok();
			}
			else if(sfxExcuseBtn == 1)
			{
				waitUntil(sfxExcuseBtn == 0);
				clearSounds();
				Excuse();
			}
		}
		else
		{
			if(sfxGreeting2Btn == 1)
			{
				waitUntil(sfxGreeting2Btn == 0);
				clearSounds();
				Greeting();
			}
			else if(sfxAnothaOne2Btn == 1)
			{
				waitUntil(sfxAnothaOne2Btn == 0);
				clearSounds();
				AnothaOne();
			}
			else if(sfxFriend2Btn == 1)
			{
				waitUntil(sfxFriend2Btn == 0);
				clearSounds();
				Friend();
			}
			else if(sfxJohnCenaBtn == 1)
			{
				waitUntil(sfxJohnCenaBtn == 0);
				clearSounds();
				JohnCena();
			}
		}
		EndTimeSlice();
	}
}

/*
Task that governs all code related to emergency stopping the sound effects
*/
task SFXOverride()
{
	while(true)
	{
		if(sfxEmergencyStopBtn == 1)
		{
			//Clear sound effects and play a confirmation beep, then restart
			stopTask(SoundEffects);
			clearSounds();
			playSound(soundShortBlip);
			wait1Msec(1000);
			startTask(SoundEffects);
		}
		EndTimeSlice();
	}
}

/*
Task that governs all code related to LCD
*/
task LCD()
{
	//TBD
}
