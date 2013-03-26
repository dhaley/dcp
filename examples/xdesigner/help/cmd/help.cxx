/* X-Designer
** (c) 1992, 1993, 1994, 1995, 1996
** Imperial Software Technology (IST),
** 95 London Street,
** Reading,
** Berkshire,
** United Kingdom RG1 4QA.
**
** Telephone: +44 1734 587055
** Fax:       +44 1734 589005
** Email:     support@ist.co.uk
*/

/*
**LIBS: -lcppgen -lclient -lxdclass -lsyslibs -lXpm -ltooltips -lXm -list -lbsd -lXt -lX11 -lsys_extras -lextras
*/

#if !defined(lint) && !defined(NOSCCS)
static char *sccsid = {"@(#)helpGuru/cmd/help.cxx	1.20"} ; /* 01/11/23 */
#endif /* lint && NOSCCS */

#include <stdio.h>
#include <stdlib.h>
#include <Xm/Xm.h>
#include "CGuru.h"

XtAppContext app_context;
Display *display;       /*  Display             */


/*
** Main routine for the help system - standard X/Motif application 
** initialisation
*/
int
main( int argc, char **argv ) {

    XtSetLanguageProc( (XtAppContext) NULL, 
		       (XtLanguageProc) NULL, 
		       (XtPointer) NULL );
    XtToolkitInitialize();
    app_context = XtCreateApplicationContext();
    display = XtOpenDisplay( app_context, NULL, argv[0], "xdhelp",
			     NULL, 0, &argc, argv);
    
    if ( !display ) {
	fprintf( stderr, "%s: can't open display, exiting...\n", 
		 argv[0] ) ;
	exit(-1) ;
    }

    /* Create the objects representing the various shells, and their
       associated widget hierarchies */
    helpShell = new CGuru;
    helpShell->create( display, argv[0], argc, argv, "xdhelp" );

    printDialog = new CPrintDialog;
    printDialog->create( helpShell->xd_rootwidget(), "printDialog" );

    cantOpenShell = new COpenDbErrorAlert;
    cantOpenShell->create( helpShell->xd_rootwidget(), "cantOpenShell" );

    sysErrAlert = new CSysErrorAlert;
    sysErrAlert->create( helpShell->xd_rootwidget(), "sysErrAlert" );

    findAlert = new CFindAlert;
    findAlert->create( helpShell->xd_rootwidget(), "findAlert" );

    findDialog = new CFindDialog;
    findDialog->create( helpShell->xd_rootwidget(), "findDialog" );

    saveFileDialog = new CSaveFileDialog;
    saveFileDialog->create( helpShell->xd_rootwidget(), "saveFileDialog" );

    historyShell = new CHistoryDialog;
    historyShell->create( helpShell->xd_rootwidget(), "historyShell" );

    aboutShell = new CAboutBox;
    aboutShell->create( helpShell->xd_rootwidget(), "aboutShell" );

    openFileDialog = new COpenFileDialog;
    openFileDialog->create( helpShell->xd_rootwidget(), "openFileDialog" );

    /* realise everything */
    XtRealizeWidget( helpShell->xd_rootwidget() );

    /* Setup the IPC system if we've been passed a window ID on which 
       to announce our presence by setting a property */
    helpShell->SetupIPC( argc, argv ) ;

    /* ...and go into the event loop */
    helpShell->MainLoop( app_context, display );

    exit( 0 );
}

