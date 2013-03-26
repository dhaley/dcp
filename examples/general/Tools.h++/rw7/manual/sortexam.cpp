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
#define RW_STD_TYPEDEFS 1	// 1
#include <rw/bintree.h>
#include <rw/collstr.h>	// 2
#include <rw/rstream.h>

main(){
	// Construct an empty SortedCollection
	SortedCollection sc;	// 3

	// Insert some RWCollectableStrings:
	sc.insert(new RWCollectableString("George"));	// 4
	sc.insert(new RWCollectableString("Mary"));	// 5
	sc.insert(new RWCollectableString("Bill"));	// 6
	sc.insert(new RWCollectableString("Throkmorton"));	// 7

	// Now iterate through the collection,
	// printing all members:
	RWCollectableString* str;	//  8

	SortedCollectionIterator sci(sc);	//  9
	while( str = (RWCollectableString*)sci() )	// 10
		cout << *str << endl;	// 11

	sc.clearAndDestroy();
	return 0;
}
