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
static char *sccsid = {"@(#)helpGuru/cmd/CHTMLParser.cxx	1.23"} ; /* 99/08/12 */
#endif /* lint && NOSCCS */

/*
** CHTMLParser:
**
** A class for parsing HTML.
**
** Jeremy Huxtable 1995
** Giles Thomas 1995, 1996
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "CStream.h"
#include "CJString.h"
#include "CHTMLParser.h"

/*
** An array of the possible attributes for an image tag
*/
HTMLAttr imageAttrs[] = {
	{ "src" },
	{ "align" },
	{ "alt" },
	{ 0 }
};

/*
** An array of the possible attributes for an anchor tag
*/
HTMLAttr aAttrs[] = {
	{ "href" },
	{ 0 }
};

/*
** An array defining all of the tags recognised, and their properties -
** whether they're single or bracketed, and what the enumeration value used 
** to represent them is.  As these are definitions rather than instances,
** the attribute lists are obviously set to 0.
*/
HTMLTagDef htmlTags[] = {
	{ "h1",		htmlH1,		htmlBracketed,	0 },
	{ "h2",		htmlH2,		htmlBracketed,	0 },
	{ "h3",		htmlH3,		htmlBracketed,	0 },
	{ "h4",		htmlH4,		htmlBracketed,	0 },
	{ "h5",		htmlH5,		htmlBracketed,	0 },
	{ "h6",		htmlH6,		htmlBracketed,	0 },
	{ "u",		htmlUnderline,	htmlBracketed,	0 },
	{ "i",		htmlItalic,	htmlBracketed,	0 },
	{ "b",		htmlBold,	htmlBracketed,	0 },
	{ "title",	htmlTitle,	htmlBracketed,	0 },
	{ "head",	htmlHead,	htmlBracketed,	0 },
	{ "body",	htmlBody,	htmlBracketed,	0 },
	{ "base",	htmlBase,	htmlBracketed,	0 },
	{ "link",	htmlLink,	htmlBracketed,	0 },
	{ "isindex",	htmlIsIndex,	htmlBracketed,	0 },
	{ "a",		htmlAnchor,	htmlBracketed,	aAttrs },
	{ "p",		htmlParagraph,	htmlSingle,	0 },
	{ "br",		htmlBreak,	htmlSingle,	0 },
	{ "address",	htmlAddress,	htmlBracketed,	0 },
	{ "listing",	htmlListing,	htmlBracketed,	0 },
	{ "em",		htmlEm,		htmlBracketed,	0 },
	{ "strong",	htmlStrong,	htmlBracketed,	0 },
	{ "code",	htmlCode,	htmlBracketed,  0 },
	{ "samp",	htmlSamp,	htmlBracketed,	0 },
	{ "kbd",	htmlKbd,	htmlBracketed,	0 },
	{ "var",	htmlVar,	htmlBracketed,	0 },
	{ "dfn",	htmlDfn,	htmlBracketed,	0 },
	{ "cite",	htmlCite,	htmlBracketed,	0 },
	{ "pre",	htmlPreformatted,	htmlBracketed,	0 },
	{ "xmp",	htmlXmp,	htmlBracketed,	0 },
	{ "plaintext",	htmlPlaintext,	htmlBracketed,	0 },
	{ "blockquote",	htmlBlockquote,	htmlBracketed,	0 },
	{ "tt",		htmlTT,		htmlBracketed,	0 },
	{ "dl",		htmlDl,		htmlBracketed,	0 },
	{ "dt",		htmlDt,		htmlBracketed,	0 },
	{ "dd",		htmlDd,		htmlBracketed,	0 },
	{ "ul",		htmlUl,		htmlBracketed,	0 },
	{ "ol",		htmlOl,		htmlBracketed,	0 },
	{ "li",		htmlLi,		htmlSingle,	0 },
	{ "menu",	htmlMenu,	htmlBracketed,	0 },
	{ "dir",	htmlDir,	htmlBracketed,	0 },
	{ "form",	htmlForm,	htmlBracketed,	0 },
	{ "input",	htmlInput,	htmlBracketed,	0 },
	{ "select",	htmlSelect,	htmlBracketed,	0 },
	{ "option",	htmlOption,	htmlBracketed,	0 },
	{ "textarea",	htmlTextarea,	htmlBracketed,	0 },
	{ "!xdhignore",	htmlXDHIgnore,	htmlSingle,	0 },
	{ "!/xdhignore",	htmlXDHIgnoreEnd,	htmlSingle,	0 },
	{ "!",		htmlComment,	htmlBracketed,	0 },
	{ "img",	htmlImg,	htmlSingle,	imageAttrs },
	{ "hr",		htmlHr,		htmlSingle,	0 },
	{ "html",	htmlHTML,	htmlBracketed,	0 },
	{ "font",	htmlFont,	htmlBracketed,	0 },
	{ 0,		htmlNull,	htmlSingle,	0 }
};

/*
** A list of the recognised entities and the ASCII characters they map to
*/
static const HTMLEntity htmlChars[] = {
	{ "AElig",  	"\306" },
	{ "Aacute",  	"\301" },
	{ "Acirc",  	"\302" },
	{ "Agrave",  	"\300" },
	{ "Aring",  	"\305" },
	{ "Atilde",  	"\303" },
	{ "Auml",  	"\304" },
	{ "Ccedil",  	"\307" },
	{ "ETH",  	"\320" },
	{ "Eacute",  	"\311" },
	{ "Ecirc",  	"\312" },
	{ "Egrave",  	"\310" },
	{ "Euml",  	"\313" },
	{ "Iacute",  	"\315" },
	{ "Icirc",  	"\316" },
	{ "Igrave",  	"\314" },
	{ "Iuml",  	"\317" },
	{ "Ntilde",  	"\321" },
	{ "Oacute",  	"\323" },
	{ "Ocirc",  	"\324" },
	{ "Ograve",  	"\322" },
	{ "Oslash",  	"\330" },
	{ "Otilde",  	"\325" },
	{ "Ouml",  	"\326" },
	{ "THORN",  	"\336" },
	{ "Uacute",  	"\332" },
	{ "Ucirc",  	"\333" },
	{ "Ugrave",  	"\331" },
	{ "Uuml",  	"\334" },
	{ "Yacute",  	"\335" },
	{ "aacute",  	"\341" },
	{ "acirc",  	"\342" },
	{ "aelig",  	"\346" },
	{ "agrave",  	"\340" },
	{ "amp",  	"\046" },
	{ "aring",  	"\345" },
	{ "atilde",  	"\343" },
	{ "auml",  	"\344" },
	{ "ccedil",  	"\347" },
	{ "eacute",  	"\351" },
	{ "ecirc",  	"\352" },
	{ "egrave",  	"\350" },
	{ "emsp",	"\002" },
	{ "ensp",	"\002" },
	{ "eth",  	"\360" },
	{ "euml",  	"\353" },
	{ "gt",  	"\076" },
	{ "iacute",  	"\355" },
	{ "icirc",  	"\356" },
	{ "igrave",  	"\354" },
	{ "iuml",  	"\357" },
	{ "lt",  	"\074" },
	{ "nbsp",	"\001" },
	{ "ntilde",  	"\361" },
	{ "oacute",  	"\363" },
	{ "ocirc",  	"\364" },
	{ "ograve",  	"\362" },
	{ "oslash",  	"\370" },
	{ "otilde",  	"\365" },
	{ "ouml",  	"\366" },
	{ "quot",	"\042" },
	{ "szlig",  	"\337" },
	{ "thorn",  	"\376" },
	{ "uacute",  	"\372" },
	{ "ucirc",  	"\373" },
	{ "ugrave",  	"\371" },
	{ "uuml",  	"\374" },
	{ "yacute",  	"\375" },
	{ "yuml",  	"\377" }
};

CHTMLContext::CHTMLContext()
{
	attributes = 0;
	next = 0;
}

CHTMLContext::~CHTMLContext()
{
	delete attributes;
	delete next;
}

/*
** A method to get the attribute attrName from the attributes list in
** the tag which is at the top of the current context.  Return 0 if
** the attribute is not found, its character position in the attributes 
** string otherwise.  If it is found, also pass back the attribute value
** in attrValue.
*/
int
CHTMLContext::GetAttribute( const char *attrName, CJString &attrValue )
{
    if ( attributes == (CJString *) 0 )
	return 0 ;

    int len     = attributes->GetLength() ;
    int attrLen = strlen( attrName ) ;

    /* Search thorough the attributes string from the attribute we're looking
       for - case insensititive because attributes are */
    int i = 0;
    int j = 0;

    for ( i=0, j=0; i < len && j < attrLen; i++ )
	if ( tolower( (*attributes)[i] ) == tolower( attrName[j] ) )
	    j++ ;
	else
	    j = 0 ;

    /* If it's not found, or has no value... */
    if ( j != attrLen || (*attributes)[i++] != '=' ) {
	/* Return an attribute value which will show up well in
	   debugging */
	attrValue = "*** ATTRIBUTE " ;
	attrValue += attrName ;
	attrValue += " NOT FOUND ***" ;

	/* and a character position of zero */
	return 0 ;
    }

    /* Often, in HTML, people miss out the quotes around attribute values
       (which is invalid SGML syntax) - we should handle this gracefully
       by pretending they're optional. */
    char terminator ;

    /* If the character after the equals sign in the attribute assignation 
       is a quote, we search for an end quote - otherwise we assume the 
       next space character is the terminator */
    if ( ( *attributes )[i] == '"' ) 
	terminator = '"' ;
    else
	terminator = ' ' ;

    /* Now we get everything up to the terminator and that's what we should
       pass back to our caller */
    attributes->GetSubstring( i + 1, 
			      attributes->Find( terminator, i + 1 ), 
			      attrValue ) ;
    /* ...and return the start character position */
    return i ;

}

CHTMLParser::CHTMLParser( CStream *anInStream, CHTMLOutputStream *anOutStream )
{
	inStream = anInStream;
	outStream = anOutStream;
	contextStack = 0;
}

CHTMLParser::~CHTMLParser()
{
	delete contextStack;
}

/*
** Method to convert from the HTML entities to the equivalent 
** characters.  Returns NULL if the entity is unknown
*/
const char *
CHTMLParser::EntityToChars( const char *entity )
{
    if (entity != (const char *) 0) {
	    for ( int i=0; i < ( sizeof( htmlChars ) / sizeof( HTMLEntity ) ); i++ )
		if ( !strcmp( entity, htmlChars[i].name ) )
		    return htmlChars[i].text ;
    }

    return ( const char * ) 0 ;
}

/*
** Read an entity and output it on the output stream appropriately
** - return the last character read
*/
char *
CHTMLParser::ReadEntity()
{
    CJString  entityStr = (CJString) 0 ;
    char    *mbChar    = (char *) 0 ;
    char     c ;
    int found  = 0;

    /* Read in the entity, allowing for (erroneous) non-';'-terminated
       entities; NB. implicit assumption in comparisons that all entities
       use byte-per-character encoding (which is standard for HTML) */
    while (((mbChar = inStream->GetChar()) != (char *) 0) &&
	    ((c = *mbChar) != 0) && 
	    (c != ';' ) && 
	    !isspace( c ) )
    {
	found++;
	entityStr += mbChar ;
	delete mbChar ;
    }
    if (!found) {
	outStream->Write( "&", 1, contextStack ) ;
	return mbChar;
    }

    /* Get the real character equivalent */
    const char *realChars = EntityToChars( entityStr ) ;

    /* If there *was* a real character equivalent... */
    if ( realChars != (const char *) 0 ) {
	/* Write out the real characters if it's OK */
	outStream->Write( realChars, strlen( realChars ),
			  contextStack ) ;
    } else {
	/* Otherwise write out the entity itself */
	outStream->Write( "&", 1, contextStack ) ;
	outStream->Write( entityStr, entityStr.GetLength(), contextStack ) ;
	outStream->Write( ";", 1, contextStack ) ;
    }

    return mbChar ;
}

/*
** Put a new HTML context on the stack; this happens when we have found
** a new tag
*/
void
CHTMLParser::Push( CHTMLContext *t )
{
	t->next = contextStack;
	contextStack = t;
}

/*
** Take the last HTML context from the stack, if there is anything there
** - return the tag from the old top of the stack.
*/
HTMLTagDef *
CHTMLParser::Pop()
{
	CHTMLContext *t = contextStack;
	if ( t ) {
		HTMLTagDef *tag = t->tag;
		contextStack = contextStack->next;
		t->next = 0;
		delete t;
		return tag;
	}
	return 0;
}

/*
** In SGML, entities should never overlap - that is, they should either 
** be entirely contained within another, or separate from it.  So,
** for example, the HTML "<em>hello <strong>world</em>!!!</strong>" is 
** invalid and should be written 
** "<em>hello <strong>world</strong></em><strong>!!!</strong>".
** Unfortunately, many HTML authors are unaware of this, and we should
** cater for them.  So, when we hit an end tag, we have to remove the
** last tag of a matching type from our stack - not simply the last tag.
**
** This routine handles that - it runs down the stack, finds the first 
** context with a tag of type /tag/ and removes it.  If it can't find an 
** appropriate tag it does nothing.
*/
void
CHTMLParser::RemoveContext( int tag ) {
    CHTMLContext *thisOne = contextStack;

    /* If we *have* a context stack... */
    if ( thisOne ) {
	CHTMLContext *oneBefore = 0 ;

	/* Find the first context using the tag we're interested in,
	   keeping track of the one before it */
	while ( thisOne && thisOne->tag && thisOne->tag->tag != tag ) {
	    oneBefore = thisOne ;
	    thisOne = thisOne->next ;
	}

	/* If we found something appropriate... */
	if ( thisOne ) {
	    if ( !oneBefore ) {
		/* ...then it was the first one we encountered - valid 
		   HTML! - and we can pop the stack as you'd expect */
		(void) Pop() ;
	    } else {
		/* We have to remove it... */
		oneBefore->next = thisOne->next ;
		thisOne->next = 0 ;
		delete thisOne ;
	    }
	}
    }
}

/*
** Search the stack of context objects for the most recent occurence of a
** particular tag
*/
CHTMLContext *
CHTMLParser::FindTag( int tag )
{
	CHTMLContext *t;
	for ( t = contextStack; t; t = t->next )
		if ( t->tag->tag == tag )
			return t;
	return 0;
}

/*
** Find the HTMLTagDef that corresponds to a given tag string
*/
HTMLTagDef *
CHTMLParser::LookupTag( const char *tag )
{
	HTMLTagDef *t;

	for ( t = htmlTags; t->tag != htmlNull; t++ )
		if ( strcmp( t->name, tag ) == 0 )
			return t;
	return 0;
}

/*
** Look up an attribute in the current context; not used at present
*/
HTMLAttr *
CHTMLParser::LookupAttr( const char *attr )
{
	return 0;
}

/*
** Method called when we encounter a tag (recognised by the fact that it
** starts with a '<') during our parse.  Decodes the tag, and calls
** appropriate functions in the output stream.  This routine is full of 
** implicit assumptions that all of the tags use one byte per character,
** which is a safe assumption given the current HTML spec., and is likely to
** remain so.
*/
void
CHTMLParser::HandleTag() {
    /* the tag and its attributes, if and when we find it */
    HTMLAttr *attr;
    HTMLTagDef *tag;

    /* Variables controlling a resizeable buffer used to read in the tag */
    int   bufLen = 32 ;
    char *buf = new char[bufLen];

    buf[0] = '\0' ;

    /* The current (multibyte) character */
    char *c ;

    /* Variable to store whether this is a start or end tag */
    int endTag;

    /* First, see if it's an end tag or a start tag by checking for a '/' 
       as the next character */
    endTag = 0;
    c = inStream->GetChar();
    if ( !c ) {
	// Purify Patch
	delete buf ;

	return ;
    }
    if ( *c == '/' ) {
	delete c ;
	c = inStream->GetChar();
	endTag = 1;
    }

    /* Now look for the end of the tag text itself (and thus the start of
       any attributes).  We store the text in buf.  We assume that all
       of the characters in a tag must be single-byte */
    int i = 0 ;
    while ( c && *c && (mblen( c, MB_LEN_MAX ) == 1)
	 && (isalpha( *c ) || isdigit( *c ) || *c == '!' || *c == '/') )
    {
	if ( isupper( *c ) )
	    *c = tolower( *c ) ;
	buf[i++] = *c ;
	delete c ;
	c = inStream->GetChar();
    }

    buf[i++] = '\0' ;

    /* See what kind of tag it is: */
    tag = LookupTag( buf );

    int chLen ;
    i = 0 ;
    buf[i] = '\0' ;
    /* Read in the tag's attribute list as a string in the buffer /buf/,
       resizing if necessary - NB. we must allow for multibyte characters 
       here as, eg., the IMG's ALT attribute might have a multibyte string
       in it: */
    while ( c && *c 
	 && !((chLen = (mblen( c, MB_LEN_MAX )) == 1) && (*c == '>')) ) 
    {
    
	/* Resize the buffer if necessary */	
	while ( i + chLen >= bufLen ) {
	    int   newBufLen = bufLen * 2 ;
	    char *newBuf    = new char[newBufLen] ;
	    strncpy( newBuf, buf, i ) ;
	    delete buf ;
	    buf = newBuf ;
	    bufLen = newBufLen ;
	}
	
	for ( int j=0; j < chLen; j++ )
	    buf[i++] = c[j] ;
	delete c ;

	c = inStream->GetChar();
    }

    buf[i] = '\0' ;
	
    // Purify Patch
    if (c) {
	delete c ;
    }

    /* If the tag was recognised... */
    if ( tag ) {
	/* If we have a start tag */
	if ( !endTag ) {

	    /* ...we need to put a new context, set up with appropriate stuff,
	       onto the stack */
	    CHTMLContext *t = new CHTMLContext;
	    t->tag = tag;
	    t->attributes = new CJString( buf );
	    Push( t );

	    /* ...and then call our output stream's begin tag method to
	       tell it to do its stuff */
	    outStream->BeginTag( contextStack );

	    /* ...then if it's not a tag we expect an end tag for,
	       we take it off the stack again. */
	    if ( tag->type != htmlBracketed )
		Pop();

	} else {
	    if ( tag->type == htmlBracketed ) {
		outStream->EndTag( contextStack );
		RemoveContext( tag->tag );
	    }
	}
    }

    // Purify Patch
    delete buf ;
}

/*
** The routine to do the work - run through the input stream, writing
** text to the CHTMLOutputStream we've been initialised with and calling
** its BeginTag and EndTag functions as appropriate 
*/
void
CHTMLParser::Parse()
{
    /* Loop through the input stream - we break by calling return when 
       we hit the end */

    for ( ;; ) {
	char *c = inStream->GetChar();
	char  firstChar = 'x' ;

	if ( !c ) {
	    return ;
	}

	/* Now, if the character read has any special meaning, it will be
	   a single-byte character.  So, in that case we switch on it. */
	if ( mblen( c, MB_LEN_MAX ) == 1 )  {

	    switch ( *c ) {
	    
	    case EOF:
	    case '\0':
		/* We've hit the end of the stream - break out of the loop
		   by returning straight away. */
		return;

	    case '<':
		/* We've hit the start of a tag.  Process it */
		HandleTag();
		break;

	    case '&':
		/* We've found an entity - process it appropriately */
		delete c ;
		c = ReadEntity() ;
		break;

	    default:
		/* We've found some normal text, so we send it off to 
		   the output stream */
		outStream->Write( c, 1, contextStack );
		break;
	    } /* ...switch */

	} else {
	    /* the character read was multibyte and should therefore be 
	       treated as a normal (non-markup) character as this is what 
	       it must be in HTML. */
	    outStream->Write( c, mblen( c, MB_LEN_MAX ), contextStack );
	}
	delete c ;
    } /* for ( ;; ) */
}

/*
** Default actions for a CHTMLOutputStream - write everything to
** stdout, BeginTag and EndTag do nothing.
*/
int
CHTMLOutputStream::Write( const char *data, int length, CHTMLContext *context )
{
    return fwrite( data, 1, length, stdout );
}

void 
CHTMLOutputStream::BeginTag( CHTMLContext *context ) 
{
}

void
CHTMLOutputStream::EndTag( CHTMLContext *context ) 
{
}
