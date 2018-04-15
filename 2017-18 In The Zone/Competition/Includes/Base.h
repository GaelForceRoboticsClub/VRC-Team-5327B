//This file contains all of the code that controls the base of the robot
const ubyte trueSpeed[128] = {
	 0,  3,  5,  7,  8,  9, 10, 10, 11, 11,
	11, 12, 12, 12, 12, 12, 12, 13, 13, 13,
	13, 14, 14, 14, 14, 14, 15, 15, 15, 15,
	16, 16, 16, 16, 16, 16, 17, 17, 17, 17,
	18, 18, 18, 18, 18, 19, 19, 19, 20, 20,
	20, 20, 21, 21, 21, 22, 22, 22, 22, 23,
	23, 23, 24, 24, 24, 24, 25, 25, 25, 26,
	26, 26, 27, 27, 27, 28, 28, 28, 29, 29,
	30, 30, 31, 31, 32, 32, 33, 33, 34, 35,
	35, 36, 37, 37, 38, 39, 39, 40, 41, 41,
	42, 43, 44, 45, 46, 46, 47, 48, 49, 50,
	51, 53, 54, 55, 57, 60, 62, 65, 69, 72,
	76, 80, 82, 85, 87, 91, 101, 127
};
int baseScale(int input)
{
	return sgn(input) * trueSpeed[abs(input)];
}

//Governs the base during Driver Control
task driverBaseTask()
{
	slaveMotor(RBBase, RFBase);
	slaveMotor(LBBase, LFBase);
	while(true)
	{
		//Back base motors are directly powered by joysticks
		motor[RFBase] = baseScale(R_JOY);
		motor[LFBase] = baseScale(L_JOY);
		//Slight delay to avoid hogging
		EndTimeSlice();
	}
}
