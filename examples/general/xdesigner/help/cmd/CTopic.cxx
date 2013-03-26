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
static char *sccsid = {"@(#)helpGuru/cmd/CTopic.cxx	1.33"} ; /* 99/08/12 */
#endif /* lint && NOSCCS */

/*
** CTopic:
**
** Classes dealing with help topics.
**
** Jeremy Huxtable 1994
** Giles Thomas 1995, 1996
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <errno.h>

#ifdef    VMS
#include <unixlib.h>
#define   CURRENT_DIRECTORY     "[]"
#define   END_DIRECTORY_MARKER  ']'
#else  /* VMS */
#define   CURRENT_DIRECTORY     "."
#define   END_DIRECTORY_MARKER  '/'
#endif /* VMS */

#ifndef   VMS
#include <dirent.h>
#endif /* VMS */

#include "CTopic.h"
#include "CSearcher.h"
#include "CHistList.h"
#include "CStream.h"
#include "CJStringFile.h"
#include "CJStop.h"
    
extern "C" { 
	int   chdir(const char *) ;
}

#ifdef    VMS
/*
** This file contains the VMS routines to implement a limited
** implementation of the Unix opendir/readdir/closedir functions.
**
** Many thanks to John Wood, Digital Equipment Coproration.
*/

#include <rms.h>

#ifndef   VMS_MAX_PATH_LENGTH
#define   VMS_MAX_PATH_LENGTH                 255
#endif /* VMS_MAX_PATH_LENGTH */

#ifndef   VMS_DEFAULT_VERSION_SPECIFICATION
#define   VMS_DEFAULT_VERSION_SPECIFICATION   "*.*;0"
#endif /* VMS_DEFAULT_VERSION_SPECIFICATION */

/* 
** Structure to mimic the Unix dirent
*/

typedef struct dirent
{
	unsigned int   d_ino ;
	unsigned short d_reclen ;
	unsigned short d_namlen ;
	char           d_name[VMS_MAX_PATH_LENGTH + 1] ;
} ;


typedef struct 
{
	struct dirent dir_entry ;
	struct FAB    fab ;
	struct NAM    nam ;
	char          result_string[VMS_MAX_PATH_LENGTH] ;
	char          expand_string[VMS_MAX_PATH_LENGTH] ;
} DIR ;

extern "C" {
	int sys$parse(struct FAB *, int, int) ;
	int sys$search(struct FAB *, int, int) ;
}

static char path_version[] = VMS_DEFAULT_VERSION_SPECIFICATION ;

#ifndef   _NO_PROTO
static DIR *opendir(char *path)
#else  /* _NO_PROTO */
static DIR *opendir(path)
	char *path ;
#endif /* _NO_PROTO */
{
	register DIR        *handle = (DIR *) 0 ;
	register struct FAB *fab    = (struct FAB *) 0 ;
	register struct NAM *nam    = (struct NAM *) 0 ;
	register char       *pptr   = (char *) 0 ;
		 long        status = (long) 0 ;

	if (((pptr = path) == (char *) 0) || (*pptr == '\0')) {
		pptr = CURRENT_DIRECTORY ;
	}

	/* Using Calloc because it zero's the allocated memory */

	if ((handle = (DIR *) calloc(sizeof(DIR), 1)) == (DIR *) 0) { 
		return (DIR *) 0 ;
	}

	fab = &(handle->fab) ;
	nam = &(handle->nam) ;
	
	*nam = cc$rms_nam ;
	*fab = cc$rms_fab ;

	nam->nam$l_rsa = handle->result_string ;
	nam->nam$b_rss = VMS_MAX_PATH_LENGTH ;
	nam->nam$l_esa = handle->expand_string ;
	nam->nam$b_ess = VMS_MAX_PATH_LENGTH ;
	
	fab->fab$l_nam = nam ;
	fab->fab$l_fna = pptr ;
	fab->fab$b_fns = strlen(pptr) ;
	fab->fab$l_dna = path_version ;
	fab->fab$b_dns = strlen(path_version) ;
    
	status = sys$parse(fab, 0, 0) ;
	
	if (!(status & 1)) { 
		free((char *) handle) ;
		
		handle = (DIR *) 0 ;
	}
		
	return handle ;
} 


#ifndef   _NO_PROTO
static struct dirent *readdir(DIR *handle)
#else  /* _NO_PROTO */
static struct dirent *readdir(handle)
	DIR *handle ;
#endif /* _NO_PROTO */
{
	register struct FAB    *fab       = (struct FAB *) 0 ;
	register struct NAM    *nam       = (struct NAM *) 0 ;
	register struct dirent *dir_entry = (struct dirent *) 0 ;
		 long           status    = (long) 0 ;
	
	if (handle == (DIR *) 0) {
		return (struct dirent *) 0 ;
	}

	fab       = &(handle->fab) ;
	nam       = &(handle->nam) ;
	dir_entry = &(handle->dir_entry) ;
	
	status = sys$search(fab, 0, 0) ;
			
	if (status == RMS$_NMF) {
		/* NO MORE FILES */

		dir_entry = (struct dirent *) 0 ;
	}
	else {
		if (!(status & 1)) {
			dir_entry = (struct dirent *) 0 ;
		}
		else {
			dir_entry->d_namlen = nam->nam$b_name + nam->nam$b_type ;
			
			memmove(dir_entry->d_name, nam->nam$l_name, dir_entry->d_namlen) ;
			
			dir_entry->d_name[dir_entry->d_namlen] = '\0' ;
		}
	}
		
	return dir_entry ;
}

#ifndef   _NO_PROTO
static void closedir(register DIR *handle)
#else  /* _NO_PROTO */
static void closedir(handle)
	register DIR *handle ;
#endif /* _NO_PROTO */
{
	if (handle != (DIR *) 0) {
    		free((char *) handle) ;
	}
}
#endif /* VMS */


CLink::CLink( const char *aText, const char *aName )
{
	text = aText;
	name = aName;
	helpDb = 0;
}

CLink::CLink( const CLink& aLink )
{
	text = aLink.text;
	name = aLink.name;
	helpDb = aLink.helpDb;
}

CLink::~CLink()
{
}

CLink&
CLink::operator=( const CLink& aLink )
{
	text = aLink.text;
	name = aLink.name;
	return *this;
}

CLinkList::~CLinkList()
{
	CLink *t;
	CLinkListIterator it( this );
	while ( ( t = it() ) != 0 )
		delete t;
	RemoveAll();
}

CTopic::CTopic()
{
	text = "";
	title = "";
	namedAnchors = new CNamedAnchList() ;
}

CTopic::~CTopic()
{
    delete namedAnchors ;
}

CHelpDb::CHelpDb()
{
	pathName = "";
}

CHelpDb::~CHelpDb()
{
}

CNamedAnchList::~CNamedAnchList() {
    CNamedAnchListIterator it( this ) ;
    CNamedAnchor *a ;

    while ( ( a = it() ) != 0  )
	delete a ;
}

/*
** Find the character position within the body text of a given named anchor,
** returning -1 if unknown.
*/
int 
CNamedAnchList::positionOf( CJString name ) {
    CNamedAnchListIterator it( this ) ;
    CNamedAnchor *a ;

    while ( ( a = it() ) != 0  )
	if ( a->name == name )
	    return a->charPos ;

    /* -1 means that the named anchor was not found. */
    return -1 ;
}

/*
** Store away the directory of the current help topic, and change directory 
** to there.  We do this so that relative pathnames are handled correctly
*/
int
CHelpDb::SetPath( const char *aFileName )
{
    int e;
    const char *p = aFileName;
    const char *baseName = aFileName;
    
    /* Get the pathname from the filename - we can't trust rindex() or
       strrchr() as they are not uniformly available, so: */
    while ( *p ) {
	if ( *p++ == END_DIRECTORY_MARKER )
	    baseName = p;
    }

    /* Store the directory away */
    pathName.SetText( aFileName, baseName-aFileName );

    if ( pathName == "" )
	pathName.SetText( CURRENT_DIRECTORY ) ;

    /* Change to the directory */
    e = chdir( pathName );

    /* Return an error if we had a problem doing that */
    if ( e < 0 )
	return errno;

    /* Now get the current working directory, in case the directory was a
       relative pathname (this is the quickest way of resolving it) */
    char *cwdarray = new char[2048+1];
    char *cwd = getcwd( cwdarray, 2048 ) ;

    if ( cwd == NULL )
	return errno ;

    pathName.SetText( cwd ) ;

    // Purify patch: wrong memory management
    // free(cwd);
    delete cwdarray ;

#ifndef   VMS
    pathName += "/";
#endif /* VMS */

    return 0;
}

/*
** Open a new topic whose filename is /key/.  Return the parsed file in the 
** form of a CTopic.
*/
CTopic *
CHelpDb::OpenTopic( const char *aKey )
{
    FILE *f = fopen( aKey, "r" );

    if ( f ) {
	CTopic *t = new CTopic;

	/* Move into the topic's directory */
	SetPath( aKey );
	CDiskFile file;
	
	/* Create a class-based interface to the FILE * */
	file.Open( f );
	CStream s( &file, CFile::fileRead );

	/* A CGuruOutputStream knows how to place the input from a 
	   CHTMLParser into the various components of whatever it has
	   been initialised with.  Input is sent by calling the various 
	   methods of the class; see the class itself for details. 
	   The default implementation knows how to fill in a CTopic 
	   class with the information it receives, but a different one 
	   might know how to produce RTF for the Microsoft Windows help 
	   system (WinHelp), or to produce some other format */
	CGuruOutputStream outStream( t );

	/* Initialise a new parser, and set it off */
	CHTMLParser p( &s, &outStream );
	p.Parse();

	/* Bug: CDiskFile closes this in the destroy method    */
	/* On some systems, if you call fclose twice, it cores */
	/*fclose( f );*/

	/* ...and we're done! */
	return t;
    }

    /* If the file open failed, return 0 to let the caller know. */
    return 0;
}

/*
** Method to search the current database (ie. the directory containing the
** current file - this is all the context we have and is appropriate for
** the restricted purposes of online help) for a particular string.  Return
** a list of CLinks representing links to the files containing the 
** string.
*/
int
CHelpDb::FindText( const char *text, long textLen, CLinkList &list )
{
    int count = 0;

    if ( *text ) {
	struct dirent *dir_entry = (struct dirent *) 0 ;

	/* Open the current directory... */
	DIR *dir_handle = opendir( CURRENT_DIRECTORY );

	/* Initialise a searcher to do the work for us */
	CSearcher searcher( text, textLen );

	/* Then, for each file... */
	while ( ( dir_entry = readdir( dir_handle ) ) != (struct dirent *) 0 ) {
	    /* Load the file as a topic... */
	    CTopic *t = OpenTopic( dir_entry->d_name );

	    /* ...and, if we understood the format to any degree */
	    if ( t ) {

		/* Check the text for the string we want... */
		if ( searcher.TextContainsPattern( t->text, 
						   t->text.GetLength() ) ) {
		    /* Get the full filename */
		    CJString linkName = pathName;
		    linkName += dir_entry->d_name;

		    /* If we couldn't detect a title, invent one */
		    if ( t->title.GetLength() == 0 ) {
			t->title.SetText( "(untitled)" ) ;
			t->title += dir_entry->d_name ;
		    }

		    /* ...then add the link to the list we're keeping */
		    list.Append( new CLink( t->title, linkName ) );
		    count++;

		}
		delete t;
	    }
	}
	closedir( dir_handle );

	return count;
    }
    return count;
}

CGuruOutputStream::CGuruOutputStream( CTopic *aTopic )
{
    /* Of course, we don't start halfway through a link... */
    inLink = False ;

    /* We start skipping leading whitespace */
    inspace = True ;
    stripping = True ;

    /* We keep a count of the number of links encoutnered so far so
       that we can number them */
    numLinks = 0 ;

    /* We need to store away the text for any link we're reading */
    linkText = 0 ;

    /* Remember what the topic we're filling in is */
    itsTopic = aTopic;

    /* Set up the two CJStringFiles so that the strings they are abstracting 
       are the appropriate bits of the topic we are filling in */
    titleFile = new CJStringFile;
    titleFile->Open( &itsTopic->title, CFile::fileWrite );
    textFile = new CJStoppableStringFile;
    textFile->Open( &itsTopic->text, CFile::fileWrite );

}

CGuruOutputStream::~CGuruOutputStream()
{
	delete titleFile;
	delete textFile;
}

int
CGuruOutputStream::Write( const char *data, int length, CHTMLContext *context )
{
    char *stripped = new char[ length + 1 ] ;
    stripped[0] = '\0' ;

    if ( stripping ) {

	int thisCharLen = 1 ;
	int i, j;

	/* First get rid of whitespace */
	for ( i=0, j=0 ; i < length; )  {

	    thisCharLen = mblen( data + i, length - i ) ;

	    if ( (thisCharLen == 1) && isspace( data[i] ) ) {

		/* If we haven't yet encountered space... */
		if ( !inspace ) {
		    /* Note that we have, but store this bit away - as a 
		       space, as tabs and carriage returns are simply layout, 
		       to be ignored in formatting HTML */
		    inspace = True ;
		    stripped[j++] = ' ' ;
		}
		 
		i++ ;

	    } else {

		/* If we've encountered anything that's not space, make a 
		   note of of this and copy the (multibyte) character 
		   across. */
		inspace = False ;
		for ( int k=0; k < thisCharLen; k++ )
		    stripped[j++] = data[i++] ;

	    }

	}

	/* Terminate the string properly and remember its length */
	stripped[j] = '\0' ;
	length = strlen( stripped ) ;

    } else { 
	strncpy( stripped, data, length ) ;
	stripped[length] = '\0' ;
    }

    /* If we're building the text describing a link, just add the text 
       onto whatever we have so far - otherwise, write it to the title text
       or to the body text as appropriate */
    if ( inLink ) {
	if ( linkText != ( CJString * ) 0 )
	    *linkText += stripped ;
    } else if ( context && context->GetTag() == htmlTitle ) {
	titleFile->Write( stripped, length );
    } else {
	textFile->Write( stripped, length );
    }

    int len = strlen( stripped ) ;

    delete stripped ;

    return len ;
}

/*
** Method to be called when we encounter an start-link tag to set up
** our internal notes of that, and to store away notes of the destination
** if there is one, and of the name/char position if it is a named anchor
*/
void
CGuruOutputStream::BeginLink( CHTMLContext *context )
{
    inLink = True ;
    if ( linkText ) {
	delete linkText ;
    }
    linkText = new CJString ;

    /* Get the destination */
    if ( context->GetAttribute( "href", destination ) ) {
	/* We've got a destination */

	if ( destination.GetLength() == 0 ) 
	    inLink = False ;

    } else
	inLink = False ;

    /* Get the name */
    CJString name ;
    if ( context->GetAttribute( "name", name ) ) {

	CNamedAnchor *newAnchor = 
	    new CNamedAnchor( name, textFile->GetCharsWritten() ) ;

	itsTopic->namedAnchors->Append( newAnchor ) ;

    }
}

/*
** Method to be called when we encounter an end-link tag to sort out the 
** list of links and the link-reading state
*/
void
CGuruOutputStream::EndLink( CHTMLContext *context )
{
    /* Sort out state */
    inLink = False ;

    if ( linkText ) {

	if ( linkText->GetLength() != 0 ) {
		    
	    /* If there was a matching start tag to this list... */
	    if ( destination.GetLength() != 0 ) {

		/* First increment our count... */
		numLinks ++ ;

		/* We need a string to put into the main text area,
		   and one to put into the list of links.  The latter
		   begins with a number. */
		CJString bodyText ;
		CJString listText( numLinks ) ;

		/* Create a string of the form "<link text> [<n>] " using
		   the list text, which at present is a string
		   representation of the number... */
		bodyText = *linkText ;
		bodyText += " [" ;
		bodyText += listText ;
		bodyText += "] " ;
		
		/* ...and a string of the form "<n>. <link text>" */
		listText += ". " ;
		listText += *linkText ;

		/* Create a links object to represent the link, and
		   add it to our topic's list of links */
		CLink *link = new CLink( listText, destination ) ;
		itsTopic->links.Append( link ) ;

		/* Change the link text to reflect the body form as we
		   no longer need it in its pure form */
		    *linkText = bodyText ;
	    }
			
	    /* whether the link is valid or not its text is still
	       needed. */
	    int length = strlen( *linkText ) ;
	    textFile->Write( *linkText, length ) ;
	}
	
	/* tidy up*/
	delete linkText ;
	linkText = 0 ;
    }
}

/*
** Method called by a CHTMLParser when it's found a link.  The CHTMLContext
** describes the link to us.  We must do something appropriate.  Most
** cases are farily obvious.
*/
void
CGuruOutputStream::BeginTag( CHTMLContext *context )
{
    if ( context ) {
	if ( context->tag )
	    /* if we understand this tag, we handle it (if it's supported) */
	    switch( context->tag->tag ) {

	      /* The following two cases switch the body text's
		 CJStoppableStringFile on or off depending on whether we've
		 just hit a <!XDHIGNORE> or a <!/XDHIGNORE> - both of which
		 are really 'begin tags' as far as current browsers (including
		 this one) are concerned.  SGML browsers may have problems.  
		 We suggest that you *do not* use these tag in any help 
		 documents you yourself produce. */

	      case htmlXDHIgnore:
		textFile->WriteIf( False ) ;
		break ;

	      case htmlXDHIgnoreEnd:
		textFile->WriteIf( True ) ;
		break ;

	      case htmlAnchor:
		BeginLink( context ) ;
		break ;
		
	      case htmlParagraph:
		textFile->Write( "\n\n", 2 ) ;
		break ;
		
	      case htmlBreak:
		textFile->Write( "\n", 1 ) ;
		break ;

	      /* some *very* crude list-handling stuff; */
	      case htmlUl:
	      case htmlOl:
	      case htmlDl:
		textFile->Write( "\n", 1 ) ;
		break ;

	      /* NB. <LI>, <DD> and <DT> are interpreted
		 even if we are not in a list! */
	      case htmlLi:
	      case htmlDt:
		textFile->Write( "\n   - ", 6 ) ;
		break ;
		
	      case htmlDd:
		textFile->Write( "\n       ", 8 ) ;
		break ;

	      /* Do emphasis with the normal method of putting
		 stars on either side of the emphasised phrase.
		 NB. this is mirrored in EndTag */
	      case htmlItalic:
	      case htmlBold:
	      case htmlEm:
		textFile->Write( "*", 1 ) ;
		break ;

	      /* Titles should have space above them */
	      case htmlH1:
	      case htmlH2:
	      case htmlH3:
	      case htmlH4:
	      case htmlH5:
	      case htmlH6:
		textFile->Write( "\n\n", 2  ) ;
		break ;

	      /* Handle preformatted by stopping the write function from
		 skipping whitespace */
	      case htmlPreformatted:
		stripping = False ;
		break ;

	      case htmlImg:
		{
		CJString alternate ;
		if ( context->GetAttribute( "alt", alternate ) )
		    textFile->Write( alternate, alternate.GetLength() ) ;
		textFile->Write( " ", 1 ) ;
		}
		break ;
	    }
    }
}

void
CGuruOutputStream::EndTag( CHTMLContext *context )
{
    if ( context ) {
	if ( context->tag )  {
	    /* If we've got a valid context... */
	    switch ( context->tag->tag ) {
	      
	    case htmlAnchor:
		EndLink( context ) ;
		break ;
		
	    /* Do emphasis with the normal method of putting
	       stars on either side of the emphasised phrase.
	       NB. this is mirrored in BeginTag */
	    case htmlItalic:
	    case htmlBold:
	    case htmlEm:
		textFile->Write( "*", 1 ) ;
		break ;
		
	    case htmlH1:
	    case htmlH2:
	    case htmlH3:
	    case htmlH4:
	    case htmlH5:
	    case htmlH6:
		textFile->Write( "\n\n", 2 ) ;
		break ;
		
	    /* some *very* crude list-handling stuff; */
	    case htmlUl:
	    case htmlOl:
	    case htmlDl:
		textFile->Write( "\n\n", 2 ) ;
		break ;

	    /* Handle preformatted end tag by allowing the write function to
	       skip whitespace */
	    case htmlPreformatted:
		stripping = True ;
	    }
	}
    }
}

