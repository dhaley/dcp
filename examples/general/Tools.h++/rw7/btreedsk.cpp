/*
 * Example 6: BTree-on-disk.  Retrieves birthdays, given a name
 *
 * $Id: btreedsk.cpp,v 7.6 1996/09/30 17:15:45 griswolf Exp $
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

#include "rw/disktree.h"
#include "rw/filemgr.h"
#include "rw/rwdate.h"
#include "rw/cstring.h"
#include "rw/rstream.h"



/* The following hack is made necessary by a bug in the DLL implementation
 * Microsoft's V4.2 Standard Library
 */
#ifdef RW_MSVC_DLL_LOCALE_FACET
#  define VC42_FORCE_CLOCALE(z) \
   locale *_temploc=(z.getloc()==locale("C"))?&(z.imbue(locale::classic())):0;
#  define VC42_REPLACE_LOCALE(z) \
     if ( _temploc ) z.imbue(*_temploc);
#else
#  define VC42_FORCE_CLOCALE(z)
#  define VC42_REPLACE_LOCALE(z)
#endif

#ifdef applec                          
#  define RW_END_PROMPT   endl << flush
#else                                  
#  define RW_END_PROMPT   flush        
#endif                                 

// example of using a struct for the void* in applyToKeyAndValue:
struct printStruct {
  RWFileManager*	filemgr;
  unsigned	 	keyLen;
};

// Function to print a key and value:
void printKey(const char* a, RWstoredValue sv, void* x); // prototype

void 
printKey(const char* a, RWstoredValue sv, void* x)
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
  printStruct *ps = (struct printStruct *)x;
  unsigned len = ps->keyLen;
  RWCString key(a,len);		// don\'t count on trailing \0 in key
  RWDate bday;
  RWFileManager* fm = ps->filemgr;
  fm->SeekTo(sv);
  bday.restoreFrom(*fm);
  cout << "Name: " << key << " birthday: " << bday << endl;
}

int main()
{
#if !defined(RW_NO_STL) && !defined(RW_NO_STD_NAMESPACE) && !defined(RW_NO_IOSTD)
  using namespace std;                                                           
#endif
  /*
   *  borland 4 needs the std namespace
   */
#if defined(RW_BCB_NAMESPACE) 
  using namespace std;
#endif
  RWCString	filename;
  RWDate	birthday;
  RWoffset	loc;

  cout << "       RWBTreeOnDisk sample program.\n";
  cout << "       Stores names and birthdays in a BTree.\n";

  cout << "Enter either the name of a new file or of a pre-existing file: " << RW_END_PROMPT;
  filename.readLine(cin);

  RWFileManager fmgr(filename.data());
  RWBTreeOnDisk bt(fmgr);	// Construct a B Tree with allocations managed by fmgr

  // display a list of this tree's parameters
  cout << "The RWBTreeOnDisk being managed in file " << filename;
  cout << ", has: " << endl;
  cout << "\tCache blocks:\t"     << bt.cacheCount() << endl;
  cout << "\tVersion:\t0x" << hex << bt.version() << dec << endl;
  cout << "\tKey Length:\t"       << bt.keyLength() << endl;
  cout << "\tOrder:\t\t"          << bt.order() << endl;
  cout << "\tMinimum Order:\t"    << bt.minOrder() << endl;
  cout << "\tHeight:\t\t"         << bt.height() << endl;
  cout << "\tEntries:\t"          << bt.entries() << endl;
  cout << endl;
  
  // Loop to do various things to the tree:

  char response;
  while (1) {
    cout << "(i)ns (n)umber of entries (f)ind (d)el (l)ist (c)lear e(x)it: " << RW_END_PROMPT;

    /*
     * Read the character; check for EOF.
     */

    VC42_FORCE_CLOCALE(cin);
    if ( !(cin >> response).good() || response=='x' || response=='X') break;
    VC42_REPLACE_LOCALE(cin);
    RWCString	name;
    RWCString	retKey;
    switch ( response ) {

    // Insert a key-value pair.
    case 'i':
    case 'I':

      cout << "Person's name: " << RW_END_PROMPT; // Prompt
      cin >> ws;			  // Skip any leading whitespace
      name.readLine(cin);		  // Get the person's name.
      name.resize(bt.keyLength());	  // Trim to the size of the B-Tree key.
      cout << "Birthday: " << RW_END_PROMPT;	  // Prompt for the person's birthday.
      cin >> birthday;			  // Read it in
      if( birthday.isValid() )		  // Check validity
      {
        loc = fmgr.allocate(birthday.binaryStoreSize());
        fmgr.SeekTo(loc);
        birthday.saveOn(fmgr);
        bt.insertKeyAndValue(name.data(), loc);	// Remember the location.
      }
      else
      {
        cin.clear();		// Clear state
        cout << "Bad date.\n";
      }
      break;

    // Find a person's birthday:
    case 'f':
    case 'F':

      cout << "Person's name: " << RW_END_PROMPT;   // Prompt
      cin >> ws;			  // Skip leading whitespace
      name.readLine(cin);	  // Get the person's name, to use as the key.
      name.resize(bt.keyLength());	  // Trim to the size of the B-Tree key.
      // Go find the birthday location.
      if(! bt.findKeyAndValue(name.data(), retKey, loc))
	cout << name << " not found.\n";
      else
      {
	fmgr.SeekTo(loc);
	birthday.restoreFrom(fmgr); // Retrieve the birthday.
	cout << "Birthday is " << birthday << endl;
      }
      break;

    // Delete a person:
    case 'd':
    case 'D':

      cout << "Name of person to delete: " << RW_END_PROMPT;
      cin >> ws;
      name.readLine(cin);
      name.resize(bt.keyLength());
      if(! bt.removeKeyAndValue(name.data(),loc))
	cout << "Can't find " << name << " to delete" << endl;
      else
	fmgr.deallocate(loc);
      
      break;

    // List the number of entries:
    case 'n':
    case 'N':

      cout << "Number of items in tree: " << bt.entries() << endl;
      break;

    // Clear the tree:
    case 'c':
    case 'C':
      cout << "Clearing..." << flush;
      bt.clear();		// Remove all keys.
      cout << "done.\n" << flush;
      break;

    // Print all entries:
    case 'l':

      struct printStruct ps;
      ps.filemgr = &fmgr;
      ps.keyLen = bt.keyLength();
      
      bt.applyToKeyAndValue(printKey, &ps);
      break;

    default:

      cerr << "Input not recognized...try again\n";

    }  // end switch
  }
  return 0;
}
