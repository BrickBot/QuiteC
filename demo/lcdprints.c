#include <qc.h>

char example[]=" ---=== WELCOME TO THE WONDERFUL RCX LEGO MINDSTORMS, THIS IS THE QC SYSTEM ===--- ";

int main()
{
	int i,l=strlen(example);

	while(!keypressed())
		
	for(i=0;i<l;i++)
	{
		LCDPrints(example+i);
		Wait(30);
	}
	return 0;
}
	
	