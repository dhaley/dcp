/*
** Generated by X-Designer
*/
#ifndef _main_xd_h
#define _main_xd_h

#define XD_MOTIF_MFC

#include <xdclass.h>

class drawing_c: public CWnd {
public:
	virtual void create (CWnd * parent, char *widget_name = NULL, unsigned int id = 0, CRect *in_rect = NULL);
protected:
	void SetCell ( unsigned int x, unsigned int y );
	void draw_line ( unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, unsigned int draw_first);
	void horizontal_line ( unsigned int x0, unsigned int y0, unsigned int x1, unsigned int draw_first );
	void draw_rectangle ( unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1 );
	void fill_rectangle ( unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1 );
	void DrawCells ();
	void DrawGrid ();
	void DrawCell ( unsigned int x, unsigned int y );
	void XGridLine ( unsigned int x );
	void YGridLine ( unsigned int y );
	int initialised;
	colour_type cells[32][32];
	unsigned int start_x, start_y;
#ifdef XD_MOTIF_MFC
	Pixel *colours[8];
	GC gc;
#else
	CBrush *colours[8];
	CDC *dc;
#endif
 
protected:
	static void DoInput( Widget, XtPointer, XtPointer );
	virtual void DoInput();
	static void DoExpose( Widget, XtPointer, XtPointer );
	virtual void DoExpose();
};

typedef drawing_c *drawing_p;

class tool_box_c: public CButton {
public:
	tool_type tool;
	virtual void create (CWnd * parent, char *widget_name = NULL, unsigned int id = 0, CRect *in_rect = NULL);
	tool_box_c();
	virtual ~tool_box_c();
private:
	CButton * toggle1;
	CButton * toggle2;
	CButton * toggle3;
	CButton * toggle4;
public:
	static void Fill( Widget, XtPointer, XtPointer );
	virtual void Fill();
	static void Rectangle( Widget, XtPointer, XtPointer );
	virtual void Rectangle();
	static void Line( Widget, XtPointer, XtPointer );
	virtual void Line();
	static void Pencil( Widget, XtPointer, XtPointer );
	virtual void Pencil();
};

typedef tool_box_c *tool_box_p;

class colour_box_c: public CWnd {
public:
	colour_type colour;

	virtual void create (CWnd * parent, char *widget_name = NULL, unsigned int id = 0, CRect *in_rect = NULL);
	colour_box_c();
	virtual ~colour_box_c();
private:
	CButton * toggle5;
	CButton * toggle6;
	CButton * toggle7;
	CButton * toggle8;
	CButton * toggle9;
	CButton * toggle10;
	CButton * toggle11;
	CButton * toggle12;
protected:
	static void Magenta( Widget, XtPointer, XtPointer );
	virtual void Magenta();
	static void Cyan( Widget, XtPointer, XtPointer );
	virtual void Cyan();
	static void Yellow( Widget, XtPointer, XtPointer );
	virtual void Yellow();
	static void Blue( Widget, XtPointer, XtPointer );
	virtual void Blue();
	static void Green( Widget, XtPointer, XtPointer );
	virtual void Green();
	static void Red( Widget, XtPointer, XtPointer );
	virtual void Red();
	static void White( Widget, XtPointer, XtPointer );
	virtual void White();
	static void Black( Widget, XtPointer, XtPointer );
	virtual void Black();
};

typedef colour_box_c *colour_box_p;

#define IDC_shell_menuBar1 102
#define IDC_shell_cascade1 103
#define ID_shell_button1 32773
#define ID_shell_button2 32774
#define ID_shell_button3 32775
#define IDC_shell_cascade2 108
#define ID_shell_button4 32778
#define ID_shell_button5 32779
#define ID_shell_button6 32780

class shell_c: public CDialog {
public:
	virtual void create (CWinApp *win_app, CRect *in_rect = NULL);

	shell_c();
	virtual ~shell_c();
	tool_box_p tool_box;
	colour_box_p colour_box;
protected:
	drawing_p drawing;
private:
	CMenu * menuBar1;
	CMenu * cascade1;
	CMenu * cascade2;
public:
	static void DoExit( Widget, XtPointer, XtPointer );
	virtual void DoExit();
};

typedef shell_c *shell_p;


extern shell_p shell;


class CXApplicationApp : public CWinApp {
public :
	CXApplicationApp ( const char *pszAppName = NULL );
	BOOL InitInstance ();
	int ExitInstance ();
};

#endif
