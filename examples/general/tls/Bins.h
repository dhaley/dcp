/* Copyright 2003 Sun Microsystems, Inc. All Rights Reserved
 */

#ifndef BINS_H
#define BINS_H

#include <string>
using namespace std;

class Bins {
 public:
  Bins();
  ~Bins();
  long writeData(char *data, long length, long pos = 0);
  long readData (char *data, long length, long pos = 0);
  long size();
  static void unit_test();
 private:
  char *tmpfile;
  int   fd;
  long  length;
  static const char* tmpdir;
  static const char* bin_prefix;
};

#endif
