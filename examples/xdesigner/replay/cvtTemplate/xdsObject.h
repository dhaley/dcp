/*
** A.J.Bartlett,
** Imperial Software Technology (IST),
** 95 London Street,
** Reading, 
** Berkshire,
** United Kingdom RG1 4QA.
**
** Telephone: +44 734 587055
** Fax:       +44 734 589005
** Email:     ab@ist.co.uk
*/

/*
** sccsid = "@(#)xdsObject.h	1.35" -- 98/05/13
*/

#ifndef    _VCR_OBJECT_H
#define    _VCR_OBJECT_H

#ifndef   _XPLAY_H
typedef void    (*void_f)() ;
typedef void_f  (*voidf_f)();
typedef int     (*int_f)();
typedef Boolean (*bool_f)();
typedef char *  (*str_f)();
typedef char *  (*ptr_f)();


#define XDSNcaptureFilename             "xdsCaptureFilename"
#define XDSNreplayInterval              "xdsReplayInterval"
#define XDSNreplayFilename              "xdsReplayFilename"
#define XDSNdirectory                   "xdsDirectory"
#endif /* _XPLAY_H */

#ifndef   NO_DEFS_REQUIRED
#include "xdsDefs.h"
#endif /* NO_DEFS_REQUIRED */


typedef Boolean (*boolean_f)();


/* General definitions */

#define XDSNtype                          "xdsType"
#define XDSNgetValues                     "xdsGetValues"
#define XDSNsetValues                     "xdsSetValues"
#define XDSNxdsGetValues                  "xdsEngineGetValues"
#define XDSNxdsSetValues                  "xdsEngineSetValues"

#define XDSNapplicationShell              "xdsApplicationShell"
#define XDSNignoreShellFunction           "xdsIgnoreShellFunction"
#define XDSNwidgetIntegrationFunction     "xdsWidgetIntegrationFunction"
#define XDSNinputMethodIntegrationFunction "xdsInputMethodIntegrationFunction"
#define XDSNcaptureJavaReady              "xdsCaptureJavaReady"
#define XDSNcaptureCoerceBulletinBoards   "xdsCaptureCoerceBulletinBoards"
#define XDSNcaptureForceDragAndDrop       "xdsCaptureForceDragAndDrop"
#define XDSNcaptureHandleClipWindow       "xdsCaptureHandleClipWindow"
#define XDSNcaptureSmartDims              "xdsCaptureSmartDims"
#define XDSNcaptureColormap               "xdsCaptureColormap"
#define XDSNcaptureUserWidgets            "xdsCaptureUserWidgets"
#define XDSNcaptureFoldLevel              "xdsCaptureFoldLevel"
#define XDSNcaptureMarginsOnly            "xdsCaptureMarginsOnly"
#define XDSNcaptureNoDimensions           "xdsCaptureNoDimensions"
#define XDSNcaptureIgnoreUserWidgetChildren  "xdsCaptureIgnoreUserWidgetChildren"
#define XDSNhelpDir                       "xdsHelpDir"
#define XDSNhelpViewer                    "xdsHelpViewer"
#define XDSNhelpDefaultUrl                "xdsHelpDefaultUrl"
#define XDSNxdsCloseDialogProc            "xdsCloseDialogProc"
#define XDSNvcrActionProc                 "xdsActionProc"
#define XDSNvcrLoadObjectProc             "xdsLoadObjectProc"
#define XDSNxdsRunUserScriptProc          "xdsRunUserScriptProc"
#define XDSNxdsEvalExpressionProc         "xdsEvalExpressionProc"
#define XDSNvcrRGBToColorObjectConverter  "xdsRGBToColorObjectConverter"
#define XDSNvcrSimpleStringFormat         "xdsSimpleStringFormat"
#define XDSNreplayTremble                 "xdsReplayTremble"


/* Dialog definitions */

#define XDSNcreateDialogFunction          "xdsDialogCreateDialog"
#define XDSNshellWidget                   "xdsDialogShellWidget"
#define XDSNshellInfoFunction             "xdsDialogShellInfoFunction"
#define XDSNpopupDialogFunction           "xdsDialogPopupDialog"
#define XDSNpopdownDialogFunction         "xdsDialogPopdownDialog"
#define XDSNerrorMessageFunction          "xdsDialogErrorMessageHandler"
#define XDSNoutputLogFunction             "xdsDialogoutputLogHandler"
#define XDSNendOfTapeFunction             "xdsDialogEndOfTape"
#define XDSNcaptureDesignFunction         "xdsDialogCaptureDesign"
#define XDSNcaptureIgnoreResources        "xdsCaptureIgnoreResources"
#define XDSNcapture64Resources            "xdsCapture64Resources"
#define XDSNcaptureForceDimensions        "xdsCaptureForceDimensions"
#define XDSNuserText                      "xdsUserText"
#define XDSNcaptureUseColorObjects      "xdsCaptureUseColorObjects"
#define XDSNcaptureUseFontObjects       "xdsCaptureUseFontObjects"
#define XDSNcaptureUseStringObjects     "xdsCaptureUseStringObjects"
#define XDSNcaptureUseObjects           "xdsCaptureUseObjects"
#define XDSNcaptureColorObjectsDisplaySensitive "xdsCaptureColorObjectsDisplaySensitive"


#define XDSNdialogCapturePage             "xdsDialogCapturePage"

#define XDSNdialogInsertMessage           "xdsDialogInsertMessage"
#define XDSNdialogRecordMessage           "xdsDialogRecordMessage"
#define XDSNdialogRewindMessage           "xdsDialogRewindMessage"
#define XDSNdialogStopMessage             "xdsDialogStopMessage"
#define XDSNdialogReplayMessage           "xdsDialogReplayMessage"
#define XDSNdialogStepMessage             "xdsDialogStepmessage"
#define XDSNdialogPauseMessage            "xdsDialogPauseMessage"
#define XDSNdialogInsertModeMessage       "xdsDialogInsertModeMessage"
#define XDSNdialogOverwriteModeMessage    "xdsDialogOverwriteModeMessage"
#define XDSNdialogEndAddMessage           "xdsDialogEndAddMessage"
#define XDSNdialogReadOnlyMessage         "xdsDialogReadOnlyMessage"

#define XDSNdialogNewFolderMessage        "xdsDialogNewFolderMessage"
#define XDSNdialogOpenSaveMessage         "xdsDialogOpenSaveMessage"
#define XDSNdialogExitSaveMessage         "xdsDialogExitSaveMessage"

#define XDSNdialogHelpViewerPreferences   "xdsDialogHelpViewerPreferences"
#define XDSNdialogRunCommentError         "xdsDialogRunCommentError"
#define XDSNdialogRunEmptyError           "xdsDialogRunEmptyError"
#define XDSNdialogNoHelpViewerError       "xdsDialogNoHelpViewerError"
#define XDSNdialogBadHelpViewerError      "xdsDialogBadHelpViewerError"
#define XDSNdialogObjectCreationError     "xdsDialogObjectCreationError"
#define XDSNdialogDirCreationError        "xdsDialogDirCreationError"
#define XDSNdialogReadOnlyError           "xdsDialogReadOnlyError"
#define XDSNdialogCannotWriteError        "xdsDialogCannotWriteError"
#define XDSNdialogCaptureError            "xdsDialogCaptureError"
#define XDSNdialogAutoStartMonitor        "xdsDialogAutoStartMonitor"

#define XDSNdialogNewFolderTitle          "xdsDialogNewFolderTitle"
#define XDSNdialogOpenFolderTitle         "xdsDialogOpenFolderTitle"
#define XDSNdialogReadFolderTitle         "xdsDialogReadFolderTitle"
#define XDSNdialogSaveFolderTitle         "xdsDialogSaveFolderTitle"
#define XDSNdialogExitFolderTitle         "xdsDialogExitFolderTitle"
#define XDSNdialogMonitorTitle            "xdsDialogMonitorTitle"
#define XDSNdialogCaptureTitle            "xdsDialogCaptureTitle"
#define XDSNdialogRecordTitle             "xdsDialogRecordTitle"
#define XDSNdialogErrorTitle              "xdsDialogErrorTitle"

#define XDSNhelpGetHelpProc               "xdsHelpGetHelpProc"
#define XDSNhelpKillHelpViewer            "xdsHelpKillHelpViewer"

#define VCR_LOAD_ACTION                   "vcrApiLoadScript"
#define VCR_UNLOAD_ACTION                 "vcrApiUnloadScript"
#define VCR_REWIND_ACTION                 "vcrApiRewind"
#define VCR_STOP_ACTION                   "vcrApiStop"
#define VCR_PAUSE_ACTION                  "vcrApiPause"
#define VCR_REPLAY_ACTION                 "vcrApiReplay"
#define VCR_RECORD_ACTION                 "vcrApiRecord"
#define VCR_STEP_ACTION                   "vcrApiSingleStep"
#define VCR_SETDELAY_ACTION               "vcrApiSetDelay"
#define VCR_SETINTERVAL_ACTION            "vcrApiSetInterval"
#define VCR_CAPTURE_ACTION                "vcrApiCaptureShell"
#define VCR_INSERT_TEXT_ACTION            "vcrApiInsertText"
#define VCR_INSERT_COMMENT_ACTION         "vcrApiInsertComment"
#define VCR_RUNTEXT_ACTION                "vcrApiRunText"
#define VCR_INSERT_ACTION               "vcrApiInsert"

/* Formatter definitions */

#define XDSNformatName                          "formatName"
#define XDSNformatPrelude                       "formatPrelude"
#define XDSNformatBeginPixmapDefinitions        "formatBeginPixmapDefinitions"
#define XDSNformatDefinePixmap                  "formatDefinePixmap"
#define XDSNformatEndPixmapDefinitions          "formatEndPixmapDefinitions"
#define XDSNformatBeginFontListDefinitions      "formatBeginFontListDefinitions"
#define XDSNformatDefineFontList                "formatDefineFontList"
#define XDSNformatEndFontListDefinitions        "formatEndFontListDefinitions"
#define XDSNformatBeginXmStringDefinitions      "formatBeginXmStringDefinitions"
#define XDSNformatDefineXmString                "formatDefineXmString"
#define XDSNformatEndXmStringDefinitions        "formatEndXmStringDefinitions"
#define XDSNformatBeginColorDefinitions         "formatBeginColorDefinitions"
#define XDSNformatDefineColor                   "formatDefineColor"
#define XDSNformatEndColorDefinitions           "formatEndColorDefinitions"
#define XDSNformatBeginMotifWidget              "formatBeginMotifWidget"
#define XDSNformatEndMotifWidget                "formatEndMotifWidget"
#define XDSNformatBeginMotifWidgetResources     "formatBeginMotifWidgetResources"
#define XDSNformatEndWidgetResources            "formatEndMotifWidgetResources"
#define XDSNformatBeginNonMotifWidget           "formatBeginNonMotifWidget"
#define XDSNformatEndNonMotifWidget             "formatEndNonMotifWidget"
#define XDSNformatBeginNonMotifWidgetResources  "formatBeginNonMotifWidgetResources"
#define XDSNformatEndNonMotifWidgetResources    "formatEndNonMotifWidgetResources"
#define XDSNformatBeginResources                "formatBeginResources"
#define XDSNformatMakeClass                     "formatMakeClass"
#define XDSNformatGlobalScope                   "formatGlobalScope"
#define XDSNformatInstantiateAs                 "formatInstantiateAs"
#define XDSNformatHandleResource                "formatHandleResource"
#define XDSNformatEndResources                  "formatEndResources"
#define XDSNformatHandleScrollbarsFirst         "formatHandleScrollbarsFirst"
#define XDSNformatScrollbarHandler              "formatScrollbarHandler"
#define XDSNformatBeginAttachments              "formatBeginAttachments"
#define XDSNformatEndAttachments                "formatEndAttachments"
#define XDSNformatBeginAttachmentGroup          "formatBeginAttachmentGroup"
#define XDSNformatHandleAttachment              "formatHandleAttachment"
#define XDSNformatEndAttachmentGroup            "formatEndAttachmentGroup"
#define XDSNformatOpenFakeMenuBar               "formatOpenFakeMenuBar"
#define XDSNformatCloseFakeMenuBar              "formatCloseFakeMenuBar"
#define XDSNformatFakeCascadeMenu               "formatFakeCascadeMenu"

#define XDSNformatBeginAbstractMotifWidget      "formatBeginAbstractMotifWidget"
#define XDSNformatBeginAbstractNonMotifWidget   "formatBeginAbstractNonMotifWidget"

#define XDSNxwdOnCapture                        "xwdOnCapture"


#define XDSNsetListErrorFunction        "xdsSetListErrorFunction"
#define XDSNlistFailureFunction         "xdsListFailureFunction"
#define XDSNgetXmListEntriesFunction    "xdsGetXmListEntriesFunction"
#define XDSNsetListItemFunction         "xdsSetListItemFunction"
#define XDSNisInListFunction            "xdsIsInListFunction"
#define XDSNxmStringToStringFunction    "xdsXmStringToStringFunction"

#define reengNONE                  0
#define reengXmDIALOG_TEMPLATE     1
#define reengXmMESSAGE_BOX         2
#define reengXmSELECTION_PROMPT    3
#define reengXmSELECTION_BOX       4
#define reengXmFILE_SELECTION_BOX  5
#define reengXmCOMMAND             6
#define reengXmMENU_BAR            7
#define reengXmPOPUP_MENU          8
#define reengXmPULLDOWN_MENU       9
#define reengXmOPTION_MENU        10
#define reengXmRADIO_BOX          11
#define reengXmROW_COLUMN         12
#define reengAPPLICATION_SHELL    13
#define reengXmFORM               14
#define reengXmFRAME              15
#define reengXmCASCADE_BUTTON     16
#define reengXmBULLETIN_BOARD     17
#define reengXmDRAWING_AREA       18
#define reengXmOTHER              19
#define reengXmMAINWINDOW         20
#define reengXmSCALE              21
#define reengTOPLEVEL_SHELL       22
#define reengXmPANEDWINDOW        23

#if       MOTIF21_WIDGETS
#define reengXmCOMBOBOX           24
#define reengXmNOTEBOOK           25
#define reengXmSIMPLESPINBOX      26
#define reengXmCONTAINER          27
#define reengXmICONGADGET         28
#define reengXmTOOLTIP            29

#define reengMAXTYPES             reengXmTOOLTIP
#else  /* MOTIF21_WIDGETS */
#define reengMAXTYPES             reengXmPANEDWINDOW
#endif /* MOTIF21_WIDGETS */


typedef struct {
	Boolean ismotif;
	Boolean needs_remap;
	Boolean hasscrollbars;
	Boolean isprimitive;
	Boolean iswidget;
	Boolean isjavaclass;
	Boolean hasglobalscope;
	Boolean parentismotif;
	Boolean preservedims;
	int     num_resources;
	Boolean isabstract;
} W_t;

typedef struct vcrXmData_s {
	int      shown;
	char *   label;
	int      size;
	void * 	 data;
	struct vcrXmData_s *   next;
} VcrXmData_t;

typedef struct i_flist_s {
	Boolean fontset;
	char * font;
	char * tag;
	struct i_flist_s * next;
} VcrXmFontList_t;

typedef char  VcrColor_t;

typedef struct i_xmstr_s {
	int    type;
	char * data;
	struct i_xmstr_s * next;
} VcrXmString_t;

#define STRING_SEPARATOR	1
#define STRING_DIRECTION	2
#define STRING_TAG		3
#define STRING_TEXT		4


/* Miscellaneous */

#define XDSCWidget      "Widget"
#define XDSCCallback    "Callback"
#define XDSCType        "Int"

#define VCR_ENGINE_OBJECT       (1 << 1)
#define VCR_DIALOG_OBJECT       (1 << 2)
#define VCR_FORMAT_OBJECT       (1 << 3)
#define VCR_USER_OBJECT         (1 << 4)
#define VCR_HELP_OBJECT         (1 << 5)
#define VCR_WIDGET_OBJECT       (1 << 6)

#define STRCHR   strchr
#define STRRCHR  strrchr
/* fix this */


/* list handling stuff */
#define LIST_BAD_WIDGET   1
#define LIST_NO_ITEMS     2
#define LIST_BAD_INSTANCE 3
#define LIST_EMPTY_LIST   4
#define LIST_ELEMENT_NOT_FOUND 5
#define LIST_OUT_OF_BOUNDS     6
#define LIST_NO_ELEMENTS       7
#define LIST_ELEMENT_NOT_IN_LIST 8


#endif /* _VCR_OBJECT_H */
