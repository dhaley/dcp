#include <Xm/Xm.h>
#include <xdclass.h>

#include <X11/IntrinsicP.h>

#include <iostream.h>

BOOL CWnd::IsWindowEnabled(void)
{
    if (_xd_rootwidget == NULL)
	return FALSE;

    return XtIsSensitive(_xd_rootwidget);
}

BOOL CWnd::EnableWindow(BOOL bEnable)
{
    // Enable or disable a window
    //  Return value:
    //  0 if the widget has not been created (no call to create() yet).
    //  0 if the window was previously enabled
    //  non-zero if the window was previously disabled.
    // Simply calls xd_enable_window which is a virtual function
    // so that it can be overridden for ScrolledText and ScrolledList

    if (_xd_rootwidget == NULL)
	return FALSE;

    return xd_enable_window (bEnable);
}

BOOL CWnd::xd_enable_window(BOOL bEnable)
{
    // Enable or disable a window
    //  Return value:
    //  0 if the widget has not been created (no call to create() yet).
    //  0 if the window was previously enabled
    //  non-zero if the window was previously disabled.

    if (_xd_rootwidget == NULL)
	return FALSE;

    BOOL wasdisabled = !XtIsSensitive(_xd_rootwidget);

    XtSetSensitive(_xd_rootwidget, bEnable);

    return wasdisabled;
}

void CWnd::SetWindowText(LPCSTR lpszString)
{
    // Set the window text for a window. The interpretation
    // of 'window text' and the validation varies wildly between
    // classes, so check the notes for xd_set_window_text() on
    // the appropriate subclass.
    xd_set_window_text(lpszString);
}

int CWnd::GetWindowText(LPSTR lpszStringBuf, int nMaxCount) const
{
    // Get the window text for a window. The interpretation
    // of 'window text' and the validation varies wildly between
    // classes, so check the notes for xd_get_window_text() on
    // the appropriate subclass.
    return xd_get_window_text(lpszStringBuf, nMaxCount);
}

int CWnd::GetWindowTextLength(void) const
{
    // Get the length of the window text for a window. The interpretation
    // of 'window text' and the validation varies wildly between
    // classes, so check the notes for xd_get_window_text_length() on
    // the appropriate subclass.
    return xd_get_window_text_length();
}

BOOL CWnd::ShowWindow(int nCmdShow)
{
    // Show, iconize or hide a window.
    // nCmdShow can be SW_RESTORE (show) or SW_HIDE (hide)
    // for any window. It can be SW_SHOWMINIMIZED for
    // ApplicationShell and TopLevelShell only.
    //
    // Return value:
    //  0 if the widget has not been created (no call to create() yet).
    //  0 if the window was previously hidden
    //  non-zero if the window was previously visible (normal or iconized)
    if (_xd_rootwidget == NULL)
    {
	return FALSE;
    }

    return xd_show_window(nCmdShow);
}

void CWnd::xd_set_window_text(LPCSTR lpszString)
{
    // Implements SetWindowText() for CWnd
    // For an ordinary CWnd the window text is just
    // invisible text associated with the window.
    // For subclasses it is used for (eg) labelString
    // of XmLabel, value of XmText, title of Shell...

    if (_xd_rootwidget != NULL) // NOOP if no window yet
    {
	XtFree(_xd_window_text);

	_xd_window_text = XtMalloc(strlen(lpszString) + 1);

	(void) strcpy(_xd_window_text, lpszString);
    }
}

int CWnd::xd_get_window_text(LPSTR lpszStringBuf, int nMaxCount) const
{
    // Implements GetWindowText() for CWnd
    // Return value:
    //  0 if the widget has not been created (no call to create() yet).
    //  The length of the text otherwise.

    if ((_xd_rootwidget == NULL) || (_xd_window_text == NULL))
	return 0;

    (void) strncpy(lpszStringBuf, _xd_window_text, nMaxCount - 1);
    lpszStringBuf[nMaxCount-1]='\0';

    return strlen(lpszStringBuf);
}

int CWnd::xd_get_window_text_length() const
{
    // Implements GetWindowTextLength() for CWnd
    // Return value:
    //  0 if the widget has not been created (no call to create() yet).
    //  The length of the text otherwise.
    if ((_xd_rootwidget == NULL) || (_xd_window_text == NULL))
	return 0;
    else
	return strlen(_xd_window_text);
}

BOOL CWnd::xd_show_window(int nCmdShow)
{
    // Changes the visibility state of a child widget
    // by mapping or unmapping it or a child gadget by
    // managing or unmanaging it.

    Boolean wasvisible = TRUE;
    Boolean gadget     = XmIsGadget(_xd_rootwidget);

    if (gadget)
	wasvisible = XtIsManaged(_xd_rootwidget);
    else
	XtVaGetValues(_xd_rootwidget, XmNmappedWhenManaged, &wasvisible, NULL);

    switch(nCmdShow)
    {
	case SW_HIDE:       if (gadget)
				XtUnmanageChild(_xd_rootwidget);
			    else
				XtSetMappedWhenManaged(_xd_rootwidget, FALSE);
			    break;

	case SW_RESTORE:    if (gadget)
				XtManageChild(_xd_rootwidget);
			    else
				XtSetMappedWhenManaged(_xd_rootwidget, TRUE);
			    break;

        case SW_SHOW:            XtManageChild(_xd_rootwidget);
                            break;

	default:            cerr << "CWnd::ShowWindow: Only SW_HIDE and SW_RESTORE supported for child windows" << endl;
    }

    return wasvisible;
}
