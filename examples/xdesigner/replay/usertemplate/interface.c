#include <stdio.h>
#include <X11/Xos.h>
#include <X11/Xlib.h>

#include <X11/Intrinsic.h>


void
exampleHalloWorld( shell, message)
	Widget shell;
	char * message;
{
	if (!message)
		message = "no message";
	(void) fprintf ( stderr, "Widget %s says '%s'\n", XtName(shell), message);
}


/* this example extends the engine with a simple dowhile loop
** using two hooks (defined in xdsSetup.h)
**
** It will only take a single line, but you could adapt it
** to read a sequence from an external file
*/

void
exampleDoWhile( shell, cmd)
	Widget shell;
	char * cmd;
{
	extern Boolean xdsUserExpression();
	extern Boolean xdsUserRequestCommand();
	/* expecting command EXPR command */
	char * p;
	char   c;
	char   command[255];

	for ( p = cmd; p && *p && !isspace(*p); p++);

	if (!p && !*p)
		return;
	c = *p;
	*p++ = '\0';

	while (isspace(*p))
		p++;

	if (!xdsUserExpression( shell, cmd)) {
		(void) fprintf ( stderr, "Expression %s failed in %s\n", cmd, XtName(shell));
		*p = c;
		return;
	}

	(void) sprintf( command, "%s\nuser dowhile %s %s\n", p, cmd, p);

	(void) fprintf ( stderr, "Executing %s\n", command);

	if (!xdsUserRequestCommand( command))
		(void) fprintf ( stderr, "Bad command (%s)\n", p);

	*p = c;

	return;
}
