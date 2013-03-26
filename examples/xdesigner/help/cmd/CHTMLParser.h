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
** sccsid = "@(#)helpGuru/cmd/CHTMLParser.h	1.7" -- 96/05/13
*/

/*
** CHTMLParser:
**
** A class for parsing HTML.
**
** Jeremy Huxtable 1995
** Giles Thomas 1995, 1996
*/

#ifndef _H_CHTMLParser
#define _H_CHTMLParser

/*
** An enumeration defining the two sorts of tags - 'bracketed' ones, which 
** *must* have an end tag, and 'single' ones which need not (SGML has no
** syntax to say that a entity *cannot* have an end tag, only enough to say 
** that the end tag is optional)
*/
enum {
	htmlSingle,
	htmlBracketed
};

/*
** An enumeration of all recognised HTML tags
*/
enum {
	htmlNull = 0,
	htmlBold,
	htmlItalic,
	htmlUnderline,
	htmlH1,
	htmlH2,
	htmlH3,
	htmlH4,
	htmlH5,
	htmlH6,
	htmlPreformatted,
	htmlImage,
	htmlFont,
	htmlHead,
	htmlBody,
	htmlTitle,
	htmlBase,
	htmlLink,
	htmlIsIndex,
	htmlAnchor,
	htmlParagraph,
	htmlBreak,
	htmlAddress,
	htmlListing,
	htmlEm,
	htmlStrong,
	htmlCode,
	htmlSamp,
	htmlKbd,
	htmlVar,
	htmlDfn,
	htmlCite,
	htmlXmp,
	htmlPlaintext,
	htmlBlockquote,
	htmlTT,
	htmlDl,
	htmlDt,
	htmlDd,
	htmlUl,
	htmlLi,
	htmlOl,
	htmlMenu,
	htmlDir,
	htmlForm,
	htmlInput,
	htmlSelect,
	htmlOption,
	htmlTextarea,
	htmlComment,
	htmlImg,
	htmlHr,
	htmlHTML,
	htmlXDHIgnore,
	htmlXDHIgnoreEnd,
	htmlUser
};

/*
** Some basic physical text styles 
*/
enum HTMLTextStyle {
	hsNormal = 0,
	hsBold = 1,
	hsItalic = 2,
	hsUnderLine = 4
};

/*
** An HTML 'entity' - some section of markup
*/
class HTMLEntity {
public:
	const char *name;
	const char *text;
};

/*
** An attribute, which a tag may have
*/
class HTMLAttr {
public:
	const char *name;
};

/*
** A HTML tag; its name, the value from the above enumeration which defines
** the tag it represents, its type - bracketed or single - and a pointer
** to its list of attributes 
*/
class HTMLTagDef {
public:
	const char *name;
	int tag;
	int type;
	HTMLAttr *attrs;
};

/*
** Two classes from the class library used in the parser 
*/
class CStream;
class CJString;

/*
** A context in the parse of the HTML document - the current context tells 
** us what the last tag was, and has a string representation of its attribute
** list (as read in from the input.  GetTag is used as an accessor for the 
** enumeration value which describes its tag, and GetAttribute can be used
** to access the tag's attributes.  The next pointer points to the last tag
** encountered which is yet to receive an end tag.
*/
class CHTMLContext {
public:
	CHTMLContext *next;
	HTMLTagDef *tag;
	CJString *attributes;

	CHTMLContext();
	~CHTMLContext();

	int GetTag() { return tag->tag; }

	/*
	** A method to get the attribute attrName from the attributes 
	** list in the tag which is at the top of the current context.  
	** Return 0 if the attribute is not found, its character
	** position in the attributes string otherwise.  If it is found, 
	** also pass back the attribute value in attrValue.
	*/
	int GetAttribute( const char *attrName, CJString &attrValue );
};

/*
** The CHTMLParser class below writes to a CHTMLOutputStream; this should be
** subclassed for any use of the parser module in anger.  The default
** implementation writes its input to stdout.
*/
class CHTMLOutputStream {
public:
	virtual int Write( const char *buf, int length, 
			   CHTMLContext *context );
	virtual void BeginTag( CHTMLContext *context ) ;
	virtual void EndTag( CHTMLContext *context );
};

/*
** This is the class to use for parsing.  It should be initialised with an
** appropriate output stream and input stream, then told to Parse().  FindTag 
** finds the highest occurence of a given tag in the current context.  The
** private methods are described alongside their implementations in 
** the implementation file for this class.
*/
class CHTMLParser {
public:
	CHTMLParser( CStream *anInStream, CHTMLOutputStream *anOutStream );
	~CHTMLParser();

	void Parse();
	CHTMLContext *FindTag( int tag );

private:
	CStream *inStream;
	CHTMLOutputStream *outStream;
	CHTMLContext *contextStack;

	HTMLTagDef *LookupTag( const char *tag );
	HTMLAttr *LookupAttr( const char *attr );

	void Push( CHTMLContext *t );
	HTMLTagDef *Pop();
	const char *EntityToChars( const char *escape );
	char *ReadEntity();

	void HandleTag() ;
	void RemoveContext( int tag );
};

#endif
