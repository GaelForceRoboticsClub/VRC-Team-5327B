//This file contains all of the auton routines

/*
1. Flip out
2. Grab center cube
3. Dump over middle fence
4. Grab 2-3 stars along perimeter
5. Dump along middle fence
6. Repeat 4-5

ALIGNMENT: Robot facing cube
*/
void LeftC3S2x()
{
	liftSpeed(-15);
	wait1Msec(250);
	claw(OPEN);
	wait1Msec(750);
	fd(127, 127, 600);
	claw(CLOSED);
	lu(127, 1300, 15);
	rt(127, 127, 300);
	liftSpeed(127);
	bk(127, 127, 400);
	lu(127, 2800, 127);
	claw(OPEN);
	lu(127, 3500, -10);
	wait1Msec(150);
	repeat(2)
	{
		ld(-127, 800, -15);
		fd(0, 127, 100);
		fd(127, 127, 450);
		claw(CLOSED);
		lu(127, 1300, -15);
		liftSpeed(127);
		bk(127, 127, 500);
		lu(127, 2800, 127);
		claw(OPEN);
		lu(127, 3500, -10);
	}
}

/*
1. Flip out
2. Grab center cube
3. Dump over middle fence but hold
4. Wait till end of auton
5. Dump cube to block any comebacks

ALIGNMENT: Robot facing cube
*/
void LeftCubeBlockM()
{
	liftSpeed(-15);
	wait1Msec(250);
	claw(OPEN);
	wait1Msec(750);
	fd(127, 127, 600);
	claw(CLOSED);
	lu(127, 1300, 15);
	rt(127, 127, 300);
	liftSpeed(127);
	bk(127, 127, 500);
	lu(127, 2900, -10);
	wait1Msec(9500);
	claw(OPEN);
}

/*
1. Flip out
2. Readjust angle of robot
3. Grab preload and corner star
4. Dump along side fence
6. Remain to block

ALIGNMENT: Robot facing perimeter but angled towards center
*/
void LeftCornerBlockL()
{
	bk(127, 127, 400);
	liftSpeed(-15);
	wait1Msec(250);
	claw(OPEN);
	wait1Msec(750);
	rt(127, 127, 100);
	fd(127, 127, 300);
	claw(CLOSED);
	wait1Msec(250);
	liftSpeed(127);
	bk(127, 127, 500);
	lu(127, 2800, 127);
	claw(OPEN);
	lu(127, 3500, -10);
	wait1Msec(150);
	ld(65, 2900, -5);
}

/*
1. Push stars
2. Flip out
3. Lift stars over cube
4. Dump along side fence

ALIGNMENT: Robot facing row of three stars
*/
void Left3S()
{
	fd(127, 127, 800);
	bk(127, 127, 200);
	liftSpeed(-15);
	wait1Msec(250);
	claw(OPEN);
	wait1Msec(750);
	fd(127, 127, 450);
	claw(CLOSED);
	wait1Msec(500);
	lu(127, 1800, 15);
	bk(127, 127, 800);
	rt(127, 127, 400);
	bk(127, 127, 400);
	liftSpeed(127);
	bk(127, 127, 600);
	lu(127, 2800, 127);
	claw(OPEN);
	lu(127, 3500, -10);
}
