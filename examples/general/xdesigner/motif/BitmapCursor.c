/*
** This code shows how to create a cursor from two bitmaps. The
** bitmaps are the cursor shape and its mask.
*/

/* Include the two bitmaps */
#include "cursor.bm"
#include "cursor_mask.bm"

/*
** Create the cursor. "w" is any old widget, and "fg" and "bg" are the
** foreground and background colours you want for the cursor.
*/

#ifndef   _NO_PROTO
Cursor create_bitmap_cursor(Widget w, XColor *fg, XColor *bg)
#else  /* _NO_PROTO */
Cursor create_bitmap_cursor(w, fg, bg)
	Widget w;
	XColor *fg, *bg;
#endif /* _NO_PROTO */
{
	Display *display  = XtDisplay(w) ;
	Drawable drawable = XtWindow(w) ;

	Pixmap   image    = XCreateBitmapFromData(display, drawable, cursor_bits,      cursor_width,      cursor_height) ;
	Pixmap   mask     = XCreateBitmapFromData(display, drawable, cursor_mask_bits, cursor_mask_width, cursor_mask_height) ;

	return XCreatePixmapCursor(display, image, mask, fg, bg, cursor_x_hot, cursor_y_hot) ;
}
