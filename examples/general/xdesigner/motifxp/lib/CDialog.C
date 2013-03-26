#include <Xm/Xm.h>
#include <Xm/DialogS.h>
#include <xdclass.h>
#include <utils.h>

#include <iostream.h>

void CDialog::xd_set_window_text(LPCSTR lpszString)
{
    // Set the text on a popup shell (the title and iconName).
    if (_xd_rootwidget != NULL)
	XtVaSetValues(_xd_rootwidget,
		      XmNtitle,    lpszString,
		      XmNiconName, lpszString, // XmDialogShell will ignore this
		      NULL) ;
}

int CDialog::xd_get_window_text(LPSTR lpszStringBuf, int nMaxCount) const
{
    // Get the text from a popup shell (the title)
    // Return value:
    //  0 if the widget has not been created (no call to create() yet).
    //  The length of the text otherwise.

    if (_xd_rootwidget == NULL)
	return 0 ;

    // _xd_rootwidget is an XmDialogShell
    String title = (String) 0 ;

    XtVaGetValues(_xd_rootwidget, XmNtitle, &title, NULL) ;

    strncpy(lpszStringBuf, title, nMaxCount - 1) ;
    lpszStringBuf[nMaxCount-1] = '\0' ;

    return strlen(lpszStringBuf) ;
}

int CDialog::xd_get_window_text_length(void) const
{
    // Get the length of the text from a popup shell (the title)
    // Return value:
    //  0 if the widget has not been created (no call to create() yet).
    //  The length of the text otherwise.

    if (_xd_rootwidget == NULL)
	return 0 ;

    // _xd_rootwidget is an ApplicationShell
    String title = (String) 0 ;
    int    len   = 0 ;

    XtVaGetValues(_xd_rootwidget, XmNtitle, &title, NULL) ;

    return (title ? strlen(title) : 0) ;
}

static BOOL xd_show_dialog_window(int nCmdShow, Widget rootwidget)
{
    // Implements ShowWindow() for XmDialogShell
    // XmDialogShell is straightforward. It is visible
    // if and only if it has a managed child, and is
    // hidden and restored by unmanaging and managing the child.

    WidgetList children    = (WidgetList) 0 ;
    Cardinal   numchildren = (Cardinal) 0 ;

    if (!rootwidget)
	return FALSE ;

    XtVaGetValues(rootwidget,
		  XmNchildren,    &children,
		  XmNnumChildren, &numchildren,
		  NULL) ;

    if (numchildren == 0) // Invisible and staying that way
	return FALSE ;

    Boolean wasvisible = XtIsManaged(children[0]) ;

    switch(nCmdShow)
    {
	case SW_HIDE:       XtUnmanageChild(children[0]) ;
			    break ;

	case SW_RESTORE:    XtManageChild(children[0]) ;
			    break ;

	default:            cerr << "CDialog::ShowWindow: Only SW_HIDE and SW_RESTORE supported for XmDialogShell windows" << endl ;
    }

    return wasvisible ;
}

static BOOL xd_show_toplevel_window(int nCmdShow, Widget rootwidget)
{
    // Implements ShowWindow() for TopLevelShell
    // First have to determine if window is "visible". In MS-W
    // the normal and iconic states both count as visible.

    if (!rootwidget)
	return FALSE ;

    unsigned long state      = xd_get_visibility_state(rootwidget);
    BOOL          wasvisible = (state != WithdrawnState) ;

    // Now change the state as required - action depends on current state
    switch(nCmdShow)
    {
	case SW_HIDE:
	    if (XtWindow(rootwidget))           // Iconic or normal
		XtPopdown(rootwidget) ;
	    else                                // Unrealized
		XtRealizeWidget(rootwidget) ;
	    break ;

	case SW_RESTORE:
	    if (!XtWindow(rootwidget)           // Unrealized
		|| (state == WithdrawnState))   // or withdrawn
	    {
		XtVaSetValues(rootwidget, XmNinitialState, NormalState, NULL) ;
		XtPopup(rootwidget, XtGrabNone) ;
	    }
	    else                                // Iconic
		XtMapWidget(rootwidget) ;

	    break;

	case SW_SHOWMINIMIZED:
	    if (!XtWindow(rootwidget)          // Unrealized
		|| (state == WithdrawnState))  // or withdrawn
	    {
		XtVaSetValues(rootwidget, XmNinitialState, IconicState, NULL) ;
		XtPopup(rootwidget, XtGrabNone) ;
	    }
	    else                                // Normal
		XIconifyWindow(XtDisplay(rootwidget),
			       XtWindow(rootwidget),
			       XScreenNumberOfScreen(XtScreen(rootwidget))) ;
	    break ;
    }

    return wasvisible ;
}

BOOL CDialog::xd_show_window(int nCmdShow)
{
    // Implements ShowWindow() for popup shells

    if (!_xd_rootwidget)
	return FALSE ;

    if (XmIsDialogShell(_xd_rootwidget))
	return xd_show_dialog_window(nCmdShow, _xd_rootwidget) ;
    else
	return xd_show_toplevel_window(nCmdShow, _xd_rootwidget) ;
}

#include "stdio.h"

int CDialog::DoModal(void)
{
    // Have to set resources and callbacks to emulate MFC behaviour
    // and use private event loop so that we can return
    // a value.

    Widget     okb          = (Widget) 0 ;
    Widget     cancelb      = (Widget) 0 ;
    Widget     bb           = (Widget) 0 ;
    WidgetList children     = (WidgetList) 0 ;
    Cardinal   num_children = (Cardinal) 0 ;

    XtVaGetValues(xd_rootwidget(), XmNchildren, &children, XmNnumChildren, &num_children, NULL) ;

    if (children && children[0]) {
            bb = children[0] ;
    }

    XtVaGetValues(bb, XmNdefaultButton, &okb, XmNcancelButton, &cancelb, NULL) ;
    
    if (okb)
        XtAddCallback(okb, XmNactivateCallback, xd_OnOk, (XtPointer) this) ;

    if (cancelb)
        XtAddCallback(cancelb, XmNactivateCallback, xd_OnCancel, (XtPointer) this) ;

    _xd_current_state = undecided ;
    // Popup the dialog
   
    XtVaGetValues(_xd_rootwidget, XmNchildren, &children, NULL) ;

    if (children[0])
    	XtManageChild(children[0]) ;

    XtAppContext app_context = XtWidgetToApplicationContext(_xd_rootwidget) ;
    XEvent       event ;

    // Process events until Ok or Cancel callback triggered
    while (_xd_current_state == undecided)
    {
	XtAppNextEvent(app_context, &event) ;
	XtDispatchEvent(&event) ;
    }

    XtUnmanageChild(children[0]) ;

    return _xd_current_state ;
}

void
CDialog::xd_OnOk(Widget, XtPointer client_data, XtPointer)
{
    CDialog *instance = (CFileDialog *)client_data ;

    instance->OnOK() ;
}

void
CDialog::OnOK(void)
{
    _xd_current_state = ok ;
}

void
CDialog::xd_OnCancel(Widget, XtPointer client_data, XtPointer)
{
    CDialog *instance = (CFileDialog *)client_data ;

    instance->OnCancel() ;
}

void
CDialog::OnCancel(void)
{
    // From cancel button or popdown (via WM menu or OK button)
    if (_xd_current_state == undecided)
	_xd_current_state = cancel ;
}
