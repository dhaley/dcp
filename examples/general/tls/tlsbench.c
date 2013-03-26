/* Copyright 2003 Sun Microsystems, Inc. All Rights Reserved
 */

#include <pthread.h>
#include <thread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define NUM_THREADS 5
#define NO_KEYS 8
#define LOOP_COUNT 1000000

/* compile as cc -o tlsbench -mt -xO3 tlsbench.c */

static void *thread_func_tls(void *arg);
static void *thread_func(void *arg);

/* global data */
static pthread_t tid[NUM_THREADS];  /* array of thread IDs */
static __thread int keys_tls[NO_KEYS];
static pthread_key_t keys[NO_KEYS]; /* list of keys */

static void *thread_func_tls(void *arg)
{
  int i, j, val;
  for(i = 0; i < LOOP_COUNT; i++){
    for(j = 0; j < NO_KEYS; j++)
      /* now get and set the local values */
      keys_tls[j] = j;
  }
  for(i = 0; i < LOOP_COUNT; i++){
    for(j = 0; j < NO_KEYS; j++){
      val = keys_tls[j];
      if ( val != j ){
	(void) fprintf(stderr, "Error getting val: %d\n", val);
	exit(-1);
      }
    }
  }
  return 0;
}
static void *thread_func(void *arg)
{
  int i, j, val;
  for(i = 0; i < LOOP_COUNT; i++){
    for(j = 0; j < NO_KEYS; j++)
      /* now get and set the local values */
      pthread_setspecific(keys[j], (const void *)&j);
  }
  for(i = 0; i < LOOP_COUNT; i++){
    for(j = 0; j < NO_KEYS; j++){
      val = *(int *)(pthread_getspecific(keys[j]));
      if ( val != j ){
	(void) fprintf(stderr, "Error getting val: %d\n", val);
	exit(-1);
      }
    }
  }
  return 0;
}

int main(int argc, char *argv[])
{
  int i;
  hrtime_t start, end;
  for ( i = 0; i < NO_KEYS; i++)
    pthread_key_create(&keys[i], NULL);
  /* first time get/set */
  start = gethrtime();
  for ( i = 0; i < NUM_THREADS; i++)
    pthread_create(&tid[i], NULL, thread_func, NULL);
  for ( i = 0; i < NUM_THREADS; i++)
    pthread_join(tid[i], NULL);
  end = gethrtime();
  (void) printf("Avg time using pthread_[get|set] = %.2f sec\n", (end - start)/1000000000.0 );
  /* now time tls */
  start = gethrtime();
  for ( i = 0; i < NUM_THREADS; i++)
    pthread_create(&tid[i], NULL, thread_func_tls, NULL);
  for ( i = 0; i < NUM_THREADS; i++)
    pthread_join(tid[i], NULL);
  end = gethrtime();
  (void) printf("Avg time using TLS               = %.2f sec\n", (end - start)/1000000000.0 );
  return 0;
}
