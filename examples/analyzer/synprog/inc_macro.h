/* Copyright 02/04/2000 Sun Microsystems, Inc. All Rights Reserved */
/* define a macro that burns CPU time */
#define extburncpu(n) \
	x = 0.0; \
	for(j=0; j<n*1000000; j++) { \
		 x = x + 1.0; \
	} \
	;
