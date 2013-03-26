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
#define RW_STD_TYPEDEFS
#include <rw/ordcltn.h>
#include <rw/collstr.h>
#include <rw/collint.h>
#include <rw/colldate.h>
#include <rw/pstream.h>

main(){
   RWpistream istr(cin);
   RWOrdered collection2;

   // Even though this program does not need to have prior
   // knowledge of exactly what it is restoring, the linker
   // needs to know what the possibilities are so that the
   // necessary code is linked in for use by RWFactory.
   // RWFactory creates RWCollectable objects based on
   // class ID's.

       RWCollectableInt   exemplarInt;
       RWCollectableDate  exemplarDate;

   // Read the collection back in:
       istr >> collection2;

   // Note: The above statement is the code that restores
   // the collection.  The rest of this example shows us
   // what is in the collection.

   // Create a temporary string with value "George"
   // in order to search for a string with the same value:
       RWCollectableString temp("George");

   // Find a "George":
   //   collection2 is searched for an occurrence of a
   //   string with value "George".
   //   The pointer "g" will point to such a string:
         RWCollectableString* g;
         g = (RWCollectableString*)collection2.find(&temp);

   // "g" now points to a string with the value "George"
   // How many occurrences of g are there in the collection?

   size_t georgeCount   = 0;
   size_t stringCount   = 0;
   size_t integerCount  = 0;
   size_t dateCount     = 0;
   size_t unknownCount  = 0;

   // Create an iterator:
       RWOrderedIterator sci(collection2);
       RWCollectable* item;

   // Iterate through the collection, item by item,
   // returning a pointer for each item:

       while ( item = sci() ) {

         // Test whether this pointer equals g.
         // That is, test for identity, not just equality:
             if (item->isA() == __RWCOLLECTABLESTRING && item==g)
               georgeCount++;

         // Count the strings, dates and integers:
             switch (item->isA()) {
               case __RWCOLLECTABLESTRING: stringCount++; break;
               case __RWCOLLECTABLEINT:    integerCount++; break;
               case __RWCOLLECTABLEDATE:   dateCount++; break;
               default:                    unknownCount++; break;
             }
   }

   // Output results:
       cout << "There are:\n\t"
         << stringCount   << " RWCollectableString(s)\n\t"
         << integerCount  << " RWCollectableInt(s)\n\t"
         << dateCount     << " RWCollectableDate(s)\n\t"
         << unknownCount  << " other RWCollectable(s)\n\n"
         << "There are "
         << georgeCount
         << " pointers to the same object \"George\"" << endl;

   // Delete all objects created and return:
       collection2.clearAndDestroy();
       return 0;
}
