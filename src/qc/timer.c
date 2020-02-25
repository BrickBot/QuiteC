// timer.c

#include "qc.h"

// there a are 4 low resolution timer that count up and rollover 
// time are in ms
short
TimerGet (short num)
{
  return async.timers[num] * 10;
}

void
TimerClear (short num)
{
  async.timers[num] = 0;
}


// there a are 10 high resolution timer that count down to zero and stop
// time are in ms
short
HiTimerGet (short num)
{
  return async.task_wakeup[num];
}

void
HiTimerSet (short num, short value)
{
  async.task_wakeup[num] = value;
}

// wait some time
void
Wait (short ms)
{
  async.task_wakeup[0] = ms;
  while (async.task_wakeup[0] > 0)
    if (keypressed ()) // if you press a key exit from wait
      break;
}