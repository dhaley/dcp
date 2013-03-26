/* Copyright 2003 Sun Microsystems, Inc. All Rights Reserved
 */

#include "HttpProtocol.h"

#include "HttpRequest.h"
#include "HttpResponse.h"

#include <cassert>
#include <iostream>
using namespace std;

HttpProtocol::HttpProtocol(URI u)
{
  curr_uri = u;
  struct hostent *h;
  struct sockaddr_in sin;
  const char *hostname = u.getHost().c_str();
  h = gethostbyname (hostname); 
  if (h == NULL) {
    fprintf(stderr, "Error  resolving hostname\n");
    perror (hostname);
    exit(-1);
  }

  sin.sin_family = AF_INET;
  sin.sin_port = htons(80);
  memcpy(&sin.sin_addr, h->h_addr, h->h_length);
  /* create socket */
  if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
    fprintf(stderr, "Unable to open socket\n");
    perror("Socket connection:");
    exit(-1);
  }
  /* do the connection */
  if( connect(sock, (struct sockaddr *)&sin, 
	      sizeof(struct sockaddr)) < 0){
    fprintf(stderr, "Error connecting\n");
    perror("connect:");
    exit(-1);
  }
}

HttpProtocol::~HttpProtocol()
{
  close(sock);
}

long HttpProtocol::getSize(URI uri)
{
  /* for http, we do a HEAD */
	assert(uri.asString() == curr_uri.asString());

  string http_message;
  int length;
  HttpRequest hr(HttpRequest::HEAD);
  
  string filename = uri.getCompletePath();
  if(filename[0] != '/')
    filename = string("/") .append(filename);
  hr.setResource(filename);
  
  length = hr.pipeToSocket(sock);
  if(length <= 0){
    fprintf(stderr, "\nError getting size\n");
    perror("write:");
    return -1;
  }
  HttpResponse hres(sock);
  length = hres.readHttpHeader();
  if(length != -1)
    length = hres.getContentLength();
  return length;
}

int HttpProtocol::getData(URI uri, char buffer[], long start, long size)
{
  /* for http, we do a GET */
	assert(uri.asString() == curr_uri.asString());

  string http_message;
  int length;
  char tmp1[128], tmp2[128];
  sprintf(tmp1, "%ld", start);
  sprintf(tmp2, "%ld", start + size);

  HttpRequest hr(HttpRequest::GET);
  string str2 = string("Range: bytes=");
  string str1 = string(tmp1);
  str1.append("-");
  str1.append(tmp2);
  hr.setHeader(str2, str1);
  string filename = uri.getCompletePath(); 
  if(filename[0] != '/')
    filename = string("/").append(filename);
  hr.setResource(filename);
  
  length = hr.pipeToSocket(sock);
  if(length <= 0){
    fprintf(stderr, "\nSocket error while sending HEAD req\n");
    perror("write:");
    return -1;
  }
  HttpResponse hres(sock);
  length = hres.readHttpHeader();
  if(length != -1)
  	length = hres.getContentLength();
	else
		return -1;
  
  if(length > 0){
   length = hres.readHttpBody(buffer, length);
  }
  return length;
}
