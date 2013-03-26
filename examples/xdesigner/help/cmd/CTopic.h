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
** sccsid = "@(#)helpGuru/cmd/CTopic.h	1.14" -- 96/02/29
*/

/*
** CTopic:
**
** Classes dealing with help topics.
**
** Jeremy Huxtable 1994
** Giles Thomas 1995, 1996
*/

#ifndef _H_CTopic
#define _H_CTopic

#include "CJString.h"
#include "CJList.h"

#include "CHTMLParser.h"

#ifndef False
typedef int Boolean ;
#define True -1
#define False 0
#endif

class CHelpDb;
class CTopic;
class CFile;

/*
** A class to represent a link to a document 
*/
class CLink {
public:
	CHelpDb *helpDb;
	CJString text;
	CJString name;

	CLink(const char *aText, const char *aName);
	CLink(const CLink& aLink);
	~CLink();

	CLink& operator=(const CLink& aLink);
};

/*
** A list of the above
*/
class CLinkList : public CJList {
public:
	~CLinkList();

	CLink *NthItem(int n) { return (CLink *)CJList::NthItem(n); }
};

/*
** An iterator to walk through the above list type 
*/
class CLinkListIterator : public CJListIterator {
public:
	CLinkListIterator(CLinkList *aList) : CJListIterator(aList) { }
	CLink *operator()() { return (CLink *)CJListIterator::operator()(); }
};

/*
** A CJStringFile is a CJString with the I/O methods of a file; it can
** be treated as a CJFile giving a useful abstraction which makes temporary
** files often unnecessary
*/
class CJStringFile;

/*
** CJStoppableStringFile is descended from CJStringFile but has extra features;
** see CTopic.cxx for details 
*/
class CJStoppableStringFile ;

/*
** A class which can accept the output of a CHTMLParser, through its 
** inheritance.  This subclass of CHTMLOutputStream kmows how to fill
** in a CTopic (with which it is initialised) with parsed HTML
*/
class CGuruOutputStream : public CHTMLOutputStream {
public:
	CGuruOutputStream(CTopic *aTopic);
	~CGuruOutputStream();

	/* Overridden from CHTMLOutputStream - it uses these to pass us
	   a set of characters, or to begin and end tags (as one would
	   expect... */
	virtual int Write(const char *buf, int length, CHTMLContext *context);
	void BeginTag(CHTMLContext *context);
	void EndTag(CHTMLContext *context);

private:
	/* The topic this CGuruOutputStream is filling in */
	CTopic *itsTopic;

	/* Internal storage - the file to which we are writing the title,
	   which is actuallt the title section of the topic */
	CJStringFile *titleFile;

	/* the file to which we are writing the body text, as above */
	CJStoppableStringFile *textFile;

	/* Flag to test if we are reading a link */
	Boolean inLink ;
	/* The destination of the link if we are */
	CJString destination ;

	/* A flag to say whether we should be stripping whitespace or not 
	   (for support fo the <PRE> tag) */
	Boolean stripping ;

	/* a link currently being parsed */
	CJString *linkText ;

        /* The number of links read so far */
        int numLinks ;

	/* A flag to see if we're in the middle of a load
	   of whitespace that we're ignoring */
	Boolean inspace ;

	/* Internal functions to handle the rather complex situation
	   when links are begun or ended */
	void BeginLink( CHTMLContext *context ) ;
	void EndLink( CHTMLContext *context ) ;

};

/*
** A class to represent named anchors (sometimes called, confusingly, tags)
** in an HTML document
*/
class CNamedAnchor {
public:
    CNamedAnchor( CJString nameStr, int charNum ) {
	name = nameStr ;
	charPos = charNum ;
    }

    CJString name ;
    int      charPos ;
};

/*
** List of the above; could be a hashtable but as there are generally
** few named anchors in a document, there's little point.
*/
class CNamedAnchList : public CJList {
public:
    CNamedAnchor *operator[]( long n ) {
	return (CNamedAnchor *) CJList::operator[]( n ) ;
    }

    /* Find the character position within the body text of a given named 
       anchor, returning -1 if unknown. */
    virtual int positionOf( CJString name ) ;

    ~CNamedAnchList() ;
};

/*
** An iterator to walk through the above list type 
*/
class CNamedAnchListIterator : public CJListIterator {
public:
	CNamedAnchListIterator( CNamedAnchList *aList ) 
	    : CJListIterator(aList) { }
	    
	CNamedAnchor *operator()() { 
	    return (CNamedAnchor *)CJListIterator::operator()() ; 
	}
};


/*
** A class to represent a help topic - conatins all information about it
** after parsing
*/
class CTopic {
public:
	CJString title;
	CJString text;
	CLinkList links;
	int refCount;

	CNamedAnchList *namedAnchors ;

	CTopic();
	~CTopic();

	void Reference() { refCount++; }
	void Dereference() { if (--refCount == 0) delete this; }
};

/*
** A database of help topics - an abstraction of the directory in
** which a topic resides
*/
class CHelpDb {
public:
        /* The path to this directory */
	CJString pathName;

	CHelpDb();
	virtual ~CHelpDb();

	/* Method to open a topic and move to its directory */
	virtual CTopic *OpenTopic(const char *aKey) ;

	/* Method to get a list of links to files in the database (ie.
	   directory) containing a particular string */
	virtual int FindText(const char *text, long textLen, CLinkList &list);

	/* Method to move to the directory of a new link, and to store 
	   state about the directory */
	int SetPath(const char *aFileName);
};

#endif /* _H_CTopic */
