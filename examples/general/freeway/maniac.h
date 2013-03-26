#pragma ident   "@(#)maniac.h	1.8    02/02/05 SMI"

// Copyright 1991, 1994, 2000, 2002 Sun Microsystems, Inc.  All Rights Reserved

#ifndef V_MANIAC_H
#define V_MANIAC_H

//
//
// Header file for maniac class for "Freeway"
//

// #include <stream.h> - Not used.


#include "vehicle.h"
#include "sports.h"

#define CLASS_MANIAC 3

class Maniac : public Sports_car {
 protected:
  
 public:
  Maniac (int = 0, int = 0, double = 0.0, double = 0.0);

//  virtual char   *classname()       { return "Maniac"; }
  virtual char   *classname()       { return (char *)"Maniac"; }
  virtual int     classnum()        { return CLASS_MANIAC; }

  virtual void    check_lane_change(Vehicle *in_front, void *neighbors);
  virtual double  optimal_dist (Vehicle *in_front);
  virtual int     limit_speed (int limit);
};

#endif
