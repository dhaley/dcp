#include <X11/StringDefs.h>
#include <X11/Intrinsic.h>

void
RegisterWidgets()
{
	extern Boolean xdsRegister();

	extern int templateNameToXY();
	extern int templateXYToName();

	(void) xdsRegister( "XintEditTable", templateNameToXY, templateXYToName);
}
