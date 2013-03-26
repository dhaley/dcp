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
//Instructions:  Pipe the output from save1 into this program, as in ->
//               save1 | read1

#define RW_STD_TYPEDEFS
#include <rw/bintree.h>
#include <rw/collstr.h>
#include <rw/pstream.h>

main(){
   RWpistream istr(cin);
   SortedCollection sc2;

   // Read the collection back in:
   istr >> sc2;	// 4

   RWCollectableString temp("George");	// 5

   // Find a "George":
   RWCollectableString* g = (RWCollectableString*)(sc2.find(&temp));	// 6

   // "g" now points to a string with the value "George"
   // How many occurrences of g are there in the 	collection?

   unsigned count = 0;	// 7
   SortedCollectionIterator sci(sc2);	// 8
   RWCollectableString* item;
   cout << "Strings in the collection are: " << endl;

   while ( item = (RWCollectableString*)sci() )   // 9
   {
     if(item)
       cout << "\t" << *item << endl; 

     if ( item==g )	//10
       count++;
   }

   cout << endl << "There are " << count << "  " << temp << "'s" << endl;

   sc2.clearAndDestroy();	//11

   return 0;
}
