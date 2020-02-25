#include <qc.h>

int main()
{
	while (!keypressed())
	  LCDPrintn(*(char*)0xefcf);
	return 0;
}