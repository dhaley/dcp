/*
 * Example 1: classes RWTime and RWDate 
 *
 * $Id: timedate.cpp,v 7.6 1996/10/23 00:35:57 griswolf Exp $
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

// Include the header files for the classes RWDate and RWTime:
#include "rw/rwdate.h"
#include "rw/rwtime.h"
#include "rw/rstream.h"

STARTWRAP
#include <time.h>               /* looking for time() */
ENDWRAP

const int sleepTime = 5;

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
  /**************************************************************/
  /*                       RWDate                               */
  /**************************************************************/

  // Construct a RWDate with the current date.
  RWDate d1;

  cout << "Print the date.\n";
  cout << d1 << "\n\n\n";

  cout << "Now print some information about the date:\n";
  cout << "Day of the year:   " << d1.day()        << endl;
  cout << "Day of the month:  " << d1.dayOfMonth() << endl;
  cout << "Name of the month: " << d1.monthName()  << endl;
  cout << "The year:          " << d1.year()       << endl;

  cout << "Construct the date 12/31/1999...";
  RWDate d2(31, "December", 1999);
  cout << "done.  Print it out:\n";
  cout << d2 << endl;

  // Was this year a leap year?
  if ( d2.leap() )
        cout << "A leap year!\n";
  else
        cout << "Not a leap year.\n";

  // Add some days to a RWDate:
  cout << "Add 37 days to this date, then print again:\n";
  d2 += 37;
  cout << d2 << endl;

  RWDate inputDate;

  while(1) {
    cout << "Enter a date in one of the following formats:\n";
    cout << "  dd-mmm-yy    (e.g. 10-MAR-99);\n";
    cout << "  mm/dd/yy     (e.g. 3/10/99);\n";
    cout << "Invalid dates will be flagged.\nUse EOF to terminate "
          << "(^Z on the PC; usually ^D on Unix).\n" << flush;
  // NOTE that for MSVC V4.2 Standard Library, you must enter
  // ^Z<return>^Z<return>.  A known bug with streams from that library.

    cin.clear();                // Clear any corrupt dates
    cin >> inputDate;           // Get the date

    if( cin.eof() ) break;      // Check for EOF

    if( inputDate.isValid() )
      cout << "You entered:\t" << inputDate << endl;
    else {
      cout << "Not a valid date.\n";
    }
  }

  /**************************************************************/
  /*                       RWTime                               */
  /**************************************************************/

  cout << "\nWell, that was fun.  Now let's exercise RWTime.\n\n";
  cout << "Construct a RWTime with the current time...";
  RWTime t1;

  cout << "done.  Now print it out.\n";
  cout << t1 << endl;

  cout << "Convert to a date, then print it out:\n";
  cout << RWDate(t1) << endl;

  cout << "Return some information about the time:\n";
  cout << "The hour is       " << t1.hour()    << endl;
  cout << "The hour (GMT) is " << t1.hourGMT() << endl;
  cout << "The minute is:    " << t1.minute()  << endl;
  cout << "The second is:    " << t1.second()  << endl;

  cout << "Hang on while I go to sleep for a few seconds...";
  cout.flush();

  time_t start, end;
  time(&start);
  do {
    time(&end);
  } while ( end - start < (time_t)sleepTime ) ;

  cout << "back again.\n\nNow construct a new time.\n";

  // Construct new RWTime with current time:
  RWTime t2;

  // Print it out:
  cout << t2 << endl;

  // The following line should not be necessary, but a bug in Sun C++
  // requires it:
  cout.flush();
  return 0;
}
