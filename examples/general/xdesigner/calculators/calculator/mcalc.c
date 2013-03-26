/*
** Motif Calculator:
**
** Copyright (c) Jeremy Huxtable 1990
**
** You may do anything you like with this code, even sell it if you want.
**
** This module implements a family of calculators under the OSF/Motif
** look and feel. The calculator engine is in this file, which includes
** a file implementing the user interface, consisting of a single function
** called "create_calc_shell" which creates and initialises all the widgets.
** If you want a different look to your calculator, just rewrite this
** function.
**
** The calculator can function either in reverse Polish notation or normal
** infix notation. This is set with the "reversePolish" resource.
** Two modifier toggles are allowed for in the calculator. These are 'Inverse'
** and 'Hyperbolic' toggles which the calculator will set and unset as
** necessary. If your user interface doesn't have these buttons, they will
** be ignored.
*/

#include <math.h>

/*
** The operators:
*/
#define OP_ADD          1       /* Addition */
#define OP_SUB          2       /* Subtraction */
#define OP_MUL          3       /* Multiplication */
#define OP_DIV          4       /* Division */
#define OP_EQ           5       /* '=' operation */
#define OP_BRA          6       /* Open parenthesis */
#define OP_KET          7       /* Close parenthesis */
#define OP_LSH          8       /* Shift left */
#define OP_RSH          9       /* Shift right */
#define OP_AND          10      /* Bitwise AND */
#define OP_OR           11      /* Bitwise OR */
#define OP_XOR          12      /* Bitwise XOR */
#define OP_NOT          13      /* Bitwise NOT */
#define OP_MOD          14      /* Remainder */
#define OP_POW          15      /* Raise to power */
#define OP_SIN          16      /* Sine */
#define OP_COS          17      /* Cosine */
#define OP_TAN          18      /* Tangent */
#define OP_SINH         19      /* Hyperbolic sine */
#define OP_COSH         20      /* Hyperbolic cosine */
#define OP_TANH         21      /* Hyperbolic tangent */
#define OP_LOG          22      /* Logarithm to base 10 */
#define OP_LN           23      /* Logarithm to base e */
#define OP_SQR          24      /* Square root */
#define OP_SGN          25      /* Change sign */
#define OP_FAC          26      /* Factorial */
#define OP_EXP          27      /* Exponential */
#define OP_REC          28      /* Reciprocal */
#define OP_MP           29      /* Add to memory */
#define OP_MM           30      /* Subtract from memory */
#define OP_STO          31      /* Store in memory */
#define OP_RCL          32      /* Recall memory */

#ifndef   PI
#define   PI              3.1415926535897932384626433832795028841971693993751
#endif /* PI */

/*
** Angle units:
*/
#define DRG_DEG         0
#define DRG_RAD         1
#define DRG_GRAD        2

/*
** Some configuration limits:
*/
#define STACK_SIZE      100
#define OP_STACK_SIZE   32
#define DISPLAY_SIZE    30

typedef double Number;

/* Just plug in your user interface here */

#include "scientific.xc"

/*
#include "fourfunc.xc"
*/

#ifndef   _NO_PROTO
extern double atof(const char *) ;
#else  /* _NO_PROTO */
extern double atof() ;
#endif /* _NO_PROTO */


Widget inv_b ;
Widget hyp_b ;

static Display     *display         = (Display *) 0 ;     /* The display we're connected to                 */
static XtAppContext app_context     = (XtAppContext) 0 ;  /* Application Context ...                        */
static Number       memory          = 0.0 ;               /* The calculator "memory"                        */
static int          pending_op      = 0 ;                 /* Pending binary operator                        */
static int          have_point      = False ;             /* True if number contains decimal point          */
static int          result          = False ;             /* True if we are displaying a result             */
static int          last_was_binary = False ;             /* True if we have just entered a binary operator */
static int          sp              = 0 ;                 /* Operand stack pointer                          */
static int          op_sp           = 0 ;                 /* Operator stack pointer                         */
static int          num_length      = 0 ;                 /* Length of current number                       */
static Boolean      entering_number = False ;             /* Are we entering a number?                      */
static int          angle_units     = 180./PI;            /* Angle units                                    */
static Boolean      inverse         = False ;             /* Inverse function pending                       */
static Boolean      hyper           = False ;             /* Hyperbolic function pending                    */
static int          base            = 10 ;                /* Input/output radix                             */

static Number       stack[STACK_SIZE] ;                   /* Operand stack                                  */
static int          op_stack[OP_STACK_SIZE] ;             /* Operator stack                                 */
static char         number[DISPLAY_SIZE] ;                /* Number being entered                           */


/*
** The calculator preferences and messages:
*/
typedef struct Pref_s 
{
	String   pr_error_string;
	String   pr_over_string;
	String   pr_under_string;
	String   pr_infinity_string;
	String   pr_display_format;
	String   pr_string_format;

	Boolean  pr_reverse_polish;
	Boolean  pr_show_pending_op;
} Pref_t, *Pref_p;

static Pref_t preferences = { (String) 0, (String) 0, (String) 0, (String) 0, (String) 0, (String) 0, False, False } ;


#ifndef   _NO_PROTO
static char *op_name(int op)
#else  /* _NO_PROTO */
static char *op_name(op)
	int op ;
#endif /* _NO_PROTO */
{
	char *s = (char *) 0 ;

	switch (op) {
	case OP_ADD:
		s = "+";
		break;
	case OP_SUB:
		s = "-";
		break;
	case OP_MUL:
		s = "*";
		break;
	case OP_DIV:
		s = "/";
		break;
	case OP_MOD:
		s = "%";
		break;
	case OP_LSH:
		s = "<";
		break;
	case OP_RSH:
		s = ">";
		break;
	case OP_POW:
		s = "^";
		break;
	case OP_AND:
		s = "&";
		break;
	case OP_OR:
		s = "|";
		break;
	case OP_XOR:
		s = "x";
		break;
	}

	return s;
}


/* Display a string */

#ifndef   _NO_PROTO
static void display_str(char *s)
#else  /* _NO_PROTO */
static void display_str(s)
	char *s;
#endif /* _NO_PROTO */
{
	char buf[128];

	(void) sprintf(buf, preferences.pr_string_format, s);

	XmTextSetString(calc_display, buf);
}


#ifdef    SCO
#define finite(x) 1
#endif /* SCO */
#ifdef	S_HPUX
#define	finite(x) 1  /* actually finite before HPUX 11 */
#endif /* S_HPUX */


/* Display a number */

#ifndef   _NO_PROTO
static void display_number(double n)
#else  /* _NO_PROTO */
static void display_number(n)
	double n;
#endif /* _NO_PROTO */
{
	if (finite(n)) {
		char buf[128];

		(void) sprintf(buf, preferences.pr_display_format, n);

		if (pending_op && preferences.pr_show_pending_op) {
			char *s = op_name(pending_op);

			if (s != (char *) 0) {
				(void) strcat(buf, s);
			}
		}

		display_str(buf);
	} else {
		display_str(preferences.pr_infinity_string);
	}
}


/* Start a new entry */

#ifndef   _NO_PROTO
static void start_new(void)
#else  /* _NO_PROTO */
static void start_new()
#endif /* _NO_PROTO */
{
	entering_number = True;
	have_point = False;
	num_length = 0;
}


/* Display an error message */
#ifndef   _NO_PROTO
static void set_error(char *s)
#else  /* _NO_PROTO */
static void set_error(s)
	char *s ;
#endif /* _NO_PROTO */
{
	display_str(s);

	start_new();
}


/* Push an operand on the stack */
#ifndef   _NO_PROTO
static void push(Number n)
#else  /* _NO_PROTO */
static void push(n)
	Number n;
#endif /* _NO_PROTO */
{
	if (sp < STACK_SIZE) {
		stack[sp++] = n;
	}
	else {
		set_error(preferences.pr_over_string);
	}
}


/* Pop a number from the operand stack */
#ifndef   _NO_PROTO
static Number pop(void)
#else  /* _NO_PROTO */
static Number pop()
#endif /* _NO_PROTO */
{
	if (sp > 0) {
		return stack[--sp];
	}

	set_error(preferences.pr_under_string);

	return 0.0;
}


/* Push an operator */
#ifndef   _NO_PROTO
static void push_op(int op)
#else  /* _NO_PROTO */
static void push_op(op)
	int op ;
#endif /* _NO_PROTO */
{
	if (op_sp < OP_STACK_SIZE) {
		op_stack[op_sp++] = op;
	}
	else {
		set_error(preferences.pr_over_string);
	}
}


/* Pop a number from the operator stack */
#ifndef   _NO_PROTO
static int pop_op(void)
#else  /* _NO_PROTO */
static int pop_op()
#endif /* _NO_PROTO */
{
	if (op_sp > 0) {
		return op_stack[--op_sp];
	}

	set_error(preferences.pr_under_string);

	return 0;
}


/* Return the top number on the operand stack */

#ifndef   _NO_PROTO
static double top_of_stack(void)
#else  /* _NO_PROTO */
static double top_of_stack()
#endif /* _NO_PROTO */
{
	if (sp > 0) {
		return stack[sp-1];
	}

	set_error(preferences.pr_under_string);

	return 0.0;
}


/* Set the 'inverse' toggle for unary functions */

#ifndef   _NO_PROTO
static void set_inverse(Boolean i)
#else  /* _NO_PROTO */
static void set_inverse(i)
	Boolean i ;
#endif /* _NO_PROTO */
{
	if ((inverse != i) && inv_b) {
		XmToggleButtonSetState(inv_b, i, False);
	}

	inverse = i;
}


/* Add a digit to the number currently being entered */

#ifndef   _NO_PROTO
static void add_digit(char c)
#else  /* _NO_PROTO */
static void add_digit(c)
	char c;
#endif /* _NO_PROTO */
{
	if (num_length < (DISPLAY_SIZE-1)) {
		if (num_length == 1 && number[0] == '0') {
			if (c != '0') {
				number[0] = c;
			}
		} else {
			number[num_length++] = c;
		}

		number[num_length] = 0;
		display_str(number);
	}

	set_inverse(False);

	if (result && sp) {
		sp--;
	}

	result = False;
	last_was_binary = False;
}


/* Set the 'hyperbolic' toggle for circular functions */
#ifndef   _NO_PROTO
static void set_hyper(Boolean i)
#else  /* _NO_PROTO */
static void set_hyper(i)
	Boolean i ;
#endif /* _NO_PROTO */
{
	if ((inverse != i) && hyp_b) {
		XmToggleButtonSetState(hyp_b, i, False);
	}

	hyper = i;
}


/* Set the 'memory' indicator (if any) */
#ifndef   _NO_PROTO
static void set_memory(void)
#else  /* _NO_PROTO */
static void set_memory()
#endif /* _NO_PROTO */
{
	if (memory != 0)
		;
}


/*
** The callback for the digit buttons.  The client data is the value of
** the digit.
*/

/* ARGSUSED */
#ifndef   _NO_PROTO
static void digit_callback(Widget                      w,
                           XtPointer                   client_data,
			   XmPushButtonCallbackStruct *call_data)
#else  /* _NO_PROTO */
static void digit_callback(w, client_data, call_data)
	Widget               w ;
	XtPointer            client_data ;
	XmPushButtonCallbackStruct *call_data  ;
#endif /* _NO_PROTO */
{
	int n = (int) client_data ;

	add_digit(n + '0') ;
}


#ifndef   _NO_PROTO
static void check_entry(void)
#else  /* _NO_PROTO */
static void check_entry()
#endif /* _NO_PROTO */
{
	if (entering_number && num_length) {
		push(atof(number)) ;
	}

	entering_number = False;
}


#ifndef   _NO_PROTO
static void decimal_point(void)
#else  /* _NO_PROTO */
static void decimal_point()
#endif /* _NO_PROTO */
{
	if (!have_point) {
		if (num_length == 0) {
			add_digit('0');
		}

		add_digit('.');
		have_point = True;
	}
}


#ifndef   _NO_PROTO
static void set_base(int n)
#else  /* _NO_PROTO */
static void set_base(n)
	int n ;
#endif /* _NO_PROTO */
{
	if ((2 <= n) && (n <= 36)) {
		base = n;
	}
}


#ifndef   _NO_PROTO
static void set_pending(int op)
#else  /* _NO_PROTO */
static void set_pending(op)
	int op ;
#endif /* _NO_PROTO */
{
	pending_op = op;
}


/*
** Perform a binary operator
*/
#ifndef   _NO_PROTO
static Boolean binary(int operator)
#else  /* _NO_PROTO */
static Boolean binary(operator)
	int operator ;
#endif /* _NO_PROTO */
{
	Number first_operand, second_operand;

	if (sp < 2) {
		return False;
	}

	second_operand = pop();
	first_operand = pop();

	switch (operator) {
	case OP_ADD:
		second_operand = first_operand + second_operand;
		break;
	case OP_SUB:
		second_operand = first_operand - second_operand;
		break;
	case OP_MUL:
		second_operand = first_operand * second_operand;
		break;
	case OP_DIV:
		if (second_operand == 0.0) {
			push(0.0);
			return False;
		}
		second_operand = first_operand / second_operand;
		break;
	case OP_MOD:
		if ((int)second_operand == 0) {
			push(0.0);
			return False;
		}
#if defined(SCO) || defined(_PowerUX)
		second_operand = (int) first_operand % (int) second_operand;
#else   /* SCO || _PowerUX */
		second_operand = drem(first_operand, second_operand);
#endif  /* SCO || _PowerUX */
		break;
	case OP_POW:
		second_operand = pow(first_operand, second_operand);
		break;
	case OP_LSH:
		second_operand = (int)first_operand << (int)second_operand;
		break;
	case OP_RSH:
		second_operand = (int)first_operand >> (int)second_operand;
		break;
	case OP_AND:
		second_operand = (int)first_operand & (int)second_operand;
		break;
	case OP_OR:
		second_operand = (int)first_operand | (int)second_operand;
		break;
	case OP_XOR:
		second_operand = (int)first_operand ^ (int)second_operand;
		break;
	}
	push(second_operand);
	return True;
}


#ifndef   _NO_PROTO
static int unary(int op)
#else  /* _NO_PROTO */
static int unary(op)
	int op ;
#endif /* _NO_PROTO */
{
	Number operand = pop();

	if (hyper) {
		switch (op) {
			case OP_SIN:
			case OP_COS:
			case OP_TAN:
				op = op - OP_SIN + OP_SINH;
				break;
		}
		set_hyper(False);
	}
	switch (op) {
	case OP_SIN:
		if (inverse)
			operand = asin(operand) * angle_units;
		else
			operand = sin(operand / angle_units);
		break;
	case OP_COS:
		if (inverse)
			operand = acos(operand) * angle_units;
		else
			operand = cos(operand / angle_units);
		break;
	case OP_TAN:
		if (inverse)
			operand = atan(operand) * angle_units;
		else
			operand = tan(operand / angle_units);
		break;
	case OP_SINH:
#ifndef   SCO
		if (inverse)
			operand = asinh(operand);
		else
			operand = sinh(operand);
#endif /* SCO */
		break;
	case OP_COSH:
#ifndef    SCO
		if (inverse)
			operand = acosh(operand);
		else
			operand = cosh(operand);
#endif  /* SCO */
		break;
	case OP_TANH:
#ifndef    SCO
		if (inverse)
			operand = atanh(operand);
		else
			operand = tanh(operand);
#endif  /* SCO */
		break;
	case OP_SQR:
		if (inverse)
			operand *= operand;
		else {
			if (operand < 0)
				return False;
			operand = sqrt(operand);
		}
		break;
	case OP_LOG:
		if (inverse)
			operand = pow(10., operand);
		else {
			if (operand <= 0)
				return False;
			operand = log10(operand);
		}
		break;
	case OP_LN:
		if (inverse)
			operand = exp(operand);
		else {
			if (operand <= 0)
				return False;
			operand = log(operand);
		}
		break;
	case OP_EXP:
		if (!inverse)
			operand = exp(operand);
		else {
			if (operand <= 0)
				return False;
			operand = log(operand);
		}
		break;
	case OP_SGN:
		operand = -operand;
		break;
	case OP_REC:
		operand = 1/operand;
		break;
	case OP_MP:
		memory += operand;
		set_memory();
		break;
	case OP_MM:
		memory -= operand;
		set_memory();
		break;
	case OP_STO:
		memory = operand;
		set_memory();
		break;
	case OP_RCL:
		operand = memory;
		break;
	case OP_NOT:
		operand = ~(int)operand;
		break;
	case OP_FAC:
		if (operand < 1)
			return FALSE;
		operand = lgamma(operand+1);
		operand = signgam * exp(operand);
		break;
	case OP_BRA:
		push_op(pending_op);
		pending_op = 0;
		break;
	}
	push(operand);
	return True;
}


/*
** The callback for the binary operator functions.
*/
#ifndef   _NO_PROTO
static void binary_op(int op)
#else  /* _NO_PROTO */
static void binary_op(op)
	int op ;
#endif /* _NO_PROTO */
{
	check_entry();
	if (preferences.pr_reverse_polish) {
		if (binary(op))
			display_number(top_of_stack());
		else
			set_error(preferences.pr_error_string);
	} else {
		int ok = True;
		/* If we had two binary operators in a row, the second
		** overrides the first */
		if (pending_op && !last_was_binary) {
			ok = binary(pending_op);
		}
		result = False;
		/* '=' and ')' are honourary binary operators */
		switch (op) {
		case OP_EQ:
			pending_op = 0;
			result = True;
			break;
		case OP_KET:
			if (op_sp)
				set_pending(pop_op());
			else
				ok = False;
			break;
		default:
			set_pending(op);
			last_was_binary = True;
			break;
		}
		if (ok)
			display_number(top_of_stack());
		else
			set_error(preferences.pr_error_string);
	}
	start_new();
	set_inverse(False);
	set_hyper(False);
}


/*
** The callback for unary operators such as '+/-'
*/
#ifndef   _NO_PROTO
static void unary_op(int op)
#else  /* _NO_PROTO */
static void unary_op(op)
#endif /* _NO_PROTO */
{
	int ok;

	check_entry();
	ok = unary(op);
	set_pending(0);
	if (ok)
		display_number(top_of_stack());
	else
		set_error(preferences.pr_error_string);
	start_new();
	set_inverse(False);
	set_hyper(False);
	last_was_binary = False;
	if (op != OP_BRA)
		result = True;
}


#ifndef   _NO_PROTO
static void set_units(int u)
#else  /* _NO_PROTO */
static void set_units(u)
	int u ;
#endif /* _NO_PROTO */
{
	switch (u) {
	case DRG_DEG:
		angle_units = 180./PI;
		break;
	case DRG_RAD:
		angle_units = 1.;
		break;
	case DRG_GRAD:
		angle_units = 200./PI;
		break;
	}
}


/* ARGSUSED */
#ifndef   _NO_PROTO
static void inverse_callback(Widget                        w,
                             XtPointer                     client_data,
			     XmToggleButtonCallbackStruct *call_data)
#else  /* _NO_PROTO */
static void inverse_callback(w, client_data, call_data)
	Widget                        w;
	XtPointer                     client_data;
	XmToggleButtonCallbackStruct *call_data;
#endif /* _NO_PROTO */
{
	set_inverse(call_data->set);
}


/*
** The actions:
*/
/* ARGSUSED */
#ifndef   _NO_PROTO
static void Digit(Widget    w,
                  XEvent   *event,
		  String   *params,
		  Cardinal *num_params)
#else  /* _NO_PROTO */
static void Digit(w, event, params, num_params)
	Widget    w;
	XEvent   *event;
	String   *params;
	Cardinal *num_params;
#endif /* _NO_PROTO */
{
	if (*num_params) {
		char c = params[0][0];
		if (c == '.')
			decimal_point();
		else if ('0' <= c && c <= '9')
			add_digit(c-'0');
	}
}


/* ARGSUSED */
#ifndef   _NO_PROTO
static void Delete(Widget    w,
                   XEvent   *event,
		   String   *params,
		   Cardinal *num_params)
#else  /* _NO_PROTO */
static void Delete(w, event, params, num_params)
	Widget    w;
	XEvent   *event;
	String   *params;
	Cardinal *num_params;
#endif /* _NO_PROTO */
{
	if (num_length > 0) {
		if (num_length == 1)
			number[0] = '0';
		else {
			num_length--;
			if (number[num_length] == '.')
				have_point = FALSE;
			number[num_length] = 0;
		}
		display_str(number);
	}
	set_inverse(False);
	set_hyper(False);
	last_was_binary = False;
}


/* ARGSUSED */
#ifndef   _NO_PROTO
static void Error(Widget    w,
                  XEvent   *event,
		  String   *params,
		  Cardinal *num_params)
#else  /* _NO_PROTO */
static void Error(w, event, params, num_params)
	Widget    w;
	XEvent   *event;
	String   *params;
	Cardinal *num_params;
#endif /* _NO_PROTO */
{
	if (*num_params)
		set_error(params[0]);
}


/* ARGSUSED */
#ifndef   _NO_PROTO
static void Base(Widget    w,
                 XEvent   *event,
		 String   *params,
		 Cardinal *num_params)
#else  /* _NO_PROTO */
static void Base(w, event, params, num_params)
	Widget    w;
	XEvent   *event;
	String   *params;
	Cardinal *num_params;
#endif /* _NO_PROTO */
{
	if (*num_params)
		set_base(atoi(params[0]));
}


/* ARGSUSED */
#ifndef   _NO_PROTO
static void Inverse(Widget    w,
                    XEvent   *event,
		    String   *params,
		    Cardinal *num_params)
#else  /* _NO_PROTO */
static void Inverse(w, event, params, num_params)
	Widget    w;
	XEvent   *event;
	String   *params;
	Cardinal *num_params;
#endif /* _NO_PROTO */
{
	set_inverse(True);
}


/* ARGSUSED */
#ifndef   _NO_PROTO
static void Hyper(Widget    w,
                  XEvent   *event,
		  String   *params,
		  Cardinal *num_params)
#else  /* _NO_PROTO */
static void Hyper(w, event, params, num_params)
	Widget    w;
	XEvent   *event;
	String   *params;
	Cardinal *num_params;
#endif /* _NO_PROTO */
{
	set_hyper(True);
}


/* ARGSUSED */
#ifndef   _NO_PROTO
static void ClearEntry(Widget    w,
                       XEvent   *event, 
		       String   *params,
		       Cardinal *num_params)
#else  /* _NO_PROTO */
static void ClearEntry(w, event, params, num_params)
	Widget    w;
	XEvent   *event;
	String   *params;
	Cardinal *num_params;
#endif /* _NO_PROTO */
{
	start_new();
	display_number(0.0);
	set_inverse(False);
	set_hyper(False);
	last_was_binary = False;
}


/* ARGSUSED */
#ifndef   _NO_PROTO
static void ClearAll(Widget    w,
                     XEvent   *event, 
		     String   *params,
		     Cardinal *num_params)
#else  /* _NO_PROTO */
static void ClearAll(w, event, params, num_params)
	Widget    w;
	XEvent   *event;
	String   *params;
	Cardinal *num_params;
#endif /* _NO_PROTO */
{
	memory = 0;
	pending_op = 0;
	ClearEntry(w, event, params, num_params);
	op_sp = sp = 0;
	set_inverse(False);
	set_hyper(False);
	push(0.0);
	result = True;
}


/* ARGSUSED */
#ifndef   _NO_PROTO
static void EnterNumber(Widget    w,
                        XEvent   *event, 
		        String   *params,
		        Cardinal *num_params)
#else  /* _NO_PROTO */
static void EnterNumber(w, event, params, num_params)
	Widget    w;
	XEvent   *event;
	String   *params;
	Cardinal *num_params;
#endif /* _NO_PROTO */
{
	if (entering_number && num_length)
		push(atof(number));
	else if (sp)
		push(stack[sp-1]);
	else
		push(0.0);
	start_new();
	last_was_binary = False;
}


/* ARGSUSED */
#ifndef   _NO_PROTO
static void Exit(Widget    w,
                 XEvent   *event, 
		 String   *params,
		 Cardinal *num_params)
#else  /* _NO_PROTO */
static void Exit(w, event, params, num_params)
	Widget    w;
	XEvent   *event;
	String   *params;
	Cardinal *num_params;
#endif /* _NO_PROTO */
{
	exit(0);
}


/* ARGSUSED */
#ifndef   _NO_PROTO
static void Exch(Widget    w,
                 XEvent   *event, 
		 String   *params,
		 Cardinal *num_params)
#else  /* _NO_PROTO */
static void Exch(w, event, params, num_params)
	Widget    w;
	XEvent   *event;
	String   *params;
	Cardinal *num_params;
#endif /* _NO_PROTO */
{
	if (sp >= 2) {
		Number n = stack[sp-1];
		stack[sp-1] = stack[sp-2];
		stack[sp-2] = n;
	} else
		set_error(preferences.pr_under_string);
	last_was_binary = False;
}


/* ARGSUSED */
#ifndef   _NO_PROTO
static void Roll(Widget    w,
                 XEvent   *event, 
		 String   *params,
		 Cardinal *num_params)
#else  /* _NO_PROTO */
static void Roll(w, event, params, num_params)
	Widget    w;
	XEvent   *event;
	String   *params;
	Cardinal *num_params;
#endif /* _NO_PROTO */
{
	if (sp >= 3) {
		Number n = stack[sp-1];
		stack[sp-1] = stack[sp-2];
		stack[sp-2] = stack[sp-3];
		stack[sp-3] = n;
	} else
		set_error(preferences.pr_under_string);
	last_was_binary = False;
}


/* ARGSUSED */
#ifndef   _NO_PROTO
static void Dup(Widget    w,
                XEvent   *event, 
		String   *params,
		Cardinal *num_params)
#else  /* _NO_PROTO */
static void Dup(w, event, params, num_params)
	Widget    w;
	XEvent   *event;
	String   *params;
	Cardinal *num_params;
#endif /* _NO_PROTO */
{
	if (sp > 0)
		push(stack[sp-1]);
	else
		set_error(preferences.pr_under_string);
	last_was_binary = False;
}


/* ARGSUSED */
#ifndef   _NO_PROTO
static void Push(Widget    w,
                 XEvent   *event, 
		 String   *params,
		 Cardinal *num_params)
#else  /* _NO_PROTO */
static void Push(w, event, params, num_params)
	Widget    w;
	XEvent   *event;
	String   *params;
	Cardinal *num_params;
#endif /* _NO_PROTO */
{
	if (*num_params)
		push(atof(params[0]));
	last_was_binary = False;
}


/* ARGSUSED */
#ifndef   _NO_PROTO
static void Pop(Widget    w,
                XEvent   *event, 
		String   *params,
		Cardinal *num_params)
#else  /* _NO_PROTO */
static void Pop(w, event, params, num_params)
	Widget    w;
	XEvent   *event;
	String   *params;
	Cardinal *num_params;
#endif /* _NO_PROTO */
{
	if (sp > 0)
		sp--;
	else
		set_error(preferences.pr_under_string);
	last_was_binary = False;
}


/* ARGSUSED */
#ifndef   _NO_PROTO
static void Equals(Widget    w,
                   XEvent   *event, 
		   String   *params,
		   Cardinal *num_params)
#else  /* _NO_PROTO */
static void Equals(w, event, params, num_params)
	Widget    w;
	XEvent   *event;
	String   *params;
	Cardinal *num_params;
#endif /* _NO_PROTO */
{
	binary_op(OP_EQ);
}


/* ARGSUSED */
#ifndef   _NO_PROTO
static void Add(Widget    w,
                XEvent   *event, 
		String   *params,
		Cardinal *num_params)
#else  /* _NO_PROTO */
static void Add(w, event, params, num_params)
	Widget    w;
	XEvent   *event;
	String   *params;
	Cardinal *num_params;
#endif /* _NO_PROTO */
{
	binary_op(OP_ADD);
}


/* ARGSUSED */
#ifndef   _NO_PROTO
static void Subtract(Widget    w,
                     XEvent   *event, 
		     String   *params,
		     Cardinal *num_params)
#else  /* _NO_PROTO */
static void Subtract(w, event, params, num_params)
	Widget    w;
	XEvent   *event;
	String   *params;
	Cardinal *num_params;
#endif /* _NO_PROTO */
{
	binary_op(OP_SUB);
}


/* ARGSUSED */
#ifndef   _NO_PROTO
static void Multiply(Widget    w,
                     XEvent   *event, 
		     String   *params,
		     Cardinal *num_params)
#else  /* _NO_PROTO */
static void Multiply(w, event, params, num_params)
	Widget    w;
	XEvent   *event;
	String   *params;
	Cardinal *num_params;
#endif /* _NO_PROTO */
{
	binary_op(OP_MUL);
}


/* ARGSUSED */
#ifndef   _NO_PROTO
static void Divide(Widget    w,
                   XEvent   *event, 
		   String   *params,
		   Cardinal *num_params)
#else  /* _NO_PROTO */
static void Divide(w, event, params, num_params)
	Widget    w;
	XEvent   *event;
	String   *params;
	Cardinal *num_params;
#endif /* _NO_PROTO */
{
	binary_op(OP_DIV);
}


/* ARGSUSED */
#ifndef   _NO_PROTO
static void Sin(Widget    w,
                XEvent   *event, 
		String   *params,
		Cardinal *num_params)
#else  /* _NO_PROTO */
static void Sin(w, event, params, num_params)
	Widget    w;
	XEvent   *event;
	String   *params;
	Cardinal *num_params;
#endif /* _NO_PROTO */
{
	unary_op(OP_SIN);
}


/* ARGSUSED */
#ifndef   _NO_PROTO
static void Cos(Widget    w,
                XEvent   *event, 
		String   *params,
		Cardinal *num_params)
#else  /* _NO_PROTO */
static void Cos(w, event, params, num_params)
	Widget    w;
	XEvent   *event;
	String   *params;
	Cardinal *num_params;
#endif /* _NO_PROTO */
{
	unary_op(OP_COS);
}


/* ARGSUSED */
#ifndef   _NO_PROTO
static void Tan(Widget    w,
                XEvent   *event, 
		String   *params,
		Cardinal *num_params)
#else  /* _NO_PROTO */
static void Tan(w, event, params, num_params)
	Widget    w;
	XEvent   *event;
	String   *params;
	Cardinal *num_params;
#endif /* _NO_PROTO */
{
	unary_op(OP_TAN);
}


/* ARGSUSED */
#ifndef   _NO_PROTO
static void Sinh(Widget    w,
                 XEvent   *event, 
		 String   *params,
		 Cardinal *num_params)
#else  /* _NO_PROTO */
static void Sinh(w, event, params, num_params)
	Widget    w;
	XEvent   *event;
	String   *params;
	Cardinal *num_params;
#endif /* _NO_PROTO */
{
	unary_op(OP_SINH);
}


/* ARGSUSED */
#ifndef   _NO_PROTO
static void Cosh(Widget    w,
                 XEvent   *event, 
		 String   *params,
		 Cardinal *num_params)
#else  /* _NO_PROTO */
static void Cosh(w, event, params, num_params)
	Widget    w;
	XEvent   *event;
	String   *params;
	Cardinal *num_params;
#endif /* _NO_PROTO */
{
	unary_op(OP_COSH);
}


/* ARGSUSED */
#ifndef   _NO_PROTO
static void Tanh(Widget    w,
                 XEvent   *event, 
		 String   *params,
		 Cardinal *num_params)
#else  /* _NO_PROTO */
static void Tanh(w, event, params, num_params)
	Widget    w;
	XEvent   *event;
	String   *params;
	Cardinal *num_params;
#endif /* _NO_PROTO */
{
	unary_op(OP_TANH);
}


/* ARGSUSED */
#ifndef   _NO_PROTO
static void Sqrt(Widget    w,
                 XEvent   *event, 
		 String   *params,
		 Cardinal *num_params)
#else  /* _NO_PROTO */
static void Sqrt(w, event, params, num_params)
	Widget    w;
	XEvent   *event;
	String   *params;
	Cardinal *num_params;
#endif /* _NO_PROTO */
{
	unary_op(OP_SQR);
}


/* ARGSUSED */
#ifndef   _NO_PROTO
static void Factorial(Widget    w,
                      XEvent   *event, 
		      String   *params,
		      Cardinal *num_params)
#else  /* _NO_PROTO */
static void Factorial(w, event, params, num_params)
	Widget    w;
	XEvent   *event;
	String   *params;
	Cardinal *num_params;
#endif /* _NO_PROTO */
{
	unary_op(OP_FAC);
}


/* ARGSUSED */
#ifndef   _NO_PROTO
static void Reciprocal(Widget    w,
                       XEvent   *event, 
		       String   *params,
		       Cardinal *num_params)
#else  /* _NO_PROTO */
static void Reciprocal(w, event, params, num_params)
	Widget    w;
	XEvent   *event;
	String   *params;
	Cardinal *num_params;
#endif /* _NO_PROTO */
{
	unary_op(OP_REC);
}


/* ARGSUSED */
#ifndef   _NO_PROTO
static void Log10(Widget    w,
                  XEvent   *event, 
		  String   *params,
		  Cardinal *num_params)
#else  /* _NO_PROTO */
static void Log10(w, event, params, num_params)
	Widget    w;
	XEvent   *event;
	String   *params;
	Cardinal *num_params;
#endif /* _NO_PROTO */
{
	unary_op(OP_LOG);
}


/* ARGSUSED */
#ifndef   _NO_PROTO
static void Ln(Widget    w,
               XEvent   *event, 
	       String   *params,
	       Cardinal *num_params)
#else  /* _NO_PROTO */
static void Ln(w, event, params, num_params)
	Widget    w;
	XEvent   *event;
	String   *params;
	Cardinal *num_params;
#endif /* _NO_PROTO */
{
	unary_op(OP_LN);
}


/* ARGSUSED */
#ifndef   _NO_PROTO
static void Exp(Widget    w,
                XEvent   *event, 
		String   *params,
		Cardinal *num_params)
#else  /* _NO_PROTO */
static void Exp(w, event, params, num_params)
	Widget    w;
	XEvent   *event;
	String   *params;
	Cardinal *num_params;
#endif /* _NO_PROTO */
{
	unary_op(OP_EXP);
}


/* ARGSUSED */
#ifndef   _NO_PROTO
static void ChangeSign(Widget    w,
                       XEvent   *event, 
		       String   *params,
		       Cardinal *num_params)
#else  /* _NO_PROTO */
static void ChangeSign(w, event, params, num_params)
	Widget    w;
	XEvent   *event;
	String   *params;
	Cardinal *num_params;
#endif /* _NO_PROTO */
{
	unary_op(OP_SGN);
}


/* ARGSUSED */
#ifndef   _NO_PROTO
static void MemAdd(Widget    w,
                   XEvent   *event, 
		   String   *params,
		   Cardinal *num_params)
#else  /* _NO_PROTO */
static void MemAdd(w, event, params, num_params)
	Widget    w;
	XEvent   *event;
	String   *params;
	Cardinal *num_params;
#endif /* _NO_PROTO */
{
	unary_op(OP_MP);
}


/* ARGSUSED */
#ifndef   _NO_PROTO
static void MemSubtract(Widget    w,
                        XEvent   *event, 
		        String   *params,
		        Cardinal *num_params)
#else  /* _NO_PROTO */
static void MemSubtract(w, event, params, num_params)
	Widget    w;
	XEvent   *event;
	String   *params;
	Cardinal *num_params;
#endif /* _NO_PROTO */
{
	unary_op(OP_MM);
}


/* ARGSUSED */
#ifndef   _NO_PROTO
static void MemStore(Widget    w,
                     XEvent   *event, 
		     String   *params,
		     Cardinal *num_params)
#else  /* _NO_PROTO */
static void MemStore(w, event, params, num_params)
	Widget    w;
	XEvent   *event;
	String   *params;
	Cardinal *num_params;
#endif /* _NO_PROTO */
{
	unary_op(OP_STO);
}


/* ARGSUSED */
#ifndef   _NO_PROTO
static void MemRecall(Widget    w,
                      XEvent   *event, 
		      String   *params,
		      Cardinal *num_params)
#else  /* _NO_PROTO */
static void MemRecall(w, event, params, num_params)
	Widget    w;
	XEvent   *event;
	String   *params;
	Cardinal *num_params;
#endif /* _NO_PROTO */
{
	unary_op(OP_RCL);
}


/* ARGSUSED */
#ifndef   _NO_PROTO
static void LeftShift(Widget    w,
                      XEvent   *event, 
		      String   *params,
		      Cardinal *num_params)
#else  /* _NO_PROTO */
static void LeftShift(w, event, params, num_params)
	Widget    w;
	XEvent   *event;
	String   *params;
	Cardinal *num_params;
#endif /* _NO_PROTO */
{
	binary_op(OP_LSH);
}


/* ARGSUSED */
#ifndef   _NO_PROTO
static void RightShift(Widget    w,
                       XEvent   *event, 
		       String   *params,
		       Cardinal *num_params)
#else  /* _NO_PROTO */
static void RightShift(w, event, params, num_params)
	Widget    w;
	XEvent   *event;
	String   *params;
	Cardinal *num_params;
#endif /* _NO_PROTO */
{
	binary_op(OP_RSH);
}


/* ARGSUSED */
#ifndef   _NO_PROTO
static void And(Widget    w,
                XEvent   *event, 
		String   *params,
		Cardinal *num_params)
#else  /* _NO_PROTO */
static void And(w, event, params, num_params)
	Widget    w;
	XEvent   *event;
	String   *params;
	Cardinal *num_params;
#endif /* _NO_PROTO */
{
	binary_op(OP_AND);
}


/* ARGSUSED */
#ifndef   _NO_PROTO
static void Or(Widget    w,
               XEvent   *event, 
	       String   *params,
	       Cardinal *num_params)
#else  /* _NO_PROTO */
static void Or(w, event, params, num_params)
	Widget    w;
	XEvent   *event;
	String   *params;
	Cardinal *num_params;
#endif /* _NO_PROTO */
{
	binary_op(OP_OR);
}


/* ARGSUSED */
#ifndef   _NO_PROTO
static void Xor(Widget    w,
                XEvent   *event, 
		String   *params,
		Cardinal *num_params)
#else  /* _NO_PROTO */
static void Xor(w, event, params, num_params)
	Widget    w;
	XEvent   *event;
	String   *params;
	Cardinal *num_params;
#endif /* _NO_PROTO */
{
	binary_op(OP_XOR);
}


/* ARGSUSED */
#ifndef   _NO_PROTO
static void RaisePower(Widget    w,
                       XEvent   *event, 
		       String   *params,
		       Cardinal *num_params)
#else  /* _NO_PROTO */
static void RaisePower(w, event, params, num_params)
	Widget    w;
	XEvent   *event;
	String   *params;
	Cardinal *num_params;
#endif /* _NO_PROTO */
{
	binary_op(OP_POW);
}


/* ARGSUSED */
#ifndef   _NO_PROTO
static void OpenParenthesis(Widget    w,
                            XEvent   *event, 
			    String   *params,
			    Cardinal *num_params)
#else  /* _NO_PROTO */
static void OpenParenthesis(w, event, params, num_params)
	Widget    w;
	XEvent   *event;
	String   *params;
	Cardinal *num_params;
#endif /* _NO_PROTO */
{
	unary_op(OP_BRA);
}


/* ARGSUSED */
#ifndef   _NO_PROTO
static void CloseParenthesis(Widget    w,
                             XEvent   *event, 
			     String   *params,
			     Cardinal *num_params)
#else  /* _NO_PROTO */
static void CloseParenthesis(w, event, params, num_params)
	Widget    w;
	XEvent   *event;
	String   *params;
	Cardinal *num_params;
#endif /* _NO_PROTO */
{
	binary_op(OP_KET);
}


/* ARGSUSED */
#ifndef   _NO_PROTO
static void Degrees(Widget    w,
                    XEvent   *event, 
		    String   *params,
		    Cardinal *num_params)
#else  /* _NO_PROTO */
static void Degrees(w, event, params, num_params)
	Widget    w;
	XEvent   *event;
	String   *params;
	Cardinal *num_params;
#endif /* _NO_PROTO */
{
	set_units(DRG_DEG);
}


/* ARGSUSED */
#ifndef   _NO_PROTO
static void Radians(Widget    w,
                    XEvent   *event, 
		    String   *params,
		    Cardinal *num_params)
#else  /* _NO_PROTO */
static void Radians(w, event, params, num_params)
	Widget    w;
	XEvent   *event;
	String   *params;
	Cardinal *num_params;
#endif /* _NO_PROTO */
{
	set_units(DRG_RAD);
}


/* ARGSUSED */
#ifndef   _NO_PROTO
static void Gradient(Widget    w,
                     XEvent   *event, 
		     String   *params,
		     Cardinal *num_params)
#else  /* _NO_PROTO */
static void Gradient(w, event, params, num_params)
	Widget    w;
	XEvent   *event;
	String   *params;
	Cardinal *num_params;
#endif /* _NO_PROTO */
{
	set_units(DRG_GRAD);
}


/* This routine is provided for debugging purposes */
#ifndef   _NO_PROTO
static void Stack(void)
#else  /* _NO_PROTO */
static void Stack()
#endif /* _NO_PROTO */
{
	int i;

	(void) printf("Stack:\n");

	for (i = 0; i < sp; i++) {
		(void) printf("  %g\n", stack[i]);
	}

	if (op_sp) {
		(void) printf("Op stack:\n");

		for (i = 0; i < op_sp; i++) {
			(void) printf("  %d\n", op_stack[i]);
		}
	}
}


/*
** The Actions Table:
*/
static XtActionsRec calc_actions[] = {
	{ "Digit",              Digit },
	{ "Delete",             Delete },
	{ "Equals",             Equals },
	{ "Add",                Add },
	{ "Subtract",           Subtract },
	{ "Multiply",           Multiply },
	{ "Divide",             Divide },
	{ "Sin",                Sin },
	{ "Cos",                Cos },
	{ "Tan",                Tan },
	{ "Log10",              Log10 },
	{ "Ln",                 Ln },
	{ "Sqrt",               Sqrt },
	{ "RaisePower",         RaisePower },
	{ "Exp",                Exp },
	{ "Reciprocal",         Reciprocal },
	{ "Factorial",          Factorial },
	{ "And",                And },
	{ "Or",                 Or },
	{ "Xor",                Xor },
	{ "LeftShift",          LeftShift },
	{ "RightShift",         RightShift },
	{ "ClearAll",           ClearAll },
	{ "ClearEntry",         ClearEntry },
	{ "ChangeSign",         ChangeSign },
	{ "OpenParenthesis",    OpenParenthesis },
	{ "CloseParenthesis",   CloseParenthesis },
	{ "Base",               Base },
	{ "Error",              Error },
	{ "EnterNumber",        EnterNumber },
	{ "Push",               Push },
	{ "Pop",                Pop },
	{ "Dup",                Dup },
	{ "Exch",               Exch },
	{ "Roll",               Roll },
	{ "Inverse",            Inverse },
	{ "Hyper",              Hyper },
	{ "Degrees",            Degrees },
	{ "Radians",            Radians },
	{ "Gradient",           Gradient },
	{ "Stack",              Stack },
	{ "MemAdd",             MemAdd },
	{ "MemSubtract",        MemSubtract },
	{ "MemStore",           MemStore },
	{ "MemRecall",          MemRecall },
};

/*
** The application resources for the calculator.
*/
static XtResource calc_resources[] = {
      {
	 "errorString", XmCXmString, XmRString,
	 sizeof(XmString), XtOffset(Pref_p, pr_error_string),
	 XmRString,
	 "Error"
      },
      {
	 "overString", XmCXmString, XmRString,
	 sizeof(XmString), XtOffset(Pref_p, pr_over_string),
	 XmRString,
	 "Stack overflow"
      },
      {
	 "underString", XmCXmString, XmRString,
	 sizeof(XmString), XtOffset(Pref_p, pr_under_string),
	 XmRString,
	 "Stack underflow"
      },
      {
	 "infinityString", XmCXmString, XmRString,
	 sizeof(XmString), XtOffset(Pref_p, pr_infinity_string),
	 XmRString,
	 "Infinity"
      },
      {
	 "displayFormat", XmCXmString, XmRString,
	 sizeof(XmString), XtOffset(Pref_p, pr_display_format),
	 XmRString,
	 "%20g"
      },
      {
	 "stringFormat", XmCXmString, XmRString,
	 sizeof(XmString), XtOffset(Pref_p, pr_string_format),
	 XmRString,
	 "%20s"
      },
      {
	 "reversePolish", XmCBoolean, XmRBoolean,
	 sizeof(Boolean), XtOffset(Pref_p, pr_reverse_polish),
	 XmRImmediate,
	 (char *)False
      },
      {
	 "showPendingOp", XmCBoolean, XmRBoolean,
	 sizeof(Boolean), XtOffset(Pref_p, pr_show_pending_op),
	 XmRImmediate,
	 (char *)True
      }
};


/*
** The main program:
*/
#ifndef   _NO_PROTO
int main(int argc, char **argv)
#else  /* _NO_PROTO */
int main(argc,argv)
	int    argc;
	char **argv;
#endif /* _NO_PROTO */
{
	XtSetLanguageProc((XtAppContext) 0, (XtLanguageProc) 0, (XtPointer) 0) ;

	XtToolkitInitialize();

	app_context = XtCreateApplicationContext();
	display     = XtOpenDisplay(app_context, NULL, argv[0], "MCalc", NULL, 0, &argc, argv);

	if (!display) {
		(void) printf("%s: Can't open display\n", argv[0]);

		exit(1);
	}

	XtAppAddActions(app_context, calc_actions, XtNumber(calc_actions));

	create_calc_shell( display, argv[0], argc, argv );

	XtRealizeWidget(calc_shell);
	XtGetApplicationResources(calc_shell, &preferences, calc_resources, XtNumber(calc_resources), (ArgList)0, 0);

	ClearAll((Widget) 0, (XEvent *) 0, (String *) 0, (Cardinal *) 0);
	XtAppMainLoop(app_context);

	/* NOTREACHED */

	return 0 ;
}
