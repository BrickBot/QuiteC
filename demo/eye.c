#include <qc.h>

#define EYE SENSOR_1
#define MOTOR OUT_A

#define MAX 140
short light[MAX];

int main()
{
	short i,j,t;
	char c;
	
	SetSensor(EYE,SENSOR_TYPE_LIGHT,SENSOR_MODE_RAW);
	SensorActive(EYE);
	
	getc();
	
	MotorSet(7,REV,MOTOR);
	Wait(220);
	MotorSet(7,FWD,MOTOR);
	
	HiTimerSet(0,MAX);
	
	while ((t=HiTimerGet(0))>0)
		light[t]=SensorRaw(EYE);
	MotorSet(7,BRK,MOTOR);
	
	IROn();
	for(i=0;i<MAX;i+=32)
	{
		while(!IRReady());
		c=IRReceive();
		Wait(30);
		for(j=0;j<32;j++)
		{
			
			IRPrintn(i+j);
			IRPrints(",");
			IRPrintn(light[i+j]);
			IRPrints("\n\r");
			
		}
		Wait(30);
	}
	IROff();
	PlaySound(3);
	return 0;
}

			
			
	
	



