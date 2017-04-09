//This header file contains all code for SFX control.

task SFX()
{
	while(true)
	{
		if(NameSFX == 1)
		{
			clearSounds();
			playSoundFile("AndHisNameIs.wav");
			waitUntil(NameSFX == 0);
		}
		else if(KachowSFX == 1)
		{
			clearSounds();
			playSoundFile("Kachow.wav");
			waitUntil(KachowSFX == 0);
		}
		EndTimeSlice();
	}
}
