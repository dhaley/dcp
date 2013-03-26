/*@ cc -c -D_NO_PROTO @I @F -o @R.o
*/

/* TEXT WIDGET VALIDATION */

#include <Xm/Xm.h>


#ifndef   _NO_PROTO
void text_widget_verify_callback(Widget    w,
                                 XtPointer client_data,
				 XtPointer call_data)
#else  /* _NO_PROTO */
void text_widget_verify_callback(w, client_data, call_data)
	Widget    w ;
	XtPointer client_data ;
	XtPointer call_data ;
#endif /* _NO_PROTO */
{
	XmTextVerifyCallbackStruct *tv ;
	int i ;

	tv = (XmTextVerifyCallbackStruct *) call_data ;

	/* IS THIS CALLBACK CALLED FOR MODIFY VERIFY REASONS ? */

	switch (tv->reason) {
		/* Usual Reasons a Text Callback is Called... */

		case XmCR_MODIFYING_TEXT_VALUE :
			/* Modify Verify Callback     */
			/* Normal Verification Reason */

			/* ... */

		case XmCR_MOVING_INSERT_CURSOR :
			/* Motion Verify Callback */

			/* ... */

		case XmCR_ACTIVATE             :
			/* Activate Callback */

			/* ... */

		case XmCR_FOCUS                :
			/* Focus Callback */

			/* ... */

		case XmCR_LOSING_FOCUS         :
			/* Focus Callback */

			/* ... */

		case XmCR_GAIN_PRIMARY         :
			/* Focus Callback */

			/* ... */

		default                        :
			break ;
	}

	/* TEXT EVENT DISCRIMINATION: HOW DO I KNOW WHAT'S HAPPENED ? */

	if (!tv->event) {
		/* NIL EVENT: EITHER PROGRAMMATIC CHANGE */
		/*            OR MOUSE PASTE OPERATION   */

		if (tv->text->length > 1) {
			/* MULTI-CHARACTER REPLACE/INSERT/PASTE */

			/* ... */
		}

		/* ... */
	}

	if (tv->event && (tv->text->length == 0)) {
		/* USER HAS DELETED CHARACTERS (FORWARDS OR BACKWARDS) */
		/* Generally Just Return Here...                       */

		/* ... */
	}

	if (tv->event && (tv->text->length == 1)) {
		/* USER HAS TYPED A SINGLE CHARACTER          */

		/* IF THIS WAS A MOUSE PASTE OF ONE CHARACTER */
		/* THEN tv->event WOULD BE NULL...            */

		/* ... */
	}

	/* TEXT INPUT VALIDATION (EITHER MOUSE PASTE OR KEYBOARD INPUT) */
	
	if (tv->text->length > 0) {
		/* EXAMPLE: VERIFY/ALLOW INTEGER INPUT ONLY */

		for (i = 0 ; i < tv->text->length ; i++) {
			/* NB: #include <ctype.h> */

			if (!isdigit(tv->text->ptr[i])) {
				/* FORBID USER ACTION */
				
				tv->doit = False ;

				/* Usual on Validation Failure      */
				/* NB: default is tv->doit set true */
				/* When passed into this function   */

				return ;
			}
		}
	}

	/* TEXT INPUT/OUTPUT MAPPING          */
	/* EXAMPLE: PASSWORD STYLE TEXT FIELD */

	for (i = 0 ; i < tv->text->length ; i++) {
		/* Only Display '*'                   */
		/* NB: you will need to squirrel away */
		/*     real input value somewhere...  */

		tv->text->ptr[i] = '*' ;
	}

	/* Where in Text Field did User Action Take Place ?                 */
	/*                                                                  */
	/* tv->startPos   - start location of modified text range           */
	/* tv->endPos     - end   location of modified text range           */
	/* tv->currInsert - cursor insertion location at start of operation */
	/* tv->newInsert  - cursor insertion location at end   of operation */
	/*                                                                  */
	/* NB: positions offset from first location of ZERO                 */
}
