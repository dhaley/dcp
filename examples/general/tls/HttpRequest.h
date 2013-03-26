/* Copyright 2003 Sun Microsystems, Inc. All Rights Reserved
 */

#ifndef INCLUDE_HTTPREQUEST_H
#define INCLUDE_HTTPREQUEST_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class HttpRequest {
 public:
  static const int GET;
  static const int HEAD;

  HttpRequest(int t);
  HttpRequest(int t, string res);
  void   setRequestType(int type);
  int    getRequestType();
  int    setHeader(string key, string value);
  void   setResource(string file);
  int    pipeToSocket(int sock);
  string asString();
 private:
  static string GET_STR(string resource);
  static string HEAD_STR(string resource);
  void defaults();
  int  reqType;

  static const string CRLF;// = string("\r\n");
  string resource;
  vector<string> headers;
};

#endif
