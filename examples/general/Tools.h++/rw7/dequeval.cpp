/*
 * dequeval.cpp: Example using RWDequeVal<T>
 *
 * $Id: dequeval.cpp,v 7.8 1996/09/19 20:16:03 griswolf Exp $
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

/*
 * This program partitions integers into even and odd numbers.
 */
#include "rw/compiler.h"
#include "rw/tvdeque.h"
#include "rw/rstream.h"

#ifndef RW_HEADER_WITH_EXTENSION
#  include <algorithm>  //STL algorithms header
#  include <utility>    //STL utilities; for ptr_fun
#  if defined(__SUNPRO_CC) && (__SUNPRO_CC == 0x500)
#  	  include <functional> //STL utilities; for ptr_fun, sunpro50
#  endif
#else
#  include <algorithm.hpp>
#  include <utility.hpp>  
#endif /* RW_HEADER_WITH_EXTENSION */


// This is a function to test for oddness:
bool isodd(int x)
{
        return (x % 2 != 0);
}

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
  typedef RWTValDeque<int>::iterator iterator;

  RWTValDeque<int> numbers;

  iterator iter;
  int n;

  cout << "Input a random assortment of integers (EOF to end):" << endl;

  // Put even numbers in front and odd numbers in back of deque:
  while (cin >> n) {
    if (n % 2 == 0)
      numbers.pushFront(n);
    else
      numbers.pushBack(n);
  }

  cout << endl << "Partitioned odds and evens." << endl;

  // Use iterators to list deque contents:
  cout << endl << "The deque now contains: ";

  for(iter = numbers.begin(); iter != numbers.end(); ++iter)
    cout << *iter << "  ";

  // Use the standard library to swap the odds and evens:
  cout << endl << endl
       << "Lets swap the odds and evens..." << endl << endl;

  // copy evens to the back:
  iter = find_if( numbers.begin(),
                  numbers.end(),
                  ptr_fun(isodd));

  copy(numbers.begin(),                 // from start of the deque
       iter,                            // until first odd
       back_inserter(numbers.std())     // insert at end of deque
      );

  // now erase them from the front:
  numbers.std().erase(numbers.begin(), iter);

  // Display and empty the deque with RW interface:
  cout << "The deque now contains: ";
  while (numbers.entries()) {
         cout << numbers.popFront() << "  ";
  }

  cout << endl << endl;

  return 0;
}
