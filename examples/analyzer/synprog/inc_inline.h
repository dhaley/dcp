/* Copyright 02/04/2000 Sun Microsystems, Inc. All Rights Reserved */

#if COMPILER(SUN)
#pragma inline (ext_inline_code)
#else
void ext_inline_code() __attribute__ ((always_inline));
#endif


void
ext_inline_code(int n)
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
