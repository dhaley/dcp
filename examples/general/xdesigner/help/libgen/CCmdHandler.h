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
** sccsid = "@(#)helpGuru/libgen/CCmdHandler.h	1.1" -- 95/12/13
*/

#ifndef _H_CCmdHandler
#define _H_CCmdHandler

#include <Xm/Xm.h>

class CCmdHandler {
public:
	CCmdHandler *nextInChain;

	CCmdHandler() { nextInChain = 0; }
	CCmdHandler(CCmdHandler *aNext) { nextInChain = aNext; }
	virtual Boolean OnCommand(long cmd) { return nextInChain ? nextInChain->OnCommand(cmd) : FALSE; }
	virtual Boolean OnUpdateCommand(long cmd) { return nextInChain ? nextInChain->OnUpdateCommand(cmd) : FALSE; }
	virtual Boolean DispatchCommand(long cmd, Boolean bUpdate) { return bUpdate ? OnUpdateCommand(cmd) : OnCommand(cmd); }
};

#endif

