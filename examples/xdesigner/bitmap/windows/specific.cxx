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


void
drawing_c::DrawCell ( unsigned int x, unsigned int y )
{
    dc->FillRect ( CRect ( x * 10 + 1, y * 10 + 1, x * 10 + 10, y * 10 + 10 ),
		    colours[cells[x][y]] );
}

void
drawing_c::XGridLine ( unsigned int x )
{
    dc->MoveTo ( 0, x * 10 );
    dc->LineTo ( 320, x * 10 );
}

void
drawing_c::YGridLine ( unsigned int y )
{
    dc->MoveTo ( y * 10, 0 );
    dc->LineTo ( y * 10, 320 );
}

/*
** X-Designer Stub drawing_c::OnPaint
*/

afx_msg void drawing_c::OnPaint()
{
    PAINTSTRUCT paint_struct;
    dc = BeginPaint ( &paint_struct );
    DrawCells ( );
    DrawGrid ( );
    EndPaint ( &paint_struct );
}

/*
** X-Designer Stub drawing_c::OnLButtonDown
*/

afx_msg void drawing_c::OnLButtonDown( UINT nFlags, CPoint point )
{
	start_x = ( point.x - 1 ) / 10; 
	start_y = ( point.y - 1 ) / 10;
	if ( start_x < 32 
	  && start_y < 32 )  
		if ( shell->tool_box->tool == pencil )   
		{
			dc = GetDC ();
			SetCell ( start_x, start_y );
			ReleaseDC ( dc );
		}
		else
			SetCapture();
}

/*
** X-Designer Stub drawing_c::OnLButtonUp
*/

afx_msg void drawing_c::OnLButtonUp( UINT nFlags, CPoint point )
{
	if ( GetCapture() != this )
		return;
	unsigned int end_x = ( point.x - 1 ) / 10; 
	unsigned int end_y = ( point.y - 1 ) / 10;
	if ( end_x < 32 
	  && end_y < 32 )           
	{
		dc = GetDC ( );
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
		ReleaseDC ( dc );
	}
	ReleaseCapture();			  
}


/*
** X-Designer Stub shell_c::DoExit
*/

void 
shell_c::DoExit ( )
{
    SendMessage ( WM_CLOSE );
}

/*

   Leave stub comments so X-Designer won't regenerate stubs

** X-Designer Stub drawing_c::DoInput
** X-Designer Stub drawing_c::DoExpose
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
