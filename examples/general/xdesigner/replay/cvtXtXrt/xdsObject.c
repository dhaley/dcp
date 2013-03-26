/* standard template for interfacing a dialog with the VCR engine */
#include <stdio.h>
#include "xdsResources.h"

static
void
xdsObjectSetValues( argv, argc)
	ArgList  argv;
	Cardinal argc;
{
	XtSetSubvalues( (XtPointer)&data,
			(XtResourceList)resources,
				XtNumber(resources), argv, argc);
}

static
void
xdsObjectGetValues( argv, argc)
	ArgList  argv;
	Cardinal argc;
{
	XtGetSubvalues( (XtPointer)&data,
			(XtResourceList)resources,
		XtNumber(resources), argv, argc);
}

#include "xdsSetup.h"

void *
XDSOBJECTCREATOR( getfun)
	void_f getfun;
{
	Arg     args[10];
	int     ac;
	Widget  appshell = (Widget)0;
	int     type     = -1;

	/* check that there is really a VCR engine at the other end */
	ac = 0;
	XtSetArg( args[ac], XDSNtype, &type); ac++;

	(*getfun) ( args, ac);

	if (type != VCR_ENGINE_OBJECT) {
		void_f vcrgf = (void_f)0;
		Arg vargs[2];
		Cardinal vac = 0;
		XtSetArg( vargs[vac], XDSNxdsGetValues, &vcrgf); vac++;
		(*getfun) (vargs, vac);
		getfun = vcrgf;
	}

	/* get the appshell from the VCR engine */
	ac = 0;
	XtSetArg( args[ac], XDSNapplicationShell, &appshell); ac++;

	(*getfun) ( args, ac);

	if (!appshell) {
		(void) fprintf (stderr, "Dialog: No Application Shell\n");
		return False;
	}

	/* prepare your resources. Do not remove this! */

	XtGetApplicationResources( appshell, &data,
					resources, XtNumber(resources),
							(ArgList)0, (Cardinal) 0);

	ac = 0;
	XtSetArg( args[ac], XDSNxdsGetValues, (XtPointer) getfun); ac++;

	xdsObjectSetValues( args, ac);

	xdsSetupObject( getfun, appshell);

	/* you've shown me yours. I'll show you mine */
	return (void*) xdsObjectGetValues;
}
