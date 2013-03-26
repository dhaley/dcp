/* Copyright 2003 Sun Microsystems, Inc. All Rights Reserved
 */
#ifndef HTTPPROTOCOL_H
#define HTTPPROTOCOL_H

#include "Protocol.h"
#include "URI.h"

#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <sys/utsname.h> 
#include <sys/systeminfo.h> 
#include <unistd.h> 
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <cstring>
#include <cstdio>
using namespace std;

class HttpProtocol: public Protocol {
 public:
  HttpProtocol(URI u);
  virtual ~HttpProtocol();
  long     getSize(URI uri);
  int      getData(URI uri, char buffer[], long start, long size);
 private:
  URI curr_uri;
  int sock;
};

#endif
