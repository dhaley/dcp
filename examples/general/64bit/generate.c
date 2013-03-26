/*
 * Copyright 2001,2002 Sun Microsystems, Inc. All Rights Reserved
 *
 * generate.c --
 *      Create a data set for sorting. The data is a set of random numbers 
 *      generated and stored in memory and then written to a file.
 */


#include "common.h"

#include <time.h>                            /* time()                       */

static    time_t    seed;                    /* seed for random # generator  */

long      array_len    = 1000000L;           /* Max # of items stored in 
						memory at any time           */
static    item_type *data = NULL;            /* array for to store items     */


static void gen_init(long);
static void gen_fill_array(long);
static void gen_clean_up(void);

/* Initialization work */
static void 
gen_init(long nmax) 
{
  int ntries = 5;
  size_t size = 
      (array_len = (array_len > nmax ? nmax : array_len)) * ITEM_SIZE;
  while (ntries-- > 0 && array_len > 0) {
    data = (item_type *) malloc(size);
    if (data == NULL) {
      printf("malloc of %ld bytes failed\n. Will try half of it ..\n", size);
      array_len /= 2L;
      size = ITEM_SIZE * array_len;
    } else {
      printf("malloc successful;array size = %ld bytes, len=%ld \n", 
              size, array_len);
      break;
    }
  }

  if (data == NULL) 
    error("Unable to allocate space");

  seed = time(0);            /* use the time value as seed for the generator */
  srand(seed);
}

/* Fill data array with upto "count" items. 
 * Assumes count is always <= array_len.
 */
static void
fill_array(long count)
{
  int random_num;
  long i;

  assert((count <= array_len) ? VALID : ERROR); /* count always <= array_len */
  for (i = 0; i < count; i++) {
    random_num = rand() % ITEM_MAX;
    data[i] = random_num;
  }
}

/* Calls fill_array until nmax items are processed. Between calls, transfers
 * array to file. The current array size is bounded by a count.
 */
void
gen_data(long nmax)
{
  long   ngenerated  = 0;   
  long   ntogenerate = 0;    
  long   nremain     = nmax;

  gen_init(nmax);
  while (ngenerated < nmax) {
    ntogenerate = MIN_OF(nremain, array_len);

    fill_array(ntogenerate);/* generate upto "ntogenerate" items into array */
    io_write(data, ITEM_SIZE*ntogenerate);

    ngenerated  += ntogenerate;                  
    nremain     -= ntogenerate;                  

#ifdef DEBUG
    printf("generated: %15ld numbers; remaining: %15ld \n",ngenerated,nremain);
#endif
  } 
  printf("\n\n");
  printf("total %ld (%ld max) items generated;\n", ngenerated, nmax);
  printf("size of data file = %ld bytes\n",  io_size());

  gen_clean_up();
}

/* Give up any resources we're holding.  */
static void 
gen_clean_up(void)
{
  free(data);
}
