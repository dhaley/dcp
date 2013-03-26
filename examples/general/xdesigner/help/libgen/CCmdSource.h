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
** sccsid = "@(#)helpGuru/libgen/CCmdSource.h	1.1" -- 95/12/13
*/

#ifndef _H_CCmdSource
#define _H_CCmdSource

#include <Xm/Xm.h>

class CCmdSource {
public:
	Widget itsWidget;
	CCmdSource next;

	virtual void Enable(Boolean bEnable) { XtSetSensitive(itsWidget, bEnable); }
	virtual void Check(Boolean bCheck) { XtToggleButtonSetState(itsWidget, bCheck); }
	virtual void Show(Boolean bShow) { if (bShow) XtMapWidget(itsWidget) else XtUnmapWidget(itsWidget); }
	virtual void SetText(const char *text) { }
};

#endif

