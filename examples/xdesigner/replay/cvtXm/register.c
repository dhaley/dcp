#include <stdio.h>
#include <X11/StringDefs.h>
#include <X11/Intrinsic.h>

#ifndef   _NO_PROTO
void RegisterWidgets(void)
#else  /* _NO_PROTO */
void RegisterWidgets()
#endif /* _NO_PROTO */
{
#ifndef   _NO_PROTO
#ifdef    HANDLE_TEXT
	extern int    xdsTextNameToXy(Widget, char *, char *, int *, int *) ;
	extern int    xdsTextXyToName(Widget, int, int, char **, char **) ;
	extern int    xdsTextFieldXyToName(Widget, int, int, char **, char **) ;
	extern int    xdsTextFieldNameToXy(Widget, char *, char *, int *, int *) ;
#endif /* HANDLE_TEXT */

	extern char  * xdsTextGetInput(Widget) ;
	extern Boolean xdsTextPutInput(Widget, char *) ;
	extern int     xdsListNameToXy(Widget, char *, char *, int *, int *) ;
	extern int     xdsListXyToName(Widget, int, int, char **, char **) ;
	extern int     xdsScrollBarNameToXy(Widget, char *, char *, int *, int *) ;
	extern int     xdsScrollBarXyToName(Widget, int, int, char **, char **) ;
	extern int     xdsDaNameToXy(Widget, char *, char *, int  *, int *) ;
	extern int     xdsDaXyToName(Widget, int, int, char **, char **) ;
#else  /* _NO_PROTO */
#ifdef    HANDLE_TEXT
	extern int    xdsTextNameToXy() ;
	extern int    xdsTextXyToName() ;
	extern int    xdsTextFieldXyToName() ;
	extern int    xdsTextFieldNameToXy() ;
#endif /* HANDLE_TEXT */

	extern char  * xdsTextGetInput() ;
	extern Boolean xdsTextPutInput() ;
	extern int     xdsListNameToXy() ;
	extern int     xdsListXyToName() ;
	extern int     xdsScrollBarNameToXy() ;
	extern int     xdsScrollBarXyToName() ;
	extern int     xdsDaNameToXy() ;
	extern int     xdsDaXyToName() ;
#endif /* _NO_PROTO */

	(void) xdsRegister( "XmList", xdsListNameToXy, xdsListXyToName);
	(void) xdsRegister( "XmScrollBar", xdsScrollBarNameToXy, xdsScrollBarXyToName);
	(void) xdsRegister( "XmDrawingArea", xdsDaNameToXy, xdsDaXyToName);

	(void) xdsIMRegister( "XmText", xdsTextGetInput, xdsTextPutInput);
	(void) xdsIMRegister( "XmTextField", xdsTextGetInput, xdsTextPutInput);

#ifdef    HANDLE_TEXT
	(void) xdsRegister( "XmText", xdsTextNameToXy, xdsTextXyToName);
	(void) xdsRegister( "XmTextField", xdsTextFieldNameToXy, xdsTextFieldXyToName);
#endif /* HANDLE_TEXT */
}
