void JohnCena()
{
	/*
		RTTL script:
		John Cena:
		d=4,o=6,b=52:
		16p, 16g, 32a#, 32f, 32p, 4g, 8p, 16a#, 32a, 32f, 32p, 4g, 8p
	*/
  //         50 = Tempo
  //          6 = Default octave
  //    Quarter = Default note length
  //        10% = Break between notes
  //
  playTone(    0,   27); wait1Msec( 300);  // Note(Rest, Duration(16th))
  playTone( 1175,   27); wait1Msec( 300);  // Note(G, Duration(16th))
  playTone( 1398,   14); wait1Msec( 150);  // Note(A#, Duration(32th))
  playTone( 1047,   14); wait1Msec( 150);  // Note(F, Duration(32th))
  playTone(    0,   14); wait1Msec( 150);  // Note(Rest, Duration(32th))
  playTone( 1175,  108); wait1Msec(1200);  // Note(G)
  return;
}
