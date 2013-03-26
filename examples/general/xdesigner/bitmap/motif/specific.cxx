/*
** Generated Code
*/

/*
** X-Designer generated prelude.
** Do not edit lines before "End of X-Designer generated prelude"
** Lines beginning ** X-Designer Stub indicate a stub
** which will not be output on re-generation
*/

/*
**LIBS: -lXm -lXt -lX11
*/

#include <afxwin.h>
#include <afxext.h>

#include "main.h"



/* End of X-Designer generated prelude */

#include "stdlib.h"

void
drawing_c::DrawCell ( unsigned int x, unsigned int y )
{
    XSetForeground ( XtDisplay ( _xd_rootwidget ), gc, *(colours[cells[x][y]]) );
    XFillRectangle ( XtDisplay ( _xd_rootwidget ), XtWindow ( _xd_rootwidget ),
			gc, x * 10 + 1, y * 10 + 1, 9, 9 );
}

void
drawing_c::XGridLine ( unsigned int x )
{
    XDrawLine ( XtDisplay ( _xd_rootwidget ), XtWindow ( _xd_rootwidget ),
			gc, 0, x * 10, 320, x * 10 );
}

void
drawing_c::YGridLine ( unsigned int y )
{
    XDrawLine ( XtDisplay ( _xd_rootwidget ), XtWindow ( _xd_rootwidget ),
			gc, y * 10, 0, y * 10, 320 );
}

/*
** X-Designer Stub drawing_c::DoInput
*/

void 
drawing_c::DoInput ( )
{
    XmAnyCallbackStruct *call_data = xd_call_data();
    if ( call_data->event->type == ButtonPress )
    {
	start_x = ( call_data->event->xbutton.x - 1 ) / 10;
	start_y = ( call_data->event->xbutton.y - 1 ) / 10;
	if ( start_x < 32
	  && start_y < 32 )
	    if ( shell->tool_box->tool == pencil )
		SetCell ( start_x, start_y );
    }
    else
	if ( call_data->event->type == ButtonRelease )
	{
	    unsigned int end_x = ( call_data->event->xbutton.x - 1 ) / 10;
	    unsigned int end_y = ( call_data->event->xbutton.y - 1 ) / 10;
	    if ( end_x < 32
	      && end_y < 32 )
	    {
		switch (shell->tool_box->tool) {
		    case line:
			draw_line ( start_x, start_y, end_x, end_y, TRUE );
			break;
		    case rectangle:
			draw_rectangle ( start_x, start_y, end_x, end_y );
			break;
		    case fill:
			fill_rectangle ( start_x, start_y, end_x, end_y );
			break;
		    default:
			break;
		}
	    }
	}
}

/*
** X-Designer Stub drawing_c::DoExpose
*/

void 
drawing_c::DoExpose ( )
{
    if ( !initialised )
    {
	initialised = TRUE;
	gc = XCreateGC ( XtDisplay ( _xd_rootwidget ), XtWindow ( _xd_rootwidget ), (unsigned long) 0, (XGCValues *) 0 );
    }
    DrawCells ();
    XSetForeground ( XtDisplay ( _xd_rootwidget ), gc, *(colours[black]) );
    DrawGrid ();
}


/*
** X-Designer Stub shell_c::DoExit
*/

void
shell_c::DoExit ( )
{
    exit ( 0 );
}

/*

   Leave stub comments so X-Designer won't regenerate stubs

** X-Designer Stub drawing_c::OnPaint
** X-Designer Stub drawing_c::OnLButtonDown
** X-Designer Stub drawing_c::OnLButtonUp
** X-Designer Stub tool_box_c::Fill
** X-Designer Stub tool_box_c::Rectangle
** X-Designer Stub tool_box_c::Line
** X-Designer Stub tool_box_c::Pencil
** X-Designer Stub colour_box_c::Magenta
** X-Designer Stub colour_box_c::Cyan
** X-Designer Stub colour_box_c::Yellow
** X-Designer Stub colour_box_c::Blue
** X-Designer Stub colour_box_c::Green
** X-Designer Stub colour_box_c::Red
** X-Designer Stub colour_box_c::White
** X-Designer Stub colour_box_c::Black
*/

