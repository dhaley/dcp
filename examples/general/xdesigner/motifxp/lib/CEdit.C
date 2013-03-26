#include <Xm/Xm.h>
#include <Xm/Text.h>
#include <Xm/ScrolledW.h>
#include <Xm/TextF.h>
#include <xdclass.h>

void CEdit::xd_rootwidget(Widget xd_rootwidget)
{
    CWnd::xd_rootwidget ( xd_rootwidget );

    if (XmIsScrolledWindow(xd_rootwidget))
    {
	WidgetList children    = (WidgetList) 0 ;
	Cardinal   numchildren = (Cardinal) 0 ;
	int        i ;

	XtVaGetValues(xd_rootwidget,
		      XmNchildren, &children,
		      XmNnumChildren, &numchildren,
		      NULL) ;

	for ( i = 0; i < numchildren; i++ )
	    if (XmIsText(children[i]) || XmIsTextField(children[i]))
	    {
		_xd_textwidget = children[i];
		break;
	    }
    }
    else
	_xd_textwidget = _xd_rootwidget;
}

Widget CEdit::xd_textwidget(void)
{
    return _xd_textwidget;
}

BOOL CEdit::xd_enable_window(BOOL bEnable)
{
    // Enable or disable a window
    //  Return value:
    //  0 if the widget has not been created (no call to create() yet).
    //  0 if the window was previously enabled
    //  non-zero if the window was previously disabled.

    if (_xd_textwidget == NULL)
	return FALSE ;

    BOOL wasdisabled =! XtIsSensitive(_xd_textwidget);

    XtSetSensitive(_xd_textwidget, bEnable);

    return wasdisabled ;
}

void CEdit::Clear(void)
{
    // Deletes the currently selected text
    if (_xd_textwidget != NULL)
    {
	if (XmIsText(_xd_textwidget))
	    XmTextRemove(_xd_textwidget);
	else if (XmIsTextField(_xd_textwidget))
	    XmTextFieldRemove(_xd_rootwidget);
    }
}

void CEdit::Copy(void)
{
    // Copies the currently selected text to the clipboard
    if (_xd_textwidget != NULL)
    {
	if (XmIsText(_xd_textwidget))
	    XmTextCopy(_xd_textwidget, XtLastTimestampProcessed(XtDisplay(_xd_textwidget)));
	else if (XmIsTextField(_xd_textwidget))
	    XmTextFieldCopy(_xd_textwidget, XtLastTimestampProcessed(XtDisplay(_xd_textwidget)));
    }
}

void CEdit::Cut(void)
{

    // Deletes the currently selected text and copies it to
    // the clipboard
    if (_xd_textwidget != NULL)
    {
	if (XmIsText(_xd_textwidget))
	    XmTextCut(_xd_textwidget, XtLastTimestampProcessed(XtDisplay(_xd_textwidget)));
	else if (XmIsTextField(_xd_textwidget))
	    XmTextFieldCut(_xd_textwidget, XtLastTimestampProcessed(XtDisplay(_xd_textwidget)));
    }
    return;
}

void CEdit::GetSel(int& nStartChar, int& nEndChar) const
{
    // Get the start and end of the selected text
    // Returns start and end as zero if there is no selected text
    Boolean        has_selection = False ;
    XmTextPosition left          = (XmTextPosition) 0 ;
    XmTextPosition right         = (XmTextPosition) 0 ;
    	
    nStartChar = nEndChar = 0;

    if (_xd_textwidget != NULL)
    {
	if (XmIsText(_xd_textwidget))
	    has_selection = XmTextGetSelectionPosition(_xd_textwidget, &left, &right);
	else if (XmIsTextField(_xd_textwidget))
	    has_selection = XmTextFieldGetSelectionPosition(_xd_textwidget, &left, &right);

	if (has_selection)
	{
	    nStartChar = (int)left;
	    nEndChar   = (int)right;
	}
    }
}

void CEdit::LimitText(int nChars)
{
    // Limit the number of characters that can be typed.
    // Does not limit the size of text that can be set
    // programmatically using SetWindowText().
    // A limit of zero means set the limit to its maximum value
    if (_xd_textwidget != NULL)
	XtVaSetValues(_xd_textwidget, XmNmaxLength, ((nChars == 0) ? UINT_MAX : nChars), NULL);
}

void CEdit::Paste(void)
{
    // Insert data from the clipboard into the text
    if (_xd_textwidget != NULL)
    {
	if (XmIsText(_xd_textwidget))
	    XmTextPaste(_xd_textwidget);
	else if (XmIsTextField(_xd_textwidget))
	    XmTextFieldPaste(_xd_textwidget);
    }
 }

void CEdit::ReplaceSel(LPCSTR lpszNewText)
{
    // Inserts the given text to replace the current selection
    // or at the insert cursor position if there is no selection.
    Boolean        has_selection = False;
    XmTextPosition left          = (XmTextPosition) 0 ;
    XmTextPosition right         = (XmTextPosition) 0 ;

    if (_xd_textwidget!=NULL)
    {
	if (XmIsText(_xd_textwidget))
	{
	    has_selection = XmTextGetSelectionPosition(_xd_textwidget, &left, &right);

	    if (!has_selection)
		left = right = XmTextGetInsertionPosition(_xd_textwidget);

	    XmTextReplace(_xd_textwidget, left, right, (char *)lpszNewText);
	}
	else if (XmIsTextField(_xd_textwidget))
	{
	    has_selection = XmTextFieldGetSelectionPosition(_xd_textwidget, &left, &right);

	    if (!has_selection)
		left = right = XmTextFieldGetInsertionPosition(_xd_textwidget);

	    XmTextFieldReplace(_xd_textwidget, left, right, (char *)lpszNewText);
	}
    }

}

BOOL CEdit::SetReadOnly(BOOL bReadOnly)
{
    // Make the text non-editable
    if (_xd_textwidget == NULL)
	return FALSE;

    XtVaSetValues(_xd_textwidget, XmNeditable, !bReadOnly, NULL);

    return TRUE;
}

void CEdit:: SetSel(int nStartChar, int nEndChar, BOOL bNoScroll)
{
    // Set the current selection.

    if (_xd_textwidget != NULL)
    {
	XtVaSetValues(_xd_textwidget, XmNautoShowCursorPosition, !bNoScroll, NULL);

	XmTextPosition len = XmTextGetLastPosition(_xd_textwidget);

	if (nEndChar > len)
	    nEndChar = (int)len ;

	if (XmIsText(_xd_textwidget))
	    XmTextSetSelection(_xd_textwidget, nStartChar, nEndChar, XtLastTimestampProcessed(XtDisplay(_xd_textwidget)));
	else if (XmIsTextField(_xd_textwidget))
	    XmTextFieldSetSelection(_xd_textwidget, nStartChar, nEndChar, XtLastTimestampProcessed(XtDisplay(_xd_textwidget)));
    }
}

void CEdit::xd_set_window_text(LPCSTR lpszString)
{
    // Implements SetWindowText() for XmText and XmTextField.
    if (_xd_textwidget != NULL)
    {
	if (XmIsText(_xd_textwidget))
	    XmTextSetString(_xd_textwidget, (char *)lpszString);
	else if (XmIsTextField(_xd_textwidget))
	    XmTextFieldSetString(_xd_textwidget, (char *)lpszString);
    }
}

int CEdit::xd_get_window_text(LPSTR lpszStringBuf, int nMaxCount) const
{
    // Implements GetWindowText() for XmText and XmTextField.
    // Return value:
    //  0 if the widget has not been created (no call to create() yet).
    //  The length of the text otherwise.

    if (_xd_textwidget!=NULL)
    {
	char *s = (char *) 0 ;
	if (XmIsText(_xd_textwidget))
	    s = XmTextGetString(_xd_textwidget);
	else if (XmIsTextField(_xd_textwidget))
	    s = XmTextFieldGetString(_xd_textwidget);

	if (s) {
		(void) strncpy(lpszStringBuf, s, nMaxCount - 1);
		XtFree(s);

		lpszStringBuf[nMaxCount-1]='\0';

		return strlen(lpszStringBuf);
    	}
    }

    return 0;
}

int CEdit::xd_get_window_text_length(void) const
{
    // Implements GetWindowTextLength() for XmText and XmTextField
    // Return value:
    //  0 if the widget has not been created (no call to create() yet).
    //  The length of the text otherwise.

    if (_xd_textwidget != NULL)
    {
	char *s = (char *) 0 ;

	if (XmIsText(_xd_textwidget))
	    s = XmTextGetString(_xd_textwidget);
	else if (XmIsTextField(_xd_textwidget))
	    s = XmTextFieldGetString(_xd_textwidget);

	if (s) {
		int length = strlen(s) ;
		
		XtFree(s) ;
		
		return length;
    	}
    }

    return 0;
}
