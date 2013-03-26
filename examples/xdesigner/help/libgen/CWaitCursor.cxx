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

#if !defined(lint) && !defined(NOSCCS)
static char *sccsid = {"@(#)helpGuru/libgen/CWaitCursor.cxx	1.1"} ; /* 95/12/13 */
#endif /* lint && NOSCCS */

#include "CWaitCursor.h"
#include <X11/cursorfont.h>
#include <X11/Intrinsic.h>
#include <X11/IntrinsicP.h>
#include <X11/Shell.h>

CWaitCursor::CWaitCursor(Widget w)
{
	int i;

	itsWidget = w;
	if (!cWaitCursor)
		cWaitCursor = XCreateFontCursor(XtDisplay(w), XC_watch);
	Display *display = XtDisplay ( itsWidget );
	XDefineCursor ( display, XtWindow ( itsWidget ), cWaitCursor );
	for ( i = 0; i < itsWidget->core.num_popups; i++ )
		if ( XtIsRealized ( itsWidget->core.popup_list[i] ) )
			XDefineCursor ( display, XtWindow ( itsWidget->core.popup_list[i] ), cWaitCursor );
	XFlush ( XtDisplay ( itsWidget ) );

}

CWaitCursor::~CWaitCursor()
{
	int i;
	Display *display = XtDisplay ( itsWidget );

	XUndefineCursor ( display, XtWindow ( itsWidget ) );
	for ( i = 0; i < itsWidget->core.num_popups; i++ )
		if ( XtIsRealized ( itsWidget->core.popup_list[i] ) )
			XUndefineCursor ( display, XtWindow ( itsWidget->core.popup_list[i] ) );
}

Cursor CWaitCursor::cWaitCursor;

