/*
 * Example 3: class RWGDlist; generic doubly-linked lists, using ints
 *
 * $Id: gdlist.cpp,v 7.4 1996/08/07 05:21:24 hart Exp $
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


// Include the header file for the class RWGDlist:
#include "rw/gdlist.h"
#include "rw/rstream.h"


/* The class RWGDlist makes use of the macro declare defined in the header file
 * <generic.h> to implement the current C++ approximation to parameterized types.
 * The first argument is the class name (RWGDlist).
 * The second argument is the type of object being stored (int).
 */

declare(RWGDlist,int)

// Some data to be stored:
int idata[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };

int main()
{
  /*                                                                                   
   * If we're using the Standard C++ Library and the iostream operators             
   * are in the std namespace, we need to pull in namespace std, or                 
   * scope the operator with std::.                                                 
   */                                                                               
#if !defined(RW_NO_STL) && !defined(RW_NO_STD_NAMESPACE) && !defined(RW_NO_IOSTD)   
  using namespace std;                                                              
#endif
  /*
   *  borland 4 needs the std namespace
   */
#if defined(RW_BCB_NAMESPACE)  
  using namespace std;
#endif
  // Construct a linked-list of pointers to ints with no links:
  // The form: RWGDlist(int) is converted via a macro to intRWGDlist.
  RWGDlist(int) L;

  cout << "Prepend ints: 4 3 2 1 0\n";
  L.prepend(&idata[4]);
  L.prepend(&idata[3]);
  L.prepend(&idata[2]);
  L.prepend(&idata[1]);
  L.prepend(&idata[0]);

  cout << "Insert (append) ints: 5 6 7 8\n";
  L.insert(&idata[5]);
  L.insert(&idata[6]);
  L.insert(&idata[7]);
  L.insert(&idata[8]);

  cout << "Value at head is:   " << *L.first()   << endl;
  cout << "Value at tail is:   " << *L.last()    << endl;
  cout << "Number of links is: " <<  L.entries() << endl;

  cout << "Now remove and print each link from head:\n";
  while ( !L.isEmpty() )
    cout << *L.get() << endl;

  cout << "Remake list L, insert: 0 1 2 3 4 5\n\n";
  L.insert(&idata[0]);
  L.insert(&idata[1]);
  L.insert(&idata[2]);
  L.insert(&idata[3]);
  L.insert(&idata[4]);
  L.insert(&idata[5]);

  cout << "Construct an iterator for the linked-list.\n";
  RWGDlistIterator(int) c(L);

  // Exercise the iterator:

  cout << "Advance iterator 1 link.  Should point to: 0\n";
  ++c;
  cout << " *c.key() = " << *c.key() << endl;

  cout << "Advance iterator again.  Should point to: 1\n";
  ++c;
  cout << " *c.key() = " << *c.key() << endl;

  cout << "Move iterator to head of list.  Should point to: 0\n";
  c.toFirst();
  cout << " *c.key() = " << *c.key() << endl;

  cout << "Move iterator to find '4' and print it out:\n";
  c.findNextReference(&idata[4]);
  cout << " *c.key() = " << *c.key() << endl;

  cout << "Delete current item (which is 4).  Should point to 3.\n";
  c.remove();
  cout << " *c.key() = " << *c.key() << endl;

  // Use the operator () to move through the list:
  // first, reset the iterator:
  c.reset();

  cout << "Now reset the iterator and use operator() to move through the list.\n";
  cout << "Should read 0 1 2 3 5:\n";
  const int* v;
  while( (v = c()) != 0 )
    cout << *v << " ";

  cout << endl;

  return 0;
}
