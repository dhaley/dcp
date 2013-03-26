/* Copyright 02/04/2000 Sun Microsystems, Inc. All Rights Reserved */
/*=======================================================*/
/* parameters defining various tasks */
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "stopwatch.h"


#define	DYNSOROUTINE	"so_cputime"
#define	DYNSONAME	"./so_syn.so"

/* callso -- dynamically link a shared object, and call a routine in it */

#ifndef NONSHARED

static	void	*so_object = NULL;
static	void	closeso(void);

int
callso(int k)
{
	int i;
	int (*so_routine)();
	char	buf[1024];
	hrtime_t	start;
	hrtime_t	vstart;

	start = gethrtime();
	vstart = gethrvtime();
 
	/* Log the event */
	wlog("start of callso", NULL);

	/* see if already linked */
	if(so_object != NULL) {
		fprintf(stderr, "callso: so_object already linked\n");
		return 0;
	}

	/* open the dynamic shared object */
	so_object = dlopen(DYNSONAME, RTLD_NOW);
	if(so_object == NULL) {
		fprintf(stderr, "callso: dlopen of %s failed--%s\n",
			DYNSONAME, dlerror());
		exit(1);
	}

	/* look up the routine name in it */
	so_routine = (int (*)())dlsym(so_object, DYNSOROUTINE);
	if(so_routine == NULL) {
		fprintf(stderr, "callso: dlsym %s not found\n",
			DYNSOROUTINE);
		exit(1);
	}

	/* invoke the routine */
	do {
		i = (*so_routine)();
	} while(start+testtime*1e9 > gethrtime());

	closeso();
	sprintf(buf, "end of callso, %s returned %d",
		DYNSOROUTINE, i);
	wlog(buf, NULL);

	whrvlog( (gethrtime() - start), (gethrvtime() - vstart),
		"callso", NULL);

	return 0;
}

/*=======================================================*/
/* closeso -- close a DSO */
void
closeso(void)
{
	int rc;

	/* Log the event */
	wlog("start of closeso", NULL);
 
	/* ensure already linked */
	if(so_object == NULL) {
		fprintf(stderr, "closeso: so_object not linked\n");
		exit(1);
	}

	/* close the dynamic shared object */
	rc = dlclose(so_object);
	if(rc != 0) {
		fprintf(stderr, "closeso: dlclose() failed--%s\n",
			dlerror());
		exit(1);
	}

	/* clear the pointer */
	so_object = NULL;
	wlog("end of closeso", NULL);

	return;
}
#else /* NONSHARED */

int callso(int i) { return 0;}
void closeso(void) { return;}

#endif	/* NONSHARED */
