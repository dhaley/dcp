/*
 * Internationalization (I18N) example.
 *
 * $Id: i18n.cpp,v 7.8 1996/05/21 18:38:04 griswolf Exp $
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
#include "rw/rwtime.h"
#include "rw/rstream.h"
#include "rw/cstring.h"
#include "rw/locale.h"
#include "rw/rwdate.h"
STARTWRAP
#include <assert.h>
ENDWRAP


#ifdef RW_NO_LOCALE
#error Your compiler/environment does not support locales
#endif /* RW_NO_LOCALE */

#ifdef _MSC_VER  /* Microsoft */
  const char *const fr = "french";
  const char *const de = "german";
#else
#if defined(__DECCXX) && defined(__osf__)  /* DEC C++ under OSF */
  const char *const fr = "fr_FR.88591";
  const char *const de = "de_DE.88591";
#else
#if defined(_AIX)
  const char *const fr = "Fr_FR";
  const char *const de = "De_DE";
#else
  const char *const fr = "fr";
  const char *const de = "de";
#endif
#endif
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
  RWDate today = RWDate::now();
  cout << "Today's date in the default locale:            "
       << today << endl;

  RWLocale& here = *new RWLocaleSnapshot("");
  cout << "Today's date using your environment:           "
       << today.asString('x', here) << endl;

  RWLocale::global(&here);
  cout << "The same, but installed as the default locale: "
       << today << endl;

  // a borland 4.52 bug requires that the french locale be set
  // prior to setting german (which not all borland versions support).
  RWLocaleSnapshot french(fr);
  RWLocale& german = *new RWLocaleSnapshot(de); // or, "de_DE"

  cout << "In German (if available):                      "
       << today.asString('x', german) << endl;

  RWCString str;
  cout << "Now enter a date in German: " << flush;
  str.readLine(cin);
  today = RWDate(str, german);
  if (today.isValid())
    cout << "Printed using the default locale: " << today << endl;

#ifndef RW_IOS_XALLOC_BROKEN
  german.imbue(cin);
  cout << "Enter another date in German: " << flush;
  cin >> today;  // read a German date!
  if (today.isValid())
    cout << today << endl;
#endif

  RWZoneSimple newYorkZone(RWZone::USEastern, RWZone::NoAm);
  RWZoneSimple parisZone  (RWZone::Europe,    RWZone::WeEu);

  /* 
   * Build RWTimes relative to other time zones.  Note that
   * first setting the local time zone is a work-around to
   * guard against a rarely exercised bug in the library in
   * which an RWTime is created as "invalid".  The bug obtains
   * only for particular date/time boundary conditions when
   * the RWTime is built for a time zone with different DST rules
   * than those of the currently set local time zone.
   */
  const RWZone* saveLocal = RWZone::local(&newYorkZone);  
  RWTime leaveNewYork(RWDate(20, 12, 1993), 23,00,00, newYorkZone);

  RWZone::local(&parisZone);
  RWTime leaveParis  (RWDate(30,  3, 1994), 05,00,00, parisZone);

  RWZone::local(saveLocal);  // restore local time zone to original value

  RWTime arriveParis(leaveNewYork + long(7 * 3600));
  RWTime arriveNewYork(leaveParis + long(7 * 3600));

  cout << "Arrive' au Paris a` "
       << arriveParis.asString('c', parisZone, french)
       << ", heure local." << endl;

  cout << "Arrive in New York at "
       << arriveNewYork.asString('c', newYorkZone)
       << ", local time." << endl;

  static RWDaylightRule sudAmerica =
     { 0, 0, TRUE, {8, 4, 0, 120}, {2, 0, 0, 120}};

  RWZoneSimple  ciudadSud( RWZone::Atlantic, &sudAmerica );

  // RWZone::local(new RWZoneSimple(RWZone::Europe, RWZone::WeEu));

  {
  RWTime now = RWTime::now();
  cout << now.hour() << ":" << now.minute() << endl;
  }

  {
  RWTime now = RWTime::now();
  cout << now.asString('H') << ":" << now.asString('M') << endl;
  }

  {
  RWTime now = RWTime::now();
  #if !(defined(__SUNPRO_CC) && (__SUNPRO_CC == 0x0500))
  struct
  #endif
  tm tmbuf;
  now.extract(&tmbuf);
  const RWLocale& here = RWLocale::global();  // the default global locale
  cout << here.asString(&tmbuf, 'H') << ":"
       << here.asString(&tmbuf, 'M') << endl;
  }

  double f = 1234567.89;
  long i = 987654;
  RWCString fs = french.asString(f, 2);
  RWCString is = french.asString(i);
  if (french.stringToNum(fs, &f) &&
      french.stringToNum(is, &i))  // verify the conversion
    cout << f << "\t" << i << endl
         << fs << "\t" << is << endl;

  double sawbuck = 1000.;

  double price = 999.;  // $9.99
  double penny = 1.;    //  $.01
  assert(price + penny == sawbuck);

  {
  const RWLocale& here = RWLocale::global();
  double sawbuck = 1000.;
  RWCString tenNone  = here.moneyAsString(sawbuck, RWLocale::NONE);
  RWCString tenLocal = here.moneyAsString(sawbuck, RWLocale::LOCAL);
  RWCString tenIntl  = here.moneyAsString(sawbuck, RWLocale::INTL);
  if (here.stringToMoney(tenNone,  &sawbuck) &&
      here.stringToMoney(tenLocal, &sawbuck) &&
      here.stringToMoney(tenIntl,  &sawbuck))  // verify conversion
    cout << sawbuck << "  " << tenNone << "  "
         << tenLocal << "  " << tenIntl << "  " << endl;
  }

  return 0;
}
