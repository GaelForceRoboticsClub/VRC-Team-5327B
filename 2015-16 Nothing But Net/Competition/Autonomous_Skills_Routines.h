void redAuton1() //4 balls preloads shot and one pyramid next to red wall
{
	pew;
	pew;
	pew;
	pew;
	wait1Msec(500);
	ABase(0, 127, 0, 1500);
	ABase(0, 0, 127, 500);
	ABase(0, 127, 0, 500);
	AIntake(1);
	ABase(0, -127, 0, 500);
	ABase(0, 127, 0, 500);
	playTone(soundBeepBeep);
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
	else if(routineToBeStarted == "autonRed1")
	{
		redAuton1();
	}
}
