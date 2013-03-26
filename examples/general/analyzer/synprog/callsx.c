/* Copyright 02/04/2000 Sun Microsystems, Inc. All Rights Reserved */
/*=======================================================*/
/* parameters defining various tasks */
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "stopwatch.h"


#define	DYNSOROUTINE	"sx_cputime"
#define	DYNSONAME	"./so_syx.so"

/* callsx -- dynamically link a shared object, and call a routine in it */

#ifndef NONSHARED

static	void	*sx_object = NULL;
static	void	closesx(void);

int
callsx(int k)
{
	int i;
	int (*sx_routine)();
	char	buf[1024];
	hrtime_t	start;
	hrtime_t	vstart;

	start = gethrtime();
	vstart = gethrvtime();
 
	/* Log the event */
	wlog("start of callsx", NULL);

	/* see if already linked */
	if(sx_object != NULL) {
		fprintf(stderr, "callsx: sx_object already linked\n");
		return 0;
	}

	/* open the dynamic shared object */
	sx_object = dlopen(DYNSONAME, RTLD_NOW);
	if(sx_object == NULL) {
		fprintf(stderr, "callsx: dlopen of %s failed--%s\n",
			DYNSONAME, dlerror());
		exit(1);
	}

	/* look up the routine name in it */
	sx_routine = (int (*)())dlsym(sx_object, DYNSOROUTINE);
	if(sx_routine == NULL) {
		fprintf(stderr, "callsx: dlsym %s not found\n",
			DYNSOROUTINE);
		exit(1);
	}

	/* invoke the routine */
	do {
		i = (*sx_routine)();
	} while(start+testtime*1e9 > gethrtime());

	closesx();
	sprintf(buf, "end of callsx, %s returned %d",
		DYNSOROUTINE, i);
	wlog(buf, NULL);

	whrvlog( (gethrtime() - start), (gethrvtime() - vstart),
		"callsx", NULL);

	return 0;
}

/*=======================================================*/
/* closesx -- close a DSO */
void
closesx(void)
{

	/* Log the event */
	wlog("start of closesx", NULL);
 
	/* ensure already linked */
	if(sx_object == NULL) {
		fprintf(stderr, "closesx: sx_object not linked\n");
		exit(1);
	}

#if 0
	/* close the dynamic shared object */
	rc = dlclose(sx_object);
	if(rc != 0) {
		fprintf(stderr, "closesx: dlclose() failed--%s\n",
			dlerror());
		exit(1);
	}

	/* clear the pointer */
	sx_object = NULL;
#endif
	wlog("end of closesx", NULL);

	return;
}
#else /* NONSHARED */

int callsx(int i) { return 0;}
void closesx(void) { return;}

#endif	/* NONSHARED */
