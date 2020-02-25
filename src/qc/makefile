all: libqc.a

include ../common.mak
	
#######################################################################

libqc.a: battery.o init.o ir.o keyb.o lcd.o qc.o rcall.o sensor.o timer.o conio.o memcpy.o memset.o strcpy.o strcmp.o strlen.o rand.o
	$(AR) rc libqc.a *.o 
	copy *.a ..\..\lib
	copy *.h ..\..\include
