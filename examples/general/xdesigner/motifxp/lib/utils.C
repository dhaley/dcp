#include <stdio.h>
#include <stdarg.h>
#include <xdclass.h>
#include <Xm/AtomMgr.h>
#include <utils.h>

void TRACE(LPCSTR pszFormat, ...)
{
     va_list ap;

     va_start (ap, pszFormat);
     vfprintf(stderr, pszFormat, ap);
     va_end (ap);
}

char *xd_text_from_XmString(XmString xmstr)
{
    // Extract char * from XmString
    // Caller frees returned char*

#if       (XmVERSION > 1)
    char *s = (char *) XmStringUnparse(xmstr, NULL, XmCHARSET_TEXT, XmCHARSET_TEXT, NULL, 0, XmOUTPUT_ALL) ;
#else  /* (XmVERSION > 1) */
    char *s = XtMalloc(1);
    *s = '\0';

    XmStringContext context;

    XmStringInitContext(&context, xmstr);

    for (;;)
    {
	char             *p;
	XmStringCharSet   tag;
	XmStringDirection direction;
	Boolean           separator;
	Boolean           ok = XmStringGetNextSegment(context, &p, &tag, &direction, &separator);

	if (!ok)
	    break;

	s = XtRealloc(s, strlen(s) + strlen(p) + 1);

	(void) strcat(s, p);

	XtFree(p);
	XtFree(tag);
    }

    XmStringFreeContext(context);
#endif  /* (XmVERSION > 1) */

    return s;
}

char *xd_text_from_XmLabel(Widget rootwidget)
{
    // Extracts char* from XmLabel widget labelString resource
    // Caller frees returned char*

    XmString label = (XmString) 0 ;
    char    *value = (char *) 0 ;

    XtVaGetValues(rootwidget, XmNlabelString, &label, NULL);

    value = xd_text_from_XmString(label);

    XmStringFree(label) ;

    return value ;
}

unsigned long xd_get_visibility_state(Widget rootwidget)
{
    // Work out if an ApplicationShell or TopLevelShell is visible.
    // This implementation inspects the WM_STATE property of the
    // window (which is a bit naughty, see the ICCCM)

    Display *display = XtDisplay(rootwidget);
    Window   window  = XtWindow(rootwidget);

    unsigned long *property = (unsigned long *) 0;
    unsigned long state     = WithdrawnState; // If in doubt assume withdrawn
    unsigned long nitems, leftover;

    Atom actual_type;
    int  actual_format;

    if (window != (Window) 0)
    {
	Atom xa_WM_STATE = XmInternAtom(display, "WM_STATE", FALSE);

	XGetWindowProperty(display, 
			   window,
			   xa_WM_STATE,
			   0L,
			   1,
			   False,
			   xa_WM_STATE,
			   &actual_type,
			   &actual_format,
			   &nitems,
			   &leftover,
			   (unsigned char **) &property);

	if (property != (unsigned long *) 0) {
		state = *property;
	
		XFree((char *)property);
	}
    }

    return state;
}
