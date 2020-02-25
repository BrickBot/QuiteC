// lcd.c

#include "qc.h"

// Show the standing man
void
LCDStand (void)
{
  __rcall1 (0x1b62, 0x3006);
  LCDRefresh ();
}

// Show a running man
void
LCDRun (void)
{
  __rcall1 (0x1b62, 0x3007);
  LCDRefresh ();
}