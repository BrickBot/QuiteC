##
## qc - the independent LEGO Mindstorms C compiler
## Makefile - allows you to keep the upper hand
## (c) 2000 by Ferrara Francesco <ferrara.francesco@tiscalinet.it>    
##
all:
	cd float 
	make
	cd ..
	cd mint
	make
	cd ..
	cd qc
	make
	cd ..

clean:
	cd float 
	del *.o *.bak *.a 
	cd ..
	cd mint
	del *.o *.bak *.a 
	cd ..
	cd qc
	del *.o *.bak *.a 
	cd ..
	del *.bak
	