#include <stdio.h>
#include <stdlib.h>
#include <Xm/Xm.h>
#include <xdclass.h>
#include <utils.h>

#ifndef   MAX_FILTER_STRING
#define   MAX_FILTER_STRING     512
#endif /* MAX_FILTER_STRING */

#ifdef    VMS
#ifndef   STRDUP_SUPPORTED
#include <stdlib.h>
#define   _STRDUP_UNSUPPORTED
#endif /* STRDUP_SUPPORTED */
#endif /* VMS */

#ifdef    _STRDUP_UNSUPPORTED
#define   _LPCSTR_COPY        _LpcstrCopy

static LPCSTR _LpcstrCopy(LPCSTR s)
{
	register char *cptr = (char *) 0 ;

	if (s != (LPCSTR) 0) {
		cptr = (char *) malloc((unsigned) (strlen((char *) s) + 1)) ;

		if (cptr != (char *) 0) {
			(void) strcpy(cptr,(char *) s) ;
		}
	}

	return (LPCSTR) cptr ;
}
#endif /* _STRDUP_UNSUPPORTED */

#ifndef   _LPCSTR_COPY
#define   _LPCSTR_COPY        strdup
#endif /* _LPCSTR_COPY */


CFileDialog::CFileDialog(BOOL     bOpenFileDialog,
			 LPCSTR   lpszDefExt,   // Ignored 
			 LPCSTR   lpszFileName,
			 DWORD  /*dwFlags*/,    // Ignored
			 LPCSTR /*lpszFilter*/, //Ignored 
			 CWnd*    pParentWnd)
{
    _xd_bOpenFileDialog = bOpenFileDialog ;

    if ( lpszFileName )
	_xd_lpszFileName = _LPCSTR_COPY(lpszFileName);
    else
	_xd_lpszFileName = NULL;

    if ( lpszDefExt)
	_xd_lpszFilter = _LPCSTR_COPY(lpszDefExt); //Modified to use actual filter
    else
	_xd_lpszFilter = NULL;

    _xd_pParentWnd    = pParentWnd;
    _xd_current_state = virgin;
}

CFileDialog::~CFileDialog(void)
{
    if (_xd_lpszFileName)
	free(_xd_lpszFileName);

    if (_xd_lpszFilter)
	free(_xd_lpszFilter);

    _xd_lpszFileName = NULL ;
    _xd_lpszFilter   = NULL ;
}

BOOL
CFileDialog::OnInitDialog(void)
{
    return TRUE;
}

int
CFileDialog::DoModal(void)
{
    // Have to set resources and callbacks to emulate MFC behaviour
    // and use private event loop so that we can return
    // a value.
    WidgetList children         = (WidgetList) 0 ;
    Cardinal   numChildren      = (Cardinal) 0 ;

    if (_xd_current_state == virgin)
    {
	OnInitDialog ();

	XmString   xm_name_string   = NULL;
	XmString   xm_filter_string = NULL;

	XtVaGetValues(_xd_rootwidget, XmNchildren, &children, XmNnumChildren, &numChildren, NULL);

	if (numChildren &&  children && children[0] )
	{
	    XtAddCallback(children[0], XmNokCallback, xd_OnOk, this);
	    XtAddCallback(children[0], XmNcancelCallback, xd_OnCancel, this);
	    XtAddCallback(_xd_rootwidget, XmNpopdownCallback, xd_OnCancel, this);

	    if (_xd_lpszFilter)
	    {
                char filter[MAX_FILTER_STRING + 1];

                if (_xd_lpszFileName)
                    (void) sprintf(filter,"%s",_xd_lpszFileName);

#if       (XmVERSION > 1)
		xm_filter_string = XmStringGenerate ( (XtPointer) filter, XmFONTLIST_DEFAULT_TAG, XmCHARSET_TEXT, NULL );
#else  /* (XmVERSION > 1) */
		xm_filter_string = XmStringCreateLtoR ( filter, XmFONTLIST_DEFAULT_TAG );
#endif /* (XmVERSION > 1) */

                if (xm_filter_string) {
                    XtVaSetValues(children[0], XmNpattern, xm_filter_string, NULL ) ;
                    XmStringFree(xm_filter_string) ;
                }
	    }

	    if (_xd_lpszFileName)
	    {
#if       (XmVERSION > 1)
		xm_name_string = XmStringGenerate((XtPointer) _xd_lpszFileName, XmFONTLIST_DEFAULT_TAG, XmCHARSET_TEXT, NULL );
#else  /* (XmVERSION > 1) */
		xm_name_string = XmStringCreateLtoR ( _xd_lpszFileName, XmFONTLIST_DEFAULT_TAG );
#endif /* (XmVERSION > 1) */

                if (xm_name_string) {
                    XtVaSetValues ( children[0], XmNdirSpec, xm_name_string, NULL );

                    XmStringFree ( xm_name_string );
                }
	    }
	}
    }

    _xd_current_state = undecided;
    // Popup the dialog
    if (children == (WidgetList) 0)
	XtVaGetValues(_xd_rootwidget, XmNchildren, &children, XmNnumChildren, &numChildren, NULL);

    if (!numChildren || !children || !children[0])
    
    XtManageChild(children[0]);

    XtAppContext app_context = XtWidgetToApplicationContext(_xd_rootwidget);
    XEvent       event;
    // Process events until Ok or Cancel callback triggered
    
    while (_xd_current_state == undecided)
    {
	XtAppNextEvent(app_context, &event);
	XtDispatchEvent(&event);
    }

    XtUnmanageChild(children[0]);

    return _xd_current_state ;
}

CString
CFileDialog::GetPathName(void) const
{
    static char *s = NULL ;

    XtFree(s) ;

    s = (char *) 0 ;

    if (_xd_current_state != ok)
	return (CString) "";

    XmString   xmstr       = (XmString) 0 ;
    WidgetList children    = (WidgetList) 0 ;
    Cardinal   numChildren = (Cardinal) 0 ;

    XtVaGetValues(_xd_rootwidget, XmNchildren, &children, XmNnumChildren, &numChildren, NULL);

    if (numChildren && children && children[0])
    	XtVaGetValues(children[0], XmNdirSpec, &xmstr, NULL);

    if (xmstr) {
    	s = xd_text_from_XmString(xmstr);

    	XmStringFree(xmstr);
    }

    return (s ? s : (CString) "") ;
}

void
CFileDialog::xd_OnOk(Widget, XtPointer client_data, XtPointer)
{
    CFileDialog *instance = (CFileDialog *)client_data;

    instance->OnOK();
}

void
CFileDialog::OnOK(void)
{
    _xd_current_state = ok;
}

void
CFileDialog::xd_OnCancel(Widget, XtPointer client_data, XtPointer)
{
    CFileDialog *instance = (CFileDialog *)client_data;

    instance->OnCancel();
}

void
CFileDialog::OnCancel(void)
{
    // From cancel button or popdown (via WM menu or OK button)
    if (_xd_current_state == undecided)
	_xd_current_state = cancel;
}
