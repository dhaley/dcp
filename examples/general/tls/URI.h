/* Copyright 2003 Sun Microsystems, Inc. All Rights Reserved
 */

#ifndef URI_H
#define URI_H

#include <string>
using namespace std;

class URI {
 public:
  URI(){}
  URI(string str) : mURI(str)
    {}
  void setURI(string uri);
  void setURI(const char* uri);
  string getFilename();
  string getHost();
  string getProtocol();
  string getCompletePath();
  string& asString();
  static void unit_test();
  string mURI;
 private:
  static string file_seperator;
  static string default_filename;
  string mHostname;
  string mProtocol;
  string mCompletePath;
};

#endif
