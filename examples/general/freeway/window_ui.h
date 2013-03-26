#pragma ident   "@(#)window_ui.h	1.17    02/02/05 SMI"

// Copyright 1994, 2000, 2002 Sun Microsystems, Inc.  All Rights Reserved

#ifndef	WINDOW_UI_H
#define	WINDOW_UI_H

#include <X11/Xatom.h>
#include <X11/Intrinsic.h>
#include <X11/Shell.h>

#include <Xm/Xm.h>
#include <Xm/ArrowB.h>
#include <Xm/CascadeB.h>
#include <Xm/DialogS.h>
#include <Xm/DrawingA.h>
#include <Xm/FileSB.h>
#include <Xm/Form.h>
#include <Xm/Label.h>
#include <Xm/List.h>
#include <Xm/PushB.h>
#include <Xm/RowColumn.h>
#include <Xm/Scale.h>
#include <Xm/ScrollBar.h>
#include <Xm/SelectioB.h>
#include <Xm/Separator.h>
#include <Xm/Text.h>
#include <Xm/TextF.h>
#include <Xm/CascadeBG.h>
#include <Xm/LabelG.h>
#include <Xm/PushBG.h>
#include <Xm/SeparatoG.h>
#include <Xm/ToggleBG.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef HP_UX
const unsigned long WHITE = 1;
const unsigned long BLACK = 0;
#else
const unsigned long WHITE = 0;
const unsigned long BLACK = 1;
#endif

class FreewayWindow;
class VinfoWindow;
class FileWindow;
class HelpWindow;
class FwyControlObjects;
class FwyZoneObjects;
class FwyMenuObjects;
class VinfoControlObjects;

extern FreewayWindow   window;
extern XtAppContext    app_context;
extern Display         *display;

class FreewayWindow {
public:
	void objects_initialize(int, char **);

	Widget shell;

	Widget topform;
	Widget controlform;
	FwyControlObjects *control_objects;

	Widget drawing;
	Widget separator2;
	Widget statuslab;
	Widget quit;

	// Associated pop-up windows
	VinfoWindow *vinfo_winp;
	FileWindow *file_winp;
	HelpWindow *help_winp;
};

class FwyControlObjects {
public:
	void objects_initialize(Widget);

	Widget menubar;
	FwyMenuObjects *menu_objects;

	Widget gslid_lab;
	Widget gap_slide;
	Widget tslid_lab;
	Widget time_slide;
	Widget time_lab;
	Widget time_val;
	Widget rand_lab;
	Widget rantog;
	Widget no_tog;
	Widget yes_tog;
	Widget separator;


	Widget spform;
	FwyZoneObjects *zone_objects;

};

const int NZONES = 3;
const int NSPEEDS = 5;

// This is the original declaration of "array of speeds expressed as char *s"
//char *const SPEED_STR[NSPEEDS] = {  "55", "45", "35", "25", "15" };

// Changed to "array of speeds expressed as const char *s"
//const char * SPEED_STR[NSPEEDS] = { "55", "45", "35", "25", "15" };

// Is this the right way to do it? 5.x Compiler doesn't report any problem!!
char *const SPEED_STR[NSPEEDS]    = { (char *) "55",
				      (char *) "45",
 				      (char *) "35",
 				      (char *) "25",
 				      (char *) "15" 
}; 



class FwyZoneObjects {
public:
	void objects_initialize (Widget);

	struct Zone {
		Widget spop;
		Widget splab;
		Widget spcas;
		Widget spmen;
		Widget sp[NSPEEDS];
		Widget spzonel;
		Widget spzoneu;
	} z[NZONES];
};

class FwyMenuObjects {
public:
	void objects_initialize (Widget);

	Widget file_menu;
	Widget filemen;
	Widget loadbut;
	Widget save;
	Widget saveas;
	Widget closefile;
	Widget start;
	Widget stop;
	Widget reset_men;
	Widget resetmen;
	Widget clearwrckbut;
	Widget resetbut;
	Widget help_men;
	Widget helpmen;
	Widget about;

};

class HelpWindow {
public:
	void objects_initialize(FreewayWindow *);
	FreewayWindow *app_winp;

	Widget shell;
	Widget topform;
	Widget text;
	Widget clobut;
};

class FileWindow {
public:
	void objects_initialize(FreewayWindow *);
	FreewayWindow *app_winp;

	Widget shell;
	Widget fibox;
};


class VinfoWindow{
public:
	void objects_initialize(FreewayWindow *);
	FreewayWindow *app_winp;

	Widget shell;

	Widget topform;
	Widget controlform;
	VinfoControlObjects *control_objects;
	Widget drawing;
};


class VinfoControlObjects {
public:
	void objects_initialize(Widget);

	Widget vlab;
	Widget vval;
	Widget clab;
	Widget cop;
	Widget coplab;
	Widget copsed;
	Widget coptruc;
	Widget copsport;
	Widget copmaniac;
	Widget coppoice;
	Widget slab;
	Widget sop;
	Widget sopmain;
	Widget sopacc;
	Widget sopcoast;
	Widget sopbrake;
	Widget sopcrash;
	Widget sopmax;
	Widget sopchange;
	Widget splab;
	Widget spval;
	Widget spup;
	Widget spdown;
	Widget maxlab;
	Widget maxval;
	Widget maxup;
	Widget maxdown;
	Widget poslab;
	Widget posval;
	Widget fglab;
	Widget fgval;
	Widget bglab;
	Widget bgval;
	Widget stepbut;
	Widget rembut;
	Widget closebut;
};


/*
	Call-back functions
*/
extern void file_load (Widget, XtPointer, XtPointer );
extern void file_save (Widget, XtPointer, XtPointer );
extern void file_saveas (Widget, XtPointer, XtPointer );
extern void file_close (Widget, XtPointer, XtPointer );
extern void fwy_start (Widget, XtPointer, XtPointer );
extern void fwy_stop (Widget, XtPointer, XtPointer );
extern void reset_clear (Widget, XtPointer, XtPointer );
extern void reset_reset (Widget, XtPointer, XtPointer );
extern void help_about (Widget, XtPointer, XtPointer );
extern void gap_change (Widget, XtPointer, XtPointer );
extern void time_change (Widget, XtPointer, XtPointer );
extern void rand (Widget, XtPointer, XtPointer );
extern void zone_speed (Widget, XtPointer, XtPointer );
extern void fw_quit (Widget, XtPointer, XtPointer );
extern void fi_cancel (Widget, XtPointer, XtPointer );
extern void fi_help (Widget, XtPointer, XtPointer );
extern void fi_ok (Widget, XtPointer, XtPointer );
extern void vi_class_select (Widget, XtPointer, XtPointer );
extern void vi_state_select (Widget, XtPointer, XtPointer );
extern void vi_speed_up (Widget, XtPointer, XtPointer );
extern void vi_speed_down (Widget, XtPointer, XtPointer );
extern void vi_max_up (Widget, XtPointer, XtPointer );
extern void vi_max_down (Widget, XtPointer, XtPointer );
extern void vi_step (Widget, XtPointer, XtPointer );
extern void vi_remove_vehicle (Widget, XtPointer, XtPointer );
extern void vi_close (Widget, XtPointer, XtPointer );
extern void help_close (Widget, XtPointer, XtPointer );
extern void popup_destroyed (Widget, XtPointer, XtPointer );

#endif /* WINDOW_UI_H */
