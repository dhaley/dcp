/*@ cc -c -D_NO_PROTO @I @F -o @R.o
*/

/* POPPING UP MENUS IN A DRAWING AREA */

#include <Xm/Xm.h>

/* (1) Create a handler to process mouse button press events */

void menu_popup_handler(drawing_area,client_data,event)
	Widget               drawing_area ;
	XtPointer            client_data ;
	XButtonPressedEvent *event ;
{
	extern Widget create_or_pick_some_menu(/* ... */) ;

	Widget popup_menu ;

	/* Lets suppose we are only poping up menus on mouse button 3  */
	/* You could of course have completely different menus for     */
	/* for mouse button 2. event->button would allow you to decide */
	/* which of the menus to display. NB: XmMenuPost resource.     */

	if (event->button != Button3) {
		return ;
	}

	/* Get the Menu we want to display                             */
	/* You could pass this in as client_data suitably cast...      */

	/* Note that if you create a drawing area menu in X-Designer   */
	/* there will (by default) be a function generated to create   */
	/* the menu hierarchy. You could just call that here.          */

	popup_menu = create_or_pick_some_menu(/* ... */) ;

	if (popup_menu != (Widget) 0) {
		/* Place the Menu at the Cursor Location */

		XmMenuPosition(popup_menu,event) ;

		/* Display it */

		XtManageChild(popup_menu) ;
	}
}


/* (2) Install the Handler for the Drawing Area in Question */
/* Only need to do this once when creating the drawing area */

void drawing_area_menus_init(drawing_area)
	Widget drawing_area ;
{
	XtAddEventHandler(drawing_area,
			  ButtonPressMask,
			  False,
			  menu_popup_handler,
			  NULL) ;  /* Or, say, the menu to display   */
}

/* (3) When Finished Processing Events                               */
/* No need to call this if just destroying the drawing area widget   */
/* NB: parameters passed here must match XtAddEventHandler() EXACTLY */

void drawing_area_menus_close(drawing_area)
	Widget drawing_area ;
{
	XtRemoveEventHandler(drawing_area,
			     ButtonPressMask,
			     False,
			     menu_popup_handler,
			     NULL) ; 
}

/* NOTES:                                                           */
/*                                                                  */
/* You can have as many popup menus as you like                     */
/* the drawable popup handler can simply chose which is appropriate */
/* so you can have lots of context-sensitive menus                  */

/* WARNINGS:                                                        */
/*                                                                  */
/* When debugging, NEVER put a breakpoint inside the popup handler  */
/* as you can seriously hang everything.                            */
/*                                                                  */
/* Try and pre-create as much of the menu system as you can OUTSIDE */
/* the popup handler. If your dynamic menu creation consumes too    */
/* much time, you may not get to see the menu since some internal   */
/* timers may kill the menu popup request.                          */
/*                                                                  */
/* The system creates a special shell to contain the menu which is  */
/* parented off the root window - this is so your menu can grow     */
/* outside the bounds of your application (all windows are clipped  */
/* by their parents, and this is how this problem is overcome).     */

/* You have, I recall, two seconds from special shell create to the */
/* final menu popup. If you exceed this the shell is destroyed for  */
/* various reasons. So if you exceed this, you wont see your menu.  */
