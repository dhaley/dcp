/*
 * exregexp.cpp: Example using extended regular expressions
 *
 * $Id: exregexp.cpp,v 7.5 1996/09/19 20:19:40 griswolf Exp $
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

#include "rw/cstring.h"
#include "rw/rstream.h"
#include "rw/re.h"


/*
 * This example demonstrates how extended regular expressions can be
 * combined to perform complex global search and replace operations.
 *
 * Note:  Since the C++ preprocessor handles special characters with the
 *        "\" escape syntax, extended regular expressions require the  
 *        use of a double back slash whenever you wish to escape a 
 *        special character.
 */

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
  RWCRExpr rgxp(" [A-Za-z\\_]+((ton)|(burg)|([cC]ity))");
  RWCString a("There is no joy in Edmonton. \n");
  RWCString b(a);
  b.replace(rgxp," Healdsburg");
  RWCString c(a);
  c.replace(rgxp, " Sioux_City");
  RWCString result(a+b+c);

  cout << endl << result << endl;
 
  cout << "Replace all town names with 'Mudville'..." << endl << endl;

  result.replace(rgxp, " Mudville", RWCString::all);

  cout << result << endl << endl;
 
  //Here extended regular expressions are used to create a highly
  //simplified syntactic scanner.  
  RWCRExpr int_constant("[\\+\\-]?[0-9]+");
  RWCRExpr float_constant("[\\+\\-]?[0-9]+\\.[0-9]*");
  RWCRExpr identifier("[A-Za-z_][A-Za-z0-9_]*");

  //Create a string with two simple assignment statements in it
  RWCString exp1("var  =  4 + -2.5;");  
  RWCString exp2("var2 = +4 -  0.5;"); 
  RWCString stmts(exp1 + "\n\t" + exp2);

  //Display all identifiers in the program segment
  cout << "In the pair of C++ statements: " << endl
       << '\t' << stmts << endl << endl
       <<  "Identifiers:\t\t";

  size_t i = 0;
  size_t size = 0;

  while( i < stmts.length()  && i != RW_NPOS)
  { 
    i += size;
    i = stmts.index(identifier, &size, i);
    if (size && i != RW_NPOS)
      cout << stmts(i, size) << "  ";
  }
  
  //Typically a scanner will replace a recognized sequence with a token
  //identifying what type of sequence it is.  The focus of this example,
  //however, is to demonstrate how to iterate through all sequences which
  //match a given extended regular expression.  Therefore.....
  stmts.replace(identifier, "", RWCString::all);
  
  // Display all floating point constants in the program segment
  cout << endl << "Float constants:\t";
  i = size = 0; 
  while( i < stmts.length()  && i != RW_NPOS)
  { 
    i += size;
    i = stmts.index(float_constant, &size, i);
    if (size && i != RW_NPOS)
      cout << stmts(i, size) << "  ";
  }
  
  stmts.replace(float_constant, "", RWCString::all);
 
  // Display all integer constants in the program segment
  cout << endl <<  "Int constants:\t\t";
  i = size = 0; 
  while( i < stmts.length()  && i != RW_NPOS)
  { 
    i += size;
    i = stmts.index(int_constant, &size, i);
    if (size && i != RW_NPOS)
      cout << stmts(i, size) << "  ";
  }
  
  cout << endl;
  return 0;
}
