task driverSFXTask()
{
	while(true)
	{
		if(JOHN_SO_BTN == 1)
		{
			clearSounds();
			playSoundFile("JohnSo.wav");
			waitUntil(JOHN_SO_BTN == 0);
		}
		else if(SOUND_CLEAR_BTN == 1)
		{
			clearSounds();
		}
		EndTimeSlice();
	}
}
