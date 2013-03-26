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
#include <assert.h>
#include <fstream.h>        
#include <rw/pstream.h>

main (){
  int j1 = 1;
  int k1 = 2;

  // Save integers to the file "int.dat"
    {
    // Open the stream to save to:
        ofstream          f("int.dat");
        RWpostream        po(f);

    // Use overloaded insertion operator to save integers:
        po << j1;
        po << k1;
    }

  // Restore integers from the file "int.dat"
    int j2 = 0;
    int k2 = 0;
    {
    // Open a separate stream to restore from:       
        ifstream          f("int.dat");
        RWpistream        pi(f);

    // Use overloaded extraction operator to restore integers:
        pi >> j2;         // j1 == j2
        pi >> k2;         // k1 == k2
    }

  assert(j1 == j2);
  assert(k1 == k2);
  return 0;
}
