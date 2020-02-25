#include <qc.h>

#define EYE SENSOR_2

int main()
{
	int minmax=0;
	
	SetSensor (EYE, SENSOR_TYPE_LIGHT, SENSOR_MODE_RAW);
	SensorActive (EYE);
	Wait(200);
	
	while(!keypressed())
	{
		int v;
		
		v=SensorValue(EYE);
		//LCDPrintn((v-310)*10/66);
		LCDPrintn(minmax);
		if (v>minmax) minmax=v;
		// max min light
		// 316 - 962
		// max min light from tube pointed to a figure (reflex) 
		// 674 - 951
		// max min light from tube pointed to a figure (reflex) (sun)
		// 631 - 926
		// First version of visor
		// 18  - 87
		Wait(50);
	}
	return 0;
}