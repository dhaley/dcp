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
#pragma warning(disable:4786)
#include <rw/tvhset.h>
#include <rw/cstring.h>
#include <iostream.h>
#include <stdcomp.h>

#ifndef RWSTD_NO_NAMESPACE
   using namespace std;
#endif

struct silly_hash{
   unsigned long operator()(RWCString x) const
   { return x.length() * (long)x(0); }
};

main(){
RWTValHashSet<RWCString,silly_hash,equal_to<RWCString> > set1;
RWTValHashSet<RWCString,silly_hash,equal_to<RWCString> > set2;

  set1.insert("one");
  set1.insert("two");
  set1.insert("three");

//Rejected, no duplicates allowed
  set1.insert("one");

  cout << set1.entries() << endl;  // Prints "3"

  set2.insert("one");
  set2.insert("five");

//Rejected, no duplicates allowed
  set2.insert("one");

  cout << ((set1.isEquivalent(set2)) ? "TRUE" : "FALSE") << endl;
  // Prints "FALSE"

  set2.intersection(set1);

  set1.clear();
  cout << set1.entries() << endl;    // Prints "0"
  cout << set2.entries() << endl;    // Prints "1"

  return 0;
}
