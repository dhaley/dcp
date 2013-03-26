/* Copyright 02/04/2000 Sun Microsystems, Inc. All Rights Reserved */

#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
#include "stopwatch.h"

static	void	so_burncpu();

int
so_cputime()
{
	wlog("start of so_cputime", NULL);

	/* put a memory leak in here */
	(void) malloc(13);

	fprintf(stderr, "so_burncpu @ 0x%08x\n", (unsigned int )so_burncpu);
	so_burncpu();

	wlog("end of so_cputime", NULL);
	return 13;
}

#if COMPILER(SUN)
#pragma init (so_init)
#else /* COMPILER(SUN) */
void so_init() __attribute__ ((constructor));
#endif /* COMPILER(SUN) */

void
so_init()
{
	fprintf(stderr, "so_init executed\n");
}

/*	so_burncpu - loop to use a bunch of user time */
void
so_burncpu()
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
		"so_burncpu", NULL);
}
