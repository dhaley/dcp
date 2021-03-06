#pragma ident   "@(#)sports.cc	1.8    02/02/05 SMI"

// Copyright 1991, 1994, 2000, 2002 Sun Microsystems, Inc.  All Rights Reserved
 
//
// Implementation of sports_car class for "Freeway".
//
//

// Praveen 
// #include <stream.h>    // sports.h will include the correct header
#include <math.h>
#include "vehicle.h"
#include "sports.h"


const double DELTA_T    = 0.0000555; // 1/5 sec expressed in hours
const double OPT_DT     = 0.0003;    // optimal buffer (in hrs) in front
const double CAR_LEN    = 0.0025;    // car length (in miles) (roughly 16 ft)
const double BRAKE_DV   = 6.0;       // 30 mph / sec for 1/5 sec
const int    CAR_LENGTH = 5;	  
const int    CAR_WIDTH  = 3;	  


Sports_car::Sports_car (int i, int l, double p, double v)
{
  classID           = CLASS_SPORTS_CAR;
  name_int          = i;
  lane_num          = l;
  position          = p;
  velocity          = v;
  state             = VSTATE_MAINTAIN;
  max_speed         = 150;
  xlocation         = 0;
  ylocation         = 0;
  change_state      = 0;
  restrict_change   = 0;
  absent_mindedness = 0;
}


double
Sports_car::vehicle_length()
{
  return CAR_LEN;
}


void
Sports_car::draw (Display *display, Drawable pix, GC gc, int x, int y, 
	     int direction_right, int scale, int xorg, int yorg, int selected)
{
  this->xloc(x);
  this->yloc(y);

  // Because car is not as wide, draw 1 pixel lower than others.
  y++;

  //
  // If I am heading to the right, then I need to draw brick to the left of 
  // front of car.  If I am heading left, draw brick to the right.
  //
  if (direction_right) x -= (CAR_LENGTH - 1);

  int l = x * scale + xorg;
  int t = y * scale + yorg;
  int w = CAR_LENGTH * scale;
  int h = CAR_WIDTH  * scale;

  // Draw brick.
  XFillRectangle(display, pix, gc, l, t, w, h);

  // Put red box around "current vehicle"
  if (selected) draw_selection(display, pix, gc, l, t, w, h, scale);
}


double
Sports_car::optimal_dist (Vehicle *in_front)
{
  //
  // Calculate optimal following distance based on my velocity and the 
  // difference in velocity from the car in front.
  //
  double dv = in_front->vel() - velocity;
  
  return(OPT_DT * velocity + (0.5 * dv * dv * DELTA_T / BRAKE_DV));
}


void
Sports_car::recalc_velocity ()
{
  // 
  // Update velocity based on state
  //
  switch (state)
    {
      case VSTATE_COAST:      velocity *= 0.98;      break;
      case VSTATE_BRAKE:      velocity -= BRAKE_DV;  break;
      case VSTATE_ACCELERATE: velocity += 2.00;      break;
      case VSTATE_MAINTAIN:                          break;
      case VSTATE_CRASH:      velocity  = 0.00;      break;
      case VSTATE_MAX_SPEED:  velocity  = max_speed; break;
      case VSTATE_CHANGE_LANE:                       break;
      case VSTATE_CHANGE_LEFT:                       break;
      case VSTATE_CHANGE_RIGHT:                      break;
    }
  if (velocity < 0.0) velocity = 0.0;
}
