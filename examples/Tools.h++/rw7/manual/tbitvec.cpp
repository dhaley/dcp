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
#include <rw/tbitvec.h>
#include <iostream.h>

const int VECSIZE = 8;

main()
{ 
  RWTBitVec<VECSIZE> a, b;           // Allocate two vectors.

  a(2) = TRUE;                  // Set bit 2 (the third bit) of a on.
  b(3) = TRUE;                  // Set bit 3 (the fourth bit) of b on.

  RWTBitVec<VECSIZE> c = a ^ b;      // Set c to the XOR of a and b.

  cout << "Vector 1" << "\t" << "Vector 2" << "\t" << "Vector 1 xor Vector 2"
       << endl;

  for(int i = 0; i < VECSIZE; i++)
    cout << a[i] << "\t\t" << b[i] << "\t\t" << c[i] << endl;

  return 0;
}
