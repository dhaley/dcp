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
** sccsid = "@(#)helpGuru/libgen/CFile.h	1.1" -- 95/12/13
*/

/*
** CFile:
**
** A class for managing files.
**
** Jeremy Huxtable 1993
*/

#ifndef _H_CFile
#define _H_CFile

#include <stdio.h>

class CFile {
public:
	enum FileMode {
		fileRead = 0,
		fileWrite
	};

	CFile() { }
	virtual ~CFile() { }

	void Open(const char *name = 0, FileMode mode = fileRead) { itsMode = mode; }
	virtual void Close() { }
	virtual void Flush() { }

	virtual int Read(char *buf, int length) = 0;
	virtual int Write(const char *buf, int length) = 0;

private:
	FileMode itsMode;
};

class CDiskFile : public CFile {
public:
	CDiskFile();
	~CDiskFile();

	void Open(const char *name, FileMode mode = fileRead);
	void Open(FILE *aFile, FileMode mode = fileRead);
	virtual void Close();
	virtual void Flush();

	virtual int Read(char *buf, int length);
	virtual int Write(const char *buf, int length);

private:
	FILE *itsFile;	
};

#endif
