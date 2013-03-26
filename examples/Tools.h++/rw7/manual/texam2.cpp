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

#include <rw/tvhdict.h>
#include <rw/cstring.h>
#include <rw/rstream.h>
#include <iomanip.h>

class Count
{                                                               // 1
  int   N;

public:
  Count() :     N(0) { }                                        // 2
  int   operator++()  { return ++N; }                           // 3
  operator      int() { return N; }                             // 4
};

unsigned hashString ( const RWCString& str )                    // 5
  { return str.hash(); }

main() {
/*The "RWDefHArgs" macro insures correct template arguments with and 
		without the presence of the Standard C++ Library*/
/*Some compilers may require a '&' before the constructor argument, to 
indicate that the argument to the constructor is a function pointer.*/
  RWTValHashDictionary<RWCString,Count RWDefHArgs(RWCString)> map(hashString); // 6

  RWCString token;

  cout << "Type in a string, "
       << "Enter EOF, CTRL Z (PC's) or CTRL D (UNIX) to quit. "
       << endl << endl << endl;

  while ( cin >> token )                                        // 7
    ++map[token];                                               // 8

  RWTValHashDictionaryIterator<RWCString,Count RWDefHArgs(RWCString)> next(map);        // 9

  cout << endl << "Word frequencies of your string: " << endl;
  cout.setf(ios::left, ios::adjustfield);                       // 10
  while ( ++next )                                              // 11
    cout << setw(20) << next.key()
	 << " " << setw(10) << next.value() << endl;            // 12

  return 0;
}
