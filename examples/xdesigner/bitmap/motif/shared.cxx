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
drawing_c::DrawCells ()
{
    unsigned int x, y;
    for ( x = 0; x < 32; x++ )
	for ( y = 0; y < 32; y++ )
	    DrawCell ( x, y );
}

void
drawing_c::DrawGrid ()
{
    unsigned int x, y;
    for ( x = 0; x <= 32; x++ )
	XGridLine ( x );
    for ( y = 0; y <= 32; y++ )
	YGridLine ( y );
}

void
drawing_c::SetCell ( unsigned int x, unsigned int y )
{
    cells[x][y] = shell->colour_box->colour;
    DrawCell ( x, y );
}

void
drawing_c::draw_line ( unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, unsigned int draw_first)
{
	unsigned int x, y;
	int dx, dy, d, incrE, incrNE, ddx, ddy;

	if (x1 < x0)
		ddx = -1;
	else
		ddx = 1;
	if (y1 < y0)
		ddy = -1;
	else
		ddy = 1;
	dx = x1-x0;
	dy = y1-y0;
	dx = abs(dx);
	dy = abs(dy);
	x = x0;
	y = y0;

	if (draw_first)
		SetCell ( x, y );
	if (abs(dx) > abs(dy)) {
		d = 2*dy-dx;
		incrE = 2*dy;
		incrNE = 2*(dy-dx);

		while (x != x1) {
			if (d <= 0)
				d += incrE;
			else {
				d += incrNE;
				y += ddy;
			}
			x += ddx;
			SetCell ( x, y );
		}
	} else {
		d = 2*dx-dy;
		incrE = 2*dx;
		incrNE = 2*(dx-dy);

		while (y != y1) {
			if (d <= 0)
				d += incrE;
			else {
				d += incrNE;
				x += ddx;
			}
			y += ddy;
			SetCell ( x, y );
		}
	}
}

void

drawing_c::horizontal_line ( unsigned int x0, unsigned int y0, unsigned int x1, unsigned int draw_first )
{
	if (draw_first)
		SetCell ( x0, y0 );
	if (x1 < x0)
	    for ( x0--; x0 >= x1; x0-- )
		SetCell ( x0, y0 );
	else
	    for ( x0++; x0 <= x1; x0++ )
		SetCell ( x0, y0 );
}

void
drawing_c::draw_rectangle ( unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1 )
{
	if (x1 == x0 || y1 == y0) {
		if (y1 == y0)
			SetCell ( x0, y0 );
		else
			draw_line(x0, y0, x1, y1, FALSE);
	} else {
		horizontal_line(x0, y0, x1, FALSE);
		draw_line(x1, y0, x1, y1, FALSE);
		horizontal_line(x1, y1, x0, FALSE);
		draw_line(x0, y1, x0, y0, FALSE);
	}
}

void
drawing_c::fill_rectangle ( unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1 )
{
	unsigned int y;
	if (y1 < y0) {
		y0 ^= y1;
		y1 ^= y0;
		y0 ^= y1;
	}
	for (y = y0; y <= y1; y++)
		horizontal_line(x0, y, x1, TRUE);
}

/*
** X-Designer Stub tool_box_c::Fill
*/

void 
tool_box_c::Fill ( )
{
    tool = fill;
}

/*
** X-Designer Stub tool_box_c::Rectangle
*/

void 
tool_box_c::Rectangle ( )
{
    tool = rectangle;
}

/*
** X-Designer Stub tool_box_c::Line
*/

void 
tool_box_c::Line ( )
{
    tool = line;
}

/*
** X-Designer Stub tool_box_c::Pencil
*/

void 
tool_box_c::Pencil ( )
{
    tool = pencil;
}

/*
** X-Designer Stub colour_box_c::Magenta
*/

void 
colour_box_c::Magenta ( )
{
    colour = magenta;
}

/*
** X-Designer Stub colour_box_c::Cyan
*/

void 
colour_box_c::Cyan ( )
{
    colour = cyan;
}

/*
** X-Designer Stub colour_box_c::Yellow
*/

void 
colour_box_c::Yellow ( )
{
    colour = yellow;
}

/*
** X-Designer Stub colour_box_c::Blue
*/

void 
colour_box_c::Blue ( )
{
    colour = blue;
}

/*
** X-Designer Stub colour_box_c::Green
*/

void 
colour_box_c::Green ( )
{
    colour = green;
}

/*
** X-Designer Stub colour_box_c::Red
*/

void 
colour_box_c::Red ( )
{
    colour = red;
}

/*
** X-Designer Stub colour_box_c::White
*/

void 
colour_box_c::White ( )
{
    colour = white;
}

/*
** X-Designer Stub colour_box_c::Black
*/

void 
colour_box_c::Black ( )
{
    colour = black;
}

/*

   Leave the X-Designer stub comments so stubs aren't regenerated

** X-Designer Stub drawing_c::DoInput
** X-Designer Stub drawing_c::DoExpose
** X-Designer Stub drawing_c::OnPaint
** X-Designer Stub drawing_c::OnLButtonDown
** X-Designer Stub drawing_c::OnLButtonUp
** X-Designer Stub shell_c::DoExit
*/

