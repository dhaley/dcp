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
** sccsid = "@(#)helpGuru/libgen/Commands.h	1.1" -- 95/12/13
*/

/*
** Common commands for applications.
*/

#ifndef _H_Commands
#define _H_Commands

enum {
	cmdNull = 0,
	cmdOK,
	cmdCancel,
	cmdNew,
	cmdOpen,
	cmdClose,
	cmdSave,
	cmdSaveAs,
	cmdRevert,
	cmdUndo,
	cmdRedo,
	cmdCut,
	cmdCopy,
	cmdPaste,
	cmdClear,
	cmdHelp,
	cmdHelpOnVersion,
	cmdHelpIndex,
	cmdUser			// Add your own commands after cmdUser
};

#endif
