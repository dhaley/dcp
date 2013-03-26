/* Copyright 2002 Sun Microsystems, Inc. All Rights Reserved */

#include "defs.h"

#if OS(Solaris)
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/lwp.h>
#include <signal.h>
#include <siginfo.h>
#include <strings.h>
#include <dlfcn.h>

#ifdef SOLARIS	/* the thread model, not the OS */
#include <thread.h>
#endif
#ifdef POSIX
#include <pthread.h>
#endif

static void	initcksig();
static int	init_done = 0;
static void	(*sigprocmask_p)();

int
check_sigmask( int n ) {
	sigset_t	oset;
	int		flag = 0;
	char		sigbuf[256];
	char		buf[256];
	int		tid;
	lwpid_t		lwpid;

	if ( !init_done ) {
	    initcksig();
	    init_done = 1;
	}

	lwpid = _lwp_self();

#ifdef SOLARIS
	tid = (int) thr_self();
#else
#ifdef POSIX
	tid = (int) pthread_self();
#else
	tid = -1;
#endif
#endif
	sigbuf[0] = 0;

#ifdef SOLARIS
	thr_sigsetmask(0, NULL, &oset);
#else
	pthread_sigmask(0, NULL, &oset);
#endif	
	if ( sigismember( &oset, SIGPROF ) ) {
	    flag = 1;
	    strcat( sigbuf, "SIGPROF(t) " );
	}
	if ( sigismember( &oset, SIGEMT ) ) {
	    flag = 1;
	    strcat( sigbuf, "SIGEMT(t) " );
	}
	sigprocmask_p(0, NULL, &oset);
	if ( sigismember( &oset, SIGPROF ) ) {
	    flag = 1;
	    strcat( sigbuf, "SIGPROF(l) " );
	}
	if ( sigismember( &oset, SIGEMT ) ) {
	    flag = 1;
	    strcat( sigbuf, "SIGEMT(l) " );
	}
	if ( flag ) {
	    sprintf( buf, "**ERROR** masked signals (%d) t@%d, l@%d: %s\n",
		n, tid, lwpid, sigbuf );
	    fprintf(stderr, buf);
#if 0
	    abort();
#endif
	}

	return flag;
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
	char		buf[256];

	void *dlh = dlopen( "libc.so.1", RTLD_NOLOAD);
	sigprocmask_p = (void (*)())dlsym( dlh, "_libc_sigprocmask");
	if(sigprocmask_p == NULL) {
	    /* this will fail on Solaris 10 */
	    sigprocmask_p = (void (*)())dlsym( dlh, "_sigprocmask");
	    if(sigprocmask_p == NULL) {
		char *e = dlerror();
		if(e == NULL) {
		    e = "unknown error";
		}
		sprintf( buf, "**ERROR** can't find _libc_sigprocmask or _sigprocmask in libc.so.1: %s\n", e);
		fprintf(stderr, buf);
		abort();
	    }
	}
	init_done = 1;
}
#endif /* OS(Solaris) */
