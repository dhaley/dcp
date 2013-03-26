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
static char *sccsid = {"@(#)helpGuru/libgen/CJStringFile.cxx	1.2"} ; /* 95/12/27 */
#endif /* lint && NOSCCS */

#include <string.h>
#include "CJStringFile.h"
#include "CJString.h"

CJStringFile::CJStringFile()
{
}

CJStringFile::~CJStringFile()
{
	if (mode == fileWrite) {
		Flush();
		delete buffer;
	}
}

void
CJStringFile::Open(CJString *aString, FileMode aMode)
{
	itsString = aString;
	position = 0;
	mode = aMode;
	if (mode == fileWrite) {
		bufSize = 1024;
		buffer = new char[bufSize];
		bufLen = 0;
	}
}

void
CJStringFile::Close()
{
	Flush();
}

void
CJStringFile::Flush()
{
	if (mode == fileWrite) {
		if (bufLen) {
			int pos = position-bufLen;
			itsString->ReplaceText(pos, pos, buffer, bufLen);
		}
		bufLen = 0;
	}
}

int
CJStringFile::Read(char *data, int length)
{
	int l = length;
	if (l > itsString->GetLength()-position)
		l = itsString->GetLength()-position;
	strncpy(data, itsString->GetData(), l);
	position += l;
	return l;
}

int
CJStringFile::Write(const char *data, int length)
{
    if ( bufSize - bufLen < length ) {
	// If our buffer's too small to hold this data...

	// Find an appropriate new size with a bit of space to spill
	// over into
	while ( bufSize - bufLen < length )
	    bufSize = bufSize * 2 ;

	// Create the new buffer
	char *newBuf = new char [bufSize] ;
	strncpy( newBuf, buffer, bufLen ) ;
	
	// And replace the old one with it
	delete buffer ;
	buffer = newBuf ;
    }

    // Add the new data on to the end of the buffer
    strncpy( buffer + bufLen, data, length ) ;
    bufLen += length ;
    position += length ;

    return length ;

#ifdef WHAT_ON_EARTH
    int l = length;

    while ( l > 0 ) {
	int bufLeft = bufSize-bufLen;
	int amount = (l > bufLeft) ? bufSize : l;
	strncpy(buffer+bufLen, data, amount);
	bufLen += amount;
	l -= amount;
	data += amount;
    }
    position += length;
    return length;
#endif
}

