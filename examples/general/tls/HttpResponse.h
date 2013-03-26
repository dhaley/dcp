/* Copyright 2003 Sun Microsystems, Inc. All Rights Reserved
 */

#ifndef INCLUDE_HTTPRESPONSE_H
#define INCLUDE_HTTPRESPONSE_H

#include <vector>
#include <string>
using namespace std;

class HttpResponse {
 public:
  HttpResponse(int soc) : socket(soc), httpStatus(-1)
    {}
  int   getStatus(){
    return httpStatus;
  }
  long   getContentLength();
  int    readHttpHeader();
  int    readHttpBody(char *data, int length);
  int    getHttpStatus(const char *);
  
 private:
  int         readLine(string& sink);
  long        parseContentLength(string);
  int         socket;
  string      response;
  int         httpStatus;
  long        clength;
};

#endif
