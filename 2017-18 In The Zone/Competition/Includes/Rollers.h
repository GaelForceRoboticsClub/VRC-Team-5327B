task driverRollerTask()
{
  int rollerDir = 0;
  bool rollersStuck = false;
  while(true)
  {
    //fancy code that checks if the "adjust" is 0; if so, don't change rollerdir. If not, change rollerdir
    rollerDir = ROLL_IN_BTN - ROLL_OUT_BTN == 0 ? rollerDir : ROLL_IN_BTN - ROLL_OUT_BTN;
    if(rollerDir == 1)  //trying to intake cone
    {
      if(rollersStuck)  //if rollers are locked just hold
      {
        motor[rollers] = 15;
      }
      else
      {
        int rollerStart = SensorValue[RollerEnc];
        motor[rollers] = 127;  //go max speed...
        wait1msec(20);
        if(abs(SensorValue[RollerEnc] - rollerStart) < THRESHOLD) //but check that encoder is moving
        {
          motor[rollers] = 15;  //else lock up
          rollersStuck = true;
        }
      }
    }
    else if(rollerDir == -1) //trying to outtake cone
    {
      rollersStuck = false;
      motor[rollers] = -127;
    }
    EndTimeSlice();
  }
}
