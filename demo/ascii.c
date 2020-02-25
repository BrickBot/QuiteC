#include <qc.h>

char example[]=" ---=== THE QUICK BROWN FOX JUMPS OVER THE LAZY DOGS === the quick brown fox jumps over the lazy dogs ===---";

int main()
{
	int i;
	
	while(!keypressed())
	
	for(i=0;i<strlen(example);i++)
	{
		LCDPrints(example+i);
		Wait(18);
	}
	
	return 0;
}
	

