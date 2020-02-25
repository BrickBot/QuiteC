#include <qc.h>

int main()
{
	getc();
	// Warning: turn on IRTower (sending a char), before pressing a key on RCX
	IROn();
	IRPrintn(-587);
	IRPrintn(50000);
	Wait(50); // ir transmit last byte wait some time
	IROff();
	return 0;
}