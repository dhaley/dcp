#pragma ident   "@(#)main.cc	1.9    02/02/05 SMI"

// Copyright 1991, 1994, 2000, 2002 Sun Microsystems, Inc.  All Rights Reserved
 
//
// main.cc - Create and initialize GUI objects and simulation.
// 		start even loop
//

#include "window_ui.h"
#include "traffic.h"

//
// Global definitions.
//
FreewayWindow	window;
XtAppContext	app_context;
Display		*display;

main(int argc, char **argv)
{
	//
	// Initialize Window System Interface
	//
	XtSetLanguageProc ((XtAppContext)NULL, (XtLanguageProc)NULL,
				(XtPointer) NULL);
	XtToolkitInitialize ();
	app_context = XtCreateApplicationContext ();
	display = XtOpenDisplay (app_context, NULL, argv[0], "freeway",
				NULL, 0, &argc, argv);
	if(!display)
	{
		printf("%s: can't open display, exiting...\n", argv[0]);
		exit(-1);
	}
	//
	// Initialize user interface components.
	//
	window.objects_initialize(argc, argv);
	// 
	// Initialize traffic simulation);
	//
	traffic_init(argc, argv);
	//
	// Turn control over to the event loop
	//
	XtRealizeWidget(window.shell); // display top-level widget.
	XtAppMainLoop(app_context);
	return 0;
}

