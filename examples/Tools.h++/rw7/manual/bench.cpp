/*
 * This example is from the Tools.h++ manual, version 7
 *
 * Copyright (c) 1989-1999 Rogue Wave Software, Inc.  All Rights Reserved.
 *
 * This computer software is owned by Rogue Wave Software, Inc. and is
 * protected by U.S. copyright laws and other laws and by international
 * treaties.  This computer software is furnished by Rogue Wave Software,
 * Inc. pursuant to a written license agreement and may be used, copied,
 * transmitted, and stored only in accordance with the terms of such
 * license and with the inclusion of the above copyright notice.  This
 * computer software or any other copies thereof may not be provided or
 * otherwise made available to any other person.
 *
 * U.S. Government Restricted Rights.  This computer software is provided
 * with Restricted Rights.  Use, duplication, or disclosure by the
 * Government is subject to restrictions as set forth in subparagraph (c)
 * (1) (ii) of The Rights in Technical Data and Computer Software clause
 * at DFARS 252.227-7013 or subparagraphs (c) (1) and (2) of the
 * Commercial Computer Software – Restricted Rights at 48 CFR 52.227-19,
 * as applicable.  Manufacturer is Rogue Wave Software, Inc., 5500
 * Flatiron Parkway, Boulder, Colorado 80301 USA.
 */
#include <rw/bench.h>			/* Benchmark software */
#include <rw/cstring.h>	                /* Rogue Wave string class */
#include <stdlib.h>
#include <iostream.h>
#include <rw/ctoken.h>
#include <rw/regexp.h>

// The string to be hashed:
const char* cs = "A multi-character string with lots of words in it to be parsed out and searched for.";

class TestBrute : public RWBench {
public:
TestBrute() { }
  virtual void		doLoop(unsigned long n);
  virtual void		idleLoop(unsigned long n);
  virtual void		what(ostream& s) const
    { s << "Brute force string search: \n"; }
};

class TestRW : public RWBench {
public:
TestRW() { }
  virtual void		doLoop(unsigned long n);
  virtual void		idleLoop(unsigned long n);
  virtual void		what(ostream& s) const
    { s << "Rogue Wave search: \n"; }
};


main(int argc, char* argv[]){
  cout << "Testing string \n\"" << cs << "\"\n";

  // Test brute force string search algorithm:
  TestBrute other;
  other.parse(argc, argv);
  other.go();
  other.report(cout);

  // Test RW searching w/regular expressions:
  TestRW rw;
  rw.parse(argc, argv);
  rw.go();
  rw.report(cout);

  return 0;
}


void TestBrute::doLoop(unsigned long n){
  RWCString string(cs);
  RWCTokenizer *tokener;
  RWCString token;

  tokener = new RWCTokenizer(string);

  while(n--){
  
    if((token = (*tokener)()).isNull())
    {
        delete tokener;
        tokener = new RWCTokenizer(string);
        token = (*tokener)();
    }

    size_t j = 0;

    for(size_t i = 0; i < string.length() && j != token.length(); i++)
    {
       j = 0;
       while((j < token.length()) && (string[i+j]==token[j]))
          j++;
    }

  }
 delete tokener;
}


void TestRW::doLoop(unsigned long n){
  RWCString string(cs);
  RWCTokenizer *tokener;
  RWCString token, result;
  RWCRegexp re("");

  tokener = new RWCTokenizer(string);
  
  while(n--){
 
   if((token = (*tokener)()).isNull())
    {
        delete tokener;
        tokener = new RWCTokenizer(string);
        token = (*tokener)();
    }  

  re = RWCRegexp(token); 
  result = string(re);       //Do the search! 

  }
 delete tokener;
}


void TestBrute::idleLoop(unsigned long n){
  RWCString string(cs);		// Subtract out the overhead
  RWCTokenizer *tokener;
  RWCString token;

  tokener = new RWCTokenizer(string);
  
  while(n--){
  
   if((token = (*tokener)()).isNull())
    {
        delete tokener;
        tokener = new RWCTokenizer(string);
        token = (*tokener)();
    }  

  }
 delete tokener;
}


void TestRW::idleLoop(unsigned long n){
  RWCString string(cs);                //Subtract out the overhead
  RWCTokenizer *tokener;
  RWCString token, result;
  RWCRegexp re("");

  tokener = new RWCTokenizer(string);
  
  while(n--){
  
   if((token = (*tokener)()).isNull())
    {
        delete tokener;
        tokener = new RWCTokenizer(string);
        token = (*tokener)();
    }  

  re = RWCRegexp(token); 

  }
 delete tokener;
}
