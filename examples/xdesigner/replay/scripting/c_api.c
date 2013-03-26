/*@ cc -o @R @F
*/
#include <stdio.h>

/* This is an example set of routines that can be used
   to generate replay scripts, using C as your scripting
   language. Youj can either pipe the output of your
   program directly into the replay program, or save it
   as a file, and use the '-f' flag


   The example is not complete.
   It is intended to show how easy it is to produce replay
   scripts in any language you are familiar with.

   The example should indent properly, both for if conditions
   and 'in' statements.


   $ cc -o c_api c_api.c
   $ c_api

*/

#ifndef   _NO_PROTO
int   In( char * shell);
int    Push( char * widget);
int    PushUser( char * widget, char * name,char * attribute);
int    Select( char * cascade,char * sel);
int    SelectPullright( char * cascade, char * pullright, char * sel);
int    If( char * condition);
int    Elif( char * condition);
int    Else(void);
int    Endif(void);
char * ApplicationShell(void);
#else  /* _NO_PROTO */
int    In() ;
int    Push() ;
int    PushUser() ;
int    Select() ;
int    SelectPullright() ;
int    If() ;
int    Elif() ;
int    Else() ;
int    Endif() ;
char * ApplicationShell() ;
#endif /* _NO_PROTO */

#ifndef   _NO_PROTO
main(int ac, char **av)
#else  /* _NO_PROTO */
main(ac, av)
	int ac ;
	char **av ;
#endif /* _NO_PROTO */
{
	In(ApplicationShell());
		Push( "mywidget");
		PushUser( "myuserwidget", "yellowone", "center");
		Select( "file", "open");
		SelectPullright( "file", "bingo", "house");

	If( "mywidget->value:'hallo world'");
		Push( "mywidget");
	Elif( "mywidget->value:'bye world'");
		Push( "mywidget");
	Else();
		Push( "mywidget");
	Endif();
}

#ifndef   _NO_PROTO
char * xdsTabs(void);
#else  /* _NO_PROTO */
char * xdsTabs();
#endif /* _NO_PROTO */

#ifndef   _NO_PROTO
char * ApplicationShell(void)
#else  /* _NO_PROTO */
char * ApplicationShell()
#endif /* _NO_PROTO */
{
	return "ApplicationShell";
}

#ifndef   _NO_PROTO
int In( char * shell)
#else  /* _NO_PROTO */
int In( shell)
	char *shell ;
#endif /* _NO_PROTO */
{
	xdsPopShell();

	printf ( "%sin %s\n", xdsTabs(), shell);

	xdsPushShell();
}

#ifndef   _NO_PROTO
int Push( char * widget)
#else  /* _NO_PROTO */
int Push( widget)
	char *widget ;
#endif /* _NO_PROTO */
{
	if (!widget)
		xdsBadCommand();
	printf ( "%spush %s\n", xdsTabs(), widget);
}

#ifndef   _NO_PROTO
int PushUser( char * widget, char * name,char * attribute)
#else  /* _NO_PROTO */
int PushUser(  widget, name, attribute )
	char * widget ;
	char * name ;
	char * attribute ;
#endif /* _NO_PROTO */
{
	if (!widget || !name || !attribute)
		xdsBadCommand();
	printf ( "%spush %s(%s,%s)\n", xdsTabs(), widget, name, attribute);
}

#ifndef   _NO_PROTO
int Select( char * cascade,char * sel)
#else  /* _NO_PROTO */
int Select( cascade, sel)
	char * cascade ;
	char * sel ;
#endif /* _NO_PROTO */
{
	char * tabs = xdsTabs();
	if (!cascade || !sel)
		xdsBadCommand();
	printf ( "%scascade %s\n%s\tselect %s\n", tabs, cascade, tabs, sel);
}

#ifndef   _NO_PROTO
int SelectPullright( char * cascade, char * pullright, char * sel)
#else  /* _NO_PROTO */
int SelectPullright( cascade, pullright, sel)
	char * cascade ;
	char * pullright ;
	char * sel ;
#endif /* _NO_PROTO */
{
	char * tabs = xdsTabs();
	if (!cascade || !pullright || !sel)
		xdsBadCommand();
	printf ( "%scascade %s\n%s\tpullright %s\n%s\t\tselect %s\n", tabs, cascade, tabs, pullright, tabs, sel);
}

#ifndef   _NO_PROTO
int If( char * condition)
#else  /* _NO_PROTO */
int If( condition)
	char * condition ;
#endif /* _NO_PROTO */
{
	if (!condition)
		xdsBadCommand();
	(void) printf ( "%sif %s\n", xdsTabs(), condition);

	xdsPush();
}

#ifndef   _NO_PROTO
int Elif( char * condition)
#else  /* _NO_PROTO */
int Elif( condition)
	char * condition ;
#endif /* _NO_PROTO */
{
	if (!condition)
		xdsBadCommand();
	xdsPop();
	(void) printf ( "%selif %s\n", xdsTabs(), condition);
	xdsPush();
}

#ifndef   _NO_PROTO
int Else(void)
#else  /* _NO_PROTO */
int Else()
#endif /* _NO_PROTO */
{
	xdsPop();
	(void) printf ( "%selse\n", xdsTabs());
	xdsPush();
}

#ifndef   _NO_PROTO
int Endif(void)
#else  /* _NO_PROTO */
int Endif()
#endif /* _NO_PROTO */
{
	xdsPop();
	(void) printf ( "%sendif\n", xdsTabs());
}

typedef struct indent_s {
	int     level;
	int     in_shell;
	struct  indent_s * next;
} Indent_t;

Indent_t * xdsIndent = (Indent_t*)0;

#ifndef   _NO_PROTO
int xdsPush(void)
#else  /* _NO_PROTO */
int xdsPush()
#endif /* _NO_PROTO */
{
	Indent_t * i = (Indent_t*) malloc ((unsigned) sizeof(Indent_t));

	i->level    = (!xdsIndent) ? 1 : xdsIndent->level + 1;
	i->in_shell = 0;
	i->next     = xdsIndent;

	xdsIndent   = i;
}

#ifndef   _NO_PROTO
int xdsPop(void)
#else  /* _NO_PROTO */
int xdsPop()
#endif /* _NO_PROTO */
{
	Indent_t * i = xdsIndent;

	xdsIndent = xdsIndent->next;

	if (i) {
		free ((void*) i);
	}
}

#ifndef   _NO_PROTO
char * xdsTabs(void)
#else  /* _NO_PROTO */
char * xdsTabs()
#endif /* _NO_PROTO */
{
	static char tabs[100];
	char * p;
	Indent_t * i;

	if (!xdsIndent) {
		xdsPush();
	}

	for (p = tabs, i = xdsIndent; i; i = i->next) {
		*p++ = '\t';
		if (i->in_shell) {
			*p++ = '\t';
		}
	}

	*p = '\0';

	return tabs;
}

#ifndef   _NO_PROTO
int xdsPushShell(void)
#else  /* _NO_PROTO */
int xdsPushShell()
#endif /* _NO_PROTO */
{
	xdsIndent->in_shell = 1;
}

#ifndef   _NO_PROTO
int xdsPopShell(void)
#else  /* _NO_PROTO */
int xdsPopShell()
#endif /* _NO_PROTO */
{
	if (!xdsIndent)
		xdsPush();

	xdsIndent->in_shell = 0;
}

#ifndef   _NO_PROTO
int xdsBadCommand(void)
#else  /* _NO_PROTO */
int xdsBadCommand()
#endif /* _NO_PROTO */
{
	(void) fprintf ( stderr, "Bad command\n");
	exit(-1);
}

/*---------------------------------------------*/
