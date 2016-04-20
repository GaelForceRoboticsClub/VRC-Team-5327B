//This header file contains the necessary functions to be run throughout the competition


/*
Function governing the movement of the base. Takes 4 parameters:
@X_comp : How much we want to strafe
@Y_comp : How much we want to drive forwards/backwards
@rot_comp : How much we want to rotate the robot CW/CCW
@duration : How long to drive
*/
void BaseControl(int X_comp, int Y_comp, int rot_comp, int slow = 0, int duration = LOOP_DELAY)
{
	/*
	Assuming the following control scheme:
	X-Drive Base, where all motors drive forward when set to 127
	X and Y are as they are defined in the Cartesian coordinate plane
	Rotation is positive for CW, negative for CCW
	*/
	rot_comp = rot_comp * (1 - (0.75 * slow));
	motor[RFBase] = Y_comp - X_comp - rot_comp;
	motor[LFBase] = Y_comp + X_comp + rot_comp;
	motor[RBBase] = Y_comp + X_comp - rot_comp;
	motor[LBBase] = Y_comp - X_comp + rot_comp;
}


/*
Function governing that resets the launcher to the sensor. Takes no parameters.
*/
void setLauncher()
{
	if(SensorValue[LauncherSet] == 1)
	{
		motor[Out1] = LAUNCHER_HOLD;
	}
	else
	{
		while(SensorValue[LauncherSet] == 0)
		{
			motor[Out1] = 127;
		}
		motor[Out1] = LAUNCHER_HOLD;
	}
}

/*
Function governing the launcher firing. Takes 2 paramters:
@ballNumber : The number of balls to be fired
@shotDelay : How long to wait between each shot (default 100)
*/
void launch(int ballNumber, int shotDelay = 100)
{
	while(ballNumber > 0)
	{
		setLauncher();
		while(SensorValue[LauncherSet] == 1)
		{
			motor[Out1] = 127;
		}
		ballNumber--;
		wait1Msec(shotDelay);
	}
}

void DLaunch(int direction, bool slow = false)
{
	if(direction != 0)
	{
		if(slow)
		{
			motor[Out1] = LAUNCHER_SLOW_SPEED * direction;
		}
		else
		{
			motor[Out1] = 127 * direction;
		}
	}
	else
	{
		motor[Out1] = LAUNCHER_HOLD;
	}
}


/*
Function governing the launcher angle. Takes 3 parameters:
@auto_angle : automatic angle setting we wish to use
@angle_adjust : direction in which to change the angle
@absolute_angle : absolute angle we wish the launcher to be at
*/
void AngleControl(int auto_angle, int angle_adjust = 0, int absolute_angle = 0)
{
	if(angle_adjust == 1 && !emergenStop)
	{
		motor[Angle] = ANGLE_ADJUST_SPEED_UP;
	}
	else if(angle_adjust == -1 && !emergenStop && SensorValue[LauncherBottomLimit] == 0)
	{
		motor[Angle] = -ANGLE_ADJUST_SPEED_DOWN;
	}
	else
	{
		motor[Angle] = ANGLE_HOLD;
	}
	if(SensorValue[LauncherBottomLimit] == 1)
	{
		playSound(soundBlip);
	}
}


/*
Function governing the intake system. Takes 2 parameters:
@direction : whether to intake or outtake balls
@autoIntakeOn : whether we should enable automatic ball sensing and intaking
*/
void IntakeControl(int direction, bool autoIntakeOn = false)
{
	if(autoIntakeOn)
	{
		if((SensorValue[BallFinder1] - SensorValue[BallFinder2]) < 2 && getUltras() > 5) //If we see the ball straight ahead
		{
			BaseControl(0, 127, 0);
		}
		else if(SensorValue[BallFinder1] > SensorValue[BallFinder2] + 2) //If we see the ball more on the right
		{
			BaseControl(63, 63, 0);
		}
		else if(SensorValue[BallFinder2] > SensorValue[BallFinder1] + 2) //If we see the ball more on the left
		{
			BaseControl(-63, 63, 0);
		}
		else //If we don't see the ball
		{
			//Do nothing, we let the driver control intake and base now
		}
		if(getUltras() < 8) //If we are close enough, turn the intake on
		{
			IntakeControl(1);
		}
	}
	else
	{
		motor[Intake] = 127 * direction;
		while(elevatorOn && ballInRamp() != 1 && direction == 0)
		{
			motor[Elevator] = -127;
		}
		motor[Elevator] = 127 * direction;
	}
}

/*
Function governing the autoloading system. Takes 2 parameters:
@overrideIn : override autoloading in
@overrideOut : override autoloading out
*/
void AutoLoadControl(int overrideIn, int overrideOut)
{
	if(overrideIn == 0 && overrideOut == 0)
	{
		if(ballInElevator() == 1)
		{
			if(ballInRamp() == 1)
			{
				if(ballInLauncher() == 1)
				{
					if(ballLauncherReady() == 1)
					{
						//Everything is full, so repel balls
						elevatorOn = false;
						motor[AutoLoader] = -127;
					}
					else
					{
						//Everything is full, so do nothing
						elevatorOn = false;
						motor[AutoLoader] = -127;
					}
				}
				else
				{
					if(ballLauncherReady() == 1)
					{
						//Launcher is empty and ready
						motor[AutoLoader] = 127;
						//Bring in next ball
						elevatorOn = true;
					}
					else
					{
						//Launcher not ready, so repel balls
						motor[AutoLoader] = -127;
						elevatorOn = false;
					}
				}
			}
			else
			{
				if(ballInLauncher() == 1)
				{
					if(ballLauncherReady() == 1)
					{
						//Ramp is empty, so bring up from elevator
						elevatorOn = true;
						motor[AutoLoader] = 0;
					}
					else
					{
						//Ramp is empty, so bring up from elevator
						elevatorOn = true;
						motor[AutoLoader] = 0;
					}
				}
				else
				{
					if(ballLauncherReady() == 1)
					{
						//Launcher is empty and ready
						motor[AutoLoader] = 127;
						//Bring in next ball
						elevatorOn = true;
					}
					else
					{
						//Ramp is empty, so bring up from elevator
						elevatorOn = true;
						motor[AutoLoader] = 0;
					}
				}
			}
		}
		else
		{
			if(ballInRamp() == 1)
			{
				if(ballInLauncher() == 1)
				{
					if(ballLauncherReady() == 1)
					{
						//Pushed all the way up so repel balls
						motor[AutoLoader] = -127;
						elevatorOn = false;
					}
					else
					{
						//Pushed all the way up so repel balls
						motor[AutoLoader] = -127;
						elevatorOn = false;
					}
				}
				else
				{
					if(ballLauncherReady() == 1)
					{
						//Launcher is empty and ready
						motor[AutoLoader] = 127;
						//Bring in next ball
						elevatorOn = false;
					}
					else
					{
						//Launcher not ready, so repel balls
						motor[AutoLoader] = -127;
						elevatorOn = false;
					}
				}
			}
			else
			{
				if(ballInLauncher() == 1)
				{
					if(ballLauncherReady() == 1)
					{
						//Everything has been pushed forward, so do nothing
						motor[AutoLoader] = 0;
						elevatorOn = false;
					}
					else
					{
						//Everything has been pushed forward, so do nothing
						motor[AutoLoader] = 0;
						elevatorOn = false;
					}
				}
				else
				{
					if(ballLauncherReady() == 1)
					{
						//Launcher is empty and ready
						motor[AutoLoader] = 0;
						//Bring in next ball
						elevatorOn = false;
					}
					else
					{
						//Launcher not ready, so do nothing
						motor[AutoLoader] = 0;
						elevatorOn = false;
					}
				}
			}
		}
	}
	else
	{
		motor[AutoLoader] = 127 * (overrideIn - overrideOut);
	}
}

/*
Possible context level 0: On, Off
Possible context level 1: Auton, Battery
Possible context level 2: Close Red, Far Red, Close Blue, Far Blue
Possible context level 3: Whatever the autons are
*/
string context[4] = {"Off", "Null", "Null", "Null"};
int cursor = 0;
string autonToRun = "";
string lastSoundPlayed[5] = {"Off", "Null", "Null", "Null", "Null"};
int click = 0;

void LCDControl(int buttons, int wheelCursor, int wheelButton)
{
	clearLCDLine(0);
	clearLCDLine(1);
	cursor = wheelCursor;
	if(buttons == 1) //Left Button
	{
		if(context[0] == "On")
		{
			context[1] = "Auton";
			context[2] = "Null";
			context[3] = "Null";
			autonToRun = "";
			lastSoundPlayed[1] = "Null";
			lastSoundPlayed[2] = "Null";
			lastSoundPlayed[3] = "Null";
			lastSoundPlayed[4] = "Null";
			click = 0;
		}
	}
	else if(buttons == 2) //Center Button
	{
		if(context[0] == "Off")
		{
			context[0] = "On";
			context[1] = "Auton";
			context[2] = "Null";
			context[3] = "Null";
		}
		else
		{
			context[0] = "Off";
			context[1] = "Null";
			context[2] = "Null";
			context[3] = "Null";
		}
	}
	else if(buttons == 4) //Right Button
	{
		if(context[0] == "On")
		{
			context[1] = "Battery";
			context[2] = "Null";
			context[3] = "Null";
		}
	}
	if(context[1] == "Auton" && context[2] == "Null" && wheelButton == 1)
	{
		if(cursor < 1024)
		{
			context[2] = "Red Far";
			context[3] = "Null";
		}
		else if (cursor < 2048)
		{
			context[2] = "Red Close";
			context[3] = "Null";
		}
		else if (cursor < 3072)
		{
			context[2] = "Blue Far";
			context[3] = "Null";
		}
		else
		{
			context[2] = "Blue Close";
			context[3] = "Null";
		}
		wheelButton = 0;
	}
	if(context[2] == "Red Far" && context[3] == "Null" && wheelButton == 1)
	{
		if(cursor < 1024)
		{
			context[3] = 0;
		}
		else if (cursor < 2048)
		{
			context[3] = 1;
		}
		else if (cursor < 3072)
		{
			context[3] = 2;
		}
		else
		{
			context[3] = 3;
		}
	}
	else if(context[2] == "Red Close" && context[3] == "Null" && wheelButton == 1)
	{
		if(cursor < 1024)
		{
			context[3] = 4;
		}
		else if (cursor < 2048)
		{
			context[3] = 5;
		}
		else if (cursor < 3072)
		{
			context[3] = 6;
		}
		else
		{
			context[3] = 7;
		}
	}
	else if(context[2] == "Blue Far" && context[3] == "Null" && wheelButton == 1)
	{
		if(cursor < 1024)
		{
			context[3] = 8;
		}
		else if (cursor < 2048)
		{
			context[3] = 9;
		}
		else if (cursor < 3072)
		{
			context[3] = 10;
		}
		else
		{
			context[3] = 11;
		}
	}
	else if(context[2] == "Blue Close" && context[3] == "Null" && wheelButton == 1)
	{
		if(cursor < 1024)
		{
			context[3] = 12;
		}
		else if (cursor < 2048)
		{
			context[3] = 13;
		}
		else if (cursor < 3072)
		{
			context[3] = 14;
		}
		else
		{
			context[3] = 15;
		}
	}
	autonToRun = context[3];
	if(context[3] != "Null")
	{
		lastSoundPlayed[4] = "Selected";
	}
}

void LCDDisplay()
{
	string line0 = "";
	string line1 = "";
	//Check context level 0 (on/off)
	if(context[0] == "Off")
	{
		bLCDBacklight = false;
		if(lastSoundPlayed[0] != "Off")
		{
			playSound(soundDownwardTones);
			lastSoundPlayed[0] = "Off";
			lastSoundPlayed[1] = "Null";
			lastSoundPlayed[2] = "Null";
			lastSoundPlayed[3] = "Null";
			lastSoundPlayed[4] = "Null";
			click = 0;
		}
	}
	else if(context[0] == "On")
	{
		bLCDBacklight = true;
		line1 = "Auton  I/O  Batt";
		if(lastSoundPlayed[0] != "On")
		{
			lastSoundPlayed[0] = "On";
			playSound(soundFastUpwardTones);
		}
	}
	//Check context level 1 (battery / auton)
	if(context[1] == "Auton")
	{
		if(cursor < 1024)
		{
			line0 = "Red Far";
			if(lastSoundPlayed[0] == "On" && lastSoundPlayed[1] != "RF" && lastSoundPlayed[2] == "Null" && lastSoundPlayed[3] == "Null" && lastSoundPlayed[4] == "Null")
			{
				lastSoundPlayed[1] = "RF";
				playSound(soundShortBlip);
			}
		}
		else if (cursor < 2048)
		{
			line0 = "Red Close";
			if(lastSoundPlayed[0] == "On" && lastSoundPlayed[1] != "RC" && lastSoundPlayed[2] == "Null" && lastSoundPlayed[3] == "Null" && lastSoundPlayed[4] == "Null")
			{
				lastSoundPlayed[1] = "RC";
				playSound(soundShortBlip);
			}
		}
		else if (cursor < 3072)
		{
			line0 = "Blue Far";
			if(lastSoundPlayed[0] == "On" && lastSoundPlayed[1] != "BF" && lastSoundPlayed[2] == "Null" && lastSoundPlayed[3] == "Null" && lastSoundPlayed[4] == "Null")
			{
				lastSoundPlayed[1] = "BF";
				playSound(soundShortBlip);
			}
		}
		else
		{
			line0 = "Blue Close";
			if(lastSoundPlayed[0] == "On" && lastSoundPlayed[1] != "BC" && lastSoundPlayed[2] == "Null" && lastSoundPlayed[3] == "Null" && lastSoundPlayed[4] == "Null")
			{
				lastSoundPlayed[1] = "BC";
				playSound(soundShortBlip);
			}
		}
	}
	else if(context[1] == "Battery")
	{
		sprintf(line0, "%s%1.1f%c%s%1.1f%c", "M: ", nImmediateBatteryLevel / 1000.0, 'V', "  S: ", BackupBatteryLevel / 1000.0, 'V');
	}
	if (context[2] == "Red Far")
	{
		if(cursor < 1024)
		{
			line0 = "RFAuto1";
			if(lastSoundPlayed[0] == "On" && lastSoundPlayed[1] == "RF" && lastSoundPlayed[2] != "RF1" &&  lastSoundPlayed[3] == "Null" && lastSoundPlayed[4] == "Null")
			{
				lastSoundPlayed[2] = "RF1";
				playSound(soundShortBlip);
			}
		}
		else if (cursor < 2048)
		{
			line0 = "RFAuto2";
			if(lastSoundPlayed[0] == "On" && lastSoundPlayed[1] == "RF" && lastSoundPlayed[2] != "RF2" &&  lastSoundPlayed[3] == "Null" && lastSoundPlayed[4] == "Null")
			{
				lastSoundPlayed[2] = "RF2";
				playSound(soundShortBlip);
			}
		}
		else if (cursor < 3072)
		{
			line0 = "RFAuto3";
			if(lastSoundPlayed[0] == "On" && lastSoundPlayed[1] == "RF" && lastSoundPlayed[2] != "RF3" &&  lastSoundPlayed[3] == "Null" && lastSoundPlayed[4] == "Null")
			{
				lastSoundPlayed[2] = "RF3";
				playSound(soundShortBlip);
			}
		}
		else
		{
			line0 = "RFAuto4";
			if(lastSoundPlayed[0] == "On" && lastSoundPlayed[1] == "RF" && lastSoundPlayed[2] != "RF4" &&  lastSoundPlayed[3] == "Null" && lastSoundPlayed[4] == "Null")
			{
				lastSoundPlayed[2] = "RF4";
				playSound(soundShortBlip);
			}
		}
	}
	else if (context[2] == "Red Close")
	{
		if(cursor < 1024)
		{
			line0 = "RCAuto1";
			if(lastSoundPlayed[0] == "On" && lastSoundPlayed[1] == "RC" && lastSoundPlayed[2] != "RC1" &&  lastSoundPlayed[3] == "Null" && lastSoundPlayed[4] == "Null")
			{
				lastSoundPlayed[2] = "RC1";
				playSound(soundShortBlip);
			}
		}
		else if (cursor < 2048)
		{
			line0 = "RCAuto2";
			if(lastSoundPlayed[0] == "On" && lastSoundPlayed[1] == "RC" && lastSoundPlayed[2] != "RC2" &&  lastSoundPlayed[3] == "Null" && lastSoundPlayed[4] == "Null")
			{
				lastSoundPlayed[2] = "RC2";
				playSound(soundShortBlip);
			}
		}
		else if (cursor < 3072)
		{
			line0 = "RCAuto3";
			if(lastSoundPlayed[0] == "On" && lastSoundPlayed[1] == "RC" && lastSoundPlayed[2] != "RC3" &&  lastSoundPlayed[3] == "Null" && lastSoundPlayed[4] == "Null")
			{
				lastSoundPlayed[2] = "RC3";
				playSound(soundShortBlip);
			}
		}
		else
		{
			line0 = "RCAuto4";
			if(lastSoundPlayed[0] == "On" && lastSoundPlayed[1] == "RC" && lastSoundPlayed[2] != "RC4" &&  lastSoundPlayed[3] == "Null" && lastSoundPlayed[4] == "Null")
			{
				lastSoundPlayed[2] = "RC4";
				playSound(soundShortBlip);
			}
		}
	}
	else if (context[2] == "Blue Far")
	{
		if(cursor < 1024)
		{
			line0 = "BFAuto1";
			if(lastSoundPlayed[0] == "On" && lastSoundPlayed[1] == "BF" && lastSoundPlayed[2] != "BF1" &&  lastSoundPlayed[3] == "Null" && lastSoundPlayed[4] == "Null")
			{
				lastSoundPlayed[2] = "BF1";
				playSound(soundShortBlip);
			}
		}
		else if (cursor < 2048)
		{
			line0 = "BFAuto2";
			if(lastSoundPlayed[0] == "On" && lastSoundPlayed[1] == "BF" && lastSoundPlayed[2] != "BF2" &&  lastSoundPlayed[3] == "Null" && lastSoundPlayed[4] == "Null")
			{
				lastSoundPlayed[2] = "BF2";
				playSound(soundShortBlip);
			}
		}
		else if (cursor < 3072)
		{
			line0 = "BFAuto3";
			if(lastSoundPlayed[0] == "On" && lastSoundPlayed[1] == "BF" && lastSoundPlayed[2] != "BF3" &&  lastSoundPlayed[3] == "Null" && lastSoundPlayed[4] == "Null")
			{
				lastSoundPlayed[2] = "BF3";
				playSound(soundShortBlip);
			}
		}
		else
		{
			line0 = "BFAuto4";
			if(lastSoundPlayed[0] == "On" && lastSoundPlayed[1] == "BF" && lastSoundPlayed[2] != "BF4" &&  lastSoundPlayed[3] == "Null" && lastSoundPlayed[4] == "Null")
			{
				lastSoundPlayed[2] = "BF4";
				playSound(soundShortBlip);
			}
		}
	}
	else if (context[2] == "Blue Close")
	{
		if(cursor < 1024)
		{
			line0 = "BCAuto1";
			if(lastSoundPlayed[0] == "On" && lastSoundPlayed[1] == "BC" && lastSoundPlayed[2] != "BC1" &&  lastSoundPlayed[3] == "Null" && lastSoundPlayed[4] == "Null")
			{
				lastSoundPlayed[2] = "BC1";
				playSound(soundShortBlip);
			}
		}
		else if (cursor < 2048)
		{
			line0 = "BCAuto2";
			if(lastSoundPlayed[0] == "On" && lastSoundPlayed[1] == "BC" && lastSoundPlayed[2] != "BC2" &&  lastSoundPlayed[3] == "Null" && lastSoundPlayed[4] == "Null")
			{
				lastSoundPlayed[2] = "BC2";
				playSound(soundShortBlip);
			}
		}
		else if (cursor < 3072)
		{
			line0 = "BCAuto3";
			if(lastSoundPlayed[0] == "On" && lastSoundPlayed[1] == "BC" && lastSoundPlayed[2] != "BC3" &&  lastSoundPlayed[3] == "Null" && lastSoundPlayed[4] == "Null")
			{
				lastSoundPlayed[2] = "BC3";
				playSound(soundShortBlip);
			}
		}
		else
		{
			line0 = "BCAuto4";
			if(lastSoundPlayed[0] == "On" && lastSoundPlayed[1] == "BC" && lastSoundPlayed[2] != "BC4" &&  lastSoundPlayed[3] == "Null" && lastSoundPlayed[4] == "Null")
			{
				lastSoundPlayed[2] = "BC4";
				playSound(soundShortBlip);
			}
		}
	}
	if (context[3] != "Null")
	{
		int leftbuffer = (16 - strlen(line0)) / 2;
		int rightbuffer = round((16 - strlen(line0)) / 2.0);
		const string routineNames[] = {
			"RFAuto1",
			"RFAuto2",
			"RFAuto3",
			"RFAuto4",
			"RCAuto1",
			"RCAuto2",
			"RCAuto3",
			"RCAuto4",
			"BFAuto1",
			"BFAuto2",
			"BFAuto3",
			"BFAuto4",
			"BCAuto1",
			"BCAuto2",
			"BCAuto3",
			"BCAuto4"
		};
		string prevLine0 = routineNames[context[3]];
		line0 = "";
		for(int i = 0; i < leftbuffer; i++)
		{
			line0 += "$";
		}
		line0 += prevLine0;
		for(int i = 0; i < rightbuffer; i++)
		{
			line0 += "$";
		}
	}
	displayLCDCenteredString(0, line0);
	displayLCDCenteredString(1, line1);
	if(SensorValue[CursorClick] == 1 && lastSoundPlayed[0] == "On" && click < 2)
	{
		playSound(soundBeepBeep);
		click++;
	}
	waitUntil(nLCDButtons == 0);
	waitUntil(SensorValue[CursorClick] == 0);
}
