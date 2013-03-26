#include <X11/StringDefs.h>
#include <X11/Intrinsic.h>

void
RegisterWidgets()
{
	extern Boolean xdsRegister();

	extern int intEditTableNameToXY();
	extern int intEditTableXYToName();

	(void) xdsRegister( "XintEditTable", intEditTableNameToXY, intEditTableXYToName);
}
