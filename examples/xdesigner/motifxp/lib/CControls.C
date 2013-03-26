#include <Xm/Xm.h>
#include <Xm/Label.h>
#include <Xm/ToggleB.h>
#include <Xm/ToggleBG.h>
#include <xdclass.h>
#include <utils.h>

#include <iostream.h>

#include <Xm/LabelG.h>

static void xd_set_XmLabel_window_text(LPCSTR lpszString, Widget rootwidget)
{
    // Set the text on an XmLabel or derivative

    if ((rootwidget != NULL) && (XmIsLabel(rootwidget) || XmIsLabelGadget(rootwidget)))
    {
	// The default parse table converts \n and \t for us.
#if       (XmVERSION > 1)
	XmString s = XmStringGenerate((XtPointer) lpszString, XmFONTLIST_DEFAULT_TAG, XmCHARSET_TEXT, NULL) ;
#else  /* (XmVERSION > 1) */
	// We use XmStringCreateLtoR here so that it converts \n to separator
	XmString s = XmStringCreateLtoR((String)lpszString, XmFONTLIST_DEFAULT_TAG) ;
#endif /* (XmVERSION > 1) */

	XtVaSetValues(rootwidget, XmNlabelString, s, NULL) ;

	XmStringFree(s) ;
    }
}

static int xd_get_XmLabel_window_text(LPSTR lpszStringBuf, int nMaxCount, Widget rootwidget)
{
    // Get the text from an XmLabel or derivative
    if ((rootwidget == NULL) || !(XmIsLabel(rootwidget) || XmIsLabelGadget(rootwidget)))
	return 0 ;

    char *label = xd_text_from_XmLabel(rootwidget) ;

    (void) strncpy(lpszStringBuf, label, nMaxCount - 1) ;

    lpszStringBuf[nMaxCount-1] = '\0' ;
    XtFree(label) ;

    return strlen(lpszStringBuf) ;
}

static int xd_get_XmLabel_window_text_length(Widget rootwidget)
{
    // Get the length of the text from an XmLabel or derivative
    if ((rootwidget == NULL) || !(XmIsLabel(rootwidget) || XmIsLabelGadget(rootwidget)))
	return 0 ;

    char *label = xd_text_from_XmLabel(rootwidget) ;
    int   i     = strlen(label) ;

    XtFree(label) ;

    return i ;
}

void CStatic::xd_set_window_text(LPCSTR lpszString)
{
    // Set the text on a label (the labelString)
    xd_set_XmLabel_window_text(lpszString, _xd_rootwidget) ;
}

void CButton::xd_set_window_text(LPCSTR lpszString)
{
    // Set the text on a button (the labelString)
    xd_set_XmLabel_window_text(lpszString, _xd_rootwidget) ;
}

int CStatic::xd_get_window_text(LPSTR lpszStringBuf, int nMaxCount) const
{
    // Get the text from a label (the labelString)
    // Return value:
    //  0 if the widget has not been created (no call to create() yet).
    //  The length of the text otherwise.

    return xd_get_XmLabel_window_text(lpszStringBuf, nMaxCount, _xd_rootwidget) ;
}

int CButton::xd_get_window_text(LPSTR lpszStringBuf, int nMaxCount) const
{
    // Get the text from a button (the labelString)
    // Return value:
    //  0 if the widget has not been created (no call to create() yet).
    //  The length of the text otherwise.

    return xd_get_XmLabel_window_text(lpszStringBuf, nMaxCount, _xd_rootwidget) ;
}

int CStatic::xd_get_window_text_length(void) const
{
    // Get the length of the text from a label (the labelString)
    // Return value:
    //  0 if the widget has not been created (no call to create() yet).
    //  The length of the text otherwise.

    return xd_get_XmLabel_window_text_length(_xd_rootwidget) ;
}

int CButton::xd_get_window_text_length(void) const
{
    // Get the length of the text from a button (the labelString)
    // Return value:
    //  0 if the widget has not been created (no call to create() yet).
    //  The length of the text otherwise.

    return xd_get_XmLabel_window_text_length(_xd_rootwidget) ;
}

int CButton::GetCheck(void) const
{
    // Get the check state of a button.
    // Return value:
    //  0 if the widget has not been created (no call to create() yet).
    //  0 if the widget is not a toggle button.
    //  0 if the widget is a toggle button and not set.
    //  1 if the widget is a toggle button and set.

    // MFC difference:
    // The return value is always 0 except for toggle buttons.
    // The return value 2 (indeterminate state) is not supported.

    if (_xd_rootwidget != NULL)
    {
	if (XmIsToggleButton(_xd_rootwidget) && XmToggleButtonGetState(_xd_rootwidget))
	    return 1 ;
	else if (XmIsToggleButtonGadget(_xd_rootwidget) && XmToggleButtonGadgetGetState(_xd_rootwidget))
	    return 1 ;
    }

    return 0 ;
 }

void CButton::SetCheck(int nCheck)
{
    // Set the check state of a button.

    // MFC difference:
    // This is a NOOP except for toggle buttons

    if (_xd_rootwidget == NULL)
	return ;

    if (XmIsToggleButton(_xd_rootwidget))
	XmToggleButtonSetState(_xd_rootwidget, nCheck, FALSE) ;
    else if (XmIsToggleButtonGadget(_xd_rootwidget))
	XmToggleButtonGadgetSetState(_xd_rootwidget, nCheck, FALSE) ;
}
