/*@ cc -c -D_NO_PROTO @I @F -o @R.o
*/

/* WINDOW MANAGER CLOSE CALLBACK */

#include <Xm/Xm.h>


/* Associate Close Callback with Dialog Shell Window */

#ifndef   _NO_PROTO
Boolean WM_set_close_callback(Widget    shell,
                              void    (*callback)(Widget, XtPointer, XtPointer),
			      XtPointer client_data)
#else  /* _NO_PROTO */
Boolean WM_set_close_callback(shell,callback,client_data)
	Widget      shell ;        /* YOUR DIALOG SHELL WIDGET       */
	void      (*callback)() ;  /* YOUR CALLBACK                  */
				   /* - SAME AS DIALOG CANCEL BUTTON */
	XtPointer   client_data ;  /* YOUR CALLBACK DATA IF ANY      */
	                           /* - SAME AS CANCEL BUTTON DATA   */
#endif /* _NO_PROTO */
{
	extern Atom XmInternAtom() ;

	Display *display  = (Display *) 0 ;
	Atom     property = (Atom) 0 ;
	Atom     protocol = (Atom) 0 ;

	if (shell == (Widget) 0) {
		return False ;
	}

	if ((display = XtDisplay(shell)) == (Display *) 0) {
		return False ;
	}

	/* Retrieve Window Manager Protocol Property */

	if ((property = XmInternAtom(display, "WM_PROTOCOLS", False)) == (Atom) 0) {
		return False ;
	}

	/* Retrieve Window Manager Delete Window Property */

	if ((protocol = XmInternAtom(display, "WM_DELETE_WINDOW", True)) == (Atom) 0) {
		return False ;
	}

	/* Ensure that Shell has the Delete Window Property */
	/* NB: Necessary since some Window managers are not */
	/* Fully XWM Compilant (olwm for instance is not)   */

	XmAddProtocols(shell, property, &protocol, 1) ;

	/* Now add our callback into the Protocol Callback List */

	XmAddProtocolCallback(shell, property, protocol, callback, client_data) ;

	return True ;
}


/* Disassociate Close Callback from Dialog Shell Window   */
/* NB: PARAMETERS MUST MATCH WM_set_close_callback() CALL */

#ifndef   _NO_PROTO
Boolean WM_unset_close_callback(Widget    shell,
                                void    (*callback)(Widget, XtPointer, XtPointer),
			        XtPointer client_data)
#else  /* _NO_PROTO */
Boolean WM_unset_close_callback(shell,callback,client_data)
	Widget      shell ;        /* YOUR DIALOG SHELL WIDGET       */
	void      (*callback)() ;  /* YOUR CALLBACK                  */
				   /* - SAME AS DIALOG CANCEL BUTTON */
	XtPointer   client_data ;  /* YOUR CALLBACK DATA IF ANY      */
	                           /* - SAME AS CANCEL BUTTON DATA   */
#endif /* _NO_PROTO */
{
	extern Atom XmInternAtom() ;

	Display *display  = (Display *) 0 ;
	Atom     property = (Atom) 0 ;
	Atom     protocol = (Atom) 0 ;

	if (shell == (Widget) 0) {
		return False ;
	}

	if ((display = XtDisplay(shell)) == (Display *) 0) {
		return False ;
	}

	/* Retrieve Window Manager Protocols Hook */
	
	if ((property = XmInternAtom(display, "WM_PROTOCOLS", False)) == (Atom) 0) {
		return False ;
	}
	
	/* Retrieve Window Manager Delete Window Property Hook */

	if ((protocol = XmInternAtom(display, "WM_DELETE_WINDOW", True)) == (Atom) 0) {
		return False ;
	}
	
	/* Remove our callback from Protocol Callback List */

	XmRemoveProtocolCallback(shell, property, protocol, callback, client_data) ;

	return True ;
}
