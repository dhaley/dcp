#include <Xm/Xm.h>
#include <Xm/RowColumn.h>
#include <Xm/PushB.h>
#include <xdclass.h>
#include <utils.h>

static Widget xd_optmenu_item(Widget rootwidget, int nIndex)
{
    // Find an item in an option menu given its index.
    // Return NULL if the index is out of range.

    // Get the menu pane
    Widget cascade  = XmOptionButtonGadget(rootwidget) ;
    Widget menupane = (Widget) 0 ;

    if (nIndex < 0)
	return NULL ;

    XtVaGetValues(cascade, XmNsubMenuId, &menupane, NULL) ;

    if (!menupane)
	return NULL ;

    WidgetList children     = (WidgetList) 0 ;
    Cardinal   num_children = (Cardinal) 0 ;

    XtVaGetValues(menupane, XmNchildren, &children, XmNnumChildren, &num_children, NULL);

    if (nIndex >= num_children)
	return NULL ;
    else
	return children[nIndex] ;
}

static char *xd_optmenu_text(Widget rootwidget, int nIndex)
{
    // Get text from an option menu item given its index
    Widget w = xd_optmenu_item(rootwidget, nIndex) ;

    if (w)
	return xd_text_from_XmLabel(w) ;
    else
	return NULL ;
}

int CComboBox::GetCurSel(void) const
{
    // Return the index of the currently selected item
    // Return value:
    //  0 if the widget has not been created (no call to create() yet).
    //  The zero-based index of the currently selected item otherwise.
    if (_xd_rootwidget==0)
	return 0 ;

    Widget selected = (Widget) 0 ;

    XtVaGetValues(_xd_rootwidget, XmNmenuHistory, &selected, NULL);

    if (!selected)
	return 0 ;

    short position = (short) 0 ;

    XtVaGetValues(selected, XmNpositionIndex, &position, NULL) ;

    return position ;
}

int CComboBox::GetLBText(int nIndex, LPSTR lpszText) const
{
    // Get a copy of the text of the item identified by nIndex
    // and return its length
    // Return value:
    //  0 if the widget has not been created (no call to create() yet).
    //  LB_ERR if the index is out of range.
    //  The length of the item text otherwise.

    int len = 0 ;

    if (_xd_rootwidget != 0)
    {
	char *s = xd_optmenu_text(_xd_rootwidget, nIndex) ;

	if (s)
	{
	    (void) strcpy(lpszText, s) ;
	    len = strlen(s) ;

	    XtFree(s) ;
	}
	else
	    len = LB_ERR ;
    }

    return len ;
}

int CComboBox::GetLBTextLen(int nIndex) const
{
    // Get the length of the text of the item identified by nIndex
    // Return value:
    //  0 if the widget has not been created (no call to create() yet).
    //  LB_ERR if the index is out of range.
    //  The length of the item text otherwise.

    int len = 0 ;

    if (_xd_rootwidget!=0)
    {
	char *s = xd_optmenu_text(_xd_rootwidget, nIndex) ;

	if (s)
	{
	    len = strlen(s) ;
	    XtFree(s) ;
	}
	else
	    len = LB_ERR ;
    }

    return len ;
}

int CComboBox::SetCurSel(int nSelect)
{
    // Set the currently selected item by index.
    // Return value:
    //  0 if the widget has not been created (no call to create() yet).
    //  LB_ERR if the index is out of range.
    //  The index of the selected item otherwise.

    // MFC difference:
    // The value nSelect==-1 is not supported as it is not
    // possible to clear the selection.

    if (_xd_rootwidget == 0)
	return 0 ;

    if (nSelect < 0)
	return LB_ERR ;

    Widget cascade  = XmOptionButtonGadget(_xd_rootwidget) ;
    Widget menupane = (Widget) 0 ;

    XtVaGetValues(cascade, XmNsubMenuId, &menupane, NULL) ;

    if (!menupane)
	return 0 ;

    WidgetList children     = (WidgetList) 0 ;
    Cardinal   num_children = (Cardinal) 0 ;

    XtVaGetValues(menupane, XmNchildren, &children, XmNnumChildren, &num_children, NULL) ;

    if (nSelect >= num_children)
	return LB_ERR ;
    else
    {
	XtVaSetValues(_xd_rootwidget, XmNmenuHistory, children[nSelect], NULL) ;

	return nSelect ;
    }
}

int CComboBox::xd_get_window_text(LPSTR lpszStringBuf, int nMaxCount) const
{
    // Get the window text of a combo box (which is the text of
    // the selected item)
    // Return value:
    //  0 if the widget has not been created (no call to create() yet).
    //  LB_ERR if there is no selected item.
    //  The length of the text otherwise.
    int len = 0 ;

    if (_xd_rootwidget!=0)
    {
	Widget w = (Widget) 0 ;

	XtVaGetValues(_xd_rootwidget, XmNmenuHistory, &w, NULL) ;

	if (w)
	{
	    char *s = xd_text_from_XmLabel(w) ;
	    
	    (void) strncpy(lpszStringBuf, s, nMaxCount - 1) ;
	    lpszStringBuf[nMaxCount-1] = '\0' ;

	    len = strlen(lpszStringBuf) ;

	    XtFree(s) ;
	}
	else
	    len = LB_ERR ;
    }

    return len ;
}

int CComboBox::xd_get_window_text_length(void) const
{
    // This corresponds to the MFC behaviour

    if (_xd_rootwidget != 0)
	return -1 ;
    else
	return 0 ;
}

void CComboBox::ResetContent(void)
{
	if (_xd_rootwidget == (Widget) 0) {
       		return ;
	}

	Widget cascade  = XmOptionButtonGadget(_xd_rootwidget) ;
	Widget menupane = (Widget) 0 ;
	
	XtVaGetValues(cascade, XmNsubMenuId, &menupane, NULL) ;

	if (!menupane)
		return ;
	
	WidgetList children     = (WidgetList) 0 ;
	Cardinal   num_children = (Cardinal) 0 ;
	int        i            = 0 ;
	
	XtVaGetValues(menupane, 
		      XmNchildren,    &children, 
		      XmNnumChildren, &num_children, 
		      NULL) ;

	for (i = 0 ; i < num_children ; i++) {
		if (children[i])
			XtDestroyWidget(children[i]) ;
	}
}

int CComboBox::InsertString(int nIndex, LPCSTR lpszString)
{
	if (_xd_rootwidget == (Widget) 0) {
       		return CB_ERR ;
	}

	if (nIndex < -1) {
       		return CB_ERR ;
	}

	Widget   cascade      = XmOptionButtonGadget(_xd_rootwidget) ;
	Widget   menupane     = (Widget) 0 ;
	Widget   new_child    = (Widget) 0 ;
	Cardinal num_children = (Cardinal) 0 ;
	XmString xms          = (XmString) 0 ;
	Arg      argv[2] ;
	Cardinal argc ;
	
	XtVaGetValues(cascade, XmNsubMenuId, &menupane, NULL) ;

	if (menupane == (Widget) 0) {
		return CB_ERR ;
	}

	XtVaGetValues(menupane, XmNnumChildren, &num_children, NULL) ;

	if (nIndex > num_children) {
		return CB_ERR ;
	}

	if (nIndex == -1) {
		nIndex = num_children + 1 ;
	}

	if ((xms = XmStringCreateLocalized((char *) lpszString)) == (XmString) 0) {
		return CB_ERRSPACE ;
	}

	argc = 0 ;
	XtSetArg(argv[argc], XmNlabelString,   xms) ;        argc++ ;
	XtSetArg(argv[argc], XmNpositionIndex, nIndex - 1) ; argc++ ;

	new_child = XmCreatePushButton(menupane, (char *) "combobox_item", argv, argc) ;

	XtManageChild(new_child) ;

	return nIndex - 1 ;
}
