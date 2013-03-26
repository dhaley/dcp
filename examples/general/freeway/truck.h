#pragma ident   "@(#)truck.h	1.7    02/02/05 SMI"

// Copyright 1994, 2000, 2002 Sun Microsystems, Inc.  All Rights Reserved

#ifndef V_TRUCK_H
#define V_TRUCK_H

//
// Header file for truck class for "Freeway".
//
//

// #include <stream.h> - Not used.

#include "vehicle.h"

#define CLASS_TRUCK 1

class Truck : public Vehicle {
 protected:
  
 public:
  Truck (int = 0, int = 0, double = 0.0, double = 0.0);

//  virtual char         *classname()       { return "Truck"; }
  virtual char         *classname()       { return (char *) "Truck"; }
  virtual int           classnum()        { return CLASS_TRUCK; }
  virtual double        vehicle_length();
  virtual void          recalc_velocity();
  virtual double        optimal_dist(Vehicle *in_front);
  virtual void          draw (Display *display, Drawable pix, GC gc, 
			      int x, int y, int direction_right, int scale, 
			      int xorg, int yorg, int selected);
};

#endif
