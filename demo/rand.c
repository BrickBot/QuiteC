#include <qc.h>

// mstimer 0-99ms

int main()
{
	int sec=0,flag=1,k;
	
	while(!keypressed()) //getc()!=ONOFF)
	{
		k=MsTimerGet()/10;
		if (k==0)
		{
			if (flag==1) sec++;
			flag=0;
		}
		else
			flag=1;
	
		LCDPrintn(sec);
	}
	return 0;
}