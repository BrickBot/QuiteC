// init.c

#include "qc.h"

__asm__ (
	  ".section .init\n\t"
	  ".global __start\n"
	  "__start:\n\t"
	  "push r0\n\t"
	  "push r1\n\t"
	  "push r2\n\t"
	  "push r3\n\t"
	  "jsr __init\n\t"
	  "pop r3\n\t"
	  "pop r2\n\t"
	  "pop r1\n\t"
	  "pop r0\n\t"
	  "rts\n\t"
	  ".string \"Do you byte, when I knock?\""
);

extern int main (void);
extern char _bss_start, _end;
char dispatch[6];
async_t async;

void
_init (void)
{
  char *p;

  /* Clear the .bss data */
  for (p = &_bss_start; p != &_end; p++)
    *p = 0;

  __rcall2 (0x3b9a, (short) &async, (short) &dispatch[0]);	/* Init Timer */
  __rcall0 (0x2964);		/* Init Power */
  __rcall0 (0x1498);		/* Init Sensor */
  __rcall0 (0x1aba);		/* Init Button */
  LCDStand ();

  main ();

  __rcall0 (0x3ed4);		/* Shutdown Timer */

  *(char *) 0xffcc = 1;
  (*(void (**)(void)) 0) ();
}
