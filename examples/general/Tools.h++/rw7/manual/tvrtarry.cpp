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
#include <rw/tvrtarry.h>
#include <rw/rstream.h>
#include <rw/diskpage.h>

#include <stdlib.h>
#include <stdio.h>

struct ErsatzInt
{
  char  buf[8];
  ErsatzInt(int i) { sprintf(buf, "%d", i); }
  friend ostream& operator<<(ostream& str, ErsatzInt i)
    { str << atoi(i.buf); return str; }
};

main()
{
  RWDiskPageHeap heap;
  RWTValVirtualArray<ErsatzInt> vec1(10000L, &heap);

  for (long i=0; i<10000L; i++)
    vec1[i] = i;                     // Some compilers may need a cast here

  cout << vec1[100] << endl;         // Prints "100"
  cout << vec1[300] << endl;         // Prints "300"

  RWTValVirtualArray<ErsatzInt> vec2 = vec1.slice(5000L, 500L);
  cout << vec2.length() << endl;     // Prints "500"
  cout << vec2[0] << endl;           // Prints "5000";

  return 0;
}
