/* Copyright 04/24/06 Sun Microsystems, Inc. All Rights Reserved */
/* synprog.c - synthetic program to use for testing performance tools */

#include	"defs.h"
#include	<sys/types.h>
#include        <sys/param.h>
#include	<sys/wait.h>
#include        <sys/ucontext.h>
#include	<stdlib.h>
#include	<stdio.h>
#include	<errno.h>
#include	<signal.h>
#include	<unistd.h>
#if OS(Solaris)
#include	<sys/processor.h>
#include	<strings.h>
#include        <procfs.h>
#else /* OS(Solaris) */
#include	<string.h>
#endif /* OS(Solaris */

#include	<dlfcn.h>
#include        <fcntl.h>
#include	"stopwatch.h"

int	get_ncpus();
int	get_clock_rate();

void    acct_init(char *);      /* initialize accounting */
void	commandline(char *);	/* routine execute a scenario */

void	forkcopy(char *, int);	/* fork copy of self to run string */
void	forkchild(char *);	/* fork child to run string */
void	reapchildren(void);	/* reap all children */
void	reapchild(int);		/* reap a child after getting SIGCLD */
void	check_sigmask();	/* check that SIGPROF and SIGEMT are not masked */
void	masksig();		/* real code to mask SIGPROF and SIGEMT */

hrtime_t	progstart;
hrtime_t	progvstart;

#if OS(Linux)
void (*sigset(int sig, void (*disp)(int)))(int);
#define ITIMER_REALPROF ITIMER_REAL
/* Linux needs to have this defined for RTLD_NEXT and RTLD_DEFAULT */
/* If the first argument of `dlsym' or `dlvsym' is set to RTLD_NEXT */
# define RTLD_NEXT      ((void *) -1l)
/* If the first argument to `dlsym' or `dlvsym' is set to RTLD_DEFAULT */
# define RTLD_DEFAULT   ((void *) 0)
#endif /* OS(Linux) */

FILE	*fid;
double testtime = 3.0;
static char acct_file[128];
static char new_name[128];
static char child_name[128];

/* descendant process tracking */
static unsigned syn_fork=0;
static unsigned syn_exec=0;
static unsigned syn_combo=0;

/* various behavior routines */
int	bounce(int);		/* bounce with a->b->a->b-> ... */
int	callso(int);		/* so load test */
int	callsx(int);		/* alternate so load test */
int	correlate(int);		/* test correlation with profiling */
int	cputime(int);		/* use a bunch of user cpu time (fp) */
int	doabort(int);		/* force a SEGV by dereferencing NULL */
int	dousleep(int);		/* loop with a usleep call */
int	endcases(int);		/* test various code construct endcases */
int	fitos(int);		/* test various code construct endcases */
int	gpf(int);		/* show gprof fallacy */
int	hrv(int);		/* gethrvtime calls */
int	icputime(int);		/* use a bunch of user cpu time (long) */
int	iofile(int);		/* do operations on a temporary file */
int	iotest(int);		/* do various io system calls */
int	ldso(int);		/* use a bunch of time in ld.so */
int	masksignals(int);		/* mask the SIGEMT and SIGPROF signals */
int	muldiv(int);		/* do integer multiply/divide for a time */
int	naptime(int);		/* sleep for a time */
int	pagethrash(int);	/* thrash around in memory */
int	recurse(int);		/* recursion test */
int	recursedeep(int);	/* deep recursion test */
int	sigtime(int);		/* use a bunch of time in a signal handler */
int	systime(int);		/* use a bunch of system time */
int	tailcallopt(int);	/* tail call optimization test */
int	underflow(int);		/* force underflow arithmetic */

int     itimer_realprof(int);   /* mess with itimer ITIMER_REALPROF */
int     sigprof(int);           /* mess with SIGPROF sigaction */
int     sigprofh(int);          /* mess with SIGPROF handler */
int     do_chdir(int);          /* do a chdir() */
int     do_exec(int);           /* do an exec() call */
int     do_popen(int);          /* do a popen() call */
int     do_system(int);         /* do a system() call */
int     do_forkexec(int);       /* do a fork()+exec() call combo */
int     do_vforkexec(int);      /* do a vfork()+exec() call combo */


/* lookup table for behavior scripts */
struct	scripttab {
	char	*name;
	int (*function)(int);
	char	*acctname;
	int	param;
};

/* the default script */
static char DEFAULT_COMMAND[] = 
	"icpu.md.cpu.rec.recd.dousl.gpf.fitos.uf.ec.tco.b.nap.sig.sys.so.sx.so" ;

struct	scripttab	scripttab[] = {
	{"abt", doabort, "doabort", 0},
	{"dousl", dousleep, "dousleep", 0},
	{"b", bounce, "bounce", 0},
	{"c", correlate, "correlate", 0},
        {"chdir", do_chdir, "chdir", 0},
        {"chdirX", do_chdir, "chdir", -1},
	{"cpu", cputime, "cputime", 0},
	{"ec", endcases, "endcases", 0},
        {"exec", do_exec, "exec", 0},
        {"execX", do_exec, "do_exec", -1},
	{"fitos", fitos, "fitos", 0},
	{"gpf", gpf, "gpf", 0},
	{"hrv", hrv, "hrv", 0},
	{"icpu", icputime, "icputime", 0},
	{"iofile", iofile, "iofile", 0},
	{"iotest", iotest, "iotest", 0},
        {"itimer", itimer_realprof, "itimer", 1},
        {"itimer0", itimer_realprof, "itimer", 0},
	{"ldso", ldso, "ldso", 0},
	{"masksig", masksignals, "masksig", 0},
	{"md", muldiv, "muldiv", 0},
	{"nap", naptime, "naptime", 0},
	{"pg", pagethrash, "pagethrash", 32},
        {"popen", do_popen, "popen", 0},
        {"popenX", do_popen, "popen", -1},
	{"rec", recurse, "recurse", 50},
	{"recd", recursedeep, "<Truncated-stack>", 500},
	{"so", callso, "callso", 0},
	{"sx", callsx, "callsx", 0},
	{"sig", sigtime, "sigtime", 0},
        {"sigprof", sigprof, "sigprof", 1},
        {"sigprof0", sigprof, "sigprof", 0},
        {"sigprofh", sigprofh, "sigprofh", 1},
        {"sigprofh0", sigprofh, "sigprofh", 0},
	{"sys", systime, "systime", 0},
        {"system", do_system, "system", 0},
        {"systemX", do_system, "do_system", -1},
	{"tco", tailcallopt, "tailcallopt", 0},
	{"uf", underflow, "underflow", 0},
        {"forkexec", do_forkexec, "forkexec", 0},
        {"vforkexec", do_vforkexec, "vforkexec", 0},
	{NULL, NULL, NULL, 0}
};

int
main(int argc, char **argv)
{
	int	i;
	int	ncpus;
#if OS(Solaris)
	int	cpuid;
#endif /* OS(Solaris)*/	
	hrtime_t	start;
	hrtime_t	vstart;
        char    *name;
	char	buf[1024];
        char    arglist[4096];

	progstart = gethrtime();
	progvstart = gethrvtime();

	name = getenv("SP_COLLECTOR_TEST_TIMER");
	if( name ) {
		testtime = atof(name);
		if (testtime <= 0)
			testtime = 1.0;
	}

        name = getenv("_SP_NAME");
        if ( (name==NULL) || (strlen(name) == 0) ) {
            strcpy(acct_file,"synprog.acct");
            /*printf("_SP_NAME undefined (for founder): %s\n", acct_file);*/
        } else {
            strcpy(acct_file,name);
            /*printf("_SP_NAME=\"%s\" (for descendant)\n", acct_file);*/
        }

        strcpy(arglist, argv[0]);
        for (i=1; i<argc; i++) {
                strcat(arglist, " ");
                strcat(arglist, argv[i]);
        }
        
	sprintf(buf, "%s run", argv[0]);
	wlog(buf, NULL);

	ncpus = get_ncpus();
        acct_init(acct_file);

	/* Start a timer */
	start = gethrtime();
	vstart = gethrvtime();

#ifndef NO_MS_ACCT
	stpwtch_calibrate();
#endif

	if(argc == 1) {
		commandline(DEFAULT_COMMAND);
	} else {
                i = 2;
                while (i < argc) {
                    forkcopy(argv[i], i-1);
                    i++;
                }

		/* do the last one ourself */
		commandline(argv[1]);
	}
	reapchildren();

	whrvlog( (gethrtime() - start), (gethrvtime()-vstart),
		buf, NULL);

	return 0;
}

/* acct_init: initialize accounting
 */

void
acct_init (char *acct_file)
{
	fid = fopen(acct_file, "w");
	if(fid == NULL) {
		fprintf(stderr, "Open of %s for output failed: %s\n",
			acct_file, strerror(errno));
		exit(1);
	}

	fprintf(fid, "MHz: %d\n", get_clock_rate() );

	fprintf(fid, "X   Incl. Total  Incl. CPU  Name\n");
	fflush(fid);

	/* set up to reap any children */
	(void) sigset(SIGCHLD, reapchild);

	/* verify the signal mask */
#if  OS(Solaris)
	check_sigmask();
#endif /*  OS(Solaris) */
}

/* commandline -- process a command line string:
 *	verbs are separated by a . character; each verb is looked-up
 *	in a table, and the routine to process it, and argument fetched.
 *	the routine is called.
 */
void
commandline(char *cmdline)
{
	char	*p;
	char	*j;
	char	prevj;
	struct	scripttab	*k;
	char	buf[1024];
	hrtime_t	pstart;
	hrtime_t	pvstart;
	hrtime_t	pend;
	hrtime_t	pvend;
	hrtime_t	start;
	hrtime_t	vstart;

	start = gethrtime();
	vstart = gethrvtime();

	/* Log the event */
	wlog(" Begin commandline", cmdline);

	p = cmdline;

	while( (*p) != 0 ){
		/* find the terminator for this verb (a . or NULL) */
		j = p;
		while( ((*j) != 0) && ((*j) != '.') ) {
			j++;
		}

		prevj = *j;
		*j = 0;

		/* now look up the phase in the table */
		for (k = &scripttab[0]; ; k++) {
			if(k->name == NULL) {
				break;
			}
			if(strcmp(p, k->name) == 0) {
				/* found a match */
				pstart = gethrtime();
				pvstart = gethrvtime();
				(k->function)(k->param);
				pend = gethrtime();
				pvend = gethrvtime();
				fprintf(fid,
			"X   %6.3f        %6.3f       %s\n",
			(double)(pend - pstart)/(double)1000000000. ,
			(double)(pvend - pvstart)/(double)1000000000. ,
			k->acctname);
				fflush(fid);
#if  OS(Solaris)
				/* verify the signal mask */
				check_sigmask();
#endif /*  OS(Solaris) */

				break;
			}
		}

		if(k->name == NULL) {
			sprintf(buf, "++ ignoring `%s'\n", p);
			fprintf(stderr, buf);
		}

		/* continue processing */
		*j = prevj;
		p = j;
		if(prevj != 0) {
			p ++;
		}
	}

	whrvlog( (gethrtime() - start), (gethrvtime() - vstart),
		"commandline", cmdline);
}

/* forkcopy -- fork a copy to run a script */
void
forkcopy(char *script, int child)
{
	int	child_pid;

	/* Log the event */
	wlog("forking copy ... ", script);

        sprintf(child_name, "%s_f%d", acct_file, ++syn_fork);

	/* fork a new process */
	child_pid = fork();
	if (child_pid < 0) {

		/* error, could not fork */
		fprintf(stderr, "forkcopy: fork failed--error %d\n", errno);
		exit(1);

	} else if(child_pid == 0) {
                syn_fork=syn_exec=syn_combo=0; /* reset for new child line */

                strcpy(acct_file,child_name);
                /*printf("_SP_NAME=\"%s\" (for fork-child)\n", acct_file);*/
                acct_init(acct_file);
                
		/* execute the script */
		commandline(script);

		/* reap the child's descendants */
		reapchild(0);
		exit(0);
	}

        fprintf(stderr,"child process %d forked by %d.\n",
                child_pid, (int)getpid());
}

void
forkchild(char * cmdline)
{
	stopwatch_t	*prog;
	char	mbuf[1024];

	/* Start a stopwatch */
	sprintf(mbuf, "%s pid[%d]" , "Synprog child", (int)getpid() );
	prog = stpwtch_alloc(mbuf, 0);

	/* process this child's command-line */
	commandline(cmdline);

	/* reap the child's descendants */
	reapchild(0);

	/* Stop print, and free the stopwatch */
	stpwtch_stop(prog);
	stpwtch_print(prog);
	free(prog);

	exit(0);
}

/* reap a child process, called in response to SIGCLD */
void
reapchild(int sig)
{
	int ret, status;

	ret = wait(&status);

	sigset(SIGCLD, reapchild);
}

/* reap all child processes prior to exit */
void
reapchildren()
{
	int status;

	/* wait for all children to exit */
	for(;;) {
		while(wait(&status) != -1) { };
		if(errno == ECHILD) {
			return;
		}
	}
}


/* =============================================================== */
/*	doabort -- force a SEGV */
int
doabort(int k)
{
	char	*nullptr = NULL;
	char	c;

	/* Log the event */
	wlog("start of doabort", NULL);

	/* and dereference a NULL */
	c = *nullptr;

	/* this should never be reached */
	return (int)c;
}

/* =============================================================== */
/*	dousleep -- loop with a usleep */
int
dousleep(int k)
{
	int	j;
	volatile double x;
	hrtime_t	start;
	hrtime_t	vstart;

	start = gethrtime();
	vstart = gethrvtime();

	/* Log the event */
	wlog("start of dousleep", NULL);

	do {
#if  OS(Solaris)
		usleep( (useconds_t) 20000);
#endif	/*  OS(Solaris) */
		x = 0.0;
		for(j=0; j<1000000; j++) {
			x = x + 1.0;
		}
	} while(start+testtime*1e9 > gethrtime());


	whrvlog( (gethrtime() - start),  (gethrvtime() - vstart),
		"dousleep", NULL);

	/* this should never be reached */
	return (int)0;
}

/* =============================================================== */
/*	correlate -- generate CPU use, correlated with profiling clock */

static void csig_handler(int);

int
correlate(int k)
{
	int	j;	/* temp value for loop */
	volatile float	x;	/* temp variable for f.p. calculation */
	hrtime_t	start;
	hrtime_t	vstart;
	struct itimerval tval;
        int retval;

	start = gethrtime();
	vstart = gethrvtime();

	/* Log the event */
	wlog("start of correlate", NULL);

	/* set up the signal handler */
	sigset(SIGALRM, csig_handler);

	/* set an itimer, to break out of the sleep loop */
	tval.it_value.tv_sec = 0;
	tval.it_value.tv_usec = 10000;
	tval.it_interval.tv_sec = 0;
	tval.it_interval.tv_usec = 10000;

	retval = setitimer(ITIMER_REAL, &tval, 0);
        if (retval!=0)
            fprintf(stderr, "setitimer(ITIMER_REAL) got %d returned: %s\n",
                retval, strerror(errno));

        do {
		x = 0.0;
		for(j=0; j<1000000; j++) {
			x = x + 1.0;
		}
		sleep(1);	/* relying on the timer to break out */
	} while(start+testtime*1e9 > gethrtime());

	/* now disable the itimer */
	tval.it_value.tv_sec = 0;
	tval.it_value.tv_usec = 0;
	tval.it_interval.tv_sec = 0;
	tval.it_interval.tv_usec = 0;

	retval = setitimer(ITIMER_REAL, &tval, 0);
        if (retval!=0)
            fprintf(stderr, "setitimer(ITIMER_REAL) got %d returned: %s\n",
                retval, strerror(errno));

	whrvlog( (gethrtime() - start),  (gethrvtime() - vstart),
		"correlate", NULL);
	return 0;
}

static void
csig_handler(int sig)
{
	return;
}

/* =============================================================== */
/*	cputime -- loop to use a bunch of user time (f.p.) */

int
cputime(int k)
{
	int	j;	/* temp value for loop */
	volatile float	x;	/* temp variable for f.p. calculation */
	hrtime_t	start;
	hrtime_t	vstart;

	start = gethrtime();
	vstart = gethrvtime();

	/* Log the event */
	wlog("start of cputime", NULL);

	do {
		x = 0.0;
		for(j=0; j<1000000; j++) {
			x = x + 1.0;
		}
	} while(start+testtime*1e9 > gethrtime());

	whrvlog( (gethrtime() - start),  (gethrvtime() - vstart),
		"cputime", NULL);
	return 0;
}

/* =============================================================== */
/*	icputime -- loop to use a bunch of user time (long) */

int
icputime(int k)
{
	int	j;	/* temp value for loop */
	volatile long	x;	/* temp variable for long calculation */
	hrtime_t	start;
	hrtime_t	vstart;

	start = gethrtime();
	vstart = gethrvtime();

	/* Log the event */
	wlog("start of icputime", NULL);

	do {
		x = 0;
		for(j=0; j<1000000; j++) {
			x = x + 1;
		}
	} while(start+testtime*1e9 > gethrtime());

	whrvlog( (gethrtime() - start),  (gethrvtime() - vstart),
		"icputime", NULL);
	return 0;
}

/* =============================================================== */
/*	hrv -- loop to do lots of gethrvtime calls */

int
hrv(int k)
{
	int	j;	/* temp value for loop */
	hrtime_t	start;
	hrtime_t	vstart;

	start = gethrtime();
	vstart = gethrvtime();

	/* Log the event */
	wlog("start of hrv", NULL);

	do {
		for(j=0; j<10000; j++) {
			(void) gethrvtime();
		}
	} while(start+testtime*1e9 > gethrtime());

	whrvlog( (gethrtime() - start),  (gethrvtime() - vstart),
		"hrv", NULL);
	return 0;
}

/* =============================================================== */
/*	ldso -- use up time in ld.so */

int
ldso(int k)
{
	hrtime_t	start;
	hrtime_t	vstart;
	int	j;	/* temp value for loop */

	start = gethrtime();
	vstart = gethrvtime();

	/* Log the event */
	wlog("start of ldso", NULL);

	do {
		for(j=0; j<10000; j++) {
			(void)dlsym(RTLD_DEFAULT, "nosuchfoo");
		}
	} while(start+testtime*1e9 > gethrtime());

	whrvlog( (gethrtime() - start),  (gethrvtime() - vstart),
		"ldso", NULL);
	return 0;
}

/* =============================================================== */
/*	masksignals -- debug aid -- call routine to mask SIGPROF and SIGEMT */

int
masksignals(int n)
{
	hrtime_t	start;
	hrtime_t	vstart;

	start = gethrtime();
	vstart = gethrvtime();

	/* Log the event */
#if  OS(Solaris)
	wlog("start of masksignals", NULL);

	masksig();
#endif /*  OS(Solaris) */

	whrvlog( (gethrtime() - start),  (gethrvtime() - vstart),
		"masksignals", NULL);
	return 0;
}

/* =============================================================== */
/*	muldiv -- loop to do a bunch of integer multiply and divide */

int
muldiv(int n)
{
	int i, j;
	volatile int k;

	hrtime_t	start;
	hrtime_t	vstart;

	start = gethrtime();
	vstart = gethrvtime();

	/* Log the event */
	wlog("start of muldiv", NULL);

	do {
	    for (i = 0; i< 1000; i++) {
		for (j = 0; j< 1000; j++) {
			k = j*i/(i+1.0);
		}
	    }
	} while(start+testtime*1e9 > gethrtime());

	whrvlog( (gethrtime() - start),  (gethrvtime() - vstart),
		"muldiv", NULL);

	return 0;
}


/* =============================================================== */
/*	underflow -- loop triggering arithmetic underflow */

int
underflow(int k)
{
	int	j;	/* temp value for loop */
	float	x,y;
	volatile float	z;
	hrtime_t	start;
	hrtime_t	vstart;

	start = gethrtime();
	vstart = gethrvtime();

	/* Log the event */
	wlog("start of underflow", NULL);

	do {
		x = 1.e-20;
		y = 1.e-20;
		for(j=0; j<50000; j++) {
			z = x * y;
		}
	} while(start+testtime*1e9 > gethrtime());

	whrvlog( (gethrtime() - start),  (gethrvtime() - vstart),
		"underflow", NULL);
	return 0;
}

/* =============================================================== */
/*	naptime -- spend time in the system sleeping */

int
naptime(int k)
{
	int i;
	hrtime_t	start;
	hrtime_t	vstart;

	start = gethrtime();
	vstart = gethrvtime();

	/* Log the event */
	wlog("start of naptime", NULL);
 
	if(k == 0) {
		k = testtime;
                if (k < 1) k = 1;
	}

	for (i = 0; i < k; i++) {
		sleep(1);
	}

	whrvlog( (gethrtime() - start),  (gethrvtime() - vstart),
		"naptime", NULL);
	return 0;
}

/* =============================================================== */
/*	recurse -- loop to show recursion */

int	real_recurse(int, int);	/* real routine to do recursion */

int
recurse(int k)
{
	hrtime_t	start;
	hrtime_t	vstart;

	start = gethrtime();
	vstart = gethrvtime();

	/* Log the event */
	wlog("start of recurse", NULL);

	if(k == 0) {
		k = 80;
	}
	(void) real_recurse(0, k);

	whrvlog( (gethrtime() - start),  (gethrvtime() - vstart),
		"recurse", NULL);
	return 0;
}

int
recursedeep(int k)
{
	hrtime_t	start;
	hrtime_t	vstart;

	start = gethrtime();
	vstart = gethrvtime();

	/* Log the event */
	wlog("start of recursedeep", NULL);

	if(k == 0) {
		k = 500;
	}
	(void) real_recurse(0, k);

	whrvlog( (gethrtime() - start),  (gethrvtime() - vstart),
		"recursedeep", NULL);
	return 0;
}

static	int	rec_count = 0;

int
real_recurse(int i, int imax)
{
	if(i == imax) {
		volatile float x;
		int j;
		hrtime_t end;
		for (end = gethrtime()+testtime*1e9; gethrtime() < end; ) {
		    x = 0.0;
		    for(j=0; j<10000000; j++) {
			 x = x + 1.0;
		    }
		}
		return rec_count;
	} else {
		real_recurse(i+1, imax);
		rec_count ++;
		return rec_count;
	}
}

/* =============================================================== */
/*	gpf -- simple example showing the gprof fallacy */

void	gpf_a(void);
void	gpf_b(void);
void	gpf_work(int);

int
gpf(int k)
{
	hrtime_t	start;
	hrtime_t	vstart;

	start = gethrtime();
	vstart = gethrvtime();

	/* Log the event */
	wlog("start of gpf", NULL);

	do {
		gpf_a();
		gpf_b();
	} while(start+testtime*1e9 > gethrtime());

	whrvlog( (gethrtime() - start),  (gethrvtime() - vstart),
		"gpf - total", NULL);
	return 0;
}

void
gpf_a()
{
	hrtime_t	start;
	hrtime_t	vstart;
	int	i;

	start = gethrtime();
	vstart = gethrvtime();

	for(i = 0; i < 9; i ++) {
		gpf_work(1);
	}

	whrvlog( (gethrtime() - start),  (gethrvtime() - vstart),
		"gpf_a -- 9 X gpf_work(1)", NULL);
}

void
gpf_b()
{
	hrtime_t	start;
	hrtime_t	vstart;

	start = gethrtime();
	vstart = gethrvtime();

	gpf_work(10);

	whrvlog( (gethrtime() - start),  (gethrvtime() - vstart),
		"gpf_b -- 1 X gpf_work(10)", NULL);
}

void
gpf_work(int amt)
{
	int	i;
	int	imax;

	imax = 4* amt * amt;

	for(i = 0; i < imax; i ++) {
		volatile float x;
		int j;
		x = 0.0;
		for(j=0; j<200000; j++) {
			 x = x + 1.0;
		}
	}
}

/* =============================================================== */
/*	bounce -- example of indirect recursion */

void	bounce_a(int, int);
void	bounce_b(int, int);

int
bounce(int k)
{
	hrtime_t	start;
	hrtime_t	vstart;

	start = gethrtime();
	vstart = gethrvtime();

	/* Log the event */
	wlog("start of bounce", NULL);

	if(k == 0) {
		k = 20;
	}

	do {
		bounce_a(0,k);
	} while(start+testtime*1e9 > gethrtime());

	whrvlog( (gethrtime() - start),  (gethrvtime() - vstart),
		"bounce", NULL);
	return 0;
}

void
bounce_a(int i, int imax)
{
	if(i == imax) {
		volatile float x;
		int j, k;
		x = 0.0;
		for(k=0; k < 8; k++) {
		    for(j=0; j<2000000; j++) {
			 x = x + 1.0;
		    }
		}
		return;
	} else {
		bounce_b(i, imax);
	}
}

void
bounce_b(int i, int imax)
{
	bounce_a(i+1, imax);
	return;
}

/* =============================================================== */
/*	sigtime -- spend time in a signal handler */

static void sigtime_handler(int);

int
sigtime(int k)
{
	hrtime_t	start;
	hrtime_t	vstart;

	start = gethrtime();
	vstart = gethrvtime();

	/* Log the event */
	wlog("start of sigtime", NULL);

	/* set up the signal handler */
	sigset(SIGHUP, sigtime_handler);

	do {
		kill(getpid(), SIGHUP);
	} while(start+testtime*1e9 > gethrtime());

	sigset(SIGHUP, SIG_DFL);

	whrvlog( (gethrtime() - start),  (gethrvtime() - vstart),
		"sigtime", NULL);
	return 0;
}

static void
sigtime_handler(int sig)
{
	int j;
	hrtime_t end;
	volatile int x;

	for (end = gethrtime()+testtime*1e9; gethrtime() < end; ) {
		x = 0;
		for(j=0; j<1000000; j++) {
			x = x + 1;
		}
        }

	return;
}


/* =============================================================== */
/*	systime -- spend time in a few system calls */
int
systime(int k)
{
	struct timeval ttime;
	double t;
	int j;
	hrtime_t	start;
	hrtime_t	vstart;
	hrtime_t	rstart;
	hrtime_t	rvstart;
	hrtime_t	end;
	hrtime_t	vend;

	t = testtime/4;
        if (t<1.0) t = 1.0;
	start = gethrtime();
	rstart = start;
	vstart = gethrvtime();
	rvstart = vstart;

	/* Log the event */
	wlog("start of systime", NULL);

	/* do gettimeofday calls */
	for (end = gethrtime()+t*1e9; gethrtime() < end; ) {
		for(j=0; j<30000; j++) {
			(void) gettimeofday(&ttime, NULL);
		}
	}

	end = gethrtime();
	vend = gethrvtime();
	whrvlog( (end - start),  (vend - vstart),
		"systime -- 10**6 gettimeofday", NULL);

	/* do gethrtime calls */
	start = gethrtime();
	vstart = gethrvtime();

	for (end = gethrtime()+t*1e9; gethrtime() < end; ) {
		(void) gethrtime();
	}

	end = gethrtime();
	vend = gethrvtime();
	whrvlog( (end - start),  (vend - vstart),
		"systime -- 10**6 gethrtime", NULL);

	/* do pairs of gethrtime calls */
	start = gethrtime();
	vstart = gethrvtime();

	for (end = gethrtime()+t*1e9; gethrtime() < end; ) {
		for(j=0; j<30000; j++) {
			(void) gethrtime();
			(void) gethrtime();
		}
	}

	end = gethrtime();
	vend = gethrvtime();
	whrvlog( (end - start),  (vend - vstart),
		"systime -- 10**6  pairs of gethrtime", NULL);

	/* do gethrvtime calls */
	start = gethrtime();
	vstart = gethrvtime();

	for (end = gethrtime()+t*1e9; gethrtime() < end; ) {
		for(j=0; j<30000; j++) {
			(void) gethrvtime();
		}
	}

	end = gethrtime();
	vend = gethrvtime();
	whrvlog( (end - start),  (vend - vstart),
		"systime -- 10**6 gethrvtime", NULL);

	whrvlog( (gethrtime() - rstart),  (gethrvtime() - rvstart),
		"systime", NULL);
	return 0;
}

/* =============================================================== */
/*	tailcallopt -- call routines that would be tail-call optimized when
 *		compiled with optimization
 */
void	tailcall_a(void);
void	tailcall_b(void);
void	tailcall_c(void);

int
tailcallopt(int n)
{
	hrtime_t	start;
	hrtime_t	vstart;

	start = gethrtime();
	vstart = gethrvtime();

	/* Log the event */
	wlog("start of tailcallopt", NULL);

	do {
		tailcall_a();
	} while(start+testtime*1e9 > gethrtime());

	whrvlog( (gethrtime() - start),  (gethrvtime() - vstart),
		"tailcallopt", NULL);
	return 0;
}

void
tailcall_a()
{
	volatile float x;
	int j;
	x = 0.0;
	for(j=0; j<4000000; j++) {
		 x = x + 1.0;
	}
	tailcall_b();
}

void
tailcall_b()
{
	volatile float x;
	int j;
	x = 0.0;
	for(j=0; j<4000000; j++) {
		 x = x + 1.0;
	}
	tailcall_c();
}

void
tailcall_c()
{
	volatile float x;
	int j;
	x = 0.0;
	for(j=0; j<4000000; j++) {
		 x = x + 1.0;
	}
}


int
itimer_realprof (int k)                 /* mess with itimer ITIMER_REALPROF */
{
	hrtime_t	start;
	hrtime_t	vstart;
        struct itimerval tval;
        int retval;

	start = gethrtime();
	vstart = gethrvtime();

	/* set an itimer */

        if (k != 0) {
            wlog("start of itimer_realprof", NULL);
            tval.it_interval.tv_sec = 1;
            tval.it_interval.tv_usec = 300000;
            tval.it_value = tval.it_interval;
        } else {
            wlog("start of itimer_realprof(0)", NULL);
            tval.it_interval.tv_sec = 0;
            tval.it_interval.tv_usec = 0;
            tval.it_value = tval.it_interval;
        }

	retval = setitimer(ITIMER_REALPROF, &tval, 0);
        if (retval!=0)
            fprintf(stderr, "setitimer(ITIMER_REALPROF) got %d returned: %s\n",
                retval, strerror(errno));

	whrvlog( (gethrtime() - start),  (gethrvtime() - vstart),
		"itimer_realprof", NULL);
	return 0;
}


static struct sigaction old_sigprof_handler;

static void sigprof_handler (int sig);
static void sigprof_sigaction (int sig, siginfo_t *sip, ucontext_t *uap);

int
sigprof(int k)
{
	hrtime_t	start;
	hrtime_t	vstart;
        struct sigaction act;

	start = gethrtime();
	vstart = gethrvtime();

	/* Log the event */
	wlog("start of sigprof", NULL);

        /* query current handler */
        if ( sigaction (SIGPROF, NULL, &act) == -1 ) {
            printf("\tFailed current sigaction query: %s\n", strerror(errno));
        } else {
            printf("\tCurrently installed sigaction 0x%p\n", act.sa_sigaction);
        }

        sigemptyset(&act.sa_mask);
        act.sa_flags = SA_RESTART|SA_SIGINFO;
        act.sa_sigaction = (void(*)(int,siginfo_t*,void*))sigprof_sigaction;

        if (k!=0) {
            /* install with deferral to original handler (if set) */
            if ( sigaction (SIGPROF, &act, &old_sigprof_handler) == -1 ) {
                printf("\tFailed to install sigprof_sigaction: %s\n", strerror(errno));
            }

            if (old_sigprof_handler.sa_sigaction == (void (*)(int, siginfo_t *, void *))SIG_DFL) {
                old_sigprof_handler.sa_sigaction = (void (*)(int, siginfo_t *, void *))SIG_IGN;
                printf("\tReplaced default sigprof handler with 0x%p\n",
                    act.sa_sigaction);
            } else {
                printf("\tReplaced sigprof handler 0x%p with 0x%p\n",
                    old_sigprof_handler.sa_sigaction, act.sa_sigaction);
            }
        } else {
            /* installed without deferral to any original handler */
            old_sigprof_handler.sa_sigaction = (void (*)(int, siginfo_t *, void *))SIG_IGN;
            if ( sigaction (SIGPROF, &act, NULL) == -1 ) {
                printf("\tFailed to install sigprof_sigaction: %s\n", strerror(errno));
            } else {
                printf("\tInstalled sigprof_sigaction 0x%p\n", act.sa_sigaction);
            }
        }

	whrvlog( (gethrtime() - start),  (gethrvtime() - vstart),
		"sigprof", NULL);
	return 0;
}

int
sigprofh(int k)
{
	hrtime_t	start;
	hrtime_t	vstart;
        struct sigaction act;

	start = gethrtime();
	vstart = gethrvtime();

	/* Log the event */
	wlog("start of sigprofh", NULL);

        /* query current handler */
        if ( sigaction (SIGPROF, NULL, &act) == -1 ) {
            printf("\tFailed current sigaction query: %s\n", strerror(errno));
        } else {
            printf("\tCurrently installed handler 0x%p\n", act.sa_handler);
        }

        sigemptyset(&act.sa_mask);
        act.sa_flags = SA_RESTART;
        act.sa_handler = sigprof_handler;

        if (k!=0) {
            /* install with deferral to original handler (if set) */
            if ( sigaction (SIGPROF, &act, &old_sigprof_handler) == -1 ) {
                printf("\tFailed to install sigprof_handler: %s\n", strerror(errno));
            }

            if (old_sigprof_handler.sa_handler == SIG_DFL) {
                old_sigprof_handler.sa_handler = SIG_IGN;
                printf("\tReplaced default sigprof handler with 0x%p\n",
                    act.sa_handler);
            } else {
                printf("\tReplaced sigprof handler 0x%p with 0x%p\n",
                    old_sigprof_handler.sa_handler, act.sa_handler);
            }
        } else {
            /* installed without deferral to any original handler */
            old_sigprof_handler.sa_handler = SIG_IGN;
            if ( sigaction (SIGPROF, &act, NULL) == -1 ) {
                printf("\tFailed to install sigprof_handler: %s\n", strerror(errno));
            } else {
                printf("\tInstalled sigprof_handler 0x%p\n", act.sa_handler);
            }
        }

	whrvlog( (gethrtime() - start),  (gethrvtime() - vstart),
		"sigprofh", NULL);
	return 0;
}

static void
sigprof_handler (int sig)
{
	int j;
	volatile int x;

        hrtime_t now = gethrtime();

        if (old_sigprof_handler.sa_handler == SIG_IGN) {
            whrvlog( now, 0, "sigprof_handler (ign)", NULL);
            for (j=0,x=0; j<1000000; j++) { x = x + 1; }
        } else {
            whrvlog( now, 0, "sigprof_handler (fwd)", NULL);
            for (j=0,x=0; j<1000000; j++) { x = x + 1; }
            /* forward signal to original handler */
            if (old_sigprof_handler.sa_flags&SA_SIGINFO)
                (old_sigprof_handler.sa_sigaction)(sig, NULL, NULL);
            else
                (old_sigprof_handler.sa_handler)(sig);
            printf("\tReturned from original sigprof handler!\n");
        }

	return;
}

static void
sigprof_sigaction (int sig, siginfo_t *sip, ucontext_t *uap)
{
	int j;
	volatile int x;

        hrtime_t now = gethrtime();

        if (old_sigprof_handler.sa_sigaction == (void (*)(int, siginfo_t *, void *))SIG_IGN) {
            whrvlog( now, 0, "sigprof_sigaction (ign)", NULL);
            for (j=0,x=0; j<1000000; j++) { x = x + 1; }
        } else {
            whrvlog( now, 0, "sigprof_sigaction (fwd)", NULL);
            for (j=0,x=0; j<1000000; j++) { x = x + 1; }
            /* forward signal to original handler */
            if (old_sigprof_handler.sa_flags&SA_SIGINFO)
                (old_sigprof_handler.sa_sigaction)(sig, sip, uap);
            else
                (old_sigprof_handler.sa_handler)(sig);
            printf("\tReturned from original sigprof sigaction!\n");
        }

	return;
}

#if 0

Need to consider various signal handler/sigaction scenarios:

1. A handler is already installed, and a new handler is being installed.
   (The original handler may be one of the defaults.)
2. A handler is already installed, and a sigaction is being installed.
3. A sigaction is already installed, and a new sigaction is being installed.
4. A sigaction is already installed, and a handler is being installed.

#endif

int
do_chdir (int k)                        /* switch to a new working directory */
{
	hrtime_t	start;
	hrtime_t	vstart;
        char           *workdir;
        char           *workdir0="/tmp";
        char           *workdir1="/";
        char            currworkdir[MAXPATHLEN];

	start = gethrtime();
	vstart = gethrvtime();

        if (k != 0) {
            wlog("start of do_chdir(X)", NULL);
            workdir=workdir1;
        } else {
            wlog("start of do_chdir", NULL);
            workdir=workdir0;
        }

        if (getcwd(currworkdir, sizeof(currworkdir)) == NULL) {
            fprintf(stderr,"old getcwd failed: %s\n", strerror(errno));
        } else {
            printf("old getcwd returned \"%s\"\n", currworkdir);
        }

        if (chdir(workdir) != 0) {
            fprintf(stderr,"chdir(\"%s\") failed: %s\n", workdir, strerror(errno));
        }

        if (getcwd(currworkdir, sizeof(currworkdir)) == NULL) {
            fprintf(stderr,"new getcwd failed: %s\n", strerror(errno));
        } else {
            printf("new getcwd returned \"%s\"\n", currworkdir);
        }
	whrvlog( (gethrtime() - start),  (gethrvtime() - vstart),
		"do_chdir", NULL);
	return 0;
}


int
do_exec (int k)                 /* do an exec() call */
{
        sprintf(new_name, "_SP_NAME=%s_x%d", acct_file, ++syn_exec);
        if (putenv(new_name)) {
            fprintf(stderr,"Failed to name child! %s\n", strerror(errno));
        }

        if (k >= 0) {
            wlog("about to exec", NULL);
            execl("./synprog", "synprog", "gpf.cpu.sx", NULL);
            wlog("exec failed!!!", NULL);
        } else {
            wlog("about to execX", NULL);
            execl("./no-such-file", "no-such-file", "gpf.cpu.sx", NULL);
            wlog("execX failed (as expected)", NULL);
        }

        return 0;
}

/* preloading libcollector to a setuid executable will fail! */
const char *cmdX="/random/crash_n_burn";
const char *cmd0="/bin/uptime";
const char *cmd1="/bin/echo hello world!";
const char *cmd2="/usr/bin/sleep 5";
const char *cmd3="/usr/bin/sleep 5; /bin/echo hello world!";
const char *cmd4="/usr/bin/sleep 2; /bin/echo hello world!; /usr/bin/sleep 2";
const char *cmd5="/bin/date; /bin/sleep 2; /bin/date; /bin/sleep 2; /bin/date";
const char *cmd6="w;w;w;w;w;w;w;w;w;w;w;w;w;w;w;w;w;w;w;w;w;w;w;w;w;w;w;w;w;w";
const char *cmd7="synprog";
const char *cmd8="synprog icpu.sx 2>&1";

int
do_popen (int k)                 /* do a popen() call */
{
        int ret;
        FILE *fd;
        char buf[BUFSIZ];
        const char *mode="r";

        /* XXXX popen() will temporarily vfork+exec() a new child */
        /* but there will be no accounting for it, unless it's synprog! */
        sprintf(new_name, "_SP_NAME=%s_c%d", acct_file, ++syn_combo);
        if (putenv(new_name)) {
            fprintf(stderr,"Failed to name child! %s\n", strerror(errno));
        }

	/* ignore reapchild to catch child here */
	(void) sigset(SIGCHLD, 0);

        if (k >= 0) {
            wlog("about to popen", NULL);
            fd=popen(cmd8,mode);
        } else {
            wlog("about to popenX!", NULL);
            fd=popen(cmdX,mode);
        }
        if (fd == NULL) {
            printf("do_popen failed: %s\n", strerror(errno));
        } else {
            printf("do_popen succeeded: fileno=%d\n", fileno(fd));
        }

        /* restore pre-popen environment */
        sprintf(new_name, "_SP_NAME=%s", acct_file);
        if (putenv(new_name)) {
            fprintf(stderr,"Failed to restore name! %s\n", strerror(errno));
        }

        if (fd != NULL) {
            while (fgets(buf, BUFSIZ, fd) != NULL)
                printf("&    %s", buf);

            if ((ret=pclose(fd)) == -1) {
                printf("do_popen pclose error: %s\n", strerror(errno));
            } else {
                printf("do_popen pclose returned %d\n", ret);
            }
        }

	/* set up to reap any children */
	(void) sigset(SIGCHLD, reapchild);

        return 0;
}

int
do_system (int k)                 /* do a system() call */
{
        int ret;

        /* XXXX system() will temporarily vfork+exec() a new child */
        /* but there will be no accounting for it, unless it's synprog! */
        sprintf(new_name, "_SP_NAME=%s_c%d", acct_file, ++syn_combo);
        if (putenv(new_name)) {
            fprintf(stderr,"Failed to name child! %s\n", strerror(errno));
        }

        if (k >= 0) {
            wlog("about to system", NULL);
            ret=system(cmd8);
        } else {
            wlog("about to systemX!", NULL);
            ret=system(cmd0);
        }
        if (ret < 0) {
            printf("do_system failed: %s\n", strerror(errno));
        } else {
            printf("do_system succeeded, ret=%d\n", ret);
        }

        /* restore pre-system environment */
        sprintf(new_name, "_SP_NAME=%s", acct_file);
        if (putenv(new_name)) {
            fprintf(stderr,"Failed to restore name! %s\n", strerror(errno));
        }

        return 0;
}

int
do_forkexec (int k)                  /* do a fork()+exec() call combo */
{
        int ret, pid;
        int status=-1;
        char arg0[128], arg1[128];
#if  OS(Solaris)
        int procfd = open("/proc/self/psinfo", O_RDONLY);
        char **pr_argv;
        psinfo_t psinfo;

        if (procfd == -1) {
            fprintf(stderr,"failed to open psinfo\n");
            return -1;
        }
        if (read(procfd, &psinfo, sizeof(psinfo)) == -1) {
            fprintf(stderr, "failed to read psinfo\n");
            close(procfd);
            return -1;
        }
        pr_argv = (char**)psinfo.pr_argv;
        strncpy(arg0, pr_argv[0], sizeof(arg0));
        if (psinfo.pr_argc > 2) 
            strncpy(arg1, pr_argv[2], sizeof(arg1));
        else
            arg1[0]=NULL;
        close(procfd);
#endif /* OS(Solaris) */

	/* ignore reapchild to catch child here */
	(void) sigset(SIGCHLD, 0);

        sprintf(child_name, "%s_f%d", acct_file, ++syn_fork);

        if ((pid = fork()) == 0) {
            syn_fork=syn_exec=syn_combo=0; /* reset for new child line */
            strcpy(acct_file,child_name);
            /*printf("_SP_NAME=\"%s\" (for fork-child)\n", acct_file);*/
            acct_init(acct_file);
            sprintf(new_name, "_SP_NAME=%s_x%d", acct_file, ++syn_exec);
            if (putenv(new_name)) {
                fprintf(stderr,"Failed to name fork child! %s\n", strerror(errno));
            }
            (void) execl(arg0, "fork+exec", arg1[0]!=(char)NULL?arg1:NULL, NULL);
            fprintf(stderr,"fork execl failed! %s\n", strerror(errno));
            _exit(127);
        } else if (pid == -1) {
            fprintf(stderr,"fork failed! %s\n", strerror(errno));
        } else {
            do {
#if OS(Solaris)
                ret = waitpid(pid, &status, WEXITED);
#else /* OS(Solaris) */
                ret = waitpid(pid, &status, WNOHANG | WUNTRACED);
#endif /* OS(Solaris) */
            } while ((ret == -1) && (errno == EINTR));

            if (ret == -1) fprintf(stderr,"waitpid failed: %s\n", strerror(errno));
#if 0
            else {
                if (WIFEXITED(status)) printf("WEXITSTATUS=%d\n", WEXITSTATUS(status));
                if (WIFSTOPPED(status)) printf("WSTOPSIG=%d\n", WSTOPSIG(status));
                if (WIFSIGNALED(status)) printf("WTERMSIG=%d\n", WTERMSIG(status));
                if (WIFCONTINUED(status)) printf("WIFCONTINUED=%d\n", WIFCONTINUED(status));
            }
#endif
    
            if (WIFEXITED(status)) {
                printf("do_forkexec succeeded: child exit status=%d\n",
                    WEXITSTATUS(status));
            } else {
                printf("do_forkexec failed! status=%d\n", status);
            }
        }

	/* set up to reap any children */
	(void) sigset(SIGCHLD, reapchild);

        return 0;
}

int
do_vforkexec (int k)                 /* do a vfork()+exec() call combo */
{
        int ret, pid;
        int status=1;
        char arg0[128], arg1[128];
#if OS(Solaris)
        int procfd = open("/proc/self/psinfo", O_RDONLY);
        char **pr_argv;
        psinfo_t psinfo;

        if (procfd == -1) {
            fprintf(stderr,"failed to open psinfo\n");
            return -1;
        }
        if (read(procfd, &psinfo, sizeof(psinfo)) == -1) {
            fprintf(stderr, "failed to read psinfo\n");
            close(procfd);
            return -1;
        }
        pr_argv = (char**)psinfo.pr_argv;
        strncpy(arg0, pr_argv[0], sizeof(arg0));
        if (psinfo.pr_argc > 2) 
            strncpy(arg1, pr_argv[2], sizeof(arg1));
        else
            arg1[0]=NULL;
        close(procfd);

#endif /* OS(Solaris) */
	/* ignore reapchild to catch child here */
	(void) sigset(SIGCHLD, 0);

        sprintf(child_name, "%s_f%d", acct_file, ++syn_fork);

        if ((pid = vfork()) == 0) {
            syn_fork=syn_exec=syn_combo=0; /* reset for new child line */
            strcpy(acct_file,child_name);
            /*printf("_SP_NAME=\"%s\" (for vfork-child)\n", acct_file);*/
            acct_init(acct_file);
            sprintf(new_name, "_SP_NAME=%s_x%d", acct_file, ++syn_exec);
            if (putenv(new_name)) {
                fprintf(stderr,"Failed to name vfork child! %s\n", strerror(errno));
            }
            (void) execl(arg0, "vfork+exec", arg1[0]!=(char)NULL?arg1:NULL, NULL);
            printf("vfork execl failed! %s\n", strerror(errno));
            _exit(127);
        } else if (pid == -1) {
            fprintf(stderr,"vfork failed! %s\n", strerror(errno));
        } else {
            do {
#if OS(Solaris)
                ret = waitpid(pid, &status, WEXITED);
#else /* OS(Solaris) */
                ret = waitpid(pid, &status, WNOHANG | WUNTRACED);
#endif /* OS(Solaris) */
            } while ((ret == -1) && (errno == EINTR));

            if (ret == -1) fprintf(stderr,"waitpid failed: %s\n", strerror(errno));
#if 0
            else {
                if (WIFEXITED(status)) printf("WEXITSTATUS=%d\n", WEXITSTATUS(status));
                if (WIFSTOPPED(status)) printf("WSTOPSIG=%d\n", WSTOPSIG(status));
                if (WIFSIGNALED(status)) printf("WTERMSIG=%d\n", WTERMSIG(status));
                if (WIFCONTINUED(status)) printf("WIFCONTINUED=%d\n", WIFCONTINUED(status));
            }
#endif
    
            if (WIFEXITED(status)) {
                printf("do_vforkexec succeeded: child exit status=%d\n",
                    WEXITSTATUS(status));
            } else {
                printf("do_vforkexec failed! status=%d\n", status);
            }
        }

	/* set up to reap any children */
	(void) sigset(SIGCHLD, reapchild);

        return 0;
}

