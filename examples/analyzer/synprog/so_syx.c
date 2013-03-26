/* Copyright 02/04/2000 Sun Microsystems, Inc. All Rights Reserved */

#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
#include "stopwatch.h"

static	void	sx_burncpu();

int
sx_cputime()
{
	wlog("start of sx_cputime", NULL);

	/* put a memory leak in here */
	(void) malloc(13);

	fprintf(stderr, "sx_burncpu @ 0x%08x\n", (unsigned int)sx_burncpu);
	sx_burncpu();

	wlog("end of sx_cputime", NULL);
	return 13;
}

#if COMPILER(SUN)
#pragma init (sx_init)
#else
void sx_init() __attribute__ ((constructor));
#endif

void
sx_init()
{
	fprintf(stderr, "sx_init executed\n");
}

/*	sx_burncpu - loop to use a bunch of user time */
void
sx_burncpu()
{
	int	j;	/* temp value for loop */
	volatile float	x;	/* temp variable for f.p. calculation */
	hrtime_t	start;
	hrtime_t	vstart;

	start = gethrtime();
	vstart = gethrvtime();

        do {
        	x = 0.0;
		for(j=0; j<100000; j++) {
			x = x + 1.0;
		}
	} while(start+testtime*1e9 > gethrtime());

	whrvlog(gethrtime()-start, gethrvtime()-vstart,
		"sx_burncpu", NULL);
}
