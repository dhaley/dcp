#pragma ident   "@(#)police.cc	1.8    02/02/05 SMI"

// Copyright 1991, 1994, 2000, 2002 Sun Microsystems, Inc.  All Rights Reserved

//
// Implementation of police driver class for "Freeway".
//

// Praveen 
// #include <stream.h>    // police.h will include the correct header
#include <math.h>
#include "vehicle_list.h"
#include "police.h"


const double DELTA_T    = 0.0000555; // 1/5 sec expressed in hours
const double OPT_DT     = 0.0001;    // optimal buffer (in hrs) in front
const double CAR_LEN    = 0.004;     // car length (in miles) (roughly 16 ft)
const double BRAKE_DV   = 6.0;       // 30 mph / sec for 1/5 sec
const int    CAR_LENGTH = 8;	  
const int    CAR_WIDTH  = 4;	  

Police::Police (int i, int l, double p, double v) 
{
  classID           = CLASS_POLICE;
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
  flash_state       = 0;
}


double
Police::vehicle_length()
{
  return CAR_LEN;
}


void
Police::recalc_pos()
{
  //
  // Update position based on velocity.
  //
  position += velocity * DELTA_T;         

  //
  // Update state of flashing lights
  //
  flash_state = 1 - flash_state;
}


void
Police::draw (Display *display, Drawable pix, GC gc, int x, int y, 
	     int direction_right, int scale, int xorg, int yorg, int selected)
{
  extern unsigned long color_red, color_blue;

  this->xloc(x);
  this->yloc(y);

  //
  // If I am heading to the right, then I need to draw brick to the left of 
  // front of car.  If I am heading left, draw brick to the right.
  //
  if (direction_right) x -= (CAR_LENGTH - 1);

  int l = x * scale + xorg;
  int t = y * scale + yorg;
  int w = CAR_LENGTH * scale;
  int h = CAR_WIDTH  * scale;
  int w2 = w / 2;
  int h2 = h / 2;

  // Draw brick.
  if (flash_state) XSetForeground(display, gc, color_red);
  else             XSetForeground(display, gc, color_blue);
  XFillRectangle(display, pix, gc, l, t, w, h);

  // Draw flashing lights on top and bottom
  if (flash_state) XSetForeground(display, gc, color_blue);
  else             XSetForeground(display, gc, color_red);
  XFillRectangle(display, pix, gc, l, t, w2, h2);
  XFillRectangle(display, pix, gc, l + w2, t + h2, w2, h2);

  // Put red box around "current vehicle"
  if (selected) draw_selection(display, pix, gc, l, t, w, h, scale);
}


