//This header file contains all of the constants referenced throughout the driver competition code.
//EDIT WITH CAUTION!

//General Constants:
const int LOOP_DELAY = 10; //How long between each refresh of the while loops governing robot code, used because we do not need 1000 refreshes per second
const int BALL_WIDTH = 10; //How big each ball is (roughly), used to determine if a ball has been spotted based on change in Ultra values
//Base Constants:

//Launcher Constants:
const int LAUNCHER_ADJUST_SPEED = 50; //Changes how fast the launcher is adjusted when manually controlled by driver
const int DELAY_BETWEEN_BALLS = 50; //How long to wait between firing one ball and pulling back for the next, useful to prevent the motor from skipping

//Intake Constants
const int BALL_INTOOK = 3000; //Sensor reading of potentiometer turnstile that represents a new ball being intaken
const int BALL_OUTTOOK = 1000; //Sensor reading of potentiometer turnstile that represents a new ball being outtaken

//Angle Constants
const int ANGLE_TOLERANCE = 5; //How close the sensor values for angle need to be to the desired angle to shoot
const int POT_SCALE = -10; //The difference between AnglePot1 and AnglePot2 when they're at the (theoretically) same angle
const int ANGLE_ADJUST_SPEED = 50; //How fast the angle is adjusted when manually controlled by driver
