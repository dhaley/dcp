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
static char *sccsid = {"@(#)helpGuru/libgen/CJList.cxx	1.1"} ; /* 95/12/13 */
#endif /* lint && NOSCCS */

/*
** CJList:
**
** A class implementing a simple list.
**
** Jeremy Huxtable 1991
*/

#include <stdlib.h>
#include <string.h>
#include "CJList.h"

CJList::CJList()
{
	blockSize = 3;
	slots = 0;
	numItems = 0;
	items = (ListElement **)malloc(sizeof(ListElement *));
}

CJList::~CJList(void)
{
	if (items) {
		free((char *)items);
		items = (ListElement **)0;
	}
}

CJList::CJList(const CJList &aList)
{
	numItems = aList.numItems;
	slots = aList.slots;
	blockSize = aList.blockSize;
	items = (ListElement **)malloc((int)(slots+1) * sizeof(ListElement *));
	if (items)
		memmove((char *)items, (char *)aList.items, (slots+1) * sizeof(ListElement *));
}

void
CJList::Store(ListElement *t, long index)
{	
	items[index-1] = t;
}

void
CJList::Resize(long numSlots)
{
	slots = numSlots;
	items = (ListElement **)realloc((char *)items, (int)(slots+1L) * sizeof(ListElement *));
}

void
CJList::Insert(ListElement *t, long index)
{	
	if (numItems >= slots)
		Resize(slots + blockSize);

	if (index <= numItems) {
		long i;
		for (i = numItems; i >= index; i--)
			items[i] = items[i-1];
	} else
		index = numItems + 1;

	numItems++;
	Store(t, index);
}

void
CJList::DeleteItem(long index)
{
	numItems--;

	if (index <= numItems) {
		long i;
		for (i = index-1; i < numItems; i++)
			items[i] = items[i+1];
	}

	if (slots > numItems + blockSize)
		Resize(slots-blockSize);
}

ListElement *
CJList::NthItem(long n) const
{
	if (1 <= n && n <= numItems)
		return items[n-1];
	return (ListElement *)0;
}

void
CJList::AppendList(CJList *list)
{
	ListElement *t;
	CJListIterator it(list);
	while ((t = it()) != 0)
		Append(t);
}

void
CJList::Prepend(ListElement *t)
{
	Insert(t, 1);
}

void
CJList::MoveTo(long from, long to)
{
	ListElement *t;

	if (from == to || from < 1 || from > numItems)
		return;

	if (to < 1)
		to = 1;
	else if (to > numItems)
		to = numItems;

	from--;
	to--;
	t = items[from];
	if (from < to)
		memmove((char *)(items+from), (char *)(items+from+1),
						(to - from) * sizeof(ListElement *));
	else if (from > to)
		memmove((char *)(items+to+1), (char *)(items+to),
						(from - to) * sizeof(ListElement *));
	items[to] = t;
}

long
CJList::IndexOf(ListElement *t) const
{
	long i;
	for (i = 0; i < numItems; i++)
		if (t == items[i])
			return i+1;
	return 0;
}

void
CJList::Remove(ListElement *t)
{
	long i = IndexOf(t);
	if (i)
		DeleteItem(i);
}

void
CJList::BringFront(ListElement *t)
{
	long i = IndexOf(t);
	if (i)
		MoveTo(i, 1);
}

void
CJList::SendBack(ListElement *t)
{
	long i = IndexOf(t);
	if (i)
		MoveTo(i, numItems);
}

void
CJList::Append(ListElement *t)
{
	Insert(t, numItems+1);
}

void
CJList::InsertAfter(ListElement *t, ListElement *after)
{
	long i = IndexOf(after);
	if (i)
		Insert(t, i+1);
}

void
CJList::RemoveAll()
{
	numItems = 0;
	if (slots > blockSize)
		Resize(blockSize);
}


CJListIterator::CJListIterator(CJList *list)
{
	itsList = list;
	index = 1;
}

void
CJListIterator::Reset(void)
{
	index = 1;
}

ListElement *
CJListIterator::operator()(void)
{
	if (itsList && index <= itsList->GetNumItems())
		return itsList->NthItem(index++);
	return (ListElement *)0;
}
