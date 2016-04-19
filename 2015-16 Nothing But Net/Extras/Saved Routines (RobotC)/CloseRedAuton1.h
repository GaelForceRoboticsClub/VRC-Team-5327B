//Automatically generated code via VRC 5327B NbN Simulation
void CloseRedAuton1()
{
  //Turn to face goal
  ABase(0, 0, 127, 16);
  //Shoot 4 preload
  //Drive forward
  ABase(127, -8, 0, 10);
  //Strafe Over
  ABase(-21, -125, 0, 4);
  //Push pile
  ABase(-127, 0, 0, 4);
  //Turn for pyramid
  ABase(0, 0, -127, 16);
  //Intake
  ABase(-127, 0, 0, 3);
  //Backup
  ABase(127, 0, 0, 3);
  //Move forward and stop intaking
  ABase(-127, 0, 0, 3);
  //Back up
  ABase(127, 0, 0, 3);
  //Turn to face angle
  ABase(0, 0, 127, 15);
  //Outtake and drive back
  ABase(-127, 0, 0, 2);
}
