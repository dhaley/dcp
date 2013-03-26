#pragma ident   "@(#)vehicle.h	1.8    00/02/11 SMI"

// Copyright 1994, 2000, 2002 Sun Microsystems, Inc.  All Rights Reserved

#ifndef VEHICLE_H
#define VEHICLE_H

//
// Header file for vehicle class for "Freeway".
//

#include <iostream.h>
#include <fstream.h>

#include <X11/Xlib.h>

#define CLASS_VEHICLE 0

enum VState {
	VSTATE_MAINTAIN = 0,	// I'm maintaining speed.
	VSTATE_ACCELERATE,	// I'm accelerating.
	VSTATE_COAST,		// I'm coasting down to a lower speed.
	VSTATE_BRAKE,		// I'm braking.
	VSTATE_CRASH,		// I have crashed into the car in front of me.
	VSTATE_MAX_SPEED,	// I've topped out at maximum speed for this car.
	VSTATE_CHANGE_LANE,	// I'm switching lanes.
	VSTATE_CHANGE_LEFT,	// I'm switching lanes to the left.
	VSTATE_CHANGE_RIGHT	// I'm switching lanes to the right.
};


class Vehicle {
 protected:
  int     classID;
  int     name_int;
  double  position;
  double  velocity;
  int     max_speed;         // top speed of this vehicle
  VState  state;	     // one of the VSTATE_ values above
  int     xlocation;	     // location on screen relative to window (x)
  int     ylocation;	     // location on screen relative to window (y)
  int     lane_num;	     // number of the lane in which I'm driving
  int     change_state;	     // how far through a lane change I've progressed
  int     restrict_change;   // counter restricts making lane changes too often
  int     absent_mindedness; // how long it's been since I updated my state
  
 public:
  Vehicle (int = 0, int = 0, double = 0.0, double = 0.0);

  int     name()            { return name_int; }
  VState  vstate()          { return state; }
  VState  vstate(VState s)  { return state = s; }
  int     lane()            { return lane_num; }
  int     lane(int l)       { return lane_num = l; }
  double  pos()             { return position; }
  double  pos(double p)     { return position = p; }
  double  rear_pos()        { return position - vehicle_length(); }
  double  vel()             { return velocity; }
  double  vel(double v)     { return velocity = v; }
  int     xloc()            { return xlocation; }
  int     xloc(int x)       { return xlocation = x; }
  int     yloc()            { return ylocation; }
  int     yloc(int y)       { return ylocation = y; }
  int     top_speed()       { return max_speed; }
  int     top_speed(int s)  { return max_speed = s; }
  int     lane_change()     { return change_state; }
  int     lane_change(int s){ return change_state = s; }
  
//  virtual char         *classname()     { return "vehicle"; }
  virtual  char         *classname()      { return (char *)"vehicle"; }
  virtual int           classnum()        { return CLASS_VEHICLE; }
  virtual void          recalc (Vehicle *in_front, const int limit, 
				void *neighbors);
  virtual void          recalc_pos();
  virtual void          recalc_state (Vehicle *in_front, const int limit);
  virtual void          check_lane_change(Vehicle *in_front, void *neighbors);
  virtual void          recalc_velocity();
  virtual int           limit_speed(int limit);
  virtual double        vehicle_length();
  virtual double        optimal_dist(Vehicle *in_front);
  virtual void          draw (Display *display, Drawable pix, GC gc, 
			      int x, int y, int direction_right, int scale, 
			      int xorg, int yorg, int selected);
  friend  void          draw_selection(Display *dpy, Drawable pix, GC gc, 
				       int x, int y, int width, 
				       int height, int scale);
  friend  ostream&      operator<< (ostream&, const Vehicle&); 
  friend  istream&      operator>> (istream&,       Vehicle&); 
};

#endif
