//This header file contains joystick button definitions to make the code easier to read.

#define ShiftBtn vexRT[Btn5U] * (1 - vexRT[Btn5D])
#define OverrideBtn vexRT[Btn5D] * vexRT[Btn5U]

//Base control
#define RBase vexRT[Ch2]
#define LBase vexRT[Ch3]

//Lift control
#define LiftUp vexRT[Btn6U] * (1 - ShiftBtn)
#define LiftDown vexRT[Btn6D] * (1 - ShiftBtn)
#define LiftUpSlow vexRT[Btn6U] * ShiftBtn
#define LiftDownSlow vexRT[Btn6D] * ShiftBtn

//Intake control
#define ClawToggle vexRT[Btn8R]

//Translational control
#define SlideUp vexRT[Btn8D] * (1 - ShiftBtn)
#define SlideDown vexRT[Btn8U] * (1 - ShiftBtn)
#define SlideAutoUp vexRT[Btn8D] * ShiftBtn
#define SlideAutoDown vexRT[Btn8U] * ShiftBtn

//Mogo control
#define MogoIn vexRT[Btn7D] * (1 - ShiftBtn)
#define MogoOut vexRT[Btn7U] * (1 - ShiftBtn)
#define MogoAutoIn vexRT[Btn7D] * ShiftBtn
#define MogoAutoOut vexRT[Btn7U] * ShiftBtn
