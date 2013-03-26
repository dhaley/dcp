/* Copyright 02/12/07 Sun Microsystems, Inc. All Rights Reserved */
/* mttest -- show threaded use of global and local locks */

#include "defs.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>

#if OS(Solaris)
#include <sys/processor.h>
#include <sys/procset.h>
#include <sys/lwp.h>
#endif /* OS(Solaris) */

#include <strings.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>
#include <assert.h>


#if OS(Linux)
typedef int        processorid_t;
typedef long long  hrtime_t;
typedef struct     timespec timespec_t;
extern             hrtime_t gethrtime();
extern             hrtime_t gethrvtime();
#endif /* OS(Linux) */

#ifdef SOLARIS	/* thread model, not OS */
	#include <thread.h>
	#include <synch.h>
	timestruc_t * hrt_to_ts(hrtime_t hrt);
        static const mutex_t mutex_initializer=DEFAULTMUTEX;
#ifdef BOUND
	char	*model = "Bound Solaris threads";
#else
	char	*model = "Unbound Solaris threads";
#endif
#endif

#ifdef POSIX
	#include <pthread.h>
	#include <semaphore.h>
	timespec_t * hrt_to_ts(hrtime_t hrt);
        static const pthread_mutex_t mutex_initializer=PTHREAD_MUTEX_INITIALIZER;
#ifdef BOUND
	char	*model = "Bound Posix threads";
#else
	char	*model = "Unbound Posix threads";
#endif
#endif

#if OS(Solaris)
int	check_sigmask(int);
#endif /* OS(Solaris) */

char	*prtime (time_t *);
int	get_clock_rate(void);
int	get_ncpus();

#ifdef SELFTEST
void	start_prof(void);
void    finish_prof(void);
#endif

#include <errno.h>
#if OS(Solaris)
#include <sys/systeminfo.h>
#else
#include <sys/sysinfo.h>
#endif /* OS(Solaris) */
#define _STRUCTURED_PROC 1
#include <sys/procfs.h>
#include <sys/fcntl.h>

#define TRUE             1 
#define FALSE            0
#define NUM_OF_THREADS   4
#define NUM_OF_BLOCKS    4 
#define MYTIMEOUT        1000000000
#define NUM_OF_RESOURCES 3 

int	repeat_count = 1;	/* number of times to repeat test */
int	job_index = -1;		/* index of selected job, if just one */
int	uniprocessor = 0;	/* non-zero if -u specified; causes single processor bind */
processorid_t	cpuid;
processorid_t	ocpuid;

// not a typedef; simplifies analyzer data display output
#define workCtr_t double

typedef struct workStruct_t{
    workCtr_t sum_ctr;
}workStruct_t;

struct	Workblk;
typedef struct Workblk {
	int	index;		/* index of this block */
	int	strategy;	/* specifies type of locking to do */
	int	proffail;	/* flag set if thread loses interrupts */

#ifdef SOLARIS
	thread_t	tid;	/* thread processing buffer */
	mutex_t		lock;	/* lock for this buffer */
#endif
#ifdef POSIX
	pthread_t	tid;	/* thread processing buffer */
	pthread_mutex_t	lock;	/* lock for this buffer */
#endif
	lwpid_t		ilwpid;	/* lwp processing buffer (initially) */
	lwpid_t		lwpid;	/* lwp processing buffer (after sync) */

	/* timers */
	hrtime_t	start;	/* buffer fetched, wall clock */
	hrtime_t	vstart;	/* buffer fetched, CPU timer */
	hrtime_t	ready;	/* lock acquired (if needed), wall clock */
	hrtime_t	vready;	/* lock acquired (if needed), CPU timer */
	hrtime_t	done;	/* work done, wall clock */
	hrtime_t	vdone;	/* work done, CPU timer */
	hrtime_t	compute_ready;	/* compute ready, wall clock */
	hrtime_t	compute_vready;	/* compute ready, CPU timer */
	hrtime_t	compute_done;	/* compute done, wall clock */
	hrtime_t	compute_vdone;	/* compute done, CPU timer */

	struct	Workblk	*next;	/* for queue management */

	workStruct_t	list[100];
} Workblk;

/* lookup table for behavior scripts */
struct  scripttab {
	char	*test_name;
	void	(*test_func)(Workblk *, struct scripttab *);
	char	*called_name;
	void	(*called_func)(workStruct_t *);
};

int	locktest();
void	resolve_symbols();
void	init_micro_acct();
void	compute_set(volatile workStruct_t *x);
void	compute(workStruct_t *x);
void	computeA(workStruct_t *x);
void	computeB(workStruct_t *x);
void	computeC(workStruct_t *x);
void	computeD(workStruct_t *x);
void	computeE(workStruct_t *x);
void	computeF(workStruct_t *x);
void	computeG(workStruct_t *x);
void	computeH(workStruct_t *x);
void	computeI(workStruct_t *x);
void	computeJ(workStruct_t *x);
void	computeK(workStruct_t *x);
void	addone(workCtr_t *x);
void	init_arrays(int strat);
void	dump_arrays();
void	*do_work(void *v);
void	thread_work();
void	nothreads(Workblk *array, struct scripttab *k);
void	lock_none(Workblk *array, struct scripttab *k);
void	cache_trash(Workblk *array, struct scripttab *k);
void	lock_global(Workblk *array, struct scripttab *k);
void	trylock_global(Workblk *array, struct scripttab *k);
void	lock_local(Workblk *array, struct scripttab *k);
void	calladd(Workblk *array, struct scripttab *k);
void	cond_global(Workblk *array, struct scripttab *k);
void	cond_timeout_global(Workblk *array, struct scripttab *k);
void	sema_global(Workblk *array, struct scripttab *k);
void	read_write(Workblk *array, struct scripttab *k);
void	s5sem(Workblk *array, struct scripttab *k);
FILE	*open_output(char *filename);
int	close_file(FILE *f);
void	scale_init(int argcc, char **argvv);
void	Print_Usage(int);

struct scripttab       scripttab[] = {
	{"nothreads", nothreads, "compute", compute},
	{"cond_timeout_global", cond_timeout_global, "computeH", computeH},
	{"lock_none", lock_none, "computeA", computeA},
	{"cache_trash", cache_trash, "computeB", computeB},
	{"lock_global", lock_global, "computeC", computeC},
	{"trylock_global", trylock_global, "computeD", computeD},
	{"lock_local", lock_local, "computeE", computeE},
	{"calladd", calladd, "computeF", computeF},
	{"sema_global", sema_global, "computeI", computeI},
#ifdef SOLARIS
	{"read_write", read_write, "computeJ", computeJ},
#endif
	{"cond_global", cond_global, "computeG", computeG},
/*	"s5sem", s5sem, "computeK", computeK, 		omazur: we need to rethink this test */
	{NULL, NULL, NULL, NULL}
};


#ifdef SOLARIS
	static	mutex_t		global_lock = DEFAULTMUTEX;
	static	mutex_t		global_cond_lock = DEFAULTMUTEX;
	static	mutex_t		global_cond_lock2 = DEFAULTMUTEX;
	static  cond_t		global_cond = DEFAULTCV;
	static  timestruc_t	time_out;
	static  rwlock_t	global_rw_lock; /* set to 0 */
	static  sema_t		global_sema_lock; /* dynamically initted */
#endif
#ifdef POSIX
	static	pthread_mutex_t	global_lock = PTHREAD_MUTEX_INITIALIZER ;
	static	pthread_mutex_t	global_cond_lock = PTHREAD_MUTEX_INITIALIZER ;
	static	pthread_mutex_t	global_cond_lock2 = PTHREAD_MUTEX_INITIALIZER ;
	static  pthread_cond_t	global_cond = PTHREAD_COND_INITIALIZER;
	static  timespec_t	time_out;
	static  sem_t		global_sema_lock; /* dynamically initted */
#endif

static int	s5_sema_id; 
static int	global_cond_flag = TRUE;
static int	count = NUM_OF_RESOURCES;

/* an array of workStruct_ts that is contiguous */
workStruct_t	*element;

typedef struct {
	int		size;
	Workblk		*arrays;
} Head;

int	nthreads = NUM_OF_THREADS;
int	narrays = NUM_OF_BLOCKS;
static	Head	head;
char	*name;
FILE	*fid;

#ifdef SOLARIS
	static	thread_t	*tid;
#endif
#ifdef POSIX
	static  pthread_t 	*tid;
	pthread_attr_t 		attr;
#endif

int
main(int argc, char **argv, char **envp)
{
	int	i;

	scale_init(argc, argv);

#define ALIGNMENTOFFSET 2 /* adjust alignment */
        i = sizeof(workStruct_t)*
            (narrays+ALIGNMENTOFFSET);
        element = memalign(64, i);
	if ( element == NULL ) {
	    perror("calloc( narrays, sizeof(workStruct_t) )");
	    exit(1);
	}
        compute_set(element);
        memset(element, 0, i);
        element+=ALIGNMENTOFFSET;

#ifdef SELFTEST
	start_prof();
#endif

	fid = open_output("mttest.acct");
	if (job_index == -1) {
		i = (sizeof(scripttab)/sizeof( struct scripttab) -1 );
	} else {
		i = 1;
	}
	fprintf(fid, "Number of tests: %d  Repeat count: %d\n",
		i, repeat_count);

	fprintf(fid, "MHz: %d\n", get_clock_rate() );

	fprintf(fid,
	    "X    Incl. Total   Incl. CPU   Incl. Sync. Wait   Name (%s)\n",
		model);
	fflush(fid);
  
	name = strdup(argv[0]);

	init_micro_acct();
#if OS(Solaris) 
	if(uniprocessor != 0) {
	    /* call processor_bind to force single CPU */
	    processor_bind(P_PID, P_MYID, cpuid, NULL);
	}
#endif /* OS(Solaris) */

#ifdef SOLARIS
	sema_init(&global_sema_lock, count, USYNC_THREAD, NULL);
#endif
#ifdef POSIX
	pthread_attr_init(&attr);

    #ifdef BOUND
	pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
    #endif

	sem_init(&global_sema_lock, 0, count);
#endif

#if 0
	if ((s5_sema_id = semget(IPC_PRIVATE, 1, 0600)) == -1)
		perror("semget: IPC_PRIVATE");

	arg.val = count;
	if (semctl(s5_sema_id, 0, SETVAL, arg) == -1)
		perror("semctl: SETVAL");
#endif

	resolve_symbols();

	i = locktest();
#if 0
	if (semctl(s5_sema_id, 0, IPC_RMID) == -1)
		perror("semctl: IPC_RMID");
#endif

	close_file(fid);

#ifdef SELFTEST
        finish_prof();
#endif

	return 0;
}

Workblk	*in_queue = NULL;
Workblk	*in_queue_last = NULL;

#ifdef SOLARIS
	mutex_t			queue_lock;
#endif
#ifdef POSIX
	pthread_mutex_t		queue_lock;
#endif


void
queue_work(Workblk * w)
{
	if(in_queue == NULL) {
		in_queue = w;
		in_queue_last = w;
	} else {
		in_queue_last->next = w;
		in_queue_last = w;
	}
}

Workblk *
fetch_work()
{
	Workblk	*w;

	/* acquire the queue lock */
#ifdef SOLARIS
	mutex_lock(&queue_lock);
#endif
#ifdef POSIX
	pthread_mutex_lock(&queue_lock);
#endif

	/* get the next block */
	w = in_queue;
	if(w != NULL) {
		in_queue = w->next;
		w->next = NULL;
		if(in_queue == NULL) {
			in_queue_last = NULL;
		}
	}

	/* free the queue lock */
#ifdef SOLARIS
	mutex_unlock(&queue_lock);
#endif
#ifdef POSIX
	pthread_mutex_unlock(&queue_lock);
#endif

	/* return the block */
	return w;
}

int
locktest()
{
	int	i;
	Workblk *array;
	struct scripttab	*k;
	hrtime_t	start;
	hrtime_t	vstart;
	hrtime_t	end;
	hrtime_t	vend;
	struct timeval	ttime;
	time_t		secs;

	head.size   = narrays;
	head.arrays = (Workblk *) calloc(narrays, sizeof(Workblk));

	for(i = 0, array = head.arrays; i < narrays; i ++, array ++) {
		array->index = i;
	}

	printf( "%s: number of %s = %d, number of blocks = %d, repeat %d times %s\n",
		name, model, nthreads, narrays, repeat_count,
		(uniprocessor == 0 ? "" : "[single CPU]") );

#ifdef SOLARIS
	tid = (thread_t *) calloc(nthreads*repeat_count, sizeof(thread_t));
#endif
#ifdef POSIX
	tid = (pthread_t *) calloc(nthreads*repeat_count, sizeof(pthread_t));
#endif
	for(count = 0; count < repeat_count; count ++) {
	    (void) gettimeofday(&ttime, NULL);
	    secs = (time_t)ttime.tv_sec;
	    printf("Iteration %d, starting %s\n",
		count+1,
		prtime (&secs) );
	    if(job_index == -1) {
	        for (i = 0; ; i++) {
		    k = &scripttab[i];
		    if (k->test_name == NULL) {
			break;
		    }

		    printf("begin thread_work, %s\n", k->test_name);

		    init_arrays(i);

		    start = gethrtime();
		    vstart = gethrvtime();

		    if( strcmp(k->test_name, "nothreads") == 0 ){
			/* the "nothreads" task is special-cased to run in the main thread */
			do_work(NULL);
		    } else if(nthreads == 1) {
			do_work(NULL);
		    } else {
			thread_work();
		    }

		    end = gethrtime();
		    vend = gethrvtime();
#if OS(Solaris)
		    check_sigmask(2);
#endif /* OS(Solaris) */
		    dump_arrays(end-start, vend-vstart, i);
	        }
	    } else {
		    k = &scripttab[job_index];
		    if (k->test_name == NULL) {
			break;
		    }

		    printf("begin thread_work, %s\n", k->test_name);

		    init_arrays(job_index);

		    start = gethrtime();
		    vstart = gethrvtime();

		    if( strcmp(k->test_name, "nothreads") == 0 ){
			/* first one is special-cased to run in 1 thread */
			do_work(NULL);
		    } else if(nthreads == 1) {
			do_work(NULL);
		    } else {
			thread_work();
		    }

		    end = gethrtime();
		    vend = gethrvtime();
#if OS(Solaris)
		    check_sigmask(2);
#endif /* OS(Solaris) */
		    dump_arrays(end-start, vend-vstart, job_index);
	     }
	}

	/* we're done, return */
	return(0);
}

void
init_arrays(int strat)
{
	int	i;
	Workblk *array;
	for(i = 0, array = head.arrays; i < narrays; i ++, array ++) {
		bzero(array, sizeof(array) );
		array->index = i;
		array->strategy = strat;
		queue_work(array);
	}
}

void
dump_arrays(hrtime_t real, hrtime_t cpu, int case_index)
{
	int	i;
	double	t1, t2, t3, t4 ,t5 ,t6, t7, t8;
	Workblk *array;
	struct scripttab	*k;
	double sumtotal = 0.;
	double sumCPU = 0.;
	double sumlock = 0.;
	double sumCompTotal = 0.;
	double sumCompCPU = 0.;
	int	proffail;

	proffail = 0;
	printf(
 "                                   real       real       real        CPU\n");
	printf(
 "idx (t id)                        total       lock     crunch     crunch\n");
	for(i = 0, array = head.arrays; i < narrays; i ++, array ++) {
		/* check to see if data lost for this block */
		/* set flag to disable the comparison */
		/* convert times to seconds */
		t1 = ( (double) array->done - array->start)
			/ (double)1000000000.;
		t2 = ( (double) array->vdone - array->vstart)
			/ (double)1000000000.;
		t3 = ( (double) array->ready - array->start)
			/ (double)1000000000.;
		t4 = ( (double) array->vready - array->vstart)
			/ (double)1000000000.;
		t5 = ( (double) array->done - array->ready)
			/ (double)1000000000.;
		t6 = ( (double) array->vdone - array->vready)
			/ (double)1000000000.;
		t7 = ( (double) array->compute_done - array->compute_ready)
			/ (double)1000000000.;
		t8 = ( (double) array->compute_vdone - array->compute_vready)
			/ (double)1000000000.;

		if(array->proffail != 0) {
			proffail = 1;
		}
		sumtotal = sumtotal + t1;	/* incl. total time */
		sumlock = sumlock + t3;		/* incl. sync. wait time */
#ifdef BOUND
		/* NOTE:
		 *  for bound threads, sumCPU includes the synchronization
		 *  CPU time; for unbound it does not
		 */
		sumCPU = sumCPU + t2;           /* test incl. CPU time */
#else
		sumCPU = sumCPU + t6;		/* test incl. CPU time */
#endif
		sumCompTotal = sumCompTotal+t7;	/* compute incl. totaltime */
		sumCompCPU = sumCompCPU + t8;	/* compute incl. CPU time */

		printf(
#if OS(Solaris)
		"#%2d (t%3d, il%3d, l%3d)      %10.6f %10.6f %10.6f %10.6f%s\n",
#else
		"#%2d (t%3ld, il%3d, l%3d)      %10.6f %10.6f %10.6f %10.6f%s\n",
#endif
			array->index, array->tid, array->ilwpid, array->lwpid, t1, t3, t5, t6,
			(array->proffail == 0 ? "" : " *") );
                assert(array->lwpid > 0);
#if defined(BOUND)
                assert(array->lwpid == array->ilwpid);
#endif
	}

	k = &scripttab[case_index];

	printf(
		"%-25s    %10.6f %10.6f  %-9s %10.6f\n",
		k->test_name,
		sumtotal,
		sumlock,
		k->called_name,
		sumCPU);
	printf(
		"main                         %10.6f\n\n",
		(double)real/(double)1000000000.);

	/* write accounting record for task */
	fprintf(fid, "X   %7.3f        %7.3f       %7.3f         %s%s\n",
		sumtotal, sumCPU, sumlock, k->test_name,
		(proffail == 0 ? "" : " *") );
	/* write accounting record for task's compute function */
	fprintf(fid, "X   %7.3f        %7.3f         0.            %s%s\n",
		sumCompTotal, sumCompCPU, k->called_name,
		(proffail == 0 ? "" : " *") );
	fflush(fid);

#if 0
	for(i = 0, array = head.arrays; i < narrays; i ++, array ++) {
	    printf(
  "\nst:%9.6f  vst:%9.6f  rd:%9.6f  vrd:%9.6f  dn:%9.6f  vdn:%9.6f\n\n",
		(double)array->start / (double)1000000000.,
		(double)array->vstart / (double)1000000000.,
		(double)array->ready / (double)1000000000.,
		(double)array->vready / (double)1000000000., 
		(double)array->done / (double)1000000000., 
		(double)array->vdone / (double)1000000000.);

	}
#endif
	fflush(stdout);

}

void
thread_work()
{
	int i;

#ifdef UNBOUND
    #ifdef SOLARIS
	if (thr_setconcurrency(nthreads) != 0) {
		perror("Oops, thr_setconcurrency failed");
		exit(1);
	}
    #endif
#endif

	/* create nthreads threads, having each start at do_work */
	for (i = 0; i < nthreads; i++) {
		int retval;

#ifdef SOLARIS
    #ifdef BOUND
		retval = thr_create(0, 0, do_work, 0, THR_BOUND, &(tid[i]));
    #endif
    #ifdef UNBOUND
		retval = thr_create(0, 0, do_work, 0, 0, &(tid[i]));
    #endif
#endif
#ifdef POSIX
    #ifdef BOUND
		retval = pthread_create(&(tid[i]), &attr, do_work, 0);
    #endif
    #ifdef UNBOUND
		retval = pthread_create(&(tid[i]), 0, do_work, 0);
    #endif
#endif

		if(retval != 0) {
			perror("Oops, thr_create failed");
			exit(1);
		}
	}

	/* wait for all threads to complete their work and join */
	for (i = 0; i < nthreads; i++) {
#ifdef SOLARIS
		thr_join(tid[i], 0, 0);
#endif
#ifdef POSIX
		pthread_join(tid[i], 0);
#endif
	}
}

/* do_work: process array's data with locking, based on array->strategy */
void *
do_work(void *v)
{
	Workblk	*array;
	struct scripttab	*k;
	int i;
	volatile double x;

#ifdef SOLARIS
	thread_t	mytid = thr_self();
#endif
#ifdef POSIX
	pthread_t	mytid = pthread_self();
#endif
#if OS(Solaris)
	/* check for signal masked */
	check_sigmask(0);
#endif /* OS(Solaris) */

	/* delay to ensure that a tick passes, so that the
	 * first profile packet doesn't show the thread startup time
	 * attributed to the accounting functions
	 */
	x = 0;
	for (i = 0; i < 2000000; i++) { x = x + 1.0; }

	for(;;) {
		/* fetch a workblk */
		array = fetch_work();
		if(array == NULL) {
			/* we're done */
			break;
		}
                array->lock = mutex_initializer;
		array->proffail = 0;
		array->tid = mytid;
#if OS(Solaris)		
		array->ilwpid = _lwp_self();
#else
		array->ilwpid = getpid() /* pthread_self()*/ ;
#endif /* OS(Solaris) */

                array->lwpid = -1; /* initialise to inappropriate value */
#if 0
		printf("thread %d, initial lwp %d, block #%d, strategy = %d\n",
		    array->tid, array->ilwpid, array->index, array->strategy);
#endif
		array->start = gethrtime();
		array->vstart = gethrvtime();

		k = &scripttab[array->strategy];
		(k->test_func)(array, k);

		array->done = gethrtime();
		array->vdone = gethrvtime();
#if OS(Solaris)
		array->lwpid = _lwp_self();
#else
		array->lwpid = getpid() /* pthread_self()*/ ;
#endif /* OS(Solaris) */
				

#if defined(BOUND)
                assert(array->lwpid == array->ilwpid);
#endif
#if OS(Solaris)
		if(check_sigmask(1) != 0) {
			/* set flag in the array */
			array->proffail = 1;
		}
#endif /* OS(Solaris) */
	}

	return NULL;
}

/* nothreads: process array's data with no locking; called without threads */
void
nothreads(Workblk *array, struct scripttab *k)
{
/*	array->ready = array->start;
	array->vready = array->vstart;
*/
	array->ready = gethrtime();
	array->vready = gethrvtime();

	array->compute_ready = array->ready;
	array->compute_vready = array->vready;

	/* do some work on the current array */
	(k->called_func)(&array->list[0]);

	array->compute_done = gethrtime();
	array->compute_vdone = gethrvtime();

}

/* lock_none: process array's data with no locking */
void
lock_none(Workblk *array, struct scripttab *k)
{
	array->ready = array->start;
	array->vready = array->vstart;

	array->compute_ready = array->ready;
	array->compute_vready = array->vready;

	/* do some work on the current array */
	(k->called_func)(&array->list[0]);

	array->compute_done = gethrtime();
	array->compute_vdone = gethrvtime();

}


/* cache_trash_even:
 *      called for even numbered l1 cache lines
 */
void
cache_trash_even(Workblk *array, struct scripttab *k)
{
	/* use a datum that will share a cache line with others */
	(k->called_func)(&element[array->index]);
}

/* cache_trash_odd: 
 *      called for odd numbered l1 cache lines
 */
void
cache_trash_odd(Workblk *array, struct scripttab *k)
{
	/* use a datum that will share a cache line with others */
	(k->called_func)(&element[array->index]);
}

/* cache_trash: multiple threads refer to adjacent words,
 *	causing false sharing of cache lines, and trashing
 */
void
cache_trash(Workblk *array, struct scripttab *k)
{
	array->ready = array->start;
	array->vready = array->vstart;

	array->compute_ready = array->ready;
	array->compute_vready = array->vready;

        /* use a datum that will share a cache line with others */        
        if( (unsigned long)(&element[array->index]) / 32 & 1){
            cache_trash_odd(array,k);
        }else{
            cache_trash_even(array,k);
        }

	array->compute_done = gethrtime();
	array->compute_vdone = gethrvtime();
}

/* lock_global: use a global lock to process array's data */
void
lock_global(Workblk *array, struct scripttab *k)
{
	/* acquire the global lock */

#ifdef SOLARIS
	mutex_lock(&global_lock);
#endif
#ifdef POSIX
	pthread_mutex_lock(&global_lock);
#endif

	array->ready = gethrtime();
	array->vready = gethrvtime();

	array->compute_ready = array->ready;
	array->compute_vready = array->vready;

	/* do some work on the current array */
	(k->called_func)(&array->list[0]);

	array->compute_done = gethrtime();
	array->compute_vdone = gethrvtime();

	/* free the global lock */
#ifdef SOLARIS
	mutex_unlock(&global_lock);
#endif
#ifdef POSIX
	pthread_mutex_unlock(&global_lock);
#endif
	/* make another call to preclude tail-call optimization on the unlock */
	(void) gethrtime();
}


/* trylock_global: busy-wait on a global lock to process array's data */
void
trylock_global(Workblk *array, struct scripttab *k)
{
	int ret;

	/* set ready before starting, since this is a busy wait */
	array->ready = gethrtime();
	array->vready = gethrvtime();

	/* busy wait to acquire the global lock */
#ifdef SOLARIS
	do {
	    ret = mutex_trylock(&global_lock);
	} while (ret == EBUSY);
#endif
#ifdef POSIX
	do {
	    ret = pthread_mutex_trylock(&global_lock);
	} while (ret == EBUSY);
#endif
	array->compute_ready = gethrtime();
	array->compute_vready = gethrvtime();

	/* do some work on the current array */
	(k->called_func)(&array->list[0]);

	array->compute_done = gethrtime();
	array->compute_vdone = gethrvtime();

	/* free the global lock */
#ifdef SOLARIS
	mutex_unlock(&global_lock);
#endif
#ifdef POSIX
	pthread_mutex_unlock(&global_lock);
#endif
	/* make another call to preclude tail-call optimization on the unlock */
	(void) gethrtime();
}

/* lock_local: use a local lock to process array's data */
void
lock_local(Workblk *array, struct scripttab *k)
{
	/* acquire the local lock */
#ifdef SOLARIS
	mutex_lock(&(array->lock));
#endif
#ifdef POSIX
	pthread_mutex_lock(&(array->lock));
#endif
	array->ready = gethrtime();
	array->vready = gethrvtime();

	array->compute_ready = array->ready;
	array->compute_vready = array->vready;

	/* do some work on the current array */
	(k->called_func)(&array->list[0]);

	array->compute_done = gethrtime();
	array->compute_vdone = gethrvtime();

	/* free the local lock */
#ifdef SOLARIS
	mutex_unlock(&array->lock);
#endif
#ifdef POSIX
	pthread_mutex_unlock(&array->lock);
#endif
	/* make another call to preclude tail-call optimization on the unlock */
	(void) gethrtime();
}

/* cond_global: use a global condition variable to process array's data */
void
cond_global(Workblk *array, struct scripttab *k)
{
	/* acquire the global condition lock */

#ifdef SOLARIS
	mutex_lock(&global_cond_lock);
#endif
#ifdef POSIX
	pthread_mutex_lock(&global_cond_lock);
#endif

	/* check to see if the condition flag is true, If not then wait
	for that condition flag to become true. */
	while (global_cond_flag != TRUE) {

#ifdef SOLARIS
		cond_wait(&global_cond, &global_cond_lock);
#endif
#ifdef POSIX
		pthread_cond_wait(&global_cond, &global_cond_lock);
#endif
	}
	/* Now, condition is true, and we have the global_cond_lock */

	/* set the condition flag to be FALSE, so when a new thread
	 * is created, it should wait till this one is done.
	 */
	global_cond_flag = FALSE;

	/* free the global_cond_lock and acquire the global lock */
#ifdef SOLARIS
	mutex_unlock(&global_cond_lock);
	mutex_lock(&global_lock);
#endif
#ifdef POSIX
	pthread_mutex_unlock(&global_cond_lock);
	pthread_mutex_lock(&global_lock);
#endif

	array->ready = gethrtime();
	array->vready = gethrvtime();

	array->compute_ready = array->ready;
	array->compute_vready = array->vready;

	/* do some work on the current array */
	(k->called_func)(&array->list[0]);

	array->compute_done = gethrtime();
	array->compute_vdone = gethrvtime();

	/* free the global lock */

#ifdef SOLARIS
	mutex_unlock(&global_lock);

	/* now set the condition, and signal any other threads */
	mutex_lock(&global_cond_lock);
#endif
#ifdef POSIX
	pthread_mutex_unlock(&global_lock);

	/* now set the condition, and signal any other threads */
	pthread_mutex_lock(&global_cond_lock);
#endif

	global_cond_flag = TRUE;
#ifdef SOLARIS
	cond_signal(&global_cond);
	mutex_unlock(&global_cond_lock);
#endif
#ifdef POSIX
	pthread_cond_signal(&global_cond);
	pthread_mutex_unlock(&global_cond_lock);
#endif
	/* make another call to preclude tail-call optimization on the unlock */
	(void) gethrtime();
}

/* cond_timeout_global: use a global condition time wait variable to 
   process array's data */
void
cond_timeout_global(Workblk *array, struct scripttab *k)
{
	int err;
	struct	timeval	current_time;

	/* acquire the global condition lock */
#ifdef SOLARIS
	mutex_lock(&global_cond_lock);
#endif
#ifdef POSIX
	pthread_mutex_lock(&global_cond_lock);
#endif
	gettimeofday(&current_time, NULL);
	time_out.tv_sec = current_time.tv_sec;
	time_out.tv_nsec = current_time.tv_usec * 1000;

	/* check to see if the condition flag is true, If not then wait
	 * for that condition flag to become true
	 */

	while (global_cond_flag != TRUE) {
		/* add MYTIMEOUT to current time for timeout */
		time_out.tv_nsec += MYTIMEOUT;
		while (time_out.tv_nsec > 1000000000) {
			time_out.tv_nsec -= 1000000000;
			time_out.tv_sec ++;
		}
			
#ifdef SOLARIS
		err = cond_timedwait( &global_cond,
			&global_cond_lock, &time_out);
#endif
#ifdef POSIX
		err = pthread_cond_timedwait( &global_cond,
			&global_cond_lock, &time_out);
#endif

		if (err == 0 ) {
			/* with the condition */
			break;
		}

	}
	/* Now, condition is true, and we have the global_cond_lock */

#ifdef SOLARIS
	mutex_unlock(&global_cond_lock);

	mutex_lock(&global_cond_lock2);
	global_cond_flag = FALSE;
	mutex_unlock(&global_cond_lock2);

	/* acquire the global lock */
	mutex_lock(&global_lock);
#endif
#ifdef POSIX
	pthread_mutex_unlock(&global_cond_lock);

	pthread_mutex_lock(&global_cond_lock2);
	global_cond_flag = FALSE;
	pthread_mutex_unlock(&global_cond_lock2);

	/* acquire the global lock */
	pthread_mutex_lock(&global_lock);
#endif

	array->ready = gethrtime();
	array->vready = gethrvtime();

	array->compute_ready = array->ready;
	array->compute_vready = array->vready;

	/* do some work on the current array */
	(k->called_func)(&array->list[0]);
	array->compute_done = gethrtime();
	array->compute_vdone = gethrvtime();

	/* free the global lock */
#ifdef SOLARIS
	mutex_unlock(&global_lock);

	/* now set the condition, and signal any other threads */
	mutex_lock(&global_cond_lock2);
#endif
#ifdef POSIX
	pthread_mutex_unlock(&global_lock);

	/* now set the condition, and signal any other threads */
	pthread_mutex_lock(&global_cond_lock2);
#endif

	global_cond_flag = TRUE;
#ifdef SOLARIS
	cond_signal(&global_cond);
	mutex_unlock(&global_cond_lock2);
#endif
#ifdef POSIX
	pthread_cond_signal(&global_cond);
	pthread_mutex_unlock(&global_cond_lock2);
#endif

	/* make another call to preclude tail-call optimization on the unlock */
	(void) gethrtime();
}

/* read_write: use a global Reader/Writer lock to process array's data */
void
read_write(Workblk *array, struct scripttab *k)
{

#ifdef SOLARIS
	switch (array->tid % NUM_OF_THREADS) {
	case 0:
	case 1:
	default:
	    rw_rdlock(&global_rw_lock);

	    array->ready = gethrtime();
	    array->vready = gethrvtime();

	    array->compute_ready = array->ready;
	    array->compute_vready = array->vready;

	    (k->called_func)(&array->list[0]);
	    array->compute_done = gethrtime();
	    array->compute_vdone = gethrvtime();

	    rw_unlock(&global_rw_lock);
	    break;

	case 2:
	    rw_wrlock(&global_rw_lock);

	    array->ready = gethrtime();
	    array->vready = gethrvtime();

	    array->compute_ready = array->ready;
	    array->compute_vready = array->vready;

	    (k->called_func)(&array->list[0]);

	    array->compute_done = gethrtime();
	    array->compute_vdone = gethrvtime();

	    rw_unlock(&global_rw_lock);
	    break;
	}
#endif

	/* make another call to preclude tail-call optimization on the unlock */
	(void) gethrtime();
}

/* sema_global: use a global semaphore to process array's data */
void
sema_global(Workblk *array, struct scripttab *k)
{
#ifdef SOLARIS
	sema_wait(&global_sema_lock); 
#endif
#ifdef POSIX
	sem_wait(&global_sema_lock); 
#endif

	array->ready = gethrtime();
	array->vready = gethrvtime();

	array->compute_ready = array->ready;
	array->compute_vready = array->vready;

	/* do some work on the current array */
	(k->called_func)(&array->list[0]);

	array->compute_done = gethrtime();
	array->compute_vdone = gethrvtime();

#ifdef SOLARIS
	sema_post(&global_sema_lock);
#endif
#ifdef POSIX
	sem_post(&global_sema_lock);
#endif

	/* make another call to preclude tail-call optimization on the unlock */
	(void) gethrtime();
}

/* s5sema: use a global UNIX System V semaphore to process array's data */
void
s5sem(Workblk *array, struct scripttab *k)
{
	static struct sembuf	op_wait[] = { { 0, -1, IPC_NOWAIT } };
	static struct sembuf	op_post[] = { { 0,  1, 0 } };
	int			sema_val;

	/* set ready before starting, since this is a busy wait */
	array->ready = gethrtime();
	array->vready = gethrvtime();

	do {
	    sema_val = semop(s5_sema_id, op_wait, 1);
	} while (sema_val == -1);

	array->compute_ready = gethrtime();
	array->compute_vready = gethrvtime();

	/* do some work on the current array */
	(k->called_func)(&array->list[0]);

	array->compute_done = gethrtime();
	array->compute_vdone = gethrvtime();

	if (semop(s5_sema_id, op_post, 1) == -1)
		perror("semop: post");
	/* make another call to preclude tail-call optimization on the unlock */
	(void) gethrtime();
}

/* lock_local: use a local lock to process array's data */
void
calladd(Workblk *array, struct scripttab *k)
{
	array->ready = array->start;
	array->vready = array->vstart;

	array->compute_ready = array->ready;
	array->compute_vready = array->vready;

	(k->called_func)(&array->list[0]);

	array->compute_done = gethrtime();
	array->compute_vdone = gethrvtime();
}

/* compute*: several copies, each burns cpu time, incrementing a workStruct_t */
static int loop_count = 80000000;
void
compute_set(volatile workStruct_t *x)
{
	int i;
	hrtime_t t;
	double testtime = 3.0;
	char *s;

	s = getenv("SP_COLLECTOR_TEST_TIMER");
	if( s ) {
		testtime = atof(s);
		if (testtime < 1.0)
			testtime = 1.0;
	}

	t = gethrtime();
	x->sum_ctr = 0;
	loop_count = 10000;
	for (i = 0; i < loop_count; i++) { x->sum_ctr = x->sum_ctr + 1.0; }
	t = gethrtime() - t;
	loop_count *=  testtime * 1e9 / t;
	printf("compute_set: loop_count=%d\n", loop_count);
}

void
compute(workStruct_t *x)
{
	int i;
	x->sum_ctr = 0;
	for (i = 0; i < loop_count; i++) { x->sum_ctr = x->sum_ctr + 1.0; }
}

void
computeA(workStruct_t *x)
{
	int i;
	x->sum_ctr = 0;
	for (i = 0; i < loop_count; i++) { x->sum_ctr = x->sum_ctr + 1.0; }
}

void
computeB(workStruct_t *x)
{
	int i;
	x->sum_ctr = 0;
	for (i = 0; i < loop_count; i++) { x->sum_ctr = x->sum_ctr + 1.0; }
}

void
computeC(workStruct_t *x)
{
	int i;
	x->sum_ctr = 0;
	for (i = 0; i < loop_count; i++) { x->sum_ctr = x->sum_ctr + 1.0; }
}

void
computeD(workStruct_t *x)
{
	int i;
	x->sum_ctr = 0;
	for (i = 0; i < loop_count; i++) { x->sum_ctr = x->sum_ctr + 1.0; }
}

void
computeE(workStruct_t *x)
{
	int i;
	x->sum_ctr = 0;
	for (i = 0; i < loop_count; i++) { x->sum_ctr = x->sum_ctr + 1.0; }
}

/* note that this one is different from the others, in that it calls
 *	a function to do the add
 */
void
computeF(workStruct_t *x)
{
	int i;
	x->sum_ctr = 0;
	for (i = 0; i < loop_count; i++) { addone(&x->sum_ctr); }
}

void
computeG(workStruct_t *x)
{
	int i;
	x->sum_ctr = 0;
	for (i = 0; i < loop_count; i++) { x->sum_ctr = x->sum_ctr + 1.0; }
}

void
computeH(workStruct_t *x)
{
	int i;
	x->sum_ctr = 0;
	for (i = 0; i < loop_count; i++) { x->sum_ctr = x->sum_ctr + 1.0; }
}

void
computeI(workStruct_t *x)
{
	int i;
	x->sum_ctr = 0;
	for (i = 0; i < loop_count; i++) { x->sum_ctr = x->sum_ctr + 1.0; }
}

void
computeJ(workStruct_t *x)
{
	int i;
	x->sum_ctr = 0;
	for (i = 0; i < loop_count; i++) { x->sum_ctr = x->sum_ctr + 1.0; }
}

void
computeK(workStruct_t *x)
{
	int i;
	x->sum_ctr = 0;
	for (i = 0; i < loop_count; i++) { x->sum_ctr = x->sum_ctr + 1.0; }
}

void
addone(workCtr_t *x)
{
	*x = *x + 1.0;
}

FILE *open_output(char *filename)
{
	FILE *f;
	errno = 0;
	f = fopen(filename, "w");
	if (f == NULL) fprintf(stderr,
		"Open of %s for output failed: %s\n",
		filename, strerror(errno));

	return f;
}

int close_file(FILE *f)
{
	int s = 0;
	if (f == NULL) return 0;
	errno = 0;
	s = fclose(f);
	if (s == EOF) perror("Close failed");
	return s;
}


void scale_init(int argcc, char **argvv)
{
    int		i, j, num;
    int		ii;
    char	*p;
    struct scripttab *kk;

    if (argcc >=2)  /* run mttest with options */ {
	for (i = 1; i < argcc; i++) {
	    j = i;

	    if(argvv[i][0] != '-') {
		Print_Usage(1);
	    }
	    if( (argvv[i][1] == 'h') || (argvv[i][1] == 'H') ) {
		Print_Usage(0);
	    }
	    if(argvv[i][1] == 'u') {
		uniprocessor ++;
		continue;
	    }

	    if (strlen(argvv[i]) == 2) {
		/* argument has blank separating key and number */
		j++;
		if (argcc > j) {
		    p = argvv[j];
		    num = atoi(p);
		} else {
		    Print_Usage(1);
		}
	    } else {
		/* argument has no blank separating key and number */
		p = argvv[i] + 2;
		num = atoi(p);
	    }

	    switch (argvv[i][1]) {
		case 't':
		case 'T':
		    nthreads = num;
		    break;

		case 'b':
		case 'B':
		    narrays = num;
		    break;

		case 'r':
		case 'R':
		    repeat_count = num;
		    break;

		case 'j':
		case 'J':
		    /* argument is a job name; p points to string */
	            for (ii = 0; ; ii++) {
			kk = &scripttab[ii];
			if (kk->test_name == NULL) {
			    /* Oops, name not found */
			    Print_Usage(2);
			}
			if( strcmp(kk->test_name, p) == 0 ) {
			    /* found it */
			    break;
			}
		    }
		    job_index = ii;
		    break;

		default:
		    Print_Usage(1);
	    }
	    i = j;
	}
    }
}


void
Print_Usage(int error)
{
	int	ii;
	struct scripttab *kk;

	if(error == 1) {
	    printf("\nError: Incorrect option\n");
	} else if (error == 2) {
	    printf("\nError: job name not found\n");
	}
	printf( "Usage: mttest [-t num_of_threads] [-b num_of_blocks] [-R repeat_count] [-u] [-j job_name]\n");
	printf( "    -u implies binding all LWPs to one CPU with processor_bind\n");
	printf( "    job_name is one of:\n");
	for (ii = 0; ; ii++) {
	    kk = &scripttab[ii];
	    if(kk->test_name == NULL) {
		break;
	    }
	    printf("\t%s\n", kk->test_name);
	}
	printf( "    if job_name is omitted, each will be run in turn\n");
	exit(-1);
}

void
resolve_symbols()
{
	void *foo;
	global_cond_flag = TRUE;
#ifdef SOLARIS
	mutex_lock(&queue_lock);
	mutex_trylock(&queue_lock);
	mutex_unlock(&queue_lock);
	foo = (void *)&cond_signal;
	foo = (void *)&cond_wait;
	foo = (void *)&cond_timedwait;
	sema_post(&global_sema_lock);
	sema_wait(&global_sema_lock); 
	rw_rdlock(&global_rw_lock);
	rw_unlock(&global_rw_lock);
	rw_wrlock(&global_rw_lock);
	rw_unlock(&global_rw_lock);
#endif
#ifdef POSIX
	pthread_mutex_lock(&queue_lock);
	pthread_mutex_trylock(&queue_lock);
	pthread_mutex_unlock(&queue_lock);
	foo = (void *)&pthread_cond_signal;
	foo = (void *)&pthread_cond_wait;
	foo = (void *)&pthread_cond_timedwait;
	sem_post(&global_sema_lock);
	sem_wait(&global_sema_lock); 
#endif
}

/*	prtime (ttime)
 *		returns a pointer to a static string in the form:
 *		Thu  01 Jan 00  00:00:00\0
 *		01234567890122345678901234
 *
 *	ttime is a pointer to a UNIX time in seconds since epoch
 *	library routine localtime() is used
 *
 */

char	*
prtime (time_t *ttime)
{
	static	char	*days[] = {
		 "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
	static	char	*months[] = {
		 "Jan", "Feb", "Mar", "Apr", "May", "Jun",
		 "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

	static	char	cvbuf[26];
	struct	tm	*tp;

	/* get the date and time */

	tp = localtime(ttime);

	/* convert to string */

	sprintf(cvbuf, "%3s  %02d %s %02d  %02d:%02d:%02d",
		days[tp->tm_wday],
		tp->tm_mday,
		months[tp->tm_mon],
		tp->tm_year%100,
		tp->tm_hour,
		tp->tm_min,
		tp->tm_sec);

	return(cvbuf);
}
