/*
 * Copyright 2001,2002 Sun Microsystems, Inc. All Rights Reserved
 *
 *  sort.c --
 *      Sorts a huge data set in a file using the quicksort method. The
 *      data is assumed to be stored in (or mapped to) an array of 
 *      "item_type"s.
 */

#include "common.h"

#define DEREF(i) *((const item_type *) (i))


static int
compare(const void *i, const void *j)
{
  if ( DEREF(i) > DEREF(j) ) return (1);
  if ( DEREF(i) < DEREF(j) ) return (-1);
  return (0);
}


#define entry(pos) sort_table[pos]

static void 
swap_entry(item_type *table, long i, long j)
{
  item_type temp = table[i];
  table[i] = table[j];
  table[j] = temp;
}

static void 
quicksort (item_type *sort_table, long l, long r)
{ 
   /* int i, j, x; */
  
  long    i;
  long    j;
  item_type x;

  i = l;
  j = r;
  x = sort_table[ ((l + r) / 2) ];
  do {
    while (sort_table[i] < x)
      i++;
    while (x < sort_table[j])
      j--;
    if (i <= j) {
      swap_entry (sort_table, i, j);
      i++;
      j--; }} while (i <= j);
  if (l < j)
    quicksort (sort_table, l, j);
  if (i < r)
    quicksort (sort_table, i, r); }



void
sort_data(item_type *data, size_t nelements)
{
  static int compare(const void *, const void *);

/*
  qsort((item_type *) data, nelements, ITEM_SIZE, compare);
*/
  quicksort(data, 0, nelements - 1);
}                                                                         
