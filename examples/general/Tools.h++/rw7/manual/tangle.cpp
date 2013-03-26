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
#include <rw/collect.h>
#include <rw/rwfile.h>
#include <iostream.h>

class Tangle : public RWCollectable
{

public:

  RWDECLARE_COLLECTABLE(Tangle)

  Tangle* nextTangle;
  int     someData;

  Tangle(Tangle* t = 0, int dat = 0)
  { nextTangle=t; someData=dat; }

  virtual void saveGuts(RWvostream&) const{;} 
  virtual void restoreGuts(RWvistream&){;}
  virtual void saveGuts(RWFile&) const;
  virtual void restoreGuts(RWFile&);

};

void Tangle::saveGuts(RWFile& file) const
{
   RWCollectable::saveGuts(file);       // Save the base class

   file.Write(someData);                // Save internals

   file << nextTangle;                  // Save the next link
}

void Tangle::restoreGuts(RWFile& file)
{
  RWCollectable::restoreGuts(file);     // Restore the base class

  file.Read(someData);                  // Restore internals

  file >> nextTangle;                   // Restore the next link
}


// Prints out data in list 

void checkList(Tangle* p, const char* msg)
{
   cout << msg << ": ";

   while (p)
   {
     cout << p -> someData << "  "; 

     p = p -> nextTangle;
   }

   cout << endl << endl;
}

void freeList(Tangle* p)
{
   if(p)
   {
     freeList(p -> nextTangle);
     delete p;
   }
}


RWDEFINE_COLLECTABLE(Tangle, 0x777)

main()
{
   Tangle *head = NULL, *head2;

   for (int i=9; i >= 0; i--)
     head = new Tangle(head,i);

   checkList(head, "List persisted");  // Check the original list

   {
     RWFile file("junk.dat");
     file << head;
   }

   RWFile file2("junk.dat");
   file2 >> head2;

   checkList(head2, "List restored"); // Check the restored list

   // Now two lists are on the heap, both need to be
   // deallocated.

   freeList(head);
   freeList(head2);

   return 0;
}
