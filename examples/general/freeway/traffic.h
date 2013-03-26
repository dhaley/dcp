#pragma ident   "@(#)traffic.h	1.6    02/02/05 SMI"

// Copyright 1991, 1994, 2000, 2002 Sun Microsystems, Inc.  All Rights Reserved
 
//
// Freeway traffic-simulation control functions
//
//

class Vehicle;
class FreewayWindow;

extern void traffic_init(int, char **);

extern void traffic_start();
extern void traffic_stop();
extern void traffic_display();
extern void traffic_reset();
extern void traffic_clear();
extern void traffic_popup_done();
extern void traffic_popup_display(int);
extern void traffic_generate();
extern void traffic_popup(Vehicle *);
extern void traffic_gap(int);
extern void traffic_time(int);
extern void traffic_state(int);
extern void traffic_class(int);
extern void traffic_randomize(int);
extern void traffic_position(char *);
extern void traffic_velocity(int);
extern void traffic_max_speed(int);
extern void traffic_step();
extern void traffic_remove();
extern void traffic_speed(int zone, int limit);
extern void traffic_force_popup_done();
extern void traffic_set_popup_values(Vehicle *);
extern void traffic_popup_scroll(Vehicle *);
extern void traffic_cancel();
extern void traffic_do_load(char *);
extern void traffic_do_save(char *);
extern void traffic_file_close();

extern char *traffic_current_file;

