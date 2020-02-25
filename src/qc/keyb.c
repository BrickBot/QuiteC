// keyb.c

#include "qc.h"

char
getc (void)
{
  short butonoff;
  short butother;
  short i;

  do
    {
      __rcall2 (0x29f2, 0x4000, (short) &butonoff);
      __rcall2 (0x1fb6, 0x3000, (short) &butother);
    }
  while (butonoff == 0x02 && butother == 0);
  for (i = 0; i < 1000; i++)
    if (keypressed ())
      i = 0;

  if (butonoff == 0x00)
    return ONOFF | butother;
  return butother;
}

short
keypressed (void)
{
  short butonoff;
  short butother;

  __rcall2 (0x29f2, 0x4000, (short) &butonoff);
  __rcall2 (0x1fb6, 0x3000, (short) &butother);

  if (butonoff == 0x00)
    return ONOFF | butother;
  return butother;
}