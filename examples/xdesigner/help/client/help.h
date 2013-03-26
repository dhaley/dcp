/* X-Designer
** (c) 1992, 1993, 1994, 1995, 1996
** Imperial Software Technology (IST),
** 95 London Street,
** Reading,
** Berkshire,
** United Kingdom RG1 4QA.
**
** Telephone: +44 1734 587055
** Fax:       +44 1734 589005
** Email:     support@ist.co.uk
*/


/*
** sccsid = "@(#)dist/release/src/help/client/help.h	1.9" -- 98/02/25
*/

/*
** help:
**
** Interface to help appl.
**
** Jeremy Huxtable 1995
*/

#ifndef _H_XDHelp
#define _H_XDHelp

#include <Xm/Xm.h>
#include <X11/Xatom.h>

#ifdef __cplusplus
extern "C" {
#endif

#define QUIT_HELP_SYSTEM_MSG "*** QUIT HELP SYSTEM"

extern int  XDHelp( Widget w, char *topic ) ;
extern void  QuitHelpViewer( Widget w ) ;
extern void XDHelpGetAtoms( Widget w ) ;

extern Atom helpWin, helpDest ;

#ifdef __cplusplus
}
#endif

#endif
