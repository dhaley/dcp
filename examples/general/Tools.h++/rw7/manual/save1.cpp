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
//Instructions:  Pipe the output from this program into read1, as in ->
//               save1 | read1


#define RW_STD_TYPEDEFS 1
#include <rw/bintree.h>
#include <rw/collstr.h>
#include <rw/pstream.h>

main(){
   // Construct an empty collection:
   SortedCollection sc;

   // Insert, but to make things interesting,
   // add an object twice.

   RWCollectableString* george = new 	RWCollectableString("George");

   sc.insert(george);	// Insert once
   sc.insert(new RWCollectableString("Mary"));
   sc.insert(george);	// Insert twice
   sc.insert(new RWCollectableString("Bill"));
   sc.insert(new RWCollectableString("Throkmorton"));

   // Store in ascii to standard output:
   RWpostream ostr(cout);	// 1
   ostr << sc;	// 2

   sc.clearAndDestroy();	// 3

   return 0;
}
