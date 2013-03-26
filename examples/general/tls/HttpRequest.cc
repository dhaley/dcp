/* Copyright 2003 Sun Microsystems, Inc. All Rights Reserved
 */

#include "HttpRequest.h"

#include <sys/systeminfo.h>
#include <unistd.h>
#include <cassert>
#include <cstdio>


const int HttpRequest::GET  = 1;
const int HttpRequest::HEAD = 2;
const string HttpRequest::CRLF = string("\r\n");

HttpRequest::HttpRequest(int t)
{
  setRequestType(t);
  defaults();
}
HttpRequest::HttpRequest(int t, string res)
{
  setRequestType(t);
  setResource(res);
  defaults();
}
void HttpRequest::setRequestType(int type)
{
  if(type != GET && type != HEAD){
    fprintf(stderr, "Unknown Request type: %d\n", type);
    assert(0);
  }
  reqType = type;
}
int HttpRequest::getRequestType()
{
  return reqType;
}
int HttpRequest::setHeader(string key, string value)
{
  string s = key;
  s.append(value);
  headers.push_back(s);
  return 1;
}
string HttpRequest::GET_STR(string res)
{
  string s = string("GET ");
  s.append(res);
  s.append(" HTTP/1.1");
  s.append(CRLF);
  return s;
}
string HttpRequest::HEAD_STR(string res)
{
  string s = string("HEAD ");
  s.append(res);
  s.append(" HTTP/1.1");
  s.append(CRLF);
  return s;
}
void HttpRequest::setResource(string file)
{
  resource = file;
}
string HttpRequest::asString()
{
  string http_message;
  if(getRequestType() == HEAD)
    http_message = HEAD_STR(resource);
  else if(getRequestType() == GET)
    http_message = GET_STR(resource);
  else {
    fprintf(stderr, "Invalid request type\n");
    assert(0);
  }
  for(int i = 0; i < headers.size(); i++){
    http_message.append( headers[i]);
    http_message.append( CRLF );
  }
  http_message.append(CRLF);
  return http_message;
}
int HttpRequest::pipeToSocket(int sock)
{
  int length = 0;
  string http_message = asString();
  //cerr << http_message <<endl;
  length = write(sock, http_message.c_str(), 
									http_message.size()); 
  return length;
}

void HttpRequest::defaults()
{
  headers.push_back("User-Agent: Mozilla-SWARMGET");
  headers.push_back("Accept:text/html, image/gif, image/jpeg, *");
  char localhost[128];
  sysinfo(SI_HOSTNAME, localhost, 128);
  string s = string("Host:");
  s.append(localhost);  
  headers.push_back(s);
}
