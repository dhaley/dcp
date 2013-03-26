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

#include <rw/collect.h>
#include <rw/tpdeque.h>
#include <rw/pstream.h>
#include <rw/rwfile.h>

#include <iostream.h>
#include <fstream.h>

class Tangle : public RWCollectable
{
public:

  RWDECLARE_COLLECTABLE(Tangle)

  inline friend RWvostream& operator<<(RWvostream& vstream, Tangle* p)
  {
    if (p) 
      p->recursiveSaveOn(vstream);
    else {
      RWCollectable *dummy = new RWCollectable;
      dummy->recursiveSaveOn(vstream);
      delete dummy;
    }

    return vstream;
  }

  Tangle(Tangle* t = 0, int dat = 0) {next_=t; data_=dat;}
  virtual void saveGuts(RWvostream&) const;
  virtual void restoreGuts(RWvistream&);
  virtual void saveGuts(RWFile&) const;
  virtual void restoreGuts(RWFile&);

  RWBoolean operator<(const Tangle& other) const
    {  return data_ < other.data_;  }

  RWBoolean operator==(const Tangle& other) const
    {  return data_ == other.data_;  }

  Tangle* next_;
  int     data_;

};

void Tangle::saveGuts(RWvostream& stream) const
{
  RWCollectable::saveGuts(stream);      // Save the base class
  stream << data_;                      // Save internals
  stream << next_;                      // Save the next link

  cout << "Persist tangle #" << data_ 
       << " which points to ";

  if(next_)
    cout << "tangle #" << next_ -> data_ << endl;
  else
    cout << "NULL" << endl;
}

void Tangle::restoreGuts(RWvistream& stream)
{
  RWCollectable::restoreGuts(stream);   // Restore the base class
  stream >> data_;
  stream >> next_;                      // Restore the next link

  cout << "Restore tangle #" << data_ 
       << " which points to ";

  if(next_)
    cout << "tangle #" << next_ -> data_ << endl;
  else
    cout << "NULL" << endl;
}

void Tangle::saveGuts(RWFile& stream) const
{
  RWCollectable::saveGuts(stream);	// Save the base class
  stream << data_;                      // Save internals
  stream << next_;                      // Save the next link

  cout << "Persist tangle #" << data_ 
       << " which points to ";

  if(next_)
    cout << "tangle #" << next_ -> data_ << endl;
  else
    cout << "NULL" << endl;
}

void Tangle::restoreGuts(RWFile& stream)
{
  RWCollectable::restoreGuts(stream);   // Restore the base class
  stream >> data_;
  stream >> next_;                      // Restore the next link

  cout << "Restore tangle #" << data_ 
       << " which points to ";

  if(next_)
    cout << "tangle #" << next_ -> data_ << endl;
  else
    cout << "NULL" << endl;
}

RWDEFINE_COLLECTABLE(Tangle, 0x777);

int main()
{
  RWTPtrDeque<Tangle>  d;
  Tangle*             head = 0;

  for (int i = 4; i > 0; i--)
    head = new Tangle(head, i);

  // Circular reference.
  Tangle*  circleHead = NULL;
  circleHead          = new Tangle(circleHead, 20000);
  circleHead->next_   = circleHead;

  d.pushBack(head);
  d.pushBack(circleHead);
  d.pushBack(head);

  {
    ofstream          f("deque.dat");
    RWpostream        po(f);
    po << d;                       // Isomorphic persistence.

  } //Close the file, destroy the stream

  cout << endl << endl;

  RWTPtrDeque<Tangle> d2;

  {
    ifstream          f("deque.dat");
    RWpistream        pi(f);
    pi >> d2;

  } //Close the file, destroy the stream


  return 0;
}
