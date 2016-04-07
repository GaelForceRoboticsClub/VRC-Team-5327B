//This header file contains the necessary functions to be run throughout the competition


/*
Function governing the movement of the base during Autonomous. Takes 4 parameters:
@X_comp : How much we want to strafe
@Y_comp : How much we want to drive forwards/backwards
@rot_comp : How much we want to rotate the robot CW/CCW
@duration : How long to drive
*/
void ABase(int X_comp, int Y_comp, int rot_comp, int duration=10)
{
	//Waits until previous duration is 0 (command finished), then adds a new command to the drive array
	waitUntil(Auton_Drive_Array[3] == 0);
	Auton_Drive_Array[0] = X_comp;
	Auton_Drive_Array[1] = Y_comp;
	Auton_Drive_Array[2] = rot_comp;
	Auton_Drive_Array[3] = duration;
}


/*
Function governing the launcher during Autonomous. Takes 3 parameters:
@direction : Whether we want to launch or adjust forwards
@duration : How long we wish to maintain this motion
@slow : Whether we should shoot at a slow speed
*/
void ALaunch(int direction, int duration = 500, bool slow)
{
	waitUntil(Auton_Launch_Array[2] == 0);
	Auton_Launch_Array[0] = direction;
	Auton_Launch_Array[1] = duration;
	Auton_Launch_Array[2] = slow;
}


/*
Function governing the angle during Autonomous. Takes 3 parameters:
@auto_angle : automatic angle setting we wish to use
@angle_adjust : direction in which to change the angle
@absolute_angle : absolute angle we wish the launcher to be at
*/
void AAngle(int auto_angle, int angle_adjust = 0, int absolute_angle = 0)
{
	Auton_Angle_Array[0] = auto_angle;
	Auton_Angle_Array[1] = angle_adjust;
	Auton_Angle_Array[2] = absolute_angle;
}


/*
Function governing the intake during Autonomous. Takes 1 parameter:
@direction : Whether we want to intake, outtake, or neither
*/
void AIntake(int direction)
{
	Auton_Intake_Array[0] = direction;
}


/*
Function governing the autoloader during Autonomous. Takes 1 parameter:
@direction : Whether we want to intake, outtake, or neither
*/
void AAutoLoad(int direction)
{
	Auton_AutoLoad_Array[0] = direction;
}

/*
Function allowing for a controlled turn based on gyroscope values. Takes 3 parameters:
@speed : The desired speed of the turn, with the sign indicating direction
@change : The desired change in current heading desired, with the sign indicating direction
@tolerance : Default 50, how far off we can be from the exact measurement to consider a success
*/
void AGyroTurn(int speed, int change, int tolerance = 50)
{
	int initialGyro = 0;
	repeat(10)
	{
		initialGyro += SensorValue[Gyro];
	}
	initialGyro /= 10;
	int targetGyro = initialGyro + change;
	if(targetGyro > 4000)
	{
		targetGyro -= 4000;
	}
	else if(targetGyro < 0)
	{
		targetGyro += 4000;
	}
	repeatUntil(closeEnough(initialGyro, targetGyro, tolerance))
	{
		ABase(0, 0, speed);
	}
	ABase(0, 0, 0);
}
