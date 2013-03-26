/*
** A.J.Fountain,
** Imperial Software Technology (IST),
** Kings Court,
** 185 Kings Road,
** Reading, 
** Berkshire,
** United Kingdom RG1 4EX.
**
** Telephone: +44 189 587055
** Fax:       +44 189 589005
** Email:     support@ist.co.uk
** Web:       http://www.ist.co.uk
*/

/*
** sccsid[] = {"@(#)dist/release/examples/demos/greptool/maindialog.c	1.3"} -- 01/08/24
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <X11/Intrinsic.h>
#include <X11/Shell.h>
#include <Xm/Xm.h>
#include <Xm/Command.h>
#include <Xm/Form.h>
#include <Xm/LabelG.h>
#include <Xm/RowColumn.h>
#include <Xm/Text.h>
#include <Xm/ToggleB.h>

#include "greptool.h" /* Defines ccdata_t, rcdata_t */

extern Widget errorshell; /* Error dialog widgets needed to */
extern Widget errorform;  /* initialise client data structure */
extern Widget errortext;  /* for rungrep callback */

#include "maindialog.xc" /* Generated dialog creation function for main dialog */

