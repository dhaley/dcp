#pragma ident   "@(#)vehicle_list.h	1.8    02/02/05 SMI"

// Copyright 1994, 2000, 2002 Sun Microsystems, Inc.  All Rights Reserved

#ifndef VEHICLE_LIST_H
#define VEHICLE_LIST_H

#include <string.h>

#include "vehicle.h"


class List {
 protected:
  List *n, *p;			// next and previous
  Vehicle *v;			// this vehicle

 public:
  List()              { n = p = this; v = 0; }
  Vehicle *value()    { return v; }
  int      hasValue() { return (this && v); }
  int      isEmpty()  { return (n == this); }
  List *   first()    { return n; }
  List *   last()     { return p; }
  List *   next()     { return n; }
  List *   prev()     { return p; }
  List *   next   (Vehicle*);
  List *   prev   (Vehicle*);
  List *   find   (Vehicle*);
  void     remove (Vehicle*);
  void     append (Vehicle*);
  void     prepend(Vehicle*);
  void     insert (Vehicle*);
};

#define insertAfter  prepend
#define insertBefore append

ostream & operator<< (ostream &, List &);

#endif
