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
 * Commercial Computer Software � Restricted Rights at 48 CFR 52.227-19,
 * as applicable.  Manufacturer is Rogue Wave Software, Inc., 5500
 * Flatiron Parkway, Boulder, Colorado 80301 USA.
 */
#include <rw/bstream.h>
#include <fstream.h>
#include <iomanip.h>

main(){
  ifstream fstr("data.dat");	// Open an input file
  RWbistream bstr(fstr);	// Construct RWbistream from it

  int i;
  float f;
  double d;

  // Restore an int that was stored in binary
  if(!((bstr >> i).good()))
     cout << "Run bostream.exe first!\n";
  else
  { 
    // Restore a float & double
    bstr >> f >> d;

    cout << "The integer: " << i << endl;
    cout << "The float: " << f << endl;
    cout << "The double: " << d << endl;
  }

  return 0;
}
