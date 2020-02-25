// qc.h
// Version 1.04

/***********************************************************************************/
extern void __rcall4 (short a, short p0, short p1, short p2, short p3);
extern void __rcall3 (short a, short p0, short p1, short p2);
extern void __rcall2 (short a, short p0, short p1);
extern void __rcall1 (short a, short p0);
extern void __rcall0 (short a);



/***********************************************************************************/
typedef struct
  {
    short serial;
    short timers[4];
    short clock_minutes;
    short shutoff_minutes;
    short task_wakeup[10];
    short motor_wakeup[3];
  }
async_t;
extern async_t async;
extern char dispatch[6];

/***********************************************************************************/
#define OUT_A	0
#define OUT_B	1
#define OUT_C	2

#define FWD	1
#define REV	2
#define BRK	3
#define FLT	4

#define ONOFF 	8
#define VIEW	2
#define PRGM	4
#define RUN	1

#define SENSOR_1 0
#define SENSOR_2 1
#define SENSOR_3 2

#define SENSOR_TYPE_RAW    0
#define SENSOR_TYPE_TOUCH  1
#define SENSOR_TYPE_TEMP   2
#define SENSOR_TYPE_LIGHT  3
#define SENSOR_TYPE_ROT    4

#define SENSOR_MODE_RAW    0x00
#define SENSOR_MODE_BOOL   0x20
#define SENSOR_MODE_EDGE   0x40
#define SENSOR_MODE_PULSE  0x60
#define SENSOR_MODE_PCT    0x80
#define SENSOR_MODE_DEGC   0xa0
#define SENSOR_MODE_DEGF   0xc0
#define SENSOR_MODE_ANGLE  0xe0

#define SOUND_CLICK		0
#define SOUND_DOUBLE_BEEP	1
#define SOUND_DOWN		2
#define SOUND_UP		3
#define SOUND_LOW_BEEP		4
#define SOUND_FAST_UP		5

#define LCD_STANDING         0x3006
#define LCD_WALKING          0x3007
#define LCD_SENSOR_0_VIEW    0x3008
#define LCD_SENSOR_0_ACTIVE  0x3009
#define LCD_SENSOR_1_VIEW    0x300a
#define LCD_SENSOR_1_ACTIVE  0x300b
#define LCD_SENSOR_2_VIEW    0x300c
#define LCD_SENSOR_2_ACTIVE  0x300d
#define LCD_MOTOR_0_VIEW     0x300e
#define LCD_MOTOR_0_REV      0x300f
#define LCD_MOTOR_0_FWD      0x3010
#define LCD_MOTOR_1_VIEW     0x3011
#define LCD_MOTOR_1_REV      0x3012
#define LCD_MOTOR_1_FWD      0x3013
#define LCD_MOTOR_2_VIEW     0x3014
#define LCD_MOTOR_2_REV      0x3015
#define LCD_MOTOR_2_FWD      0x3016
#define LCD_DATALOG          0x3018
#define LCD_DOWNLOAD         0x3019
#define LCD_UPLOAD           0x301a
#define LCD_BATTERY          0x301b
#define LCD_RANGE_SHORT      0x301c
#define LCD_RANGE_LONG       0x301d
#define LCD_ALL              0x3020

/***********************************************************************************/
static inline void
LCDPrintn (short number)
{
  __rcall3 (0x1ff2, 0x3001, number, 0x3002); 	// LCDNumber
  __rcall0 (0x27c8);				// LCDRefresh
}

/*
 * code=3006: standing figure
 * code=3007: walking figure
 * code=3008: sensor 0 view selected
 * code=3009: sensor 0 active
 * code=300a: sensor 1 view selected
 * code=300b: sensor 1 active
 * code=300c: sensor 2 view selected
 * code=300d: sensor 2 active
 * code=300e: motor 0 view selected
 * code=300f: motor 0 backward arrow
 * code=3010: motor 0 forward arrow
 * code=3011: motor 1 view selected
 * code=3012: motor 1 backward arrow
 * code=3013: motor 1 forward arrow
 * code=3014: motor 2 view selected
 * code=3015: motor 2 backward arrow
 * code=3016: motor 2 forward arrow
 * code=3018: datalog indicator, multiple calls add 4 quarters clockwise
 * code=3019: download in progress, multiple calls adds up to 5 dots to right
 * code=301a: upload in progress, multiple calls removes up to 5 dots from left
 * code=301b: battery low
 * code=301c: short range indicator
 * code=301d: long range indicator
 * code=3020: all segments
 * All codes set bits in @ef43[10] array to affect display
 * Display must be refreshed for changes to become visible
 */
static inline void
LCDShow (short code)
{
  __rcall1 (0x1b62, code);
}

static inline void
LCDHide (short code)
{
  __rcall1 (0x1e4a, code);
}

/*
 * Set lcd number (short code, short value, short pointcode)
 *
 * code=3001: Set lcd main number signed
 *   Set main number on display to signed value, with no leading zeros
 *   If value > 9999, displayed value is 9999
 *   If value < -9999, displayed value is -9999
 * code=3017: Set lcd program number
 *   Set program number on display to value, use pointcode=0
 *   If value < 0, no value is displayed
 *   If value > 0, no value is displayed
 *   Pointcode is ignored, no real need to set to zero
 * code=301f: Set lcd main number unsigned
 *   Set main number on display to unsigned value, with leading zeros
 *   Value is unsigned, so it is never less than 0
 * For 3001, 301f:
 *   pointcode=3002: no decimal point
 *   pointcode=3003: 000.0 format
 *   pointcode=3004: 00.00 format
 *   pointcode=3005: 0.000 format
 */
static inline void
LCDNumber (short pointcode, short value, short code)
{
  __rcall3 (0x1ff2, code, value, pointcode);
}

static inline void
LCDClear (void)
{
  __rcall0 (0x27ac);
}

static inline void
LCDRefresh (void)
{
  __rcall0 (0x27c8);
}

static inline void
MotorSet (short power, short mode, short motor)
{
  __rcall3 (0x1a4e, 0x2000 | motor, mode, power);
}

static inline void
PlaySound (short sound)
{
  __rcall2 (0x299a, 0x4004, sound);

}

static inline void
PlayTone (short freq, short duration)
{
  __rcall3 (0x327c, 0x1773, freq, duration);
}

static inline void
SensorPassive (short sensor)
{
  __rcall1 (0x19c4, 0x1000 | sensor);
}

static inline void
SensorActive (short sensor)
{
  __rcall1 (0x1946, 0x1000 | sensor);
}

static inline void
IRLong (void)
{
  __rcall1 (0x3250, 0x1770);
}

static inline void
IRShort (void)
{
  __rcall1 (0x3266, 0x1770);
}

static inline unsigned char
MsTimerGet(void)
{
	return *(unsigned char*)0xefd0;
}

////////////////////////////////////////////////////////////////////////////////////////////////

void
  PowerOff (void);

void
  WaitSound (void);

void
  SetSensor (int numsensor, char type, char mode);

short
  SensorValue (int numsensor);

short
  SensorRaw (int numsensor);

char
  SensorBoolean (int numsensor);

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

char
  getc (void);

short
  keypressed (void);

void
  LCDStand (void);

void
  LCDRun (void);

void
  LCDPrints (char *str);
  
short
  RCXBattery (void);

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
