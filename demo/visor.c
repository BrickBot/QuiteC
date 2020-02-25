#include <qc.h>

// Photo Robot Software.
///////////////////////////////////////////////////////
//   You must construct a Robot with differential 
// motors on the OUT_A & OUT_C and connect
// the light sensor on the SENSOR_2 with a 3rd motor
// connected to the OUT_B (I have used a Walkman motor)
//   You must connect some gear to let the light sensor
// go up & down and the two motor (OUT_A & OUT_C) to move
// the robot left & right. So you can control all movement
// to build an Image step by step. 
//   Block the down movement at some degree with some trick 
// so that you can give the motor some time so reach the down 
// position & recalibrate for the next round with a fixed pos.
//   I have used a VERY simple protocol to comunicate with the
// computer via IR. 
//   loop for YMAX times
//     Wait a char
//     Send XMAX char with data
//   end loop
//   Now that the Robot have got all data, you can transmit
// that to the computer via InfraRed, I have done so with a 
// VB6 program (included) that collect the data & build a 
// TGA image.
//   I have done some equalize on the resulting image.


#define EYE	SENSOR_2

#define SXMOTOR		OUT_A
#define EYEMOTOR	OUT_B
#define DXMOTOR		OUT_C

#define DOWN	REV
#define UP	FWD

//#define FULLTIME 100
#define XMAX 60
#define YMAX 100
// this can be done only into QC
// this is VERY large array!!!
char light[YMAX][XMAX];

int 
main ()
{
  int x, y, l, c;

  SetSensor (EYE, SENSOR_TYPE_LIGHT, SENSOR_MODE_RAW);
  SensorActive (EYE);

  getc();
  PlaySound(0);
      
  for (x = 0; x < XMAX; x++)
    {
      LCDPrintn (x);
      if ((x%10)==0) PlaySound(1);
      // move right with a 2/100 sec. step
      MotorSet (4, FWD, SXMOTOR);
      MotorSet (4, REV, DXMOTOR);
      Wait (2);
      MotorSet (7, BRK, SXMOTOR);
      MotorSet (7, BRK, DXMOTOR);
      
      // Move the light sensor down to the blocking position
      // adding 10/100s to the correct time
      MotorSet (1, DOWN, EYEMOTOR);
      Wait (YMAX + 5);

      MotorSet (1, UP, EYEMOTOR);
      HiTimerSet (0, YMAX);
      while ((y = HiTimerGet (0) - 1) >= 0)
	{
	  l = 255-(SensorValue (EYE)-674);
	  light[y][x]=l;
	}
      MotorSet (7, BRK, EYEMOTOR);
    }

  // wait a char on the RCX to start
  while (getc () != ONOFF)
      {
      IROn ();
      PlaySound (0);
      // wait a char from IR
      while (!IRReady ());
      c = IRReceive ();
      IRSend (XMAX);
      IRSend (YMAX);
      
      for (y = YMAX-1; y >=0; y--)
	{
	  while (!IRReady ());
	  c = IRReceive ();
	  PlaySound (0);

	  for (x = 0; x < XMAX; x++)
	    {
	      IRSend (light[y][x]);
	    }
	}
      IROff ();
    }

  
  return 0;
}
