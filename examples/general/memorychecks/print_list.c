/* Copyright 2002 Sun Microsystems, Inc. All Rights Reserved
 *
 * print_list.c
 *
 */

#include <limits.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include "memtest.h"

void print_list(struct cust_rec *lp)

{
struct cust_rec *curr_ptr;
struct cust_rec *tmp_ptr;

curr_ptr = lp;
while (curr_ptr != NULL)
	{
	printf("Customer Name = %s\n", curr_ptr->cust_name);
	curr_ptr = curr_ptr->next;
	}
}
