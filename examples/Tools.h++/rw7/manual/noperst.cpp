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
//Instructions:  This example requires C++ Standard Library support.
//               Compile with your include path set to the C++ Standard Library
//               header files and to the Tools.h++ root directory.

#include <rw/tvdeque.h>
#include <rw/edefs.h>
#include <iostream.h>

#ifdef RW_NO_STL
#error  This examples is only for users with the C++ Standard Library
#else

class VerySimple
{
     char  data_;
  
  public:

     VerySimple(char data) : data_(data){}
     VerySimple()          : data_('\0'){}

     bool  operator< (const VerySimple& other) const
     { return data_ <  other.data_; }

     bool  operator==(const VerySimple& other) const
     { return data_ == other.data_; }

};

//Overachieving compilers instantiate all template members whether used or not.
//RW_DONT_PERSIST provides dummy definitions of member functions used by our
//template collection class persistence mechanism.  To see if you have an
//overachieving compiler ...

//TRY COMMENTING OUT THE FOLLOWING LINE AND RECOMPILING

RW_DONT_PERSIST(VerySimple);


int main()
{
  RWTValDeque<VerySimple> d;

  cout << endl
       << "This example demonstrates the use of RW_DONT_PERSIST."
       << endl
       << "Please see the user's guide for more information."
       << endl;

  return 0;
}

#endif  //#ifdef RW_NO_STL
