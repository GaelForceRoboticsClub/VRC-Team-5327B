//This header file contains all code for SFX control.

task SFX()
{
	while(true)
	{
		if(NameBtn == 1)
		{
			clearSounds()
			playSound("AndHisNameIs.wav");
			waitUntil(NameBtn == 0);
		}
		else if(KachowBtn == 1)
		{
			clearSounds()
			playSound("Kachow.wav");
			waitUntil(KachowBtn == 0);
		}
		EndTimeSlice();
	}
}
