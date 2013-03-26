#include <X11/Xatom.h>
#include <X11/Intrinsic.h>
#include <Xm/Xm.h>
#include <stdio.h>

#ifndef __hpux
#include <rpc/rpc.h>
#endif /* __hpux */

static Display *d        = (Display *) 0 ;
static char    *propName = "_Frame_RPC";

#include "client.c"

typedef struct _XDHelpDoc_s {
	char *doc;
	char **path;
	int handle;
	Bool new_window;
} _XDHelpDoc_t, *_XDHelpDoc_p;

typedef struct _XDHelpPair_s {
	_XDHelpDoc_p doc;
	char **tag;
	Bool open_doc;
} _XDHelpPair_t, *_XDHelpPair_p;


static int last_doc = 0;


#ifndef   _NO_PROTO
static Bool open_doc(_XDHelpDoc_p doc)
#else  /* _NO_PROTO */
static Bool open_doc(doc)
    _XDHelpDoc_p doc;
#endif /* _NO_PROTO */
{
    if ( ! doc->doc )
	return False;
    if ( doc->doc[0] == '/' || ! *(doc->path) )
	doc->handle = OpenDoc ( doc->doc );
    else
    {
	char *doc_name = (char *) 0;
	doc_name = (char *) XtMalloc ( strlen ( doc->doc ) + strlen ( *(doc->path) ) + 2 );
	(void) strcpy ( doc_name, *(doc->path) );
	(void) strcat ( doc_name, "/" );
	(void) strcat ( doc_name, doc->doc );

#ifdef    HELP_DEBUG
	(void) printf ( "%s\n", doc_name );
#endif /* HELP_DEBUG */

	doc->handle = OpenDoc ( doc_name );
	XtFree ( doc_name );
    }
    if ( doc->handle < 0 )
	return False;

    return True;
}


#ifndef   _NO_PROTO
static int go_to_link(_XDHelpDoc_p doc, char *tag)
#else  /* _NO_PROTO */
static int go_to_link(doc,tag)
    _XDHelpDoc_p doc;
    char        *tag;
#endif /* _NO_PROTO */
{
    if ( ! doc->doc )
	return False;
    if ( doc->doc[0] == '/' || ! *(doc->path) )
	return GoToLink ( doc->handle, doc->doc, tag, FALSE );
    else
    {
	char *doc_name = (char *) 0;
	int return_value;
	doc_name = (char *) XtMalloc ( strlen ( doc->doc ) + strlen ( *(doc->path) ) + 2 );
	(void) strcpy ( doc_name, *(doc->path) );
	(void) strcat ( doc_name, "/" );
	(void) strcat ( doc_name, doc->doc );
	return_value = GoToLink ( doc->handle, doc_name, tag, FALSE );
	XtFree ( doc_name );
	return return_value;
    }
}


/* The XDhelp_link() function itself */

#ifndef   _NO_PROTO
void XDhelp_link(Widget w, XtPointer client_data, XtPointer call_data)
#else  /* _NO_PROTO */
void XDhelp_link(w, client_data, call_data)
	Widget    w;		/*  widget id           */
	XtPointer client_data;	/*  data from application   */
	XtPointer call_data;      /*  data from widget class  */
#endif /* _NO_PROTO */
{
    _XDHelpPair_p help_pair = (_XDHelpPair_p) client_data;
    _XDHelpDoc_p doc = help_pair->doc;
    char *tag = (char *) 0 ;
    /*
    ** d is required by the client module provided by Frame
    */
    if ( XmIsGadget ( w ) ) {
	d = XtDisplay ( XtParent ( w ) );
    }
    else {
	d = XtDisplay ( w );
    }

    if ( ! localCall ( NULLPROC, xdr_void, NULL, xdr_void, NULL, fiveSeconds ) )
    {
	int pid = fork ();
	int retval;
	switch (pid) {
	    case 0:
		retval = execlp ( "viewer", "viewer", "+viewerIsServer", (char *)0 );
		(void) fprintf ( stderr, "Failed to start viewer, errno = %d\n", retval );
		exit ( -1 );
	    case -1:
		(void) fprintf ( stderr, "Failed to fork to start viewer\n" );
		return;
	    default:
		sleep (10);
	}
    }
    if ( help_pair->open_doc )
    {
	if ( ! open_doc ( doc ) )
	    return;
	if ( !doc->new_window )
	{
	    if ( last_doc != 0 && last_doc != doc->handle )
		CloseDoc ( last_doc );
	    last_doc = doc->handle;
	}
	return;
    }
    if ( help_pair->tag )
	tag = *(help_pair->tag);
    else
	tag = XtName ( w );
    if ( ! doc->new_window )
	doc->handle = last_doc;
    if ( doc->handle )
	if ( go_to_link ( doc, tag ) == 0 )
	    return;
    if ( ! open_doc ( doc ) )
	return;
    if ( !doc->new_window )
	last_doc = doc->handle;
    else
	if ( last_doc == doc->handle )
	    last_doc = 0;
    (void) go_to_link ( doc, tag );
}
