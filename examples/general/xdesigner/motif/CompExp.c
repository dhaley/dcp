/*
** When using the DrawingArea widget it is often desirable to compress
** multiple Expose events together to avoid repeatedly refreshing the
** display in the widget. This can be done by the X toolkit, but,
** unfortunately, the Motif DrawingArea widget has compress_exposures
** turned off. Ways round this include changing the DrawingArea class
** structure at runtime (not recommended), or deriving your own widget
** from DrawingArea. An easier way is simply to do the following in
** your expose callback for the DrawingArea.This compresses all Expose
** events in the Event queue into one event by taking the union of all
** the exposed areas. The code can easily be modified if you need to
** preserve the shape of the exposed region rather than simply taking
** the enclosing box.
*/

/* ARGSUSED */
#ifndef   _NO_PROTO
static void expose_callback(Widget                       w,
                            XtPointer                    client_data, 
			    XmDrawingAreaCallbackStruct *call_data)
#else  /* _NO_PROTO */
static void expose_callback(w, client_data, call_data)
	Widget                       w ;
	XtPointer                    client_data ;
	XmDrawingAreaCallbackStruct *call_data ;
#endif /* _NO_PROTO */
{
	XEvent    *event = call_data->event ;
	XEvent     next_exposure ;
	XRectangle rect ;
	Region     region = 0 ;

	/* Process all remaining Expose events in the queue*/
	while (XCheckWindowEvent(XtDisplay(w), XtWindow(w), ExposureMask, &next_exposure)) {
		if (!region) {
			region = XCreateRegion();
			XtAddExposureToRegion(event, region);
		}
		XtAddExposureToRegion(&next_exposure, region);
	}

	/* Now work out the bounding box of the exposed region */
	if (region) {
		XClipBox(region, &rect);
		event->x = rect.x;
		event->y = rect.y;
		event->width = rect.width;
		event->height = rect.height;
		XDestroyRegion(region);
	}

	<Normal expose callback stuff>
}
