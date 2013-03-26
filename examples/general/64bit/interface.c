/*
 * Copyright 2001,2002 Sun Microsystems, Inc. All Rights Reserved
 *
 * interface.c -- 
 *      All interactions with user are handled in this file. 
 *
 */
#include "common.h"

int   sorted    = 0;                        /* flag set when data is sorted */

int
options(void)
{
    /* options: 0 - data value at i,
     *          1 - data in range i to j, 
     *          2 - quit
     *          3 - sort, if data not sorted yet
     */
          
    int opt = 2;
    printf((sorted ? "===========After  sorting===== \n" 
	           : "===========Before sorting===== \n")
	   );

    printf("Choose a # against the options listed below:\n"
	   "\t(0) data[i]?\n"
	   "\t(1) data[i....j]?\n"
	   "\t(2) Quit?\n"
	   );
    printf(sorted ? "" : "\t(3) Sort?\n");
    printf("Enter your choice: ");
    scanf("%d", &opt);
    return opt;
}
/* Macro to check if 'index' falls within range [0 - max) of array */
#define RANGE(a, MAX)  ((a) >= 0L && (a) < (MAX))

void
show_data(item_type *data, long max)
{
    int choice = -1;
    long val, val2;
    do {
	choice = options();

	switch(choice) {
	case 0:
	    printf("data[i=?]; i = ");
	    scanf("%ld", &val);
	    if (RANGE(val, max))
		printf("data[%ld] = %d\n", val, *(data + val));
	    else
		printf("invalid i; range of i is [%ld ... %ld]\n", 0L, max -1);
	    break;
	case 1:
	    printf("data[i=?...j=?]; i = ");
	    scanf("%ld", &val);
	    printf("data[i=%ld...j=?]; j = ", val);
	    scanf("%ld", &val2);
	    if (val2 >= val && RANGE(val, max) && RANGE(val2, max)) {
		long index = val;
		printf("\n--- Showing #s from %ld to %ld ---\n", val, val2);
		printf("%5d:\t",index);
		for (index = val; index <= val2; index++) {
		    printf("%5ld ", data[index]);
		    /*if (index != 0 && index % 9 == 0) printf("\n\t");*/
		    if ((index + 1) % 10 == 0 && index +1 <= val2)
			printf("\n%5d:\t", index+1);
		}
		printf("\n\n");
	    } else
		printf("invalid i or j; range is [%ld ... %ld]; i <= j\n",
		       0L, max -1L);
	    break;
	case 3:
	    if (!sorted) {
		printf("sorting the data ...");
		sort_data(data, max);
		sorted++;
		printf("done\n");
	    } else
		printf("Data already sorted.\n");
	    break;
	case 2:
	    printf("quitting ...\n");
	    choice = -1;
	    break;
	default:
	    printf("Didn't understand your option!!\n");
	}
    } while (choice != -1);
}
