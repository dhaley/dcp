#include <stdio.h>
#include <X11/StringDefs.h>
#include <X11/Intrinsic.h>
#include <Xm/Xm.h>

#ifndef   _NO_PROTO
Boolean xdsTextPutInput( Widget widget, char * text)
#else  /* _NO_PROTO */
Boolean xdsTextPutInput( widget, text)
	Widget widget;
	char * text;
#endif /* _NO_PROTO */
{
	Arg arg ;

	if (!widget)
		return False;

	XtSetArg( arg, XmNvalue, text);
	XtSetValues( widget, &arg, 1);

	return False;
}

#ifndef   _NO_PROTO
char * xdsTextGetInput( Widget widget)
#else  /* _NO_PROTO */
char * xdsTextGetInput( widget)
	Widget widget;
#endif /* _NO_PROTO */
{
	Arg    arg ;
	char * value = (char*)0;

	if (!widget)
		return (char*)0;

	XtSetArg( arg, XmNvalue, &value);
	XtGetValues( widget, &arg, 1);

	return value;
}

/* this module is not compiled by default.

   For most test situations we have found that treating text fields
   as simple data entry fields, where you just REPLACE the text in it
   is the safest and most effective technique.

   This module is for specialised usage of the Text widget - eg for
   testing an editor
*/

#ifdef    HANDLE_TEXT

#ifndef   _NO_PROTO
int xdsTextNameToXy( Widget widget, char * name, char * attr, int  * xp, int * yp)
#else  /* _NO_PROTO */
int xdsTextNameToXy( widget, name, attr, xp, yp)
	Widget widget;
	char * name;
	char * attr;
	int  * xp;
	int * yp;
#endif /* _NO_PROTO */
{
	Position x = (Position)0;
	Position y = (Position)0;
	XmTextPosition pos = atoi(attr);

	XmTextShowPosition( widget, pos);
	if (!XmTextPosToXY( widget, pos, &x, &y))
		return 0;

	*xp = x;
	*yp = y;

	return 1;
}

#ifndef   _NO_PROTO
int xdsTextFieldNameToXy( Widget widget, char * name, char * attr, int  * xp, int * yp)
#else  /* _NO_PROTO */
int xdsTextFieldNameToXy( widget, name, attr, xp, yp)
	Widget widget;
	char * name;
	char * attr;
	int  * xp;
	int * yp;
#endif /* _NO_PROTO */
{
	Position x = (Position)0;
	Position y = (Position)0;
	XmTextPosition pos = atoi(attr);

	XmTextFieldShowPosition( widget, pos);
	if (!XmTextFieldPosToXY( widget, pos, &x, &y))
		return 0;

	*xp = x;
	*yp = y;

	return 1;
}

#ifndef   _NO_PROTO
static int _xdsTextXYToName( Widget widget, XmTextPosition pos, char ** namep, char ** attrp)
#else  /* _NO_PROTO */
static int _xdsTextXYToName( widget, pos, namep, attrp)
	Widget widget;
	XmTextPosition pos;
	char ** namep;
	char ** attrp;
#endif /* _NO_PROTO */
{
	static char posdata[20];

	(void) sprintf ( posdata, "%d", pos);

	*namep = "position";
	*attrp = posdata;

	return 1;
}

#ifndef   _NO_PROTO
int xdsTextXyToName( Widget widget, int x, int y, char ** namep, char ** attrp)
#else  /* _NO_PROTO */
int xdsTextXyToName( widget, x, y, namep, attrp)
	Widget widget;
	int x, y;
	char ** namep;
	char ** attrp;
#endif /* _NO_PROTO */
{
	return _xdsTextXYToName( widget, XmTextXYToPos( widget, x, y), namep, attrp);
}

#ifndef   _NO_PROTO
int xdsTextFieldXyToName( Widget widget, int x, int y, char ** namep, char ** attrp)
#else  /* _NO_PROTO */
int xdsTextFieldXyToName( widget, x, y, namep, attrp)
	Widget widget;
	int x, y;
	char ** namep;
	char ** attrp;
#endif /* _NO_PROTO */
{
	return _xdsTextXYToName( widget, XmTextFieldXYToPos( widget, x, y), namep, attrp);
}
#endif /* HANDLE_TEXT */
