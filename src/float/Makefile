include ../common.mak
	
#######################################################################

libfloat.a: addsf3.o cmpsf2.o divsf3.o expandsf.o fixsfsi.o floatsisf.o joinsf.o mulsf3.o negsf2.o normalsf.o startsf.o
	$(AR) rc libfloat.a $^
	copy *.a ..\..\lib
	