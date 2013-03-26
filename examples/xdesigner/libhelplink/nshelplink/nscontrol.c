/* X-Designer
** (c) 1992, 1993, 1994, 1995
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
 
#if !defined(lint) && !defined(NOSCCS)
static char *sccsid = "%Z%%Q%%M%     %I%" ; /* %E% */
#endif /* lint && NOSCCS */
 
/* 
** File:       %M%
** Purpose:    Simple control over the Netscape WWW browser
** Created by: Giles P.J. Thomas
** Date:       1st February 1996
*/

/*
** The following enables declaration of strtok_r via strings.h on Solaris.
*/
#ifndef linux
#define   __EXTENSIONS__ 1
#endif /* linux */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#ifndef   Bool
#define   Bool   int
#endif /* Bool */

#ifdef    VMS
#include <processes.h>

#define   BACKGROUND_ARGUMENT           ""
#define   OUTPUT_REDIRECT_ARGUMENT      ""
#endif /* VMS */

#ifndef   MAX_PATH_LENGTH
#define   MAX_PATH_LENGTH               4096
#endif /* MAX_PATH_LENGTH */

#ifndef   MAX_NETSCAPE_COMMAND
#define   MAX_NETSCAPE_COMMAND          512
#endif /* MAX_NETSCAPE_COMMAND */

#ifndef   MAX_NETSCAPE_ARGUMENT
#define   MAX_NETSCAPE_ARGUMENT         512
#endif /* MAX_NETSCAPE_ARGUMENT */

/*
** BROWSER_PROGS should be set to a colon separated list of possible web 
** browser command names (e.g. "firefox:mozilla:netscape"). 
*/ 
#ifndef   BROWSER_COMMANDS
#define   BROWSER_COMMANDS              BROWSER_PROGS
#endif /* BROWSER_COMMANDS */

#ifndef   NETSCAPE_REMOTE_ARGUMENT
#define   NETSCAPE_REMOTE_ARGUMENT      "-remote"
#endif /* NETSCAPE_REMOTE_ARGUMENT */

#ifndef   NETSCAPE_NEW_WINDOW_FORMAT
#define   NETSCAPE_NEW_WINDOW_FORMAT    "'openURL(%s,new-window)'"
#endif /* NETSCAPE_NEW_WINDOW_FORMAT */

#ifndef   NETSCAPE_OLD_WINDOW_FORMAT
#define   NETSCAPE_OLD_WINDOW_FORMAT    "'openURL(%s)'"
#endif /* NETSCAPE_OLD_WINDOW_FORMAT */

#ifndef   BACKGROUND_ARGUMENT
#define   BACKGROUND_ARGUMENT           "&"
#endif /* BACKGROUND_ARGUMENT */

#ifndef   OUTPUT_REDIRECT_ARGUMENT
#define   OUTPUT_REDIRECT_ARGUMENT      "> /dev/null 2>&1"
#endif /* OUTPUT_REDIRECT_ARGUMENT */

/*
** This shouldn't get used if everything is configured properly.
*/
#ifndef   DEFAULT_BROWSER
#define   DEFAULT_BROWSER               "netscape"
#endif /* DEFAULT_BROWSER */

#ifndef   X_OK
#define   X_OK                          1
#endif /* X_OK */

#ifndef   _NO_PROTO
static char *SearchPath(void)
#else  /* _NO_PROTO */
static char *SearchPath()
#endif /* _NO_PROTO */
{
	char *browser_cmd = (char *) 0 ;
	char  buffer[MAX_NETSCAPE_COMMAND + 1] ;
	char  pcopy[MAX_PATH_LENGTH + 1] ;
        static char  cmdscopy[MAX_NETSCAPE_COMMAND + 1] ;
        static char  default_browser[MAX_NETSCAPE_COMMAND + 1] ;
	char *path ;
	char *token ;
        char *cmd_name ;
        char *last_cmd ;
        char *last_tok ;
        
        (void) strcpy(cmdscopy, BROWSER_COMMANDS) ;
        cmd_name = strtok_r(cmdscopy, ":", &last_cmd) ;
        
        /* Use first command name as default. */
        strcpy(default_browser, cmd_name) ;
        
        if ((path = getenv("PATH")) != (char *) 0) {
        
                while ((cmd_name != (char *) 0) && (browser_cmd == (char *) 0)) {

		        (void) strcpy(pcopy, path) ;

		        token = strtok_r(pcopy, ":", &last_tok) ;

		        while (token != (char *) 0) {
			        (void) sprintf(buffer, "%s/%s", token, cmd_name) ;

			        if (access(buffer, X_OK) == 0) {
				        browser_cmd = cmd_name ;
				        break ;
			        }

			        token = strtok_r(NULL, ":", &last_tok) ;
		        }
                        
                        cmd_name = strtok_r(NULL, ":", &last_cmd) ;
	        }
        }
        
        if (browser_cmd == (char *) 0) {
            browser_cmd = default_browser ;
        }

	return browser_cmd ;
}

#ifndef   _NO_PROTO
static char *BrowserName(void)
#else  /* _NO_PROTO */
static char *BrowserName()
#endif /* _NO_PROTO */
{
	static char *browser = (char *) 0 ;

	if ((browser = getenv("XDHELP_BROWSER")) != (char *) 0) {
		return browser ;
	}

	if ((browser = SearchPath()) == (char *) 0) {
		browser = (char *) DEFAULT_BROWSER ;
	}

	return browser ;
}

#ifndef   _NO_PROTO
static int netscape(char * browser_prog, char *url, Bool ownWindow, Bool connect)
#else  /* _NO_PROTO */
static int netscape(browser_prog, url, ownWindow, connect)
        char *browser_prog ;
	char *url ;
	Bool  ownWindow ;
	Bool  connect ;
#endif /* _NO_PROTO */
{
	char  command[MAX_NETSCAPE_COMMAND + 1] ;
	char  url_argument[MAX_NETSCAPE_ARGUMENT + 1] ;

#ifdef    VMS
	if (connect) {
		/* Mimic Background Task via fork/exec with no wait */

		int pid = vfork() ;

		if (pid == 0) {
			/* Child Process */

			execl(browser_prog, 
			      browser_prog,
			      url,
			      (char *) 0) ;

			exit(1) ;
		}

		return ((pid > 0) ? 0 : 1) ;
	}
#else  /* VMS */
	if (connect) {
		(void) sprintf(command, 
			       "%s %s %s",
				browser_prog,
				url,
				BACKGROUND_ARGUMENT) ;
	}
#endif /* VMS */
	else if (ownWindow) {
		(void) sprintf(url_argument, 
			       NETSCAPE_NEW_WINDOW_FORMAT,
			       url) ;

		(void) sprintf(command,
			       "%s %s %s %s",
			       browser_prog,
			       NETSCAPE_REMOTE_ARGUMENT,
			       url_argument,
			       OUTPUT_REDIRECT_ARGUMENT) ;

	}
	else {
                (void) sprintf(url_argument, 
                               NETSCAPE_OLD_WINDOW_FORMAT,
                               url) ;
 
                (void) sprintf(command,
                               "%s %s %s %s",
                               browser_prog,
                               NETSCAPE_REMOTE_ARGUMENT,
                               url_argument,
			       OUTPUT_REDIRECT_ARGUMENT) ;
	}

	return system(command) ;
}

/*
** A function to send Netscape to a particular URL.  If no
** Netscape is running, start one.  If /ownWindow/ then
** open a new browser window to show the URL.  If a new Netscape
** had to be started, return 0 - otherwise return 1.
*/

#ifndef   _NO_PROTO
int SendNetscapeTo(char *url, Bool ownWindow)
#else  /* _NO_PROTO */
int SendNetscapeTo(url, ownWindow)
    char *url ;
    Bool  ownWindow ;
#endif /* _NO_PROTO */
{
 	char *browser_prog = BrowserName() ;
        
       /* Execute the command */
        if (netscape(browser_prog, url, ownWindow, 0) != 0) {
	        if (netscape(browser_prog, url, ownWindow, 1) != 0) {
	                (void) fprintf( stderr,  "Could not start %s to send it to %s.\n", browser_prog, url) ;
	                (void) fflush(stderr) ;
                        return 0 ;
                }
        }

        return 1 ;
}
