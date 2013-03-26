#include <X11/StringDefs.h>
#include <X11/Intrinsic.h>

extern int xrtGraphNameToXY();
extern int xrtGraphXYToName();
extern int xrt3dNameToXY();
extern int xrt3dXYToName();

void
RegisterWidgets()
{
	extern Boolean xdsRegister();

	(void) xdsRegister( "XtXrtGraph", xrtGraphNameToXY, xrtGraphXYToName);
	(void) xdsRegister( "XtXrt3d", xrt3dNameToXY, xrt3dXYToName);
}
