/*
 * "Bus" example from the Tools.h++ manual.
 *
 * $Id: bus.cpp,v 7.6 1996/08/19 16:44:51 griswolf Exp $
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

#include "bus.h"
#include "rw/bstream.h"
#include "rw/pstream.h"
#include "rw/rwfile.h"



/*
 * The following complex conditional inclusion results from mixing
 * nww, old, and idiosyncratic header names. It _will_ get better...
 * ... someday.
 */
#ifdef __ZTC__
# include <fstream.hpp>
#else
# ifdef __GLOCK__
#   include <fstream.hxx>
# else
#   ifndef RW_NO_IOSTD
#     include <fstream>
#   else
#     include <fstream.h>
#   endif
# endif
#endif

RWDEFINE_COLLECTABLE(Bus, 200)

Bus::Bus() :
  busNumber_  (0),
  driver_     ("Unknown"),
  passengers_ (rwnil)
{
}

Bus::Bus(int busno, const RWCString& driver) :
  busNumber_  (busno),
  driver_     (driver),
  passengers_ (rwnil)
{
}

Bus::~Bus()
{
  customers_.clearAndDestroy();
  delete passengers_;
}

RWspace
Bus::binaryStoreSize() const
{
  RWspace count = customers_.recursiveStoreSize() +
    sizeof(busNumber_) +
    driver_.binaryStoreSize();

  if (passengers_)
    count += passengers_->recursiveStoreSize();
  else
    count += RWCollectable::nilStoreSize();

  return count;
}

int
Bus::compareTo(const RWCollectable* c) const
{
  const Bus* b = (const Bus*)c;
  if (busNumber_ == b->busNumber_) return 0;
  return busNumber_ > b->busNumber_ ? 1 : -1;
}

RWBoolean
Bus::isEqual(const RWCollectable* c) const
{
  const Bus* b = (const Bus*)c;
  return busNumber_ == b->busNumber_;
}

unsigned
Bus::hash() const
{
  return (unsigned)busNumber_;
}

size_t
Bus::customers() const
{
  return customers_.entries();
}

size_t
Bus::passengers() const
{
  return passengers_ ? passengers_->entries() : 0;
}

void
Bus::saveGuts(RWFile& f) const
{
  RWCollectable::saveGuts(f);
  f.Write(busNumber_);
  f << driver_ << customers_;

  f << passengers_; // nil pointer handled automatically
}

void
Bus::saveGuts(RWvostream& strm) const
{
  RWCollectable::saveGuts(strm);
  strm << busNumber_ << driver_ << customers_;

  strm << passengers_; // nil pointer handled automatically
}

void
Bus::restoreGuts(RWFile& f)
{
  RWCollectable::restoreGuts(f);
  f.Read(busNumber_);
  f >> driver_ >> customers_;

  delete passengers_;
  f >> passengers_; //  nil pointer handled automatically
}

void
Bus::restoreGuts(RWvistream& strm)
{
  RWCollectable::restoreGuts(strm);
  strm >> busNumber_ >> driver_ >> customers_;

  delete passengers_;
  strm >> passengers_; //  nil pointer handled automatically
}


void
Bus::addPassenger(const char* name)
{
  RWCollectableString* s = new RWCollectableString(name);
  customers_.insert( s );

  if (!passengers_)
    passengers_ = new RWSet;

  passengers_->insert(s);
}

void
Bus::addCustomer(const char* name)
{
  customers_.insert( new RWCollectableString(name) );
}

void restoreBus(RWvistream& stream); // prototype
void restoreBus(RWvistream& stream)
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
  Bus* newBus;
  stream >> newBus;		// Restore a bus

  cout << "Bus number " << newBus->number() 
    << " has been restored; its driver is " << newBus->driver() << ".\n";
  cout << "It has " << newBus->customers() << " customers and "
    << newBus->passengers() << " passengers.\n\n";

  delete newBus;
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
  Bus theBus(1, "Kesey");
  theBus.addPassenger("Frank");
  theBus.addPassenger("Paula");
  theBus.addCustomer("Dan");
  theBus.addCustomer("Chris");

  {
    ofstream f("bus.bin");
    RWbostream stream(f);
    stream << theBus;		// Persist theBus to a binary stream
  }

  {
    ofstream f("bus.str");
    RWpostream stream(f);
    stream << theBus;		// Persist theBus to an ASCII stream
  }


  {
    ifstream f("bus.bin");
    RWbistream stream(f);
    cout << "Restoring from a binary stream...\n";
    restoreBus(stream);		// Restore from a binary stream
  }

  {
    ifstream f("bus.str");
    RWpistream stream(f);
    cout << "Restoring from an ASCII stream...\n";
    restoreBus(stream);		// Restore from an ASCII stream
  }

  // The following line should not be necessary, but a bug in Sun C++
  // requires it:
  cout.flush();

  return 0;
}

