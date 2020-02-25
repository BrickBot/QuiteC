#include <qc.h>

int main()
{
	char c;
	int i;
	
	while (getc()!=ONOFF)
	{
		IROn();
		while(!IRReady());
		c=IRReceive();
		PlaySound(2);
		for(i=0;i<10;i++)
			IRSend('0'+i);
		IROff();		
	}
	return 0;
}