void flipout()
{
	autonVbarUp();
	autonLiftUp(LIFT_MIN + 300, true);
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
	aFd(65, 65, 200);	//Drive to stago
	autonVbarDown(VBAR_DOWN - 200);	//Bring cone down on stago
	autonLiftDown(1800, true);	//Bring cone down on stago
	wait1Msec(250);
	autonClawOpen();	//Drop cone
	wait1Msec(250);
	aBk(65, 65, 150);	//Back away carefully
	//Ideally position ourselves for next mogo? only if we have time
	clap(5);	//Celebrate?
	autonLiftDown(true);	//Lift down to be ready for driver control
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
	aFd(127, 127, 500);	//Drive to mogo
	autonMogoIn(true);	//Intake mogo
	wait1Msec(250);
	autonClawOpen(true);	//Drop preload
	wait1Msec(250);
	autonLiftDown();	//Reset lift & vbar for next cone
	autonVbarDown(true);
	aFd(127, 127, 100);	//Drive to next cone straight in front
	autonClawClose(true);	//Grab cone
	wait1Msec(250);
	autonLiftUp(LIFT_MIN + 300, true);	//Lift up slightly
	autonVbarUp(true);	//Get cone over mogo
	wait1Msec(250);
	autonClawOpen();	//Drop cone
	aBk(127, 127, 600);	//Drive backwards towards goal zones
	aTn(127, -127, 100);	//Turn 180 to prepare to score
	aFd(85, 127, 300);	//Drive slanted to get to 20 point zone faster
	autonMogoOut(MOGO_OUT - 1000);	//Drop mogo at a height
	aBk(127, 127, 200);	//Slam backwards to release mogo
}

void a2cone5Pt()
{
	//Hopefully almost literally the same as the previous one
}
