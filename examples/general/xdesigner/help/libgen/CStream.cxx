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
static char *sccsid = {"@(#)helpGuru/libgen/CStream.cxx	1.2"} ; /* 96/05/13 */
#endif /* lint && NOSCCS */

/*
** CStream:
**
** A class for managing a data stream to and from a file.
**
** Jeremy Huxtable 1993
*/

#include "CStream.h"

#include <string.h>
#include <stdlib.h>
#include <limits.h>


CStream::CStream(CFile *aFile, CFile::FileMode mode)
{
	itsFile = aFile;
	charsInBuf = BUFFER_MAX - 1 ;
	RefreshBuffer( BUFFER_MAX - 1 ) ;
}

CStream::~CStream()
{
	Close();
}

void
CStream::Open()
{
}

void
CStream::Close()
{
	itsFile->Close();
}

/**
** A method to read in /numChars/ elements from the file, assuming that the
** bottom /numChars/ elements have been used.
*/
void
CStream::RefreshBuffer( int numChars )
{

    if ( numChars > charsInBuf ) {
	fprintf( stderr, "Internal error: attempt to invalidate characters in stream buffer which don't exist.\n" ) ;
	return ;
    }

    if ( numChars <= 0 ) {
	return ;
    }

    if ( numChars >= BUFFER_MAX ) 
	numChars = BUFFER_MAX - 1 ;

    /* Move the top /charsInBuf/ - /numChars/ down; /top/ holds the position 
       of the last character in the buffer after the move */
    int top = 0 ;
    for ( int i = numChars; i < charsInBuf; i++, top++ )
	buffer[top] = buffer[i] ;

    /* Now read in as many characters as we can: */
    charsInBuf -= numChars ;
    charsInBuf += itsFile->Read( buffer + top, numChars ) ;

}

int
CStream::Read(char *buf, int length)
{
    int numRead ;

    // An optimisation for the simplest case, when we're at EOF.
    if ( charsInBuf == 0 )  {
	buf[0] = '\0' ;
	return 0 ;
    }

    if ( length <= charsInBuf )  {
	strncpy( buf, buffer, length ) ;
	numRead = length ;
	RefreshBuffer( length ) ;
    } else {
	strncpy( buf, buffer, charsInBuf ) ;
	numRead = charsInBuf + itsFile->Read( buf + charsInBuf, 
					      length - charsInBuf ) ;
	RefreshBuffer( charsInBuf ) ;
    }

    return numRead ;
}

int
CStream::Write(char *buf, int length)
{
	return itsFile->Write(buf, length);
}

void
CStream::PutChar(char *c)
{
	Write( c, strlen( c ) ) ;
}

char *
CStream::GetChar()
{
    char *result ;

    if ( charsInBuf == 0 )
	result = 0 ;
    else {

	int l = mblen( buffer, BUFFER_MAX ) ;
	
	if ( l != 0 )  {
	    result = new char[l+1] ;

	    int i = 0;
	    for ( i=0; i < l && buffer[i]; i++ )
		result[i] = buffer[i] ;
	    result[i] = '\0' ;

	    RefreshBuffer( l ) ;

	} else
	    result = 0 ;
    }
    
    return result ;
}

