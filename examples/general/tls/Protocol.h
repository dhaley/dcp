/* Copyright 2003 Sun Microsystems, Inc. All Rights Reserved
 */

#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <string>
using namespace std;

#include "URI.h"

class Protocol {
 public:
  virtual ~Protocol(){}
  virtual long getSize(URI uri) = 0;
  virtual int getData(URI uri, char buffer[], long start, long end) = 0;
};

#endif
