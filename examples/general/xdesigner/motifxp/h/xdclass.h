// This header defines the base classes used by X-Designer when
// generating Motif code compatible with the Microsoft Foundation
// Classes.  The base classes constitute a subset of the MFC
// classes each presenting a subset of the interface -
// essentially those methods used to query and change the state
// of the objects.  There are no methods which could only be
// implemented by writing code that creates or destroys widgets.
// If you need such functionality you should use a prelude to
// declare a method for it and provide separate Motif and MFC
// implementations.

#ifndef _xdclass_h
#define _xdclass_h

#include <Xm/Xm.h>

#ifndef   XMD_H
#include <X11/XWDFile.h>
#endif /* XMD_H */

// Some basic typdefs and defines for MS Windows compatibility
#define FAR
typedef unsigned int    UINT;
typedef unsigned long   DWORD;

#ifndef   XMD_H
typedef int             BOOL;
#endif /* XMD_H */

typedef int FAR*        LPINT;
typedef char FAR*       LPSTR;
typedef const char FAR* LPCSTR;

// Hiding and showing windows
// Limited subset of MFC values here - can do everything ICCCM allows
// WINUSER.H vc\include
#define SW_HIDE             0
#define SW_SHOWMINIMIZED    2
#define SW_SHOW             5
#define SW_RESTORE          9

// Menu item manipulation
#define MF_BYCOMMAND        0x0000
#define MF_BYPOSITION       0x0400
#define MF_ENABLED          0x0000
#define MF_GRAYED           0x0001
#define MF_UNCHECKED        0x0000
#define MF_CHECKED          0x0008
#define MF_SEPARATOR        0x0800

// Return values from dialog functions
#define IDOK        1
#define IDCANCEL    2

// CFileDialog constants
#define OFN_OVERWRITEPROMPT          0x00000002
#define OFN_HIDEREADONLY             0x00000004

// For max length in CEdit controls
#ifndef   UINT_MAX
#ifndef	  __xlC__
#define   UINT_MAX 0xffff
#endif /* __xlC__  */
#endif /* UINT_MAX */


// Error returns from CListBox
#define LB_ERR (-1)

// TRACE function - use like printf(), but sends output to stderr
void TRACE(LPCSTR pszFormat, ...);

// Forward declaration for API compatibility, but we do not
// use or implement the CRect class
class CRect;
typedef CRect *LPCRECT;


// Again for API compatibility but very simple approach
typedef char* CString;

class CObject
{
// X-Designer related methods and data
public:
    virtual ~CObject() {;}  // virtual destructor to ensure cleanup

protected:
    CObject() {_xd_rootwidget=NULL;}

private:
    // Certain C++ compilers (eg gcc 2.5) require there to be an
    // implementation of the copy constructor. If your application
    // fails to link try using the second version of the constructor
    CObject(const CObject& objectSrc);              // no default copy
    //CObject(const CObject& objectSrc) { abort();} // no default copy
    void operator=(const CObject& objectSrc);       // no default assignment

public:
    virtual Widget xd_rootwidget(void) const           { return _xd_rootwidget; }
    virtual void   xd_rootwidget(Widget xd_rootwidget) {_xd_rootwidget = xd_rootwidget;}

protected:
    Widget _xd_rootwidget;
};

class CCmdTarget : public CObject // Dummy class for compatibility
{
};

class CWnd : public CCmdTarget
{
// Methods for application code
public:
    BOOL IsWindowEnabled(void);
    BOOL EnableWindow(BOOL bEnable = TRUE);
    void SetWindowText(LPCSTR lpszString);
    int  GetWindowText(LPSTR lpszStringBuf, int nMaxCount) const;
    int  GetWindowTextLength() const;
    BOOL ShowWindow(int nCmdShow);

// X-Designer related methods and data
public:
    CWnd(void)      { _xd_window_text = NULL; _xd_call_data = NULL; }
    virtual ~CWnd() { XtFree(_xd_window_text); }

    void                 xd_call_data(XmAnyCallbackStruct *call_data) { _xd_call_data = call_data; }
    XmAnyCallbackStruct *xd_call_data(void)                           { return _xd_call_data; }

protected:
    virtual BOOL xd_enable_window(BOOL bEnable);
    virtual void xd_set_window_text(LPCSTR lpszString);
    virtual int  xd_get_window_text(LPSTR lpszStringBuf, int nMaxCount) const;
    virtual int  xd_get_window_text_length(void) const;
    virtual BOOL xd_show_window(int nCmdShow); // SW_HIDE, SW_RESTORE only

private:
    char                *_xd_window_text;
    XmAnyCallbackStruct *_xd_call_data;
};

class CFrameWnd : public CWnd
{
// X-Designer related methods and data
protected:
    void xd_set_window_text(LPCSTR lpszString);
    int  xd_get_window_text(LPSTR lpszStringBuf, int nMaxCount) const;
    int  xd_get_window_text_length(void) const;
    BOOL xd_show_window(int nCmdShow); // SW_HIDE, SW_RESTORE, SW_SHOWMINIMIZED
};

class CDialog : public CWnd
{
// X-Designer related methods and data
public:
    virtual int DoModal(void);

protected:
    void xd_set_window_text(LPCSTR lpszString);
    int  xd_get_window_text(LPSTR lpszStringBuf, int nMaxCount) const;
    int  xd_get_window_text_length(void) const;
    BOOL xd_show_window(int nCmdShow); // SW_HIDE, SW_RESTORE for all shells
				       // SW_SHOWMINIMIZED for TopLevelShell only

    enum state { ok = IDOK, cancel = IDCANCEL, virgin, undecided} ;

    state _xd_current_state;

    virtual void OnOK(void);
    static  void xd_OnOk(Widget, XtPointer, XtPointer);

    virtual void OnCancel(void);
    static  void xd_OnCancel(Widget, XtPointer, XtPointer);
};

class CFileDialog : public CDialog
{
public:
    CFileDialog(BOOL   bOpenFileDialog,     // TRUE for FileOpen, FALSE for FileSaveAs
	        LPCSTR lpszDefExt   = NULL, // Ignored
		LPCSTR lpszFileName = NULL,
		DWORD  dwFlags      = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, // Ignored
		LPCSTR lpszFilter   = NULL,
		CWnd*  pParentWnd   = NULL);

    virtual     ~CFileDialog(void);
    virtual BOOL OnInitDialog(void);
    virtual int  DoModal(void);
    CString      GetPathName(void) const;  // return full path name

// X-Designer related methods and data
protected:
    BOOL  _xd_bOpenFileDialog;
    LPSTR _xd_lpszFileName;
    LPSTR _xd_lpszFilter;
    CWnd* _xd_pParentWnd;
    CWnd*  xd_ParentWnd(void) const { return _xd_pParentWnd; }

    enum state { ok = IDOK, cancel = IDCANCEL, virgin, undecided } ;

    state _xd_current_state;

    virtual void OnOK(void);
    static  void xd_OnOk(Widget, XtPointer, XtPointer);

    virtual void OnCancel(void);
    static  void xd_OnCancel(Widget, XtPointer, XtPointer);
};

class CMenu : public CObject
{
// Methods for application code
public:
    CMenu(void);
    ~CMenu();

    UINT CheckMenuItem(UINT nIDCheckItem, UINT nCheck);
    UINT EnableMenuItem(UINT nIDEnableItem, UINT nEnable);
    UINT GetMenuState(UINT nID, UINT nFlags);
    BOOL TrackPopupMenu(UINT nFlags, int x, int y, CWnd *pWnd, LPCRECT lpRect = 0);

// X-Designer related methods and data
public:
    // Maintains a mapping from item IDs to widgets
    void xd_register_menu_item(UINT nIDItem, Widget item);
    // Maintains a list of submenus
    void xd_register_menu(CMenu *menu);

protected:
    class IDmap
    {
    public:
	UINT id;
	Widget w;
    };

    Widget   xd_get_menu_item_by_position(UINT nPos);
    Widget   xd_get_menu_item_by_id(UINT nIDItem);
    IDmap  *_xd_items;
    int     _xd_next_item;
    int     _xd_items_allocated;
    CMenu **_xd_menus;
    int     _xd_next_menu;
    int     _xd_menus_allocated;
};

class CSplitterWnd : public CWnd
{
};

// ComboBox error status codes

#define   CB_ERR        -1
#define   CB_ERRSPACE   -2

class CComboBox : public CWnd
{
// Methods for application code
public:
    int GetCurSel(void) const;
    int GetLBText(int nIndex, LPSTR lpszText) const;
    int GetLBTextLen(int nIndex) const;
    int SetCurSel(int nSelect);
	
    // Added: must implement these into main X-Designer tree...
    void ResetContent(void);
    int  InsertString(int nIndex, LPCSTR lpszItem);

// X-Designer related methods and data
protected:
    void xd_set_window_text(LPCSTR) {} // NOOP for CComboBox
    int  xd_get_window_text(LPSTR lpszStringBuf, int nMaxCount) const;
    int  xd_get_window_text_length(void) const;
};

class CStatic : public CWnd
{
// X-Designer related methods and data
protected:
    void xd_set_window_text(LPCSTR lpszString);
    int  xd_get_window_text(LPSTR lpszStringBuf, int nMaxCount) const;
    int  xd_get_window_text_length(void) const;
};

class CButton : public CWnd
{
// Methods for application code
public:
    int  GetCheck(void) const; // Only sensible for toggle buttons
    void SetCheck(int nCheck); // Only sensible for toggle buttons

// X-Designer related methods and data
protected:
    void xd_set_window_text(LPCSTR lpszString);
    int  xd_get_window_text(LPSTR lpszStringBuf, int nMaxCount) const;
    int  xd_get_window_text_length(void) const;
};

class CBitmapButton : public CButton
{
};

class CListBox : public CWnd
{
// Methods for application code
public:
    CListBox(void) { _xd_listwidget = NULL; }

    int  DeleteString(UINT nIndex);
    int  GetCount(void) const;
    int  GetCurSel(void) const;
    int  GetSel(int nIndex) const;
    int  GetSelCount(void) const;
    int  GetSelItems(int nMaxItems, LPINT rgIndex) const;
    int  GetText(int nIndex, LPSTR lpszBuffer) const;
    int  GetTextLen(int nIndex) const;
    int  GetTopIndex(void) const;
    int  InsertString(int nIndex, LPCSTR lpszItem);
    void ResetContent(void);
    int  SelItemRange(BOOL bSelect, int nFirstItem, int nLastItem);
    int  SetCurSel(int nSelect);
    int  SetSel(int nIndex, BOOL bSelect = TRUE);
    int  SetTopIndex(int nIndex);
// For Scrolled list the list widget will not be the same as the root widget
    void   xd_rootwidget(Widget xd_rootwidget);
    Widget xd_rootwidget(void) const {return CWnd::xd_rootwidget();}
    Widget xd_listwidget(void);

// X-Designer related methods and data
protected:
    virtual BOOL xd_enable_window(BOOL bEnable);

private:
    Widget _xd_listwidget;
};

class CEdit : public CWnd
{
// Methods for application code
public:
    CEdit(void) {_xd_textwidget=NULL;}

    void Clear(void);
    void Copy(void);
    void Cut(void);
    void GetSel(int& nStartChar, int& nEndChar) const;
    void LimitText(int nChars = 0);
    void Paste(void);
    void ReplaceSel(LPCSTR lpszNewText);
    BOOL SetReadOnly(BOOL bReadOnly = TRUE);
    void SetSel(int nStartChar, int nEndChar, BOOL bNoScroll = FALSE);
// For Scrolled text the text widget will not be the same as the root widget
    void   xd_rootwidget(Widget xd_rootwidget);
    Widget xd_rootwidget(void) const {return CWnd::xd_rootwidget();}
    Widget xd_textwidget(void);

// X-Designer related methods and data
protected:
    virtual BOOL xd_enable_window(BOOL bEnable);
    void         xd_set_window_text(LPCSTR lpszString);
    int          xd_get_window_text(LPSTR lpszStringBuf, int nMaxCount) const;
    int          xd_get_window_text_length(void) const;

private:
    Widget _xd_textwidget;
};

class CScrollBar : public CWnd
{
// Methods for application code
public:
    int  GetScrollPos(void) const;
    int  GetPos(void) const { return GetScrollPos(); }
    void GetScrollRange(LPINT lpMinPos, LPINT lpMaxPos) const;
    int  SetScrollPos(int nPos, BOOL bRedraw = TRUE);
    int  SetPos( int nPos ) { return SetScrollPos( nPos ); }
    void SetScrollRange(int nMinPos, int nMaxPos, BOOL bRedraw = TRUE);
    void ShowScrollBar(BOOL bShow = TRUE);
};

class CWinApp : public CCmdTarget
{
public:
	CWinApp(const char* pszAppName = NULL);

	virtual int ExitInstance(void);
	virtual BOOL InitInstance(void);

	const char *m_pszAppName;
	int         m_nCmdShow;
	CWnd       *m_pMainWnd;
	LPSTR       m_lpCmdLine;
	Display   *xd_display() const            { return _xd_display; }
	void       xd_display(Display *display)  { _xd_display = display; }
	char     **xd_argv(void) const           { return _xd_argv; }
	void       xd_argv(char **argv)          { _xd_argv = argv; }
	int        xd_argc(void) const           { return _xd_argc; }
	void       xd_argc(int argc)             { _xd_argc = argc; }
	char      *xd_app_class(void) const      { return _xd_app_class; }
	void       xd_app_class(char *app_class) { _xd_app_class=app_class; }

private:
	int      _xd_argc;
	char   **_xd_argv;
	Display *_xd_display;
	char    *_xd_app_class;
};

class CTabCtrl : public CWnd
{
};

extern CWinApp *AfxGetApp(void);

#endif /* _xdclass_h */
