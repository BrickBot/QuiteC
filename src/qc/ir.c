// ir.c

#include "qc.h"

char _echotxchar = 0;
char _lasttxchar = 0;

// void IRSend(char c);
//
// Send a byte with IR interface
// very RAW not RCX opcode dependent
// you can use HyperTerminal
// remember that IR tower switch off 2-3 seconds after last char sent!

__asm__ ("
        .section .text
        .global _IRSend
_IRSend:    
        push r6
        push r4
    
txloop: mov.w   #__echotxchar,r4      ;point at the status byte
        btst    #0,@r4              ;if echo not expected, check if tx ready
        beq     txq2

        mov.b   @0xdc:8,r2l         ;echo expected, grab the status register
        and.b   #0x38,r2l           ;was there an error?
        beq     txq3                ;if not, check for a real char

        mov.b   @0xdc:8,r2l         ;grab the status register again
        and.b   #0xc7,r2l           ;clear error bits
        mov.b   r2l,@0xdc:8

        bclr    #0,@r4              ;fixme: just clear echo expected for now

        bra     txq2                ;and check if tx ready

txq3:   btst    #6,@0xdc:8          ;check the rdrf flag
        beq     txloop              ;if zero, we're not ready

        mov.b   @__lasttxchar,r3h     ;grab the expected echo char
        mov.b   @0xdd:8,r3l         ;grab the byte
        bclr    #6,@0xdc:8          ;clear the rdrf flag

        bclr    #0,@r4              ;fixme: just clear echo expected for now
                                    ;       and drop through to tx check
;       cmp     r3h,r3l             ;is the echoed char the same?
;       bne     rxq2                ;if not, indicate false

txq2:   btst    #7,@0xdc:8          ;check the tdre flag
        beq     txloop              ;if zero, we're not ready

tx2:    mov.b   r1l,@__lasttxchar    ;save for echo compare
        mov.w   #__echotxchar,r4
        bset    #0,@r4              ;indicate echo expected

        mov.w   #0x0913,r2          ;set up the ir carrier for tx
        mov.b   r2h,@0xd0:8
        mov.b   r2l,@0xd1:8
        mov.b   #0x1a,r2h
        mov.b   r2h,@0xd2:8
       
        mov.b   r0l,@0xdb:8         ;send the byte
        bclr    #7,@0xdc:8          ;clear the tdre flag
        
        pop r4
        pop r6
        rts
");


// char IRReceive (void);
//
// give you a char in IR read buffer
// warning: check before if char is present in buffer with IRReady!

__asm__ ("
    .section .text
    .global _IRReceive
_IRReceive:    
    push r6

    mov.w   #0x0,r0        ;clear the high byte of result
    mov.b   @0xdd:8,r0l    ;grab the byte
    bclr    #6,@0xdc:8     ;clear the rdrf flag

    pop r6
    rts
");

// short IRReady (void);
//
// 0 or 1 if a char is present in the read buffer

__asm__ ("
    .section .text
    .global _IRReady
_IRReady:    
    push r6
    
    mov.w   #0x0000,r0          ;preload the false result

    mov.w   #__echotxchar,r1     ;point at the echo status

    mov.b   @0xdc:8,r2l         ;grab the status register
    and.b   #0x38,r2l           ;was there an error?
    beq     rxq3                ;if not, check for a real char

    mov.b   @0xdc:8,r2l         ;grab the status register again
    and.b   #0xc7,r2l           ;clear error bits
    mov.b   r2l,@0xdc:8

    bclr    #0,@r1              ;fixme: just clear echo expected for now

    bra     rxq2                ;and indicate false

rxq3:
    btst    #6,@0xdc:8          ;check the rdrf flag
    beq     rxq2                ;if zero, we're not ready

    btst    #0,@r1              ;we have a char, is echo expected?
    beq     rxq1                ;if not indicate ready with a char

rxq4:
    mov.b   @__lasttxchar,r3h    ;grab the expected echo char
    mov.b   @0xdd:8,r3l         ;grab the byte
    bclr    #6,@0xdc:8          ;clear the rdrf flag

    bclr    #0,@r1              ;fixme: just clear echo expected for now
                                ;       and don't worry about the char

;   cmp     r3h,r3l             ;is the echoed char the same?
;   bne     rxq2                ;if not, indicate false

    bra     rxq2                ;indicate false now

rxq1:
    mov.w   #0x0001,r0          ;make result true
rxq2:
    pop     r6
    rts
");

// Print a short with sign without leading zeros
void 
IRPrintn(short n)
{
	char digit[5];
	short i;
	short flag=1;
	
	if (n<0)
	{
		IRSend('-');
		n=-n;
	}
	for(i=0;i<5;i++)
	{
		digit[4-i]='0'+(n%10);
		n/=10;
	}
	for(i=0;i<5;i++)
	{
		if (digit[i]!='0' || flag==0 || i==4)
		{
			flag=0;
			IRSend(digit[i]);
		}
	}
}

// Print a string
void
IRPrints(char *str)
{
	short i=0;
	
	while (str[i]!=0 && i<80)
		IRSend(str[i++]);
}

// Turn on IR signal at 38Khz
void IROn (void)
{
	*(char*)0xffda	=0;
	*(char*)0xffd0	=0x09;
	*(char*)0xffd1	=0x13;
	*(char*)0xffd2	=0x1a;
	*(char*)0xffd8	=0x00;
	*(char*)0xffd9	=0xcf;
	*(char*)0xffdc	=0x00;  
	*(char*)0xffda	=0x30;
}

// Turn off IR signal
// Warning: before switching off signal wait 30-50 ms from 
// your last sent char
void IROff (void)
{
	*(char*)0xffd0	=0x00;
	*(char*)0xffd1	=0x50;
	*(char*)0xffd2	=0x1a;
}