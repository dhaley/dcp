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
static char *sccsid = {"@(#)helpGuru/cmd/CHistList.cxx	1.5"} ; /* 96/02/27 */
#endif /* lint && NOSCCS */

#include "CHistList.h"

/*
** A history list is the same as a list of links but has the notion of a 
** current item.  When a new item is added, items from the current to 
** the tail are first deleted.
*/

CHistoryList::CHistoryList()
{
    currentItem = -1;
}

CHistoryList::~CHistoryList()
{
}

/*
** This is like Append, but removes all items after the current item first.
*/
void
CHistoryList::AppendItem( CLink *anItem )
{
    long i;

    /* Delete all items after the current one */
    for ( i = currentItem + 1; i < numItems; i++ )
	delete (*this)[i];
    SetNumItems( currentItem + 1 );

    /* Add on the new item */
    Append( anItem );

    /* ...and tidy up */
    currentItem = GetNumItems() - 1;
}

/*
** Method to find the first item in the history list 
*/
CLink *
CHistoryList::First()
{
	return (CLink *) FirstItem();
}

/*
** Method to go back in the history list, if possible, *not* forgetting 
** the current item - this will happen if a new item is added without 
** going forward first 
*/
CLink *
CHistoryList::Back()
{
    if ( currentItem > 0 )
	currentItem--;
    return ( *this )[currentItem];
}

/*
** Method to go forward in the history list if possible
*/
CLink *
CHistoryList::Forward()
{
    if ( items && currentItem < GetNumItems()-1 )
	currentItem++;
    return ( *this )[currentItem];
}

/*
** Check if it's possible to go back in the list 
*/
int
CHistoryList::CanGoBack()
{
    return currentItem > 0;
}

/*
** Check if it's possible to go forward in the list
*/
int
CHistoryList::CanGoForward()
{
    return currentItem < GetNumItems() - 1;
}
