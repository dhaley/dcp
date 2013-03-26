/*
 * Copyright 03/14/07 Sun Microsystems, Inc. All Rights Reserved
 */

#include	"defs.h"
#if OS(Solaris)
#pragma ident "@(#)gethrtime.c 1.13 07/03/14"
#include <sys/systeminfo.h>
#define _STRUCTURED_PROC 1
#include <sys/procfs.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/processor.h>
#include <sys/procset.h>
#include <sys/lwp.h>
#include <errno.h>
#endif	/* OS(Solaris) */

#include	<unistd.h>
#include	<string.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<sys/resource.h>
#include	<sys/time.h>

/* =============================================================== */
/*
 * Below this are the get_clock_rate() and get_ncpus() for all OSs and architectures
 */
/* prototypes */

int	get_clock_rate();
int	get_ncpus();

/* implementation */
static int clock_rate = 0;
static int ncpus = 0;
static char	msgbuf[1024];

int
get_clock_rate(void)
{
#if OS(Solaris)
    int cpu;
    int ret;
    processor_info_t pi_info;
    int maxcpus;

    maxcpus = sysconf( _SC_CPUID_MAX );
    if ( maxcpus == -1 ) {
	maxcpus = sysconf( _SC_NPROCESSORS_CONF ) + 2048;
    }
    for ( cpu = 0; cpu < maxcpus; cpu++ ) {
	if( (ret = p_online(cpu, P_STATUS)) != -1 ) {
	    if( (ret != P_ONLINE) && (ret != P_NOINTR) ) {
		/* skip any CPUs that are not currently online */
		continue;
	    }
	    int val = processor_info(cpu, &pi_info);
	    if(val == 0) {
		if(clock_rate == 0) {
		    clock_rate = pi_info.pi_clock;
		    sprintf(msgbuf, "Clock rate = %d MHz (from processor_info()) %d CPUs\n", clock_rate, ncpus);
		}
	    }
	    ncpus ++;
	}
    }
#else /* OS(Linux) */
    /* Linux version -- read /proc/cpuinfo
     *	Note the parsing is different on intel-Linux and sparc-Linux
     */
    FILE *fp;
    if ( ( fp = fopen("/proc/cpuinfo", "r") ) != NULL ) {

	char temp[1024];
	while ( fgets( temp, sizeof(temp), fp ) != NULL) {
#if ARCH(SPARC)
	    /* cpu count for SPARC linux -- read from /proc/cpuinfo */
	    if ( strncmp( temp, "ncpus active", 12 ) == 0 ) {
		char *val = strchr( temp, ':' );
		ncpus = val? atol(val + 1 ) : 0;
	    }
#endif	/* ARCH(SPARC) */

	    if(clock_rate == 0) {
		/* pick the first line that gives a CPU clock rate */
#if ARCH(SPARC)
		long long clk;
		if ( strncmp( temp, "Cpu0ClkTck", 10 ) == 0 ) {
		    char *val = strchr( temp, ':' );
		    clk = val ? strtoll( val + 1, NULL, 16 ) : 0;
		    clock_rate = (int) (clk/1000000);
		}
#else	/* ARCH(SPARC) */
		if ( strncmp( temp, "cpu MHz", 7 ) == 0 ) {
		    char *val = strchr( temp, ':' );
		    clock_rate = val ? atoi( val + 1 ) : 0;
		}
#endif	/* ARCH(SPARC) */
	    }

	    /* did we get a clock rate? */
	    if ( clock_rate != 0 ) {
#if ARCH(SPARC)
		/* since we got a cpu count, we can break from the look */
		break;
#endif	/* ARCH(SPARC) */
	    }
#if ARCH(Intel)
	    /* On intel-Linux, count cpus based on "cpu MHz" lines */
	    if ( strncmp( temp, "cpu MHz", 7 ) == 0 ) {
		    ncpus ++;
	    }
#endif /* ARCH(Intel) */
	}    
	fclose(fp);
    }	

    if ( clock_rate != 0 ) {
	sprintf(msgbuf, "Clock rate = %d MHz (from reading /proc/cpuinfo) %d CPUs\n", clock_rate, ncpus);
    }
#endif /* OS() */

    /* did we get a clock rate? */
    if ( clock_rate == 0 ) {
	clock_rate = 1000;       
	sprintf(msgbuf, "Clock rate = %d MHz (set by default) %d CPUs\n", clock_rate, ncpus);
    }

    /* fprintf(stderr, "%s", msgbuf); */
    return clock_rate;
}

int
get_ncpus(void) {
    if(clock_rate == 0) {
	(void) get_clock_rate();
    }
    return ncpus;
}

#if OS(Solaris)
/* no need define gethrtime() or gethrvtime() */
#include <sys/types.h>      /* processor_info_t     */
#include <sys/processor.h>      /* processor_info_t     */

#else /* OS(Solaris) */

/* =============================================================== */
/*
 * Below this are the Linux versions of gethrvtime and gethrtime
 */

typedef long long      hrtime_t;

/* function prototypes */
hrtime_t gethrtime();
hrtime_t gethrvtime();

/* gethrvtime -- generic solution, getting user time from getrusage, and reformatting */
hrtime_t
gethrvtime(void)
{
    struct rusage usage;
    int status;
    hrtime_t rc = 0;
    double drc;
    
    status = getrusage (RUSAGE_SELF, &usage);
    if (!status) {
	drc = usage.ru_utime.tv_sec + usage.ru_utime.tv_usec * 1e-6; 
	drc = drc * 1000000000;
	rc = (hrtime_t) drc;
    }
    return rc;
}

#if ARCH(SPARC) || COMPILER(SUN)
/* generic gethrtime() -- using gettimeofday(), and reformatting */
/*
 *  gettimeofday() returns time of day in elapsed seconds and microseconds
 *      since 00:00 Universal Coordinated Time, January 1, 1970.
 *      Subtract 30 years from this to get a smaller number and 
 *      thus avoid any overflow.
 */

#define SUBTRACT_30_YEARS       30 * 365 * (24 * 60 * 60)
hrtime_t
gethrtime(void)
{
	struct timeval tv;
	struct timezone tz;
	int status;
	hrtime_t rc = 0;
	double drc;

	tz.tz_dsttime = 0;

	status = gettimeofday(&tv, NULL);
	if (!status) {
	    drc = (tv.tv_sec - SUBTRACT_30_YEARS);
	    drc = drc * 1000000000 + tv.tv_usec * 1000;
	    rc = (hrtime_t) drc;
	}
	return rc;
}

#if 0
static hrtime_t
rd_hr_clock(void)
{
	hrtime_t stick;

#if WSIZE(64)
	__asm__ (
	"	rd	%%asr24, %0\n\t"
	: "=&r" (stick));
#else /* WSIZE() */

/* From Greg Onufer: The instructions are srlx and sra to split
 *	the 64-bit register into the high and low parts.
 */
	stick = 0;
#endif /* WSIZE() */

	return (stick);
}

hrtime_t
gethrtime()
{
    hrtime_t res;
    if ( clock_rate == 0 ) {
	get_clock_rate();
    }
    res = rd_hr_clock();
    rd_hr_clock(res);
    return (res / clock_rate * 1000);
}
#endif	/* if 0 */

#else	/* ARCH(SPARC) || COMPILER(SUN) */

/* Version for x86 Linux -- uses inline assembler macro to read clock */

#if WSIZE(32)
#define rdtscll(val) \
     __asm__ __volatile__("rdtsc" : "=A" (val))

#else	/* WSIZE() */
#define rdtscll(val) do { \
	     unsigned int __a,__d; \
	     asm volatile("rdtsc" : "=a" (__a), "=d" (__d)); \
	     (val) = ((unsigned long)__a) | (((unsigned long)__d)<<32); \
} while(0)
#endif /* WSIZE() */

hrtime_t
gethrtime(void)
{
    hrtime_t res;
    if ( clock_rate == 0 ) {
	get_clock_rate();
    }
    rdtscll(res);
    return (res / clock_rate * 1000);
}
#endif	/* ARCH(SPARC) || COMPILER(SUN) */

#endif	/* OS(Solaris) */

void
init_micro_acct()
{
#if OS(Solaris)
	int	ctlfd;
	long	ret;
	double	a = 0.;
	long	ctl[2];
	char	arch[64], procname[1024];

	ret = sysinfo(SI_RELEASE, arch, sizeof(arch));
	if(ret < 0) {
		printf(" sysinfo(SI_RELEASE,arch,sizeof(arch)) = %ld, %d\n",
			ret, errno);
	}

	a = atof(arch);
	printf( "  OS release %s -- ", arch);

	sprintf(procname, "/proc/%d/ctl", (int)getpid());
	ctlfd  = open(procname, O_WRONLY);
	if(ctlfd < 0) {
		fprintf(stderr, "open %s failed, errno = %d\n",
			procname, errno);
	}
	ctl[0] = PCSET;;
	ctl[1] = PR_MSACCT;
	if (write(ctlfd, ctl, 2*sizeof(long)) < 0) {
		fprintf(stderr, "write failed, errno = %d\n",
			errno);
	}
	close(ctlfd);
	printf( "enabling microstate accounting %s.\n", arch);
#endif /* OS(Solaris) */
}
