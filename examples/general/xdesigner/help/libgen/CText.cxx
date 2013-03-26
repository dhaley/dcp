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
static char *sccsid = {"@(#)helpGuru/libgen/CText.cxx	1.2"} ; /* 97/01/02 */
#endif /* lint && NOSCCS */

#include <Xm/Xm.h>
#include <Xm/Text.h>
#include <Xm/CutPaste.h>

#include "Commands.h"
#include "CText.h"

Boolean
CText::IsEditable()
{
	Boolean editable;
	XtVaGetValues(itsWidget, XmNeditable, &editable, NULL);
	return editable;
}

Boolean
CText::OnCommand(long cmd)
{
	if (XmGetFocusWidget(itsWidget) == itsWidget) {
		switch (cmd) {
		case cmdCut:
 			return XmTextCut(itsWidget, XtLastTimestampProcessed(XtDisplay(itsWidget)));
		case cmdCopy:
			return XmTextCopy(itsWidget, XtLastTimestampProcessed(XtDisplay(itsWidget)));
		case cmdPaste:
			return XmTextPaste(itsWidget);
		case cmdClear:
			return XmTextRemove(itsWidget);
		}
	}
	return False;
}

Boolean
CText::OnUpdateCommand(long cmd)
{
	unsigned long length;
	long left, right;
	int status;

	if (XmGetFocusWidget(itsWidget) == itsWidget) {
		switch (cmd) {
		case cmdUndo:
			return False;
		case cmdCut:
		case cmdClear:
			if (!IsEditable())
				return False;
			// Fall into...
		case cmdCopy:
 			if (XmTextGetSelectionPosition(itsWidget, &left, &right))
				return left != right;
			else
				return False;
		case cmdPaste:
			if (!IsEditable())
				return False;
      			status = XmClipboardInquireLength(XtDisplay(itsWidget), XtWindow(itsWidget), "STRING", &length);

      			if (status == ClipboardNoData || length == 0) {
	 			status = XmClipboardInquireLength(XtDisplay(itsWidget), XtWindow(itsWidget), "COMPOUND_TEXT", &length);
	 			if (status == ClipboardNoData || length == 0 || status == ClipboardLocked)
					return False;
      			} else if (status == ClipboardLocked)
				return False;
	 		return True;
		}
	}
	return False;
}

