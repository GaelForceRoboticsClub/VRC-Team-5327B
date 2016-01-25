//This header file contains all of the constants referenced throughout the driver competition code.
//EDIT WITH CAUTION!

//Base Constants:

//Launcher Constants:
const int LAUNCHER_ADJUST_SPEED = 50; //Changes how fast the launcher is adjusted when manually controlled by driver

//Intake Constants
const int BALL_INTOOK = 3000;
const int BALL_OUTTOOK = 1000;

//Angle Constants
const int ANGLE_TOLERANCE = 5; //How close the sensor values for angle need to be to the desired angle to shoot
const int POT_SCALE = -10; //The difference between AnglePot1 and AnglePot2 when they're at the (theoretically) same angle
const int ANGLE_ADJUST_SPEED = 50; //How fast the angle is adjusted when manually controlled by driver
