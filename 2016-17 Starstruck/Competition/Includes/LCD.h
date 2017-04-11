//This header file contains all code for LCD control.

//First, define an array of the four starting tiles
const string startTileArray[] = {
	"Alliance Red",
	"Hang Red",
	"Alliance Blue",
	"Hang Blue"
};

//Define a sample array of all of the available autons
//This array can be updated or assigned as autonomous routines
//grow increasingly complex
const string autonArray[][] = {
	{
		"RA_C3S",
		"RA_C",
		"RA_3-1",
		"RA_3",
		"None"
	},
	{
		"RH_C3S",
		"RH_C",
		"RH_3-1",
		"RH_3",
		"None"
	},
	{
		"BA_C3S",
		"BA_C",
		"BA_3-1",
		"BA_3",
		"None"
	},
	{
		"RH_C3S",
		"RH_C",
		"RH_3-1",
		"RH_3",
		"None"
	}
};

/*
Function that displays the desired string on the LCD.
Takes the following inputs:
- @startTile : The index of the starting tile to select
- @autonNumber : Which autonomous to run
- @timeDelay : How long to wait before starting routine
- @confirm : Used to finalize auton selection
Has no outputs.
*/
void LCDDisplay(int startTile, int autonNumber, int timeDelay, bool confirm = true)
{
	string toDisplay1 = ""; //Store two strings for future display
	string toDisplay2 = "";
	if(confirm) //If we are ready to finalize, display settings for confirmation
	{
		stringFormat(toDisplay1, "%s %ds", autonArray[startTile][autonNumber], timeDelay);
		toDisplay2 = "Reset";
	}
	else
	{
		if(autonNumber != -1) //Double check to see which menu level we are
		{
			if(timeDelay != -1)
			{
				stringFormat(toDisplay1, "Delay: %d s", timeDelay); //Allow for customizable delay
			}
			else
			{
				toDisplay1 = autonArray[startTile][autonNumber];
			}
		}
		else
		{
			toDisplay1 = startTileArray[startTile];
		}
		toDisplay2 = "<   SELECT   >";
	}
	displayLCDCenteredString(0, toDisplay1); //Send finished strings to LCD for display
	displayLCDCenteredString(1, toDisplay2);
}

//These arrays are used to help navigate through the menu system
int menuIndex[] = {
	0,
	-1,
	-1,
};

const int menuMax[] = {
	3,
	4,
	10,
};

int currMenuLevel = 0;
bool confirmed = false;

//Shortcut for scrolling left
void LCDLeft()
{
	menuIndex[currMenuLevel] = (menuIndex[currMenuLevel] > 0) ? menuIndex[currMenuLevel] - 1 : menuMax[currMenuLevel];
}

//Shortcut for scrolling right
void LCDRight()
{
	menuIndex[currMenuLevel] = (menuIndex[currMenuLevel] < menuMax[currMenuLevel]) ? menuIndex[currMenuLevel] + 1 : 0;
}

//Shortcut for hitting the center button
void LCDCenter()
{
	if(currMenuLevel < 2)
	{
		currMenuLevel++;
		menuIndex[currMenuLevel] = 0;
	}
	else if(currMenuLevel == 2 && !confirmed)
	{
		confirmed = true;
		playSound(soundUpwardTones);
	}
	else
	{
		confirmed = false;
		currMenuLevel = 0;
		menuIndex[0] = 0;
		menuIndex[1] = -1;
		menuIndex[2] = -1;
	}
}

//Main task that governs LCD code
task LCD()
{
	//Turn on backlight
	bLCDBacklight = true;
	bool noButtonsPressed = true;
	clearTimer(timer1);
	clearTimer(timer2);
	while(true)
	{
		if(!noButtonsPressed)
		{
			clearTimer(timer2);
		}
		bLCDBacklight = (time1[timer2] <= 5000);
		//Switch to respond to user input
		if(noButtonsPressed){
			switch(nLCDButtons){
			case kButtonLeft:
				LCDLeft();
				break;
			case kButtonCenter:
				LCDCenter();
				break;
			case kButtonRight:
				LCDRight();
				break;
			}
		}
		noButtonsPressed = !nLCDButtons;
		//Clear LCD for display
		clearLCDLine(0);
		clearLCDLine(1);
		//Display current location
		LCDDisplay(menuIndex[0], menuIndex[1], menuIndex[2], confirmed);
		wait1Msec(20);
		//Play chirpy warning sound every 5 seconds as a reminder
		if(bIfiRobotDisabled && !confirmed && time1[timer1] >= 5000)
		{
			playSound(soundBlip);
			clearTimer(timer1);
		}
		EndTimeSlice();
	}
}
