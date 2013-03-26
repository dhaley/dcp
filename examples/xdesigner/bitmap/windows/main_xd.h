/*
** Generated by X-Designer
*/
#ifndef _main_xd_h
#define _main_xd_h

#define XD_WINDOWS_MFC

#include <afxcmn.h>


#define IDC_shell_drawing 113

class drawing_c: public CWnd {
public:
	void AddChildItem (UINT nID, CWnd *parent);
	virtual void create ( CWnd *parent, CWnd *root_dialog );
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
 
	CRect rect;
protected:
	//{{AFX_MSG(drawing_c)
		afx_msg void OnPaint();
		afx_msg void OnLButtonDown( UINT nFlags, CPoint point );
		afx_msg void OnLButtonUp( UINT nFlags, CPoint point );
		afx_msg BOOL OnEraseBkgnd ( CDC *pDC );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP ()
};

typedef drawing_c *drawing_p;

#define IDC_shell_tool_box 115
#define IDC_tool_box_toggle1 116
#define IDC_tool_box_toggle2 117
#define IDC_tool_box_toggle3 118
#define IDC_tool_box_toggle4 119

class tool_box_c: public CButton {
public:
	tool_type tool;
	void AddChildItem (UINT nID, CWnd *parent);
	virtual void create ( CWnd *parent, CWnd *root_dialog );
	tool_box_c();
	virtual ~tool_box_c();
	CRect rect;
private:
	CButton * toggle1;
	CButton * toggle2;
	CButton * toggle3;
	CButton * toggle4;
public:
	virtual void Fill();
	virtual void Rectangle();
	virtual void Line();
	virtual void Pencil();
protected:
	//{{AFX_MSG(tool_box_c)
		afx_msg void OnValueChanged_toggle1();
		afx_msg void OnValueChanged_toggle2();
		afx_msg void OnValueChanged_toggle3();
		afx_msg void OnValueChanged_toggle4();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP ()
};

typedef tool_box_c *tool_box_p;

#define IDC_shell_colour_box 121
#define IDC_colour_box_toggle5 122
#define IDC_colour_box_toggle6 123
#define IDC_colour_box_toggle7 124
#define IDC_colour_box_toggle8 125
#define IDC_colour_box_toggle9 126
#define IDC_colour_box_toggle10 127
#define IDC_colour_box_toggle11 128
#define IDC_colour_box_toggle12 129

class colour_box_c: public CWnd {
public:
	colour_type colour;

	void AddChildItem (UINT nID, CWnd *parent);
	virtual void create ( CWnd *parent, CWnd *root_dialog );
	colour_box_c();
	virtual ~colour_box_c();
	CRect rect;
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
	virtual void Magenta();
	virtual void Cyan();
	virtual void Yellow();
	virtual void Blue();
	virtual void Green();
	virtual void Red();
	virtual void White();
	virtual void Black();
protected:
	//{{AFX_MSG(colour_box_c)
		afx_msg void OnValueChanged_toggle5();
		afx_msg void OnValueChanged_toggle6();
		afx_msg void OnValueChanged_toggle7();
		afx_msg void OnValueChanged_toggle8();
		afx_msg void OnValueChanged_toggle9();
		afx_msg void OnValueChanged_toggle10();
		afx_msg void OnValueChanged_toggle11();
		afx_msg void OnValueChanged_toggle12();
		afx_msg BOOL OnEraseBkgnd ( CDC *pDC );
		afx_msg HBRUSH OnCtlColor ( CDC *pDC, CWnd *pWnd, UINT nCtlColor );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP ()
};

typedef colour_box_c *colour_box_p;

#define IDD_shell 100
#define IDC_shell_menuBar1 102
#define IDC_shell_cascade1 103
#define ID_shell_button1 32773
#define ID_shell_button2 32774
#define ID_shell_button3 32775
#define IDC_shell_cascade2 108
#define ID_shell_button4 32778
#define ID_shell_button5 32779
#define ID_shell_button6 32780
#define IDC_shell_separator1 120

class shell_c: public CDialog {
public:
	//{{AFX_DATA(shell_c)
		enum {IDD = IDD_shell};
	//}}AFX_DATA
	virtual BOOL OnInitDialog();

	shell_c();
	virtual ~shell_c();
	tool_box_p tool_box;
	colour_box_p colour_box;
protected:
	drawing_p drawing;
	CRect rect;
private:
	CMenu * menuBar1;
	CMenu * cascade1;
	CMenu * cascade2;
public:
	virtual void DoExit();
protected:
	//{{AFX_MSG(shell_c)
		afx_msg void OnActivate_button3();
		afx_msg void OnSize ( UINT nType, int cx, int cy );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP ()
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
