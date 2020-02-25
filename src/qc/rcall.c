// rcall.c
/*
- H8 gcc C function:
	r0=func(r0,r1,r2,stack,stack)
	
	r0,r1,r2 are parameters
	r3 is temp value can be not saved 
	r4,r5 are register var and must be saved
	r6 is used as an offset from stack
	r7 is the stack pointer
	
	
- RCX rom funzion:
	r6=rom(r6,stack,stack,stack,stack)
*/

  
__asm__ ("
	  .section .text
	  .global ___rcall0
	  ___rcall0:
	  push r6
	  jsr @r0
	  mov.w r6,r0
	  pop r6
	  rts
");

__asm__ ("
	  .section .text
	  .global ___rcall1
	  ___rcall1:
	  push r6
	  mov.w r1,r6
	  jsr @r0
	  mov.w r6,r0
	  pop r6
	  rts
");


__asm__ ("
	  .section .text
	  .global ___rcall2
	  ___rcall2:
	  push r6
	  push r2
	  mov.w r1,r6
	  jsr @r0
	  mov.w r6,r0
	  adds #0x2,r7
	  pop r6
	  rts
");

__asm__ ("
	  .section .text
	  .global ___rcall3
	  ___rcall3:
	  push r6
	  mov.w @(0x4,r7),r3
	  push r3
	  push r2
	  mov.w r1,r6
	  jsr @r0
	  mov.w r6,r0
	  adds #0x2,r7
	  adds #0x2,r7
	  pop r6
	  rts
");


__asm__ ("
	  .section .text
	  .global ___rcall4
	  ___rcall4:
	  push r6
	  mov.w @(0x6,r7),r3
	  push r3
	  mov.w @(0x6,r7),r3
	  push r3
	  push r2
	  mov.w r1,r6
	  jsr @r0
	  mov.w r6,r0
	  add.b #0x6,r7l
	  addx #0x0,r7h
	  pop r6
	  rts
");
