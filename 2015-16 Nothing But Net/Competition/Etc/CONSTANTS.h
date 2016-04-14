//This header file contains all of the constants referenced throughout the driver competition code.
//EDIT WITH CAUTION!

//General Constants:
const int LOOP_DELAY = 1; //How long between each refresh of the while loops governing robot code, used because we do not need 1000 refreshes per second
const unsigned int TrueSpeed[128] =
{
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0, 21, 21, 21, 22, 22, 22, 23, 24, 24,
	25, 25, 25, 25, 26, 27, 27, 28, 28, 28,
	28, 29, 30, 30, 30, 31, 31, 32, 32, 32,
	33, 33, 34, 34, 35, 35, 35, 36, 36, 37,
	37, 37, 37, 38, 38, 39, 39, 39, 40, 40,
	41, 41, 42, 42, 43, 44, 44, 45, 45, 46,
	46, 47, 47, 48, 48, 49, 50, 50, 51, 52,
	52, 53, 54, 55, 56, 57, 57, 58, 59, 60,
	61, 62, 63, 64, 65, 66, 67, 67, 68, 70,
	71, 72, 72, 73, 74, 76, 77, 78, 79, 79,
	80, 81, 83, 84, 84, 86, 86, 87, 87, 88,
	88, 89, 89, 90, 90,127,127,127
};

//Base Constants:
//None, all base calculations are made relative to user control

//Launcher Constants:
const int LAUNCHER_SLOW_SPEED = 80; //How fast the launcher is adjusted on Slow setting
const int LAUNCHER_HOLD = 15; //How fast to move backwards so as to hold the launcher from firing

//Intake Constants
const int BALL_SENSED_LAUNCHER = 2500;
const int BALL_SENSED_ELEVATOR = 2500;
const int BALL_SENSED_RAMP = 2500;

//Autoloader Constants
const int AUTOLOAD_FORWARD = 100;
const int AUTOLOAD_BACK = -65;

//Angle Constants
const int ANGLE_TOLERANCE = 10; //How close the sensor values for angle need to be to the desired angle to shoot
const int ANGLE_ADJUST_SPEED_DOWN = 50; //How fast the angle is adjusted when manually controlled by driver down
const int ANGLE_ADJUST_SPEED_UP = 90; //How fast the angle is adjusted when manually controlled by driver up
int ANGLE_LONG_RANGE = 1660; //The potentiometer setting for shooting long range (starting tiles)
int ANGLE_SHORT_RANGE = 1530; //The potentiometer setting for shooting close up (midfield ish)
const int ANGLE_MAX_VAL = -1090; //Maximum limit for launcher
const int ANGLE_MIN_VAL = -720; //Minimum limit for launcher
const int ANGLE_HOLD = 15;
