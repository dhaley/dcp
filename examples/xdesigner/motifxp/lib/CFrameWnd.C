#include <Xm/Xm.h>
#include <xdclass.h>
#include <utils.h>

#include <iostream.h>

void CFrameWnd::xd_set_window_text(LPCSTR lpszString)
{
    // Set the text on an application shell (the title and iconName)
    if (_xd_rootwidget != NULL)
	XtVaSetValues(_xd_rootwidget, XmNtitle, lpszString, XmNiconName, lpszString, NULL);
}

int CFrameWnd::xd_get_window_text(LPSTR lpszStringBuf, int nMaxCount) const
{
    // Get the text from an application shell (the title)
    // Return value:
    //  0 if the widget has not been created (no call to create() yet).
    //  The length of the text otherwise.

    if (_xd_rootwidget == NULL)
	return 0;

    // _xd_rootwidget is an ApplicationShell
    String title = (String) 0 ;

    XtVaGetValues(_xd_rootwidget, XmNtitle, &title, NULL);

    if (title) { 
	(void) strncpy(lpszStringBuf, title, nMaxCount - 1);
	
	lpszStringBuf[nMaxCount - 1] = '\0';

	return strlen(lpszStringBuf);
    }

    return 0 ;
}

int CFrameWnd::xd_get_window_text_length() const
{
    // Get the length of the text from an application shell (the title)
    // Return value:
    //  0 if the widget has not been created (no call to create() yet).
    //  The length of the text otherwise.

    if (_xd_rootwidget == NULL)
	return 0;

    String title = (String) 0 ;
    int    len   = 0 ;

    XtVaGetValues(_xd_rootwidget, XmNtitle, &title, NULL);

    return (title ?  strlen(title) : 0) ;
}

BOOL CFrameWnd::xd_show_window(int nCmdShow)
{
    // Implements ShowWindow() for application shell
    // First have to determine if window is "visible". In MS-W
    // the normal and iconic states both count as visible.

    unsigned long state      = xd_get_visibility_state(_xd_rootwidget);
    BOOL          wasvisible = (state != WithdrawnState);

    // Now change state - action depends on current state
    switch(nCmdShow)
    {
	case SW_HIDE:
	    if (XtWindow(_xd_rootwidget)) // Already realized
		XWithdrawWindow(XtDisplay(_xd_rootwidget), XtWindow(_xd_rootwidget), XScreenNumberOfScreen(XtScreen(_xd_rootwidget)));
	    else
	    {
		XtVaSetValues(_xd_rootwidget, XmNmappedWhenManaged, FALSE, NULL);
		XtRealizeWidget(_xd_rootwidget);
	    }
	    break;

	case SW_RESTORE:
	    XtVaSetValues(_xd_rootwidget, XmNinitialState, NormalState, XmNmappedWhenManaged, TRUE, NULL);

	    if (!XtWindow(_xd_rootwidget))
		XtRealizeWidget(_xd_rootwidget);
	    else
		XtMapWidget(_xd_rootwidget);
	    break;

	case SW_SHOWMINIMIZED:
	    if (state == NormalState)
		XIconifyWindow(XtDisplay(_xd_rootwidget), XtWindow(_xd_rootwidget), XScreenNumberOfScreen(XtScreen(_xd_rootwidget)));
	    else
	    {
		XtVaSetValues(_xd_rootwidget, XmNinitialState, IconicState, XmNmappedWhenManaged, TRUE, NULL);

		if (!XtWindow(_xd_rootwidget))
		    XtRealizeWidget(_xd_rootwidget);
		else if (state==WithdrawnState)
		    XtMapWidget(_xd_rootwidget);
	    }
	    break;
    }

    return wasvisible;
}
