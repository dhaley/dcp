/*
 * Copyright 2001,2002 Sun Microsystems, Inc. All Rights Reserved
 *
 *  main.c
 */
#include "common.h"

char *prog_name = NULL;                      /* argv[0] */

/* generate the data and store in file */
void
gopt_handler(char *fname, long nitems) 
{
  io_creat(fname);
  gen_data(nitems);
  io_close(); 
}

/* map file to memory and sort. clean up */
void 
sopt_handler(char *fname)
{
  long nitems;
  item_type* data = io_map_file(fname);
  nitems          = io_size()/ITEM_SIZE;

  show_data(data, nitems);
  
  io_unmap(data, io_size()); 
  io_close();
}


void
usage(void)
{
  printf("Usage: \n"
    "%s -g <filename> -n <#>  create and sort a data set of n items in file\n"
    "%s -s <filename>         sort data in file\n",
         prog_name, prog_name);

  exit(1);
}

void
main(int argc, char**argv)
{
  char *data_filename = NULL;
  long nitems = -1;
  /* flags to identify what options are specified and to implement:
   *    if -g is specified, -n is mandatory 
   *    -g and -s are exclusive
   */
  int gopt = 0; 
  int nopt = 0;
  int sopt = 0; 

  extern char *optarg;
  extern int optind;
  char c; 

  prog_name = strdup(argv[0]);

  if (argc < 3) usage();
  /* process options */
  while ((c = getopt(argc, argv, "g:s:n:")) != EOF) {
    switch (c) {
    case 'g':
	if (sopt) usage();
	gopt++;
	data_filename = strdup(optarg);
	break;
    case 's':
	if (gopt) usage();
	sopt++;
	data_filename = strdup(optarg);
	break;
    case 'n':
	nopt++;
	nitems = atol(optarg); /* convert to long */
	break;
    case '?':
	usage();
    }
  }
  if (sopt) 
      sopt_handler(data_filename);
  else if (gopt && nopt) { 
      printf("data file = %s\n", data_filename);
      printf("nitems to generate = %ld\n", nitems);
      gopt_handler(data_filename, nitems);
      sopt_handler(data_filename);
  } else
      usage();
}
