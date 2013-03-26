/*
 * Example 9: RWDiskPageHeap. 
 *
 * $Id: pageheap.cpp,v 7.4 1996/08/07 05:21:24 hart Exp $
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
 *
 ***************************************************************************
 */

#include "rw/diskpage.h"
#include "rw/rstream.h"

struct Node {
  int   key;
  RWHandle      next;
};

RWHandle head = 0;

const int N = 100;      // Exercise 100 Nodes

int main() {
  /*                                                                                
   * If we're using the Standard C++ Library and the iostream operators             
   * are in the std namespace, we need to pull in namespace std, or                 
   * scope the operator with std::.                                                 
   */                                                                               
#if !defined(RW_NO_STL) && !defined(RW_NO_STD_NAMESPACE) && !defined(RW_NO_IOSTD)   
  using namespace std;                                                              
#endif
  /*
   *  borland 4 needs the std namespace
   */
#if defined(RW_BCB_NAMESPACE)
  using namespace std;
#endif
  // Construct a disk-based page heap with page size equal
  // to the size of Node and with 10 buffers:
  RWDiskPageHeap heap(0, 10, sizeof(Node));

  if (!heap.isValid())
  {
    cerr << "Unable to open temporary swap file.\n";
    cerr << "Do you have write privileges?\n" << flush;
    return 0;
  }

  // Build the linked list:
  for (int i=0; i<N; i++){
    RWHandle h = heap.allocate();
    Node* newNode = (Node*)heap.lock(h);
    newNode->key  = i;
    newNode->next = head;
    head = h;
    heap.dirty(h);
    heap.unlock(h);
  }

  // Now walk the list:
  unsigned count = 0;
  RWHandle nodeHandle = head;
  while(nodeHandle){
    Node* node = (Node*)heap.lock(nodeHandle);
    RWHandle nextHandle = node->next;
    heap.unlock(nodeHandle);
    heap.deallocate(nodeHandle);
    nodeHandle = nextHandle;
    count++;
  }

  cout << "List with " << count << " nodes walked.\n";

  // The following line should not be necessary, but a bug in Sun C++
  // requires it:
  cout.flush();

  return 0;
}

