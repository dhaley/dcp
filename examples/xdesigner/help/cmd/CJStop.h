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

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "CTopic.h"
#include "CJStringFile.h"

/*
** A subclass of the CJStringFile which discards its input 
** depending on its state; designed to allow the output stream to
** control whether it is printing or skipping text.  Will only
** print text after the first whitespace it receives post-creation.
** Also keeps a count of how many characters (not including whitespace
** or characters written when it's been in stopped mode) it has had
**
*/
class CJStoppableStringFile : public CJStringFile {
public:
    CJStoppableStringFile() ;

    int GetCharsWritten() ;

    void WriteIf( Boolean whether ) ;

    int Write( const char *buf, int length ); 

private:
    Boolean writeIf ;
    Boolean seenNonWhitespace ;
    int charsWritten ;
} ;
