/* QuiteC 1.04 */

/***************************************************************************************/
/* LCD *********************************************************************************/
/***************************************************************************************/

void
  LCDPrintn (short number);

void
  LCDPrints (char *str);

void
  LCDStand (void);

void
  LCDRun (void);

void
  LCDShow (short code);

void
  LCDHide (short code);

void
  LCDClear (void);

void
  LCDRefresh (void);  

void
  LCDNumber (short pointcode, short value, short code);

/***************************************************************************************/
/* MOTOR *******************************************************************************/
/***************************************************************************************/

void
  MotorSet (short power, short mode, short motor);

/***************************************************************************************/
/* SOUND *******************************************************************************/
/***************************************************************************************/

void
  PlaySound (short sound);

void
  PlayTone (short freq, short duration);

void
  WaitSound (void);

/***************************************************************************************/
/* SENSOR ******************************************************************************/
/***************************************************************************************/

void
  SensorPassive (short sensor);

void
  SensorActive (short sensor);

void
  SetSensor (int numsensor, char type, char mode);

short
  SensorValue (int numsensor);

short
  SensorRaw (int numsensor);

char
  SensorBoolean (int numsensor);

/***************************************************************************************/
/* INFRARED ****************************************************************************/
/***************************************************************************************/

void
  IRLong (void);

void
  IRShort (void);

short
  IRReady (void);

char
  IRReceive (void);

void
  IRSend (char c);

void
  IRPrintn (short n);

void
  IRPrints (char *str);

void
  IROn (void);

void
  IROff (void);

/***************************************************************************************/
/* UTILITY *****************************************************************************/
/***************************************************************************************/

void
  PowerOff (void);

short
  RCXBattery (void);

/***************************************************************************************/
/* TIMER *******************************************************************************/
/***************************************************************************************/

unsigned char
  MsTimerGet (void);
  
short
  HiTimerGet (short num);

void
  HiTimerSet (short num, short value);

short
  TimerGet (short num);

void
  TimerSet (short num, short value);

void
  TimerClear (short num);

void
  Wait (short ms);

/***************************************************************************************/
/* KEYBOARD ***************************************************************************/
/***************************************************************************************/

char
  getc (void);

short
  keypressed (void);

/***************************************************************************************/
/* STDLIB *****************************************************************************/
/***************************************************************************************/

void
 *memcpy (void *dest, const void *src, short size);

void
 *memset (void *s, int c, short n);

char
 *strcpy (char *dest, const char *src);

int
  strlen (const char *s);

int
  strcmp (const char *s1, const char *s2);
  
void 
  srand(unsigned long seed);

unsigned short 
  rand(void);