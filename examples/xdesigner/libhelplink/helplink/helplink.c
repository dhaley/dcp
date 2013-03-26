/* X-Designer
** (c) 1992, 1993, 1994, 1995
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
static char *sccsid = "@(#)helplink.c     1.14" ; /* 96/12/13 */
#endif /* lint && NOSCCS */
 
/* 
** File:       helplink.c
** Purpose:    Provision of XD/Help-based online help for 
**             xdesigner-generated applications
** Created by: Giles P.J. Thomas (giles@ist.co.uk)
** Date:       3rd February 1996
*/

#include <stdio.h>
#include <X11/Intrinsic.h>

#ifndef   Bool
#define   Bool    int
#endif /* Bool */


/********** Structures used by this code: **********/

typedef struct _XDHelpDoc_s 
{
    char  *doc ;         /* The document name */
    char **path ;        /* The default path, if one exists */
    int    handle ;      /* UNUSED - FrameMaker help uses this */
    Bool   new_window ;  /* Flag to tell us if we need a new window */

} _XDHelpDoc_t, *_XDHelpDoc_p;

typedef struct _XDHelpPair_s 
{
    _XDHelpDoc_p   doc ;          /* The document to load */
    char         **tag ;          /* The tag within it to go to */
    Bool           open_doc ;     /* Should we be going to the start of the
				    document (True) or the tag with name
				    <widget name> (False)? */
} _XDHelpPair_t, *_XDHelpPair_p;


/********** Utility functions **********/


/*
** Function to build a tag from the given tag, the widget, and the 
** open_doc value. Result does not need to be freed.
*/

#ifndef   _NO_PROTO
static char *FullTag(char **oldTag, Bool open_doc, Widget w)
#else  /* _NO_PROTO */
static char *FullTag(oldTag, open_doc, w)
    char **oldTag ;
    Bool   open_doc ;
    Widget w ;
#endif /* _NO_PROTO */
{
    if ( oldTag != (char **) 0 )
	return *oldTag ;

    if ( open_doc )
	return "" ;

    return XtName( w ) ;
}


/*
** Function to build a full pathname from the default path and a
** document filename.  Caller must free result.
*/

#ifndef   _NO_PROTO
static char *FullFilename(char *file, char *path)
#else  /* _NO_PROTO */
static char *FullFilename(file, path)
    char *file ;
    char *path ;
#endif /* _NO_PROTO */
{
    register char *filename ;

    /* if the filename's relative or there's no default path anyway, we
       just return the filename */
    if ( file[0] == '/' || path == (char *) 0 )
	return strdup( file ) ;

    /* Otherwise we concatenate the two and return the result */
    filename = (char *) malloc( strlen( path ) + strlen( file ) + 2 ) ;
    (void) sprintf( filename, "%s/%s", path, file ) ;

    return filename ;
}


/*
** Function to build a URL from a filename and a tag
*/

#ifndef   _NO_PROTO
static char *FullURL(char *filename, char *tag)
#else  /* _NO_PROTO */
static char *FullURL(filename, tag)
    char *filename ;
    char *tag ;
#endif /* _NO_PROTO */
{
    register char *url = (char *) XtMalloc( strlen( filename ) + strlen( tag ) + 10 ) ;

    (void) sprintf( url, "%s#%s", filename, tag ) ;

    return url ;
}


/********** The help link function itself **********/


#ifndef   _NO_PROTO
void XDhelp_link(Widget w, XtPointer client_data, XtPointer call_data)
#else  /* _NO_PROTO */
void XDhelp_link(w, client_data, call_data )
    Widget    w ;
    XtPointer client_data ;
    XtPointer call_data ;
#endif /* _NO_PROTO */
{
    _XDHelpPair_p  helpPair = (_XDHelpPair_p) client_data ;
    char          *tag,
	          *filename,
	          *url ;

    Widget         thisOne = w ;
    Widget         IPCwidget ;
    
    if ( helpPair == (_XDHelpPair_p) 0 ) {
	(void) fputs( "Error in help link; NULL help pair.\n", stderr ) ;
	return ;
    }

    if ( helpPair->doc == (_XDHelpDoc_p) 0 ) {
	(void) fputs( "Error in help link; NULL help document\n", stderr ) ;
	return ;
    }

    /* We use a widget for IPC with XD/Help.  This must be the 
       same widget for every call, as the protocol would leave us with
       one XD/Help for each widget we used.  So, we walk up the 
       hierarchy until we find the application shell and we use that.
       This has the down side that we will be waiting for property changes
       on our application shell, which happens fairly regularly due to
       window manager interactions, but it has the useful feature that
       we do not need to remeber (and avoid destroying) a particular widget
       simply because we're using it for IPC - if the application shell
       has been destroyed, we will be very unlikely to be calling help
       systems... */
    while ( thisOne != (Widget) 0 ) {
	IPCwidget = thisOne ;
	thisOne = XtParent( thisOne ) ;
    }

    /* If we can't find a widget to use for communication, we might as
       well give up... */
    if ( IPCwidget == (Widget) 0 ) {
	(void) fputs( "Cannot find widget to use for XD/Help IPC\n", stderr ) ;
	return ;
    }

    tag = FullTag( helpPair->tag, helpPair->open_doc,  w ) ;
    filename = FullFilename( helpPair->doc->doc, *helpPair->doc->path ) ;
    url = FullURL( filename, tag ) ;

    XDHelp( IPCwidget, url ) ;

    free( filename ) ;
    XtFree( url ) ;
}
