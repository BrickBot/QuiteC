#include <qc.h>

short GetSP(void);
__asm__ ("
        .section .text
_GetSP:
        mov.w r7,r0
        rts
        ");


int main()
{
        LCDPrintn(GetSP());
        getc();
        return 0;
}
        
