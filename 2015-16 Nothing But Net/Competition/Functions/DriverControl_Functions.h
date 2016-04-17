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
Function governing the launcher firing. Takes 3 parameters:
@direction : Direction in which to fire
@duration : How long to fire
@slow : Whether we should shoot slow
*/
void LauncherControl(int direction, int duration = 500, bool slow = false)
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
		wait1Msec(duration);
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
		else if (cursor < 3071)
		{
			context[2] = "Blue Far";
			context[3] = "Null";
		}
		else
		{
			context[2] = "Blue Close";
			context[3] = "Null";
		}
	}
	if(context[2] == "Red Far" && context[3] == "Null" && wheelButton == 1)
	{
		if(cursor < 1024)
		{
			context[3] = "RFAuto1";
		}
		else if (cursor < 2048)
		{
			context[3] = "RFAuto2";
		}
		else if (cursor < 3071)
		{
			context[3] = "RFAuto3";
		}
		else
		{
			context[3] = "RFAuto4";
		}
	}
	else if(context[2] == "Red Close" && context[3] == "Null" && wheelButton == 1)
	{
		if(cursor < 1024)
		{
			context[3] = "RCAuto1";
		}
		else if (cursor < 2048)
		{
			context[3] = "RCAuto2";
		}
		else if (cursor < 3071)
		{
			context[3] = "RCAuto3";
		}
		else
		{
			context[3] = "RCAuto4";
		}
	}
	else if(context[2] == "Blue Far" && context[3] == "Null" && wheelButton == 1)
	{
		if(cursor < 1024)
		{
			context[3] = "BFAuto1";
		}
		else if (cursor < 2048)
		{
			context[3] = "BFAuto2";
		}
		else if (cursor < 3071)
		{
			context[3] = "BFAuto3";
		}
		else
		{
			context[3] = "BFAuto4";
		}
	}
	else if(context[2] == "Blue Close" && context[3] == "Null" && wheelButton == 1)
	{
		if(cursor < 1024)
		{
			context[3] = "BCAuto1";
		}
		else if (cursor < 2048)
		{
			context[3] = "BCAuto2";
		}
		else if (cursor < 3071)
		{
			context[3] = "BCAuto3";
		}
		else
		{
			context[3] = "BCAuto4";
		}
	}
	autonToRun = context[3];
}
void LCDDisplay()
{
	string line0 = "";
	string line1 = "";
	//Check context level 0 (on/off)
	if(context[0] == "Off")
	{
		bLCDBacklight = false;
	}
	else if(context[0] == "On")
	{
		bLCDBacklight = true;
		line1 = "Auton  I/O  Batt";
	}
	//Check context level 1 (battery / auton)
	if(context[1] == "Auton")
	{
		if(cursor < 1024)
		{
			line0 = "Red Far";
		}
		else if (cursor < 2048)
		{
			line0 = "Red Close";
		}
		else if (cursor < 3071)
		{
			line0 = "Blue Far";
		}
		else
		{
			line0 = "Blue Close";
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
		}
		else if (cursor < 2048)
		{
			line0 = "RFAuto2";
		}
		else if (cursor < 3071)
		{
			line0 = "RFAuto3";
		}
		else
		{
			line0 = "RFAuto4";
		}
	}
	else if (context[2] == "Red Close")
	{
		if(cursor < 1024)
		{
			line0 = "RCAuto1";
		}
		else if (cursor < 2048)
		{
			line0 = "RCAuto2";
		}
		else if (cursor < 3071)
		{
			line0 = "RCAuto3";
		}
		else
		{
			line0 = "RCAuto4";
		}
	}
	else if (context[2] == "Blue Far")
	{
		if(cursor < 1024)
		{
			line0 = "BFAuto1";
		}
		else if (cursor < 2048)
		{
			line0 = "BFAuto2";
		}
		else if (cursor < 3071)
		{
			line0 = "BFAuto3";
		}
		else
		{
			line0 = "BFAuto4";
		}
	}
	else if (context[2] == "Blue Close")
	{
		if(cursor < 1024)
		{
			line0 = "BCAuto1";
		}
		else if (cursor < 2048)
		{
			line0 = "BCAuto2";
		}
		else if (cursor < 3071)
		{
			line0 = "BCAuto3";
		}
		else
		{
			line0 = "BCAuto4";
		}
	}
	displayLCDCenteredString(0, line0);
	displayLCDCenteredString(1, line1);
}
