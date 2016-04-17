//Automatically generated code via VRC 5327B NbN Simulation
void BlueHoard2()
{
  //Pull back
  ABase(-127, 0, 0, 25);
  //Shift for pyramid
  ABase(0, 127, 0, 3);
  //Grab pyramid
  ABase(127, 0, 0, 4);
  //Realign
  ABase(0, -127, 0, 7);
  //Pyramids outtaken
  ABase(127, 0, 0, 12);
  //getready for last pyramid
  ABase(0, 0, 127, 2);
  //Slam wal
  ABase(-3, -127, 0, 5);
  //Push in to home
  ABase(124, 25, 0, 11);
}
