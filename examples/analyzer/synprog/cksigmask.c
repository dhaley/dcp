/* Copyright 02/04/2000 Sun Microsystems, Inc. All Rights Reserved */

#include "defs.h"
#if OS(Solaris)

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/lwp.h>
#include <dlfcn.h>

#ifdef HWC
#include <libcpc.h>
#include <errno.h>
cpc_event_t	sample;
cpc_event_t	previous_sample;
static	int	no_previous_sample = 1;

void start_hwc(void);

#endif

/*
 * In first call to either routine, find libc's _sigprocmask --
 * if libthread is * linked, the call will be otherwise intercepted,
 * and return the libthread notion of the mask, not the real one
 */
static	void	(*sigprocmask_p)();
static	int	init_done = 0;
static	void	initcksig();
void	masksig();

/* check the LWP signal mask to ensure that SIGPROF and SIGEMT are not masked */
void
check_sigmask()
{
	sigset_t	olwpset;
	char	buf[1024];

	/* find real _sigprocmask, if necessary */
	if(init_done == 0) {
	    initcksig();
	}

	/* fetch the current mask */
	sigprocmask_p(0, NULL, &olwpset);

	/* check the bits for SIGPROF and SIGEMT */
	if ( sigismember( &olwpset, SIGPROF ) ) {
	    sprintf(buf, "**ERROR** SIGPROF masked in LWP %d\n", _lwp_self() );
	    fprintf (stderr, buf);
	}
	if ( sigismember( &olwpset, SIGEMT ) ) {
	    sprintf(buf, "**ERROR** SIGEMT masked in LWP %d\n", _lwp_self() );
	    fprintf (stderr, buf);
	}

#ifdef HWC
	if (cpc_take_sample(&sample) == -1) {
	    if(no_previous_sample == 0) {
		/* HWC sampling has stopped working */
		(void) sprintf(buf, "**ERROR** HWC sampling failed: %s\n",
			strerror(errno));
		fprintf (stderr, buf);
	    }
	} else {
	    /* check the new sample against the old */
	    if(no_previous_sample == 0) {
		if( (sample.ce_pic[0] == previous_sample.ce_pic[0])
			&& (sample.ce_pic[1] == previous_sample.ce_pic[1]) ) {
		    /* the counters haven't moved */
		    sprintf(buf, "**ERROR** HWC counters haven't moved pic[0] = %12lld, [1] = %12lld\n",
			sample.ce_pic[0],
			sample.ce_pic[1]);
		    fprintf(stderr, buf);
		} else {
		    /* counters have moved */
		    sprintf(buf, "  HWC counters moved to pic[0] = %12lld, [1] = %12lld\n",
			sample.ce_pic[0],
			sample.ce_pic[1]);
		    fprintf(stderr, buf);
	 	}
	    }
	    /* update previous_sample */
	    previous_sample = sample;
	    no_previous_sample = 0;
	}
#endif
}

/* mask SIGPROF and SIGEMT for the current LWP */
void
masksig()
{
	sigset_t        olwpset;

	/* find real _sigprocmask, if necessary */
	if(init_done == 0) {
	    initcksig();
	}

	/* clear the signal mask for SIGPROF and SIGEMT */
	sigprocmask_p(0, NULL, &olwpset);
	sigaddset(&olwpset, SIGPROF);
	sigaddset(&olwpset, SIGEMT);
	sigprocmask_p(SIG_SETMASK, &olwpset, NULL);
}

static void
initcksig()
{
	char	buf[1024];

	void *dlh = dlopen( "libc.so.1", RTLD_NOLOAD);
	sigprocmask_p = (void (*)())dlsym( dlh, "_sigprocmask");
	if(sigprocmask_p == NULL) {
	    char *e = dlerror();
	    if(e != NULL) {
		e = "unknown error";
	    }
	    sprintf( buf, "**ERROR** can't find _libc_sigprocmask in libc.so.1: %s\n", e);
	    fprintf(stderr, buf);
	    abort();
	}

	init_done = 1;

#ifdef HWC
	if (cpc_take_sample(&previous_sample) == -1) {
	    /* HWC counting isn't working */
	    sprintf(buf, "  HWC counters not enabled: %s\n",
		strerror(errno));
	    fprintf(stderr, buf);
	} else {
	    fprintf(stderr, "  HWC counters enabled\n");
	    no_previous_sample = 0;
	}
#endif
}

#endif /* OS(Solaris) */
