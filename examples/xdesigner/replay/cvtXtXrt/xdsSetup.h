#ifndef _XDSSETUP_H
#define _XDSSETUP_H

/* this is a suggested boilerplate. Add routines etc of your own */

static
void
xdsSetupObject( getfun, appshell)
	void_f getfun;
	Widget appshell;
{
	RegisterWidgets();
}

/* since the real routine is standard and static to this module */
void
xdsUserSetValues( argv, argc)
	ArgList argv;
	Cardinal argc;
{
	xdsObjectSetValues( argv, argc);
}

static
void_f
xdsUserGetValuesProc()
{
	Arg args[2];
	Cardinal ac = 0;
	void_f gf;

	XtSetArg( args[ac], XDSNxdsGetValues, &gf); ac++;
	xdsObjectGetValues( args, ac);

	if (!gf)
		return (void_f)0;

	return gf;
}

XtPointer
xdsGetAnyFunction( name)
	char * name;
{
	void_f gf;
	Arg args[2];
	Cardinal ac = 0;
	XtPointer xp = (XtPointer)0;

	if ((gf = xdsUserGetValuesProc()) == (void_f)0)
		return (XtPointer)0;

	XtSetArg( args[ac], name, &xp); ac++;

	(*gf) (args, ac);

	return xp;
}

static
bool_f
xdsGetRegisterFunction()
{
	static bool_f bf = (bool_f)0;
	static Boolean bad = False;

	if (bad)
		return (bool_f)0;

	if (bf)
		return bf;

	bf = (bool_f) xdsGetAnyFunction(XDSNwidgetIntegrationFunction);

	if (!bf)
		goto badEnd;

	return bf;
badEnd:
	bad = True;
	return (bool_f)0;
}


static
bool_f
xdsGetIMRegisterFunction()
{
	static bool_f bf = (bool_f)0;
	static Boolean bad = False;

	if (bad)
		return (bool_f)0;

	if (bf)
		return bf;

	bf = (bool_f) xdsGetAnyFunction(XDSNinputMethodIntegrationFunction);

	if (!bf)
		goto badEnd;

	return bf;
badEnd:
	bad = True;
	return (bool_f)0;
}


Boolean
xdsRegister( classname, name2xy, xy2name)
	char * classname;
	int_f  name2xy;
	int_f  xy2name;
{
	bool_f bf = xdsGetRegisterFunction();

	if (!bf)
		return False;

	return (*bf)( classname, name2xy, xy2name);
}

Boolean
xdsIMRegister( classname, im_in_f, im_out_f)
	char * classname;
	str_f  im_in_f;
	bool_f im_out_f;
{
	bool_f bf = xdsGetIMRegisterFunction();

	if (!bf)
		return False;

	return (*bf)( classname, im_in_f, im_out_f);
}



#endif
