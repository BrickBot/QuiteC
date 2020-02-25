#include <qc.h>

#define CENTRE SENSOR_1
#define EYE SENSOR_2
#define BUMPER SENSOR_3

#define STEER OUT_A
#define RADAR  OUT_B
#define MOTOR OUT_C

#define AVA REV
#define IND FWD

#define DX FWD
#define SX REV
#define CE 0
int posizioneSTEER=SX;
int angle=-1;

#define FULLCIRCLE 215
	
void centraSTEER()
{
	if (posizioneSTEER!=CE)
	{
		if (posizioneSTEER==SX)
		  MotorSet(0,DX,STEER);
		else 
		  MotorSet(0,SX,STEER);
		while (!SensorBoolean(CENTRE));
		MotorSet(7,BRK,STEER);
		posizioneSTEER=CE;
	}
}

void radar(void)
{
	static int max,tempangle;
	static int state=0;
	switch (state)
	{
	case 0:	HiTimerSet(0,FULLCIRCLE+5);
		state=1;
		break;
	case 1: MotorSet(7,REV,RADAR);
		if (HiTimerGet(0)<=0)
			state=2;
		break;
	case 2:	HiTimerSet(0,FULLCIRCLE);
		max=0;
		state=3;
		break;
	case 3: MotorSet(7,FWD,RADAR);
		if (max<=SensorValue(EYE))
		{
			tempangle=HiTimerGet(0);
			max=SensorValue(EYE);
		}
		if (HiTimerGet(0)==angle)
			PlayTone(880,1);
		if (HiTimerGet(0)<=0)
		{
			angle=tempangle;
			state=0;
		}
		break;
	}
}
	
void pause(int ms)
{
	HiTimerSet(1,ms);
	while (HiTimerGet(1)>0) 
	  radar();
}

void turn(int dir,int time)
{
	MotorSet(0,dir,STEER);
	pause(time);
	MotorSet(7,BRK,STEER);
	posizioneSTEER=dir;
}
					
int main()
{
	SetSensor(STEER,SENSOR_TYPE_TOUCH,SENSOR_MODE_BOOL);
	SensorPassive(CENTRE);
	
	SetSensor(BUMPER,SENSOR_TYPE_TOUCH,SENSOR_MODE_BOOL);
	SensorPassive(BUMPER);
	
	SetSensor(EYE,SENSOR_TYPE_LIGHT,SENSOR_MODE_PCT);
	SensorActive(EYE);
	
	while (getc()!=ONOFF)
	{
		LCDRun();		
		
		centraSTEER();	
		MotorSet(7,AVA,MOTOR);
		
		while (!keypressed())
		{
			radar();
			if (angle>FULLCIRCLE*3/4)
			{
				turn(SX,40);
				pause(20);
				centraSTEER();
			}
			if (angle<FULLCIRCLE*1/4)
			{
				turn(DX,40);
				pause(20);
				centraSTEER();
			}
			
			if (!SensorBoolean(BUMPER))
			{
				MotorSet(7,BRK,MOTOR);
				if (angle<=100)
					turn(SX,40);
				else
					turn(DX,40);
				pause(60);
				
				MotorSet(7,IND,MOTOR);
				pause(60);
				
				centraSTEER();
				MotorSet(7,BRK,MOTOR);
				pause(60);
				MotorSet(7,AVA,MOTOR);
			}
			LCDPrintn(RCXBattery());
		}
		LCDStand();
		MotorSet(7,BRK,MOTOR);
		MotorSet(7,BRK,RADAR);

		getc();
	}
	return 0;
}
	
	
	
	
	
