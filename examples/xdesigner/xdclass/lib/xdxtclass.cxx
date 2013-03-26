#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#include <xdclass.h>

xd_XtWidget_c::xd_XtWidget_c(void)
{
    _xd_rootwidget = NULL;
}

void xd_XtWidget_c::SetValue(String name, XtArgVal value)
{
    Arg      al[1];
    Cardinal ac = 0;

    XtSetArg(al[ac], name, value); ac++;
    XtSetValues(_xd_rootwidget, al, ac);
}

void xd_XtWidget_c::SetValues(ArgList args, Cardinal num_args)
{
    XtSetValues(_xd_rootwidget, args, num_args);
}

void xd_XtWidget_c::VaSetValues(String name,...)
{
    String attr  = (String) 0 ;
    int    count = 1;

    va_list ap;

    /* Ignore empty argument list */
    if (name == NULL)
	return;

    /* First count the (non-empty) argument list */
    va_start(ap, name);

    va_arg(ap, XtArgVal); // Pop first value

    for (attr = va_arg(ap, String); attr != NULL; attr = va_arg(ap, String))
    {
	va_arg(ap, XtArgVal); // Pop value
	++count;
    }
    va_end(ap);

    /* Now transfer values into an ArgList and throw at XtSetValues*/

    ArgList  al = new Arg[count];
    XtArgVal value;
    Cardinal ac = 0;

    va_start(ap, name);

    value = va_arg(ap, XtArgVal);
    XtSetArg(al[ac], name, value); ac++;

    for (attr = va_arg(ap, String); attr != NULL; attr = va_arg(ap, String))
    {
	value = va_arg(ap, XtArgVal);
	if (value)
	{
	    XtSetArg(al[ac], attr, value); ac++;
	}
    }
    va_end(ap);
    XtSetValues(_xd_rootwidget, al, ac);

    /* Tidy up - commented out version is for aged compilers */
    //delete [count]al;
    delete [] al;
}

void xd_XtWidget_c::GetValue(String name, void* value) const
{
    Arg      al[1];
    Cardinal ac = 0;

    if (_xd_rootwidget) {
    	XtSetArg(al[ac], name, value); ac++;
    	XtGetValues(_xd_rootwidget, al, ac);
    }
}

void xd_XtWidget_c::GetValues(ArgList args, Cardinal num_args) const
{
	if (_xd_rootwidget)
    		XtGetValues(_xd_rootwidget, args, num_args);
}

void xd_XtWidget_c::VaGetValues(String name,...) const
{
    String attr  = (String) 0 ;
    int    count = 1;
    va_list ap;

    /* Ignore empty argument list */
    if (name == NULL)
	return;

    /* First count the (non-empty) argument list */
    va_start(ap, name);

    va_arg(ap, XtArgVal); // Pop first value
    for (attr = va_arg(ap, String); attr != NULL; attr = va_arg(ap, String))
    {
	va_arg(ap, XtArgVal); // Pop value
	++count;
    }
    va_end(ap);

    /* Now transfer values into an ArgList and throw at XtGetValues*/

    ArgList  al = new Arg[count];
    XtArgVal value;
    Cardinal ac = 0;

    va_start(ap, name);
    value = va_arg(ap, XtArgVal);
    XtSetArg(al[ac], name, value); ac++;

    for (attr = va_arg(ap, String); attr != NULL; attr = va_arg(ap, String))
    {
	value = va_arg(ap, XtArgVal);
	if (value)
	{
	    XtSetArg(al[ac], attr, value); ac++;
	}
    }
    va_end(ap);
    XtGetValues(_xd_rootwidget, al, ac);

    /* Tidy up - commented out version is for aged compilers */
    //delete [count]al;
    delete [] al;
}

void xd_XtWidget_c::Map(void)
{
    if (_xd_rootwidget) 
	XtMapWidget(_xd_rootwidget);
}

void xd_XtWidget_c::Unmap(void)
{
    if (_xd_rootwidget) 
	XtUnmapWidget(_xd_rootwidget);
}

void xd_XtWidget_c::xd_enable(void)
{
    if (_xd_rootwidget) 
	XtSetSensitive(_xd_rootwidget, TRUE);
}

void xd_XtWidget_c::xd_disable(void)
{
    if (_xd_rootwidget) 
	XtSetSensitive(_xd_rootwidget, FALSE);
}

void xd_XtWidget_c::xd_destroy(void)
{
    if (_xd_rootwidget) {
	XtDestroyWidget(_xd_rootwidget);
	_xd_rootwidget = NULL;
    }
}

void xd_ApplicationShell_c::xd_exit(int status)
{
    exit(status);
}

void xd_ApplicationShell_c::Realize(void)
{
    if (_xd_rootwidget) 
	XtRealizeWidget(_xd_rootwidget);
}

void xd_ChildWidget_c::Manage(void)
{
    if (_xd_rootwidget) 
	XtManageChild(_xd_rootwidget);
}

void xd_ChildWidget_c::Unmanage(void)
{
    if (_xd_rootwidget) 
	XtUnmanageChild(_xd_rootwidget);
}

void xd_NonShellWidget_c::xd_show(void)
{
    Map();
}

void xd_NonShellWidget_c::xd_hide(void)
{
    Unmap();
}
