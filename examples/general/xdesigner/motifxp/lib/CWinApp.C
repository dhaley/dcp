#include <iostream.h>
#include <stdlib.h>
#include <Xm/Xm.h>
#include <xdclass.h>

#include <X11/IntrinsicP.h>


static CWinApp *afxCurrentWinApp = NULL ;

CWinApp::CWinApp(const char* pszAppName)
{
    if ( afxCurrentWinApp )
	cerr << "CWinApp::CWinApp: Only a single CWinApp instance is supported" << endl;

    afxCurrentWinApp = this;
    m_nCmdShow       = SW_RESTORE;
    m_pMainWnd       = NULL;
    m_pszAppName     = pszAppName;
    _xd_argc         = 0;
    _xd_argv         = NULL;
    _xd_display      = NULL;
    _xd_app_class    = NULL;
}

BOOL CWinApp::InitInstance(void)
{
    return TRUE;
}

int CWinApp::ExitInstance(void)
{
    return 0;
}

CWinApp* AfxGetApp(void)
{
    return afxCurrentWinApp;
}
