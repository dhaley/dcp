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
** sccsid = "@(#)helpGuru/cmd/CHistList.h	1.3" -- 96/02/27
*/

#ifndef _H_CHistoryList
#define _H_CHistoryList

#include "CTopic.h"

/*
** A history list is the same as a list of links but has the notion of a 
** current item.  When a new item is added, items from the current to 
** the tail are first deleted.
*/
class CHistoryList : public CLinkList {
public:
	long currentItem;

	CHistoryList();
	~CHistoryList();

	CLink *operator[]( long n ) { 
	    return (CLink *) CJList::operator[]( n );
	}

	/* Add a new item to the list, first deleting eveything after
	   the current item */
	void AppendItem( CLink *anItem );

	/* Return the first item in the list (without affecting currentItem) */
	CLink *First();

	/* Make currentItem the item before or after the one it was, if 
	   that's possible, returning the new current item. */
	CLink *Back();
	CLink *Forward();

	/* Functions to check if we *can* go forward or back */
	int CanGoBack();
	int CanGoForward();
};

#endif
