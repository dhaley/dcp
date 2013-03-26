#pragma ident   "@(#)sports.h	1.7    02/02/05 SMI"

// Copyright 1991, 1994, 2000, 2002 Sun Microsystems, Inc.  All Rights Reserved

#ifndef V_SPORTS_H
#define V_SPORTS_H

//
//
// Header file for sports_car class for "Freeway".
//
//

// #include <stream.h> - Not used.


#include "vehicle.h"

#define CLASS_SPORTS_CAR 2

class Sports_car : public Vehicle {
 protected:
  
 public:
  Sports_car (int = 0, int = 0, double = 0.0, double = 0.0);

//  virtual char         *classname()       { return "Sports car"; }
  virtual char         *classname()       { return (char *)"Sports car"; }
  virtual int           classnum()        { return CLASS_SPORTS_CAR; }
  virtual double        vehicle_length();
  virtual void          recalc_velocity();
  virtual double        optimal_dist(Vehicle *in_front);
  virtual void          draw (Display *display, Drawable pix, GC gc, 
			      int x, int y, int direction_right, int scale, 
			      int xorg, int yorg, int selected);
};

#endif
