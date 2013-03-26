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
#include <rw/rwdate.h>
#include <rw/rstream.h>
#include <rw/locale.h>
#include <rw/cstring.h>

main()
{
  RWLocaleSnapshot us("C");
  RWLocaleSnapshot french("fr");       // or vendor specific // 1

  RWCString americanDate("10 June 2025");
  RWCString frenchDate("10 Juin 2025");

  RWDate d(frenchDate, french);        // OK                 // 2

  cout << frenchDate << ((d.isValid()) ? " IS " : " IS NOT ")
       << "a valid date (french locale)." << endl << endl;
  
  RWDate bad = RWDate(frenchDate);                           // 3
  cout << frenchDate;
  cout << ((bad.isValid() && bad == d) ? " IS " : " IS NOT ")
       << "a valid date (default locale)." << endl << endl;

  bad = RWDate(americanDate, french);                        // 4
  cout << americanDate;
  cout << ((bad.isValid() && bad == d) ? " IS " : " IS NOT ")
       << "a valid date (french locale)." << endl << endl;

  cout << d << endl;                                         // 5
  cout << d.asString() << endl;                              // 6
  cout << d.asString('x', french) << endl;                   // 7

  return 0;
}
