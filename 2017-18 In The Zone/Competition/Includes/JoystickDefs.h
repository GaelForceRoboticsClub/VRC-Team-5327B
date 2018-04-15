//This file contains all of the joystick button assignments for the robot

//Base control
#define R_JOY vexRT[JOY_JOY_RV]
#define L_JOY vexRT[JOY_JOY_LV]

//Lift control
#define LIFT_UP_BTN vexRT[JOY_TRIG_RU]
#define LIFT_DOWN_BTN vexRT[JOY_TRIG_RD]
#define LIFT_UP_SLOW_BTN 0 		//Slow lift functionality has been disabled
#define LIFT_DOWN_SLOW_BTN 0

//Vertibar control
#define VBAR_UP_BTN vexRT[JOY_TRIG_LU]
#define VBAR_DOWN_BTN vexRT[JOY_TRIG_LD]

//Claw control
#define CLAW_RELEASE_BTN vexRT[JOY_BTN_LU]

//Mogo control
#define MOGO_OUT_ADJ_BTN vexRT[JOY_BTN_RU]
#define MOGO_IN_ADJ_BTN vexRT[JOY_BTN_RD]
#define MOGO_TOGGLE_BTN vexRT[JOY_BTN_RR]

//Brake toggling
#define BRAKE_TOGGLE_BTN vexRT[JOY_BTN_RL]
