/*@ cc -c -D_NO_PROTO @I @F -o @R.o
*/

/* CURSOR SETTING FUNCTIONS */

#include <X11/Intrinsic.h>
#include <X11/cursorfont.h>
#include <Xm/Xm.h>

/* Create a Cursor Object of a given Type (See X11/cursorfont.h) */

#ifndef   _NO_PROTO
static Cursor create_font_cursor(Display *display, int cursor_type)
#else  /* _NO_PROTO */
static Cursor create_font_cursor(display,cursor_type)
	Display *display ;
	int      cursor_type ;
#endif /* _NO_PROTO */
{
	extern Cursor XCreateFontCursor() ;

	/* Ensure Cursor is within sensible bounds */

	if ((cursor_type < XC_X_cursor) || (cursor_type > XC_num_glyphs)) {
		return (Cursor) 0 ;
	}

	/* Cursors are per-display resources. Ensure Display is Ok */

	if (display == (Display *) 0) {
		return (Cursor) 0 ;
	}

	/* CREATE FONT CURSOR */

	return XCreateFontCursor(display,cursor_type) ;
}


/* Set the cursor for given widget */

#ifndef   _NO_PROTO
static Boolean set_font_cursor(Widget widget, Cursor cursor)
#else  /* _NO_PROTO */
static Boolean set_font_cursor(widget,cursor)
	Widget widget ;
	Cursor cursor ;
#endif /* _NO_PROTO */
{
	Display *display ;
	Window   window ;
	
	if ((widget == (Widget) 0) || (cursor == (Cursor) 0)) {
		return False ;
	}

	if (XmIsGadget(widget)) {
		/* ESSENTIAL: Gadgets do not have their own window */

		return False ;
	}

	if ((display = XtDisplay(widget)) == (Display *) 0) {
		return False ;
	}

	if ((window = XtWindow(widget)) == (Window) 0) {
		return False ;
	}

	/* DEFINE CURSOR FOR THE WINDOW */

	XDefineCursor(display,window,cursor) ;

	/* For Immediate Effect */

	XFlush(display) ;

	return True ;
}


/* NB: Cursors are INHERITED through the widget hierarchy  */
/* Therefore to set the cursor for a whole dialog, set the */
/* Cursor for the top level shell widget.                  */

/* Wander up the hierarchy to the top level shell */

#ifndef   _NO_PROTO
static Widget find_shell(Widget widget)
#else  /* _NO_PROTO */
static Widget find_shell(widget)
	Widget widget ;
#endif /* _NO_PROTO */
{
	register Widget w = widget ;

	while (w != (Widget) 0) {
		if (XtIsShell(w)) {
			break ;
		}

		w = XtParent(w) ;
	}

	return w ;
}


/* Set the Cursor for a Whole Dialog to the Watch (Waiting) Cursor           */
/* NB: static Cursor: rework if you are opening many displays or closing and */
/*     restarting sessions onto a single display.                            */

#ifndef   _NO_PROTO
Boolean set_watch_cursor(Widget widget)
#else  /* _NO_PROTO */
Boolean set_watch_cursor(widget)
	Widget widget ;
#endif /* _NO_PROTO */
{
	static Cursor cursor = (Cursor) 0 ;
	       Widget shell ;

	/* Ignore this if setting for a specific widget (sub-hierarchy) */

	if ((shell = find_shell(widget)) == (Widget) 0) {
		return False ;
	}
	
	/* Create the Watch Cursor */

	if (cursor == (Cursor) 0) {
		cursor = create_font_cursor(XtDisplay(shell), XC_watch) ;
	}

	/* Set it */

	if (cursor != (Cursor) 0) {
		return set_font_cursor(shell,cursor) ;
	}

	return False ;
}


/* Revert the Cursor for a Whole Dialog to the Normal (Left Pointer) Cursor  */
/* NB: static Cursor: rework if you are opening many displays or closing and */
/*     restarting sessions onto a single display.                            */

#ifndef   _NO_PROTO
Boolean set_normal_cursor(Widget widget)
#else  /* _NO_PROTO */
Boolean set_normal_cursor(widget)
	Widget widget ;
#endif /* _NO_PROTO */
{
	static Cursor cursor = (Cursor) 0 ;
	       Widget shell ;

	/* Ignore this if setting for a specific widget (sub-hierarchy) */

	if ((shell = find_shell(widget)) == (Widget) 0) {
		return False ;
	}

	/* Create the Normal Left Pointer Cursor */

	if (cursor == (Cursor) 0) {
		cursor = create_font_cursor(XtDisplay(shell), XC_left_ptr) ;
	}
	
	/* Set it */

	if (cursor != (Cursor) 0) {
		return set_font_cursor(shell,cursor) ;
	}

	return False ;
}
