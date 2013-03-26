
/*
** Generated Code
*/

class command_c: public xd_XmCommand_c {
public:
	virtual void create (Widget parent);
	Widget command;
	Widget textentry;
	Widget textresult;
protected:
	Widget slist;
	Widget hbar;
	Widget vbar;
	Widget list;
	Widget sellabel;
	Widget result_form;
	Widget result_label;
};

typedef command_c *command_p;

class rcform_c: public xd_XmForm_c {
public:
	virtual void create (Widget parent);
protected:
	Widget rcform;
	Widget buttonform;
	Widget col1form;
	Widget button_eq;
	Widget button_plus;
	Widget button7;
	Widget button4;
	Widget button1;
	Widget button0;
	Widget col2form;
	Widget button_left;
	Widget button_minus;
	Widget button8;
	Widget button5;
	Widget button2;
	Widget button_decimal;
	Widget col3form;
	Widget button_right;
	Widget button_times;
	Widget button9;
	Widget button6;
	Widget button3;
	Widget button_log10;
	Widget col4form;
	Widget button_pow;
	Widget button_div;
	Widget button_loge;
	Widget button_sin;
	Widget button_cos;
	Widget button_atan;
	Widget var_popup_form;
	Widget var_popup;
	Widget OptionLabel;
	Widget OptionButton;
	Widget var_menu;
	Widget button_e;
	Widget button_pi;
	Widget space_clear_form;
	Widget space_button;
	Widget eval_button;
	Widget clear_button;
};

typedef rcform_c *rcform_p;

class topshell_c: public xd_ApplicationShell_c {
public:
	virtual void create (Display *display, char *app_name, int app_argc, char **app_argv);
	topshell_c();
	virtual ~topshell_c();
	Widget topshell;
	command_p command;
protected:
	Widget topform;
	rcform_p rcform;
};

typedef topshell_c *topshell_p;


extern topshell_p topshell;


