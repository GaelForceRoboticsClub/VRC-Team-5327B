//This header file contains all of the autonomous-simplifying function code for the robot

//All drive functions operate on the same principle, and are named differently for readability
//lpower represents the speed to turn the left side of the base
//rpower represents the speed to turn the right side of the base
//distance represents how many ticks the right side will turn in the movement

void fd(int lpower, int rpower, int distance)
{
	nMotorEncoder[RFBase] = 0;
	motor[LFBase] = abs(lpower);
	motor[RFBase] = abs(rpower);
	waitUntil(abs(nMotorEncoder[RFBase]) > distance);
	motor[LFBase] = 0;
	motor[RFBase] = 0;
}

void bk(int lpower, int rpower, int distance)
{
	nMotorEncoder[RFBase] = 0;
	motor[LFBase] = -abs(lpower);
	motor[RFBase] = -abs(rpower);
	waitUntil(abs(nMotorEncoder[RFBase]) > distance);
	motor[LFBase] = 0;
	motor[RFBase] = 0;
}

void rt(int lpower, int rpower, int distance)
{
	nMotorEncoder[RFBase] = 0;
	motor[LFBase] = abs(lpower);
	motor[RFBase] = -abs(rpower);
	waitUntil(abs(nMotorEncoder[RFBase]) > distance);
	motor[LFBase] = 0;
	motor[RFBase] = 0;
}

void lt(int lpower, int rpower, int distance)
{
	nMotorEncoder[RFBase] = 0;
	motor[LFBase] = -abs(lpower);
	motor[RFBase] = abs(rpower);
	waitUntil(abs(nMotorEncoder[RFBase]) > distance);
	motor[LFBase] = 0;
	motor[RFBase] = 0;
}

//Similarly, all lift functions have the same premise
//power represents the speed at which to move the lift
//pot_val represents the target lift height to reach
//hold represents the ending speed the lift should remain at

void lu(int power, int pot_val, int hold)
{
	motor[LiftR12] = abs(power);
	waitUntil(SensorValue[LiftPot] >= pot_val);
	motor[LiftR12] = hold;
}

void ld(int power, int pot_val, int hold)
{
	motor[LiftR12] = -abs(power);
	waitUntil(SensorValue[LiftPot] <= pot_val);
	motor[LiftR12] = hold;
}
