/*
 * cstring.cpp: Example using the RWCString class
 *
 * $Id: cstring.cpp,v 7.9 1996/08/07 05:21:24 hart Exp $
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
 ***************************************************************************/

// Include the header file for the class RWCString:
#include "rw/cstring.h"
#include "rw/rstream.h"


void exerciseSubString();	// Defined below

#ifdef applec
#  define RW_END_PROMPT   endl << flush 
#else
#  define RW_END_PROMPT   flush
#endif

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

// Construct an empty string:
  RWCString  x;

  // Read a word from the terminal:
  cout << "Type a word: " << RW_END_PROMPT;
  cin >> x;
  cout << "You typed: " << x << endl;
  
  // Print the number of characters:
  cout << "The length of the word is:\t" << x.length() << endl;

  // Assignment to a char*: 
  RWCString a;
  a = "test string";
  cout << a << endl;

 
  // The use of a size_t type for RWCString subscripts is necessary to 
  // prevent the compiler from facing an ambiguous choice of automatic 
  // type conversions: (RWCString)->(char *) or (int)3->(size_t)3. 
  size_t fourth_letter = 3;
  cout << "a[3]: " << a[fourth_letter] << endl;

  // Construct two RWCStrings:
  RWCString one = "one";
  RWCString two = "two";

  // Concatenate them:
  cout << "one + two :\t" << one + two << endl;
  // Append a char* to one:
  one += "plus";
  cout << "one += plus :\t" << one << endl;

  // Convert a RWCString to upper case:;
  RWCString Case("Test Of toUpper() And toLower()");
  cout << "Original string:   " << Case << endl;
  cout << "toUpper() version: " << toUpper(Case) <<endl;
  cout << "toLower() version: " << toLower(Case) <<endl;

  // Illustration of pattern search:
  RWCString Pattern = "And";
  cout << "Search for pattern using an RWCString containing \"" << Pattern << "\"\n";
  cout << " Index of first match : " 
       << Case.index(Pattern) << "\n\n";

  // Find a char* pattern:
  const char* charPattern = "to";
  cout << "Search for pattern using a char* containing \"" << charPattern << "\"\n";
  int iMatch = Case.index(charPattern);
  cout << "Index of first match  : " << iMatch << endl;
  cout << "Index of second match : " 
       << Case.index(charPattern, iMatch+1) << endl;

  exerciseSubString();

  // The following line should not be necessary, but a bug in Sun C++
  // requires it:
  cout.flush();

  return 0;
}

/*
 * Exercise the RWSubString class.
 */

void
exerciseSubString()
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
  // Construct a RWCString and print it out:
  RWCString Y("History is bunk.");
  cout << "\nTest of Substrings.\nOriginal string \"Y\":\n" << Y << endl;

  // Now print out a substring of Y, using a conversion to a RWCString:
  cout << "Y(8,2): " << RWCString(Y(8,2)) << endl;

  // Here is an example of using a RWSubString as an lvalue:
  // This changes the RWCString Y.
  Y(8,2) = "was";
  cout << "Use a substring as an l-value:\n";
  cout << "Y(8,2) = \"was\":\n" << Y << endl;
}
