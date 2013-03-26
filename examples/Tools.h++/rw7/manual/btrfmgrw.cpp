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
#include <rw/collstr.h>

#include <rw/disktree.h>
#include <rw/filemgr.h>

main()
{
   RWBTreeOnDisk *btrees[3];

   RWoffset rootArray[3];         //Stores offsets to the RWBTreeOnDisks 
                                  //within the managed file "fm"
   RWoffset recordloc;

   const RWCollectableString crossreference[5][3] =
        {  "Rogue Wave Software", "Corvallis",     "(503) 754-3010",
           "Microsoft",           "Redmond",       "(206) 882-8080",
           "Borland",             "Scotts Valley", "(408) 431-1000",
           "Symantec",            "Long Beach",    "(310) 449-4140",
           "SGI",                 "San Ramon",     "(619) 371-7760"  };


   RWFileManager fm("index.dat");
   RWoffset rootArrayOffset = fm.allocate(sizeof(rootArray));

   for (int itree=0; itree<3; itree++)
   {
     btrees[itree] = new RWBTreeOnDisk(fm, 10, RWBTreeOnDisk::create);
     rootArray[itree] = btrees[itree] -> baseLocation();
   }

   fm.SeekTo(rootArrayOffset);

   fm.Write(rootArray, 3);

   for(int recnum=0; recnum < 5; recnum++)
   {
     recordloc = fm.allocate( crossreference[recnum][0].recursiveStoreSize() +
                              crossreference[recnum][1].recursiveStoreSize() +
                              crossreference[recnum][2].recursiveStoreSize() );
     fm.SeekTo(recordloc);
     fm << crossreference[recnum][0]; 
     fm << crossreference[recnum][1]; 
     fm << crossreference[recnum][2]; 

     btrees[0] -> insertKeyAndValue(crossreference[recnum][0],recordloc);
     btrees[1] -> insertKeyAndValue(crossreference[recnum][1],recordloc);
     btrees[2] -> insertKeyAndValue(crossreference[recnum][2],recordloc);
     
   }

   for (int i=0; i<3; i++)
      delete btrees[i];

   return 0;
}
