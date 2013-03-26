/* Copyright 2003 Sun Microsystems, Inc. All Rights Reserved
 */

#ifndef STORAGEBINS_H
#define STORAGEBINS_H

#include <string>
#include <vector>
using namespace std;

#include "URI.h"
#include "Bins.h"

/* Bins are either
 * RED: bin is empty
 * Yellow: bin is not empty
 * GREEN: Bin is full, and has been written to disk
 */

class StorageBins {
 public:
  StorageBins() {}
  int init(URI uri, int nobins);
  int writeData(int binno, char data[], long length);
  int getStatus();
  int getBinStatus(int binno);
  int writeToFile(const char* file );
  int getNoBins();
  int getNoEmptyBins();
  void setBinStatus(int no, int s);
  static void unit_test();
  int getEmptyBin();
  ~StorageBins();

  static const char RED;
  static const char YELLOW;
  static const char GREEN;
 private:
  int noBins;
  Bins *binArray;
  char *status;
	int empty_bins;
};
#endif
