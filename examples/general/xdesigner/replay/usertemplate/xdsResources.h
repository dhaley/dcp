#ifndef _RESOURCES_H
#define _RESOURCES_H 1

#include <X11/StringDefs.h>
#include <X11/Intrinsic.h>

#include "xdsObject.h"


#ifndef XDSOBJECTCREATOR
YOU_SHOULD_SET_XDSOBJECT_IN_THE_MAKEFILE
#endif

extern void exampleHalloWorld();
extern void exampleDoWhile();

static void xdsObjectGetValues();
static void xdsObjectSetValues();

typedef struct {
	int       type;
	XtPointer setValues;
	XtPointer getValues;
	XtPointer engineSetValues;
	XtPointer engineGetValues;
	/*-----------------------*/
	XtPointer HalloWorld;
	XtPointer repeat;
} data_t;

static data_t data;

static
XtResource resources[] = {
	{
		XDSNtype, XDSCType, XtRInt, sizeof(int),
		XtOffsetOf(data_t,type), XtRImmediate,
		(XtPointer)VCR_USER_OBJECT
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
	},
	/* ------------------- add your own here */
	{
		"HalloWorld", XtCCallback, XtRPointer, sizeof(XtPointer),
		XtOffsetOf(data_t,HalloWorld), XtRImmediate,
		(XtPointer)exampleHalloWorld
	},
	{
		"dowhile", XtCCallback, XtRPointer, sizeof(XtPointer),
		XtOffsetOf(data_t,repeat), XtRImmediate,
		(XtPointer)exampleDoWhile
	}
};



#endif
