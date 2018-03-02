//This file contains all of the code controlling the sound effects of the robot

//Governs sound effects during Driver Control
task driverSFXTask()
{
	while(true)
	{
		//Check if we want to play "John So"
		if(JOHN_SO_BTN == 1)
		{
			//Clear any currently playing sound
			clearSounds();
			//Play file
			playSoundFile("JohnSo.wav");
			//Ensure no repeat toggling
			waitUntil(JOHN_SO_BTN == 0);
		}
		//If we need to immediately clear
		else if(SOUND_CLEAR_BTN == 1)
		{
			//Simply clear the sounds
			clearSounds();
		}
		//Delay to avoid hogging
		EndTimeSlice();
	}
}
