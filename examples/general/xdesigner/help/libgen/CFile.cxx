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

#if !defined(lint) && !defined(NOSCCS)
static char *sccsid = {"@(#)helpGuru/libgen/CFile.cxx	1.1"} ; /* 95/12/13 */
#endif /* lint && NOSCCS */

/*
** CFile:
**
** A class for managing files.
**
** Jeremy Huxtable 1993
*/

#include "CFile.h"

CDiskFile::CDiskFile()
{
	itsFile = 0;
}

CDiskFile::~CDiskFile()
{
	Close();
}

void
CDiskFile::Open(const char *name, FileMode aMode)
{
	itsFile = fopen(name, aMode == fileRead ? "r" : "w");
}

void
CDiskFile::Open(FILE *aFile, FileMode aMode)
{
	itsFile = aFile;
}

void
CDiskFile::Close()
{
	if (itsFile)
		fclose(itsFile);
	itsFile = 0;
}

void
CDiskFile::Flush()
{
	if (itsFile)
		fflush(itsFile);
}

int
CDiskFile::Read(char *buf, int length)
{
	return fread(buf, 1, length, itsFile);
}

int
CDiskFile::Write(const char *buf, int length)
{
	return fwrite(buf, 1, length, itsFile);
}
