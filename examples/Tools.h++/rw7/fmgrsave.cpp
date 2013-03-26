/*
 * Example 7: FileManager.  Saves a linked list of ints.
 * This example appears in Section 11.2 of the manual.
 *
 * $Id: fmgrsave.cpp,v 7.5 1996/08/07 05:21:24 hart Exp $
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

#include "rw/filemgr.h"
#include "rw/rstream.h"


#ifdef applec                          
#  define RW_END_PROMPT   endl << flush
#else                                  
#  define RW_END_PROMPT   flush        
#endif                                 

struct DiskNode {
  int      data;
  RWoffset nextNode;
};

int main()
{
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
  cout << "Test of a linked-list on disk, using the RWFileManager.\n";

  RWFileManager fm("linklist.dat");
  
  // Allocate space for offset to start of the linked list:
  fm.allocate(sizeof(RWoffset));
  // Allocate space for the first link:
  RWoffset thisNode = fm.allocate(sizeof(DiskNode));
  
  fm.SeekTo(fm.start());
  fm.Write(thisNode);
  
  DiskNode n;
  int temp;
  RWoffset lastNode;
  cout << "Input a series of integers, then EOF to end:\n" << RW_END_PROMPT;

  /* Borland bug necessitates explicit test for good. */  
  while ( (cin >> temp).good() ){
    n.data = temp;
    n.nextNode = fm.allocate(sizeof(DiskNode));
    fm.SeekTo(thisNode);
    fm.Write(n.data);
    fm.Write(n.nextNode);
    lastNode = thisNode;
    thisNode = n.nextNode;
  }
  
  fm.deallocate(n.nextNode);
  n.nextNode = RWNIL;
  fm.SeekTo(lastNode);
  fm.Write(n.data);	
  fm.Write(n.nextNode);
  cout << "\nNow run fmgrrtrv to read them in.\n" << flush;
  /* an extra line is needed for Win95 to eat after pressing CTRL-Z(eof) */
  return 0;
}
