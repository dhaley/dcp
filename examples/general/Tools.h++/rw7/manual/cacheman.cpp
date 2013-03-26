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
#include <rw/cacheman.h>
#include <rw/rwfile.h>

#include <rw/bench.h>			/* Benchmark software */
#include <rw/cstring.h>	                /* Rogue Wave string class */
#include <iostream.h>
#include <ctype.h>


// The string to be used in cache benchmark:

const char* cs = "A quick brown fox jumped over the lazy brown dog.";
const char* cs2 = "  Rub a dub dub three men in a tub.";

class NoCache : public RWBench {
public:
NoCache() { }
  virtual void		doLoop(unsigned long n);
  virtual void		idleLoop(unsigned long n);
  virtual void		what(ostream& s) const
    { s << "File access not using RWCacheManager: \n"; }
};

class Cache : public RWBench {
public:
Cache() { }
  virtual void		doLoop(unsigned long n);
  virtual void		idleLoop(unsigned long n);
  virtual void		what(ostream& s) const
    { s << "File access using RWCacheManager: \n"; }
};


main(int argc, char* argv[])
{
  cout << "Testing string: \n\"" << cs << cs2 << "\"\n";
  cout.flush();

  // Test file access w/o cache manager:
  NoCache other;
  other.parse(argc, argv);
  other.go();
  other.report(cout);

  // Test RW cache manager:
  Cache rw;
  rw.parse(argc, argv);
  rw.go();
  rw.report(cout);

  return 0;
}


void NoCache::doLoop(unsigned long n)
{
   RWoffset loc[26];
   RWFile file("file.dat");		// Construct a file
   file.SeekToBegin();


   int index;
   size_t size;
   char letter;
   int value;

   RWCString letters(cs);
   letters += cs2;

   size = letters.length();

   for(int i = 0; i < 26; i++)
   {
      loc[i] = file.CurOffset();
      file.Write(i);
   }

   while(n--)
   {
      letter = letters[(size_t)(n%size)];
      if(toupper(letter) != tolower(letter))
      {
         index = toupper(letter) - 'A'; 
         file.SeekTo(loc[index]);
         file.Read(value);
      }
   }

}


void Cache::doLoop(unsigned long n)
{
   RWoffset loc[26];
   RWFile file("file.dat");		// Construct a file
   file.SeekToBegin();


   size_t index;
   size_t size;
   char letter;
   int value;

   RWCString letters(cs);
   letters += cs2;
   size = letters.length();

   for(int i = 0; i < 26; i++)
   {
      loc[i] = file.CurOffset();
      file.Write(i);
   }

   // Construct a cache, using 10 slots for ints:
   RWCacheManager cache(&file, sizeof(int), 10);

   while(n--)
   {
      letter = letters[(size_t)(n%size)];
      if(toupper(letter) != tolower(letter))
      {
         index = toupper(letter) - 'A'; 
         cache.read(loc[index], &value);
      }
   }


}


void NoCache::idleLoop(unsigned long n)
{
   RWoffset loc[26];
   RWFile file("file.dat");		// Construct a file
   file.SeekToBegin();


   int index;
   size_t size;
   char letter;
   int value;

   RWCString letters(cs);
   letters += cs2;
   size = letters.length();

   for(int i = 0; i < 26; i++)
   {
      loc[i] = file.CurOffset();
      file.Write(i);
   }

   while(n--)
   {
      letter = letters[(size_t)(n%size)];
      if(toupper(letter) != tolower(letter))
        index = toupper(letter) - 'A'; 
   }

}


void Cache::idleLoop(unsigned long n)
{
   RWoffset loc[26];
   RWFile file("file.dat");		// Construct a file
   file.SeekToBegin();


   int index;
   int size;
   char letter;
   int value;

   RWCString letters(cs);
   letters += cs2;
   size = letters.length();

   for(int i = 0; i < 26; i++)
   {
      loc[i] = file.CurOffset();
      file.Write(i);
   }

   // Construct a cache, using 10 slots for ints:
   RWCacheManager cache(&file, sizeof(int), 10);

   while(n--)
   {
      letter = letters[(size_t)(n%size)];
      if(toupper(letter) != tolower(letter))
         index = toupper(letter) - 'A'; 
   }


}
