//This header file contains all of the constants referenced throughout the driver competition code.
//EDIT WITH CAUTION!

//General Constants:
const int LOOP_DELAY = 10; //How long between each refresh of the while loops governing robot code, used because we do not need 1000 refreshes per second
const int BALL_WIDTH = 10; //How big each ball is (roughly), used to determine if a ball has been spotted based on change in Ultra values
//Base Constants:

//Launcher Constants:
const int LAUNCHER_ADJUST_SPEED = 127; //Changes how fast the launcher is adjusted when manually controlled by driver
const int DELAY_BETWEEN_BALLS = 50; //How long to wait between firing one ball and pulling back for the next, useful to prevent the motor from skipping
const int LAUNCHER_SLOW_SPEED = 80; //How fast the launcher is adjusted on Slow setting
const int LAUNCHER_HOLD = 15; //How fast to move backwards so as to hold the launcher from firing

//Intake Constants
const int BALL_INTOOK = 3000; //Sensor reading of potentiometer turnstile that represents a new ball being intaken
const int BALL_OUTTOOK = 1000; //Sensor reading of potentiometer turnstile that represents a new ball being outtaken
const int BALL_SENSED_LAUNCHER = 500;
const int BALL_SENSED_RAMP = 300;

//Angle Constants
const int ANGLE_TOLERANCE = 10; //How close the sensor values for angle need to be to the desired angle to shoot
const int ANGLE_ADJUST_SPEED = 50; //How fast the angle is adjusted when manually controlled by driver
const int ANGLE_LONG_RANGE = -300; //The potentiometer setting for shooting long range (starting tiles)
const int ANGLE_SHORT_RANGE = -890; //The potentiometer setting for shooting close up (midfield ish)
const int ANGLE_MAX_VAL = -1090; //Maximum limit for launcher
const int ANGLE_MIN_VAL = -720; //Minimum limit for launcher
