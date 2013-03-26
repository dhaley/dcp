/* Copyright 2002 Sun Microsystems, Inc. All Rights Reserved
 *
 * memtest.c
 * 
 * Purpose: The purpose of this example is to provide a means to 
 * exercise the runtime error checking features in the product debugger.
 * Please note that this program has some INTENTIONAL memory access
 * errors and memory leaks.
 *
 */

#include <limits.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include "memtest.h"

void init_array_loc(char *cp);
void init_array(char *array_loc, int size);
struct cust_rec *build_customer_list(FILE *fp);
void print_list(struct cust_rec *lp);
void free_list(struct cust_rec *lp);



main(int argc, char **argv)

{
FILE *fp;
char *cp1;
char *tmp_ptr;
int i;
char cust_file_path[100];
struct cust_rec *ptr;
struct cust_rec *list_top;


cp1 = (char *)malloc(ARRAY_SIZE);
tmp_ptr = cp1;
for (i=0; i<=ARRAY_SIZE; i++)
	{
	init_array_loc(tmp_ptr);
	tmp_ptr++;
	}

cp1 = (char *)malloc(ARRAY_SIZE);
tmp_ptr = cp1;
for (i=0; i<ARRAY_SIZE-1; i++)
	{
	*tmp_ptr = 'b';
	tmp_ptr++;
	}

tmp_ptr = cp1;
for (i=0; i<=ARRAY_SIZE; i++)
	{
	printf("The Value of Element %d = %c\n", i, *tmp_ptr);
	tmp_ptr++;
	}

cp1 = (char *)malloc(ARRAY_SIZE);
tmp_ptr = cp1;
init_array(tmp_ptr, ARRAY_SIZE);

cp1 = (char *)malloc(ARRAY_SIZE);
tmp_ptr = cp1;
init_array(tmp_ptr, ARRAY_SIZE);

if (argc == 1)
	sprintf (cust_file_path, "%s/Customer.db", getenv ("HOME"));
else
	strcpy (cust_file_path, argv[1]);

fp = fopen(cust_file_path, "r");

if (fp == NULL) 
	{
	printf ("Error opening file %s\n", cust_file_path);
	exit (1);
	}

list_top = build_customer_list(fp);

print_list(list_top);
free_list(list_top);

}
