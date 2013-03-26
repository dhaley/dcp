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
#include <rw/gsortvec.h>
#include <rw/rstream.h>
#include <iostream.h>

declare(RWGVector,int)
declare(RWGSortedVector,int)
implement(RWGVector,int)
implement(RWGSortedVector,int)

// Declare and define "comparison function" to partition even and odd numbers
int compFun(const int* a, const int* b)  {
      return (*a%2) - (*b%2);
}

main()  {
  // Declare and define an instance,
  // using the comparison function 'compFun':
  RWGSortedVector(int) avec(compFun);

  int someData[6] = {3, 17, 4, 5, 32, -1};

  cout << "When these numbers are inserted as follows:"
       << endl << "\t";


  // Do some insertions:
  int i = 0;
  while(someData[i] > 0)
  {
     avec.insert(someData[i]);
     cout << someData[i++] << "\t";
  }
 

  cout << endl << endl << "Now the RWGSortedVector is ordered as follows: "
       << endl << "\t";

  for(i = 0; i < avec.entries(); i++)
     cout << avec(i) << "\t";


  cout << endl << endl
       << "The second element is: " << avec(1);   

  cout << endl 
       << "The index of the first odd element is: " << avec.index(1)
       << endl; 

  return 0;
}
