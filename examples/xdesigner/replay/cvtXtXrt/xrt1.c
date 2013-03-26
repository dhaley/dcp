#include <stdio.h>
#include <X11/Xatom.h>
#include <X11/IntrinsicP.h>
#include <X11/Intrinsic.h>
#include <X11/CoreP.h>
#include <X11/Shell.h>
#include <X11/StringDefs.h>

#include <Xm/Xm.h>
#include <Xm/XrtTable.h>


int
xrtTableXYToName( widget, x, y, namep, attrp)
	Widget widget;
	int x, y;
	char ** namep;
	char ** attrp;
{
	return 0;
}

int
xrtTableNameToXY( widget, name, attr, xp, yp)
	Widget widget;
	char * name;
	char * attr;
	int * xp;
	int * yp;
{
	return 0;
}
