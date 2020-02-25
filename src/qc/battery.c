// battery.c

#include "qc.h"

// NOTE: the value is taken directly from the A/D conversion
//   you can use this value if you want to know if a motor require too load
//   value is in mV
//   alkaline battery read is ~9000, rechargeable battery ~7200

short
RCXBattery (void)
{
  short mv;

  __rcall2 (0x29f2, 0x4001, (short) &mv);
  return mv * 43988 / 1560;
}
