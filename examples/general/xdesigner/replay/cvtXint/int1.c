#include <stdio.h>
#include <X11/Xatom.h>
#include <X11/IntrinsicP.h>
#include <X11/Intrinsic.h>
#include <X11/CoreP.h>
#include <X11/Shell.h>
#include <X11/StringDefs.h>

#include <Xint/EditTable.h>


/* the INT EditTable conversion routines */
static
void
intTableDimensions( widget, colp, rowp)
	Widget widget;
	int * colp;
	int * rowp;
{
	Arg args[3];
	Cardinal ac = 0;

	XtSetArg( args[ac], XmNnumberOfColumns, colp); ac++;
	XtSetArg( args[ac], XmNnumberOfRows, rowp); ac++;
	XtGetValues( widget, args, ac);
}



void
intRowColToXY( widget, row, col, xp, yp)
	Widget widget;
	int    row;
	int     col;
	int *   xp;
	int *   yp;
{
	int xo, yo;
	int w, h;

	*xp = 0;
	*yp = 0;

	(void) XintEditTableGetCellGeometry( widget, col, row, &xo, &yo, &w, &h);

	*xp = xo + (w/2);
	*yp = yo + (h/2);

	return;
}

void
intXYToRowCol( widget, x, y, rowp, colp)
	Widget widget;
	int    x;
	int    y;
	int   *rowp;
	int   *colp;
{
	int xc = 1;
	int yc = 1;
	int dummy, dummy1;
	int w, h;
	int xo, yo;
	int max_cols = 0;
	int max_rows = 0;

	intTableDimensions( widget, &max_cols, &max_rows);

	while ( xc <= max_cols) {
		(void) XintEditTableGetCellGeometry( widget, xc, yc, &xo, &dummy, &w, &dummy1);

		if (x > xo && (x < xo + w))
			break;
		xc++;
	}

	while ( yc <= max_rows) {
		(void) XintEditTableGetCellGeometry( widget, xc, yc, &dummy, &yo, &dummy1, &h);
		if (y > yo && (y < yo + h))
			break;
		yc++;
	}
	*rowp = yc;
	*colp = xc;

	return;
}



int
intEditTableXYToName( widget, x, y, namep, attrp)
	Widget widget;
	int x, y;
	char ** namep;
	char ** attrp;
{
	static char col[15];
	static char row[15];

	int tcol = 0;
	int trow = 0;

	intXYToRowCol( widget, x, y, &trow, &tcol);

	(void) sprintf ( col, "col#%d", tcol);
	(void) sprintf ( row, "row#%d", trow);

	*namep = row;
	*attrp = col;

	return 1;
}

int
intEditTableNameToXY( widget, name, attr, xp, yp)
	Widget widget;
	char * name;
	char * attr;
	int * xp;
	int * yp;
{
	int rowval = atoi(name+4);
	int colval = atoi(attr+4);

	intRowColToXY( widget, rowval, colval, xp, yp);

	return 1;
}
