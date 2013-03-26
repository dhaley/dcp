#pragma ident   "@(#)callbacks.cc	1.14    02/02/05 SMI"

// Copyright 1991, 1994, 2000, 2002  Sun Microsystems, Inc.  All Rights Reserved
 
//
// window_stubs.cc - Callback functions for UI events and actions
//

#include "window_ui.h"
#include "traffic.h"
#include "about.h"

static int do_file_load = 0;
//
// Handler for "Load..." menu item
//
void 
file_load(Widget w, XtPointer client_data, XtPointer xt_call_data )
{
	do_file_load = 1;
	XtVaSetValues(window.file_winp->shell,
			XmNtitle, "Freeway Load File", NULL);
	XtMapWidget(window.file_winp->shell);
}

static
void file_save_popup() {
	do_file_load = 0;
	XtVaSetValues(window.file_winp->shell,
			XmNtitle, "Freeway Save File", NULL);
	XtMapWidget(window.file_winp->shell);
}

//
// Handler for "Save" menu item
//
void 
file_save (Widget w, XtPointer client_data, XtPointer xt_call_data )
{
	if (!traffic_current_file) {
		file_save_popup();
	} else {
		traffic_do_save(traffic_current_file);
	}
}

//
// Handler for "Save As..." menu item
//
void 
file_saveas (Widget w, XtPointer client_data, XtPointer xt_call_data )
{
	file_save_popup();
}

//
// Handler for "Close" menu item
//
void 
file_close (Widget w, XtPointer client_data, XtPointer xt_call_data )
{
	traffic_file_close();
}

//
// Handler for "About.." help-menu item
//
void 
help_about (Widget w, XtPointer client_data, XtPointer xt_call_data )
{
	XmTextSetString(window.help_winp->text, (char *)about_text);
	XtMapWidget(window.help_winp->shell);
}

//
// Handler for `menu_reset (Reset)'.
//
void 
reset_reset (Widget w, XtPointer client_data, XtPointer xt_call_data )
{
	XmPushButtonCallbackStruct *call_data =
		(XmPushButtonCallbackStruct *) xt_call_data;
	traffic_reset();
}

//
// Handler for `menu_reset (Clear Wrecks)'.
//
void 
reset_clear (Widget w, XtPointer client_data, XtPointer xt_call_data )
{
	XmPushButtonCallbackStruct *call_data =
		(XmPushButtonCallbackStruct *) xt_call_data;
	traffic_clear();
}

//
// Callback function for `gap'.
//
void 
gap_change (Widget w, XtPointer client_data, XtPointer xt_call_data )
{
	XmScaleCallbackStruct *call_data =
		(XmScaleCallbackStruct *) xt_call_data;
	traffic_gap(call_data->value);
}

void 
fwy_start (Widget w, XtPointer client_data, XtPointer xt_call_data )
{
	XmAnyCallbackStruct *call_data =
		(XmAnyCallbackStruct *) xt_call_data;
	traffic_start();
}

//
// Callback function for `button_stop'.
//
void 
fwy_stop (Widget w, XtPointer client_data, XtPointer xt_call_data )
{
	XmAnyCallbackStruct *call_data =
		(XmAnyCallbackStruct *) xt_call_data;
	traffic_stop();
}


//
// Callback function for `choice_randomize'.
//
void 
rand (Widget w, XtPointer client_data, XtPointer xt_call_data )
{
	XmToggleButtonCallbackStruct *call_data =
		(XmToggleButtonCallbackStruct *) xt_call_data;
	int value = (int)client_data;
	traffic_randomize(value);
}

void 
time_change (Widget w, XtPointer client_data, XtPointer xt_call_data )
{
	XmScaleCallbackStruct *call_data =
		(XmScaleCallbackStruct *) xt_call_data;
	traffic_time(call_data->value);
}

//
// Callback function for setting speed zones.
// Callback function for `speed2'.
// Callback function for `speed3'.
void 
zone_speed (Widget w, XtPointer client_data, XtPointer xt_call_data )
{
	int ix;
	XmRowColumnCallbackStruct *call_data =
		(XmRowColumnCallbackStruct *) xt_call_data;
	if (client_data == NULL) {
		return;
	}
	int zone = ((int)client_data) - 1;
	FwyZoneObjects *zobjs= window.control_objects->zone_objects;
	for (ix = 0; ix < NSPEEDS; ix++) {
		if (zobjs->z[zone].sp[ix] == w)
			break;
	}
	if (ix >= NSPEEDS) {
		return;
	}
	traffic_speed(zone, 55-(10*ix));
}

//
// Callback for "Close" button on Vehicle Information popup
//
void 
vi_close (Widget w, XtPointer client_data, XtPointer xt_call_data )
{
	XtUnmapWidget(window.vinfo_winp->shell);
	traffic_popup_done();
}

//
// Callback for "Close" button on Help popup
//
void 
help_close (Widget w, XtPointer client_data, XtPointer xt_call_data )
{
	XtUnmapWidget(window.help_winp->shell);
}

//
// Callback function for `textfield_position'.
//
// Panel_setting
//handler_position(Panel_item item, Event *event)
//{
	//char *	value = (char *) xv_get(item, PANEL_VALUE);
	//traffic_position(value);
	//return panel_text_notify(item, event);
//}

//
// Callback function for `choice_class'.
//
void 
vi_class_select (Widget w, XtPointer client_data, XtPointer xt_call_data )
{
	XmRowColumnCallbackStruct *call_data =
		(XmRowColumnCallbackStruct *) xt_call_data;
	int value = 1;
	traffic_class(value);
}

//
// Callback function for `choice_state'.
//
void 
vi_state_select (Widget w, XtPointer client_data, XtPointer xt_call_data )
{
	XmRowColumnCallbackStruct *call_data =
		(XmRowColumnCallbackStruct *) xt_call_data;
	int value = 1;
	traffic_state(value);
}

//
// Callback function for `textfield_velocity'.
//

void 
vi_speed_up (Widget w, XtPointer client_data, XtPointer xt_call_data )
{
	XmArrowButtonCallbackStruct *call_data =
		(XmArrowButtonCallbackStruct *) xt_call_data;
	// Cause mouse clicks on increment/decrement buttons to jump 5 MPH.
	int value = 1;
	traffic_velocity(value);
}

void 
vi_speed_down (Widget w, XtPointer client_data, XtPointer xt_call_data )
{
	XmArrowButtonCallbackStruct *call_data =
		(XmArrowButtonCallbackStruct *) xt_call_data;
	// Cause mouse clicks on increment/decrement buttons to jump 5 MPH.
	int value = 1;
	traffic_velocity(value);
}

//
// Callback function for `button_step'.
//
void 
vi_step (Widget w, XtPointer client_data, XtPointer xt_call_data )
{
	XmPushButtonCallbackStruct *call_data =
		(XmPushButtonCallbackStruct *) xt_call_data;
	traffic_step();
}

//
// Callback function for `Remove Vehicle'.
//
void 
vi_remove_vehicle (Widget w, XtPointer client_data, XtPointer xt_call_data )
{
	XmPushButtonCallbackStruct *call_data =
		(XmPushButtonCallbackStruct *) xt_call_data;
	traffic_remove();
}

// Callback for up arrow settting maximum speed
void 
vi_max_up (Widget w, XtPointer client_data, XtPointer xt_call_data )
{
	XmArrowButtonCallbackStruct *call_data =
		(XmArrowButtonCallbackStruct *) xt_call_data;

	//int	value = (int) xv_get(item, PANEL_VALUE);
	int value = 1;
	traffic_max_speed(value);
	//return panel_text_notify(item, event);
}

// Callback for down arrow settting maximum speed
void 
vi_max_down (Widget w, XtPointer client_data, XtPointer xt_call_data )
{
	XmArrowButtonCallbackStruct *call_data =
		(XmArrowButtonCallbackStruct *) xt_call_data;
}

//
// Callback function for `OK' on file selector
//
void 
fi_ok (Widget w, XtPointer client_data, XtPointer xt_call_data )
{
	XmFileSelectionBoxCallbackStruct *call_data =
		(XmFileSelectionBoxCallbackStruct *)xt_call_data;

	char *text = 0;
	XmStringGetLtoR(call_data->value, XmSTRING_DEFAULT_CHARSET, &text);
	if (do_file_load) {
		traffic_do_load(text);
	} else {
		traffic_do_save(text);
	}
	XtFree(text);
	XtUnmapWidget(window.file_winp->shell);
}

//
// Callback function for `Cancel' on file selector
//
void 
fi_cancel (Widget w, XtPointer client_data, XtPointer xt_call_data )
{
	XtUnmapWidget(window.file_winp->shell);
}

//
// Callback for Freeway "Quit" button
void 
fw_quit (Widget w, XtPointer client_data, XtPointer xt_call_data )
{
	XmPushButtonCallbackStruct *call_data =
		(XmPushButtonCallbackStruct *) xt_call_data;
	traffic_stop();
	exit(0);
}

//
// Callback for Freeway "Quit" button
void 
popup_destroyed(Widget w, XtPointer client_data, XtPointer xt_call_data )
{
	// A user has used the window-system's popup-window menu
	// to dismiss the window. This cuases the window to be destroyed
	// since the XmdeleteResponse resource was sent to XmDESTROY
	// to avoid the strange behavior of different window managers.
	// Figure-out which window was destroyed and reinitialize it.

	if (w == window.file_winp->shell) {
		window.file_winp->objects_initialize(&window);
	} else if (w == window.help_winp->shell) {
		window.help_winp->objects_initialize(&window);
	} else if (w == window.vinfo_winp->shell){
		window.vinfo_winp->objects_initialize(&window);
	}
}

