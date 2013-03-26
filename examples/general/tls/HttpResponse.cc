/* Copyright 2003 Sun Microsystems, Inc. All Rights Reserved
 */

#include "HttpResponse.h"
#include <unistd.h>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

long HttpResponse::getContentLength()
{
  return clength;
}

int HttpResponse::getHttpStatus(const char *str)
{
  /* Status-Line = HTTP-Version SP Status-Code SP Reason-Phrase CRLF */
  char *tmp;
  char *str1 = strdup(str);
  while(*str== ' ')str++;
  tmp = strtok(str1, " ");
  tmp = strtok(NULL, " ");
  int status_code = atoi(tmp);
  free(str1);
  return status_code;
}

int HttpResponse::readHttpHeader()
{
  int status;
  string hdr;

  status = readLine(hdr);
  int code = getHttpStatus(hdr.c_str());

  if(code == 200 || code == 206)
    {/* valid response */}
  else
    {
      const char* str;
      fprintf(stderr, "Unable to complete Request. \
											Http Error code: %d\n", code); 
      switch(code/100){
      case 0: 
	str = "Unknown error";
	break;
      case 1: str = "Informational - Not used, but reserved for future use";
	break;
      case 2: str = "Good request, but you have found a bug in this program";
	break;
      case 3: str = "Redirection request. Redirection not implemented";
	break;
      case 4: str = "Client Error - The request contains bad syntax or cannot be fulfilled";
	break;
      case 5: str = "Server Error - The server failed to fulfill an apparently valid request";
	break;
      }
      fprintf(stderr, "%s\n", str);
      return -1;
    }
  
  do {
    hdr = "";
    status = readLine(hdr);
    if(status > 0){
      //printf("%s\n", hdr.c_str()); 
      if(hdr[0] == '\n')
	break;
      if(hdr[1] == '\n')
	break;
      if(hdr.find("Content-Length:") != string::npos)
	parseContentLength(hdr);
      else if(hdr.find("Content-length:") != string::npos)
	parseContentLength(hdr);
    }
  }while(status > 0);
  return 1;
}

long HttpResponse::parseContentLength(string str)
{
  string val;
  int pos;
  clength = -1;
  if(str.length() == 0) return -1;
  pos = str.find_first_of(":", 0);
  if(pos == string::npos){
    fprintf(stderr, "Couldnt parse content length\n");
    return -1;
  }
  val = str.substr(pos+1, str.size() - pos - 1);
  clength = atol(val.c_str());
  return clength;
}

int HttpResponse::readHttpBody(char *data, int length)
{
  int count = 0, res, pos;
  count = length;
  pos = 0;
  do {
    res = read(socket, &data[pos], count);
    count = count - res;
    pos += res;
  }while((res > 0) && (count >= 0));
  return length - count;
}

int HttpResponse::readLine(string& sink)
{
  int counter = 0;
  char c = '\0';
  int status = -1;
  do {
    status = read(socket, &c, 1);
    if(status < 0)
      break;
    sink += c;
    if(c == '\n') 
      break;
  }while(status > 0);
  return status;
}
