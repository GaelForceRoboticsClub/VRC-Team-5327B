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

void startRoutine(string routineToBeStarted)
{
	if(routineToBeStarted == "ProgSkills1")
	{
		progskills1();
	}
	else if(routineToBeStarted == "redAuton1")
	{
		redAuton1();
	}
}
