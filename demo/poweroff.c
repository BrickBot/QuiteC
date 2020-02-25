#include <qc.h>

int main()
{
    int i;

    getc();
    PowerOff();
    getc();
    for (i = 0; i < 1000; i++)
	LCDPrintn(i);
    return 0;
}
