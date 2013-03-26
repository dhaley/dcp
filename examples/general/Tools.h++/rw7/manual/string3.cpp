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
#include <rw/cstring.h>
#include <rw/rstream.h>

#include <iostream.h>

main()
{
  RWCString a("abc");                                           // 1
  RWCString b("abc\0def");                                      // 2
  RWCString c("abc\0def", 7);                                   // 3

  cout << "An RWCString with no embedded nulls: " << endl;
  cout << "RWCString::length() gives " << a.length() << endl;   // Prints "3"
  cout << "strlen gives " << strlen(a.data()) << endl << endl;  // Prints "3"

  cout << "An RWCString with embedded nulls, but with no length specified: "
       << endl;
  cout << "RWCString::length() gives " << b.length() << endl;   // Prints "3"
  cout << "strlen gives " << strlen(b.data()) << endl << endl;  // Prints "3" 

  cout << "An RWCString with embedded nulls, and constructed with a length: "
       << endl;
  cout << "RWCString::length() gives " << c.length() << endl;   // Prints "7"
  cout << "strlen gives " << strlen(c.data()) << endl;          // Prints "3"

  return 0;

}
