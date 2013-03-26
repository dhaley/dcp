#include <stdio.h>
#include <Xm/Command.h>
#include <Xm/ToggleB.h>
#include <Xm/Text.h>

#include "greptool.h"


/* Set command to current value */

/* ARGSUSED */
#ifndef   _NO_PROTO
void setcommand(Widget          w,
                XtPointer       client_data,
		XtPointer       call_data)
#else  /* _NO_PROTO */
void setcommand(w, client_data, call_data)
	Widget          w;
	XtPointer       client_data;
	XtPointer       call_data;
#endif /* _NO_PROTO */
{
	char    buffer[512];
	char    *s;
	ccdata_p ccp = (ccdata_p) client_data ;

	/* Create command buffer - starts with command name */

	(void) strcpy(buffer, "/bin/grep ");

	/* Get values of option buttons and add command line flags */

	if (XmToggleButtonGetState(*(ccp->ignore_case_widget)))
			(void) strcat(buffer, "-i ");
	if (XmToggleButtonGetState(*(ccp->show_lines_widget)))
			(void) strcat(buffer, "-n ");
	if (XmToggleButtonGetState(*(ccp->show_files_widget)))
			(void) strcat(buffer, "-l ");
	if (XmToggleButtonGetState(*(ccp->invert_widget)))
			(void) strcat(buffer, "-v ");
	if (XmToggleButtonGetState(*(ccp->count_lines_widget)))
			(void) strcat(buffer, "-c ");
	if (XmToggleButtonGetState(*(ccp->show_block_widget)))
			(void) strcat(buffer, "-b ");

	/* Add search pattern and search file names */

	if ((s = XmTextGetString(*(ccp->pattern_widget))) != (char *) 0) {
		(void) strcat(buffer, s);
		(void) strcat(buffer, " ");
		XtFree(s);
	}
	if ((s = XmTextGetString(*(ccp->searchfiles_widget))) != (char *) 0) {
		(void) strcat(buffer, s);
		XtFree(s);
	}

	/* Finally, set the value of the command input field */

	XmCommandSetValue(*(ccp->command_widget),
			  XmStringCreate(buffer, XmSTRING_DEFAULT_CHARSET));
}
