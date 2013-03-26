/* Copyright 01/28/05 Sun Microsystems, Inc. All Rights Reserved
** @(#)wtime.c 1.3 05/01/28 SMI
*/

#include <sys/time.h>

double wtime()
{
    hrtime_t nsec;

    /*-- Nanosecond timer under Solaris --*/

    nsec = gethrtime();

    return(((double)nsec)*1.0e-09);
}

double wtime_()
{
    return(wtime());
}

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/processor.h>
#include <sys/procset.h>
#include <stdlib.h>

extern int pbind_(int*);

int pbind_(int* cpu)
{
    int retval=processor_bind(P_PID, P_MYID, *cpu, NULL);
    if (retval != 0)
        fprintf(stderr,"processor_bind to processor %d failed: %s\n", 
                *cpu, strerror(errno));
    return(retval);
}

void compute_set_(double *tmr)
{
    double testtime = 3.0;
    char *s;

    s = getenv("SP_COLLECTOR_TEST_TIMER");
    if( s ) {
        testtime = atof(s);
        if (testtime < 1.0)
            testtime = 1.0;
    }
    *tmr = testtime;
}


