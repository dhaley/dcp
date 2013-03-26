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
static char *sccsid = "@(#)helplink.c     1.10" ; /* 98/06/15 */
#endif /* lint && NOSCCS */
 
/* 
** File:       helplink.c
** Purpose:    Provision of Netscape-based online help for 
**             generated applications
** Created by: Giles P.J. Thomas
** Date:       1st February 1996
*/

#include <stdio.h>
#include <string.h>
#include <X11/Intrinsic.h>

#ifndef   Bool
#define   Bool   int
#endif /* Bool */


#ifndef   _NO_PROTO
extern void SendNetscapeTo(char *, Bool) ;
#else  /* _NO_PROTO */
extern void SendNetscapeTo() ;
#endif /* _NO_PROTO */

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
#ifdef    VMS
    int vms_path = 0 ;
#endif /* VMS */

    char *filename ;

    /* if the filename's relative or there's no default path anyway, we
       just return the filename */
    
    if ( file[0] == '/' || path == NULL ) {
	return strdup( file ) ;
    }

#ifdef    VMS
    {
	/* Just in case we get the D:[X.Y]Z format instead of unix-style path */

   	char *cptr ;

    	if (((cptr = strrchr(file, ']')) == (char *) 0)) {
		return strdup( file ) ;
    	}

	vms_path = 1 ;
    }
#endif /* VMS */

    /* Otherwise we concatenate the two and return the result */
    filename = (char *) XtMalloc( strlen( path ) + strlen( file ) + 2 ) ;

    (void) sprintf( filename, 
#ifdef    VMS
		    (vms_path ? "%s%s" : "%s/%s"),
#else  /* VMS */
		    "%s/%s", 
#endif /* VMS */
		    path, 
		    file ) ;

    /* WOOPS - THIS WAS MISSING */

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
    char *url = (char *) XtMalloc( strlen( filename ) + strlen( tag ) + 10 ) ;

    /* Netscape has the intelligence to work out whether whatever we
       give it is a local file or a remote one, eg. to put file: at
	 the start of the URL or to put http: there.  So, we don't make
	 any assumptions here... */
    
    (void) sprintf( url, "%s#%s", filename, tag ) ;

    return url ;
}

/********** The help link function itself **********/

#ifndef   _NO_PROTO
void XDhelp_link(Widget w, XtPointer client_data, XtPointer call_data)
#else  /* _NO_PROTO */
void XDhelp_link(w, client_data, call_data)
    Widget    w ;
    XtPointer client_data ;
    XtPointer call_data ;
#endif /* _NO_PROTO */
{
    _XDHelpPair_p  helpPair = (_XDHelpPair_p) client_data ;
    char          *tag,
		  *filename,
		  *url ;

    if ( helpPair == NULL ) {
	fputs( "Error in help link; NULL help pair.\n", stderr ) ;
	return ;
    }

    if ( helpPair->doc == NULL ) {
	fputs( "Error in help link; NULL help document\n", stderr ) ;
	return ;
    }

    tag = FullTag( helpPair->tag, helpPair->open_doc,  w ) ;
    filename = FullFilename( helpPair->doc->doc, *helpPair->doc->path ) ;
    url = FullURL( filename, tag ) ;

    SendNetscapeTo( url, helpPair->doc->new_window ) ;

    free( filename ) ;
    free( url ) ;
}
