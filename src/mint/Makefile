all: libmint.a

include ../common.mak
	
#######################################################################

libmint.a: divhi3.o divsi3.o modhi3.o modsi3.o mulhi3.o mulsi3.o udivhi3.o udivsi3.o umodhi3.o umodsi3.o 
	$(AR) rc libmint.a $^
	copy *.a ..\..\lib
	