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
#include <rw/pstream.h>
#include <fstream.h>
#include <iostream.h>

class Simple
{
  inline friend RWvostream& 
  operator<< (RWvostream& stream, const Simple& object)
  { stream << object.data_; return stream; }

  inline friend RWvistream&
  operator>>(RWvistream& stream, Simple& object)
  { stream >> object.data_; return stream; }

  inline friend RWFile& 
  operator<< (RWFile& stream, const Simple& object)
  { stream << object.data_; return stream; }

  inline friend RWFile&
  operator>>(RWFile& stream, Simple& object)
  { stream >> object.data_; return stream; }

  char  data_;

public:

   friend ostream& operator<< (ostream &str, Simple& object);

   Simple(char data) : data_(data){}
   Simple() : data_('\0'){}

   bool  operator<(const Simple& other) const
   { return data_ < other.data_; }

   bool  operator==(const Simple& other) const
   { return data_ == other.data_; }

};

   ostream& operator<< (ostream &str, Simple& object)
   { str << object.data_; return str; } 


int main()
{
  RWTValDeque<Simple> deq;

  Simple  i('e');
  Simple  h('v');
  Simple  g('a');
  Simple  f('W');
  Simple  e('e');
  Simple  d('u');
  Simple  c('g');
  Simple  b('o');
  Simple  a('R');
  
  deq.pushFront(e);
  deq.pushFront(d);
  deq.pushFront(c);
  deq.pushFront(b);
  deq.pushFront(a);
  deq.pushBack(f);
  deq.pushBack(g);
  deq.pushBack(h);
  deq.pushBack(i);
  {
    ofstream          f("deque.dat");
    RWpostream        po(f);
    po << deq;
  }

  RWTValDeque<Simple> d2;
  {
    ifstream          f("deque.dat");
    RWpistream        pi(f);

    pi >> deq;
  }

  Simple rest;

  while(!d2.isEmpty())
  {
    rest = d2.popFront();
    cout << rest; 
  }
  
  cout << endl;

  return 0;
}
