/* Copyright 02/04/2000 Sun Microsystems, Inc. All Rights Reserved */

#include <stdio.h>
#include <stdlib.h>
#include "stopwatch.h"

/* Portable random number generator defined below.  Taken from ANSI C by  *
 * K & R.  Not a great generator, but fast, and good enough for my needs. */

#define IA 1103515245u
#define IC 12345u
#define IM 2147483648u

void	masksig();

static unsigned int current_random = 1;

static	int
my_irand (int imax)
{
/* Create a random integer between 0 and imax, inclusive.  i.e. [0..imax] */ 
	int ival;

	/* Use overflow to wrap */
	current_random = current_random * IA + IC;
	ival = current_random & (IM - 1);  /* Modulus */

	ival = (int) ((float) ival * (float) (imax + 0.999) / (float) IM);
	return(ival);
}
 
#define	N	6000000

int
fitos(int n)
{
	int i, k, retv;
	int max;
	hrtime_t        start;
	hrtime_t        vstart;

	start = gethrtime();
	vstart = gethrvtime();

	/* Log the event */
	wlog("start of fitos", NULL);

	if(n <= 0) n = 1;
	max = N * n;

	do {
		for (current_random=1, i=retv=k=0; i < max; i++) {
			retv += my_irand(100);
			k += (current_random & (IM - 1)) >= (1 << 22);
		}
	} while(start+testtime*1e9 > gethrtime());
	(void) fprintf(stderr, "\t\t%d out of a total of %d >= 2^22 (%d)\n", k, max, retv);

	whrvlog( (gethrtime() - start), (gethrvtime() - vstart),
		"fitos", NULL);

	return 0;
}
