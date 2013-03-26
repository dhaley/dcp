#pragma ident   "@(#)traffic.cc	1.22    02/02/05 SMI"

// Copyright 1991, 1994, 2000, 2002 Sun Microsystems, Inc.  All Rights Reserved
 
//
// Most of the application logic for "Freeway"
//
//

#include <X11/Xos.h>
#include <X11/Xlib.h>



// Praveen
// #include <stream.h>   // io.h will include the correct header 



#include "vehicle.h"
#include "vehicle_list.h"
#include "truck.h"
#include "sports.h"
#include "maniac.h"
#include "police.h"


#include <stdio.h>
#include <math.h>
#include <sys/param.h>
#include <sys/types.h>

#include "window_ui.h"
#include "traffic.h"

static unsigned long state_to_color(int);
static void traffic_simulate(XtPointer, unsigned long*);

//
// Constants for drawing on window.
//
const int           N_LANES        = 4;
const int           LANES_EACH_DIR = 2;
const int           PIX_PER_MILE   = 2000;
const int           PIX_PER_SIGN   = 200;
const int           DRAWING_WIDTH  = 600;
const int           DRAWING_HEIGHT = 170;
const int           CYC_PER_STAT   = 5;
const int           LANE_WIDTH     = 12;
const int           DASH_PERIOD    = 20;  
const int           DASH_LENGTH    = 5;  
const int           CAR_LENGTH     = 7;		
const int           CAR_WIDTH      = 4;		
const int           TWENTIETH_SEC  = 50;   // milleseconds
const int           TENTH_SEC      = 100;  // milleseconds
const int           ONE_SEC        = 1000; // milleseconds


//
// Global variables.  If they are not static, chances are that they are
// employed outside this file.
//
static int name_counter = 0;  // Generate unique names for vehicles

static unsigned long	timerhandle;

int			pixel_depth = 8;
char			*traffic_current_file = NULL;
static GC		gc = NULL;
static XGCValues	xgcv;
static XID		xwin = NULL;
static Drawable         popup_xwin = NULL;
static Pixmap           pix_1 = NULL;
static Pixmap           pix_2 = NULL;
static Pixmap           pop_pix = NULL;
Vehicle			*popup_current = NULL;
static int		running = FALSE;
static int		was_running= FALSE;

int			randomize      = 0;

static List		*lanes[4];
static int		will_do_load;
static struct itimerval	timer;
static int		yloc[4];

int			width;
double			width_in_miles;

static int		height;
static int		popup_width, popup_height, popup_top;
static int		limits[3];
static double		generate_gap;
static unsigned int	update_time = TWENTIETH_SEC;
static int		lanes_top, lanes_height;
unsigned long	color_black, color_white, color_blue, color_violet,
		color_red,   color_green, color_orange, color_yellow,
		color_grey;

// static char *state_names[] = {
// 	"Maintain", "Accelerate", "Coast", "Brake", "Crash", "Top Speed", 
// 	"Lane Change" };
static const char *state_names[] = {
	"Maintain", "Accelerate", "Coast", "Brake", "Crash", "Top Speed", 
	"Lane Change" };

//
// Macros deal with lanes in their pre-configured arrangement:
// (Okay, so it's a silly arrangement; it has to do with history.)
//
//  -------------------------------
//  -  -  -  -  Lane 3  -  -  -  - 
//  -------------------------------  <== traffic going left  <==
//  -  -  -  -  Lane 1  -  -  -  - 
//  -------------------------------
//  -------------------------------
//  -  -  -  -  Lane 0  -  -  -  - 
//  -------------------------------  ==> traffic going right ==>
//  -  -  -  -  Lane 2  -  -  -  - 
//  -------------------------------
//
#define IsUpperLane(n)		((n) & 1)
#define IsLowerLane(n)		(!IsUpperLane(n))
#define IsInsideLane(n)		((n) < 2)
#define LowerToUpperLane(n)	((n)+1)
#define UpperToLowerLane(n)	((n)-1)
#define GetNeighborLane(n)	( (IsLowerLane(n)) ? 2 - (n) : 4 - (n) )

#define ChangingLanes(s)	( (s) == VSTATE_CHANGE_LANE  || \
					(s) == VSTATE_CHANGE_LEFT  || \
					(s) == VSTATE_CHANGE_RIGHT )

//
// Used to decice whether mouse click is on particular car
//
int
is_between(int n, int lo, int hi)
{
	return (n >= (lo) && n <= (hi));
}

//
// Given a vehicle, this function finds out which speed zone (segment) it's in.
//
int
get_segment(Vehicle *v)
{
	int seg = (int) (v->xloc() / PIX_PER_SIGN);
	if (seg > 2) {
		seg = 2;
	} else if (seg < 0) {
		seg = 0;
	}
	return seg;
}

//
// Given a segment (speed zone) and a lane number, this function returns
// the message item which displays average velocity there.
//
Widget
seg_to_message(int seg, int lane)
{
	switch(lane) {
	case 0:
	case 2:
		return window.control_objects->zone_objects->z[seg].spzonel;
		break;
	case 1:
	case 3:
		return window.control_objects->zone_objects->z[seg].spzoneu;
		break;
	}
	return NULL; // should never happen
}


//
// Show the current filename and status in the application frame.
//
void
traffic_frame()
{
	char msg[100];
	//	char *status = running  ? "Running" : "Stopped";
	char *status = (char *) (running  ? "Running" : "Stopped");
	if (popup_current && was_running) {
	  //	status =  "Suspended";
		status = (char *) "Suspended";
	}
	if (traffic_current_file) {
		int i = strlen(traffic_current_file) - 1;
		while (i>0 && traffic_current_file[i-1] != '/') {
			i--;
		}
		sprintf(msg, "%s: %s", traffic_current_file + i, status);
	} else {
		sprintf(msg, "%s", status);
	}
	XmString str = XmStringCreateSimple(msg);
	XtVaSetValues( window.statuslab, XmNlabelString, str, NULL);
	XmStringFree(str);
}

//
// Do statistics for average velocities.  Most times, don't display anything
// for performance reasons.  Only do it every CYC_PER_STAT times.  If the
// boolean argument delay is FALSE, display it now regardless.
//
void
traffic_stats(int delay)
{
	static int	stats_counter = 0;
	static int	segment_cnt[2][3];
	static double	segment_vel[2][3];
	static char	buff[10];
	int j ;

	// 
	// Most times, do nothing.
	//
	if (delay && ((stats_counter++ % CYC_PER_STAT) != 0)) {
		return;
	}
	//
	// Initialize counters
	//
	for (j = 0; j < 2; j++) {
		for (int i = 0; i < 3; i++) {
			segment_vel[j][i] = 0.0;
			segment_cnt[j][i] = 0;
		}
	}
	//
	// Find average velocity in each segment
	//
	for (j = 0; j < N_LANES; j++) {
		for(List *l = lanes[j]->first(); l->hasValue(); l = l->next())
		{ 
			Vehicle *v = l->value(); 
			int    seg = get_segment(v);
			int    top = (j == 1 || j == 3) ? 1 : 0;
			
			segment_cnt[top][seg]++;
			segment_vel[top][seg] += v->vel();
		}
	}
	// 
	// Display average velocities
	//
	for (j = 0; j < 2; j++) {
		for (int i = 0; i < 3; i++) {
			double count = (double) segment_cnt[j][i];
			
			if (count == 0) {
				sprintf(buff, " ");
			} else {
				sprintf(buff, "%2d", 
					(int) (segment_vel[j][i] / count));
			}
			Widget message = seg_to_message(i, j);
			XmString str = XmStringCreateSimple(buff);
			XtVaSetValues( message, XmNlabelString, str, NULL);
			XmStringFree(str);
		}
	}
}

//
// Deal with the clock.  Argument says whether to advance or reset time.
///
void
clock_advance(int advance)
{
	static char	buffer[30];
	static int	hours;
	static int	mins;
	static int	secs;
	static int	tenths;
	
	if (advance) {
		tenths += 2;		      // advance 1/5 second
	} else {
		hours = mins = secs = tenths = 0; // zero the clock
	}
	if (tenths >= 10) {
		tenths = 0;
		secs += 1;
		if (secs >= 60) {
			secs = 0;
			mins += 1;
			if (mins >= 60) {
		    		mins = 0;
		    		hours += 1;
			}
		}
	}
	sprintf(buffer, "%d:%02d:%02d.%d", hours, mins, secs, tenths);

	// Set clock message to show simulation clock.
	XmString str = XmStringCreateSimple(buffer);
	XtVaSetValues(window.control_objects->time_val, XmNlabelString, str, NULL);
	XmStringFree(str);
}


//
// Advance all of the vehicles in their lanes.  Basically, this loops over
// all the vehicles in all the lanes and tells them to recalculate.
//
void
traffic_advance()
{
	// for (int j = 0; j <= N_LANES; j++)  // buggy version
	for (int j = 0; j < N_LANES; j++) {
		List *next = NULL;

		for (List *i = lanes[j]->first(); i->hasValue(); i = next) { 
			Vehicle *current, *in_front;
			int      index, limit;

			current = i->value();
			next = i->next(); 
			index = get_segment(current);
			limit = limits[index];

			//
			// Vehicles in the inside lane get to go
			// 5 mph over limit.
			//
			if (IsInsideLane(j)) {
				limit += 5;
			}
			//
			// Tell vehicle to recalculate 
			//
			List *neighbors = lanes[GetNeighborLane(j)];
			List *upperlane = IsLowerLane(j) ?
						lanes[LowerToUpperLane(j)]
						: NULL;
			if (next->hasValue()) {
				in_front = next->value();
			} else if (upperlane && !upperlane->isEmpty()) {
				in_front = upperlane->first()->value();
			} else {
				in_front = NULL;
			}
			current->recalc(in_front, limit, (void *) neighbors);

			//
			// See if it has gone off the edge
			//
			if (IsLowerLane(j) && current->xloc() > width) {
				//
				// Gone off the right side of bottom lane;
				// turn it around.
			    	//
				double p  = current->pos() - width_in_miles;
				int    up = LowerToUpperLane(j);
				  current->lane(up);
				  current->pos(p);
				  lanes[j] ->remove (current);
				  lanes[up]->prepend(current);
				  break;
				}
			else if (IsUpperLane(j) && current->xloc() < -10) {
				//
				// Gone off the left side of upper lane;
				// remove it.
				//
				if (current == popup_current) {
					traffic_force_popup_done();
				}
				lanes[j]->remove(current);
				delete current;
			}
			//
			// Deal with lane changes
			//
			else if (ChangingLanes(current->vstate())) {
				int delta = current->lane_change();
				if (delta >= CAR_WIDTH) {
					int n = GetNeighborLane(j);
					lanes[j]->remove(current);
					lanes[n]->insert(current);
					current->lane  (n);
					current->vstate(VSTATE_MAINTAIN);
					current->lane_change(
						LANE_WIDTH - delta - 2);
				} else {
					current->lane_change(delta + 1);
				}
			} else if (current->lane_change()) {
				current->lane_change(
					current->lane_change() - 1);
			}
		}
	}
}

//
// Advances simulation.  Internal function called every so often by a timer.
//
void
traffic_simulate(XtPointer, unsigned long*)
{
	clock_advance(TRUE);		// advance simulation clock
	traffic_advance();		// advance time for all vehicles
	traffic_generate();		// potentially generate new vehicles
	traffic_stats(TRUE);		// do statistics on vehicles in lanes
	traffic_display();		// display the vehicles in new states
	// Set timer
	timerhandle = XtAppAddTimeOut(
			app_context,
			(unsigned long)update_time,
			traffic_simulate,
			NULL);
}

//
// Give me a new vehicle of the given class (passed by number).
//
Vehicle *
new_vehicle(int classnum, int name, int lane, double pos, double vel)
{
	Vehicle *v;

	switch (classnum) {
	case CLASS_TRUCK: 
		v = (Vehicle *) new Truck(name, lane, pos, vel);
		break; 
	case CLASS_SPORTS_CAR: 
		v = (Vehicle *) new Sports_car(name, lane, pos, vel);
		break;
	case CLASS_MANIAC:
		v = (Vehicle *) new Maniac(name, lane, pos, vel);
		break;
	case CLASS_POLICE: 
		v = (Vehicle *) new Police(name, lane, pos, vel);
		break;
	case CLASS_VEHICLE:
	default:
		v = new Vehicle(name, lane, pos, vel);
		break;
	}
	return v;
}

//
// Called for every simulation update.  May generate new cars if there is room.
//
void
traffic_generate()
{
	//
	// If the lane is empty or if the last car in lane is
	// beyond "generate_gap" // then generate a new car in that lane.
	// "generate_gap" is set by slider.
	// The new vehicle takes a position of 0 and velocity of car in front.
	//
	for (int i = 0; i < N_LANES; i += 2) {
		Vehicle *last = (lanes[i]->isEmpty()) ?
					NULL
					:lanes[i]->first()->value();
		if ((!last || last->rear_pos() > generate_gap) &&
			(!randomize || !name_counter || (rand() % 4 == 0))) 
		{
			Vehicle *v;
			int classnum;
			int limit = IsInsideLane(i) ?
					limits[0] 
					: limits[0] + 5;
			double vel = (last) ?
					last->vel() 
					: (double) limit;
			if (rand() % 10 == 0) {
				classnum = CLASS_SPORTS_CAR;
			} else if (rand() % 15 == 0) {
				classnum = CLASS_TRUCK;
			} else {
				classnum = CLASS_VEHICLE;
			}

			v = new_vehicle(classnum, name_counter++, i, 0.0, vel);
			lanes[i]->prepend(v);
		}
	}
}


//
// Draw box outline in given gc
//
void
draw_box(Drawable win, GC gc, int l, int t, int r, int b)
{
#define DrawThickLine(dy, de, gc, x1, y1, x2, y2)     \
	XFillRectangle(dy, de, gc, x1, y1, (x2 - x1 + 2), (y2 - y1 + 2));

	DrawThickLine(display, win, gc, l, t, r, t);
	DrawThickLine(display, win, gc, r, t, r, b);
	DrawThickLine(display, win, gc, l, b, r, b);
	DrawThickLine(display, win, gc, l, t, l, b);
}


static int box_l, box_r, box_t, box_b;
//
// Draw box around selected area
//
void
BoxPopupArea()
{
	int x = popup_current->xloc();

	box_l = x - popup_width  / 6;	// left
	box_r = x + popup_width  / 6;	// right
	// box_t and box_b are set in traffic_repaint rather than here

	XSetForeground(display, gc, (pixel_depth > 1)?color_red:color_white);
	draw_box(xwin, gc, box_l, box_t, box_r, box_b);
}

//
// Tell all the vehicles to redraw themselves
//
static void
draw_vehicles(Drawable pix, int scale, int xoff, int yoff)
{
	for (int j = 0; j < N_LANES; j++) {
		for (List *i = lanes[j]->first(); i->hasValue(); i = i->next())
		{ 
			Vehicle *current = i->value();
			int x = (int) (current->pos() * PIX_PER_MILE);
			int go_right = IsLowerLane(j);
			//
			// Decide whether vehicle is moving 
			// to the right or left.
			//
			x = go_right ? x : width - x;
			
			XSetForeground(display, gc, 
					state_to_color(current->vstate()));

			int y = yloc[j];
			int state = current->vstate();
	
			if (ChangingLanes(state) || current->lane_change()) {
				switch (j) {
				case 0:
					y += current->lane_change();
					break;
				case 1:
					y -= current->lane_change();
					break;
				case 2:
					y -= current->lane_change();
					break;
				case 3:
					y += current->lane_change();
					break;
				}
			}
			//
			// Tell the vehicle to draw itself.
			//
			int selected  = (current == popup_current);

			current->draw(display, pix, gc, x, y,
					go_right, scale, xoff, yoff, selected);
		}
	}
}

//
// Draw the whole roadway.
//
void
traffic_display()
{
	static   int  boxed = FALSE;
	//
	// If I'm not ready to draw, bail out.
	//
	if (!display || !xwin || !gc ) {
		return;
	}
	// Erase roadway by copying empty version from pix_1.
	XCopyArea(display, pix_1, pix_2, gc, 0, 0, width, lanes_height, 0, 0);
			
	draw_vehicles(pix_2, 1, 0, 0);
	
	XCopyArea(display, pix_2, xwin, gc, 0, 0, width, lanes_height, 0, 
			lanes_top);
	if (popup_current) {
		BoxPopupArea();
	}
	XFlush(display);
}


//
// Get requested pixel value (color) by name.
//
static unsigned long
get_color(Display *dpy, Colormap cmap, char *name)
{
	XColor cdef;
	XColor rgbdef;
	
	if (XAllocNamedColor(dpy, cmap, name, &cdef, &rgbdef)) {
//	if (XParseColor(dpy, cmap, name, &cdef) &&
//			XAllocColor(dpy, cmap, &cdef)) {
		return cdef.pixel;
	} else {
		return WHITE;
	}
}

//
// Return color for a given state.
//
static unsigned long
state_to_color(int s)
{
	switch(s) {
	case VSTATE_COAST:
		return color_orange;
	case VSTATE_BRAKE:        
		return color_red;   
	case VSTATE_ACCELERATE:   
		return color_green; 
	case VSTATE_CRASH:        
		return color_yellow;
	case VSTATE_MAINTAIN:     
		return color_white; 
	case VSTATE_MAX_SPEED:
		return color_blue;  
	case VSTATE_CHANGE_LANE:
	case VSTATE_CHANGE_LEFT:
	case VSTATE_CHANGE_RIGHT:
		return color_violet;
	default:
		return color_black; // shouldn't happen
	}
}

//
// Set speed limit menus based on limits[] array.
//
static void
traffic_set_limits()
{
	FwyZoneObjects *zobjs= window.control_objects->zone_objects;
	for (int ix = 0; ix < NZONES; ix++) {
		int which = (55 - limits[ix]) / 10;
		XtVaSetValues(	zobjs->z[ix].spop,
				XmNmenuHistory, zobjs->z[ix].sp[which],
				NULL);
	}
}


static const int border = 15;

//
// Display the turn sign.
//
static void
display_signs()
{
#include "arrow_up.bitmap"
#include "arrow_over.bitmap"
#include "arrow_right.bitmap"
#include "arrow_left.bitmap"

	static Pixmap pix_over  = NULL;
	static Pixmap pix_up    = NULL;
	static Pixmap pix_right = NULL;
	static Pixmap pix_left  = NULL;

	int w = arrow_over_width;
	int h = arrow_over_height;
	int l = border / 4;
	int r = width - w - border / 4;
	int t = 0;	// Arrow tops are at top of drawing area
	int b = lanes_top + lanes_height + border / 4;

	unsigned long fg = (pixel_depth > 1) ? color_white : color_black;
	unsigned long bg = (pixel_depth > 1) ? color_black : color_white;

	if (!pix_over) {
		pix_over = XCreatePixmapFromBitmapData
			(display, xwin, (char *)arrow_over_bits, w, h,
			  fg, bg, pixel_depth);
	}
	if (!pix_up) {
		pix_up = XCreatePixmapFromBitmapData
			(display, xwin, (char *)arrow_up_bits, w, h,
			 fg, bg, pixel_depth);
	}
	if (!pix_right) {
		pix_right = XCreatePixmapFromBitmapData
			(display, xwin, (char *)arrow_right_bits, w, h,
			 fg, bg, pixel_depth);
	} 
	if (!pix_left) {
		pix_left = XCreatePixmapFromBitmapData
			(display, xwin, (char *)arrow_left_bits, w, h,
			  fg, bg, pixel_depth);
	}

	XCopyArea(display, pix_up,    xwin, gc, 0, 0, w, h, r, b);
	XCopyArea(display, pix_over,  xwin, gc, 0, 0, w, h, r, t);
	XCopyArea(display, pix_left,  xwin, gc, 0, 0, w, h, l, t);
	XCopyArea(display, pix_right, xwin, gc, 0, 0, w, h, l, b);
}

const int legend_box_half = 14;
//
// Draw colored box for legend.
//
static void
draw_color_box(int x, int y, unsigned long c)
{
	int l = x;
	int t = y - legend_box_half;
	int r = x + legend_box_half;
	int b = y;
	
	// Fill rectangle in color
	XSetForeground(display, gc, c);
	XFillRectangle(display, xwin, gc, l, t, (r - l), (b - t));
	
	// Draw border in black
	XSetForeground(display, gc, color_black);
	draw_box(xwin, gc, l, t, r, b);
}

//
// Display a legend indicating which colors belong to which state
//
static void
display_legend()
{
	// Position below lower arrow signs
	int y = legend_box_half + arrow_over_height +
			(lanes_top + lanes_height + border / 2);
	
	for (int i = VSTATE_MAINTAIN; i <= VSTATE_CHANGE_LANE; i++) {
		int x = (i * width / (VSTATE_CHANGE_LANE + 1));
		unsigned long c = state_to_color(i);
			
		draw_color_box(x, y, c);
			
		XSetForeground(display, gc, color_white);
		XDrawString(display, xwin, gc, x + 20, y,
				state_names[i], strlen(state_names[i]));
	}
}

//
// Mark the different speed zones above the roadway.
//
static void
display_zones()
{
	int y = border;
	
	for (int ix = 0; ix < 3; ix++) {
		char buf[20];
		int x_line = ix * PIX_PER_SIGN;
		int x_text = x_line + PIX_PER_SIGN/3;

		XSetForeground(display, gc,
				(pixel_depth > 1)? color_white : color_black);
		if (ix) {
			XDrawLine(display, xwin, gc, 
				   x_line, y - 15,
				   x_line, y +  5);
		}
			
		sprintf(buf, "Speed Zone %d", ix+1);
		XDrawString(display, xwin, gc, x_text, y, buf, strlen(buf));
	}
}

//
// Get graphics context, color map, etc.
//
static void
setup_graphics(Display *dpy, Window xwin)
{
	XWindowAttributes window_attributes;
	Colormap cmap;
	
	// get cmap
	XGetWindowAttributes(dpy, xwin, &window_attributes);
	cmap = window_attributes.colormap;
	
	// make gc
	gc   = XCreateGC(dpy, xwin, 0, NULL);
	XGetGCValues(dpy, gc, 0, &xgcv);
	
	// get some colors
	color_green	= get_color(dpy, cmap, (char *) "green");
	color_red	= get_color(dpy, cmap, (char *) "red");
	color_yellow	= get_color(dpy, cmap, (char *) "yellow");
	color_orange	= get_color(dpy, cmap, (char *) "orange");
	color_blue	= get_color(dpy, cmap, (char *) "cyan");
	color_violet	= get_color(dpy, cmap, (char *) "magenta");
	color_white	= get_color(dpy, cmap, (char *) "white");
	color_black	= get_color(dpy, cmap, (char *) "black");
	color_grey	= get_color(dpy, cmap, (char *) "grey70");
	if (color_black == WHITE) {
		color_black = BLACK; // shouldn't happen
	}
	
	pix_1 = XCreatePixmap(dpy, xwin, width, lanes_height, pixel_depth);
	pix_2 = XCreatePixmap(dpy, xwin, width, lanes_height, pixel_depth);
	pop_pix = XCreatePixmap(dpy, xwin, width, lanes_height * 3, pixel_depth);

}

//
// Draws black road with yellow and white lines for roadway.
//
void
draw_street(Pixmap pix, int scale, int xoff)
{
	int mid = lanes_height / 2;

	// Draw street in black
	XSetForeground(display, gc, color_black);
	XFillRectangle(display, pix, gc, 0, 0,
		width * scale, lanes_height * scale);
	
	// Draw lane lines -- center divider
	XSetForeground(display, gc, color_yellow);
	XFillRectangle(display, pix, gc, 0, mid * scale, width * scale, scale);
	
	// Draw lane lines -- dashed lanes 
	XSetForeground(display, gc, color_white);
	for (int l = 1; l < LANES_EACH_DIR; l++) {
		int yoff  = l * LANE_WIDTH;
		int yup   = (mid - yoff) * scale;
		int ydown = (mid + yoff) * scale;
		for (int i = 0; i < width; i += DASH_PERIOD) {
			XFillRectangle(display, pix, gc, i * scale + xoff,
				yup,   DASH_LENGTH * scale, scale);
			XFillRectangle(display, pix, gc, i * scale + xoff,
				ydown, DASH_LENGTH * scale, scale);
		}
	}
	// Draw lane lines -- edges
	int bot = (lanes_height - 1) * scale;
	XFillRectangle(display, pix, gc, 0, 0,   width * scale, scale);
	XFillRectangle(display, pix, gc, 0, bot, width * scale, scale);
}

//
// Repaint the canvas.  Called for expose events, like when the windows are
// first created.
//
void
traffic_repaint(Widget widget, XtPointer clientdata,
			XEvent *event, Boolean *cont)
{
	width = DRAWING_WIDTH;
	height = DRAWING_HEIGHT;
	width_in_miles = (double) width / (double) PIX_PER_MILE;

	// Lanes placed underer arrow signs
	lanes_top = arrow_over_height + border/4;
	lanes_height = 2 * LANE_WIDTH * LANES_EACH_DIR + 1;
	int lanes_middle = lanes_top + LANE_WIDTH * LANES_EACH_DIR;

	yloc[0]   = lanes_middle + ((LANE_WIDTH-CAR_WIDTH) / 2) - lanes_top;
	yloc[1]   = lanes_middle - ((LANE_WIDTH+CAR_WIDTH) / 2) - lanes_top;
	yloc[2]   = yloc[0] + LANE_WIDTH;
	yloc[3]   = yloc[1] - LANE_WIDTH;
	box_t     = lanes_top + 1;
	box_b     = lanes_top + lanes_height - 3;

	if (!xwin) {
		XWindowAttributes watts;

		xwin      = XtWindow(window.drawing);
		XGetWindowAttributes(display, xwin, &watts);
		pixel_depth = watts.depth;
	}

	if (!gc) {
		setup_graphics(display, xwin);
	}

	if (pixel_depth > 1) {
		display_legend();
	}
	display_zones();
	display_signs();
	draw_street(pix_1, 1, 0);
	traffic_display();
}


//
// Repaint the popup canvas.  Doesn't actually draw yet.  Just remember stuff.
//
void
traffic_popup_repaint(Widget widget, XtPointer clientdata,
			XEvent *event, Boolean *cont)
{
	if (!gc) {
		return;
	}
	// Remember stuff for drawing later
	popup_xwin   = xwin;
	//popup_width  = (int) xv_get(paint_window, XV_WIDTH);
	//popup_height = (int) xv_get(paint_window, XV_HEIGHT);
	popup_top    = (popup_height / 2) - LANE_WIDTH * LANES_EACH_DIR * 3;
}

//
// Draw vehicles on popup.  They are magnified (x3) from the regular roadway.
//
void
traffic_popup_display(int xoff)
{
	//
	// If I'm not ready to draw, bail out.
	//
	if (!popup_xwin) {
		return;
	}

	// Erase roadway.
	XSetForeground(display, gc, color_black);
	XFillRectangle(display, pop_pix, gc, 0, 0,
			popup_width, lanes_height * 3);

	// Draw vehicles over street lines.
	int xadj = (xoff - popup_current->xloc()) * 3 + popup_width / 2;
	draw_street  (pop_pix, 3, xadj);
	draw_vehicles(pop_pix, 3, xadj, 0);

	// Erase parts of roadway which are off edge of screen
	int xleft = popup_current->xloc() - popup_width / 6 - xoff;
	int xright = popup_current->xloc() + popup_width / 6 - xoff;
	int left_edge = (xleft  < 0)     ? -3 * xleft : 0;
	int right_edge = (xright > width) ? 
		popup_width - 3 * (xright - width) : popup_width;
	int show_width = right_edge - left_edge;
	if (left_edge) {
		XClearArea(display, popup_xwin, 0, 0, left_edge, 0, 0);
	} else {
		XClearArea(display, popup_xwin, right_edge, 0, 0, 0, 0);
	}

	// Copy to the display
	XCopyArea(display, pop_pix, popup_xwin, gc, left_edge, 0, show_width, 
			lanes_height * 3, left_edge, popup_top);
	XFlush(display);
}


/*******************************************************************
//
// Handle mouse events in the canvas.  It was probably the user selecting a car
//
void
traffic_mouse_event(Xv_window xvwin, Event *event, Notify_arg)
{
	//
	// If this is not a "mouse selection", bail out.
	//
	if (event_action(event) != ACTION_SELECT || !event_is_down(event)) {
		return;
	}

	//
	// See if this mouse click happened in the main window or in the popup
	//
	int in_popup = (xvwin == canvas_paint_window(popup_obj->canvas2));
	int scale = in_popup ? 3 : 1;
	int lane_match = -1;

	//
	// Try to figure out which vehicle was selected.
	//
	for (int j = 0; j < N_LANES; j++) {
		int y;

		if (in_popup) {
			y = yloc[j] * scale + popup_top;
		} else {
			y = yloc[j] + lanes_top;
		}

		// If y matches for a particular lane...
		if (is_between(event->ie_locy, 
				 y - 4*scale, y + (CAR_WIDTH+4)*scale))
		{
			lane_match = j;
			break;
		}
	}
	if (lane_match == -1) {
		return;	// mouse click was not in traffic
	}

	Vehicle *closest  = NULL;
	int      distance = 2000;

	// 
	// Find the vehicle in this lane which is closest to the mouse click.
	//
	for (List *i = lanes[lane_match]->first(); i->hasValue(); i = i->next())
	{ 
		Vehicle *current = i->value();
		int x = current->xloc();

		if (in_popup) {
			x = scale * (x - popup_current->xloc() + CAR_LENGTH/2) 
			             + popup_width/2;
			int dx = abs(event->ie_locx - x);
			if (distance > dx) {
				distance = dx;
				closest  = current;
			}
		}

		if (closest == NULL) {
			return;	// nobody nearby
		}

		if (in_popup) {
			// scroll the popup to center the selection
			traffic_popup_scroll(closest);
		} else if (popup_current) {
			// display the popup with the selected vehicle
			if (abs(popup_current->xloc() - closest->xloc())
					< popup_width / 6) {
				traffic_popup_scroll(closest);
			} else {
				traffic_popup(closest);
			}
		} else {
			was_running = running;
			traffic_stop();
			traffic_popup(closest);
		}
	}
}
*******************************************************/


//
// Called by traffic_init() and traffic_reset().  Set default values
// for buttons, sliders, etc.
//
void
traffic_default_settings()
{
	// gap between new cars slider
	XmScaleSetValue(window.control_objects->gap_slide, 20);
	traffic_gap(20);
	
	// time between updates slider
	XmScaleSetValue(window.control_objects->time_slide, 40);
	traffic_time(40);
	
	// randomize
	randomize = TRUE;
	XmToggleButtonGadgetSetState(
			window.control_objects->yes_tog,
			randomize,
			TRUE);
	
	// speed limits
	for (int i = 0; i < 3; i++) {
		limits[i] = 55;
	}
	traffic_set_limits();
}


//
// Called when application first starts from modified window_stubs.C
// Gives us an opportunity to jot down some global variables for window stuff.
//
void 
traffic_init(int argc, char **argv)
{
	int i;
	// Initialize some local variables
	for (i = 0; i < N_LANES; i++) {
		lanes[i] = new List();
	}
	
	// Set up traffic_repaint() to be called whenever window is exposed.
	XtAddEventHandler(window.drawing, ExposureMask,
		False, traffic_repaint, NULL);


//  // Set up traffic_mouse_event() to intercept events for mouse clicks.
//  xv_set(canvas_paint_window(window.canvas1),
//	 WIN_EVENT_PROC,     traffic_mouse_event,
//	 WIN_CONSUME_EVENTS, WIN_MOUSE_BUTTONS, NULL,
//	 NULL);
//  xv_set(canvas_paint_window(popup_obj->canvas2),
//	 WIN_EVENT_PROC,     traffic_mouse_event,
//	 WIN_CONSUME_EVENTS, WIN_MOUSE_BUTTONS, NULL,
//	 NULL);
//  
//  // Set up traffic_popup_repaint() to be called whenever popup is exposed.
//  xv_set(popup_obj->canvas2,
//	 CANVAS_REPAINT_PROC,   traffic_popup_repaint,
//	 CANVAS_X_PAINT_WINDOW, TRUE,
//	 NULL);
//  

	// Set speeds, buttons, etc to default.
	traffic_default_settings();

	// Reset clock to time of big bang.
	clock_advance(FALSE);

	// Show status in frame
	traffic_frame();

	// Parse command line.
	for (i = 1; i < argc; i++) {
		if (argv[i][0] != '-') {
			traffic_current_file = argv[i];	// name of file to load
			traffic_do_load(traffic_current_file);
		}
	}
}


//////////////////////////////////////////////////////////////////////
//                                                                  //
//                                                                  //
//           FUNCTIONS CALLED IN RESPONSE TO USER ACTIONS           //
//                                                                  //
//                                                                  //
//////////////////////////////////////////////////////////////////////


//
// Called when user moves "gap" slider.  "gap" arg ranges from 0 to 100.
//
void
traffic_gap(int gap)
{
	generate_gap = (double) (20.0 + 4.0 * gap) / 5280;
}

//
// Called when user moves "time" slider.  "time" arg ranges from 0 to 100.
//
void
traffic_time(int time)
{
	double frac = (double) time / 100.0;

	// Set update time to range from 1/20 to 19/20
	// second by a quadratic scale
	update_time  = (int) ((double) (ONE_SEC - TENTH_SEC) * (frac * frac));
	update_time += TWENTIETH_SEC;

	if (running) {
		// Set up new timer with correct update time
		traffic_stop();
		traffic_start();
	}
}

//
// Called when user clicks mouse button on a particular vehicle.
// Causes "vehicle info" popup to appear.
//
void
traffic_popup(Vehicle *v)
{
	popup_current = v;

	traffic_set_popup_values(v);

	//xv_set(popup_obj->popup1, FRAME_CMD_PUSHPIN_IN, TRUE, NULL);
	//xv_set(popup_obj->popup1, XV_SHOW, TRUE, NULL);
	
	traffic_display();	// puts dot in current vehicle on main
	traffic_popup_display(0);
	traffic_frame();	// indicate state "suspended" if appropriate
}

//
// Scroll popup until given vehicle is centered and selected.
// This function was called in response to a mouse click by the user.
//
void
traffic_popup_scroll(Vehicle *v)
{
	int dx  = v->xloc() - popup_current->xloc();
	int dir = (dx > 0) ? -1 : 1;

	popup_current = v;
	traffic_set_popup_values(v);
	traffic_display();		// puts dot in current vehicle on main


#define round_to(m, i) ( ((int) ((i) / (m))) * m )

	const int step = 5;

	// Scroll to the correct place such that the current vehicle is centered
	for (int i = round_to(step, dx); (i*dir) <= 0; i += (dir * step)) {
		traffic_popup_display(i);
	}
}

//
// Called to put values from vehicle into popup
//
void
traffic_set_popup_values(Vehicle *v)
{
	static char buffer[20];
	
	if (!v) return;
	
	//xv_set(popup_obj->choice_state, PANEL_VALUE, v->vstate(), NULL);
	
	//xv_set(popup_obj->choice_class, PANEL_VALUE, v->classnum(), NULL);
	
	sprintf(buffer, "%d", v->name());
	//xv_set(popup_obj->textfield_vehicle, PANEL_VALUE, buffer, NULL);
	
	sprintf(buffer, "%d", (int) (v->pos() * 5280.0));
	//xv_set(popup_obj->textfield_position, PANEL_VALUE, buffer, NULL);
	
	//xv_set(popup_obj->textfield_velocity, PANEL_VALUE, (int) v->vel(), NULL);
	
	//xv_set(popup_obj->textfield_max_speed, PANEL_VALUE, v->top_speed(), NULL);

	// Get gap in front and back
	List  *front     = lanes[v->lane()]->next(v);
	List  *back      = lanes[v->lane()]->prev(v);
	double front_gap = front->hasValue() ? front->value()->rear_pos()-v->pos():-1;
	double  back_gap = back ->hasValue() ? v->rear_pos()-back->value()->pos() :-1;

#define round(f) (int) ((f) + 0.5)

	if (front_gap < 0) {
		sprintf(buffer, "(lead car)");
	} else {
		sprintf(buffer, "%d", round(front_gap * 5280.0));
	}
	//xv_set(popup_obj->textfield_front_gap,  PANEL_VALUE, buffer, NULL);

	if (back_gap < 0) {
		sprintf(buffer, "(rear car)");
	} else {
		sprintf(buffer, "%d", round(back_gap * 5280.0));
	}
	//xv_set(popup_obj->textfield_behind_gap, PANEL_VALUE, buffer, NULL);
}


//
// Called when user presses start button
//
void
traffic_start()
{

	traffic_force_popup_done();

	if (running == 0) {
		running = 1;
		// Start simulation timer 
		timerhandle = XtAppAddTimeOut(
			app_context,
			(unsigned long)update_time,
			(XtTimerCallbackProc)traffic_simulate,
			NULL);
	}
	traffic_frame();		// update frame with file name and status
}


//
// Called when user presses stop button
//
void
traffic_stop()
{
	// Turn off timer
	if (running) {
		running = 0;
		XtRemoveTimeOut(timerhandle);
	}
	traffic_frame();		// update frame with file name and status
}

//
// Called when user presses reset button
//
void
traffic_reset()
{
	traffic_force_popup_done();
	traffic_stop();
	traffic_file_close();
	traffic_default_settings();

	//
	// Remove existing vehicles
	//
	for (int j = 0; j < N_LANES; j++) {
		while (!lanes[j]->isEmpty()) {
			Vehicle *v = lanes[j]->first()->value();
			lanes[j]->remove(v);
			delete v;
		}
	}
	name_counter = 0;		// start counting vehicles at 0 again
	traffic_display();		// display empty lanes
	traffic_stats(FALSE);		// erase averages velocities
	clock_advance(FALSE);		// reset clock to time of big bang

}

//
// Called when user chooses "Clear Wrecks" menu item.
//
void
traffic_clear()
{
	traffic_stop();

	for (int j = 0; j < N_LANES; j++) {
		List *next = NULL;
		for (List *i = lanes[j]->first(); i->hasValue(); i = next) { 
			Vehicle *current;
		
			current = i->value();
			next    = i->next(); 

			if (current->vstate() == VSTATE_CRASH) {
				lanes[j]->remove(current);
			}
		}
	}
	traffic_display();	// display lanes without wrecked cars
	traffic_stats(FALSE);	// do statistics to erase averages velocities
}

//
// Called when user chooses "load" from filename popup
//
void
traffic_do_load(char *filename)
{
	if (!filename) {
		return;
	}

	traffic_reset();

	if (traffic_current_file) {
		free(traffic_current_file);
	}
	traffic_current_file = strdup(filename);

	ifstream mystream(filename, ios::in);

	// Get application state...
	for (int i = 0; i < 3; i++) {
		mystream >> limits[i];    // limits
		if (limits[i] > 55 || limits[i] < 15) {
			limits[i] = 55;
		}
	}
	traffic_set_limits();

	int gap, time;
	mystream >> gap;
	if (gap >= 0 && gap <= 100) {
		// Check if in range of slider since read-in of a bad-value
		// (e.g. if non-freeway-saved file is accidently read)
		// causes strange window-system errors.
		XmScaleSetValue(window.control_objects->gap_slide, gap);
		traffic_gap(gap);
	}

	mystream >> time;
	if (time >= 0 && time<= 100) {
		// Check if in range of slider since read-in of a bad-value
		// (e.g. if non-freeway-saved file is accidently read)
		// causes strange window-system errors.
		XmScaleSetValue(window.control_objects->time_slide, time);
		traffic_time(time);
	}

	mystream >> randomize;				// randomize

	if (randomize != TRUE && randomize != FALSE) {
		randomize == TRUE;
	}

	XmToggleButtonGadgetSetState(
			window.control_objects->yes_tog,
			randomize,
			TRUE);

	mystream >> name_counter;

	Vehicle *current = NULL;
	while (mystream.good()) { 
		int classnum;

		mystream >> classnum;

		if (mystream.good()) {
			Vehicle *v = new_vehicle(classnum, 0, 0, 0.0, 0.0);
			mystream >> *v;
			if (mystream.fail())  {
				delete v;
			} else {
				lanes[v->lane()]->append(v);
			}
		}
	}
	mystream.close();
	traffic_frame();	// update frame with file name and status
	traffic_stats(FALSE);	// do statistics on vehicles in lanes
	traffic_display();	// display the vehicles in new states
}

//
// Called when user chooses "save" from file menu
//
void
traffic_do_save(char *filename)
{
	if (!filename) {
		return;
	}
	if (traffic_current_file) {
		free(traffic_current_file);
	}
	traffic_current_file = strdup(filename);

	ofstream mystream(traffic_current_file, ios::out);

	// Dump application state...
	for (int i = 0; i < 3; i++) {
		mystream << limits[i] << "\t";       // limits
	}
	int value = 0;
	XmScaleGetValue(window.control_objects->gap_slide, &value);
	mystream << value << "\t";		 		// gap
	XmScaleGetValue(window.control_objects->time_slide, &value);
	mystream << value << "\t";				// time
	mystream << randomize << " " << name_counter << endl;	// random,etc

	// Dump vehicle states...
	for (int j = 0; j < N_LANES; j++) {
		for (List *l = lanes[j]->first(); l->hasValue(); l = l->next())
		{ 
			Vehicle *current = l->value();
			mystream << current->classnum() <<
					"\t" << *current << endl;
		}
	}
	mystream.close();
	traffic_frame();// update frame with file name and status
}

//
// Called when user chooses "close" from file menu
//
void
traffic_file_close()
{
	if (!traffic_current_file) {
		return;
	}
	free(traffic_current_file);
	traffic_current_file = NULL;
	traffic_frame();	// update frame with file name and status
}

//
// Called when user changes a speed limit.
//
void
traffic_speed(int zone, int limit)
{
	limits[zone] = limit;
}

//
// Called when user changes max_speed in popup
//
void
traffic_max_speed(int m)
{
	popup_current->top_speed(m);
}

//
// Called when user presses step button in popup
//
void
traffic_step()
{
	traffic_simulate(NULL, 0);

	if (popup_current) {
		// current may have been removed during _simulate()
		traffic_popup_display(0);
		traffic_set_popup_values(popup_current);
	}
}

//
// Called when user presses remove button in popup
//
void
traffic_remove()
{
	int lane = popup_current->lane();
	int oldx = popup_current->xloc(); 

	// find car to be showing next (either previous or next car in list)
	List *l = lanes[lane]->prev(popup_current);

	if (!l->hasValue()) {
		l = lanes[lane]->next(popup_current);
	}
	// remove car from the list
	lanes[lane]->remove(popup_current);
	delete popup_current;

	// show next one or hide popup
	if (l->hasValue()) {
		Vehicle *next = l->value();
		if ( abs(oldx - next->xloc()) < popup_width / 6) {
			traffic_popup_scroll(next);
		} else {
			traffic_popup(next);
		}
	} else {
		traffic_force_popup_done();
	}
}

//
// Force popup to hide.
//
void
traffic_force_popup_done()
{
	if (popup_current) {
		traffic_popup_done();
	}
}

//
// Called when user removes pushpin on popup
//
void
traffic_popup_done()
{

	// traffic_get_popup_values();
	//traffic_state((int) xv_get(popup_obj->choice_state, PANEL_VALUE));
	//traffic_class((int) xv_get(popup_obj->choice_class, PANEL_VALUE));
	//traffic_position((char *) xv_get(popup_obj->textfield_position, PANEL_VALUE));
	//traffic_velocity((int) xv_get(popup_obj->textfield_velocity, PANEL_VALUE));
	//traffic_max_speed((int) xv_get(popup_obj->textfield_max_speed, PANEL_VALUE));

	popup_current = NULL;

	traffic_display();		// draw traffic without "current" vehicle

	if (was_running) {
		traffic_start();
	}
}

//
// Called when user types in position textfield
//
void
traffic_position(char *text)
{
	double val;
	sscanf(text, "%lf", &val);
	val /= 5280.0;
	popup_current->pos(val);
}

//
// Called when user types in velocity textfield
//
void
traffic_velocity(int val)
{
	if (( (int) popup_current->vel() ) != val) {
		// If it has changed...
		popup_current->vel((double) val);
	}
}

//
// Called when user changes "state" choice item
//
void
traffic_state(int newstate)
{
	if (newstate == popup_current->vstate()) {
		return;
	}
	
	popup_current->vstate((VState) newstate);
	
	traffic_popup_display(0);
	traffic_display();		// display on main window
}

//
// Called when user changes "class" choice item
//
void
traffic_class(int newclass)
{
	//
	// Don't do anything if it's the same class.
	//
	if (newclass == popup_current->classnum()) {
		return;
	}

	int    lanenum = popup_current->lane();
	double pos     = popup_current->pos();
	double vel     = popup_current->vel();

	// 
	// Create a new vehicle in the chosen class with the same
	// characteristics as the current vehicle.
	//
	Vehicle *v = new_vehicle(newclass, name_counter++, lanenum, pos, vel);

	v->vstate(popup_current->vstate());
	v->xloc(popup_current->xloc());
	v->top_speed(popup_current->top_speed());
	v->lane_change(popup_current->lane_change());

	//
	// Make the switch. 
	//
	List *lane = lanes[popup_current->lane()];
	lane->remove(popup_current);
	delete popup_current;
	popup_current = v;
	lane->insert(popup_current);
	traffic_set_popup_values(popup_current);
	traffic_popup_display(0);
	traffic_display();		// display on main window
}

//
// Called when user changes "randomize" choice item
//
void
traffic_randomize(int choice)
{
	randomize = choice;
}


