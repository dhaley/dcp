/* Copyright 02/04/2000 Sun Microsystems, Inc. All Rights Reserved */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "stopwatch.h"

/*=======================================================*/
/*	endcases - examine some wierd endcases of programming style
 *		test cases for inlined code, macros, #included code, ...
 */
void	inc_func(int);
void	inc_brace(int);
void	inc_body(int);
void	inc_entry(int);
void	inc_middle(int);
void	inc_exit(int);
void	macro_code(int);
void	ext_macro_code(int);
void	inline_code(int);
static	void	s_inline_code(int);
void	ext_inline_code(int);

#if COMPILER(SUN)
#pragma inline(inline_code)
#pragma inline(s_inline_code)
#else
void inline_code() __attribute__ ((always_inline));
void s_inline_code() __attribute__ ((always_inline));
#endif

#include "inc_inline.h"

int	n;

/* define a macro that burns CPU time */
#define burncpu(nn) \
	x = 0; \
	for(j=0; j< (nn * 1000000); j++) { \
		 x = x + 1; \
	} \
	;

int
endcases(int n)
{
	hrtime_t	start;
	hrtime_t	vstart;

	start = gethrtime();
	vstart = gethrvtime();

	/* Log the event */
	wlog("start of endcases", NULL);

	if(n ==0) {
		n = 4;
	}
	
	do {
	/* test inlines */
	inline_code(n);
	s_inline_code(n);
	ext_inline_code(n);

	/* test macros */
	macro_code(n);
	ext_macro_code(n);

	/* test various cases of #include'd code */
	inc_func(n);
	inc_brace(n);
	inc_body(n);
	inc_entry(n);
	inc_middle(n);
	inc_exit(n);
	} while(start+testtime*1e9 > gethrtime());

	whrvlog(gethrtime()-start, gethrvtime()-vstart,
		"endcases", NULL);

	return 0;
}

/* spend time in a inline locally-defined */
void
inline_code(int n)
{
	volatile long x;
	int jmax;
	int j;

	jmax = n * 2000000;
	x = 0;
	for(j=0; j<jmax; j++) {
		 x = x + 1;
	}
}

/* spend time in a static inline locally-defined */
static void
s_inline_code(int n)
{
	volatile long x;
	int jmax;
	int j;

	jmax = n * 2000000;
	x = 0;
	for(j=0; j<jmax; j++) {
		 x = x + 1;
	}
}

/* spend time in a macro locally-defined */
void
macro_code(int n)
{
	volatile long x;
	int j;

	burncpu(n);
}

/* spend time in a macro externally-defined */
#include "inc_macro.h"
void
ext_macro_code(int n)
{
	volatile long x;
	int j;

	extburncpu(n);
}

#include "inc_func.h"

void
inc_brace(int n)
#include "inc_brace.h"

void
inc_body(int n)
{
#include "inc_body.h"
}

void
inc_entry(int n)
#include "inc_entry.h"
	{
	    volatile float x;
	    int j, jmax;

	    jmax = n * 2000000;
	    x = 0.0;
	    for(j=0; j<jmax; j++) {
		 x = x + 1.0;
	    }
	}
}

void
inc_middle(int n)
{
	{
	    volatile float x;
	    int j, jmax;

	    jmax = n * 2000000;
	    x = 0.0;
	    for(j=0; j<jmax; j++) {
		 x = x + 1.0;
	    }
	}
#include "inc_body.h"
	{
	    volatile float x;
	    int j, jmax;

	    jmax = n * 2000000;
	    x = 0.0;
	    for(j=0; j<jmax; j++) {
		 x = x + 1.0;
	    }
	}
}

void
inc_exit(int n)
{
	{
	    volatile float x;
	    int j, jmax;

	    jmax = n * 2000000;
	    x = 0.0;
	    for(j=0; j<jmax; j++) {
		 x = x + 1.0;
	    }
	}
#include "inc_exit.h"

