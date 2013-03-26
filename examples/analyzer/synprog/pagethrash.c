/* Copyright 02/04/2000 Sun Microsystems, Inc. All Rights Reserved */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "stopwatch.h"

/*=======================================================*/
/*	pagethrash - allocate some memory, and thrash around in it */
int
pagethrash(int thrashmb)
{
	unsigned long	size;
	unsigned long 	loc;
	void	*space;
	long	npages;
	long	i;
	int	pagesize;
	char	buf[1024];
	stopwatch_t	*w;
	hrtime_t	start;
	hrtime_t	vstart;

	start = gethrtime();
	vstart = gethrvtime();

	/* Log the event */
	wlog("start of pagethrash", NULL);

	/* Start a stopwatch */
	w = stpwtch_alloc("pagethrash", 0);

	/* compute the size */
	size = thrashmb*1024*1024;

	pagesize = getpagesize();
	space = malloc(size + pagesize);

	if(space == NULL) {
		fprintf(stderr,
			"\tpagethrash failed; can't get %ld bytes.\n",
			 size);
		exit(1);
	}

	/* round address to page boundary */
	loc = (((unsigned long)space + pagesize -1) & (~(pagesize-1)));
	npages = size /pagesize;

	/* touch all the pages to force them in */
	for (i = 0; i < npages; i ++) {
		stpwtch_start(w);
		*(int *)(loc + i*pagesize) = i;
		stpwtch_stop(w);
	}

	/* now free up the space */
	free(space);

	/* print the timing results */
	stpwtch_print(w);
	free( (void *) w);

	sprintf(buf, "pagethrash: %ld pages", npages);
	whrvlog(gethrtime()-start, gethrvtime()-vstart,
		buf, NULL);

	return 0;
}
