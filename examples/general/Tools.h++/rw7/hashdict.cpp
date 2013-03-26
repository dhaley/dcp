/* 
 * Example 5: Hashed dictionaries
 *
 * This program uses RWCollectableStrings as keys
 *   and RWCollectableInts as values.
 *
 * $Id: hashdict.cpp,v 7.7 1996/08/07 05:21:24 hart Exp $
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


/*
 * Declarations for class RWCollectableString:  
 * This class inherits class RWCString and class RWCollectable.  
 * Class RWCollectable has virtual functions hash() and matches() that are 
 * redefined by class RWCollectableString.  These functions are used to 
 * insert and retrieve RWCollectableStrings in the hash table.
 */
#include "rw/collstr.h"

// Declarations for class RWCollectableInt:
#include "rw/collint.h"

// Declarations for RWHashDictionary:
#include "rw/hashdict.h"
#include "rw/rstream.h"

STARTWRAP
#include <stdlib.h>
ENDWRAP


#ifdef applec                          
#  define RW_END_PROMPT   endl << flush
#else                                  
#  define RW_END_PROMPT   flush        
#endif                                 

// The following can easily be changed to store and retrieve 
// keys and values of other types:
typedef RWCollectableString KeyType;    
typedef RWCollectableInt    ValueType;

// The following can be changed to use a different container class; 
// for example, a B-Tree:
typedef RWHashDictionary        DictionaryType;

/* Global function to print keys and values.  This function is handed to  
 * RWHashDictionary::apply().
 */

void printKeyAndValue( RWCollectable* ky, RWCollectable* val, void*); // prototype

void
printKeyAndValue( RWCollectable* ky, RWCollectable* val, void*)
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
  /* Do the necessary typecast, then print 'em out: */
  cout << *(const KeyType*) ky << "\t" <<  *(const ValueType*)val << endl;
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
  cout << "***************Example of Hash Dictionary *****************\n\n";

  // Construct a dictionary with no entries:
  DictionaryType dictionary;

  // Loop to do various things to the Dictionary:
  // Since the Dictionary stores pointers to keys and values, storage will be 
  // provided from the heap for the actual keys and values.

  KeyType*        theKey;      // pointer to key.
  ValueType*      theValue;    // pointer to value.
  KeyType         aKey;        // Test key.
  char            option;      // Options for switch.
  RWCollectable*  retVal;      // used to hold return values

  RWCString     wasteBin;    // Receptacle for erroneous input.

  do {
    cout << dictionary.entries() << " entries in dictionary.\n";

    cout << "(i)nsert (f)ind (d)elete (l)ist (c)lear e(x)it:\t" << RW_END_PROMPT;

    // Borland bug necessitates explicit test for .good():

    if ( !(cin >> option).good() ) break; // Check for EOF
    
    switch ( option ) {
    case 'i':         // Insert a key-value pair.
    case 'I':
      cout << "Enter word to act as key:\t" << RW_END_PROMPT;
      theKey = new KeyType;   // Allocate from the heap.
      cin >> *theKey;

      cout << "Enter int to act as value:\t" << RW_END_PROMPT;
      theValue = new ValueType;  // Allocate from the heap.
      if(cin.good()) cin >> *theValue;

      if(cin.good())                     //Has all the input been good?
        retVal = dictionary.insertKeyAndValue(theKey, theValue);
      else
      {                                  //If bad input received.
        cin.clear(0);                    //Flag the stream as good.
        wasteBin.readLine(cin);          //Flush input buffer into wasteBin
        cout << "\n" << wasteBin
             << " is not a valid int value, please try again.\n\n";
        break;
      }

      cout << "\nKey " << *theKey;
      if (retVal)
        cout << " with value " << *theValue << " entered.\n\n";
      else
        cout << " already exists in dictionary.\n\n";
      
      break;
    case 'f':        // Find a value, given a test key.
    case 'F':
      cout << "Enter word to find:\t" << RW_END_PROMPT;
      cin >> aKey;
      theValue = (ValueType*)dictionary.findValue(&aKey);
      if ( theValue )
        cout << "\n" << aKey << " is a member of the collection with value "
             << *theValue << "\n\n";
      else
        cout << "\n" << aKey << " is not a member of the collection.\n\n";
      break;
    case 'd':       // Delete a key.
    case 'D':
      cout << "Enter word to be deleted:\t" << RW_END_PROMPT;
      cin >> aKey;
      RWCollectable* temp;      // Temporary necessary to calm cfront down
      theKey = (KeyType*)dictionary.removeKeyAndValue(&aKey, temp);
      if(theKey){
        theValue = (ValueType*)temp;
        cout << "\n" << "Key " << *theKey << " with value "
             << *theValue << " removed.\n\n";
        delete theKey;         
        delete theValue;
      }
      else
        cout << "\n" << "Key " << aKey << " not found.\n\n";
      break;
    case 'l':    // List contents of Dictionary.
    case 'L':
      // Uses global function defined above:
      dictionary.applyToKeyAndValue(printKeyAndValue, rwnil); 
      cout << "\n";
      break;
    case 'c':   // Clear the Dictionary
    case 'C':
      dictionary.clearAndDestroy();
      cout << "\n"; // Program will state "0 entries"
      break;
    case 'x':
    case 'X':
      break;
    default:
      cerr << "\nNot recognized.\n\n";
    }   // end switch
  } while (option != 'x' && option != 'X') ;

  return 0;
}

