/* X-Designer
** (c) 1992, 1993, 1994, 1995, 1996
** Imperial Software Technology (IST),
** 95 London Street,
** Reading,
** Berkshire,
** United Kingdom RG1 4QA.
**
** Telephone: +44 1734 587055
** Fax:       +44 1734 589005
** Email:     support@ist.co.uk
*/


/*
** sccsid = "@(#)helpGuru/libgen/CWaitCursor.h	1.1" -- 95/12/13
*/

#ifndef _H_CWaitCursor
#define _H_CWaitCursor

#include <Xm/Xm.h>

class CWaitCursor {
public:
	Widget itsWidget;

	CWaitCursor(Widget w);
	~CWaitCursor();

	static Cursor cWaitCursor;
};

#endif

