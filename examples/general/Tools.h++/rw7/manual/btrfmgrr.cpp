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
#include <iostream.h>
#include <rw/collstr.h>
#include <rw/disktree.h>
#include <rw/filemgr.h>

main(){
   RWoffset rootArray[3];	        // Location of the tree roots
   RWBTreeOnDisk* treeArray[3]; 	// Pointers to the RWBTreeOnDisks

   RWCollectableString value;
   int i;

   RWFileManager fm("index.dat","rb");
   if((fm.isValid()) && (fm.Exists()))
   {
     fm.SeekTo(fm.start());    	        // Recover locations of root nodes
     fm.Read(rootArray, 3);
   
     for (int itree=0; itree<3; itree++)
     {
       // Initialize the three trees:
       treeArray[itree] =
          new RWBTreeOnDisk( fm,
                             10,                         // Max. nodes cached
                             RWBTreeOnDisk::autoCreate,  // Will read old tree
                             16,                         // Key length
                             FALSE,                      // Do not ignore nulls
                             rootArray[itree] );         // Location of root
     }
   
     RWoffset recordloc;

     cout << "Find data about Rogue Wave Software: " << endl << "   ";
     recordloc = treeArray[0] -> findValue("Rogue Wave Software"); 
     fm.SeekTo(recordloc);
     for(i=0; i<3; i++)
     {
        fm >> value;
        cout << value << "  ";
     }
     cout << endl << endl;
     
     cout << "Find the software company from Long Beach: " << endl << "   ";
     recordloc = treeArray[1] -> findValue("Long Beach"); 
     fm.SeekTo(recordloc);
     for(i=0; i<3; i++)
     {
        fm >> value;
        cout << value << "  ";
     }
     cout << endl << endl;
     
     cout << "Who's at (408) 431-1000 ?: " << endl << "   ";
     recordloc = treeArray[2] -> findValue("(408) 431-1000"); 
     fm.SeekTo(recordloc);
     for(i=0; i<3; i++)
     {
        fm >> value;
        cout << value << "  ";
     }
     cout << endl << endl;
     
     for (int i=0; i<3; i++)
       delete treeArray[i];
   }
   else
     cout << "Run btrfmgrw first!" << endl;

   return 0;
}
