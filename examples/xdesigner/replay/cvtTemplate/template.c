#include <stdio.h>
#include <X11/Xatom.h>
#include <X11/Intrinsic.h>
#include <X11/Shell.h>
#include <X11/StringDefs.h>

/*
This is a prototype converter
*/


int
templateXYToName( widget, x, y, namep, attrp)
	Widget widget;
	int x, y;
	char ** namep;
	char ** attrp;
{
	static char n[15];
	static char a[15];

	(void) sprintf ( n, "bicycle-widget");
	(void) sprintf ( a, "front-wheel");

	*namep = n;
	*attrp = a;

	return 1;
}

int
templateNameToXY( widget, name, attr, xp, yp)
	Widget widget;
	char * name;
	char * attr;
	int * xp;
	int * yp;
{
	if (strcmp(name, "bicycle-widget") != 0)
		return 0;
	if (strcmp(attr, "front-wheel") != 0)
		return 0;


	*xp = -1;   /* this is cheating. We're not replaying the events, */
	*yp = -1;   /* because the bicycle widget isnt real */
		    /* if the converter returns NEGATIVE values it means D-I-Y */

	return 1;
}
