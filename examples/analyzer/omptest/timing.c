/* Copyright 01/10/07 Sun Microsystems, Inc. All Rights Reserved
** @(#)timing.c 1.7 07/01/10 SMI
*/

#include "defs.h"

#include <stdio.h>
#include <stdlib.h>

#if OS(Linux)
typedef long long  hrtime_t;
extern             hrtime_t gethrtime();
#else   /* OS(Linux) */
#include <sys/time.h>
#endif  /* OS(Linux) */

extern  int get_clock_rate(void);
extern  void initarray_(), timerdo_();

int
getmhz_()
{
	return get_clock_rate();
}

void compute_set_(int *n, int *m, double *a, double *b, double *c)
{
	hrtime_t t;
	double testtime = 3.0;
	char *s;

	s = getenv("SP_COLLECTOR_TEST_TIMER");
	if( s ) {
		testtime = atof(s);
		if (testtime < 1.0)
			testtime = 1.0;
	}
	initarray_(n,a,b,c);
	t = gethrtime();
	*m = 10;
	timerdo_(n,m,a,b,c);
	t = gethrtime() - t;
	*m *= testtime * 1e9 / t;
	printf("compute_set: loop_count=%d\n", *m);
}
