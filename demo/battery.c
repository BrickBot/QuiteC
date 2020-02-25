#include <qc.h>

int main()
{
	do
	{
	  LCDPrintn(RCXBattery());
	} while (!keypressed());
	return 0;
}