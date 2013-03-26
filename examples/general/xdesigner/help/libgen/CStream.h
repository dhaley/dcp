/* X-Designer
** (c) 1992, 1993, 1994, 1995, 1996
** Imperial Software Technology (IST),
** 95 London Street,
** Reading,
** Berkshire,
** United Kingdom RG1 4QA.
**
** Telephone: +44 1734 587055
** Fax:       +44 1734 589005
** Email:     support@ist.co.uk
*/


/*
** sccsid = "@(#)helpGuru/libgen/CStream.h	1.4" -- 97/08/05
*/

/*
** CStream:
**
** A class for managing a data stream to and from a file.
**
** Jeremy Huxtable 1993
*/

#ifndef _H_CStream
#define _H_CStream

#include "CFile.h"

#include <stdlib.h>
#include <limits.h>

#if defined(__linux__) || defined(__ansidecl_lynx_h)
#undef  MB_LEN_MAX
#define MB_LEN_MAX  2
#endif

#ifdef    VMS
#if       __VMS_VER < 60200000
#undef  MB_LEN_MAX
#define MB_LEN_MAX  2
#endif /* __VMS_VER */
#endif /* VMS */

#define BUFFER_MAX MB_LEN_MAX

class CStream {
public:
	CStream(CFile *aFile, CFile::FileMode mode);
	~CStream();

	virtual void Open();
	virtual void Close();

	virtual int Read(char *buf, int length);
	virtual int Write(char *buf, int length);

	/* Multibyte character I/O */
	virtual void  PutChar( char *c ) ;
	virtual char *GetChar() ;

private:
	CFile *itsFile;
	char   buffer[BUFFER_MAX] ;
	int    charsInBuf ;

protected:
	virtual void RefreshBuffer( int numChars ) ;
};

#endif
