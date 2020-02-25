/* qc.c */

#include "qc.h"

// void PowerOff(void)
// 
// switch to low power mode your program REMAIN RESIDENT
// The CPU resume from the exact point of the call to PowerOff!!!

void PowerOff(void)
{
	LCDClear();
	LCDRefresh();
	
	PlaySound(0);
	WaitSound();
	
	__rcall0 (0x2a62); /* Shutdown Power */
	__rcall2 (0x3b9a, (short) &async, (short) &dispatch[0]);	/* Init Timer */
	__rcall0(0x1498); /* Init Sensor */
	
	PlaySound(0);
	WaitSound();
}

void
WaitSound (void)
{
  char playing;

  do
    {
      __rcall2 (0x3ccc, 0x700c, (short) &playing);
    }
  while (playing);
}


