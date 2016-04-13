void redAuton1() //4 balls preloads shot and one pyramid next to red wall
{
	Greeting();
	wait1Msec(500);
	Vision();
	playSound(soundBlip);
	wait1Msec(500);
	Scanning();
	playSound(soundFastUpwardTones);
	Target();
	wait1Msec(1500);
	motor[Out1] = 127;
	motor[Out2] = 127;
}

void blueCaptureAuton1() //4 preloads,
{
	pew;
	pew;
	pew;
	pew;
	ABase(0, -127, 0, 1500);
	ABase(127, 0, 0, 250);
	AIntake(-1);
	ABase(0, 127, 0, 500);
	ABase(127, 0, 0, 500);
	ABase(0, 127, 0, 500);
	ABase(65, 65, 0, 1000);
	AIntake(0);
}

void blueCaptureAuton2()
{
	pew;
	pew;
	pew;
	pew;
	ABase(0, 0, 127, 750);
	ABase(0, 127, 0, 1500);
	ABase(0, 0, 127, 250);
	AIntake(1);
	ABase(0, 127, 0, 500);
	ABase(0, -127, 0, 250);
	ABase(0, 127, 0, 250);
	ABase(0, -127, 0, 250);
	AIntake(0);
	ABase(0, 0, 127, 500);
	AIntake(-1);
	ABase(0, 127, 0, 750);
	ABase(30, 97, 0, 250);
	ABase(0, 127, 0, 250);
	ABase(0, -127, 0, 500);
	ABase(-127, 0, 0, 250);
	ABase(0, 127, 0, 1000);
	AIntake(0);
}

void blueDefAuton1()
{
	pew;
	pew;
	pew;
	pew;
	ABase(0, 0, -127, 250);
	AIntake(1);
	ABase(0, 127, 0, 500);
	ABase(0, 0, -127, 50);
	ABase(0, 127, 0, 500);
}

void blueDefAuton2()
{
	pew;
	pew;
	pew;
	pew;
	ABase(0, 0, -127, 250);
	AIntake(1);
	ABase(0, 127, 0, 500);
	ABase(0, 0, 127, 150);
	ABase(0, 127, 0, 500);
}

void progskills1()
{
	pew;
	pew;
	pew;
	pew;
	pew;
	pew;
	pew;
	pew;
	pew;
	pew;
	pew;
	pew;
	pew;
	pew;
	pew;
	pew;
	pew;
	pew;
	pew;
	pew;
	pew;
	pew;
	pew;
	pew;
	pew;
	pew;
	pew;
	pew;
	pew;
	pew;
	pew;
	pew;
	ABase(-127, 0, 0, 500); //Align off of wall by driving to the left
	ABase(127, 0, 0, 5250); //Strafe over to the right and align off of wall
	ABase(-127, 0, 0, 100); //Readjust base to prepare for firing
	pew;
	pew;
	pew;
	pew;
	pew;
	pew;
	pew;
	pew;
	pew;
	pew;
	pew;
	pew;
	pew;
	pew;
	pew;
	pew;
	pew;
	pew;
	pew;
	pew;
	pew;
	pew;
	pew;
	pew;
	pew;
	pew;
	pew;
	pew;
	pew;
	pew;
	pew;
	pew;
}

void originalAutonJeffrey()
{
	while(SensorValue[in8] >= -310)
	{
		motor[RFBase] = -32;
		motor[LFBase] = 32;
		motor[RBBase] = -32;
		motor[LBBase] = 32;
	}
	motor[RFBase] = 0;
	motor[LFBase] = 0;
	motor[RBBase] = 0;
	motor[LBBase] = 0;
	wait1Msec(500);
	//ABase(0, -127, 0, 2500);

	motor[RFBase] = -75;
	motor[LFBase] = -127;
	motor[RBBase] = -75;
	motor[LBBase] = -127;
	wait1Msec(4000);
	motor[RFBase] = 0;
	motor[LFBase] = 0;
	motor[RBBase] = 0;
	motor[LBBase] = 0;

	wait1Msec(1000);
	motor[RFBase] = 127;
	motor[LFBase] = -127;
	motor[RBBase] = -127;
	motor[LBBase] = 127;
	wait1Msec(500);
	motor[RFBase] = 0;
	motor[LFBase] = 0;
	motor[RBBase] = 0;
	motor[LBBase] = 0;
	/*while(SensorValue[LauncherSet] == 0)
	{
	motor[Out1] = 127;
	motor[Out2] = 127;
	}
	motor[Out1] = LAUNCHER_HOLD;
	motor[Out2] = LAUNCHER_HOLD;
	LauncherControlAuton(3);
	while(SensorValue[BallSensorLauncher] <= 2000)
	{
	motor[Out1] = 127;
	motor[Out2] = 127;
	}
	motor[Out1] = LAUNCHER_HOLD;
	motor[Out2] = LAUNCHER_HOLD;


	ABase(-32, 0, 0, 500);
	wait1Msec(2000);
	ABase(0, -127, 0, 2000);
	*/
}
