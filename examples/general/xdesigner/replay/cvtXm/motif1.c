#include <stdio.h>
#include <X11/StringDefs.h>
#include <X11/IntrinsicP.h>
#include <X11/CoreP.h>
#include <Xm/Xm.h>

/* scales are currently handled as a special case of ScrollBar. */

#ifndef   _NO_PROTO
int xdsScrollBarNameToXy( Widget widget, char * name, char * attr, int * xp, int * yp)
#else  /* _NO_PROTO */
int xdsScrollBarNameToXy( widget, name, attr, xp, yp)
	Widget widget;
	char * name;
	char * attr;
	int  * xp;
	int * yp;
#endif /* _NO_PROTO */
{
	Widget pa = XtParent( widget);

	if (xdsIsScale( pa))
		return xdsScaleNameToXy( pa, name, attr, xp, yp);

	return xdsScrollBarNameToXy1( widget, name, attr, xp, yp);
}

#ifndef   _NO_PROTO
int xdsScrollBarXyToName( Widget widget, int x, int y, char ** namep, char ** attrp)
#else  /* _NO_PROTO */
int xdsScrollBarXyToName( widget, x, y, namep, attrp)
	Widget widget;
	int x, y;
	char ** namep;
	char ** attrp;
#endif /* _NO_PROTO */
{
	Widget pa = XtParent( widget);

	if (xdsIsScale( pa))
		return xdsScaleXyToName( pa, x, y, namep, attrp);

	return xdsScrollBarXyToName1( widget, x, y, namep, attrp);
}

#ifndef   _NO_PROTO
int xdsScrollBarNameToXy1( Widget widget, char * name, char * attr, int  * xp, int * yp)
#else  /* _NO_PROTO */
int xdsScrollBarNameToXy1( widget, name, attr, xp, yp)
	Widget widget;
	char * name;
	char * attr;
	int  * xp;
	int * yp;
#endif /* _NO_PROTO */
{
	int value;
	int slider_size;
	int increment;
	int page_increment;

	*xp = -1;
	*yp = -1; /* dont send events */

	XmScrollBarGetValues( widget, &value, &slider_size, &increment, &page_increment);

	value = atoi( attr);

	XmScrollBarSetValues( widget, value, slider_size, increment, page_increment, True);

	return 1;
}

#ifndef   _NO_PROTO
int xdsScrollBarXyToName1( Widget widget, int x, int y, char ** namep, char ** attrp)
#else  /* _NO_PROTO */
int xdsScrollBarXyToName1( widget, x, y, namep, attrp)
	Widget widget;
	int x, y;
	char ** namep;
	char ** attrp;
#endif /* _NO_PROTO */
{
	static char val[20];

	Arg   arg ;
	int   value;
	char *s = XtName( widget);

	if (s && *s && (strcmp(s, "Scrollbar") == 0)) {
		if (xdsIsScaleChild( widget))
			return xdsScaleXyToName( XtParent(widget), x, y, namep,attrp);
	}

	XtSetArg( arg, XmNvalue, &value); 
	XtGetValues( widget, &arg, 1);

	(void) sprintf ( val, "%d", value);

	*namep = "value";
	*attrp = val;

	return 1;
}

#ifndef   _NO_PROTO
int xdsIsScaleChild( Widget w)
#else  /* _NO_PROTO */
int xdsIsScaleChild( w)
	Widget w;
#endif /* _NO_PROTO */
{
	if (!(w = XtParent(w)))
		return 0;
	return xdsIsScale(w);
}

#ifndef   _NO_PROTO
int xdsIsScale( Widget w)
#else  /* _NO_PROTO */
int xdsIsScale( w)
	Widget w;
#endif /* _NO_PROTO */
{
	return xdsIsType( w, "XmScale");
}

#ifndef   _NO_PROTO
int xdsIsType( Widget w, char * type)
#else  /* _NO_PROTO */
int xdsIsType( w, type)
	Widget w;
	char * type;
#endif /* _NO_PROTO */
{
	CorePart *  cp;
	WidgetClass wc;
	CoreClassPart * cdata;

	cp = &(w->core);
	wc = cp->widget_class;
	cdata = &(wc->core_class);

	return (strcmp(cdata->class_name, type) == 0);
}

#ifndef   _NO_PROTO
int xdsScaleNameToXy( Widget widget, char * name, char * attr, int  * xp, int * yp)
#else  /* _NO_PROTO */
int xdsScaleNameToXy( widget, name, attr, xp, yp)
	Widget widget;
	char * name;
	char * attr;
	int  * xp;
	int * yp;
#endif /* _NO_PROTO */
{
	int value;

	*xp = -1;
	*yp = -1; /* dont send events */

	value = atoi( attr);

	XmScaleSetValue( widget, value);

	return 1;
}

#ifndef   _NO_PROTO
int xdsScaleXyToName( Widget widget, int x, int y, char ** namep, char ** attrp)
#else  /* _NO_PROTO */
int xdsScaleXyToName( widget, x, y, namep, attrp)
	Widget widget;
	int x, y;
	char ** namep;
	char ** attrp;
#endif /* _NO_PROTO */
{
	static char val[20];

	Arg arg;
	int value;

	XtSetArg( arg, XmNvalue, &value); 
	XtGetValues( widget, &arg, 1);

	(void) sprintf ( val, "%d", value);

	*namep = "value";
	*attrp = val;

	return 1;
}

#ifndef   _NO_PROTO
int xdsDaNameToXy( Widget widget, char * name, char * attr, int  * xp, int * yp)
#else  /* _NO_PROTO */
int xdsDaNameToXy( widget, name, attr, xp, yp)
	Widget widget;
	char * name;
	char * attr;
	int  * xp;
	int * yp;
#endif /* _NO_PROTO */
{
	if (!isdigit(*name))
		return 0;
	if (!isdigit(*attr))
		return 0;

	*xp = atoi(name);
	*yp = atoi(attr);

	return 1;
}

#ifndef   _NO_PROTO
int xdsDaXyToName( Widget widget, int x, int y, char ** namep, char ** attrp)
#else  /* _NO_PROTO */
int xdsDaXyToName( widget, x, y, namep, attrp)
	Widget widget;
	int x, y;
	char ** namep;
	char ** attrp;
#endif /* _NO_PROTO */
{
	static char xs[8];
	static char ys[8];

	(void) sprintf ( xs, "%d", x);
	(void) sprintf ( ys, "%d", y);

	*namep = xs;
	*attrp = ys;

	return 1;
}
