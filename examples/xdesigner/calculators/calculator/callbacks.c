/*
** Calculator: A sample X-Designer application.
**
** This program is a simple example of using X-Designer to produce a
** real application.  It consists of a simple 4-function calculator
** with a few functions such as sin, cos, sqare root etc. It is not
** intended to be used as a real calculator, as quite a bit more work
** would need to be done in order to make it work in a proper and complete
** manner.  It does, however, demonstrate the principles.
**
** The user interface of the calculator is designed with X-Designer, the
** design being in the file "calculator.xd".  The generated code for
** this is placed in the file "calculator.xc".  The X-Designer default
** main program option is used and all resources are generated in the C
** file.
**
** This file contains the callbacks for all the buttons in the design.
** These are grouped into several groups: digits, binary operators, unary
** operators and some miscellaneous ones, such as Clear and decimal point.
** Most of the code in here is actually concerned with implementing the
** calculator functionality.
**
** Note the use of callback client data to pass arguments to the callbacks.
** This allows a callback to be shared between several buttons.
*/

#include <Xm/Xm.h>
#include <math.h>

/* Possible calculator states */
#define CLEARED         0       /* Initial state */
#define ENTERING_FIRST  1       /* Entering a first operand */
#define BINOP_ENTERED   2       /* Just entered a binary operator */
#define ENTERING_SECOND 3       /* Entering a second operand, binaru op pending */

static double first_operand;    /* The first operand of a binary operator */
static double second_operand;   /* The second operand of a binary operator */
static int state = CLEARED;     /* Current state */
static int operator;            /* Pending binary operator */
static int new_number = 1;      /* A digit starts a new number if true */

/*
** The callback for the digit buttons.  The client data is the value of
** the digit.
*/
digit(w, client_data, call_data)
	Widget w;
	char *client_data;
	char *call_data;
{
	int n = (int)client_data;
	if (new_number) {
		first_operand = second_operand;
		second_operand = 0.0;
		new_number = 0;
	}
	second_operand = second_operand * 10 + n;
	set_display(second_operand);
	if (state == BINOP_ENTERED)
		state = ENTERING_SECOND;
	else if ( state != ENTERING_SECOND )
		state = ENTERING_FIRST;
}

/* The callback for the deciaml point button - not implemented yet! */
decimal_point()
{
}

/*
** Perform the pending binary operator
*/
static
do_pending_op()
{
	switch (operator) {
	case '+':
		second_operand = first_operand + second_operand;
		break;
	case '-':
		second_operand = first_operand - second_operand;
		break;
	case '*':
		second_operand = first_operand * second_operand;
		break;
	case '/':
		if (second_operand == 0.0) {
			set_error();
			return 0;
		} else
			second_operand = first_operand / second_operand;
		break;
	}
	return 1;
}

/*
** The callback for the binary operator functions. The client data contains
** a character describing the operator, e.g. '+' for addition.  Note that
** '=' is treated as a special binary operator.
*/
binary(w, client_data, call_data)
	Widget w;
	char *client_data;
	char *call_data;
{
	int op = (int)client_data;
	if (state == ENTERING_FIRST) {
		first_operand = second_operand;
	} else if (state == ENTERING_SECOND) {
		if (do_pending_op())
			set_display(second_operand);
	}
	if (op == '=')
		state = CLEARED;
	else
		state = BINOP_ENTERED;
	new_number = 1;
	operator = op;
}

/*
** The callback for uanry operators such as '+/-'
*/
unary(w, client_data, call_data)
	Widget w;
	char *client_data;
	char *call_data;
{
	int op = (int)client_data;
	switch (op) {
	case 's':
		second_operand = sin(second_operand);
		break;
	case 'c':
		second_operand = cos(second_operand);
		break;
	case 't':
		second_operand = tan(second_operand);
		break;
	case 'q':
		if (second_operand >= 0)
			second_operand = sqrt(second_operand);
		else {
			set_error();
			return;
		}
		break;
	case 'l':
		if (second_operand > 0)
			second_operand = log10(second_operand);
		else {
			set_error();
			return;
		}
		break;
	case 'L':
		if (second_operand > 0)
			second_operand = log(second_operand);
		else {
			set_error();
			return;
		}
		break;
	case '+':
		second_operand = -second_operand;
		break;
	}

	set_display(second_operand);
	if (state != ENTERING_SECOND)
		state = CLEARED;
	new_number = 1;
}

/* The callback for the 'C' button */
clear_entry()
{
	set_display(second_operand = 0.0);
	new_number = 1;
}

/* The callback for the 'AC' button */
clear_all()
{
	set_display(second_operand = 0.0);
	state = CLEARED;
	new_number = 1;
}

/* Set the display to a particular number */
static
set_display(n)
	double n;
{
	extern Widget calc_display;
	char buf[128];
	sprintf(buf, "%g", n);
	XmTextSetString(calc_display, buf);
}

/* Set the display to display an error */
static
set_error()
{
	extern Widget calc_display;
	XmTextSetString(calc_display, "Error");
	state = CLEARED;
	second_operand = 0.0;
	new_number = 1;
}
