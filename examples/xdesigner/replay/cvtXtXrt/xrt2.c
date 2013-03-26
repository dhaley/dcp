#include <stdio.h>
#include <X11/Xatom.h>
#include <X11/IntrinsicP.h>
#include <X11/Intrinsic.h>
#include <X11/CoreP.h>
#include <X11/Shell.h>
#include <X11/StringDefs.h>

#include <Xm/Xm.h>
#include <Xm/XrtGraph.h>

#define NEAR_MISS 2

int
xrtGetGraphData( widget, x, y, namep, attrp)
	Widget widget;
	int    x;
	int    y;
	char ** namep;
	char ** attrp;
{
	XrtPickResult pmap;
	XrtRegion     rval;

	rval = XrtPick( widget, XRT_DATASET1| XRT_DATASET2,
				x, y,
				&pmap,
				XRT_XFOCUS | XRT_YFOCUS);

	if (rval != XRT_RGN_IN_GRAPH)
		return outside_graph( rval, namep, attrp);

	if (pmap.distance > NEAR_MISS)
		return inside_graph( widget, x, y, namep, attrp);

	(void) sprintf ( *namep, "DS%d/%d", pmap.dataset, pmap.set+1);
	(void) sprintf ( *attrp, "#%d", pmap.point + 1);

	return 1;
}

int
outside_graph( rval, namep, attrp)
	XrtRegion rval;
	char ** namep;
	char ** attrp;
{
	char * msg;

	switch (rval) {
		case XRT_RGN_NOWHERE:
			msg = "NOWHERE";
			break;
		case XRT_RGN_IN_LEGEND:
			msg = "LEGEND";
			break;
		case XRT_RGN_IN_HEADER:
			msg = "HEADER";
			break;
		case XRT_RGN_IN_FOOTER:
			msg = "FOOTER";
			break;
		default:
			msg = "UNKNOWN";
			break;
	}

	(void) sprintf ( *namep, "outside");
	(void) sprintf ( *attrp, msg);

	return 1;
}


int
inside_graph( widget, x, y, namep, attrp)
	Widget widget;
	int x, y;
	char ** namep;
	char ** attrp;
{
	XrtMapResult  map;
	XrtRegion     rval;

	rval = XrtMap( widget, 1, x, y, &map);

	if (rval != XRT_RGN_IN_GRAPH)
		return outside_graph( rval, namep, attrp);


	if (map.x == XRT_HUGE_VAL)
		(void) sprintf ( *namep, "x#%d", x);
	else
		(void) sprintf ( *namep, "x=%f", map.x);

	if (map.y == XRT_HUGE_VAL)
		(void) sprintf ( *attrp, "y#%d", y);
	else
		(void) sprintf ( *attrp, "y=%f", map.y);


	return 1;
}


int
xrtGraphXYToName( widget, x, y, namep, attrp)
	Widget widget;
	int x, y;
	char ** namep;
	char ** attrp;
{
	int rval = 0;
	static char namebuf[64];
	static char attrbuf[64];

	*namep = namebuf;
	*attrp = attrbuf;

	rval = xrtGetGraphData( widget, x, y, namep, attrp);

	return rval;
}

Boolean
xrtParseData( name, attr, dp, sp, pp)
	char * name;
	char * attr;
	int  * dp;
	int * sp;
	int * pp;
{
	char * p;

	if (*(name+3) != '/')
		return False;
	*(name+3) = '\0';
	*dp = atoi(name+2);
	*(name+3) = '/';
	*sp = atoi(name+4);

	if (*attr != '#')
		return False;

	*pp = atoi(attr+1);

	*sp = *sp -1;
	*pp = *pp -1;

	return True;
}

int
xrtGraphDataToXY( widget, name, attr, xp, yp)
	Widget widget;
	char * name;
	char * attr;
	int * xp;
	int * yp;
{
	XrtPickResult pick;
	int dataset;
	int set;
	int point;

	if (!xrtParseData( name, attr, &dataset, &set, &point))
		return 0;

	XrtUnpick( widget, dataset, set, point, &pick);

	if (pick.pix_x == -1 || pick.pix_y == -1) {
		return 0;
	}

	*xp = pick.pix_x;
	*yp = pick.pix_y;

	return 1;
}

int
xrtGraphInsideGraphToXY( widget, name, attr, xp, yp)
	Widget widget;
	char * name;
	char * attr;
	int * xp;
	int * yp;
{
	XrtMapResult map;
	float x_axis = XRT_HUGE_VAL;
	float y_axis = XRT_HUGE_VAL;

	*xp = 0;
	*yp = 0;

	if (*name != 'x')
		return 0;
	if (*(name+1) == '#')
		*xp = atoi(name+2);
	else
		x_axis = atof(name+2);

	if (*attr != 'y')
		return 0;

	if (*(attr+1) == '#')
		*yp = atoi(attr+2);
	else
		y_axis = atof(attr+2);

       if (*xp && *yp)
		return 1;

       XrtUnmap( widget, 1, x_axis, y_axis, &map);

       if (!*xp) {
		if (map.pix_x == -1)
			return 0;
		*xp = map.pix_x;
       }

       if (!*yp) {
		if (map.pix_y == -1)
			return 0;
		*yp = map.pix_y;
       }

       return 1;
}

int
xrtGraphOutsideGraphToXY( widget,  attr, xp, yp)
	Widget widget;
	char * attr;
	int * xp;
	int * yp;
{
	*xp = -1;
	*yp = -1;

	return 1;
}

int
xrtGraphNameToXY( widget, name, attr, xp, yp)
	Widget widget;
	char * name;
	char * attr;
	int * xp;
	int * yp;
{
	if (strncmp(name, "DS", 2) == 0)
		return xrtGraphDataToXY( widget, name, attr, xp, yp);
	if (strcmp(name, "outside") == 0)
		return xrtGraphOutsideGraphToXY( widget, attr, xp, yp);

	return xrtGraphInsideGraphToXY( widget, name, attr, xp, yp);
}
