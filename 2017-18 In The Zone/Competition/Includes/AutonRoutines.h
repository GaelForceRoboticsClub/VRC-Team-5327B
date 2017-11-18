void flipout()
{
	autonVbarUp(true);
	autonLiftUp(LIFT_MIN + 200, true);
}

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

void stago()
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

void block()
{
	//Need to figure out if this is best route
	aFd(127, 127, 650, 6000); //Drive forward with a timeout to avoid damage to motors
}

void a2Cone20Pt()
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
	aBk(85, 127, 2200);	//Drive backwards towards goal zones
	wait1Msec(250);
	aTn(-65, 65, 800);
	wait1Msec(250);
	autonMogoOut(MOGO_OUT - 400, true);
	wait1Msec(250);
	aFd(127, 127, 400);
	aBk(100, 100, 400);
	/*aTn(127, -127, 100);	//Turn 180 to prepare to score
	aFd(85, 127, 300);	//Drive slanted to get to 20 point zone faster
	autonMogoOut(MOGO_OUT - 1000);	//Drop mogo at a height
	aBk(127, 127, 200);	//Slam backwards to release mogo*/
	wait1Msec(5000);
}

void a2cone5Pt()
{
	//Hopefully almost literally the same as the previous one
}
