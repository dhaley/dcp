/*@ cc -g -c @I @F @L -o @R.o
*/

/*
** X-Designer,
** Imperial Software Technology (IST),
** Kings Court,
** 185 Kings Road,
** Reading, 
** Berkshire,
** United Kingdom RG1 4EX.
**
** Telephone: +44 189 587055
** Fax:       +44 189 589005
** Email:     support@ist.co.uk
** Web:       http://www.ist.co.uk
*/

#ifndef   lint
static char *sccsid[] = {"@(#)dist/release/examples/demos/greptool/greptool.c	1.4"} ; /* 01/08/24 */
#endif /* lint */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <X11/Intrinsic.h>

XtAppContext app_context = (XtAppContext) 0 ;
Display         *display = (Display *) 0 ;       /* Display */

extern Widget mainshell;


#ifndef   _NO_PROTO
int main(int argc, char **argv)
#else  /* _NO_PROTO */
int main(argc,argv)
	int    argc ;
	char **argv ;
#endif /* _NO_PROTO */
{
	XtSetLanguageProc((XtAppContext) 0, (XtLanguageProc) 0, (XtPointer) 0) ;

	/* Initialise Xt intrinsics */
	XtToolkitInitialize ();

	app_context = XtCreateApplicationContext ();
	display     = XtOpenDisplay (app_context, NULL, "greptool", "greptool", NULL, 0, &argc, argv);

	if (!display) {
	    (void) fprintf(stderr, "greptool : can't open display, exiting...");

	    exit(0);
	}

	/* Create main dialog */

	create_mainshell(display, argv[0], argc, argv);

	/* Realise main dialog root widget and enter main loop */

	XtRealizeWidget (mainshell);
	XtAppMainLoop (app_context);

	/* NOTREACHED */

	return 0 ;
}

