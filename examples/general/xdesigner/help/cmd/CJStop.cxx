/* X-Designer
** ( c ) 1992, 1993, 1994, 1995, 1996
** Imperial Software Technology ( IST ),
** 95 London Street,
** Reading,
** Berkshire,
** United Kingdom RG1 4QA.
**
** Telephone: +44 1734 587055
** Fax:       +44 1734 589005
** Email:     support@ist.co.uk
*/

#if !defined( lint ) && !defined( NOSCCS )
static char *sccsid = {"@(#)CJStop.cxx	1.2"} ; /* 96/12/04 */
#endif /* lint && NOSCCS */

#include "CJStop.h"

/*
** A subclass of the CJStringFile which discards its input 
** depending on its state; designed to allow the output stream to
** control whether it is printing or skipping text.  Will only
** print text after the first whitespace it receives post-creation.
** Also keeps a count of how many characters (not including whitespace
** or characters written when it's been in stopped mode) it has had
**
*/
    CJStoppableStringFile::CJStoppableStringFile() 
	: CJStringFile() 
    {
	writeIf = True ;
	seenNonWhitespace = False ;
	charsWritten = 0 ;
    }
	
    int CJStoppableStringFile:: GetCharsWritten() {
	return charsWritten ;
    }

    void CJStoppableStringFile::WriteIf( Boolean whether ) 
    { writeIf = whether ; } ;

    int CJStoppableStringFile::Write( const char *buf, int length ) {

	if ( writeIf ) {

	    if ( !seenNonWhitespace )  {

		int i = 0 ;
		int thisCharLen = 1 ;

		for ( i=0 ; i<length ; i += thisCharLen )  {
		    thisCharLen = mblen( buf + i, length - i ) ;
		    seenNonWhitespace = !((thisCharLen == 1)
					  && isspace( buf[i] )) ;
		}
	    }

	    charsWritten += length ;

	    if ( seenNonWhitespace ) {
		return CJStringFile::Write( buf, length ) ;
	    }

	}
	return length ;
    }

