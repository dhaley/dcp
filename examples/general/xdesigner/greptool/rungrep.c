#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/Text.h>

#include "greptool.h"

/*
** Run command, acquire stdout and stderr separately.
** If any errors, pop up error dialog and display them.
*/


#ifndef   _NO_PROTO
void rungrep(Widget                   w,
             XtPointer                client_data,
	     XmCommandCallbackStruct *call_data)
#else  /* _NO_PROTO */
void rungrep(w, client_data, call_data)
	Widget                   w;
	XtPointer                client_data;
	XmCommandCallbackStruct *call_data;
#endif /* _NO_PROTO */
{
	char                    buffer[512];
	int                     pid, outpos, errpos, waitstat;
	int                     pipestdout[2], pipestderr[2];
	FILE                    *grepout, *greperr;
	XmStringContext         context;
	char                    *text;
	XmStringCharSet         charset;
	XmStringDirection       direction;
	Boolean                 separator;
	rcdata_p                rcp ;
	
	if ((rcp = (rcdata_p) client_data) == (rcdata_p) 0) {
		(void) fprintf(stderr, "greptool: callback passed nil data\n");

		return ;
	}

	/* Get the command string from the call data */

	XmStringInitContext(&context, call_data->value);
	XmStringGetNextSegment(context, &text, &charset, &direction, &separator);
	XmStringFreeContext(context);

	/* Create two pipes to communicate with grep - one for
	   standard output and one for standard error */
	if (pipe(pipestdout) < 0 || pipe(pipestderr) < 0) {
		(void) fprintf(stderr, "greptool: cannot create pipe\n");
		exit (-1);
	}

	switch (pid = fork()) {
	case 0:
		/* In child branch of fork - close reading end of pipes
		   and dup the writing ends onto stdout and stderr */
		(void) close(pipestdout[0]);
		(void) close(pipestderr[0]);
		(void) dup2(pipestdout[1], 1);
		(void) dup2(pipestderr[1], 2);
		/* Run the command */
		(void) execl ( "/bin/sh", "/bin/sh", "-c", text, 0);
		(void) fprintf(stderr, "greptool: exec failed\n");
		exit (-1);

	case -1:
		/* Fork didn't work... */
		(void) fprintf(stderr, "greptool: cannot fork\n");
		exit (-1);

	default:
		/* In parent branch of fork - close writing ends of pipes,
		   and open stdout pipe for reading */
		(void) close(pipestdout[1]);
		(void) close(pipestderr[1]);
		grepout = fdopen(pipestdout[0], "r");

		/* Blank out hits text widget, then read output of grep
		   and display in text widget */
		outpos = 0;
		XmTextSetString(*(rcp->hitstring_widget), "");

		for (;;) {
			if (fgets(buffer, 512, grepout) == (char *)0) break;
			XmTextReplace(*(rcp->hitstring_widget), outpos, outpos, buffer);
			outpos = outpos + strlen(buffer);
		}

		(void) fclose(grepout);

		/* Get exit status of grep, display errors if non-zero */
		while (wait (&waitstat) != pid);
		if (waitstat && 0xFF00) {

			/* If no error dialog, create it */
			if (*(rcp->errorshell_widget) == (Widget) 0)
				create_errorshell(*(rcp->mainshell_widget));

			/* Blank out errors text widget, then read errors
			   from grep and display in text widget */
			XmTextSetString(*(rcp->errortext_widget), "");
			greperr = fdopen(pipestderr[0], "r");
			errpos = 0;
			while (1) {
				if (fgets(buffer, 512, greperr) == (char *)0) break;
				XmTextReplace(*(rcp->errortext_widget), errpos, errpos, buffer);
				errpos = errpos + strlen(buffer);
			}
			(void) fclose(greperr);

			/* Manage first child of error dialog shell (ie pop it up) */
			XtManageChild(*(rcp->errorform_widget));
		}
	}
}
