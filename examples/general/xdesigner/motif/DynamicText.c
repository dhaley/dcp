/*
** Occasionally, it is nice to be able to pop up a Text widget
** dynamically. An example is in a drawing program where a user wants
** to enter a label on a diagram. To enter the label a Text widget can be
** popped up, and then popped down again when <return> is pressed or
** when another drawing tool is selected.
** The following two functions implement such a text widget:
*/

/*
** In the following:
**      text is the dynamic text widget
**      da is the DrawingArea it is being popped up in
**      shell is the Shell containing the drawing area
*/


#ifndef   _NO_PROTO
Widget popup_text_widget(Widget shell, Widget da, int x, int y)
#else  /* _NO_PROTO */
Widget popup_text_widget(shell, da, x, y)
	Widget shell;
	Widget da;
	int    x;
	int    y;
#endif /* _NO_PROTO */
{
	Arg al[2];
	int ac = 0;

	XtSetArg(al[ac], XmNx, x); ac++;
	XtSetArg(al[ac], XmNy, y); ac++;

	text = XmCreateText(da, "dynamic_text", al, ac);

	XtManageChild(text);
	XtSetKeyboardFocus(shell, text);

	return text;
}


#ifndef   _NO_PROTO
void popdown_text_widget(Widget shell, Widget da, Widget text)
#else  /* _NO_PROTO */
void popdown_text_widget(shell, da, text)
	Widget shell ;
	Widget da ;
	Widget text ;
#endif /* _NO_PROTO */
{
	XtUnmanageChild(text);

	XtSetKeyboardFocus(shell, da);
}
