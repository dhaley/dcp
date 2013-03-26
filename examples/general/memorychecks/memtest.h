/* Copyright 2002 Sun Microsystems, Inc. All Rights Reserved
 *
 * memtest.h
 *
 */

#define ARRAY_SIZE	5

struct emp_rec {
  char *name;
  int  emp_num;
  struct emp_rec *prev;
  struct emp_rec *next;
  };

typedef struct emp_rec emp_rec;

struct order_rec {
   int order_num;
   struct order_rec *next_order;
   };

struct cust_rec {
#ifdef STRDUP
   char *cust_name;
#else
   char cust_name[25];
#endif
   struct order_rec *cust_orders;
   struct cust_rec *next;
   };

typedef struct cust_rec cust_rec;
typedef struct order_rec order_rec;
