#include <stdio.h>
#include <X11/Xatom.h>
#include <X11/IntrinsicP.h>
#include <X11/Intrinsic.h>
#include <X11/CoreP.h>
#include <X11/Shell.h>
#include <X11/StringDefs.h>

#include <Xm/Xm.h>
#include <Xm/Xrt3d.h>

#define NEAR_MISS 2

int
outside_3d_graph( rval, namep, attrp)
	Xrt3dRegion rval;
	char ** namep;
	char ** attrp;
{
	char * msg;

	switch (rval) {
		case XRT3D_RGN_NOWHERE:
			msg = "NOWHERE";
			break;
		case XRT3D_RGN_IN_LEGEND:
			msg = "LEGEND";
			break;
		case XRT3D_RGN_IN_HEADER:
			msg = "HEADER";
			break;
		case XRT3D_RGN_IN_FOOTER:
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
xrtGet3DData( widget, x, y, namep, attrp)
	Widget widget;
	int    x;
	int    y;
	char ** namep;
	char ** attrp;
{
	Xrt3dMapResult  map;
	Xrt3dRegion     rval;

	rval = Xrt3dMap( widget, x, y, &map);

	if (rval != XRT3D_RGN_IN_GRAPH)
		return outside_3d_graph( rval, namep, attrp);

	if (map.x == XRT3D_HUGE_VAL)
		(void) sprintf ( *namep, "window");
	else
		(void) sprintf ( *namep, "surface");

	if (map.x == XRT3D_HUGE_VAL)
		(void) sprintf ( *attrp, "%d %d", x, y);
	else
		(void) sprintf ( *attrp, "%f %f %f", map.x, map.y, map.z);


	return 1;
}


int
xrt3dXYToName( widget, x, y, namep, attrp)
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

	rval = xrtGet3DData( widget, x, y, namep, attrp);

	return rval;
}

static
char *
nextwhite( s)
	char * s;
{
	for (; s && *s && !isspace(*s); s++);
	if (!s || !*s)
		return (char*)0;
	return s;
}

static
char *
overwhite( s)
	char * s;
{
	for (; s && *s && isspace(*s); s++);
	if (!s || !*s)
		return (char*)0;
	return s;
}


int
xrt3dInsideGraphToXY( widget, attr, xp, yp)
	Widget widget;
	char * attr;
	int * xp;
	int * yp;
{
	Xrt3dMapResult map;

	double x, y, z;
	char * s;
	char * p;

	if (!attr)
		return 0;

	p = overwhite(attr);
	if (!p)
		return 0;

	s = nextwhite( p);
	if (!s)
		return 0;

	*s++ = '\0';

	x = atof( p);

	p = overwhite(s);
	s = nextwhite( p);
	if (!s)
		return 0;

	*s++ = '\0';

	y = atof( p);

	p = overwhite( s);
	s = nextwhite( p);

	if (s)
		*s++ = '\0';

	z = atof( p);

	Xrt3dUnmap( widget, x, y, z, &map);

	if (map.pix_x == -1 || map.pix_y == -1) {
		return 0;
	}
	*xp = map.pix_x;
	*yp = map.pix_y;

       return 1;
}

int
xrt3dOutsideGraphToXY( widget,  attr, xp, yp)
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
xrt3dxyToXY( widget,  attr, xp, yp)
	Widget widget;
	char * attr;
	int * xp;
	int * yp;
{
	char * s;
	char * p;
	int x, y;

	p = overwhite( attr);
	if (!p)
		return 0;
	s = nextwhite( p);
	if (!s)
		return 0;
	*s++ = '\0';
	*xp = atoi(p);

	p = overwhite(s);
	s = nextwhite(p);
	if (s)
		*s = '\0';

	*yp = atoi(p);

	return 1;
}

int
xrt3dNameToXY( widget, name, attr, xp, yp)
	Widget widget;
	char * name;
	char * attr;
	int * xp;
	int * yp;
{
	name = overwhite(name);
	attr = overwhite(attr);

	if (strcmp(name, "outside") == 0)
		return xrt3dOutsideGraphToXY( widget, attr, xp, yp);
	if (strcmp(name, "window") == 0)
		return xrt3dxyToXY( widget, attr, xp, yp);

	return xrt3dInsideGraphToXY( widget, attr, xp, yp);
}
