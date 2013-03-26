/*
 * Example 4: class BinaryTree, storing and retrieving collectable strings
 *
 * $Id: binaryt.cpp,v 7.8 1996/09/20 15:05:54 griswolf Exp $
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


// Declarations for Binary Tree class:
#include "rw/bintree.h"

/*
 * Declarations for class RWCollectableString.  
 * This class inherits class RWCString and class RWCollectable.  
 * Class RWCollectable has a virtual function compareTo() that is redefined 
 * by class RWCollectableString.  This function is used to order the 
 * RWCollectableStrings in the binary tree.
 */
#include "rw/collstr.h"
#include "rw/rstream.h"

/*
 * "STARTWRAP" and "ENDWRAP" are macros that allow inclusion of ANSI-C header
 * files using standard "C" linkage.  They are necessary for C++ compilers that
 * do not supply their own special "C++" header files and, instead, rely on
 * standard C header files.
 */
STARTWRAP
#include <stdlib.h>
ENDWRAP

/*
 * The following complex conditional inclusion results from mixing
 * nww, old, and idiosyncratic header names. It _will_ get better...
 * ... someday.
 */

#ifdef __GLOCK__
#  include <fstream.hxx>
#else
#  ifndef RW_NO_IOSTD
#    include <fstream>
#  else
#    include <fstream.h>
#  endif
#endif


#ifdef applec                          
#  define RW_END_PROMPT   endl << flush
#else                                  
#  define RW_END_PROMPT   flush         
#endif                                 

/*
 * A pointer to this function will be handed to RWBinaryTree::apply() 
 * to enumerate the members of the collection.
 */
static void
printStrings(RWCollectable* c, void*)
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
  /*
   * Cast the RWCollectable pointer to a RWCollectableString pointer,
   * then dereference and print.  RWCollectableString inherits
   * its ability to be printed from its base class RWCString.
   */
  cout << * (RWCollectableString*) c << " ";
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
  RWBinaryTree		B;
  RWCollectableString	aWord;
  RWCollectableString*	pWord;
  int i = 0;

  cout << "***** Example using a Binary Tree (SortedCollection) ******\n";
  
  ifstream inputFile("textfile.in", ios::in);
  if(!inputFile){
    cerr << "Cannot open file textfile.in.\n";
    exit(1);
  }

  cout << "Reading from file \"textfile.in\"...\n";

  // Read until we hit an EOF:
  // Macintosh needs explicit check for eof 

#ifndef macintosh
  while ( inputFile >> aWord )
#else
  while ( !(inputFile >> aWord ).eof() )
#endif  
  { 

    // Transfer it to something off the heap and insert:
    pWord = new RWCollectableString(aWord);
    B.insert(pWord);

    cout << i++ << " " << *pWord << endl;
  }

  cout << "done.\n\nA total of " << i << " words were read.\n";
  cout << "Contents of the tree are:\n\n";
  B.apply(printStrings, 0);    // Uses global function defined above.
  cout << "\n\n";

  // Loop to do various things to the table:
  char option;
  
  while(1){

    cout << "(i)nsert (s)earch (d)elete (c)lear (l)ist e(x)it:\t" << RW_END_PROMPT;

    // Check for EOF or terminating character:
    if ( !(cin >> option).good() || option=='x' || option=='X' ) break;

    switch ( option ) {
    case 'i':		// Insert a word in tree.
    case 'I':
      cout << "Enter word:\t" << RW_END_PROMPT;
      pWord = new RWCollectableString;
      if(pWord){
        if( (cin >> *pWord).good() ) B.insert(pWord);	// Check for failed stream
        else delete pWord;
      }
      else cerr << "Out of memory.\n";
      break;
    case 's':		// Find the number of occurrences of a word.
    case 'S':
      cout << "Enter word:\t" << RW_END_PROMPT;
      cin >> aWord;
      cout << B.occurrencesOf(&aWord) << " occurrences of word in tree.\n";
      break;
    case 'd':   	// Remove a word.
    case 'D':
      cout << "Enter word:\t" << RW_END_PROMPT;
      cin >> aWord;
      B.removeAndDestroy(&aWord);
      break;
    case 'c':
    case 'C':		// Both clear AND destroy the contents
      B.clearAndDestroy();
      break;
    case 'l':
    case 'L':		// List the contents of the tree, in order.
      cout << B.entries() << " entries in tree:\n";
      B.apply(printStrings,0);
      cout << "\n\n";
      break;
    default:
      cerr << "Unrecognized.\n";
    } 	// End switch
  }	// End while

  cout << endl;		// To pretty things up.

  B.clearAndDestroy();	// Not really essential, but good style

  return 0;
}
