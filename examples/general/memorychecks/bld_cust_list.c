/* Copyright 2002 Sun Microsystems, Inc. All Rights Reserved
 *
 * bld_cust_list.c 
 *
 */

#include <limits.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include "memtest.h"

struct cust_rec *build_customer_list(FILE *cust_file)

{
char line[1000];
struct cust_rec *curr_cust_ptr;
struct cust_rec *new_cust_ptr;
struct order_rec *curr_order_ptr;
struct order_rec *new_order_ptr;
struct cust_rec *top_of_list;
char *return_str;


curr_cust_ptr = NULL;
curr_order_ptr = NULL;
while (fgets (line, sizeof(line), cust_file) != NULL) 
	{
 	line[strlen(line) - 1] = '\0';
	if (strncmp(line, "N", 1) == 0)
	     {
	     new_cust_ptr = (cust_rec *) malloc (sizeof (cust_rec));
#ifdef STRDUP
	     new_cust_ptr->cust_name = strdup(line+2);
#else
	     strcpy(new_cust_ptr->cust_name, line+2);
#endif
	     new_cust_ptr->cust_orders = NULL;
	     new_cust_ptr->next = NULL;
	     curr_order_ptr = NULL;
	     if (curr_cust_ptr == NULL)
	        top_of_list = new_cust_ptr;
	     else
	        curr_cust_ptr->next = new_cust_ptr;
	     curr_cust_ptr = new_cust_ptr;
	     }
	else if (strncmp(line, "O", 1) == 0)
	     {
	     new_order_ptr = (order_rec *) malloc (sizeof (order_rec));
	     new_order_ptr->order_num = atoi(line+2);
	     new_order_ptr->next_order = NULL;
	     if (curr_order_ptr == NULL)
	         curr_cust_ptr->cust_orders = new_order_ptr;
	     else
	        curr_order_ptr->next_order = new_order_ptr;
	     curr_order_ptr = new_order_ptr;
	     }
	else
	     {
	     printf("ERROR: Invalid Data in Database!\n");
	     }
	}

return(top_of_list);

}
