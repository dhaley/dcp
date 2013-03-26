/* Copyright 02/04/2000 Sun Microsystems, Inc. All Rights Reserved */

{
	volatile float x;
	int jmax;
	int j;

	jmax = n * 2000000;
	x = 0.0;
	for(j=0; j<jmax; j++) {
		 x = x + 1.0;
	}
}
