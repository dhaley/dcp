#pragma ident   "@(#)window_ui.cc	1.21    02/02/05 SMI"

// Copyright 1991, 1994, 2000, 2002 Sun Microsystems, Inc.  All Rights Reserved
 
//
// window_ui.cc - Graphical User Interface object initialization functions.
//

#include "window_ui.h"
static unsigned int blue = BLACK;
static unsigned int grey = WHITE;

void
FreewayWindow::objects_initialize (
			int app_argc,
			char **app_argv)
{
	Arg al[10];		/* argument list */
	int ac = 0;		/* argument count */
	XmString xmstring;

	XtSetArg(al[ac], XmNallowShellResize, FALSE); ac++;
	XtSetArg(al[ac], XmNtitle, (char *) "Freeway"); ac++;
	XtSetArg(al[ac], XmNargc, app_argc); ac++;
	XtSetArg(al[ac], XmNargv, app_argv); ac++;
	shell = XtAppCreateShell (
				(char *) "Freeway",
				(char *) "XApplication",
				applicationShellWidgetClass,
				display,
				al,
				ac );

	if (DefaultDepthOfScreen(DefaultScreenOfDisplay(display)) != 1) {
		// Get back-ground colors for colored-screene
		XrmValue from_value, to_value;
		from_value.addr = (char *)"LightSteelBlue2";
		from_value.size = strlen( from_value.addr ) + 1;
		to_value.addr = NULL;
		XtConvertAndStore (shell, XmRString, &from_value,
					XmRPixel, &to_value);
		if (to_value.addr) {
			grey = *(unsigned int *)to_value.addr;
		}

		from_value.addr = (char *)"LightSteelBlue3";
		from_value.size = strlen( from_value.addr ) + 1;
		to_value.addr = NULL;
		XtConvertAndStore (shell, XmRString, &from_value,
					XmRPixel, &to_value);
		if (to_value.addr) {
			blue = *(unsigned int *)to_value.addr;
		}
	}

	// Create pop-up windows;
	vinfo_winp = new VinfoWindow();
	file_winp = new FileWindow();
	help_winp = new HelpWindow();
	vinfo_winp->objects_initialize(this);
	file_winp->objects_initialize(this);
	help_winp->objects_initialize(this);

	// Initialize main window widgets
	ac = 0;
	XtSetArg(al[ac], XmNautoUnmanage, FALSE); ac++;
	XtSetArg(al[ac], XmNbackground, grey); ac++;
	topform = XmCreateForm (shell, (char *)"topform", al, ac );

	ac = 0;
	XtSetArg(al[ac], XmNbackground, grey); ac++;
	controlform = XmCreateForm (topform, (char *)"controlform", al, ac );
	control_objects = new FwyControlObjects();
	control_objects->objects_initialize(controlform);

	ac = 0;
	XtSetArg(al[ac], XmNwidth, 600); ac++;
	XtSetArg(al[ac], XmNheight, 170); ac++;
	XtSetArg(al[ac], XmNbackground, blue); ac++;
	drawing = XmCreateDrawingArea( topform, (char *)"drawing", al, ac );

	separator2 = XmCreateSeparator( topform, (char *)"separator2", al, 0 );
	      
	ac = 0;
	xmstring = XmStringCreateLtoR((char *)"Status",
				(XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstring); ac++;
	XtSetArg(al[ac], XmNalignment, XmALIGNMENT_BEGINNING); ac++;
	XtSetArg(al[ac], XmNrecomputeSize, FALSE); ac++;
	XtSetArg(al[ac], XmNbackground, grey); ac++;
	statuslab = XmCreateLabel( topform, (char *)"statuslab", al, ac );
	XmStringFree(xmstring);

	ac = 0;
	xmstring = XmStringCreateLtoR((char *)"Quit",
				(XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstring); ac++;
	XtSetArg(al[ac], XmNbackground, grey); ac++;
	quit = XmCreatePushButton( topform, (char *)"quit", al, ac );
	XmStringFree(xmstring);

	XtVaSetValues(controlform,
			XmNtopAttachment, XmATTACH_FORM,
			XmNleftAttachment, XmATTACH_FORM,
			XmNrightAttachment, XmATTACH_FORM,
			NULL);
	XtVaSetValues(drawing,
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNtopWidget, controlform,
			XmNbottomAttachment, XmATTACH_WIDGET,
			XmNbottomWidget, separator2,
			XmNleftAttachment, XmATTACH_FORM,
			XmNrightAttachment, XmATTACH_FORM,
			NULL);
	XtVaSetValues(separator2,
			XmNtopAttachment, XmATTACH_NONE,
			XmNbottomAttachment, XmATTACH_WIDGET,
			XmNbottomWidget, statuslab,
			XmNleftAttachment, XmATTACH_FORM,
			XmNrightAttachment, XmATTACH_FORM,
			NULL); 
	XtVaSetValues(statuslab,
			XmNtopAttachment, XmATTACH_OPPOSITE_WIDGET,
			XmNtopWidget, quit,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNleftAttachment, XmATTACH_FORM,
			XmNrightAttachment, XmATTACH_WIDGET,
			XmNrightWidget, quit,
			NULL);
	XtVaSetValues(quit,
			XmNtopAttachment, XmATTACH_NONE,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNleftAttachment, XmATTACH_NONE,
			XmNrightAttachment, XmATTACH_FORM,
			NULL);

	XtAddCallback(quit, XmNactivateCallback, fw_quit,NULL);

	XtManageChild(controlform);
	XtManageChild(drawing);
	XtManageChild(separator2);
	XtManageChild(statuslab);
	XtManageChild(quit);
	XtManageChild (topform);
}

void 
FwyControlObjects::objects_initialize(Widget controlform)
{
	Arg al[10];
	int ac = 0;
	XmString xmstring;

	ac = 0;
	XtSetArg(al[ac], XmNbackground, grey); ac++;
	menubar = XmCreateMenuBar( controlform, (char *)"menubar", al, ac );
	menu_objects = new FwyMenuObjects();
	menu_objects->objects_initialize(menubar);

	ac = 0;
	XtSetArg(al[ac], XmNbackground, blue); ac++;
	spform = XmCreateForm(controlform, (char *)"spform", al, ac);
	zone_objects = new FwyZoneObjects();
	zone_objects->objects_initialize(spform);

	ac = 0;
	xmstring = XmStringCreateLtoR((char *)"Gap between vehicles:",
				(XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstring); ac++;
	XtSetArg(al[ac], XmNalignment, XmALIGNMENT_END); ac++;
	XtSetArg(al[ac], XmNbackground, grey); ac++;
	gslid_lab = XmCreateLabel( controlform, (char *)"gslid_lab", al, ac );
	XmStringFree(xmstring);

	ac = 0;
	XtSetArg(al[ac], XmNshowValue, FALSE); ac++;
	XtSetArg(al[ac], XmNminimum, 0); ac++;
	XtSetArg(al[ac], XmNmaximum, 100); ac++;
	XtSetArg(al[ac], XmNvalue, 0); ac++;
	XtSetArg(al[ac], XmNorientation, XmHORIZONTAL); ac++;
	XtSetArg(al[ac], XmNprocessingDirection, XmMAX_ON_RIGHT); ac++;
	XtSetArg(al[ac], XmNscaleMultiple, 1); ac++;
	XtSetArg(al[ac], XmNbackground, grey); ac++;
	gap_slide = XmCreateScale( controlform, (char *)"gap_slide", al, ac );

	ac = 0;
	xmstring = XmStringCreateLtoR((char *)"Time between updates:",
				(XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstring); ac++;
	XtSetArg(al[ac], XmNbackground, grey); ac++;
	tslid_lab = XmCreateLabel( controlform, (char *)"tslid_lab", al, ac );
	XmStringFree(xmstring);

	ac = 0;
	XtSetArg(al[ac], XmNminimum, 0); ac++;
	XtSetArg(al[ac], XmNmaximum, 100); ac++;
	XtSetArg(al[ac], XmNvalue, 0); ac++;
	XtSetArg(al[ac], XmNorientation, XmHORIZONTAL); ac++;
	XtSetArg(al[ac], XmNprocessingDirection, XmMAX_ON_RIGHT); ac++;
	XtSetArg(al[ac], XmNscaleMultiple, 1); ac++;
	XtSetArg(al[ac], XmNbackground, grey); ac++;
	time_slide = XmCreateScale( controlform, (char *)"time_slide", al, ac );

	ac = 0;
	xmstring = XmStringCreateLtoR((char *)"Simulation time:",
				(XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstring); ac++;
	XtSetArg(al[ac], XmNalignment, XmALIGNMENT_END); ac++;
	XtSetArg(al[ac], XmNbackground, grey); ac++;
	time_lab = XmCreateLabel( controlform, (char *)"time_lab", al, ac );
	XmStringFree(xmstring);

	ac = 0;
	xmstring = XmStringCreateLtoR((char *)"0:00:00.0",
				(XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstring); ac++;
	XtSetArg(al[ac], XmNalignment, XmALIGNMENT_END); ac++;
	XtSetArg(al[ac], XmNbackground, grey); ac++;
	time_val = XmCreateLabel( controlform, (char *)"time_val", al, ac );
	XmStringFree(xmstring);

	ac = 0;
	xmstring = XmStringCreateLtoR((char *)"Randomize?",
				(XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstring); ac++;
	XtSetArg(al[ac], XmNalignment, XmALIGNMENT_END); ac++;
	XtSetArg(al[ac], XmNbackground, grey); ac++;
	rand_lab = XmCreateLabel( controlform, (char *)"rand_lab", al, ac );
	XmStringFree(xmstring);

	ac = 0;
	XtSetArg(al[ac], XmNnumColumns, 1); ac++;
	XtSetArg(al[ac], XmNspacing, 0); ac++;
	XtSetArg(al[ac], XmNmarginWidth, 0); ac++;
	XtSetArg(al[ac], XmNmarginHeight, 0); ac++;
	XtSetArg(al[ac], XmNorientation, XmHORIZONTAL); ac++;
	XtSetArg(al[ac], XmNbackground, grey); ac++;
	rantog = XmCreateRadioBox( controlform, (char *)"rantog", al, ac );

	ac = 0;
	xmstring = XmStringCreateLtoR((char *)"No",
				(XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstring); ac++;
	XtSetArg(al[ac], XmNbackground, grey); ac++;
	no_tog = XmCreateToggleButtonGadget( rantog, (char *)"no_tog", al, ac );
	XmStringFree(xmstring);

	ac = 0;
	xmstring = XmStringCreateLtoR((char *)"Yes",
				(XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstring); ac++;
	XtSetArg(al[ac], XmNset, TRUE); ac++;
	XtSetArg(al[ac], XmNbackground, grey); ac++;
	yes_tog = XmCreateToggleButtonGadget( rantog, (char *)"yes_tog", al, ac );
	XmStringFree(xmstring);

	separator = XmCreateSeparator(controlform, (char *)"separator", al, 0);

	XtVaSetValues(menubar,
			XmNtopAttachment, XmATTACH_FORM,
			XmNtopOffset, 1,
			XmNbottomAttachment, XmATTACH_NONE,
			XmNleftAttachment, XmATTACH_FORM,
			XmNrightAttachment, XmATTACH_FORM,
			NULL);
	XtVaSetValues(gslid_lab,
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNtopWidget, menubar,
			XmNbottomAttachment, XmATTACH_NONE,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNleftPosition, 5,
			XmNrightAttachment, XmATTACH_NONE,
			NULL);
	XtVaSetValues(gap_slide,
			XmNtopAttachment, XmATTACH_OPPOSITE_WIDGET,
			XmNtopWidget, gslid_lab,
			XmNbottomAttachment, XmATTACH_OPPOSITE_WIDGET,
			XmNbottomWidget, gslid_lab,
			XmNleftAttachment, XmATTACH_WIDGET,
			XmNleftOffset, 10,
			XmNleftWidget, gslid_lab,
			XmNrightAttachment, XmATTACH_NONE,
			NULL);
	XtVaSetValues(tslid_lab,
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNtopWidget, gslid_lab,
			XmNbottomAttachment, XmATTACH_NONE,
			XmNleftAttachment, XmATTACH_OPPOSITE_WIDGET,
			XmNleftWidget, gslid_lab,
			XmNrightAttachment, XmATTACH_NONE,
			NULL);
	XtVaSetValues(time_slide,
			XmNtopAttachment, XmATTACH_OPPOSITE_WIDGET,
			XmNtopWidget, tslid_lab,
			XmNbottomAttachment, XmATTACH_OPPOSITE_WIDGET,
			XmNbottomWidget, tslid_lab,
			XmNleftAttachment, XmATTACH_WIDGET,
			XmNleftOffset, 10,
			XmNleftWidget, tslid_lab,
			XmNrightAttachment, XmATTACH_NONE,
			NULL);
	XtVaSetValues(time_lab,
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNtopWidget, menubar,
			XmNbottomAttachment, XmATTACH_NONE,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNleftPosition, 60,
			XmNrightAttachment, XmATTACH_NONE,
			NULL);
	XtVaSetValues(time_val,
			XmNtopAttachment, XmATTACH_OPPOSITE_WIDGET,
			XmNtopWidget, time_lab,
			XmNbottomAttachment, XmATTACH_OPPOSITE_WIDGET,
			XmNbottomWidget, time_lab,
			XmNleftAttachment, XmATTACH_WIDGET,
			XmNleftOffset, 10,
			XmNleftWidget, time_lab,
			XmNrightAttachment, XmATTACH_NONE,
			NULL);
	XtVaSetValues(rand_lab,
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNtopWidget, time_lab,
			XmNbottomAttachment, XmATTACH_NONE,
		        XmNleftAttachment, XmATTACH_NONE,
			XmNrightAttachment, XmATTACH_OPPOSITE_WIDGET,
			XmNrightWidget, time_lab,
			NULL);
	XtVaSetValues(rantog,
			XmNtopAttachment, XmATTACH_OPPOSITE_WIDGET,
			XmNtopWidget, rand_lab,
			XmNbottomAttachment, XmATTACH_OPPOSITE_WIDGET,
			XmNbottomWidget, rand_lab,
			XmNleftAttachment, XmATTACH_WIDGET,
			XmNleftOffset, 10,
			XmNleftWidget, rand_lab,
			XmNrightAttachment, XmATTACH_NONE,
			NULL);
	XtVaSetValues(separator,
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNtopWidget, tslid_lab,
			XmNbottomAttachment, XmATTACH_NONE,
			XmNleftAttachment, XmATTACH_FORM,
			XmNrightAttachment, XmATTACH_FORM,
			NULL);
	XtVaSetValues(spform,
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNtopWidget, separator,
			XmNbottomAttachment, XmATTACH_NONE,
			XmNleftAttachment, XmATTACH_FORM,
			XmNrightAttachment, XmATTACH_FORM,
			NULL);

	XtAddCallback(gap_slide, XmNvalueChangedCallback, gap_change,NULL);
	XtAddCallback(time_slide, XmNvalueChangedCallback, time_change,NULL);
	XtAddCallback(no_tog, XmNarmCallback, rand,(void*)NULL);
	XtAddCallback(yes_tog, XmNarmCallback, rand,(void*)1);

	XtManageChild(no_tog);
	XtManageChild(yes_tog);
	XtManageChild(menubar);
	XtManageChild(gslid_lab);
	XtManageChild(gap_slide);
	XtManageChild(tslid_lab);
	XtManageChild(time_slide);
	XtManageChild(time_lab);
	XtManageChild(time_val);
	XtManageChild(rand_lab);
	XtManageChild(rantog);
	XtManageChild(separator);
	XtManageChild(spform);
}

void
FwyMenuObjects::objects_initialize (Widget menubar)
{
	Arg al[10];
	int ac = 0;
	XmString xmstring;
	XrmValue from_value, to_value; /* For resource conversion */

	ac = 0;
	xmstring = XmStringCreateLtoR( (char *)"File",
				(XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstring); ac++;
	from_value.addr = (char *)"F";
	from_value.size = strlen( from_value.addr ) + 1;
	to_value.addr = NULL;
	XtConvertAndStore (menubar, XmRString, &from_value,
				XmRKeySym, &to_value);
	if( to_value.addr ) {
		XtSetArg(al[ac], XmNmnemonic, *(unsigned int *)to_value.addr);
		ac++;
	}
	XtSetArg(al[ac], XmNbackground, grey); ac++;
	file_menu = XmCreateCascadeButton( menubar, (char *)"file_menu", al, ac );
	XmStringFree(xmstring);

	filemen = XmCreatePulldownMenu( menubar, (char *)"filemen", al, 0);

	ac = 0;
	xmstring = XmStringCreateLtoR((char *)"Load...",
				(XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstring); ac++;
	XtSetArg(al[ac], XmNbackground, grey); ac++;
	loadbut = XmCreatePushButton( filemen, (char *)"loadbut", al, ac );
	XmStringFree(xmstring);

	ac = 0;
	xmstring = XmStringCreateLtoR((char *)"Save",
				(XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstring); ac++;
	XtSetArg(al[ac], XmNbackground, grey); ac++;
	save = XmCreatePushButton( filemen, (char *)"save", al, ac );
	XmStringFree(xmstring);

	ac = 0;
	xmstring = XmStringCreateLtoR((char *)"Save As...",
				(XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstring); ac++;
	XtSetArg(al[ac], XmNbackground, grey); ac++;
	saveas = XmCreatePushButton( filemen, (char *)"saveas", al, ac );
	XmStringFree(xmstring);

	ac = 0;
	xmstring = XmStringCreateLtoR((char *)"Close File",
				(XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstring); ac++;
	XtSetArg(al[ac], XmNbackground, grey); ac++;
	closefile = XmCreatePushButton( filemen, (char *)"closefile", al, ac );
	XmStringFree(xmstring);

	ac = 0;
	xmstring = XmStringCreateLtoR((char *)"Start",
				(XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstring); ac++;
	XtSetArg(al[ac], XmNbackground, grey); ac++;
	start = XmCreateCascadeButton( menubar, (char *)"start", al, ac );
	XmStringFree(xmstring);

	ac = 0;
	xmstring = XmStringCreateLtoR((char *)"Stop",
				(XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstring); ac++;
	XtSetArg(al[ac], XmNbackground, grey); ac++;
	stop = XmCreateCascadeButton( menubar, (char *)"stop", al, ac );
	XmStringFree(xmstring);

	ac = 0;
	xmstring = XmStringCreateLtoR((char *)"Reset",
				(XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstring); ac++;
	from_value.addr = (char *)"R";
	from_value.size = strlen( from_value.addr ) + 1;
	to_value.addr = NULL;
	XtConvertAndStore(menubar, XmRString, &from_value, XmRKeySym, &to_value);
	if (to_value.addr) {
		XtSetArg(al[ac], XmNmnemonic, *(unsigned int *)to_value.addr);
		ac++;
	}
	XtSetArg(al[ac], XmNbackground, grey); ac++;
	reset_men = XmCreateCascadeButton( menubar, (char *)"reset_men", al, ac );
	XmStringFree(xmstring);

	resetmen = XmCreatePulldownMenu(menubar, (char *)"resetmen", al, 0);

	ac = 0;
	xmstring = XmStringCreateLtoR((char *)"Clear Wrecks",
				(XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstring); ac++;
	XtSetArg(al[ac], XmNbackground, grey); ac++;
	clearwrckbut = XmCreatePushButton(resetmen, (char *)"clearwrckbut", al, ac );
	XmStringFree(xmstring);

	ac = 0;
	xmstring = XmStringCreateLtoR((char *)"Reset",
				(XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstring); ac++;
	XtSetArg(al[ac], XmNbackground, grey); ac++;
	resetbut = XmCreatePushButton( resetmen, (char *)"resetbut", al, ac );
	XmStringFree(xmstring);

	ac = 0;
	xmstring = XmStringCreateLtoR((char *)"Help",
				(XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstring); ac++;
	from_value.addr = (char *)"H";
	from_value.size = strlen( from_value.addr ) + 1;
	to_value.addr = NULL;
	XtConvertAndStore(menubar, XmRString, &from_value, XmRKeySym, &to_value);
	if (to_value.addr) {
		XtSetArg(al[ac], XmNmnemonic, *(unsigned int *)to_value.addr);
		ac++;
	}
	XtSetArg(al[ac], XmNbackground, grey); ac++;
	help_men = XmCreateCascadeButton( menubar, (char *)"help_men", al, ac );
	XmStringFree(xmstring);

	ac = 0;
	XtSetArg(al[ac], XmNbackground, grey); ac++;
	helpmen= XmCreatePulldownMenu (menubar, (char *)"helpmen", al, ac);

	ac = 0;
	xmstring = XmStringCreateLtoR((char *)"About...",
				(XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstring); ac++;
	XtSetArg(al[ac], XmNbackground, grey); ac++;
	about = XmCreatePushButton( helpmen, (char *)"about", al, ac );
	XmStringFree(xmstring);

	XtVaSetValues(menubar, XmNmenuHelpWidget, help_men, NULL);
	XtVaSetValues(file_menu, XmNsubMenuId, filemen, NULL);
	XtVaSetValues(reset_men, XmNsubMenuId, resetmen, NULL);
	XtVaSetValues(help_men, XmNsubMenuId, helpmen, NULL);

	XtAddCallback(loadbut, XmNactivateCallback, file_load,NULL);
	XtAddCallback(save, XmNactivateCallback, file_save,NULL);
	XtAddCallback(saveas, XmNactivateCallback, file_saveas,NULL);
	XtAddCallback(closefile, XmNactivateCallback, file_close,NULL);
	XtAddCallback(start, XmNactivateCallback, fwy_start,NULL);
	XtAddCallback(stop, XmNactivateCallback, fwy_stop,NULL);
	XtAddCallback(clearwrckbut, XmNactivateCallback, reset_clear,NULL);
	XtAddCallback(resetbut, XmNactivateCallback, reset_reset,NULL);
	XtAddCallback(about, XmNactivateCallback, help_about,NULL);

	XtManageChild(loadbut);
	XtManageChild(save);
	XtManageChild(saveas);
	XtManageChild(closefile);
	XtManageChild(clearwrckbut);
	XtManageChild(resetbut);
	XtManageChild(about);
	XtManageChild(file_menu);
	XtManageChild(start);
	XtManageChild(stop);
	XtManageChild(reset_men);
	XtManageChild(help_men);
}

void
FwyZoneObjects::objects_initialize (Widget spform)
{
	Arg al[64];
	int ac = 0;
	XmString xmstring;
	char name[50];
	int jx, ix;


	for (ix = 0; ix < NZONES; ix++) {
		ac = 0;
		sprintf(name, "spop%d", ix);
		XtSetArg(al[ac], XmNbackground, blue); ac++;
		z[ix].spop = XmCreateOptionMenu(spform, name, al, ac);
		z[ix].splab = XmOptionLabelGadget( z[ix].spop );
		z[ix].spcas = XmOptionButtonGadget( z[ix].spop );
	
		ac = 0;
		sprintf(name, "spmen%d", ix);
		XtSetArg(al[ac], XmNorientation, XmHORIZONTAL); ac++;
		XtSetArg(al[ac], XmNbackground, grey); ac++;
		z[ix].spmen = XmCreatePulldownMenu( z[ix].spop, name, al, ac );
	
		for (jx = 0; jx < NSPEEDS; jx++) {
			ac = 0;
			sprintf(name, "sp%s_%d", SPEED_STR[jx], ix);
			xmstring = XmStringCreateLtoR( (char *)SPEED_STR[jx], 
					(XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
			XtSetArg(al[ac], XmNlabelString, xmstring); ac++;
			XtSetArg(al[ac], XmNbackground, grey); ac++;
			z[ix].sp[jx] = XmCreatePushButton( z[ix].spmen, name, al, ac );
			XmStringFree(xmstring);

			XtAddCallback(z[ix].sp[jx], XmNactivateCallback,
					zone_speed, (XtPointer)(ix + 1));
		}
	
		ac = 0;
		sprintf(name, "spzonel%d", ix);
		xmstring = XmStringCreateLtoR((char *)" ", 
					(XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
		XtSetArg(al[ac], XmNlabelString, xmstring); ac++;
		XtSetArg(al[ac], XmNbackground, blue); ac++;
		z[ix].spzonel = XmCreateLabel( spform, name, al, ac );
		sprintf(name, "spzoneu%d", ix);
		XtSetArg(al[ac], XmNbackground, blue); ac++;
		z[ix].spzoneu = XmCreateLabel( spform, name, al, ac );
		XmStringFree(xmstring);
	
		XtVaSetValues(z[ix].spop,
				XmNtopAttachment, XmATTACH_NONE,
				XmNbottomAttachment, XmATTACH_FORM,
				XmNleftAttachment, XmATTACH_POSITION,
				XmNleftPosition, ix * (int)(100/NZONES + 1),
				XmNrightAttachment, XmATTACH_NONE,
				NULL);
		XtVaSetValues(z[ix].spzonel,
				XmNtopAttachment, XmATTACH_NONE,
				XmNbottomAttachment, XmATTACH_FORM,
				XmNleftAttachment, XmATTACH_WIDGET,
				XmNleftOffset, 20,
				XmNleftWidget, z[ix].spop,
				XmNrightAttachment, XmATTACH_NONE,
				NULL);
		XtVaSetValues(z[ix].spzoneu,
				XmNtopAttachment, XmATTACH_FORM,
				XmNbottomAttachment, XmATTACH_WIDGET,
				XmNbottomWidget, z[ix].spzonel,
				XmNleftAttachment, XmATTACH_OPPOSITE_WIDGET,
				XmNleftWidget, z[ix].spzonel,
				XmNrightAttachment, XmATTACH_NONE,
				NULL);
	
		XtVaSetValues (z[ix].spcas, XmNsubMenuId, z[ix].spmen, NULL);
	
		for (jx = 0; jx < NSPEEDS; jx++) {
			XtManageChild(z[ix].sp[jx]);
		}

		XtManageChild(z[ix].spop);
		XtManageChild(z[ix].spzonel);
		XtManageChild(z[ix].spzoneu);
	}
}

void
FileWindow::objects_initialize(FreewayWindow *awp)
{
	Arg al[10];
	int ac = 0;
	Widget aw= 0, bw = 0, cw = 0;

	app_winp = awp;

	ac = 0;
	XtSetArg(al[ac], XmNbackground, grey); ac++;
	fibox = XmCreateFileSelectionDialog(
			app_winp->shell,
			(char *)"fibox", al, ac);

	shell = XtParent(fibox);
	XtVaSetValues(shell,
			XmNmappedWhenManaged, FALSE,
			XmNdeleteResponse, XmDESTROY,
			XmNbackground, grey,
			NULL);
	XtAddCallback (shell, XmNdestroyCallback, popup_destroyed, NULL);

	aw= XmFileSelectionBoxGetChild(fibox, XmDIALOG_HELP_BUTTON);
	XtUnmanageChild(aw);

	aw= XmFileSelectionBoxGetChild(fibox, XmDIALOG_FILTER_TEXT);
	XtVaSetValues(aw, XmNbackground, WHITE, NULL);

	aw= XmFileSelectionBoxGetChild(fibox, XmDIALOG_LIST);
	XtVaSetValues(aw, XmNbackground, WHITE, NULL);
	aw = XtParent(aw);
	bw= XtNameToWidget(aw, "HorScrollBar");
	cw= XtNameToWidget(aw, "VertScrollBar");
	XtVaSetValues(aw, XmNbackground, grey, NULL);
	XtVaSetValues(bw, XmNbackground, grey, NULL);
	XtVaSetValues(cw, XmNbackground, grey, NULL);

	aw= XmFileSelectionBoxGetChild(fibox, XmDIALOG_DIR_LIST);
	XtVaSetValues(aw, XmNbackground, WHITE, NULL);
	aw = XtParent(aw);
	bw= XtNameToWidget(aw, "HorScrollBar");
	cw= XtNameToWidget(aw, "VertScrollBar");
	XtVaSetValues(aw, XmNbackground, grey, NULL);
	XtVaSetValues(bw, XmNbackground, grey, NULL);
	XtVaSetValues(cw, XmNbackground, grey, NULL);

	aw= XmFileSelectionBoxGetChild(fibox, XmDIALOG_TEXT);
	XtVaSetValues(aw, XmNbackground, WHITE, NULL);

	XtAddCallback(fibox, XmNcancelCallback, fi_cancel,NULL);
	XtAddCallback(fibox, XmNokCallback, fi_ok,NULL);

	XtManageChild(fibox);
}


void
VinfoWindow::objects_initialize(FreewayWindow *awp)
{
	Arg al[10];
	int ac = 0;
	XmString xmstring;

	app_winp = awp;

	XtSetArg(al[ac], XmNmappedWhenManaged, FALSE); ac++;
	XtSetArg(al[ac], XmNallowShellResize, TRUE); ac++;
	XtSetArg(al[ac], XmNtitle, (char *)"Vehicle Information"); ac++;
	XtSetArg(al[ac], XmNdeleteResponse, XmDESTROY); ac++;
	XtSetArg(al[ac], XmNbackground, grey); ac++;
	shell = XmCreateDialogShell(awp->shell, (char *)"vinfo_shell", al,ac );
	XtAddCallback (shell, XmNdestroyCallback, popup_destroyed, NULL);

	ac = 0;
	XtSetArg(al[ac], XmNautoUnmanage, FALSE); ac++;
	XtSetArg(al[ac], XmNbackground, grey); ac++;
	topform = XmCreateForm( shell, (char *)"topform", al, ac );

	ac = 0;
	XtSetArg(al[ac], XmNbackground, blue); ac++;
	drawing = XmCreateDrawingArea(topform, (char *)"drawing", al, ac);
	ac = 0;
	XtSetArg(al[ac], XmNbackground, grey); ac++;
	controlform = XmCreateForm(topform,(char *)"controlform",al,ac);
	control_objects = new VinfoControlObjects();
	control_objects->objects_initialize(controlform);


	XtVaSetValues(drawing,
			XmNtopAttachment, XmATTACH_FORM,
			XmNbottomAttachment, XmATTACH_WIDGET,
			XmNbottomWidget, controlform,
			XmNleftAttachment, XmATTACH_FORM,
			XmNrightAttachment, XmATTACH_FORM,
			NULL);
	XtVaSetValues(controlform,
			XmNtopAttachment, XmATTACH_NONE,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNleftAttachment, XmATTACH_FORM,
			XmNrightAttachment, XmATTACH_FORM,
			NULL);

	XtManageChild(drawing);
	XtManageChild(controlform);
}

void
VinfoControlObjects::objects_initialize (Widget controlform)
{
	Arg al[10];
	int ac = 0;
	XmString xmstring;

	ac = 0;
	xmstring = XmStringCreateLtoR((char *)"Vehicle", 
				(XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstring); ac++;
	XtSetArg(al[ac], XmNbackground, grey); ac++;
	vlab = XmCreateLabel( controlform, (char *)"vlab", al, ac );
	XmStringFree(xmstring);

	ac = 0;
	xmstring = XmStringCreateLtoR((char *)"2", 
				(XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstring); ac++;
	XtSetArg(al[ac], XmNbackground, grey); ac++;
	vval = XmCreateLabel( controlform, (char *)"vval", al, ac );

	ac = 0;
	XmStringFree(xmstring);
	xmstring = XmStringCreateLtoR((char *)"Class: ", 
				(XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstring); ac++;
	XtSetArg(al[ac], XmNmarginTop, 5); ac++;
	XtSetArg(al[ac], XmNmarginBottom, 5); ac++;
	XtSetArg(al[ac], XmNbackground, grey); ac++;
	clab = XmCreateLabel( controlform, (char *)"clab", al, ac );
	XmStringFree(xmstring);

	ac = 0;
	XtSetArg(al[ac], XmNbackground, grey); ac++;
	cop = XmCreateOptionMenu( controlform, (char *)"cop", al, ac );
	coplab = XmOptionLabelGadget( cop );
	Widget copbutton = XmOptionButtonGadget( cop );
	ac = 0;
	XtSetArg(al[ac], XmNbackground, grey); ac++;
	Widget copmenu = XmCreatePulldownMenu( cop, (char *)"copmenu", al,ac );
	xmstring = XmStringCreateLtoR((char *)"Sedan", 
				(XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstring); ac++;
	XtSetArg(al[ac], XmNbackground, grey); ac++;
	copsed = XmCreatePushButton( copmenu, (char *)"copsed", al, ac );
	XmStringFree(xmstring);

	ac = 0;
	xmstring = XmStringCreateLtoR((char *)"Truck", 
				(XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstring); ac++;
	XtSetArg(al[ac], XmNbackground, grey); ac++;
	coptruc = XmCreatePushButton( copmenu, (char *)"coptruc", al, ac );

	ac = 0;
	XmStringFree(xmstring);
	xmstring = XmStringCreateLtoR((char *)"Sports Car", 
				(XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstring); ac++;
	XtSetArg(al[ac], XmNbackground, grey); ac++;
	copsport = XmCreatePushButton( copmenu, (char *)"copsport", al, ac );
	XmStringFree(xmstring);

	ac = 0;
	xmstring = XmStringCreateLtoR((char *)"Maniac", 
				(XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstring); ac++;
	XtSetArg(al[ac], XmNbackground, grey); ac++;
	copmaniac = XmCreatePushButton( copmenu, (char *)"copmaniac", al, ac );
	XmStringFree(xmstring);

	ac = 0;
	xmstring = XmStringCreateLtoR((char *)"Police", 
				(XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstring); ac++;
	XtSetArg(al[ac], XmNbackground, grey); ac++;
	coppoice = XmCreatePushButton( copmenu, (char *)"coppoice", al, ac );
	XmStringFree(xmstring);

	ac = 0;
	xmstring = XmStringCreateLtoR((char *)"State: ", 
				(XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstring); ac++;
	XtSetArg(al[ac], XmNmarginTop, 5); ac++;
	XtSetArg(al[ac], XmNmarginBottom, 5); ac++;
	XtSetArg(al[ac], XmNbackground, grey); ac++;
	slab = XmCreateLabel( controlform, (char *)"slab", al, ac );
	XmStringFree(xmstring);

	ac = 0;
	sop = XmCreateOptionMenu( controlform, (char *)"sop", al, ac );
	Widget sopbutton = XmOptionButtonGadget( sop );
	Widget sopmenu = XmCreatePulldownMenu( sop, (char *)"sopmenu", al,ac );
	xmstring = XmStringCreateLtoR((char *)"Maintain", 
				(XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstring); ac++;
	XtSetArg(al[ac], XmNbackground, grey); ac++;
	sopmain = XmCreatePushButton( sopmenu, (char *)"sopmain", al, ac );

	ac = 0;
	XmStringFree(xmstring);
	xmstring = XmStringCreateLtoR((char *)"Accelerate", 
				(XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstring); ac++;
	XtSetArg(al[ac], XmNbackground, grey); ac++;
	sopacc = XmCreatePushButton( sopmenu, (char *)"sopacc", al, ac );
	XmStringFree(xmstring);

	ac = 0;
	xmstring = XmStringCreateLtoR((char *)"Coaste", 
				(XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstring); ac++;
	XtSetArg(al[ac], XmNbackground, grey); ac++;
	sopcoast = XmCreatePushButton( sopmenu, (char *)"sopcoast", al, ac );
	XmStringFree(xmstring);

	ac = 0;
	xmstring = XmStringCreateLtoR((char *)"Brake", 
				(XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstring); ac++;
	XtSetArg(al[ac], XmNbackground, grey); ac++;
	sopbrake = XmCreatePushButton( sopmenu, (char *)"sopbrake", al, ac );

	ac = 0;
	XmStringFree(xmstring);
	xmstring = XmStringCreateLtoR((char *)"Crash", 
				(XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstring); ac++;
	XtSetArg(al[ac], XmNbackground, grey); ac++;
	sopcrash = XmCreatePushButton( sopmenu, (char *)"sopcrash", al, ac );
	XmStringFree(xmstring);

	ac = 0;
	xmstring = XmStringCreateLtoR((char *)"Max Speed", 
				(XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstring); ac++;
	XtSetArg(al[ac], XmNbackground, grey); ac++;
	sopmax = XmCreatePushButton( sopmenu, (char *)"sopmax", al, ac );

	ac = 0;
	XmStringFree(xmstring);
	xmstring = XmStringCreateLtoR((char *)"Lane Change", 
				(XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstring); ac++;
	XtSetArg(al[ac], XmNbackground, grey); ac++;
	sopchange = XmCreatePushButton( sopmenu, (char *)"sopchange", al, ac );
	XmStringFree(xmstring);

	ac = 0;
	xmstring = XmStringCreateLtoR((char *)"Speed (in mph): ", 
				(XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstring); ac++;
	XtSetArg(al[ac], XmNmarginTop, 2); ac++;
	XtSetArg(al[ac], XmNmarginBottom, 2); ac++;
	XtSetArg(al[ac], XmNbackground, grey); ac++;
	splab = XmCreateLabel( controlform, (char *)"splab", al, ac );
	XmStringFree(xmstring);

	ac = 0;
	xmstring = XmStringCreateLtoR((char *)"55", 
				(XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstring); ac++;
	XtSetArg(al[ac], XmNmarginTop, 2); ac++;
	XtSetArg(al[ac], XmNmarginBottom, 2); ac++;
	XtSetArg(al[ac], XmNbackground, grey); ac++;
	spval = XmCreateLabel( controlform, (char *)"spval", al, ac );
	XmStringFree(xmstring);

	ac = 0;
	spup = XmCreateArrowButton( controlform, (char *)"spup", al, ac );
	XtSetArg(al[ac], XmNarrowDirection, XmARROW_DOWN); ac++;
	XtSetArg(al[ac], XmNbackground, grey); ac++;
	spdown = XmCreateArrowButton( controlform, (char *)"spdown", al, ac );

	ac = 0;
	xmstring = XmStringCreateLtoR((char *)"Maximum speed: ", 
				(XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstring); ac++;
	XtSetArg(al[ac], XmNmarginTop, 2); ac++;
	XtSetArg(al[ac], XmNmarginBottom, 2); ac++;
	XtSetArg(al[ac], XmNbackground, grey); ac++;
	maxlab = XmCreateLabel( controlform, (char *)"maxlab", al, ac );
	XmStringFree(xmstring);

	ac = 0;
	xmstring = XmStringCreateLtoR((char *)"100", 
				(XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstring); ac++;
	XtSetArg(al[ac], XmNmarginTop, 2); ac++;
	XtSetArg(al[ac], XmNmarginBottom, 2); ac++;
	XtSetArg(al[ac], XmNbackground, grey); ac++;
	maxval = XmCreateLabel( controlform, (char *)"maxval", al, ac );
	XmStringFree(xmstring);

	ac = 0;
	XtSetArg(al[ac], XmNbackground, grey); ac++;
	maxup = XmCreateArrowButton( controlform, (char *)"maxup", al, ac );
	ac = 0;
	XtSetArg(al[ac], XmNarrowDirection, XmARROW_DOWN); ac++;
	XtSetArg(al[ac], XmNbackground, grey); ac++;
	maxdown = XmCreateArrowButton( controlform, (char *)"maxdown", al,ac );

	ac = 0;
	xmstring = XmStringCreateLtoR((char *)"Position (feet): ", 
				(XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstring); ac++;
	XtSetArg(al[ac], XmNbackground, grey); ac++;
	poslab = XmCreateLabel( controlform, (char *)"poslab", al, ac );
	XmStringFree(xmstring);

	ac = 0;
	xmstring = XmStringCreateLtoR((char *)"564", 
				(XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstring); ac++;
	XtSetArg(al[ac], XmNbackground, grey); ac++;
	posval = XmCreateLabel( controlform, (char *)"posval", al, ac );
	XmStringFree(xmstring);

	ac = 0;
	xmstring = XmStringCreateLtoR((char *)"... gap in front: ", 
				(XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstring); ac++;
	XtSetArg(al[ac], XmNbackground, grey); ac++;
	fglab = XmCreateLabel( controlform, (char *)"fglab", al, ac );
	XmStringFree(xmstring);

	ac = 0;
	xmstring = XmStringCreateLtoR((char *)"156", 
				(XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstring); ac++;
	XtSetArg(al[ac], XmNbackground, grey); ac++;
	fgval = XmCreateLabel( controlform, (char *)"fgval", al, ac );
	XmStringFree(xmstring);

	ac = 0;
	xmstring = XmStringCreateLtoR((char *)"... gap in back: ", 
				(XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstring); ac++;
	XtSetArg(al[ac], XmNbackground, grey); ac++;
	bglab = XmCreateLabel( controlform, (char *)"bglab", al, ac );
	XmStringFree(xmstring);

	ac = 0;
	xmstring = XmStringCreateLtoR((char *)"166", 
				(XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstring); ac++;
	XtSetArg(al[ac], XmNbackground, grey); ac++;
	bgval = XmCreateLabel( controlform, (char *)"bgval", al, ac );
	XmStringFree(xmstring);

	ac = 0;
	xmstring = XmStringCreateLtoR((char *)"Step", 
				(XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstring); ac++;
	XtSetArg(al[ac], XmNbackground, grey); ac++;
	stepbut = XmCreatePushButton( controlform, (char *)"stepbut", al, ac );
	XmStringFree(xmstring);

	ac = 0;
	xmstring = XmStringCreateLtoR((char *)"Remove Vehicle", 
				(XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstring); ac++;
	XtSetArg(al[ac], XmNbackground, grey); ac++;
	rembut = XmCreatePushButton( controlform, (char *)"rembut", al, ac );
	XmStringFree(xmstring);

	ac = 0;
	xmstring = XmStringCreateLtoR((char *)"Close", 
				(XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstring); ac++;
	XtSetArg(al[ac], XmNbackground, grey); ac++;
	closebut = XmCreatePushButton( controlform, (char *)"closebut",al,ac );
	XmStringFree(xmstring);

	XtVaSetValues(vlab,
			XmNtopAttachment, XmATTACH_FORM,
			XmNbottomAttachment, XmATTACH_NONE,
			XmNleftAttachment, XmATTACH_FORM,
			XmNleftOffset, 50,
			NULL);
	XtVaSetValues(vval,
			XmNtopAttachment, XmATTACH_OPPOSITE_WIDGET,
			XmNtopWidget, vlab,
			XmNbottomAttachment, XmATTACH_NONE,
			XmNleftAttachment, XmATTACH_WIDGET,
			XmNleftWidget, vlab,
			XmNrightAttachment, XmATTACH_NONE,
			NULL);
	XtVaSetValues(clab,
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNtopOffset, 10,
			XmNtopWidget, vlab,
			XmNbottomAttachment, XmATTACH_NONE,
			XmNleftAttachment, XmATTACH_OPPOSITE_WIDGET,
			XmNleftWidget, vlab,
			XmNrightAttachment, XmATTACH_NONE,
			NULL);
	XtVaSetValues(cop,
			XmNtopAttachment, XmATTACH_OPPOSITE_WIDGET,
			XmNtopWidget, clab,
			XmNbottomAttachment, XmATTACH_NONE,
			XmNleftAttachment, XmATTACH_WIDGET,
			XmNleftWidget, clab,
			XmNrightAttachment, XmATTACH_NONE,
			NULL);
	XtVaSetValues(slab,
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNtopOffset, 10,
			XmNtopWidget, clab,
			XmNbottomAttachment, XmATTACH_NONE,
			XmNleftAttachment, XmATTACH_OPPOSITE_WIDGET,
			XmNleftWidget, clab,
			XmNrightAttachment, XmATTACH_NONE,
			NULL);
	XtVaSetValues(sop,
			XmNtopAttachment, XmATTACH_OPPOSITE_WIDGET,
			XmNtopWidget, slab,
			XmNbottomAttachment, XmATTACH_NONE,
			XmNleftAttachment, XmATTACH_WIDGET,
			XmNleftWidget, slab,
			XmNrightAttachment, XmATTACH_NONE,
			NULL);
	XtVaSetValues(splab,
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNtopOffset, 20,
			XmNtopWidget, slab,
			XmNbottomAttachment, XmATTACH_NONE,
			XmNleftAttachment, XmATTACH_OPPOSITE_WIDGET,
			XmNleftWidget, slab,
			XmNrightAttachment, XmATTACH_NONE,
			NULL);
	XtVaSetValues(spval,
			XmNtopAttachment, XmATTACH_OPPOSITE_WIDGET,
			XmNtopWidget, splab,
			XmNbottomAttachment, XmATTACH_NONE,
			XmNleftAttachment, XmATTACH_WIDGET,
			XmNleftWidget, splab,
			XmNrightAttachment, XmATTACH_NONE,
			NULL);
	XtVaSetValues(spup,
			XmNtopAttachment, XmATTACH_OPPOSITE_WIDGET,
			XmNtopWidget, splab,
			XmNbottomAttachment, XmATTACH_NONE,
			XmNleftAttachment, XmATTACH_WIDGET,
			XmNleftWidget, spval,
			XmNrightAttachment, XmATTACH_NONE,
			NULL);
	XtVaSetValues(spdown,
			XmNtopAttachment, XmATTACH_OPPOSITE_WIDGET,
			XmNtopWidget, splab,
			XmNbottomAttachment, XmATTACH_NONE,
			XmNleftAttachment, XmATTACH_WIDGET,
			XmNleftWidget, spup,
			XmNrightAttachment, XmATTACH_NONE,
			NULL);
	XtVaSetValues(maxlab,
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNtopOffset, 10,
			XmNtopWidget, splab,
			XmNbottomAttachment, XmATTACH_NONE,
			XmNleftAttachment, XmATTACH_OPPOSITE_WIDGET,
			XmNleftWidget, splab,
			XmNrightAttachment, XmATTACH_NONE,
			NULL);
	XtVaSetValues(maxval,
			XmNtopAttachment, XmATTACH_OPPOSITE_WIDGET,
			XmNtopWidget, maxlab,
			XmNbottomAttachment, XmATTACH_NONE,
			XmNleftAttachment, XmATTACH_WIDGET,
			XmNleftWidget, maxlab,
			XmNrightAttachment, XmATTACH_NONE,
			NULL);
	XtVaSetValues(maxup,
			XmNtopAttachment, XmATTACH_OPPOSITE_WIDGET,
			XmNtopWidget, maxlab,
			XmNbottomAttachment, XmATTACH_NONE,
			XmNleftAttachment, XmATTACH_WIDGET,
			XmNleftWidget, maxval,
			XmNrightAttachment, XmATTACH_NONE,
			NULL);
	XtVaSetValues(maxdown,
			XmNtopAttachment, XmATTACH_OPPOSITE_WIDGET,
			XmNtopWidget, maxlab,
			XmNbottomAttachment, XmATTACH_NONE,
			XmNleftAttachment, XmATTACH_WIDGET,
			XmNleftWidget, maxup,
			XmNrightAttachment, XmATTACH_NONE,
			NULL);
	XtVaSetValues(poslab,
			XmNtopAttachment, XmATTACH_OPPOSITE_WIDGET,
			XmNtopWidget, cop,
			XmNbottomAttachment, XmATTACH_NONE,
			XmNleftAttachment, XmATTACH_WIDGET,
			XmNleftOffset, 50,
			XmNleftWidget, cop,
			XmNrightAttachment, XmATTACH_NONE,
			NULL);
	XtVaSetValues(posval,
			XmNtopAttachment, XmATTACH_OPPOSITE_WIDGET,
			XmNtopWidget, poslab,
			XmNbottomAttachment, XmATTACH_NONE,
			XmNleftAttachment, XmATTACH_WIDGET,
			XmNleftWidget, poslab,
			XmNrightAttachment, XmATTACH_NONE,
			NULL);
	XtVaSetValues(fglab,
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNtopOffset, 10,
			XmNtopWidget, poslab,
			XmNbottomAttachment, XmATTACH_NONE,
			XmNleftAttachment, XmATTACH_OPPOSITE_WIDGET,
			XmNleftWidget, poslab,
			XmNrightAttachment, XmATTACH_NONE,
			NULL);
	XtVaSetValues(fgval,
			XmNtopAttachment, XmATTACH_OPPOSITE_WIDGET,
			XmNtopWidget, fglab,
			XmNbottomAttachment, XmATTACH_NONE,
			XmNleftAttachment, XmATTACH_WIDGET,
			XmNleftWidget, fglab,
			XmNrightAttachment, XmATTACH_NONE,
			NULL);
	XtVaSetValues(bglab,
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNtopOffset, 10,
			XmNtopWidget, fglab,
			XmNbottomAttachment, XmATTACH_NONE,
			XmNleftAttachment, XmATTACH_OPPOSITE_WIDGET,
			XmNleftWidget, fglab,
			XmNrightAttachment, XmATTACH_NONE,
			NULL);
	XtVaSetValues(bgval,
			XmNtopAttachment, XmATTACH_OPPOSITE_WIDGET,
			XmNtopWidget, bglab,
			XmNbottomAttachment, XmATTACH_NONE,
			XmNleftAttachment, XmATTACH_WIDGET,
			XmNleftWidget, bglab,
			XmNrightAttachment, XmATTACH_NONE,
			NULL);
	XtVaSetValues(stepbut,
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNtopOffset, 10,
			XmNtopWidget, bglab,
			XmNbottomAttachment, XmATTACH_NONE,
			XmNleftAttachment, XmATTACH_OPPOSITE_WIDGET,
			XmNleftWidget, bglab,
			XmNrightAttachment, XmATTACH_NONE,
			NULL);
	XtVaSetValues(rembut,
			XmNtopAttachment, XmATTACH_OPPOSITE_WIDGET,
			XmNtopWidget, stepbut,
			XmNbottomAttachment, XmATTACH_NONE,
			XmNleftAttachment, XmATTACH_WIDGET,
			XmNleftOffset, 10,
			XmNleftWidget, stepbut,
			XmNrightAttachment, XmATTACH_FORM,
			XmNrightOffset, 50,
			NULL);
	XtVaSetValues(closebut,
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNtopOffset, 10,
			XmNtopWidget, rembut,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNleftAttachment, XmATTACH_NONE,
			XmNrightAttachment, XmATTACH_FORM,
			NULL);

	XtVaSetValues(copbutton, XmNsubMenuId, copmenu, NULL);
	XtVaSetValues(sopbutton, XmNsubMenuId, sopmenu, NULL);

	XtAddCallback(copmenu,
			XmNtearOffMenuActivateCallback, vi_class_select,NULL);
	XtAddCallback(sopmenu,
			XmNtearOffMenuActivateCallback, vi_state_select,NULL);
	XtAddCallback(spup, XmNactivateCallback, vi_speed_up,NULL);
	XtAddCallback(spdown, XmNactivateCallback, vi_speed_down,NULL);
	XtAddCallback(maxup, XmNactivateCallback, vi_max_up,NULL);
	XtAddCallback(maxdown, XmNactivateCallback, vi_max_down,NULL);
	XtAddCallback(stepbut, XmNactivateCallback, vi_step,NULL);
	XtAddCallback(rembut, XmNactivateCallback, vi_remove_vehicle,NULL);
	XtAddCallback(closebut, XmNactivateCallback, vi_close,NULL);

	XtManageChild(copsed);
	XtManageChild(coptruc);
	XtManageChild(copsport);
	XtManageChild(copmaniac);
	XtManageChild(coppoice);
	XtManageChild(sopacc);
	XtManageChild(sopcoast);
	XtManageChild(sopbrake);
	XtManageChild(sopcrash);
	XtManageChild(sopmax);
	XtManageChild(sopchange);
	XtManageChild(sopmain);
	XtManageChild(vlab);
	XtManageChild(vval);
	XtManageChild(clab);
	XtManageChild(cop);
	XtManageChild(slab);
	XtManageChild(sop);
	XtManageChild(splab);
	XtManageChild(spval);
	XtManageChild(spup);
	XtManageChild(spdown);
	XtManageChild(maxlab);
	XtManageChild(maxval);
	XtManageChild(maxup);
	XtManageChild(maxdown);
	XtManageChild(poslab);
	XtManageChild(posval);
	XtManageChild(fglab);
	XtManageChild(fgval);
	XtManageChild(bglab);
	XtManageChild(bgval);
	XtManageChild(stepbut);
	XtManageChild(rembut);
	XtManageChild(closebut);

}

void
HelpWindow::objects_initialize (FreewayWindow *awp)
{
	Arg al[10];
	int ac = 0;
	XmString xmstring;

	app_winp = awp;

	XtSetArg(al[ac], XmNmappedWhenManaged, FALSE); ac++;
	XtSetArg(al[ac], XmNallowShellResize, TRUE); ac++;
	XtSetArg(al[ac], XmNtitle, (char *) "About Freeway"); ac++;
	XtSetArg(al[ac], XmNdeleteResponse, XmDESTROY); ac++;
	XtSetArg(al[ac], XmNbackground, grey); ac++;
	shell = XmCreateDialogShell(awp->shell, (char *)"help_shell", al, ac );
	XtAddCallback (shell, XmNdestroyCallback, popup_destroyed, NULL);

	ac = 0;
	XtSetArg(al[ac], XmNautoUnmanage, FALSE); ac++;
	XtSetArg(al[ac], XmNbackground, grey); ac++;
	topform = XmCreateForm ( shell, (char *) "topform", al, ac );

	ac = 0;
	XtSetArg(al[ac], XmNeditable, FALSE); ac++;
	XtSetArg(al[ac], XmNresizeHeight, TRUE); ac++;
	XtSetArg(al[ac], XmNresizeWidth, TRUE); ac++;
	XtSetArg(al[ac], XmNeditMode, XmMULTI_LINE_EDIT); ac++;
	XtSetArg(al[ac], XmNwordWrap, TRUE); ac++;
	XtSetArg(al[ac], XmNbackground, WHITE); ac++;
	text = XmCreateText(topform, (char *) "help_text", al, ac );

	ac = 0;
	xmstring = XmStringCreateLtoR((char *) "Close", 
				(XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstring); ac++;
	XtSetArg(al[ac], XmNbackground, grey); ac++;
	clobut = XmCreatePushButton( topform, (char *) "clobut", al, ac );
	XmStringFree(xmstring);

	XtVaSetValues(text,
		XmNtopAttachment, XmATTACH_FORM,
		XmNbottomAttachment, XmATTACH_FORM,
		XmNbottomOffset, 25,
		XmNleftAttachment, XmATTACH_FORM,
		XmNrightAttachment, XmATTACH_FORM,
		NULL);
	XtVaSetValues(clobut,
		XmNtopAttachment, XmATTACH_NONE,
		XmNbottomAttachment, XmATTACH_FORM,
		XmNleftAttachment, XmATTACH_NONE,
		XmNrightAttachment, XmATTACH_FORM,
		NULL);

	XtVaSetValues(text, XtNwidth, 300, XtNheight, 100, NULL);

	XtAddCallback(clobut, XmNactivateCallback, help_close,NULL);

	XtManageChild(topform);
	XtManageChild(text);
	XtManageChild(clobut);
}

