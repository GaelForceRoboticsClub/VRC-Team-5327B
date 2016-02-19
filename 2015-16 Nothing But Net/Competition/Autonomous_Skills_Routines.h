void progskills1()
{
	pew
	pew
	pew
	pew
	pew
	pew
	pew
	pew
	pew
	pew
	pew
	pew
	pew
	pew
	pew
	pew
	pew
	pew
	pew
	pew
	pew
	pew
	pew
	pew
	pew
	pew
	pew
	pew
	pew
	pew
	pew
	pew
	ABase(-127, 0, 0, 500); //Align off of wall by driving to the left
	ABase(127, 0, 0, 2500); //Strafe over to the right and align off of wall
	ABase(-127, 0, 0, 100); //Readjust base to prepare for firing
	pew
	pew
	pew
	pew
	pew
	pew
	pew
	pew
	pew
	pew
	pew
	pew
	pew
	pew
	pew
	pew
	pew
	pew
	pew
	pew
	pew
	pew
	pew
	pew
	pew
	pew
	pew
	pew
	pew
	pew
	pew
	pew
}

void startRoutine(string routineToBeStarted)
{
	if(routineToBeStarted == "ProgSkills1")
	{
		progskills1();
	}
}
