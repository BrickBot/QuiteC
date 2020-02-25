@echo off
rem 
rem Only file name, NO EXTENSION
rem 
..\bin\h8300-hms-gcc -c -I ..\include %1.c -O3 -Wall -W -Wunused -fno-builtin -fomit-frame-pointer
..\bin\h8300-hms-ld -o %1.srec %1.o -L..\lib -lqc -lfloat -lmint -u__start -T ..\lib\rcx.lds
