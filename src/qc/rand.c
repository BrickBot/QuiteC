// rand.c

#include "qc.h"

static unsigned long _seed;

void srand(unsigned long seed)
{
	_seed=seed^0x1668db7b;
}

unsigned short rand(void)
{
	_seed=69069L*_seed+1;
	return _seed&0xffff;
}


