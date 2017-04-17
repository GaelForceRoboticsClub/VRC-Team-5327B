//This header file contains all code for SFX control.

task SFX()
{
	while(true)
	{
		if(KachowSFX == 1)
		{
			clearSounds();
			playSoundFile("Kachow.wav");
			waitUntil(KachowSFX == 0);
		}
		EndTimeSlice();
	}
}
