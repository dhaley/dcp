/*
** Generated Code
*/
/*
**LIBS: -lXm -lXt -lX11
*/

#include <X11/Xatom.h>
#include <X11/Intrinsic.h>
#include <X11/Shell.h>

#include <Xm/Xm.h>
#include <Xm/Command.h>
#include <Xm/DialogS.h>
#include <Xm/Form.h>
#include <Xm/List.h>
#include <Xm/PushB.h>
#include <Xm/RowColumn.h>
#include <Xm/ScrollBar.h>
#include <Xm/SelectioB.h>
#include <Xm/Text.h>
#include <Xm/CascadeBG.h>
#include <Xm/LabelG.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "xdclass.h"

#include "Value.h"
#include "Nodes.h"
#include "CalcDemo.h"

extern char *textInput;
extern char *textInputPtr;
extern char * XmTextGetString() ;
extern topshell_p topshell;

XtAppContext app_context;
Display *display;       /*  Display             */

void insert_callback (Widget button, 
		      XtPointer command, 
		      XtPointer xt_call_data)
{
  XmAnyCallbackStruct *call_data = (XmAnyCallbackStruct *) xt_call_data;
  command_c *command_ptr = (command_c *)command;

  Arg al[64];                    /* Arg List */
  register int ac = 0;           /* Arg Count */
  XmString label_string;
  char *text;

  XtSetArg(al[ac],XmNlabelString,&label_string);ac++;
  XtGetValues(button,al,ac);
  XmStringGetLtoR(label_string,
		  (XmStringCharSet)XmFONTLIST_DEFAULT_TAG,
		  &text);
  XmTextInsert(command_ptr->textentry,
	       XmTextGetLastPosition(command_ptr->textentry),
	       text);
  XtFree(text);
  XmProcessTraversal(command_ptr->textentry,XmTRAVERSE_CURRENT);
}

void clear_callback (Widget button, 
		     XtPointer command, 
		     XtPointer xt_call_data)
{
  XmAnyCallbackStruct *call_data = (XmAnyCallbackStruct *) xt_call_data;
  command_c *command_ptr = (command_c *)command;

  Arg al[64];                    /* Arg List */
  register int ac = 0;           /* Arg Count */
  XmString label_string;
  char *text;

  text = NULL;
  XmTextSetString(command_ptr->textentry,
		  text);
  XmProcessTraversal(command_ptr->textentry,XmTRAVERSE_CURRENT);
}

static char *buffer = NULL;

void eval_callback (Widget button, 
		     XtPointer command, 
		     XtPointer xt_call_data)
{
  XmAnyCallbackStruct *call_data = (XmAnyCallbackStruct *) xt_call_data;
  command_c *command_ptr = (command_c *)command;
  Node *root;
  Value value;
  Arg al[64];                    /* Arg List */
  register int ac = 0;           /* Arg Count */
  XmString label_string;

  lexeme[0] = 0;
  textInput = XmTextGetString(command_ptr->textentry);
  textInputPtr = textInput;
  token = scan();

  if (!buffer)
    buffer = XtMalloc(64);
  *buffer = '\0';

  if ( (root = Exp()) && (token == EOLN))
    {
      if (strlen(lexeme) > 0)
	{
	  value = root->eval();
	  if (!value.IsError())
	    {
	      print_buff(buffer,value);
	      XmTextSetString(command_ptr->textresult,
			      buffer);
	    }
	  else
	    {
	      XBell(display, 100);
	    }
	  delete root;
	  lexeme[0] = 0;
	}
    }
  else
    XBell(display, 100);
  
  XmProcessTraversal(command_ptr->textentry,XmTRAVERSE_CURRENT);
}

int main (int argc, char **argv)
{
	XtSetLanguageProc ( (XtAppContext) NULL, 
			   (XtLanguageProc) NULL, (XtPointer) NULL );
	XtToolkitInitialize ();
	app_context = XtCreateApplicationContext ();
	display = XtOpenDisplay (app_context, NULL, argv[0], "XApplication",
	                         NULL, 0, &argc, argv);
	if (!display)
	{
	    printf("%s: can't open display, exiting...\n", argv[0]);
	    exit (-1);
	}
	topshell = new topshell_c;
	topshell->create ( display, argv[0], argc, argv );
	/*
	 * Add e and pi to the symtab
         */
	{
	  Value v;
	  v = (Value) 2.718281828;
	  AddSymtabEntry("e",v);
	  v = (Value) 3.141592653;
	  AddSymtabEntry("pi",v);
	}
	buffer = XtMalloc(64*sizeof(char));
	*buffer = '\0';

	XtRealizeWidget (topshell->xd_rootwidget());
	XtAppMainLoop (app_context);
	exit (0);
}

