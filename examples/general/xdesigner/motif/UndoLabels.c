/*
** An application which implements "Undo" should, according to the
** Motif style guide, change its label according to the action which
** is to be undone. For example, if you have just Cut text from a
** file, the label should read "Undo cut".
** This code gives one method for keeping the labels in the
** application's resource file and changing them dynamically.
**
** The basic idea is that we keep an array of undo labels, indexed by
** a number indicating the action to be undone.
*/

/*
** Firstly, define the actions:
*/
#define UNDO_NONE  0
#define UNDO_CUT   1
#define UNDO_COPY  2
.....

/*
** Next define an array to hold the undo labels:
*/
static XmString undo_labels[] = 
{
	0, /* UNDO_NONE         */
	0, /* UNDO_CUT          */
	0, /* UNDO_COPY         */
	.....
};

/*
** Then define an array for getting the labels from the resource file:
*/
static XtResource undo_resources[] = 
{
      {
	 "undoNone", XmCXmString, XmRXmString,
	 sizeof(XmString), UNDO_NONE * sizeof(XmString),
	 XmRImmediate,
	 0
      },
      {
	 "undoCut", XmCXmString, XmRXmString,
	 sizeof(XmString), UNDO_CUT * sizeof(XmString),
	 XmRImmediate,
	 0
      },
      .....
};

/*
** At some stage in the application startup code, do the following to
** actually fetch the labels into the array:
*/
#ifndef   _NO_PROTO
void init_undo_labels(Widget shell)
#else  /* _NO_PROTO */
void init_undo_labels(shell)
	Widget shell ;
#endif /* _NO_PROTO */
{
	XtGetApplicationResources(shell, undo_labels, undo_resources, XtNumber(undo_resources), (ArgList)0, 0);
}

/*
** Then we just need a function to access the array:
*/

#ifndef   _NO_PROTO
XmString undo_label(int action)
#else  /* _NO_PROTO */
XmString undo_label(action)
	int action;
#endif /* _NO_PROTO */
{
	static XmString dflt = (XmString) 0 ;

	if ((0 <= action) && (action < XtNumber(undo_labels)) && undo_labels[action]) {
		return undo_labels[action] ;
	}

	if (dflt == (XmString) 0) {
#if       (XmVERSION > 1)
		dflt = XmStringGenerate((char *) "Undo", XmFONTLIST_DEFAULT_TAG, XmCHARSET_TEXT, NULL) ;
#else  /* (XmVERSION > 1) */
		dflt = XmStringCreateLtoR("Undo", XmFONTLIST_DEFAULT_TAG) ;
#endif /* (XmVERSION > 1) */
	}

	return dflt ;
}

/*
** The code to actually change the label in the undo menu would look
** like this:
*/
#ifndef   _NO_PROTO
void set_undo_label(Widget undo_button, int action)
#else  /* _NO_PROTO */
void set_undo_label(undo_button, action)
	Widget undo_button;
	int    action;
#endif /* _NO_PROTO */
{
	XmString xms = undo_label(action);

	XtVaSetValues(undo_button, XmNlabelString, xms, 0) ;
	XtSetSensitive(undo_button, action != UNDO_NONE);
}


/*
** Finally, we need to write the resource file.
** The undo labels should go into the resource file as follows:

   <app-name>.undoNone: Can't Undo
   <app-name>.undoCut: Undo Cut
   <app-name>.undoCopy: Undo Copy
   .....

*/
