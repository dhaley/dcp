/*
 * Copyright 11/08/06 Sun Microsystems, Inc. All Rights Reserved
 * @(#)hello_race.c 1.1 06/11/08 SMI
 */


#include <stdio.h>
#include <stdlib.h>

#include <omp.h>

void main()
{
   int n = -1;
#pragma omp parallel shared(n)
   {
#pragma omp single
     {
       printf("Number of threads is %d\n",omp_get_num_threads());
     }
     
     n = omp_get_thread_num();

     printf("Hello Data Race World n = %d\n",n);
   }
}
