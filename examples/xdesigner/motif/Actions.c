/*
** The DrawingArea widget is often used as an interactive widget,
** handling mouse clicks and key presses etc. Although the widget has
** an input callback which is called whenever such an event occurs in
** it, it is better to use the Translations mechanism for handling
** input. This allows the redefinition of translations in defaults
** files.
** The following code demonstrates the setting of default Translations
** and Actions for a DrawingArea widget.
*/

/*
** Firstly, define your actions. We are assuming an application such
** as a drawing package:
*/

/* Forward declarations of the action procedures: */

#ifndef   _NO_PROTO
static void Select(Widget, XEvent *, String *, Cardinal *) ;
static void Extend(Widget, XEvent *, String *, Cardinal *) ;
static void Redraw(Widget, XEvent *, String *, Cardinal *) ;
static void Clear(Widget, XEvent *, String *, Cardinal *) ;
#else  /* _NO_PROTO */
static void Select() ;
static void Extend() ;
static void Redraw() ;
static void Clear() ;
#endif /* _NO_PROTO */


/* Define an array containing the mapping from action names to actions: */
static XtActionsRec da_actions[] = 
{
	{ "Redraw",     Redraw },
	{ "Select",     Select },
	{ "Extend",     Extend },
	{ "Clear",      Clear },
} ;


/* Now define the default translations: */
static char da_keys[] = 
{
	"~Ctrl ~Shift ~Meta<Btn1Down>: Select() \n\
	 ~Ctrl  Shift ~Meta<Btn1Down>: Extend() \n\
	 <Key>Delete: Clear() \n\
	 Ctrl<Key>R: Redraw()"
} ;


/* A sample callback, called for the "Select" action. */
/* ARGSUSED */
#ifndef   _NO_PROTO
static void Select(Widget    w,
                   XEvent   *event,
		   String   *params,
		   Cardinal *num_params)
#else  /* _NO_PROTO */
static void Select(w, event, params, num_params)
	Widget    w;
	XEvent   *event;
	String   *params;
	Cardinal *num_params;
#endif /* _NO_PROTO */
{
	XButtonEvent *button_event = (XButtonEvent *) event ;
}


/*
** Finally, after creating the DrawingArea, set up the translations
** for it.
*/

#ifndef   _NO_PROTO
void set_translations(XtAppContext app_context, Widget w)
#else  /* _NO_PROTO */
void set_translations(app_context, w)
	XtAppContext app_context ;
	Widget       w ;
#endif /* _NO_PROTO */
{
	XtTranslations da_translations ;

	XtAppAddActions(app_context, da_actions, XtNumber(da_actions)) ;

	if ((da_translations = XtParseTranslationTable(da_keys)) != (XtTranslations) 0) {
		XtOverrideTranslations(w, da_translations) ;
	}
}
