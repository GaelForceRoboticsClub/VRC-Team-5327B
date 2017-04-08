#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    LiftPot,        sensorPotentiometer)
#pragma config(Sensor, in2,    RLine,          sensorLineFollower)
#pragma config(Sensor, in3,    LLine,          sensorLineFollower)
#pragma config(Sensor, in4,    Gyro,           sensorGyro)
#pragma config(Sensor, dgtl1,  ReadyBump,      sensorTouch)
#pragma config(Sensor, dgtl10, LEDs,           sensorDigitalOut)
#pragma config(Sensor, dgtl11, Bands,          sensorDigitalOut)
#pragma config(Sensor, dgtl12, ClawP,          sensorDigitalOut)
#pragma config(Sensor, I2C_1,  RBaseEnc,       sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port2,           RFBase,        tmotorVex393_MC29, openLoop, reversed, driveRight, encoderPort, I2C_1)
#pragma config(Motor,  port3,           LFBase,        tmotorVex393_MC29, openLoop, driveLeft)
#pragma config(Motor,  port4,           LiftR12,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           LiftL12,       tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           RBBase,        tmotorVex393_MC29, openLoop, reversed, driveRight)
#pragma config(Motor,  port7,           LBBase,        tmotorVex393_MC29, openLoop, driveLeft)
#pragma config(Motor,  port8,           LiftR3L3,      tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           Claw,          tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/**************************
BUILD DATE: 	1/20/16
AUTHOR: 			JAIVEER SINGH
V4.3.2
**************************/

//VRC Specific pragmas below
#pragma platform(VEX)
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)
#include "/includes/Vex_Competition_Includes-.h"
//VRC Specific pragmas above

#include "Joystick_Defs.h" 	//Define joystick buttons in more user-friendly terms
#include "Constants.h" 			//All constants used in the entire program
#include "TrueSpeed_Slew.h" //Advanced motor control for the robot
#include "Base.h"						//All base-control code
#include "Claw.h" 					//All claw-control code
#include "Lift.h" 					//All lift-control code
#include "LCD.h"						//All LCD code
#include "Auton_Func.h"			//Autonomous function code
#include "Auton_Routines.h" //Autonomous routines code

//Ready for match after reconnect
void pre_auton()
{
	startTask(LCD);
	//By slaving motors together, they can never accidentally drive in opposite directions
	lift_hold = 0;
	slaveMotor(RBBase, RFBase);
	slaveMotor(LBBase, LFBase);
	slaveMotor(LiftR3L3, LiftR12);
	slaveMotor(LiftL12, LiftR12);
	//Warning sound before claw close
	playTone(750, 10);
	wait1Msec(500);
	claw(CLOSED);
}

bool auton_flag = false;

task autonomous()
{
	LeftC3S2x();
	auton_flag = true;
}

task usercontrol()
{

	startTask(base);
	startTask(intake);
	startTask(lift);
	startTask(sfx);
	while(true)
	{
		EndTimeSlice();
	}
}
