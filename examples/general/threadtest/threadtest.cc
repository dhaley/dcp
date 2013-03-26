/* Copyright 2001,2002 Sun Microsystems, Inc. All Rights Reserved 
 *
 * threadtest.c - This module displays a GUI, which allows th
 * user to invoke different numbers of threads that do some simple
 * work. The GUI displays buttons labeled 1, 2, and 3. Clicking on 
 * the button labeled "1" invokes a single thread. Clicking on "2"
 * invokes two threads, and so forth. The threads update labels
 * that are next to the buttons, so the user knows whether or not
 * they are running. This program can be used to explore the
 * debugger GUI support of multi-threaded programs.
 * 
 * Syntax:
 *	threadtest
 *
 */

#include <Xm/Xm.h>
#include <Xm/PushB.h>
#include <Xm/RowColumn.h>
#include <Xm/Label.h>

#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <thread.h>

#include <stdio.h>
#define NO_OF_BUTTONS 3

/* Function prototypes */
void ThreadWork(Widget w, XtPointer clientData, XtPointer callData);
extern "C" void *myThread(void *);

/* structures */
typedef struct cb_s 
{
   Widget  *currentLabelP;
   int     buttonNo;
} ThreadCB;

XtAppContext context;

main(int argc, char **argv)
{
Widget 	top, parent, button[5], label[5];
Arg 	wargs[10];
int	i;
char 	bLabel[5];

ThreadCB tcb[3];

/* set up our main window */
top = XtAppInitialize(&context, "ThreadWin", NULL, 0, &argc, argv,
			NULL, NULL, 0);

/* set some arguments for our Row/Column Widget */
XtSetArg(wargs[0], XmNorientation, XmHORIZONTAL);
XtSetArg(wargs[1], XmNentryAlignment, XmALIGNMENT_CENTER);
XtSetArg(wargs[2], XmNisAligned, True);
XtSetArg(wargs[3], XmNnumColumns, 3);
XtSetArg(wargs[4], XmNpacking, XmPACK_COLUMN);

/* create the Row/Column Widget */
parent = XtCreateManagedWidget("parent", xmRowColumnWidgetClass, top, 
				wargs, 5);

/* create the button widgets and corresponding labels. The
 * button labels show how many threads will be started 
 */
for (i=0;i<NO_OF_BUTTONS;i++) 
{
   sprintf(bLabel, "%d", i+1);
   XtSetArg(wargs[0], XmNlabelString, XmStringCreate(bLabel,
	    XmSTRING_DEFAULT_CHARSET));
   button[i] = XmCreatePushButton(parent, (char *)"button", wargs, 1);
   label[i] = XtCreateManagedWidget((char *)"--------", xmLabelWidgetClass,
   		                    parent, NULL, 0);

   /* fill in ThreadCB */
   tcb[i].buttonNo = i+1;
   tcb[i].currentLabelP = &label[i];

   XtAddCallback(button[i], XmNactivateCallback, ThreadWork, &tcb[i]);

}

thr_setconcurrency(sysconf(_SC_NPROCESSORS_ONLN)+1);

XtManageChildren(button, NO_OF_BUTTONS);
XtRealizeWidget(top);
XtAppMainLoop(context);
return(0);
}


/* ThreadWork() - Button Callback */ 
void ThreadWork(Widget w, XtPointer clientData, XtPointer callData)
{
int i;
ThreadCB *tcbP = (ThreadCB *) clientData;

/* Loop through the button number (1, 2, or 3). Create that
 * many threads 
 */
/* for(i=0; i<tcbP->buttonNo; i++) */
for(i=0; i<tcbP->buttonNo; i++) 
{
   thr_create(NULL, 0, myThread, (void *)tcbP->currentLabelP,
   	      THR_DETACHED, NULL);
}
return;
}


/* myThread() -- called from ThreadWork() routine.  This is the
 * routine that changes the button and simulates some work
 */

void *myThread(void *arg)
{
Widget *wP = (Widget *) arg;
Pixel fg, bg;
XEvent event;
Arg warg[2];
Display *display;
Window win;
int x,y;
char buf[8];

sprintf(buf, "Running");
XtVaSetValues(*wP,
 XtVaTypedArg, XmNlabelString, XmRString, buf, strlen(buf), NULL);

/* force a pointer movement Xevent so label changes will be visible */
display = XtDisplay(*wP);
win = XtWindow(*wP);
event.xmotion.display = display;
event.xmotion.window = win;
XSendEvent(display, win, TRUE, PointerMotionMask, &event);
XFlush(display);

/* do some processing */
for (x=0;x<5000000;x++)
	y = x;

sprintf(buf, "--------");
XtVaSetValues(*wP,
XtVaTypedArg, XmNlabelString, XmRString, buf, strlen(buf), NULL);

/* force Xevent again */
XSendEvent(display, win, TRUE, PointerMotionMask, &event);
XFlush(display);

return((void *)0);
}
