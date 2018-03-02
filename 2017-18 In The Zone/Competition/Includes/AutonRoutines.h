//Initiates the proper flipout action at the start of autonomous
void flipout()
{
	autonVbarUp(true);
	autonLiftUp(LIFT_MIN + 200, true);
}

//Actuates the claw repeatedly to 'clap' for specified count
void clap(int i)
{
	repeat(i)
	{
		autonClawClose(true);
		wait1Msec(250);
		autonClawOpen(true);
		wait1Msec(250);
	}
}

void stagoThenRight()
{
	flipout();	//Flipout
	autonLiftUp(2000);	//Lift up tall enough for stago
	autonMogoOut(MOGO_OUT, true);	//Get mogo intake out and ready
	aFd(65, 65, 1100);	//Drive to stago
	autonVbarDown(true);	//Bring cone down on stago
	autonLiftDown(1850, true);	//Bring cone down on stago
	wait1Msec(500);
	autonClawOpen();	//Drop cone
	wait1Msec(250);
	aBk(65, 65, 350);	//Back away carefully
	//Ideally position ourselves for next mogo? only if we have time
	clap(5);	//Celebrate?
	autonLiftDown(LIFT_MIN + 700, true);	//Lift down to be ready for driver control
	aTn(-65, 65, 475);
	wait1Msec(500);
	aFd(127, 127, 1600);
}

void aStagoThenLeft()
{
	flipout();	//Flipout
	autonLiftUp(2000);	//Lift up tall enough for stago
	autonMogoOut(MOGO_OUT, true);	//Get mogo intake out and ready
	aFd(65, 65, 1100);	//Drive to stago
	autonVbarDown(true);	//Bring cone down on stago
	autonLiftDown(1850, true);	//Bring cone down on stago
	wait1Msec(500);
	autonClawOpen();	//Drop cone
	wait1Msec(250);
	aBk(65, 65, 350);	//Back away carefully
	//Ideally position ourselves for next mogo? only if we have time
	clap(5);	//Celebrate?
	autonLiftDown(LIFT_MIN + 700, true);	//Lift down to be ready for driver control
	aTn(65, -65, 475);
	wait1Msec(500);
	aFd(127, 127, 1600);
}

void aBlock()
{
	//Need to figure out if this is best route
	aFd(127, 127, 650, 6000); //Drive forward with a timeout to avoid damage to motors
}

void a2Cone5PtRightWall()
{
	flipout();	//Flipout
	autonMogoOut();	//Get mogo intake ready
	wait1Msec(500);
	aFd(127, 127, 2350);	//Drive to mogo
	aFd(65, 65, 600);
	autonVbarDown(true);
	wait1Msec(1000);
	autonClawOpen();
	wait1Msec(250);
	autonLiftUp(LIFT_MIN + 500);
	autonMogoIn(true);	//Intake mogo
	wait1Msec(500);
	aBk(85, 127, 1300);	//Drive backwards towards goal zones
	wait1Msec(1050);
	aTn(-65, 65, 800);
	autonMogoOut(true);
	aBk(100, 100, 350);
	wait1Msec(5000);
}
void a2Cone5PtLeftWall()
{
	flipout();	//Flipout
	autonMogoOut();	//Get mogo intake ready
	wait1Msec(500);
	aFd(127, 127, 2350);	//Drive to mogo
	aFd(65, 65, 600);
	autonVbarDown(true);
	wait1Msec(1000);
	autonClawOpen();
	wait1Msec(250);
	autonLiftUp(LIFT_MIN + 500);
	autonMogoIn(true);	//Intake mogo
	wait1Msec(500);
	aBk(85, 127, 1300);	//Drive backwards towards goal zones
	wait1Msec(1050);
	aTn(65, -65, 800);
	autonMogoOut(true);
	aBk(100, 100, 350);
	wait1Msec(5000);
}
