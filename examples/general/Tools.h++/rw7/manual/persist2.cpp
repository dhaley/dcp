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
#include <rw/tpdlist.h>  // RWTPtrDlist
#include <rw/collint.h>  // RWCollectableInt
#include <rw/rwfile.h>   // RWFile


int
main (){
  RWTPtrDlist<RWCollectableInt> dlist1;
  RWCollectableInt    *one  = new RWCollectableInt(1);
  dlist1.insert(one);
  dlist1.insert(one);
  {
    RWFile            f("dlist.dat");
    f << dlist1;  // Isomorphic persistence of dlist1.
  }

  assert(dlist1[0] == one && dlist1[0] == dlist1[1]);
    // dlist1[0], dlist[1] and "one" all point to the
    // same place.

  RWTPtrDlist<RWCollectableInt> dlist2;
  {
    RWFile            f("dlist.dat");

    f >> dlist2; 
      // dlist2 now contains 2 pointers
      // to the same RWCollectableInt of value 1.
      // However, this RWCollectableInt isn't at 
      // the same address as the value 
      // that "one" points to.
  }

  // See Figure 3 below to see what dlist1 and dlist2
  // now look like in memory.

  assert(dlist2[0] == dlist2[1] && (*dlist2[0]) == *one);
    // dlist2[0] and dlist2[1] point to the same place
    // and that place has the same value as "one".

  delete dlist2[0];
  delete one;
    // The developer must allocate and delete objects.
    // The templatized collection member function
    // clearAndDestroy() doesn't check that a given
    // pointer is deleted only once.
    // So in this case, delete the shared
    // pointer manually.
 
  return 0;   
}
