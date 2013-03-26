#include <Xm/Xm.h>
#include <Xm/RowColumn.h>
#include <Xm/CascadeB.h>
#include <Xm/CascadeBG.h>
#include <Xm/ToggleB.h>
#include <Xm/ToggleBG.h>
#include <Xm/Separator.h>
#include <Xm/SeparatoG.h>

#include <xdclass.h>

static const int INITIAL_ALLOC = 10;

CMenu::CMenu(void)
{
    _xd_items           = NULL;
    _xd_next_item       = 0;
    _xd_items_allocated = 0;
    _xd_menus           = NULL;
    _xd_next_menu       = 0;
    _xd_menus_allocated = 0;
}

CMenu::~CMenu()
{
    XtFree((char *)_xd_items);
    XtFree((char *)_xd_menus);
}

UINT
CMenu::CheckMenuItem(UINT nIDCheckItem, UINT nCheck)
{
    // Set the check state of a menu item corresponding to a
    // toggle button.
    // nIDCheckItem identifies the item either by its ID or
    // by its position.
    // nCheck specifies:
    //  a/ whether nIDCheckItem is an ID (MF_BYCOMMAND) or a
    //      position (MF_BYPOSITION)
    //  b/ whether to set (MF_CHECKED) or unset (MF_UNCHECKED)
    //      the toggle button.
    // The value of nCheck is a bitwise or of one (a) value
    // and one (b) value. That is, one of these four values:
    //      MF_BYCOMMAND | MF_CHECKED
    //      MF_BYCOMMAND | MF_UNCHECKED
    //      MF_BYPOSITION | MF_CHECKED
    //      MF_BYPOSITION | MF_UNCHECKED
    // If nCheck includes MF_BYCOMMAND the search for
    // the item includes submenus.
    // Comments on the design of this API should be sent to
    // Bill Gates.
    //
    // Return value:
    // -1 if the menu item is not found or is not a toggle button.
    // The previous state (MF_CHECKED or MF_UNCHECKED) otherwise.
    //
    // MFC difference:
    //  MFC allows the check state to be set by position on all
    //  menu components (items, separators, submenus) and by ID
    //  on all menu items. We only allow check state to be set on
    //  items that correspond to toggle buttons.

    Widget w     = NULL;
    int    state = -1;

    if (nCheck & MF_BYPOSITION)
	w = xd_get_menu_item_by_position(nIDCheckItem);
    else
	w = xd_get_menu_item_by_id(nIDCheckItem);

    if (w)
    {
	if (XmIsToggleButton(w))
	{
	    state = XmToggleButtonGetState(w) ? MF_CHECKED :  MF_UNCHECKED;

	    XmToggleButtonSetState(w, (nCheck & MF_CHECKED) ? TRUE : FALSE, FALSE);
	}
	else if (XmIsToggleButtonGadget(w))
	{
	    state = XmToggleButtonGadgetGetState(w) ? MF_CHECKED : MF_UNCHECKED;

	    XmToggleButtonGadgetSetState(w, (nCheck & MF_CHECKED) ? TRUE : FALSE, FALSE);
	}
    }

    return state;
}

UINT
CMenu::EnableMenuItem(UINT nIDEnableItem, UINT nEnable)
{
    // Enable or disable a menu item.
    // nIDEnableItem identifies the item either by its ID or
    // by its position.
    // nEnable specifies:
    //  a/ whether nIDEnableItem is an ID (MF_BYCOMMAND) or a
    //      position (MF_BYPOSITION)
    //  b/ whether to enable (MF_ENABLED) or disable (MF_GRAYED)
    //      the item.
    // The value of nEnable is a bitwise or of one (a) value
    // and one (b) value. That is, one of these four values:
    //      MF_BYCOMMAND | MF_ENABLED
    //      MF_BYCOMMAND | MF_GRAYED
    //      MF_BYPOSITION | MF_ENABLED
    //      MF_BYPOSITION | MF_GRAYED
    // If nEnable includes MF_BYCOMMAND the search for
    // the item includes submenus.
    // Comments on the design of this API should be sent to
    // Bill Gates.
    //
    // Return value:
    // -1 if the menu item is not found.
    // -1 if the item is identified by ID and is a menubar,
    //      menu, cascade button or separator.
    // The previous state (MF_ENABLED or MF_GRAYED) otherwise.
    //
    // MFC difference:
    //  We do not support the state MF_DISABLED (insensitive but
    //  not greyed out).

    Widget w     = NULL;
    int    state = -1;

    if (nEnable & MF_BYPOSITION)
	w = xd_get_menu_item_by_position(nIDEnableItem);
    else
    {
	w = xd_get_menu_item_by_id(nIDEnableItem);
	// Can only enable/disable by ID ordinary menu items
	// (not menubar, menu, submenu or separator).

	if (w && (XmIsRowColumn(w) || XmIsCascadeButton(w) || XmIsCascadeButtonGadget(w) || XmIsSeparator(w) || XmIsSeparatorGadget(w)))
	    w = NULL;
    }

    if (w)
    {
	state = XtIsSensitive(w) ? MF_ENABLED : MF_GRAYED;

	XtSetSensitive(w, (nEnable & MF_GRAYED) ? FALSE : TRUE);
    }

    return state;
}

UINT
CMenu::GetMenuState(UINT nID, UINT nFlags)
{
    // Get the state of a menu item.
    // nID identifies the menu item by position or by ID, according to
    // the value of nFlags.
    // nFlags is MF_BYPOSITION or MF_BYCOMMAND.
    // If nFlags is MF_BYCOMMAND the search for
    // the item includes submenus.
    //
    // Return value:
    // -1 if the menu item is not found.
    // -1 if the item is identified by ID and is a separator.
    // The state otherwise. The state is a bitwise or of:
    //  MF_CHECKED or MF_UNCHECKED
    //  with MF_GRAYED or MF_ENABLED
    //  and possibly MF_SEPARATOR.
    // WARNING: MF_ENABLED and MF_UNCHECKED are zero.
    //          (state & MF_ENABLED) will always test false,
    //          as will (state & MF_UNCHECKED).
    // Everyone makes mistakes, but most of us try to correct them...
    //
    // MFC difference:
    //  A query on the state of a pop-up menu (cascade button) in
    //  MFC returns the number of items in the pop-up in the high
    //  order byte of the (16 bit) UINT return value and the state
    //  in the low order byte. We just return the state.
    Widget w     = NULL;
    int    state = -1;

    if (nFlags == MF_BYPOSITION)
	w = xd_get_menu_item_by_position(nID);
    else
    {
	w = xd_get_menu_item_by_id(nID);

	// Cannot get state of separator by ID
	if (w && (XmIsSeparator(w) || XmIsSeparatorGadget(w)))
	    w = NULL;
    }

    if (w)
    {
	UINT checked = MF_UNCHECKED, sensitive=MF_ENABLED, separator=0;

	if (XmIsToggleButton(w))
	    checked = XmToggleButtonGetState(w) ? MF_CHECKED :  MF_UNCHECKED;
	else if (XmIsToggleButtonGadget(w))
	    checked = XmToggleButtonGadgetGetState(w) ? MF_CHECKED :  MF_UNCHECKED;

	sensitive = XtIsSensitive(w) ? MF_ENABLED : MF_GRAYED;

	// Only MS could think that a separator is a state of a menu item...
	separator = (XmIsSeparator(w) || XmIsSeparatorGadget(w)) ? MF_SEPARATOR : 0;

	state = checked | sensitive | separator;
    }

    return state;
}

void
CMenu::xd_register_menu_item(UINT nIDItem, Widget item)
{
    // Maintains mapping from item ids to widgets
    // This is used to find items by ID (MF_BYCOMMAND)
    if (_xd_items == NULL)
    {
	_xd_items           = (IDmap *)XtMalloc(INITIAL_ALLOC*sizeof(IDmap));
	_xd_items_allocated = INITIAL_ALLOC;

	_xd_next_item = 0 ;
    }

    if (_xd_next_item == _xd_items_allocated)
    {
	_xd_items_allocated *= 2;
	_xd_items            = (IDmap *)XtRealloc((char *)_xd_items, _xd_items_allocated * sizeof(IDmap));
    }

    _xd_items[_xd_next_item].id = nIDItem;
    _xd_items[_xd_next_item].w  = item;
    _xd_next_item++;
}

Widget
CMenu::xd_get_menu_item_by_id(UINT nIDItem)
{
    // Search for a menu item with the given ID.
    // Search self first, then submenus
    int i;

    for (i = 0; i < _xd_next_item; i++)
	if (_xd_items[i].id == nIDItem)
	    return _xd_items[i].w;

    for (i = 0; i < _xd_next_menu; i++)
    {
	Widget w = _xd_menus[i]->xd_get_menu_item_by_id(nIDItem);

	if (w)
	    return w;
    }

    return NULL;
}

Widget
CMenu::xd_get_menu_item_by_position(UINT nPos)
{
    // Get menu item by position in menu.
    if (nPos >= _xd_next_item)
	return NULL;
    else
	return _xd_items[nPos].w;
}

void
CMenu::xd_register_menu(CMenu *menu)
{
    //Maintains list of child CMenus to optimise recursive search.
    if (_xd_menus == NULL)
    {
	_xd_menus           = (CMenu **)XtMalloc(INITIAL_ALLOC*sizeof(CMenu *));
	_xd_menus_allocated = INITIAL_ALLOC;
	_xd_next_menu       = 0;
    }

    if (_xd_next_menu == _xd_menus_allocated)
    {
	_xd_menus_allocated *= 2;
	_xd_menus            = (CMenu **)XtRealloc((char *)_xd_menus, _xd_menus_allocated*sizeof(CMenu *));
    }

    _xd_menus[_xd_next_menu] = menu;
    _xd_next_menu++;
}

BOOL
CMenu::TrackPopupMenu(UINT, int, int, CWnd* pWnd, LPCRECT)
{
    XmAnyCallbackStruct *call_data = pWnd->xd_call_data();

    if (call_data && (call_data->event->type == ButtonPress))
    {
	XmMenuPosition(xd_rootwidget(), &(call_data->event->xbutton));

	XtManageChild(xd_rootwidget());

	return TRUE ;
    }

    return FALSE ;
}
