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
#include <Xm/Label.h>
#include <Xm/List.h>
#include <Xm/PushB.h>
#include <Xm/RowColumn.h>
#include <Xm/ScrollBar.h>
#include <Xm/SelectioB.h>
#include <Xm/Text.h>
#include <Xm/TextF.h>
#include <Xm/CascadeBG.h>
#include <Xm/LabelG.h>

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "xdclass.h"



#include "CalcDemo.h"

extern void eval_callback (Widget, XtPointer, XtPointer );
extern void insert_callback (Widget, XtPointer, XtPointer );
extern void clear_callback (Widget, XtPointer, XtPointer );
topshell_p topshell = (topshell_p) NULL;



void command_c::create (Widget parent)
{
	Display *display = XtDisplay ( parent );
	Widget children[4];      /* Children to manage */
	Arg al[64];                    /* Arg List */
	register int ac = 0;           /* Arg Count */
	char from_s [256];             /* For resource conversion */
	XrmValue from_value, to_value; /* ditto */
	XtPointer tmp_value;             /* ditto */
	int fg, bg;                    /* colour values for pixmaps */ 
	XmString *list_items;          /* For list items */
	int list_item;                 /* Index for list_items */
	Atom *atom_list;               /* For Drop Site targets */
	XmString xmstrings[16];    /* temporary storage for XmStrings */

	command = XmCreateCommand ( parent, "command", al, ac );
	_xd_rootwidget = command;
	list = XmCommandGetChild ( command, XmDIALOG_LIST );
	sellabel = XmCommandGetChild ( command, XmDIALOG_PROMPT_LABEL );
	textentry = XmCommandGetChild ( command, XmDIALOG_COMMAND_TEXT );
	slist = XtParent ( list );

	XtSetArg(al[ac], XmNhorizontalScrollBar, &hbar ); ac++;
	XtSetArg(al[ac], XmNverticalScrollBar, &vbar ); ac++;
	XtGetValues(slist, al, ac );
	ac = 0;
	xmstrings[0] = XmStringCreateLtoR("Enter Expression", (XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstrings[0]); ac++;
	XtSetArg(al[ac], XmNalignment, XmALIGNMENT_BEGINNING); ac++;
	XtSetValues ( sellabel,al, ac );
	ac = 0;
	XmStringFree ( xmstrings [ 0 ] );
	result_form = XmCreateForm ( command, "result_form", al, ac );
	textresult = XmCreateTextField ( result_form, "Text", al, ac );
	xmstrings[0] = XmStringCreateLtoR("Result:", (XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstrings[0]); ac++;
	XtSetArg(al[ac], XmNalignment, XmALIGNMENT_BEGINNING); ac++;
	result_label = XmCreateLabel ( result_form, "label", al, ac );
	ac = 0;
	XmStringFree ( xmstrings [ 0 ] );
	XtAddCallback (textentry, XmNactivateCallback, eval_callback,topshell->command);

	XtSetArg(al[ac], XmNtopAttachment, XmATTACH_WIDGET); ac++;
	XtSetArg(al[ac], XmNtopWidget, result_label); ac++;
	XtSetArg(al[ac], XmNbottomAttachment, XmATTACH_FORM); ac++;
	XtSetArg(al[ac], XmNleftAttachment, XmATTACH_FORM); ac++;
	XtSetArg(al[ac], XmNrightAttachment, XmATTACH_FORM); ac++;
	XtSetValues ( textresult,al, ac );
	ac = 0;

	XtSetArg(al[ac], XmNtopAttachment, XmATTACH_FORM); ac++;
	XtSetArg(al[ac], XmNbottomAttachment, XmATTACH_NONE); ac++;
	XtSetArg(al[ac], XmNleftAttachment, XmATTACH_FORM); ac++;
	XtSetArg(al[ac], XmNrightAttachment, XmATTACH_FORM); ac++;
	XtSetValues ( result_label,al, ac );
	ac = 0;
	children[ac++] = textresult;
	children[ac++] = result_label;
	XtManageChildren(children, ac);
	ac = 0;
	children[ac++] = result_form;
	XtManageChildren(children, ac);
	ac = 0;
}

void rcform_c::create (Widget parent)
{
	Display *display = XtDisplay ( parent );
	Widget children[6];      /* Children to manage */
	Arg al[64];                    /* Arg List */
	register int ac = 0;           /* Arg Count */
	char from_s [256];             /* For resource conversion */
	XrmValue from_value, to_value; /* ditto */
	XtPointer tmp_value;             /* ditto */
	int fg, bg;                    /* colour values for pixmaps */ 
	XmString *list_items;          /* For list items */
	int list_item;                 /* Index for list_items */
	Atom *atom_list;               /* For Drop Site targets */
	XmString xmstrings[16];    /* temporary storage for XmStrings */

	rcform = XmCreateForm ( parent, "rcform", al, ac );
	_xd_rootwidget = rcform;
	buttonform = XmCreateForm ( rcform, "buttonform", al, ac );
	col1form = XmCreateForm ( buttonform, "col1form", al, ac );
	xmstrings[0] = XmStringCreateLtoR("=", (XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstrings[0]); ac++;
	button_eq = XmCreatePushButton ( col1form, "calc_button", al, ac );
	ac = 0;
	XmStringFree ( xmstrings [ 0 ] );
	xmstrings[0] = XmStringCreateLtoR("+", (XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstrings[0]); ac++;
	button_plus = XmCreatePushButton ( col1form, "calc_button", al, ac );
	ac = 0;
	XmStringFree ( xmstrings [ 0 ] );
	xmstrings[0] = XmStringCreateLtoR("7", (XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstrings[0]); ac++;
	button7 = XmCreatePushButton ( col1form, "calc_button_num", al, ac );
	ac = 0;
	XmStringFree ( xmstrings [ 0 ] );
	xmstrings[0] = XmStringCreateLtoR("4", (XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstrings[0]); ac++;
	button4 = XmCreatePushButton ( col1form, "calc_button_num", al, ac );
	ac = 0;
	XmStringFree ( xmstrings [ 0 ] );
	xmstrings[0] = XmStringCreateLtoR("1", (XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstrings[0]); ac++;
	button1 = XmCreatePushButton ( col1form, "calc_button_num", al, ac );
	ac = 0;
	XmStringFree ( xmstrings [ 0 ] );
	xmstrings[0] = XmStringCreateLtoR("0", (XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstrings[0]); ac++;
	button0 = XmCreatePushButton ( col1form, "calc_button_num", al, ac );
	ac = 0;
	XmStringFree ( xmstrings [ 0 ] );
	col2form = XmCreateForm ( buttonform, "col2form", al, ac );
	xmstrings[0] = XmStringCreateLtoR("(", (XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstrings[0]); ac++;
	button_left = XmCreatePushButton ( col2form, "calc_button", al, ac );
	ac = 0;
	XmStringFree ( xmstrings [ 0 ] );
	xmstrings[0] = XmStringCreateLtoR("-", (XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstrings[0]); ac++;
	button_minus = XmCreatePushButton ( col2form, "calc_button", al, ac );
	ac = 0;
	XmStringFree ( xmstrings [ 0 ] );
	xmstrings[0] = XmStringCreateLtoR("8", (XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstrings[0]); ac++;
	button8 = XmCreatePushButton ( col2form, "calc_button_num", al, ac );
	ac = 0;
	XmStringFree ( xmstrings [ 0 ] );
	xmstrings[0] = XmStringCreateLtoR("5", (XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstrings[0]); ac++;
	button5 = XmCreatePushButton ( col2form, "calc_button_num", al, ac );
	ac = 0;
	XmStringFree ( xmstrings [ 0 ] );
	xmstrings[0] = XmStringCreateLtoR("2", (XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstrings[0]); ac++;
	button2 = XmCreatePushButton ( col2form, "calc_button_num", al, ac );
	ac = 0;
	XmStringFree ( xmstrings [ 0 ] );
	xmstrings[0] = XmStringCreateLtoR(".", (XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstrings[0]); ac++;
	button_decimal = XmCreatePushButton ( col2form, "calc_button_num", al, ac );
	ac = 0;
	XmStringFree ( xmstrings [ 0 ] );
	col3form = XmCreateForm ( buttonform, "col3form", al, ac );
	xmstrings[0] = XmStringCreateLtoR(")", (XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstrings[0]); ac++;
	button_right = XmCreatePushButton ( col3form, "calc_button", al, ac );
	ac = 0;
	XmStringFree ( xmstrings [ 0 ] );
	xmstrings[0] = XmStringCreateLtoR("*", (XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstrings[0]); ac++;
	button_times = XmCreatePushButton ( col3form, "calc_button", al, ac );
	ac = 0;
	XmStringFree ( xmstrings [ 0 ] );
	xmstrings[0] = XmStringCreateLtoR("9", (XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstrings[0]); ac++;
	button9 = XmCreatePushButton ( col3form, "calc_button_num", al, ac );
	ac = 0;
	XmStringFree ( xmstrings [ 0 ] );
	xmstrings[0] = XmStringCreateLtoR("6", (XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstrings[0]); ac++;
	button6 = XmCreatePushButton ( col3form, "calc_button_num", al, ac );
	ac = 0;
	XmStringFree ( xmstrings [ 0 ] );
	xmstrings[0] = XmStringCreateLtoR("3", (XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstrings[0]); ac++;
	button3 = XmCreatePushButton ( col3form, "calc_button_num", al, ac );
	ac = 0;
	XmStringFree ( xmstrings [ 0 ] );
	xmstrings[0] = XmStringCreateLtoR("log10", (XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstrings[0]); ac++;
	button_log10 = XmCreatePushButton ( col3form, "calc_button", al, ac );
	ac = 0;
	XmStringFree ( xmstrings [ 0 ] );
	col4form = XmCreateForm ( buttonform, "col4form", al, ac );
	xmstrings[0] = XmStringCreateLtoR("^", (XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstrings[0]); ac++;
	button_pow = XmCreatePushButton ( col4form, "calc_button", al, ac );
	ac = 0;
	XmStringFree ( xmstrings [ 0 ] );
	xmstrings[0] = XmStringCreateLtoR("/", (XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstrings[0]); ac++;
	button_div = XmCreatePushButton ( col4form, "calc_button", al, ac );
	ac = 0;
	XmStringFree ( xmstrings [ 0 ] );
	xmstrings[0] = XmStringCreateLtoR("loge", (XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstrings[0]); ac++;
	button_loge = XmCreatePushButton ( col4form, "calc_button", al, ac );
	ac = 0;
	XmStringFree ( xmstrings [ 0 ] );
	xmstrings[0] = XmStringCreateLtoR("sin", (XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstrings[0]); ac++;
	button_sin = XmCreatePushButton ( col4form, "calc_button", al, ac );
	ac = 0;
	XmStringFree ( xmstrings [ 0 ] );
	xmstrings[0] = XmStringCreateLtoR("cos", (XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstrings[0]); ac++;
	button_cos = XmCreatePushButton ( col4form, "calc_button", al, ac );
	ac = 0;
	XmStringFree ( xmstrings [ 0 ] );
	xmstrings[0] = XmStringCreateLtoR("atan", (XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstrings[0]); ac++;
	button_atan = XmCreatePushButton ( col4form, "calc_button", al, ac );
	ac = 0;
	XmStringFree ( xmstrings [ 0 ] );
	var_popup_form = XmCreateForm ( rcform, "var_popup_form", al, ac );
	xmstrings[0] = XmStringCreateLtoR("Constants", (XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstrings[0]); ac++;
	var_popup = XmCreateOptionMenu ( var_popup_form, "var_popup", al, ac );
	ac = 0;
	XmStringFree ( xmstrings [ 0 ] );
	OptionLabel = XmOptionLabelGadget ( var_popup );
	OptionButton = XmOptionButtonGadget ( var_popup );
	var_menu = XmCreatePulldownMenu ( var_popup, "var_menu", al, ac );
	xmstrings[0] = XmStringCreateLtoR("e", (XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstrings[0]); ac++;
	button_e = XmCreatePushButton ( var_menu, "calc_button", al, ac );
	ac = 0;
	XmStringFree ( xmstrings [ 0 ] );
	xmstrings[0] = XmStringCreateLtoR("pi", (XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstrings[0]); ac++;
	button_pi = XmCreatePushButton ( var_menu, "calc_button", al, ac );
	ac = 0;
	XmStringFree ( xmstrings [ 0 ] );
	space_clear_form = XmCreateForm ( var_popup_form, "space_clear_form", al, ac );
	xmstrings[0] = XmStringCreateLtoR(" ", (XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstrings[0]); ac++;
	space_button = XmCreatePushButton ( space_clear_form, "calc_button", al, ac );
	ac = 0;
	XmStringFree ( xmstrings [ 0 ] );
	xmstrings[0] = XmStringCreateLtoR("Eval", (XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstrings[0]); ac++;
	eval_button = XmCreatePushButton ( space_clear_form, "calc_button", al, ac );
	ac = 0;
	XmStringFree ( xmstrings [ 0 ] );
	xmstrings[0] = XmStringCreateLtoR("Clear", (XmStringCharSet)XmFONTLIST_DEFAULT_TAG);
	XtSetArg(al[ac], XmNlabelString, xmstrings[0]); ac++;
	clear_button = XmCreatePushButton ( space_clear_form, "calc_button", al, ac );
	ac = 0;
	XmStringFree ( xmstrings [ 0 ] );

	XtSetArg(al[ac], XmNtopAttachment, XmATTACH_WIDGET); ac++;
	XtSetArg(al[ac], XmNtopWidget, var_popup_form); ac++;
	XtSetArg(al[ac], XmNbottomAttachment, XmATTACH_FORM); ac++;
	XtSetArg(al[ac], XmNleftAttachment, XmATTACH_FORM); ac++;
	XtSetArg(al[ac], XmNrightAttachment, XmATTACH_FORM); ac++;
	XtSetValues ( buttonform,al, ac );
	ac = 0;

	XtSetArg(al[ac], XmNtopAttachment, XmATTACH_FORM); ac++;
	XtSetArg(al[ac], XmNleftAttachment, XmATTACH_FORM); ac++;
	XtSetArg(al[ac], XmNrightAttachment, XmATTACH_FORM); ac++;
	XtSetValues ( var_popup_form,al, ac );
	ac = 0;

	XtSetArg(al[ac], XmNtopAttachment, XmATTACH_FORM); ac++;
	XtSetArg(al[ac], XmNtopOffset, 0); ac++;
	XtSetArg(al[ac], XmNbottomAttachment, XmATTACH_FORM); ac++;
	XtSetArg(al[ac], XmNbottomOffset, 0); ac++;
	XtSetArg(al[ac], XmNleftAttachment, XmATTACH_FORM); ac++;
	XtSetArg(al[ac], XmNleftOffset, 0); ac++;
	XtSetArg(al[ac], XmNrightAttachment, XmATTACH_POSITION); ac++;
	XtSetArg(al[ac], XmNrightPosition, 25); ac++;
	XtSetValues ( col1form,al, ac );
	ac = 0;

	XtSetArg(al[ac], XmNtopAttachment, XmATTACH_FORM); ac++;
	XtSetArg(al[ac], XmNtopOffset, 0); ac++;
	XtSetArg(al[ac], XmNbottomAttachment, XmATTACH_FORM); ac++;
	XtSetArg(al[ac], XmNbottomOffset, 0); ac++;
	XtSetArg(al[ac], XmNleftAttachment, XmATTACH_POSITION); ac++;
	XtSetArg(al[ac], XmNleftPosition, 25); ac++;
	XtSetArg(al[ac], XmNrightAttachment, XmATTACH_POSITION); ac++;
	XtSetArg(al[ac], XmNrightPosition, 50); ac++;
	XtSetValues ( col2form,al, ac );
	ac = 0;

	XtSetArg(al[ac], XmNtopAttachment, XmATTACH_FORM); ac++;
	XtSetArg(al[ac], XmNtopOffset, 0); ac++;
	XtSetArg(al[ac], XmNbottomAttachment, XmATTACH_FORM); ac++;
	XtSetArg(al[ac], XmNbottomOffset, 0); ac++;
	XtSetArg(al[ac], XmNleftAttachment, XmATTACH_POSITION); ac++;
	XtSetArg(al[ac], XmNleftPosition, 50); ac++;
	XtSetArg(al[ac], XmNrightAttachment, XmATTACH_POSITION); ac++;
	XtSetArg(al[ac], XmNrightPosition, 75); ac++;
	XtSetValues ( col3form,al, ac );
	ac = 0;

	XtSetArg(al[ac], XmNtopAttachment, XmATTACH_FORM); ac++;
	XtSetArg(al[ac], XmNtopOffset, 0); ac++;
	XtSetArg(al[ac], XmNbottomAttachment, XmATTACH_FORM); ac++;
	XtSetArg(al[ac], XmNbottomOffset, 0); ac++;
	XtSetArg(al[ac], XmNleftAttachment, XmATTACH_POSITION); ac++;
	XtSetArg(al[ac], XmNleftPosition, 75); ac++;
	XtSetArg(al[ac], XmNrightAttachment, XmATTACH_FORM); ac++;
	XtSetArg(al[ac], XmNrightOffset, 0); ac++;
	XtSetValues ( col4form,al, ac );
	ac = 0;

	XtSetArg(al[ac], XmNtopAttachment, XmATTACH_FORM); ac++;
	XtSetArg(al[ac], XmNbottomAttachment, XmATTACH_POSITION); ac++;
	XtSetArg(al[ac], XmNbottomPosition, 16); ac++;
	XtSetArg(al[ac], XmNleftAttachment, XmATTACH_FORM); ac++;
	XtSetArg(al[ac], XmNrightAttachment, XmATTACH_FORM); ac++;
	XtSetValues ( button_eq,al, ac );
	ac = 0;

	XtSetArg(al[ac], XmNtopAttachment, XmATTACH_POSITION); ac++;
	XtSetArg(al[ac], XmNtopPosition, 16); ac++;
	XtSetArg(al[ac], XmNbottomAttachment, XmATTACH_POSITION); ac++;
	XtSetArg(al[ac], XmNbottomPosition, 33); ac++;
	XtSetArg(al[ac], XmNleftAttachment, XmATTACH_FORM); ac++;
	XtSetArg(al[ac], XmNrightAttachment, XmATTACH_FORM); ac++;
	XtSetValues ( button_plus,al, ac );
	ac = 0;

	XtSetArg(al[ac], XmNtopAttachment, XmATTACH_POSITION); ac++;
	XtSetArg(al[ac], XmNtopPosition, 33); ac++;
	XtSetArg(al[ac], XmNbottomAttachment, XmATTACH_POSITION); ac++;
	XtSetArg(al[ac], XmNbottomPosition, 50); ac++;
	XtSetArg(al[ac], XmNleftAttachment, XmATTACH_FORM); ac++;
	XtSetArg(al[ac], XmNrightAttachment, XmATTACH_FORM); ac++;
	XtSetValues ( button7,al, ac );
	ac = 0;

	XtSetArg(al[ac], XmNtopAttachment, XmATTACH_POSITION); ac++;
	XtSetArg(al[ac], XmNtopPosition, 50); ac++;
	XtSetArg(al[ac], XmNbottomAttachment, XmATTACH_POSITION); ac++;
	XtSetArg(al[ac], XmNbottomPosition, 66); ac++;
	XtSetArg(al[ac], XmNleftAttachment, XmATTACH_FORM); ac++;
	XtSetArg(al[ac], XmNrightAttachment, XmATTACH_FORM); ac++;
	XtSetValues ( button4,al, ac );
	ac = 0;

	XtSetArg(al[ac], XmNtopAttachment, XmATTACH_POSITION); ac++;
	XtSetArg(al[ac], XmNtopPosition, 66); ac++;
	XtSetArg(al[ac], XmNbottomAttachment, XmATTACH_POSITION); ac++;
	XtSetArg(al[ac], XmNbottomPosition, 83); ac++;
	XtSetArg(al[ac], XmNleftAttachment, XmATTACH_FORM); ac++;
	XtSetArg(al[ac], XmNrightAttachment, XmATTACH_FORM); ac++;
	XtSetValues ( button1,al, ac );
	ac = 0;

	XtSetArg(al[ac], XmNtopAttachment, XmATTACH_POSITION); ac++;
	XtSetArg(al[ac], XmNtopPosition, 83); ac++;
	XtSetArg(al[ac], XmNbottomAttachment, XmATTACH_FORM); ac++;
	XtSetArg(al[ac], XmNleftAttachment, XmATTACH_FORM); ac++;
	XtSetArg(al[ac], XmNrightAttachment, XmATTACH_FORM); ac++;
	XtSetValues ( button0,al, ac );
	ac = 0;
	XtAddCallback (button_eq, XmNactivateCallback, insert_callback,topshell->command);
	XtAddCallback (button_plus, XmNactivateCallback, insert_callback,topshell->command);
	XtAddCallback (button7, XmNactivateCallback, insert_callback,topshell->command);
	XtAddCallback (button4, XmNactivateCallback, insert_callback,topshell->command);
	XtAddCallback (button1, XmNactivateCallback, insert_callback,topshell->command);
	XtAddCallback (button0, XmNactivateCallback, insert_callback,topshell->command);
	children[ac++] = button_eq;
	children[ac++] = button_plus;
	children[ac++] = button7;
	children[ac++] = button4;
	children[ac++] = button1;
	children[ac++] = button0;
	XtManageChildren(children, ac);
	ac = 0;

	XtSetArg(al[ac], XmNtopAttachment, XmATTACH_FORM); ac++;
	XtSetArg(al[ac], XmNbottomAttachment, XmATTACH_POSITION); ac++;
	XtSetArg(al[ac], XmNbottomPosition, 16); ac++;
	XtSetArg(al[ac], XmNleftAttachment, XmATTACH_FORM); ac++;
	XtSetArg(al[ac], XmNrightAttachment, XmATTACH_FORM); ac++;
	XtSetValues ( button_left,al, ac );
	ac = 0;

	XtSetArg(al[ac], XmNtopAttachment, XmATTACH_POSITION); ac++;
	XtSetArg(al[ac], XmNtopPosition, 16); ac++;
	XtSetArg(al[ac], XmNbottomAttachment, XmATTACH_POSITION); ac++;
	XtSetArg(al[ac], XmNbottomPosition, 33); ac++;
	XtSetArg(al[ac], XmNleftAttachment, XmATTACH_FORM); ac++;
	XtSetArg(al[ac], XmNrightAttachment, XmATTACH_FORM); ac++;
	XtSetValues ( button_minus,al, ac );
	ac = 0;

	XtSetArg(al[ac], XmNtopAttachment, XmATTACH_POSITION); ac++;
	XtSetArg(al[ac], XmNtopPosition, 33); ac++;
	XtSetArg(al[ac], XmNbottomAttachment, XmATTACH_POSITION); ac++;
	XtSetArg(al[ac], XmNbottomPosition, 50); ac++;
	XtSetArg(al[ac], XmNleftAttachment, XmATTACH_FORM); ac++;
	XtSetArg(al[ac], XmNrightAttachment, XmATTACH_FORM); ac++;
	XtSetValues ( button8,al, ac );
	ac = 0;

	XtSetArg(al[ac], XmNtopAttachment, XmATTACH_POSITION); ac++;
	XtSetArg(al[ac], XmNtopPosition, 50); ac++;
	XtSetArg(al[ac], XmNbottomAttachment, XmATTACH_POSITION); ac++;
	XtSetArg(al[ac], XmNbottomPosition, 66); ac++;
	XtSetArg(al[ac], XmNleftAttachment, XmATTACH_FORM); ac++;
	XtSetArg(al[ac], XmNrightAttachment, XmATTACH_FORM); ac++;
	XtSetValues ( button5,al, ac );
	ac = 0;

	XtSetArg(al[ac], XmNtopAttachment, XmATTACH_POSITION); ac++;
	XtSetArg(al[ac], XmNtopPosition, 66); ac++;
	XtSetArg(al[ac], XmNbottomAttachment, XmATTACH_POSITION); ac++;
	XtSetArg(al[ac], XmNbottomPosition, 83); ac++;
	XtSetArg(al[ac], XmNleftAttachment, XmATTACH_FORM); ac++;
	XtSetArg(al[ac], XmNrightAttachment, XmATTACH_FORM); ac++;
	XtSetValues ( button2,al, ac );
	ac = 0;

	XtSetArg(al[ac], XmNtopAttachment, XmATTACH_POSITION); ac++;
	XtSetArg(al[ac], XmNtopPosition, 83); ac++;
	XtSetArg(al[ac], XmNbottomAttachment, XmATTACH_FORM); ac++;
	XtSetArg(al[ac], XmNleftAttachment, XmATTACH_FORM); ac++;
	XtSetArg(al[ac], XmNrightAttachment, XmATTACH_FORM); ac++;
	XtSetValues ( button_decimal,al, ac );
	ac = 0;
	XtAddCallback (button_left, XmNactivateCallback, insert_callback,topshell->command);
	XtAddCallback (button_minus, XmNactivateCallback, insert_callback,topshell->command);
	XtAddCallback (button8, XmNactivateCallback, insert_callback,topshell->command);
	XtAddCallback (button5, XmNactivateCallback, insert_callback,topshell->command);
	XtAddCallback (button2, XmNactivateCallback, insert_callback,topshell->command);
	XtAddCallback (button_decimal, XmNactivateCallback, insert_callback,topshell->command);
	children[ac++] = button_left;
	children[ac++] = button_minus;
	children[ac++] = button8;
	children[ac++] = button5;
	children[ac++] = button2;
	children[ac++] = button_decimal;
	XtManageChildren(children, ac);
	ac = 0;

	XtSetArg(al[ac], XmNtopAttachment, XmATTACH_FORM); ac++;
	XtSetArg(al[ac], XmNbottomAttachment, XmATTACH_POSITION); ac++;
	XtSetArg(al[ac], XmNbottomPosition, 16); ac++;
	XtSetArg(al[ac], XmNleftAttachment, XmATTACH_FORM); ac++;
	XtSetArg(al[ac], XmNrightAttachment, XmATTACH_FORM); ac++;
	XtSetValues ( button_right,al, ac );
	ac = 0;

	XtSetArg(al[ac], XmNtopAttachment, XmATTACH_POSITION); ac++;
	XtSetArg(al[ac], XmNtopPosition, 16); ac++;
	XtSetArg(al[ac], XmNbottomAttachment, XmATTACH_POSITION); ac++;
	XtSetArg(al[ac], XmNbottomPosition, 33); ac++;
	XtSetArg(al[ac], XmNleftAttachment, XmATTACH_FORM); ac++;
	XtSetArg(al[ac], XmNrightAttachment, XmATTACH_FORM); ac++;
	XtSetValues ( button_times,al, ac );
	ac = 0;

	XtSetArg(al[ac], XmNtopAttachment, XmATTACH_POSITION); ac++;
	XtSetArg(al[ac], XmNtopPosition, 33); ac++;
	XtSetArg(al[ac], XmNbottomAttachment, XmATTACH_POSITION); ac++;
	XtSetArg(al[ac], XmNbottomPosition, 50); ac++;
	XtSetArg(al[ac], XmNleftAttachment, XmATTACH_FORM); ac++;
	XtSetArg(al[ac], XmNrightAttachment, XmATTACH_FORM); ac++;
	XtSetValues ( button9,al, ac );
	ac = 0;

	XtSetArg(al[ac], XmNtopAttachment, XmATTACH_POSITION); ac++;
	XtSetArg(al[ac], XmNtopPosition, 50); ac++;
	XtSetArg(al[ac], XmNbottomAttachment, XmATTACH_POSITION); ac++;
	XtSetArg(al[ac], XmNbottomPosition, 66); ac++;
	XtSetArg(al[ac], XmNleftAttachment, XmATTACH_FORM); ac++;
	XtSetArg(al[ac], XmNrightAttachment, XmATTACH_FORM); ac++;
	XtSetValues ( button6,al, ac );
	ac = 0;

	XtSetArg(al[ac], XmNtopAttachment, XmATTACH_POSITION); ac++;
	XtSetArg(al[ac], XmNtopPosition, 66); ac++;
	XtSetArg(al[ac], XmNbottomAttachment, XmATTACH_POSITION); ac++;
	XtSetArg(al[ac], XmNbottomPosition, 83); ac++;
	XtSetArg(al[ac], XmNleftAttachment, XmATTACH_FORM); ac++;
	XtSetArg(al[ac], XmNrightAttachment, XmATTACH_FORM); ac++;
	XtSetValues ( button3,al, ac );
	ac = 0;

	XtSetArg(al[ac], XmNtopAttachment, XmATTACH_POSITION); ac++;
	XtSetArg(al[ac], XmNtopPosition, 83); ac++;
	XtSetArg(al[ac], XmNbottomAttachment, XmATTACH_FORM); ac++;
	XtSetArg(al[ac], XmNleftAttachment, XmATTACH_FORM); ac++;
	XtSetArg(al[ac], XmNrightAttachment, XmATTACH_FORM); ac++;
	XtSetValues ( button_log10,al, ac );
	ac = 0;
	XtAddCallback (button_right, XmNactivateCallback, insert_callback,topshell->command);
	XtAddCallback (button_times, XmNactivateCallback, insert_callback,topshell->command);
	XtAddCallback (button9, XmNactivateCallback, insert_callback,topshell->command);
	XtAddCallback (button6, XmNactivateCallback, insert_callback,topshell->command);
	XtAddCallback (button3, XmNactivateCallback, insert_callback,topshell->command);
	XtAddCallback (button_log10, XmNactivateCallback, insert_callback,topshell->command);
	children[ac++] = button_right;
	children[ac++] = button_times;
	children[ac++] = button9;
	children[ac++] = button6;
	children[ac++] = button3;
	children[ac++] = button_log10;
	XtManageChildren(children, ac);
	ac = 0;

	XtSetArg(al[ac], XmNtopAttachment, XmATTACH_FORM); ac++;
	XtSetArg(al[ac], XmNbottomAttachment, XmATTACH_WIDGET); ac++;
	XtSetArg(al[ac], XmNbottomWidget, button_div); ac++;
	XtSetArg(al[ac], XmNleftAttachment, XmATTACH_FORM); ac++;
	XtSetArg(al[ac], XmNrightAttachment, XmATTACH_FORM); ac++;
	XtSetArg(al[ac], XmNrightOffset, 0); ac++;
	XtSetValues ( button_pow,al, ac );
	ac = 0;

	XtSetArg(al[ac], XmNtopAttachment, XmATTACH_POSITION); ac++;
	XtSetArg(al[ac], XmNtopPosition, 16); ac++;
	XtSetArg(al[ac], XmNbottomAttachment, XmATTACH_POSITION); ac++;
	XtSetArg(al[ac], XmNbottomPosition, 33); ac++;
	XtSetArg(al[ac], XmNleftAttachment, XmATTACH_FORM); ac++;
	XtSetArg(al[ac], XmNrightAttachment, XmATTACH_FORM); ac++;
	XtSetValues ( button_div,al, ac );
	ac = 0;

	XtSetArg(al[ac], XmNtopAttachment, XmATTACH_POSITION); ac++;
	XtSetArg(al[ac], XmNtopPosition, 33); ac++;
	XtSetArg(al[ac], XmNbottomAttachment, XmATTACH_POSITION); ac++;
	XtSetArg(al[ac], XmNbottomPosition, 50); ac++;
	XtSetArg(al[ac], XmNleftAttachment, XmATTACH_FORM); ac++;
	XtSetArg(al[ac], XmNrightAttachment, XmATTACH_FORM); ac++;
	XtSetValues ( button_loge,al, ac );
	ac = 0;

	XtSetArg(al[ac], XmNtopAttachment, XmATTACH_POSITION); ac++;
	XtSetArg(al[ac], XmNtopPosition, 50); ac++;
	XtSetArg(al[ac], XmNbottomAttachment, XmATTACH_POSITION); ac++;
	XtSetArg(al[ac], XmNbottomPosition, 66); ac++;
	XtSetArg(al[ac], XmNleftAttachment, XmATTACH_FORM); ac++;
	XtSetArg(al[ac], XmNrightAttachment, XmATTACH_FORM); ac++;
	XtSetValues ( button_sin,al, ac );
	ac = 0;

	XtSetArg(al[ac], XmNtopAttachment, XmATTACH_POSITION); ac++;
	XtSetArg(al[ac], XmNtopPosition, 66); ac++;
	XtSetArg(al[ac], XmNbottomAttachment, XmATTACH_POSITION); ac++;
	XtSetArg(al[ac], XmNbottomPosition, 83); ac++;
	XtSetArg(al[ac], XmNleftAttachment, XmATTACH_FORM); ac++;
	XtSetArg(al[ac], XmNrightAttachment, XmATTACH_FORM); ac++;
	XtSetValues ( button_cos,al, ac );
	ac = 0;

	XtSetArg(al[ac], XmNtopAttachment, XmATTACH_POSITION); ac++;
	XtSetArg(al[ac], XmNtopPosition, 83); ac++;
	XtSetArg(al[ac], XmNbottomAttachment, XmATTACH_FORM); ac++;
	XtSetArg(al[ac], XmNleftAttachment, XmATTACH_FORM); ac++;
	XtSetArg(al[ac], XmNrightAttachment, XmATTACH_FORM); ac++;
	XtSetValues ( button_atan,al, ac );
	ac = 0;
	XtAddCallback (button_pow, XmNactivateCallback, insert_callback,topshell->command);
	XtAddCallback (button_div, XmNactivateCallback, insert_callback,topshell->command);
	XtAddCallback (button_loge, XmNactivateCallback, insert_callback,topshell->command);
	XtAddCallback (button_sin, XmNactivateCallback, insert_callback,topshell->command);
	XtAddCallback (button_cos, XmNactivateCallback, insert_callback,topshell->command);
	XtAddCallback (button_atan, XmNactivateCallback, insert_callback,topshell->command);
	children[ac++] = button_pow;
	children[ac++] = button_div;
	children[ac++] = button_loge;
	children[ac++] = button_sin;
	children[ac++] = button_cos;
	children[ac++] = button_atan;
	XtManageChildren(children, ac);
	ac = 0;
	children[ac++] = col1form;
	children[ac++] = col2form;
	children[ac++] = col3form;
	children[ac++] = col4form;
	XtManageChildren(children, ac);
	ac = 0;

	XtSetArg(al[ac], XmNtopAttachment, XmATTACH_FORM); ac++;
	XtSetArg(al[ac], XmNbottomAttachment, XmATTACH_FORM); ac++;
	XtSetArg(al[ac], XmNleftAttachment, XmATTACH_FORM); ac++;
	XtSetArg(al[ac], XmNrightAttachment, XmATTACH_WIDGET); ac++;
	XtSetArg(al[ac], XmNrightWidget, space_clear_form); ac++;
	XtSetValues ( var_popup,al, ac );
	ac = 0;

	XtSetArg(al[ac], XmNtopAttachment, XmATTACH_FORM); ac++;
	XtSetArg(al[ac], XmNtopOffset, 0); ac++;
	XtSetArg(al[ac], XmNbottomAttachment, XmATTACH_FORM); ac++;
	XtSetArg(al[ac], XmNbottomOffset, 0); ac++;
	XtSetArg(al[ac], XmNleftAttachment, XmATTACH_NONE); ac++;
	XtSetArg(al[ac], XmNrightAttachment, XmATTACH_FORM); ac++;
	XtSetArg(al[ac], XmNrightOffset, 0); ac++;
	XtSetValues ( space_clear_form,al, ac );
	ac = 0;
	XtAddCallback (button_e, XmNactivateCallback, insert_callback,topshell->command);
	XtAddCallback (button_pi, XmNactivateCallback, insert_callback,topshell->command);
	children[ac++] = button_e;
	children[ac++] = button_pi;
	XtManageChildren(children, ac);
	ac = 0;
	XtSetArg(al[ac], XmNsubMenuId, var_menu); ac++;
	XtSetValues ( OptionButton, al, ac );
	ac = 0;

	XtSetArg(al[ac], XmNtopAttachment, XmATTACH_FORM); ac++;
	XtSetArg(al[ac], XmNtopOffset, 0); ac++;
	XtSetArg(al[ac], XmNbottomAttachment, XmATTACH_FORM); ac++;
	XtSetArg(al[ac], XmNleftAttachment, XmATTACH_FORM); ac++;
	XtSetArg(al[ac], XmNrightAttachment, XmATTACH_POSITION); ac++;
	XtSetArg(al[ac], XmNrightPosition, 33); ac++;
	XtSetValues ( space_button,al, ac );
	ac = 0;

	XtSetArg(al[ac], XmNtopAttachment, XmATTACH_FORM); ac++;
	XtSetArg(al[ac], XmNtopOffset, 0); ac++;
	XtSetArg(al[ac], XmNbottomAttachment, XmATTACH_FORM); ac++;
	XtSetArg(al[ac], XmNbottomOffset, 0); ac++;
	XtSetArg(al[ac], XmNleftAttachment, XmATTACH_POSITION); ac++;
	XtSetArg(al[ac], XmNleftPosition, 33); ac++;
	XtSetArg(al[ac], XmNrightAttachment, XmATTACH_POSITION); ac++;
	XtSetArg(al[ac], XmNrightPosition, 66); ac++;
	XtSetValues ( eval_button,al, ac );
	ac = 0;

	XtSetArg(al[ac], XmNtopAttachment, XmATTACH_FORM); ac++;
	XtSetArg(al[ac], XmNtopOffset, 0); ac++;
	XtSetArg(al[ac], XmNbottomAttachment, XmATTACH_FORM); ac++;
	XtSetArg(al[ac], XmNbottomOffset, 0); ac++;
	XtSetArg(al[ac], XmNleftAttachment, XmATTACH_POSITION); ac++;
	XtSetArg(al[ac], XmNleftPosition, 66); ac++;
	XtSetArg(al[ac], XmNrightAttachment, XmATTACH_FORM); ac++;
	XtSetArg(al[ac], XmNrightOffset, 0); ac++;
	XtSetValues ( clear_button,al, ac );
	ac = 0;
	XtAddCallback (space_button, XmNactivateCallback, insert_callback,topshell->command);
	XtAddCallback (eval_button, XmNactivateCallback, eval_callback,topshell->command);
	XtAddCallback (clear_button, XmNactivateCallback, clear_callback,topshell->command);
	children[ac++] = space_button;
	children[ac++] = eval_button;
	children[ac++] = clear_button;
	XtManageChildren(children, ac);
	ac = 0;
	children[ac++] = var_popup;
	children[ac++] = space_clear_form;
	XtManageChildren(children, ac);
	ac = 0;
	children[ac++] = buttonform;
	children[ac++] = var_popup_form;
	XtManageChildren(children, ac);
	ac = 0;
}

void topshell_c::create (Display *display, char *app_name, int app_argc, char **app_argv)
{
	Widget children[2];      /* Children to manage */
	Arg al[64];                    /* Arg List */
	register int ac = 0;           /* Arg Count */
	char from_s [256];             /* For resource conversion */
	XrmValue from_value, to_value; /* ditto */
	XtPointer tmp_value;             /* ditto */
	int fg, bg;                    /* colour values for pixmaps */ 
	XmString *list_items;          /* For list items */
	int list_item;                 /* Index for list_items */
	Atom *atom_list;               /* For Drop Site targets */
	XmString xmstrings[16];    /* temporary storage for XmStrings */

	XtSetArg(al[ac], XmNallowShellResize, TRUE); ac++;
	XtSetArg(al[ac], XmNtitle, "CalcDemo"); ac++;
	XtSetArg(al[ac], XmNargc, app_argc); ac++;
	XtSetArg(al[ac], XmNargv, app_argv); ac++;
	topshell = XtAppCreateShell ( app_name, "CalcDemo", applicationShellWidgetClass, display, al, ac );
	ac = 0;
	_xd_rootwidget = topshell;
	XtSetArg(al[ac], XmNwidth, 241); ac++;
	XtSetArg(al[ac], XmNheight, 481); ac++;
	XtSetArg(al[ac], XmNautoUnmanage, FALSE); ac++;
	topform = XmCreateForm ( topshell, "topform", al, ac );
	ac = 0;
	command->create ( topform );
	rcform->create ( topform );

	XtSetArg(al[ac], XmNtopAttachment, XmATTACH_FORM); ac++;
	XtSetArg(al[ac], XmNbottomAttachment, XmATTACH_WIDGET); ac++;
	XtSetArg(al[ac], XmNbottomWidget, rcform->xd_rootwidget()); ac++;
	XtSetArg(al[ac], XmNleftAttachment, XmATTACH_FORM); ac++;
	XtSetArg(al[ac], XmNrightAttachment, XmATTACH_FORM); ac++;
	XtSetValues ( command->xd_rootwidget(),al, ac );
	ac = 0;

	XtSetArg(al[ac], XmNtopAttachment, XmATTACH_NONE); ac++;
	XtSetArg(al[ac], XmNbottomAttachment, XmATTACH_FORM); ac++;
	XtSetArg(al[ac], XmNleftAttachment, XmATTACH_FORM); ac++;
	XtSetArg(al[ac], XmNrightAttachment, XmATTACH_FORM); ac++;
	XtSetValues ( rcform->xd_rootwidget(),al, ac );
	ac = 0;
	children[ac++] = command->xd_rootwidget();
	children[ac++] = rcform->xd_rootwidget();
	XtManageChildren(children, ac);
	ac = 0;
	XtManageChild ( topform);
}

topshell_c::topshell_c()
{
	command = new command_c;
	rcform = new rcform_c;
}

topshell_c::~topshell_c()
{
	delete command;
	delete rcform;
}

