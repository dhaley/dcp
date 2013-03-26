#include <Xm/DialogS.h>

#include <xdclass.h>

xd_XmDialog_c::xd_XmDialog_c(void)
{
    xd_childwidget = NULL;
}

Widget xd_XmDialog_c::xd_getchildwidget(void)
{
    if (!xd_childwidget)
    {
	Cardinal numchildren = (Cardinal) 0 ;

	GetValue(XmNnumChildren, &numchildren);

	if (numchildren != 0)
	{
	    WidgetList children = (WidgetList) 0 ;

	    GetValue(XmNchildren, &children);

	    xd_childwidget = children[0] ;
	}
    }

    return xd_childwidget;
}

void xd_XmDialog_c::xd_show(void)
{
    if (!_xd_rootwidget) // Nothing to show
	return;

    if (!xd_getchildwidget()) // Nothing to show
	return;

    XtManageChild(xd_childwidget);
}

void xd_XmDialog_c::xd_hide(void)
{
    if (!_xd_rootwidget) // Nothing to hide
	return;
    if (!xd_getchildwidget()) // Nothing to hide
	return;

    XtUnmanageChild(xd_childwidget);
}

void xd_XmDialog_c::Raise(void)
{
    if (!_xd_rootwidget)
	return ;

    Window window = XtWindow(_xd_rootwidget) ;

    if (window)
    	(void) XRaiseWindow(XtDisplay(_xd_rootwidget), window);
}
