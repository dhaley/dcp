/*
From sun!marks on 11/10/88 

Here is your number:  300009

	--Mark Stein <marks@sun.com>
	  Portable ONC Engineering
	  Sun Microsystems, Inc.
*/

typedef int IntT;
typedef unsigned int UIntT;
typedef string StringT<>;
typedef int ErrorT;
typedef int BoolT;

struct FmRpcNiceErrorT {
	ErrorT code;
	StringT message;
};

/* This MUST be on 1 line for 4.0hack script to work. */
typedef IntT FmRpcCommandsT<150>;

struct FmRpcCommandsArgT {
	UIntT doc; 
	FmRpcCommandsT commands;
};

struct FmRpcNewDocArgT {
	StringT template;
};

struct FmRpcNewDocReturnT {
	UIntT doc;
	FmRpcNiceErrorT nice; 
};

struct FmRpcOpenDocArgT {
	StringT doc;
};

struct FmRpcOpenDocReturnT {
	UIntT doc;
	FmRpcNiceErrorT nice; 
};

struct FmRpcImportArgT {
	BoolT isCurrentDoc;
	UIntT doc;
	StringT file;
	BoolT isCopy;
};

struct FmRpcSaveDocArgT {
	UIntT doc;
	StringT file;
	IntT mode;
	BoolT isMakeBackup; 
	IntT saveOptions;
};

struct FmRpcSaveTextArgT {
	UIntT doc;
	StringT file;
	IntT mode;
	BoolT isMakeBackup; 
	IntT saveOptions;
};

struct FmRpcSaveMifArgT {
	UIntT doc;
	StringT file;
	IntT mode;
	BoolT isMakeBackup; 
	IntT saveOptions;
};

struct FmRpcGoToLinkArgT {
	UIntT doc;
	StringT dstDoc;
    StringT tag;
	BoolT isNewWindow;
};

struct FmRpcMessageArgT {
	StringT doc;
	StringT message;
};

struct FmRpcListExternalsArgT {
	UIntT doc;
	StringT file;
};

struct FmRpcEditInsetArgT {
	StringT insetFile;
	BoolT isIntern;
};

struct FmRpcUpdateInsetArgT {
	StringT insetFile;
};

program FM_RPC_PROG {
	version FM_RPC_VERS {
		FmRpcNiceErrorT FM_RPC_COMMANDS(FmRpcCommandsArgT) = 1;

		FmRpcNewDocReturnT FM_RPC_NEW_DOC(FmRpcNewDocArgT) = 100;
		FmRpcOpenDocReturnT FM_RPC_OPEN_DOC(FmRpcOpenDocArgT) = 101;
		FmRpcNiceErrorT FM_RPC_IMPORT(FmRpcImportArgT) = 102;
		FmRpcNiceErrorT FM_RPC_SAVE_DOC(FmRpcSaveDocArgT) = 103;
		FmRpcNiceErrorT FM_RPC_SAVE_TEXT(FmRpcSaveTextArgT) = 104;
		FmRpcNiceErrorT FM_RPC_SAVE_MIF(FmRpcSaveMifArgT) = 105;
		FmRpcNiceErrorT FM_RPC_LIST_EXTERNALS(FmRpcListExternalsArgT) = 106;
		/* XXX added without upping the version number ejk 900912 */
		FmRpcNiceErrorT FM_RPC_QUIT_APP(void) = 107;

		FmRpcNiceErrorT FM_RPC_GO_TO_LINK(FmRpcGoToLinkArgT) = 202;
		FmRpcNiceErrorT FM_RPC_MESSAGE(FmRpcMessageArgT) = 203;

		FmRpcNiceErrorT FM_RPC_LAUNCH(void) = 300;
		FmRpcNiceErrorT FM_RPC_EDIT_INSET(FmRpcEditInsetArgT) = 301;
		FmRpcNiceErrorT FM_RPC_UPDATE_INSET(FmRpcUpdateInsetArgT) = 302;
	} = 1;
} = 300009;
