/* 
 * mmapptr.cpp: Example using pointer-based RWMultiMapPtr<K,T,C>
 *
 * $Id: mmapptr.cpp,v 7.7 1996/09/19 20:19:26 griswolf Exp $
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
 *
 ***************************************************************************
 */

#ifdef RW_NO_STL
#error Cannot compile this example if RW_NO_STL is defined.
#endif /* RW_NO_STL */

#include "rw/cstring.h"
#include "rw/rwdate.h"
#include "rw/tpmmap.h"
#include "rw/rstream.h"
#ifndef RW_NO_IOSTD
#  include <iomanip>
#else
#  include <iomanip.h>
#endif

#ifndef RW_HEADER_WITH_EXTENSION
#  include <functional>
#  include <utility>
#else
#  include <functional.hpp>
#  include <utility.hpp>
#endif /* RW_HEADER_WITH_EXTENSION */


int main()
{
  /*                                                                                
   * If we're using the Standard C++ Library and the iostream operators             
   * and/or comparison templates are in the std namespace, we need to                  
   * pull in namespace std, or scope the operator with std::.                                                 
   */                                                                               
#if !defined(RW_NO_STL) && !defined(RW_NO_STD_NAMESPACE)   
  using namespace std;                                                              
#endif
  /*
   *  borland 4 needs the std namespace
   */
#if defined(RW_BCB_NAMESPACE)  
  using namespace std;
#endif
  typedef RWTPtrMultiMap<RWCString, RWDate, less<RWCString> > RWMMap;

  RWMMap birthdays;

  birthdays.insertKeyAndValue(new RWCString("John"),
                              new RWDate(12, "April", 1975));

  birthdays.insertKeyAndValue(new RWCString("Paul"),
                              new RWDate(2, "Nov", 1980));

  birthdays.insertKeyAndValue(new RWCString("Mary"),
                              new RWDate(22, "Oct", 1987));

  birthdays.insertKeyAndValue(new RWCString("Paul"),
                              new RWDate(19, "June", 1971));

  birthdays.insertKeyAndValue(new RWCString("Sally"),
                              new RWDate(15, "March", 1976));

  birthdays.insertKeyAndValue(new RWCString("Paul"),
                              new RWDate(6, "July", 1950));

  // Display the data stored in the map
  cout << endl;
  cout << "Created a map storing the pairs:" << endl << endl;

  RWMMap::iterator iter = birthdays.begin();
  for(; !(iter == birthdays.end()); iter++)
          cout << setw(8) << *(*iter).first
               << "     " << *(*iter).second << endl;

  cout << endl;

  // How many "Paul"s?
  RWCString paulstr("Paul");

  RWMMap::size_type n = birthdays.occurrencesOf(&paulstr);
  RWMMap::size_type idx = 0;

  cout << "There are " << n << " Pauls.  "
       << "Their birthdays are:" << endl << endl;

  RWMMap::const_iterator iter2 = birthdays.std().lower_bound(&paulstr);

  while (++idx <= n) {
    cout << setw(7) << idx << ".     " << *(*iter2).second << endl;
    ++iter2;
  }

  cout << endl;  
  return 0;
}
