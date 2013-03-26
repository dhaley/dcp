/* Copyright 2003 Sun Microsystems, Inc. All Rights Reserved
 */

#ifndef PROTOCOLFACTORY_H
#define PROTOCOLFACTORY_H

#include "URI.h"
#include <string>
using namespace std;

#include "Protocol.h"
#include "HttpProtocol.h"

class ProtocolFactory {
 public:
  static Protocol* getProtocol(URI uri){
    if(uri.getProtocol() == "http")
      return new HttpProtocol(uri);
    return 0;
  }
};

#endif

