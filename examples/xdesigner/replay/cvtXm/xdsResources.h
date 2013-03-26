#ifndef _RESOURCES_H
#define _RESOURCES_H 1

#include <X11/StringDefs.h>
#include <X11/Intrinsic.h>

#include <xdsObject.h>


#ifndef XDSOBJECTCREATOR
YOU_SHOULD_SET_XDSOBJECT_IN_THE_MAKEFILE
#endif

static void xdsObjectGetValues();
static void xdsObjectSetValues();

typedef struct {
	int       type;
	XtPointer setValues;
	XtPointer getValues;
	XtPointer engineSetValues;
	XtPointer engineGetValues;
	/*-----------------------*/
} data_t;

static data_t data;

static
XtResource resources[] = {
	{
		XDSNtype, XDSCType, XtRInt, sizeof(int),
		XtOffsetOf(data_t,type), XtRImmediate,
		(XtPointer)VCR_WIDGET_OBJECT
	},
	{
		XDSNsetValues, XtCCallback, XtRPointer, sizeof(XtPointer),
		XtOffsetOf(data_t,setValues), XtRImmediate,
		(XtPointer)xdsObjectSetValues
	},
	{
		XDSNgetValues, XtCCallback, XtRPointer, sizeof(XtPointer),
		XtOffsetOf(data_t,getValues), XtRImmediate,
		(XtPointer)xdsObjectGetValues
	},
	{
		XDSNxdsSetValues, XtCCallback, XtRPointer, sizeof(XtPointer),
		XtOffsetOf(data_t,engineSetValues), XtRPointer,
		(XtPointer)0
	},
	{
		XDSNxdsGetValues, XtCCallback, XtRPointer, sizeof(XtPointer),
		XtOffsetOf(data_t,engineGetValues), XtRPointer,
		(XtPointer)0
	}
};



#endif
