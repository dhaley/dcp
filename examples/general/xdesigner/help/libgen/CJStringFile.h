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
** sccsid = "@(#)helpGuru/libgen/CJStringFile.h	1.1" -- 95/12/13
*/

/*
** CJStringFile:
**
** A 'file' which exists as a CJString in memory.
**
** Jeremy Huxtable 1994
*/

#ifndef _H_CJStringFile
#define _H_CJStringFile

#include "CFile.h"

class CJString;

class CJStringFile : public CFile {
public:
	CJStringFile();
	~CJStringFile();

	virtual void Open(CJString *aString, FileMode mode = fileRead);
	virtual void Close();
	virtual void Flush();

	virtual int Read(char *buf, int length);
	virtual int Write(const char *buf, int length);

private:
	CJString *itsString;
	char *buffer;
	int bufLen, bufSize, position, mode;
};

#endif
