/*
** When using DrawingAreas, you need to be able to handle Expose
** events in order to refresh the display. If you are scrolling
** the drawing area using XCopyArea, then you will want to receive
** Expose events to handle the redrawing of the area which is
** 'scrolled on'. This is not quite as straightforward as it would
** seem.
**
** Firstly, the graphics context which you use for scrolling must have
** "graphics_exposures" set to True. This causes the X server to
** generate a GraphicsExpose event when an area is exposed due to
** scrolling.
** Next, you need to get the DrawingArea widget to handle the
** GraphicsExpose event. Unfortunately, the DrawingArea expose
** callback will not be called for these events. What you need to do
** is register an event handler for the widget in order to handle the
** GraphicsExpose events.
** This is also useful for handling other related event types such as
** VisibilityNotify. For example, if your drawing code is slow, you
** may want to stop drawing if part or all of the widget is covered
** while you are in the middle of drawing.
*/


#ifndef   _NO_PROTO
void register_handlers(Widget w)
#else  /* _NO_PROTO */
void register_handlers(w)
	Widget w;
#endif /* _NO_PROTO */
{
	XtAddEventHandler(w, 0L,                   True, graphics_expose_callback, (char *) 0) ;
	XtAddEventHandler(w, VisibilityChangeMask, True, graphics_expose_callback, (char *) 0) ;
}


/*
** The event handler for GraphicsExpose events.
*/

/* ARGSUSED */
#ifndef   _NO_PROTO
static void graphics_expose_callback(Widget    w,
                                     XtPointer client_data,
				     XEvent   *event,
				     Boolean  *continue_to_dispatch)
#else  /* _NO_PROTO */
static void graphics_expose_callback(w, client_data, event, continue_to_dispatch)
	Widget    w ;
	XtPointer client_data ;
	XEvent   *event ;
	Boolean  *continue_to_dispatch ;
#endif /* _NO_PROTO */
{
	switch (event->type) {
	case GraphicsExpose:
		normal_expose_callback(w, client_data, (XExposeEvent *)event);
		break;
	case NoExpose:
		break;
	case VisibilityNotify:
		break;
	}
}
