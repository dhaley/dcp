#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <ctype.h>

#include "xdclass.h"

xd_XtWidget_c::xd_XtWidget_c()
{
    _xd_rootwidget=0;
    return;
}

void xd_XtWidget_c::SetValue(String name, XtArgVal value)
{
    Arg al[1];
    Cardinal ac=0;
    XtSetArg(al[ac], name, value); ac++;
    XtSetValues(_xd_rootwidget, al, ac);
    return;
}

void xd_XtWidget_c::SetValues(ArgList args, Cardinal num_args)
{
    XtSetValues(_xd_rootwidget, args, num_args);
    return;
}

void xd_XtWidget_c::VaSetValues(String name,...)
{
    String attr;
    XtArgVal arg;
    int count=1;
    va_list ap;

    /* Ignore empty argument list */
    if (name==NULL)
	return;

    /* First count the (non-empty) argument list */
    va_start(ap, name);

    va_arg(ap, XtArgVal); // Pop first value
    for (attr = va_arg(ap, String); attr != NULL;
			attr = va_arg(ap, String))
    {
	va_arg(ap, XtArgVal); // Pop value
	++count;
    }
    va_end(ap);

    /* Now transfer values into an ArgList and throw at XtSetValues*/

    ArgList al=new Arg[count];
    XtArgVal value;
    Cardinal ac=0;

    va_start(ap, name);
    value=va_arg(ap, XtArgVal);
    XtSetArg(al[ac], name, value); ac++;
    for (attr = va_arg(ap, String); attr != NULL;
			attr = va_arg(ap, String))
    {
	value=va_arg(ap, XtArgVal);
	if (value)
	{
	    XtSetArg(al[ac], attr, value); ac++;
	}
    }
    va_end(ap);
    XtSetValues(_xd_rootwidget, al, ac);

    /* Tidy up */
    delete al;
    return;
}

void xd_XtWidget_c::GetValue(String name, void* value)
{
    Arg al[1];
    Cardinal ac=0;
    XtSetArg(al[ac], name, value); ac++;
    XtGetValues(_xd_rootwidget, al, ac);
    return;
}

void xd_XtWidget_c::GetValues(ArgList args, Cardinal num_args)
{
    XtGetValues(_xd_rootwidget, args, num_args);
    return;
}

void xd_XtWidget_c::VaGetValues(String name,...)
{
    //FIXME - not yet implemented
}

void xd_XtWidget_c::Map()
{
    XtMapWidget(_xd_rootwidget);
    return;
}

void xd_XtWidget_c::Unmap()
{
    XtUnmapWidget(_xd_rootwidget);
    return;
}

void xd_XtWidget_c::xd_enable()
{
    XtSetSensitive(_xd_rootwidget, TRUE);
    return;
}

void xd_XtWidget_c::xd_disable()
{
    XtSetSensitive(_xd_rootwidget, FALSE);
    return;
}

void xd_XtWidget_c::xd_destroy()
{
    if (_xd_rootwidget){
	XtDestroyWidget(_xd_rootwidget);
	_xd_rootwidget=0;
    }
    return;
}

void xd_ApplicationShell_c::xd_exit(int status)
{
    exit(status);
    return;
}

void xd_ApplicationShell_c::Realize()
{
    XtRealizeWidget(_xd_rootwidget);
    return;
}

void xd_ChildWidget_c::Manage()
{
    XtManageChild(_xd_rootwidget);
    return;
}

void xd_ChildWidget_c::Unmanage()
{
    XtUnmanageChild(_xd_rootwidget);
    return;
}

void xd_NonShellWidget_c::xd_show()
{
    Map();
    return;
}

void xd_NonShellWidget_c::xd_hide()
{
    Unmap();
    return;
}
