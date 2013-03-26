/* Copyright 2003 Sun Microsystems, Inc. All Rights Reserved
 */

#include "StorageBins.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <strings.h>

#include <cstdio>
#include <cstdlib>
#include <cassert>
using namespace std;

/* Bins can be one of RED, YELLOW or GREEN
 * RED means no thread has requested bin to write
 * YELLOW means one or more threads are trying to
 * fill the bin
 * GREEN means a thread has successfully written
 * data to the bin
 */
const char StorageBins::RED       = 'R';
const char StorageBins::YELLOW    = 'Y';
const char StorageBins::GREEN     = 'G';

int StorageBins::init(URI uri, int nobins)
{
  noBins = nobins;
  int j = RED;
  binArray = new Bins[nobins];
  status = new char[nobins+1];
  for(int i = 0; i < noBins; i++){
    status[i] = j;
  }
	status[noBins]='\0';
	empty_bins = noBins;
  return 1;
}
StorageBins::~StorageBins()
{
  delete[] binArray;
  delete[] status;
}
int StorageBins::getEmptyBin()
{
	int no = noBins;
	char *c;
	for(int i = 0; i < noBins; i++)
		if(status[i] == RED){
			status[i]=YELLOW;
			return i;
		}
	for(int i = 0; i < noBins; i++)
		if(status[i] == YELLOW)
			return i;
  return -1;
}
int StorageBins::writeData(int binno, char data[], long length)
{
  Bins *b = &binArray[binno];
	/*
  if(status[binno] == GREEN)
    fprintf(stderr, "Possible contamination of Bin:%d\n",
										binno);
	*/
  int result = b->writeData(data, length);
  if (result != -1){
    status[binno] = GREEN;
		empty_bins--;
	}
  return result;
}

int StorageBins::getStatus()
{
  return GREEN;
}
void StorageBins::setBinStatus(int no, int s)
{
  status[no] = s;
}
int StorageBins::getBinStatus(int binno)
{
  return status[binno];
}

int StorageBins::writeToFile(const char* file)
{
  /* get all the bins and collect them */
  int fd = open(file, O_WRONLY | O_CREAT |O_TRUNC,
									S_IREAD|S_IWRITE);
  if (fd < 0){
    fprintf(stderr, "Error opening file:%s\n", file);
    return -1;
  }
  char *buf;
  long bin_size, result;
  bin_size = binArray[0].size();
	if(bin_size <= 0){
		fprintf(stderr, "Error saving bins to file: bin_size \
										was %d\n", bin_size);
		return -1;
	}
  buf = new char[bin_size + 1];
  for(int i = 0; i < noBins; i++){
    if(status[i] != GREEN){
      fprintf(stderr, "Internal error: trying to write to bin %d ", i);
      fprintf(stderr, "with non-green status:%c\n", status[i]);
      assert(0);
    }
    bin_size = binArray[i].size();
    result = binArray[i].readData(buf, bin_size);
    
    if(result != bin_size){
			fprintf(stderr, "Cant read bin: %d\n", i);
      perror("unable to read bin");
      //assert(0);
    }
    
    result = write(fd, buf, bin_size);
    if(result != bin_size){
      fprintf(stderr, "Error writing to file %s\n", file);
      perror("Error:");
      //assert(0);
    }
    
  }
  delete[] buf;
  close(fd);
  return 1;
}

int StorageBins::getNoBins()
{
  return noBins;
}

int StorageBins::getNoEmptyBins()
{
  return empty_bins;
}
void StorageBins::unit_test()
{
  StorageBins sb;
	int i;
  URI u("http://pastwatch.eng");
  char tst[] = "abcbdcbdcbdbcdcbdcbdcbdbdcd";
  char buf[128];
  sb.init(u, 10);
  for(i = 0; i < sb.getNoBins(); i++){
    sb.writeData(i, tst, 12);
    sb.setBinStatus(i, StorageBins::GREEN);
  }
  sb.writeToFile("/tmp/a");
	StorageBins s;
	s.init(u, 5);
	while((i = s.getEmptyBin())!= -1){
		fprintf(stdout, "Bin free:%d\n", i);
		s.writeData(i, tst, 12);
	}
}

#ifdef MAIN
int main(int argc, char *argv[])
{
		StorageBins::unit_test();
}
#endif
