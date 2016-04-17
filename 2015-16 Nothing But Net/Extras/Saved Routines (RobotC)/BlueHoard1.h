//Automatically generated code via VRC 5327B NbN Simulation
void BlueHoard1()
{
  //Pull back to Net
  ABase(-127, 0, 0, 29);
  //Turn towards wall pyramid
  ABase(0, 0, 127, 3);
  //Approach pyramid
  ABase(127, 0, 0, 4);
  AIntake(1);
  //Grab pyramid
  ABase(0, 0, 127, 2);
  ABase(126, -16, 0, 2);
  AIntake(0);
  //Turn back
  ABase(0, 0, -127, 3);
  //Back up
  ABase(-127, 0, 0, 3);
  //Prepare to hoard
  ABase(0, 0, -127, 2);
  AIntake(-1);
  //Two pyramids hoard
  ABase(127, 0, 0, 11);
  //Last pyramid hoard
  ABase(119, 43, 0, 7);
  //ready to move
  ABase(0, 0, -127, 1);
  ABase(27, 124, 0, 2);
  //Done hoarding
  ABase(123, -33, 0, 11);
  AIntake(0);
}
