#include <Xm/Xm.h>
#include <Xm/List.h>
#include <Xm/ScrolledW.h>

#include <iostream.h>

#include <xdclass.h>
#include <utils.h>

static inline int min(int a, int b)
{
    return (a < b) ? a : b;
}

static inline int max(int a, int b)
{
    return (a > b) ? a : b;
}

static Boolean xd_list_is_single_select(Widget listwidget)
{
    // Determine if selection is single item or multiple
    unsigned char selection_policy = XmSINGLE_SELECT ;

    if (listwidget) {
    	XtVaGetValues(listwidget, XmNselectionPolicy, &selection_policy, NULL);
    }

    return ((selection_policy == XmSINGLE_SELECT) || (selection_policy == XmBROWSE_SELECT));
}

void CListBox::xd_rootwidget(Widget xd_rootwidget)
{
    CWnd::xd_rootwidget(xd_rootwidget);

    if (XmIsScrolledWindow(xd_rootwidget))
    {
	WidgetList children    = (WidgetList) 0 ;
	Cardinal   numchildren = (Cardinal) 0 ;
	int        i;

	XtVaGetValues(xd_rootwidget, XmNchildren, &children, XmNnumChildren, &numchildren, NULL);

	if (numchildren && children) {
		for ( i = 0; i < numchildren; i++ ) 
			if ( XmIsList ( children[i] ) ) {
				_xd_listwidget = children[i];
				
				break;
			}
    	}
    }
    else
	_xd_listwidget = _xd_rootwidget;
}

Widget CListBox::xd_listwidget(void)
{
    return _xd_listwidget;
}

BOOL CListBox::xd_enable_window(BOOL bEnable)
{
    // Enable or disable a window
    //  Return value:
    //  0 if the widget has not been created (no call to create() yet).
    //  0 if the window was previously enabled
    //  non-zero if the window was previously disabled.

    if (_xd_listwidget == NULL)
	return FALSE;

    BOOL wasdisabled = !XtIsSensitive(_xd_listwidget);

    XtSetSensitive(_xd_listwidget, bEnable);

    return wasdisabled;
}

int CListBox::DeleteString(UINT nIndex)
{
    // Delete the list item identified by nIndex
    // The first item has index zero
    // Return value:
    //  0 if the widget has not been created (no call to create() yet).
    //  LB_ERR if the index is out of range.
    //  The number of items remaining in the list otherwise.
    if (_xd_listwidget!=NULL)
    {
	if (nIndex >= GetCount())
	    return LB_ERR;

	XmListDeletePos(_xd_listwidget, nIndex+1); //Items numbered from zero in MSW
    }

    return GetCount();
}

int CListBox::GetCount(void) const
{
    // Get the number of items in the list.
    // Return value:
    //  0 if the widget has not been created (no call to create() yet).
    //  The number of items in the list otherwise.
    int count = 0;

    if (_xd_listwidget!=NULL)
	XtVaGetValues(_xd_listwidget, XmNitemCount, &count, NULL);

    return count;
}

int CListBox::GetCurSel(void) const
{
    // Get the index of the currently selected item in a single
    // selection list.
    // Return value:
    //  0 if the widget has not been created (no call to create() yet).
    //  LB_ERR if the list is a multiple selection list
    //  LB_ERR if the list has no selected item.
    //  The index of the selected item otherwise.

    // MFC difference:
    //  We return LB_ERR consistently when applied to a multiple
    //  selection list that has been created. MFC returns a
    //  nonsense positive value.

    int selected = 0;

    if (_xd_listwidget != NULL)
	if (xd_list_is_single_select(_xd_listwidget))
	{
	    int *position_list  = (int *) 0 ;
	    int  position_count = 0 ;

	    Boolean has_selection = XmListGetSelectedPos(_xd_listwidget, &position_list, &position_count);

	    if (!has_selection)
		selected = LB_ERR;
	    else
	    {
		selected = position_list[0] - 1; // Items numbered from 0 in MFC

		XtFree((char *)position_list);
	    }
	}
    else
	selected = LB_ERR;

    return selected;
}

int CListBox::GetSel(int nIndex) const
{
    // Get the selection state of an item.
    // Return value:
    //  0 if the widget has not been created (no call to create() yet).
    //  LB_ERR if the index is out of range.
    //  0 if the item is not selected.
    //  A positive value if the item is selected.
    int selected = 0;

    if (_xd_listwidget != NULL)
	if (nIndex < 0 || nIndex >= GetCount())
	    selected = LB_ERR;
	else
	    selected = XmListPosSelected(_xd_listwidget, nIndex+1) ? 1 : 0;

    return selected;
}

int CListBox::GetSelCount(void) const
{
    // Get the number of selected items in a multiple selection list
    // Return value:
    //  0 if the widget has not been created (no call to create() yet).
    //  LB_ERR if the list is a single selection list
    //  The number of selected items otherwise.
    int count = 0;

    if (_xd_listwidget != NULL)
    {
	if (xd_list_is_single_select(_xd_listwidget))
	    count = LB_ERR;
	else
	{
	    int *position_list = (int *) 0;

	    Boolean has_selection = XmListGetSelectedPos(_xd_listwidget, &position_list, &count);

	    if (has_selection)
		XtFree((char *)position_list);
	}
    }

    return count;
}

int CListBox::GetSelItems(int nMaxItems, LPINT rgIndex) const
{
    // Get the indices of the selected items in a multiple selection list
    // and copy them into the array rgIndex.
    // Return value:
    //  0 if the widget has not been created (no call to create() yet).
    //  LB_ERR if the list is a single selection list
    //  The number of indices copied into rgIndex otherwise.
    int count = 0;

    if (_xd_listwidget!=NULL)
    {
	if (xd_list_is_single_select(_xd_listwidget))
	    count = LB_ERR;
	else
	{
	    int *position_list = (int *) 0 ;

	    Boolean has_selection = XmListGetSelectedPos(_xd_listwidget, &position_list, &count);

	    if (has_selection)
	    {
		count = min(count, nMaxItems);

		for (int i = 0; i < count; i++)
		    rgIndex[i] = position_list[i]-1;

		XtFree((char *)position_list);
	    }
	}
    }

    return count;
}

int CListBox::GetText(int nIndex, LPSTR lpszBuffer) const
{
    // Get the text of the item identified by nIndex
    // Return value:
    //  0 if the widget has not been created (no call to create() yet).
    //  LB_ERR if the index is out of range.
    //  The length of the text otherwise.
    int length = 0;

    if (nIndex < 0)
	return LB_ERR;

    if (_xd_listwidget != NULL)
    {
	XmStringTable items      = (XmStringTable) 0;
	int           item_count = 0;

	XtVaGetValues(_xd_listwidget, XmNitems, &items, XmNitemCount, &item_count, NULL);

	if (nIndex >= item_count)
	    length = LB_ERR;
	else
	{
	    char *s = xd_text_from_XmString(items[nIndex]);

	    if (s) { 
		(void) strcpy(lpszBuffer, s);
		
		length = strlen(s);
		
		XtFree(s);
	    }
	}
    }

    return length;
}

int CListBox::GetTextLen(int nIndex) const
{
    // Get the length of the text of the item identified by nIndex
    // Return value:
    //  0 if the widget has not been created (no call to create() yet).
    //  LB_ERR if the index is out of range.
    //  The length of the text otherwise.
    int length = 0;

    if (nIndex < 0)
	return LB_ERR ;

    if (_xd_listwidget != NULL)
    {
	XmStringTable items      = (XmStringTable) 0 ;
	int           item_count = 0 ;

	XtVaGetValues(_xd_listwidget, XmNitems, &items, XmNitemCount, &item_count, NULL);

	if (nIndex>=item_count)
	    length = LB_ERR;
	else
	{
	    char *s = xd_text_from_XmString(items[nIndex]);

	    if (s) {
	    	length = strlen(s);
		
		XtFree(s);
	    }
	}
    }

    return length;
}

int CListBox::GetTopIndex() const
{
    // Get the index of the item that is visible at the top of the list.
    // Return value:
    //  0 if the widget has not been created (no call to create() yet).
    //  The index of the top item otherwise.

    int topitem = 1;

    if (_xd_listwidget != NULL)
	XtVaGetValues(_xd_listwidget, XmNtopItemPosition, &topitem, NULL);

    return topitem-1;
}

int CListBox::InsertString(int nIndex, LPCSTR lpszItem)
{
    // Insert an item into the list at the position given by nIndex.
    // If nIndex is -1 the item is appended at the end of the list.
    // Return value:
    //  0 if the widget has not been created (no call to create() yet).
    //  LB_ERR if the index is out of range.
    //  The position at which the item was inserted otehrwise.

    if (_xd_listwidget==0)
	return 0;
    if (nIndex>GetCount()|| nIndex<-1)
	return LB_ERR;
    XmString s=XmStringCreateLocalized((char *)lpszItem);
    XmListAddItem(_xd_listwidget, s, nIndex+1);
    /* PR 4583 - Memory Leak */
    XmStringFree(s);
    if (nIndex==-1)
	return GetCount()-1;
    else
	return nIndex;
}

void CListBox::ResetContent(void)
{
    // Remove all items from the list
    if (_xd_listwidget != NULL)
	XmListDeleteAllItems(_xd_listwidget);
}

int CListBox::SelItemRange(BOOL bSelect, int nFirstItem, int nLastItem)
{
    // Select (bSelect=TRUE) or deselect (bSelect=FALSE) a range
    // of items in a multiple selection list.
    // Return value:
    //  0 if the widget has not been created (no call to create() yet).
    //  LB_ERR if the list is a single selection list.
    //  A value other than LB_ERR otherwise.

    if (_xd_listwidget == NULL)
	return 0;

    if (xd_list_is_single_select(_xd_listwidget))
	return LB_ERR;

    // MFC method does not object to selection beyond end of list
    // and is clever enough to cope with first>last
    int first = min(nFirstItem, nLastItem)+1;
    int count = GetCount();

    if (first > count)
	return 0;

    int last = max(nFirstItem, nLastItem)+1;
    last = min(last, count);

    int i = 0 ;

    for (i = first; i <= last; i++) {
	if (bSelect) {
	    XmListSelectPos(_xd_listwidget, i, FALSE);
     	}
	else {
	    XmListDeselectPos(_xd_listwidget, i);
     	}
    }

    return i;
}

int CListBox::SetCurSel(int nSelect)
{
    // Select an item in a single selection list and scroll
    // it into view.
    // If nSelect is -1 the selection is cleared.
    // Return value:
    //  0 if the widget has not been created (no call to create() yet).
    //  LB_ERR if the list is a multiple selection list.
    //  LB_ERR if the index is out of range.
    //  A value other than LB_ERR otherwise.

    if (_xd_listwidget == NULL)
	return 0;

    if (!xd_list_is_single_select(_xd_listwidget))
	return LB_ERR;

    if ((nSelect >= GetCount()) || (nSelect < -1))
	return LB_ERR;

    if (nSelect == -1)
    {
	XmListDeselectAllItems(_xd_listwidget);
    }
    else
    {
	XmListSelectPos(_xd_listwidget, nSelect+1, FALSE);

	// Scroll into view
	int top           = 0 ;
	int visible_items = 0 ;

	XtVaGetValues(_xd_listwidget, XmNtopItemPosition, &top, XmNvisibleItemCount, &visible_items, NULL);

	if ((nSelect + 1) < top)
	    XmListSetPos(_xd_listwidget, nSelect + 1);

	if ((nSelect + 1) >= (top + visible_items))
	    XmListSetBottomPos(_xd_listwidget, nSelect + 1);
    }

    return 0;
}

int CListBox::SetSel(int nIndex, BOOL bSelect)
{
    // Select (bSelect=TRUE) or deselect (bSelect=FALSE) an
    // item in a multiple selection list.
    // If nSelect is -1 all items are selected or deselected.
    // Return value:
    //  0 if the widget has not been created (no call to create() yet).
    //  LB_ERR if the list is a single selection list.
    //  LB_ERR if the index is out of range.
    //  A value other than LB_ERR otherwise.

    if (_xd_listwidget == NULL)
	return 0;

    if (xd_list_is_single_select(_xd_listwidget))
	return LB_ERR;

    if ((nIndex >= GetCount()) || (nIndex < -1))
	return LB_ERR;

    if (nIndex == -1)
    {
	if (bSelect)
	{
	    int count = GetCount();

	    for (int i = 1; i <= count; i++)
		XmListSelectPos(_xd_listwidget, i, FALSE);
	}
	else
	    XmListDeselectAllItems(_xd_listwidget);
    }
    else
    {
	if (bSelect)
	    XmListSelectPos(_xd_listwidget, nIndex + 1, FALSE);
	else
	    XmListDeselectPos(_xd_listwidget, nIndex + 1);
    }

    return 0;
}

int CListBox::SetTopIndex(int nIndex)
{
    // Scroll the list to make an item visible.
    // Return value:
    //  0 if the widget has not been created (no call to create() yet).
    //  LB_ERR if the index is out of range.
    //  A value other than LB_ERR otherwise.

    if (_xd_listwidget == NULL)
	return 0;

    if ((nIndex >= GetCount()) || (nIndex < 0))
	return LB_ERR;

    XmListSetPos(_xd_listwidget, nIndex + 1);

    return 0;
}
