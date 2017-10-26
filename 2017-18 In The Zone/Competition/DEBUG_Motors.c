int motors_on[] = {
	0, 1, 1, 0, 0,
	1, 1, 0, 0, 0
	};

task main()
{
	for(int i = 0; i < 10; i ++)
	{
		motor[i] = motors_on[i] * 65;
		wait1Msec(500);
		motor[i] = 0;
		if(motors_on[i] == 1)
		{
			repeat(i + 1)
			{
				playTone(700, 2);
				wait1Msec(50);
			}
		}
		wait1Msec(1000);
	}
}
