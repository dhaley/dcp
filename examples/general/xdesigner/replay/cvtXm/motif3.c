#include <stdio.h>
#include <X11/StringDefs.h>
#include <X11/Intrinsic.h>
#include <Xm/Xm.h>
#include "xdsObject.h"

#ifndef   _NO_PROTO
Boolean xdsCvtSetListError( int n)
#else  /* _NO_PROTO */
Boolean xdsCvtSetListError( n)
	int n;
#endif /* _NO_PROTO */
{
	static bool_f call = (bool_f)0;

	if (!call) {
		call = (bool_f) xdsGetAnyFunction(XDSNsetListErrorFunction);
		if (call == (bool_f)0)
			return False;
	}
	return (*call) ( n);
}

#ifndef   _NO_PROTO
int xdsCvtListFailure(void)
#else  /* _NO_PROTO */
int xdsCvtListFailure()
#endif /* _NO_PROTO */
{
	static int_f call = (int_f)0;

	if (!call) {
		call = (int_f) xdsGetAnyFunction(XDSNlistFailureFunction);
		if (call == (int_f)0)
			return 0;
	}
	return (*call) ();
}

#ifndef   _NO_PROTO
Boolean xdsCvtGetXmListEntries( Widget widget, XmString ** listp, int * countp)
#else  /* _NO_PROTO */
Boolean xdsCvtGetXmListEntries( widget, listp, countp)
	Widget widget;
	XmString ** listp;
	int       * countp;
#endif /* _NO_PROTO */
{
	static bool_f call = (bool_f)0;

	if (!call) {
		call = (bool_f) xdsGetAnyFunction(XDSNgetXmListEntriesFunction);
		if (call == (bool_f)0)
			return False;
	}
	return (*call) ( widget, listp, countp);
}

#ifndef   _NO_PROTO
int xdsCvtSetListItem( Widget widget, int pos)
#else  /* _NO_PROTO */
int xdsCvtSetListItem( widget, pos)
	Widget widget;
	int pos;
#endif /* _NO_PROTO */
{
	static int_f call = (int_f)0;

	if (!call) {
		call = (int_f) xdsGetAnyFunction(XDSNsetListItemFunction);
		if (call == (int_f)0)
			return 0;
	}
	return (*call) ( widget, pos);
}

#ifndef   _NO_PROTO
int xdsCvtIsInList( Widget widget, char * name)
#else  /* _NO_PROTO */
int xdsCvtIsInList( widget, name)
	Widget widget;
	char * name;
#endif /* _NO_PROTO */
{
	static int_f call = (int_f)0;

	if (!call) {
		call = (int_f) xdsGetAnyFunction(XDSNisInListFunction);
		if (call == (int_f)0)
			return 0;
	}
	return (*call) ( widget, name);
}

#ifndef   _NO_PROTO
char * xdsCvtXmStringToString( XmString xmstring)
#else  /* _NO_PROTO */
char * xdsCvtXmStringToString( xmstring)
	XmString xmstring;
#endif /* _NO_PROTO */
{
	static str_f call = (str_f)0;

	if (!call) {
		call = (str_f) xdsGetAnyFunction(XDSNxmStringToStringFunction);
		if (call == (str_f)0)
			return 0;
	}
	return (*call) ( xmstring);
}
