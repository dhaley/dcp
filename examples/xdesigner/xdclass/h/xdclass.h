#ifndef XDCLASS_H
#define XDCLASS_H
#ifdef __cplusplus

#include <Xm/Xm.h>
#include <stdlib.h>

class xd_base_c
{
    public:
	xd_base_c(void)              {_xd_rootwidget=NULL;}
	Widget xd_rootwidget() const {return _xd_rootwidget;}

    protected:
	Widget _xd_rootwidget;

    private:
	void operator=(xd_base_c&); // No assignment

	// Certain C++ compilers (eg gcc 2.5) require there to be an
	// implementation of the copy constructor. If your application
	// fails to link try using the second version of the constructor
	//xd_base_c(xd_base_c&) ;           // No default copy
	xd_base_c(xd_base_c&) { abort();}   // No default copy
};

class xd_XtWidget_c: public xd_base_c
{
    public:
	xd_XtWidget_c(void);

	void SetValue(String name, XtArgVal value);
	void SetValues(ArgList args, Cardinal num_args);
	void VaSetValues(String name,...);
	void GetValue(String name, void *value) const;
	void GetValues(ArgList args, Cardinal num_args) const;
	void VaGetValues(String name,...) const;
	void Map(void);
	void Unmap(void);

    public:
	virtual void xd_enable(void);
	virtual void xd_disable(void);
	virtual void xd_destroy(void);
};

class xd_TopLevelShell_c: public xd_XtWidget_c
{
};

class xd_ApplicationShell_c: public xd_TopLevelShell_c
{
    public:
	void xd_exit(int status=0);
	void Realize(void);
};

class xd_ChildWidget_c: public xd_XtWidget_c
{
    public:
	virtual void xd_show()=0;
	virtual void xd_hide()=0;

	void Manage(void);
	void Unmanage(void);
};

class xd_XmDialog_c: public xd_ChildWidget_c
{
    public:
	xd_XmDialog_c(void);
	virtual void xd_show(void);
	virtual void xd_hide(void);
	void         Raise(void);
    protected:
	Widget xd_getchildwidget(void);
	Widget xd_childwidget;
};

class xd_NonShellWidget_c: public xd_ChildWidget_c
{
    public:
	virtual void xd_show(void);
	virtual void xd_hide(void);
};

class xd_XmLabel_c: public xd_NonShellWidget_c
{
};

class xd_XmCascadeButton_c: public xd_NonShellWidget_c
{
};

class xd_XmDrawnButton_c: public xd_NonShellWidget_c
{
};

class xd_XmPushButton_c: public xd_NonShellWidget_c
{
};

class xd_XmToggleButton_c: public xd_NonShellWidget_c
{
};

class xd_XmArrowButton_c: public xd_NonShellWidget_c
{
};

class xd_XmList_c: public xd_NonShellWidget_c
{
};

class xd_XmScrollBar_c: public xd_NonShellWidget_c
{
};

class xd_XmSeparator_c: public xd_NonShellWidget_c
{
};

class xd_XmText_c: public xd_NonShellWidget_c
{
};

class xd_XmTextField_c: public xd_NonShellWidget_c
{
};

class xd_XmBulletinBoard_c: public xd_NonShellWidget_c
{
};

class xd_XmRowColumn_c: public xd_NonShellWidget_c
{
};

class xd_XmRadioBox_c: public xd_NonShellWidget_c
{
};

class xd_XmDrawingArea_c: public xd_NonShellWidget_c
{
};

class xd_XmPanedWindow_c: public xd_NonShellWidget_c
{
};

class xd_XmFrame_c: public xd_NonShellWidget_c
{
};

class xd_XmScale_c: public xd_NonShellWidget_c
{
};

class xd_XmScrolledWindow_c: public xd_NonShellWidget_c
{
};

class xd_XmScrolledText_c: public xd_NonShellWidget_c
{
};

class xd_XmScrolledList_c: public xd_NonShellWidget_c
{
};

class xd_XmMainWindow: public xd_NonShellWidget_c
{
};

class xd_XmSelectionBox_c: public xd_NonShellWidget_c
{
};

class xd_XmFileSelectionBox_c: public xd_NonShellWidget_c
{
};

class xd_XmCommand_c: public xd_NonShellWidget_c
{
};

class xd_XmMessageBox_c: public xd_NonShellWidget_c
{
};

class xd_XmMainWindow_c: public xd_NonShellWidget_c
{
};

class xd_XmForm_c: public xd_NonShellWidget_c
{
};

class xd_XmMenuBar_c: public xd_NonShellWidget_c
{
};

class xd_XmPulldownMenu_c: public xd_NonShellWidget_c
{
};

class xd_XmPopupMenu_c: public xd_NonShellWidget_c
{
};

class xd_XmOptionMenu_c: public xd_NonShellWidget_c
{
};

/*
** Java Emulation Widgets
*/

class xd_XdBorder_c: public xd_NonShellWidget_c 
{ 
}; 

class xd_XdCard_c: public xd_NonShellWidget_c 
{ 
}; 

class xd_XdGrid_c: public xd_NonShellWidget_c 
{ 
}; 

class xd_XdGridBag_c: public xd_NonShellWidget_c 
{ 
}; 

class xd_XdFlow_c: public xd_NonShellWidget_c 
{ 
}; 

/*
** Motif 2.1 Widgets
*/

class xd_XmComboBox_c: public xd_NonShellWidget_c
{
};

class xd_XmContainer_c: public xd_NonShellWidget_c
{
};

class xd_XmSpinBox_c: public xd_NonShellWidget_c
{
};

class xd_XmSimpleSpinBox_c: public xd_NonShellWidget_c
{
};

class xd_XmNotebook_c: public xd_NonShellWidget_c
{
};

class xd_XmIconGadget_c: public xd_NonShellWidget_c
{
};

class xd_XmGrabShell_c: public xd_XtWidget_c
{
};

class xd_XmPrintShell_c: public xd_ApplicationShell_c
{
};

class xd_SessionShell_c: public xd_ApplicationShell_c
{
};

// For Straight Motif C++ code generation
// The widget internals sort out the CWnd.

class xd_XdTable_c: public xd_XtWidget_c
{
};

#endif /*__cplusplus*/
#endif /*XDCLASS_H*/
