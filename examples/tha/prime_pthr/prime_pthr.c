/* 
 * Copyright 04/17/07 Sun Microsystems, Inc. All Rights Reserved 
 * @(#)prime_pthr.c 1.3 07/04/17 SMI 
 */


#include <stdio.h>
#include <math.h>
#include <pthread.h>

#define THREADS 4
#define N 10000

int primes[N];
int pflag[N];
int total = 0;

int is_prime(int v)
{
    int i;
    int bound = floor(sqrt(v)) + 1;

    for (i = 2; i < bound; i++) {
        /* no need to check against known composites */ 
        if (!pflag[i])
            continue;
        if (v % i == 0) {
            pflag[v] = 0;
            return 0;
        }
    }
    return (v > 1); 
}

void *work(void *arg)
{
    int start;
    int end;
    int i;

    start = (N/THREADS) * (*(int *)arg);
    end = start + N/THREADS;
    for (i = start; i < end; i++) {
        if ( is_prime(i) ) {
            primes[total] = i;
            total++;        
        }
    }
    return NULL;
}

int main(int argn, char **argv)
{
    int i;
    pthread_t tids[THREADS-1];

    for (i = 0; i < N; i++) {
        pflag[i] = 1; 
    }

    for (i = 0; i < THREADS-1; i++) {
        pthread_create(&tids[i], NULL, work, (void *)&i);
    }

    i = THREADS-1;
    work((void *)&i);
        
    for (i = 0; i < THREADS-1; i++) {
        pthread_join(tids[i], NULL);
    }

    printf("Number of prime numbers between 2 and %d: %d\n",
           N, total);

    return 0;
}
