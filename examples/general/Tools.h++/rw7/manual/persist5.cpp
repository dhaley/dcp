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
#include <rw/ordcltn.h>
#include <rw/collstr.h>
#include <rw/collint.h>
#include <rw/colldate.h>
#include <rw/pstream.h>

int
main(){
   // Construct an empty collection 
   RWOrdered collection;

   // Insert objects into the collection.

   RWCollectableString* george;
   george = new RWCollectableString("George");

   collection.insert(george);     // Add a string once
   collection.insert(george);     // Add a string twice
   collection.insert(new RWCollectableInt(100));    
   collection.insert(new RWCollectableDate(3, "May", 1959));

   // "Store" to cout using portable stream.
   RWpostream ostr(cout);	
   ostr << collection;     
      // The above statement calls the insertion operator:
      //    Rwvistream&  
      //      operator<<(RWvistream&, const RWCollectable&);
	

   // Now delete all the members in collection.  
   // clearAndDestroy() has been written so that it deletes 
   // each object only once, so that you do not have to 
   // worry about deleting the same object too many times.

   collection.clearAndDestroy();	

   return 0;
}
