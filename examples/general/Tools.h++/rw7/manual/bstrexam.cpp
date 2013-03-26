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
#include <rw/bstream.h>
#include <rw/cstring.h>
#include <fstream.h>

#ifdef __BORLANDC__
# define MODE ios::binary       // 1
#else
# define MODE 0
#endif

void save(const RWCString& a, RWvostream& v)
{
  v << a;	                // Save to the virtual output stream
}

RWCString recover(RWvistream& v)
{
   RWCString dupe;
   v >> dupe;                   // Restore from the virtual input stream
   return dupe;
}

main()
{
   RWCString a("A string with\ttabs and a\nnewline.");

   {
     ofstream f("junk.dat", ios::out|MODE);	// 2
     RWbostream bostr(f);                       // 3
     save(a, bostr);
   }                                            // 4

   ifstream f("junk.dat", ios::in|MODE);        // 5
   RWbistream bistr(f);                         // 6
   RWCString b = recover(bistr);                // 7

   cout << "String sent to stream as: " << endl
        << "\t" << a << endl;                           // 8

   cout << "String read from stream as: " << endl
        << "\t" << b << endl;

   return 0;

}
