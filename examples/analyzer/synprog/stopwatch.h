/* Copyright 02/04/2000 Sun Microsystems, Inc. All Rights Reserved */

#ifndef _STOPWATCH_
#define _STOPWATCH_

#include "defs.h"

#if OS(Linux)
#include <time.h>
typedef    int     processorid_t;
typedef long long      hrtime_t;
typedef struct timespec timespec_t;
extern hrtime_t gethrtime();
extern hrtime_t gethrvtime();
#endif /* OS(Linux) */

#include <sys/time.h>

extern double testtime;
char	*prtime (time_t *t);
char	*prdelta(struct timeval t);
void	wlog(char *, char *);
void	whrlog(hrtime_t delta, char *, char *);
void	whrvlog(hrtime_t delta, hrtime_t vdelta, char *, char *);

typedef	struct stopwatch {
	double	sum;		/* in nanoseconds */
	double	sumsq;		/* in (nanoseconds ** 2)  */
	double	last;		/* in nanoseconds */
	hrtime_t	begin;
	hrtime_t	start;
	hrtime_t	tempus;
	hrtime_t	delta;
	hrtime_t	min;
	hrtime_t	max;
	int	count;
	char	*name;
} stopwatch_t;

stopwatch_t *stpwtch_alloc(char *, int);

void	stpwtch_calibrate();
void	stpwtch_start(stopwatch_t *);
void	stpwtch_stop(stopwatch_t *);
void	stpwtch_print(stopwatch_t *);

#endif
