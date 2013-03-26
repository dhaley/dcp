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
#include <rw/compiler.h>
#include <rw/cstring.h>
#include <rw/wstring.h>
#include <iostream.h>

#ifndef RW_NO_WSTR

main()
{
  RWCString Sun("\306\374\315\313\306\374");

  RWWString wSun(Sun, RWWString::multiByte);	// MBCS to wide string

  RWCString check = wSun.toMultiByte();

  cout << endl << "Original: " << Sun << endl << endl;
  cout << "Conversion to widechar using constructor: " << wSun << endl;
  cout << "Conversion to multibyte using member:      " << check
       << endl << endl;

  if(Sun == check)
     cout << "They are equal!" << endl << endl;
  else
     cout << "They are not equal!" << endl << endl;


  return 0;
}

#else
#error Your compiler does not support wide character strings
#endif
