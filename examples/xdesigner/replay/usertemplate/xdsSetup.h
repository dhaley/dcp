/* this is a suggested boilerplate. Add routines etc of your own */

static
void
xdsSetupObject( getfun, appshell)
	void_f getfun;
	Widget appshell;
{
}

/* since the real routine is standard and static to this module */
void
vcrUserSetValues( argv, argc)
	ArgList argv;
	Cardinal argc;
{
	xdsObjectSetValues( argv, argc);
}


void_f
vcrUserGetValuesProc()
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

static
void_f
xdsUserProc( s)
	char * s;
{
	Arg args[2];
	Cardinal ac = 0;
	void_f gf = (void_f)0;
	void_f uf = (void_f)0;

	gf = vcrUserGetValuesProc();

	if (!gf)
		return (void_f)0;

	XtSetArg( args[ac], s, &uf); ac++;

	(*gf)( args, ac);

	if (!uf)
		return (void_f)0;

	return (void_f)uf;
}

Boolean
xdsUserRequestCommand( script)
	char * script;
{
	bool_f uf = (bool_f)0;

	if (!script && !*script)
		return False;
	uf = (bool_f)xdsUserProc( XDSNxdsRunUserScriptProc);
	if (!uf)
		return False;

	return (*uf) ( script);
}

Boolean
xdsUserExpression( shellwidget, expr)
	Widget shellwidget;
	char * expr;
{
	bool_f uf = (bool_f)0;

	if (!expr && !*expr)
		return False;
	uf = (bool_f)xdsUserProc( XDSNxdsEvalExpressionProc);
	if (!uf)
		return False;

	return (*uf) ( shellwidget, expr);
}
