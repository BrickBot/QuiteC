// sensor.c

#include "qc.h"

typedef struct {
    char type;
    char mode;
    short raw;
    short value;
    char boolean;
  } sensor_t;
  
static sensor_t sensor[3];

void
SetSensor (int numsensor, char type, char mode)
{
  sensor[numsensor].type = type;
  sensor[numsensor].mode = mode;
}

short
SensorValue (int numsensor)
{
  __rcall2 (0x14c0, 0x1000 | numsensor, (short) &sensor[numsensor]);
  return sensor[numsensor].value;
}


short
SensorRaw (int numsensor)
{
  __rcall2 (0x14c0, 0x1000 | numsensor, (short) &sensor[numsensor]);
  return sensor[numsensor].raw;
}

char
SensorBoolean (int numsensor)
{
  __rcall2 (0x14c0, 0x1000 | numsensor, (short) &sensor[numsensor]);
  return sensor[numsensor].boolean;
}