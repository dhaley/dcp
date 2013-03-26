#include <stdio.h>
#include <X11/StringDefs.h>
#include <X11/Intrinsic.h>
#include <Xm/Xm.h>
#include "xdsObject.h"

#ifndef   _NO_PROTO
static char * xdsInsertNewLines(char *);
static char * xdsRemoveNewLines(char *);
	
extern char *  xdsCvtXmStringToString(XmString);
extern Boolean xdsCvtSetListError(int);
extern int     xdsCvtListFailure(void);
extern int     xdsCvtSetListItem(Widget, int);
extern Boolean xdsCvtGetXmListEntries(Widget, XmString **, int *);
#else  /* _NO_PROTO */
static char * xdsInsertNewLines();
static char * xdsRemoveNewLines();

extern char *  xdsCvtXmStringToString();
extern Boolean xdsCvtSetListError();
extern int     xdsCvtListFailure();
extern int     xdsCvtSetListItem();
extern Boolean xdsCvtGetXmListEntries();
#endif /* _NO_PROTO */

#ifndef   _NO_PROTO
int xdsListNameToXy( Widget widget, char * name, char * attr, int  * xp, int * yp)
#else  /* _NO_PROTO */
int xdsListNameToXy( widget, name, attr, xp, yp)
	Widget widget;
	char * name;
	char * attr;
	int  * xp;
	int * yp;
#endif /* _NO_PROTO */
{
	Position x, y;
	Dimension w, h;

	int pos;
	int len = 0;
	int n;
	char * s;
	int instance = 1;
	XmString * list = (XmString*)0;
	XmString   item;

	if ((instance = atoi(attr)) == 0) {
		xdsCvtSetListError(LIST_BAD_INSTANCE);
		return xdsCvtListFailure();
	}

	instance--;

	(void) xdsInsertNewLines( name);
	if (!xdsCvtGetXmListEntries( widget, &list, &len)) {
		xdsCvtSetListError(LIST_EMPTY_LIST);
		(void) xdsRemoveNewLines( name);
		return xdsCvtListFailure();
	}


	for ( n = 0; n < len; n++) {
		s = xdsCvtXmStringToString(list[n]);
		if (strcmp( name, s) != 0)
			continue;
		if (instance--)
			continue;
		break;
	}

	if (n == len) {
		xdsCvtSetListError(LIST_ELEMENT_NOT_FOUND);
		(void) xdsRemoveNewLines( name);
		return xdsCvtListFailure();
	}

	(void) xdsCvtSetListItem( widget, n+1);

	if (!XmListPosToBounds( widget, n+1, &x, &y, &w, &h)) {
		xdsCvtSetListError(LIST_OUT_OF_BOUNDS);
		(void) xdsRemoveNewLines( name);
		return xdsCvtListFailure();
	}

	*xp = x + (w/2);
	*yp = y + (h/2);

	(void) xdsRemoveNewLines( name);
	return 1;
}

#ifndef   _NO_PROTO
int xdsListXyToName( Widget widget, int x, int y, char ** namep, char ** attrp)
#else  /* _NO_PROTO */
int xdsListXyToName( widget, x, y, namep, attrp)
	Widget widget;
	int x, y;
	char ** namep;
	char ** attrp;
#endif /* _NO_PROTO */
{
#ifndef   _NO_PROTO
	extern int XmListYToPos(Widget, Position);
#else  /* _NO_PROTO */
	extern int XmListYToPos();
#endif /* _NO_PROTO */

	static char name[255];
	static char count[20];

	char * p;

	int pos;
	int len = 0;
	int n;

	int instance = 1;
	int  pos_count = 0;
	int *pos_list = (int*)0;

	XmString * list = (XmString*)0;
	XmString   item;

	if (!xdsCvtGetXmListEntries( widget,&list, &len)) {
		return xdsCvtListFailure();
	}

	pos = XmListYToPos( widget, (Position)y);

	if (pos < 0 || pos > len) {
		xdsCvtSetListError(LIST_OUT_OF_BOUNDS);
		return xdsCvtListFailure();
	}

	item = list[--pos];


	p = xdsCvtXmStringToString(item);
	if (!p)
		return 0;

	if (pos == 0)
		pos_count = 0;
	else if (XmListGetMatchPos( widget, item, &pos_list, &pos_count)) {
		for (n = 0; n < pos_count; n++) {
			if (pos_list[n] < pos)
				instance++;
		}
		if (pos_list)
			XtFree((void*)pos_list);

	} else
		return 0;


	(void) sprintf ( count, "%d", instance);

	(void) strcpy ( name, xdsRemoveNewLines(p));

	*namep  = name;
	*attrp  = count;

	return 1;
}

#ifndef   _NO_PROTO
static char * xdsInsertNewLines( char * s)
#else  /* _NO_PROTO */
static char * xdsInsertNewLines( s)
	char * s;
#endif /* _NO_PROTO */
{
	char * p;

	for (p = s; p && *p; p++) {
		if ( *p == 'n' && *(p-1) == '\\')
			*p = '\n';
	}

	return s;
}

#ifndef   _NO_PROTO
static char * xdsRemoveNewLines( char * s)
#else  /* _NO_PROTO */
static char * xdsRemoveNewLines( s)
	char * s;
#endif /* _NO_PROTO */
{
	char * p;

	for (p = s; p && *p; p++) {
		if ( *p == '\n' && *(p-1) == '\\')
			*p = 'n';
	}

	return s;
}
