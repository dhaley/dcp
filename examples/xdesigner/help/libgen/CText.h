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
** sccsid = "@(#)helpGuru/libgen/CText.h	1.1" -- 95/12/13
*/

#ifndef _H_CText
#define _H_CText

#include <Xm/Xm.h>
#include "CCmdHandler.h"

class CText : public CCmdHandler {
public:
	Widget itsWidget;

	CText() { }
	CText(Widget aWidget) { itsWidget = aWidget; }
	Boolean IsEditable();
	virtual Boolean OnCommand(long cmd);
	virtual Boolean OnUpdateCommand(long cmd);
};

#endif
