/* Copyright 2003 Sun Microsystems, Inc. All Rights Reserved
 */

#include "Bins.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#include <cstdio>
#include <cstdlib>
#include <cassert>
using namespace std;

const char* Bins::tmpdir     = "/tmp";
const char* Bins::bin_prefix = "bins";

Bins::Bins()
{
  tmpfile = tempnam(tmpdir, bin_prefix);
  assert( tmpfile != 0 );
  length = 0;
}

long Bins::writeData(char *data, long len, long pos)
{
  long result = 0;
  fd = open(tmpfile, O_WRONLY | O_CREAT, 0666);

  if(fd < 0 ){
    fprintf(stderr, "Error opening temporary file: %s\n", tmpfile);
    perror("Error code:");
    assert( fd >= 0 );
  }
  if(pos != 0)
    result =  pwrite(fd, data, len, pos);
  else 
    result =  write(fd, data, len); 
  close(fd);
  length = len + pos;
  return result;
}

long Bins::readData(char *data, long len, long pos)
{
  fd = open(tmpfile, O_RDONLY);
  if(fd == -1 ){
    fprintf(stderr, "Error opening temporary file\n");
    perror("Error code:");
    assert( fd >= 0 );
  }
  long result = 0;
  if( pos == 0 )
    result = read(fd, data, len); 
  else 
    result = pread(fd, data, len, pos); 
  close(fd);
  return result;
}
long Bins::size()
{
  return length;
}

Bins::~Bins()
{
  if(tmpfile != 0){
    unlink(tmpfile);
    free(tmpfile);
  }
  if(fd > 0)
    close(fd);
}

void Bins::unit_test()
{
  char tst[] = "abcbdcbdcbdbcdcbdcbdcbdbdcd";
  char buf[128];
  for(int i = 0; i < 10; i++){
    Bins b;
    //b.init();
    assert(b.writeData(tst, 12) > 0);
    assert(b.readData(buf, 10) > 0);
    buf[10] = '\0';
    printf("%d %s %s\n", i, b.tmpfile, buf);
  }
}

