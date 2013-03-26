/* Copyright 2003 Sun Microsystems, Inc. All Rights Reserved
 */

#include "URI.h"
#include <iostream>
using namespace std;

string URI::file_seperator("/");
string URI::default_filename("index.html");

void URI::setURI(string uri)
{   mURI = uri;
}
void URI::setURI(const char* uri)
{   mURI = string(uri);
}
string URI::getProtocol()
{
  string tmp = mURI;
  if( mURI.length() == 0){
    fprintf(stderr, "URI is null\n");
    return "ERROR_URI_NOT_INIT";
  }
  string::size_type pos = mURI.find ("://",0); 
  if(pos != string::npos)
    mProtocol = mURI.substr(0, pos);
  else
    mProtocol = "http";
  return mProtocol;
}
string URI::getHost()
{
  string tmp = mURI;
  if( mURI.length() == 0){
    fprintf(stderr, "URI is null\n");
    return "ERROR_URI_NOT_INIT";
  }
  string::size_type pos = mURI.find ("://",0);
  if(pos != string::npos)
    tmp = mURI.substr(pos+3, mURI.length() - pos -3);
  int start = tmp.find(file_seperator);
  mHostname = tmp.substr(0, start);
  return mHostname;
}
string URI::getCompletePath()
{
  string tmp = mURI;
  if( mURI.length() == 0){
    fprintf(stderr, "URI is null\n");
    return "ERROR_URI_NOT_INIT";
  }
  string::size_type pos = mURI.find ("://",0);
  if(pos != string::npos)
    tmp = mURI.substr(pos+3, mURI.length() - pos -3);
  int start = tmp.find(file_seperator);
  if(start == string::npos){
    /* url's like http://a.com */
    tmp = string("/");
  }
  else {
    tmp = tmp.substr(start, tmp.size());
  }
  mCompletePath = tmp;
  return mCompletePath;

}
string URI::getFilename()
{
  string tmp = mURI;
  if( mURI.length() == 0){
    fprintf(stderr, "URI is null\n");
    return "ERROR_URI_NOT_INIT";
  }
  string::size_type pos = mURI.find ("://",0);
  if(pos != string::npos)
    tmp = mURI.substr(pos+3, mURI.length() - pos -3);

  int start = tmp.find_last_of(file_seperator);
  if (start == string::npos ){
    /* not found */
    return default_filename;
  }
  else if( start == tmp.length() - 1){
    //uri was of the form http://a.com/
    return default_filename;
  }
  //TODO: handle uri's of the form http://a.com
  return tmp.substr(start + 1, tmp.length() - start);
}
string& URI::asString()
{
  return mURI;
}

void URI::unit_test()
{
  URI u("http://pastwatch.eng/index.html");
	printf("%s:%s:%s:%s\n", u.asString().c_str(),
									u.getHost().c_str(), u.getFilename().c_str(),
									u.getCompletePath().c_str());
  u.setURI("http://pastwatch.eng/");
  u.setURI("http://pastwatch.eng");
  u.setURI("http://pastwatch.eng/a/b/c/d");
  u.setURI("http://pastwatch.eng///a/b/c/d");
  u.setURI("ftp://pastwatch.eng///a/b/c/d");
}
  

