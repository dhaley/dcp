/* Copyright 2002 Sun Microsystems, Inc. All Rights Reserved
 *
 * free_list.c
 *
 */

#include <limits.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include "memtest.h"

void free_list(struct cust_rec *lp)

{
struct cust_rec *curr_ptr;
struct cust_rec *tmp_ptr;

curr_ptr = lp;
while (curr_ptr->next != NULL)
	{
	printf("Freeing Node With Customer Name = %s\n", curr_ptr->cust_name);
	tmp_ptr = curr_ptr;
	curr_ptr = curr_ptr->next;
	free(tmp_ptr);
	}
}
