/* Copyright 2003 Sun Microsystems, Inc. All Rights Reserved
 */

#include "Protocol.h"
#include <pthread.h>
#include <thread.h>
#include <sys/lwp.h>

#include "ProtocolFactory.h"
#include "Bins.h"
#include "StorageBins.h"
#include "progress-bar.h"

/* This is what I call a download accelator or da.
 * We try to speedup a download by breaking
 * the download into several chunks and downloading
 * the chunks seperately, possibly from different
 * mirros. You can control the number of threads by
 * invoking da with the -n switch
 *
 * This is only to illustrate how TLS can be used to
 * parallelize a program which uses several shared
 * global variables.
 *
 * The program is intensionally written to use
 * global variables.
 *
 * driver initializes all components and downloads
 * the chunks.
 *
 * Protocol is used to virtulize the underlying protocol.
 * This makes it very easy to support more protocols
 *
 * HttpProtocol, HttpRespose, HttpRequest all implement
 * various parts of the HTTP protocol.
 *
 * StorageBins maintains several Bins. While downloading
 * a large file, its good if we save the chunks on disk
 * rather than in memory. Bins uses tempnam(3C) function
 * call to save these chunks in file (in /tmp as bins*).
 * StorageBins also tracks the status of each of the bins.
 * 
 */

/* global variables */
static const long STEP = 1024*1024;
static URI u;
static StorageBins sb;
static long size;

/* Thread Local Variables 
 * Thread local variables are prefixed with the __thread 
 * attribute. There is no limit on the number of TLS
 * variables you can create.
 *
 * If your code uses Microsoft notation for TLS, you can 
 * define the following macros in your code to emulate 
 * that behavior.
 * #define TlsGetValue(a) a
 * #define TlsSetValue((a),(b)) (a)=(b)
 *
 * GCC uses the same syntax as the Sun Compiler.
 *
 * In this program, each thread uses the same
 * data buffer to retreive data.
 */

/* HACK FOR NON TLS use
 */
#ifndef TLS
#define __thread 
#endif
__thread static char data[STEP];
__thread static Protocol *p;

#ifdef	__cplusplus
extern "C" {
#endif
  static void *download_chunk(void *arg);
	static int download(char *str, int no_threads);
#ifdef	__cplusplus
} 
#endif

/* This function is called by every thread.
 * Each thread requests an empty bin
 * For binno, the thread downloads data between
 * [step*binno, step]. For the last bin, the thread
 * will download [step*binno, end]
 */
static void *download_chunk(void *arg)
{
  int i, j, val;
  long start, how_many;
  p = ProtocolFactory::getProtocol(u);
  if(p == NULL){
    fprintf(stderr, "Protocol not supported for %s\n",
	    u.asString().c_str());
    return 0 ;
  }
  int b, status, flag;
  flag = 0;
	/* fill all empty bins, and dump into file */
  while((i = sb.getEmptyBin())!= -1){
    start = i*STEP;
    how_many = (start + STEP <= size) ? STEP : size - start;
    status = p->getData(u, data, start, how_many);
    if(status < 0){
      fprintf(stderr, "Error occured while trying to get data\n");
      break;
    }
    sb.writeData(i, data, how_many);
  }
  delete p;
  return 0;
}

static void usage(char *name)
{
  fprintf(stderr, "Usage: %s [-n no of threads] [-h] url\n", name);
}

int main(int argc, char *argv[])
{
  char* str=NULL;
  /* process arguments */
  extern char *optarg;
  extern int optind;
  int errflag = 0;
  int c;
  int no_of_threads = 1; /* use 1 as default */
  while ((c = getopt(argc, argv, "hn:")) != EOF)
    switch (c) {
    case 'n':
    case 'N':
      no_of_threads = atoi(optarg);
			if(no_of_threads <= 0)
				errflag++;
      break;
		case 'h':
    case '?':
      errflag++;
      break;
    }
  str = argv[optind];
  if ((errflag) || (str == NULL)) {
    usage(argv[0]);
    exit(-1);
  }
	return download(str, no_of_threads);
}

static int download(char *str, int no_threads)
{
	Protocol *p1;
	int nobins;
	const char *opfile;
#ifdef TLS
  pthread_t *tid = new pthread_t[no_threads];
#endif

  u.setURI(str);
  p1 = ProtocolFactory::getProtocol(u);
  if(p1 == NULL){
    fprintf(stderr, "Protocol not supported for %s\n", str);
#ifdef TLS
		delete tid;
#endif
    return -1;
  }
  size = p1->getSize(u);
  if(size < 1){
    /* error message would already be printed, so just quit */
#ifdef TLS
		delete tid;
#endif
    return -1;
  }
  delete p1;

  nobins = (int)(size/STEP) + 1;
  if(size == STEP)
    nobins = 1;
	/* if there is only 1 bin, use only 1 thread */
	if(nobins == 1)
		no_threads = 1;
  sb.init(u, nobins);
#ifdef TLS
  for(int i = 0; i < no_threads; i++)
    pthread_create(&tid[i],  NULL, download_chunk, 0);
#endif
  while(sb.getNoEmptyBins() > 0){
    int percent;
    percent = (nobins - sb.getNoEmptyBins()) * 100;
    percent /= nobins;
    draw_progress_bar(percent);
#ifndef TLS
		download_chunk(0);
#else
    sleep(1);
#endif
  }
  draw_progress_bar(100);
#ifdef TLS
  for (int i = 0; i < no_threads; i++)
    pthread_join(tid[i], NULL);
	delete tid;
#endif
	opfile = u.getFilename().c_str();
  sb.writeToFile(opfile);
  printf("\n '%s' saved (%ld bytes)\n", opfile, size);
}

