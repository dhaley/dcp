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

#if !defined(lint) && !defined(NOSCCS)
static char *sccsid = {"@(#)dist/release/src/help/client/help.c	1.22"} ; /* 96/11/14 */
#endif /* lint && NOSCCS */

/*
** help.c:
**
** Interface to help viewer
**
** Giles Thomas 1996
**
** VMS Port, A.J.Fountain, November 1997
*/

#include <stdio.h>
#include <stdlib.h>
#include "help.h"
#include "path.h"

/*
** help client library - the protocol
**
** The protocol used to connect to XDhelp is simple.  The calling application
** designates one of its widgets as a communication endpoint.  It calls 
** XDhelp() passing in this widget, and a topic.  XDhelp looks at this 
** widget's window's properties - if the property XDHELP_WIN is set on it, it 
** gets the value of this property.  This property is another window ID.  It 
** tries to set the property XDHELP_DEST on this other window to the help key.
** If it succeeds then it exits signalling success.
** 
** If the property is not set, or if the set of XDHELP_DEST fails, then either
** XDhelp has not been started or it has exited.  So, the calling application
** starts XDhelp, passing in the window ID of its widget.  It then waits for
** the property to be set, which XDhelp does when it has created a window to
** use for *its* endpoint.  When this happens, it sets XDHELP_DEST as above.
**
** If XDHelp() is called while the application is waiting for the property
** to be set, it does not try to start another XDhelp but simply changes
** what it will set the XDHELP_DEST to when one does start.  This part of
** the protocol might need changing for some applications, or for XDhelps
** which might crash before they have had a chance to let the calling
** application know of their existence.
**
** A final useful feature is the ability to specify that a function be called
** with a particular parameter when the help viewer starts up.  The function
** XDHelpAddStartedCallback( void *(fn)( XtPointer ), XtPointer  ) is used to 
** set this, and is can be cleared with XDHelpRemoveStartedCallback().  Later
** revisions might support multiple callbacks of this type.
*/

#define XDHELP_WIN  "XDHELP_WIN"
#define XDHELP_DEST "XDHELP_DEST"

#ifdef    VMS
#define COMMAND_TEMPLATE "%s" /* "%s -wid %u" */
#else  /* VMS */
#define COMMAND_TEMPLATE "%s -wid %u &"
#endif /* VMS */

/* Forward declarations of some functions used in the main routine */

#ifndef   _NO_PROTO
static Window  GetDestWindow(Widget) ;
static Boolean SetKeyOnDest(Display *, Window, char *) ;
static int     StartXDHelp(Window) ;
static void    AddXDHCallback(Widget) ;
static void    XDHStartedCallback(Widget, XtPointer, XEvent *, Boolean *) ;
#else  /* _NO_PROTO */
static Window  GetDestWindow() ;
static Boolean SetKeyOnDest() ;
static int     StartXDHelp() ;
static void    AddXDHCallback() ;
static void    XDHStartedCallback() ;
#endif /* _NO_PROTO */

/**
** State information for protocol 
*/
static Boolean  waitingForXDHelp = False ;
static char    *currentTopic     = (char *) 0 ;


/**
** A user callback which can be used to check when the help viewer
** has appeared
*/
static void      (*startedCallback)() = (void (*)()) 0 ;
static XtPointer   startedClosure     = (XtPointer) 0 ;

#ifdef    VMS
#define   STRDUP_UNSUPPORTED
#endif /* VMS */

#ifdef    STRDUP_UNSUPPORTED
#ifdef    VMS
extern void *malloc(size_t) ;
#else  /* VMS */
#include <malloc.h>
#endif /* VMS */

#ifndef   _NO_PROTO
static char *strdup(char *s)
#else  /* _NO_PROTO */
static char *strdup(s)
	char *s ;
#endif /* _NO_PROTO */
{
	register char *cptr = (char *) 0 ;
			  
	if (s != (char *) 0) {
		if ((cptr = (char *) malloc((size_t) strlen(s) + 1)) != (char *) 0) {
			(void) strcpy(cptr, s) ;
		}
	}

	return cptr ;
}
#endif /* STRDUP_UNSUPPORTED */


/**
** Display some help, using widget /w/ as the widget for preliminary 
** data transfer if any is necessary.  Returns 1 if the
** connection succeeded, 0 if it failed and a wait will occur before
** the help is displayed.  Either way, the help will eventually be
** displayed so long as the viewer works.  If -1 is returned, an 
** error occured when trying to fork/exec the help viewer, or the 
** widget passed in for IPC was invalid.
*/

#ifndef   _NO_PROTO
int XDHelp(Widget w, char *topic) 
#else  /* _NO_PROTO */
int XDHelp(w, topic) 
	Widget w ;
	char  *topic ;
#endif /* _NO_PROTO */
{
#ifndef   _NO_PROTO
    void XDHelpGetAtoms(Widget) ;
#else  /* _NO_PROTO */
    void XDHelpGetAtoms() ;
#endif /* _NO_PROTO */

    Display * d;
    Window    win;

    Window destWindow ;

    if ( w == (Widget) 0 )
	  return -1 ;

    /* Get display for later use */
    if ( XmIsGadget (w) ) {
	Widget parent = XtParent(w) ;

	d = XtDisplay ( parent) ;
	win = XtWindow ( parent) ;
    }
    else {
	d = XtDisplay (w);
	win = XtWindow (w);
    }

    /* Initialise if necessary */
    XDHelpGetAtoms( w ) ;

    /* Store away the topic so that we know where we should be... */
    if (currentTopic != topic) {
	if ( currentTopic != (char *) 0 )
		free( currentTopic ) ;
	currentTopic = strdup( topic ) ;
    }
    /* If we're already waiting for XDhelp to start up then knowing
       where to go should be sufficient */
    if ( waitingForXDHelp )
	return 0 ;

    /* If we have a destination window specified... */
    if ( (destWindow = GetDestWindow( w )) != (Window) 0 )
	/* ...if we can set the property on it */
	if ( SetKeyOnDest( d, destWindow, topic ) )
	    return 1 ;

    /* At this point, either there was no property set on our window,
       or the XDhelp whose window ID was contained in the property 
       has disappeared.  Either way, if we're not meant to be quietting a
       help viewer, we need to start one.  We set the callback first, as 
       we have to select for the events before we start the program to
       ensure we do pick up any changes. */
    if ( !strcmp( topic, QUIT_HELP_SYSTEM_MSG ) )
	return 1 ;

    AddXDHCallback( w) ;
    return StartXDHelp( win ) ;
}


#ifndef   _NO_PROTO
void QuitHelpViewer( Widget w )
#else  /* _NO_PROTO */
void QuitHelpViewer( w )
	Widget w ;
#endif /* _NO_PROTO */
{
    XDHelp( w, QUIT_HELP_SYSTEM_MSG ) ;
}


#ifndef   _NO_PROTO
void XDHelpAddStartedCallback( void (*fn)(), XtPointer closure )
#else  /* _NO_PROTO */
void XDHelpAddStartedCallback( fn, closure )
    void      (*fn)() ;
    XtPointer   closure ;
#endif /* _NO_PROTO */
{
    startedCallback = fn ;
    startedClosure  = closure ;
}


#ifndef   _NO_PROTO
void XDHelpRemoveStartedCallback(void)
#else  /* _NO_PROTO */
void XDHelpRemoveStartedCallback()
#endif /* _NO_PROTO */
{
    startedCallback = (void (*)()) 0 ;
    startedClosure  = (XtPointer) 0 ;
}

/*
** Atoms cached for efficiency
*/
Atom helpWin  = (Atom) 0 ;
Atom helpDest = (Atom) 0 ;

/*
** Routine to set up the atoms
*/

#ifndef   _NO_PROTO
void XDHelpGetAtoms( Widget w )
#else  /* _NO_PROTO */
void XDHelpGetAtoms( w )
    Widget w ;
#endif /* _NO_PROTO */
{
    Display * d;
    
    if ( XmIsGadget (w) ) {
	d = XtDisplay ( XtParent (w) );
    }
    else {
	d = XtDisplay ( w );
    }

    if ( helpWin == 0 )
	helpWin = XInternAtom( d, XDHELP_WIN, False ) ;
    if ( helpDest == 0 )
	helpDest = XInternAtom( d, XDHELP_DEST, False ) ;
}

/*
** See if a property XDHELP_WIN is set on parameter /w/ and return it coerced
** to a Window if it is
*/

#ifndef   _NO_PROTO
static Window GetDestWindow( Widget w )
#else  /* _NO_PROTO */
static Window GetDestWindow( w )
    Widget w ;
#endif /* _NO_PROTO */
{
    int  propGetResult ;
    Atom actualType ;
    int  actualFormat ;
    long nItems,
	 bytesAfter ;

    unsigned char *property ;

    Display * d;
    Window    win;

    /* Get display for later use */
    if ( XmIsGadget (w) ) {
	Widget parent = XtParent(w) ;

	d = XtDisplay ( parent) ;
	win = XtWindow ( parent) ;
    }
    else {
	d = XtDisplay (w);
	win = XtWindow (w);
    }
    /* Get the property */
    propGetResult = XGetWindowProperty( d,
					win,
					helpWin,
					(long) 0,
					(long) 1,
					False,
					XA_WINDOW,
					&actualType,
					&actualFormat,
					&nItems,
					&bytesAfter,
					&property ) ;

    /* If we couldn't get the property... */
    if ( propGetResult != Success || actualType != XA_WINDOW )
	return (Window) 0 ;

    return *(Window *)property ;
}

static int    (*oldErrorHandler)()  = (int (*)()) 0 ;
static Display *errorDisplay        = (Display *) 0 ;
static Boolean  haveHadBadWinError  = False ;


#ifndef   _NO_PROTO
static int XDHErrorHandler( Display *display, XErrorEvent *error )
#else  /* _NO_PROTO */
static int XDHErrorHandler( display, error )
    Display     *display ;
    XErrorEvent *error ;
#endif /* _NO_PROTO */
{
    if ( (display == errorDisplay) && (error->error_code == BadWindow) ) {
	haveHadBadWinError = True ;
    } else {
	if (oldErrorHandler != (int (*)()) 0) {
		return (*oldErrorHandler)( display, error ) ;
	}
    }

    return 0 ;
}

/*
** Try to set the property XDHELP_DEST on /window/ to /value/.  Return True
** on success, False on failure
*/

#ifndef   _NO_PROTO
static Boolean SetKeyOnDest( Display *display, Window window, char *value )
#else  /* _NO_PROTO */
static Boolean SetKeyOnDest( display, window, value )
    Display *display ;
    Window   window ;
    char    *value ;
#endif /* _NO_PROTO */
{
    /* The only way we can detect that the window doesn't exist is to pick
       up X errors.  As these are called outside the scope of this function
       we must store away some information */
    oldErrorHandler = XSetErrorHandler( XDHErrorHandler ) ;
    errorDisplay = display ;
    haveHadBadWinError = False ;

    /* Now we change the property */
    XChangeProperty( display, window, helpDest, XA_STRING, sizeof( char ) * 8,
		     PropModeReplace, value, strlen( value ) + 1 ) ;
    
    /* The X error, if there is going to be one, will only happen if we 
       synchonise with the server.  One of these calls will call the
       error handler above if there was a problem in the XChangeProperty */
    XFlush( display ) ;
    XSync( display, False ) ;

    /* The error handler will have been called by this point, so we
       should reinstate the old one */
    (void) XSetErrorHandler( oldErrorHandler ) ;

    /* Now, if the error handler has been called due to the problem we 
       were expecting, haveHadBadWinError is True */
    return !haveHadBadWinError ;
}

#ifdef    VMS
/* String Expansion for removal of environment variables        */
/* The classical popen("echo string") solution is not available */

#include <string.h>
include <ctype.h>

#ifndef   MAX_DIR_PATH_LEN
#define   MAX_DIR_PATH_LEN   1024
#endif /* MAX_DIR_PATH_LEN */

#ifndef   MAX_VARIABLE_NAME
#define   MAX_VARIABLE_NAME   64
#endif /* MAX_VARIABLE_NAME */

#ifndef   _NO_PROTO
static char *VMS_varname(char *spec, char **after)
#else  /* _NO_PROTO */
static char *VMS_varname(spec,after)
	char  *spec ;
	char **after ; /* RETURNED */
#endif /* _NO_PROTO */
{
	static char variable[MAX_VARIABLE_NAME + 1] ;
  
	register char *cptr ;
	register char *dptr ;
	register char *eptr = (char *) 0 ;
		 int   parenthesis = 0 ;

	if (after != (char **) 0) {
		*after = spec ;
	}
  
	/* Must Start $ */
    
	if (((cptr = spec) == (char *) 0) || (*cptr != '$')) {
		return (char *) 0 ;
	}
     
	dptr = ++cptr ;
      
	/* $(VARIABLE) ${VARIABLE} as well as $VARIABLE */
    
	if ((*dptr == '(') || (*dptr == '{')) {
		dptr = ++cptr ;
		parenthesis = 1 ;
	}
	
	eptr = dptr ;
     
	for ( ; dptr && *dptr ; dptr++) {
		if (isalnum(*dptr) || (*dptr == '_')) {
			continue ;
		}
	
		/* End of Variable !? */

		if (parenthesis) {
			if ((*dptr == ')') || (*dptr == '}')) {
				eptr = dptr + 1 ;

				break ;
			}
		}

		eptr = dptr ;
	      
		break ;
	}

	(void) strncpy(variable,cptr,dptr-cptr) ;
	      
	variable[(dptr - cptr)] = '\0' ;

	if (after != (char **) 0) {
		*after = &(spec[(eptr - spec)]) ;
	}
		
	return variable ;
}

#ifndef   _NO_PROTO
static char *VMS_expand_string(char *s)
#else  /* _NO_PROTO */
static char *VMS_expand_string(s)
	char *s ;
#endif /* _NO_PROTO */
{
	static char p[MAX_DIR_PATH_LEN + 1] ;

	register char *e ;
		 char *var   = (char *) 0 ;
		 char *env   = (char *) 0 ;
		 char *after = (char *) 0 ;


	if ((var = VMS_varname(s,&after)) != (char *) 0) {
		if ((env = getenv(var)) != (char *) 0) {
			if (after && *after && (*after == ':')) {
				if (*(after + 1) == '[') {
					/* $VAR:[AA]BB.C -> D:[XX.]:[AA]BB.C -> D:[XX.AAA]BB.C */

					e = strrchr(env,']') ;

					if ((e != (char *) 0) && (*(e + 1) == '\0')) {
						if (e != env) {
							if (*(e - 1) != '.') {
								/* D:[XX] -> D:[XX. */
	
								*e = '.' ;
							}
							else {
								/* D:[XX.] -> D:[XX. */
	
								*e = '\0' ;
							}
						}

						/* :[AA]BB.C -> AA]BB.C */
	
						after = after + 2 ;
					}
				}
				else {
					/* $VAR:BB.c -> D:[XX.]:BB.C -> D:[XX]BB.c */

					e = strrchr(env,']') ;

					if ((e != (char *) 0) && (*(e + 1) == '\0')) {
						if (e != env) {
							if (*(e - 1) == '.') {
								/* D:[XX.] -> D:[XX] */

								*(e - 1) = ']' ;
								*e       = '\0' ;
							}
						}

						/* :BB.c -> BB.c */

						after++ ;
					}
				}
			}
			
			(void) sprintf(p, "%s%s", env, (after ? after : "")) ;

			return p ;
		}
	}
			
	return s ;
}
#endif /* VMS */


#ifdef    VMS
/* Fork off detached process */

#include <processes.h>

#ifndef   _NO_PROTO
static int VMS_detach_xdhelp(char *command, int windowid)
#else  /* _NO_PROTO */
static int VMS_detach_xdhelp(command, windowid)
	char *command ;
	int   windowid ;
#endif /* _NO_PROTO */
{
	int pid = vfork() ;

	if (pid > 0) { 
		/* parent process */

		return 0 ;
	}

	if (pid < 0) {
		/* vfork failure */

		return -1 ;
	}

	if (pid == 0) {
		/* child process */

		char  window_id_string[64] ;
		char *cmd = strrchr(command, ']') ;
		char name[256] ;

		if (cmd != (char *) 0) {
			(void) strcpy(name, cmd + 1) ;
		}
		else {
			(void) strcpy(name, command) ;
		}

		(void) sprintf(window_id_string, "%u", windowid) ;

		execl(command, name, "-wid", window_id_string, (char *) 0) ;

		/* Hopefully, we dont reach this */

		(void) fprintf(stderr, "Cannot execute command %s -wid %s\n", command, window_id_string) ;
		(void) fflush(stderr) ;

		exit(1) ;
	}

	/* NO WAIT */

	return 0 ;

}
#endif /* VMS */

/*
** Start up XDhelp, telling it that the window it needs to announce itself
** on is /window/.  Return 0 on success, -1 on failure.
*/

#ifndef   _NO_PROTO
static int StartXDHelp( Window window )
#else  /* _NO_PROTO */
static int StartXDHelp( window )
    Window window ;
#endif /* _NO_PROTO */
{
    char *command = (char *) 0 ;
    char *path    = _HELPPATH ;
    int   result  = 0 ;

    /* Set our state */
    waitingForXDHelp = True ;

#ifdef    VMS
    path   = VMS_expand_string(path) ;
    result = VMS_detach_xdhelp(path, (int) window) ;
#else  /* VMS */
    command = (char *) XtMalloc( strlen( COMMAND_TEMPLATE ) + strlen( path ) + 64 ) ;
    /* Create and execute the command */
    sprintf( command, COMMAND_TEMPLATE, path, (int) window ) ;

    result = ((system( command ) == 0) ? 0 : -1) ;
    XtFree( command ) ;
#endif /* VMS */

    return result ;
}

/*
** Add a callback on /widget/ to send XDhelp to the current topic when 
** the property XDHELP_WIN is set on /widget/.
*/

#ifndef   _NO_PROTO
static void AddXDHCallback( Widget widget )
#else  /* _NO_PROTO */
static void AddXDHCallback( widget )
    Widget widget ;
#endif /* _NO_PROTO */
{
    if ( XmIsGadget( widget ) )
	widget = XtParent( widget );

    XtAddEventHandler( widget, PropertyChangeMask, False, XDHStartedCallback, (XtPointer) 0 ) ;
}

/*
** Callback to send XDhelp to a stored-away topic, currentTopic, when a
** property is set
** NB. we don't pass in the topic in the client data because it might have
** changed in between one run and the next.
*/

#ifndef   _NO_PROTO
static void XDHStartedCallback( Widget w, XtPointer client_data, XEvent *event, Boolean *ctd )
#else  /* _NO_PROTO */
static void XDHStartedCallback( w, client_data, event, ctd )
    Widget     w ;
    XtPointer  client_data ;
    XEvent    *event ;
    Boolean   *ctd ;
#endif /* _NO_PROTO */
{
    /* Check that this *is* the event we were expecting */
    if ( event->type != PropertyNotify
      || event->xproperty.atom != helpWin ) {
	*ctd = True ;
	return ;
    }

    /* XDHelp must have started up (even if it has now gone down again) so
       we're not waiting any more */
    waitingForXDHelp = False ;

    /* Just go through the normal process; XDHelp might have disappeared
       immediately after telling us it was alive. */
    XDHelp( w, currentTopic ) ;

    if ( startedCallback != (void (*)()) 0 ) 
	(*startedCallback)( startedClosure ) ;
}
