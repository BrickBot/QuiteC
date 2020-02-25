BINPREFIX= h8300-hms-
BINDIR	 = ../../bin/
LIBDIR	 = ../../lib/
INCDIR	 = ../../include/
CFLAGS	 = -O3 -Wall -W -Wunused -fno-builtin -fomit-frame-pointer
LFLAGS   = -T$(LIBDIR)rcx.lds -u__start --relax

# programs

CC = $(BINDIR)$(BINPREFIX)gcc
AS = $(BINDIR)$(BINPREFIX)as
AR = $(BINDIR)$(BINPREFIX)ar
LD = $(BINDIR)$(BINPREFIX)ld 

# pattern rules

%.o: %.c %.h
	$(CC) $(CFLAGS) -I$(INCDIR) -c $*.c
%.o: %.s
	$(AS) $*.s -o $*.o
%.s: %.c
	$(CC) $(CFLAGS) -I$(INCDIR) -S $*.c
%.a: 
	$(AR) rc $*.a $(filter %.o,$^)
%.srec: %.o
	$(LD) $(LFLAGS) -o $*.srec $(filter %.o,$^) -L$(LIBDIR)
	
#######################################################################
	