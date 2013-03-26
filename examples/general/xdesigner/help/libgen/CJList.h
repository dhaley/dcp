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
** sccsid = "@(#)helpGuru/libgen/CJList.h	1.1" -- 95/12/13
*/

/*
** CJList:
**
** A class implementing a simple list.
**
** Jeremy Huxtable 1991
*/

#ifndef _H_CJList
#define _H_CJList

typedef void ListElement;

class CJList {

	friend class CJListIterator;

protected:
	long blockSize;
	long slots;
	long numItems;
	ListElement **items;

public:
	/* Creation/Copying */
	CJList();
	CJList(const CJList &aList);
	virtual ~CJList();

	/* Access */
	virtual void AppendList(CJList *list);
	CJList&	operator+=(CJList* list) { AppendList(list); return *this; }
	CJList&	operator+=(ListElement* t) { Append(t); return *this; }
	CJList&	operator-=(ListElement* t) { Remove(t); return *this; }

	/* Miscellaneous */
	ListElement *NthItem(long n) const;
	ListElement *&operator[](long index) const { return items[index]; }

	void RemoveAll(void);

	ListElement *FirstItem(void) { return NthItem(1); }
	ListElement *LastItem(void) { return NthItem(numItems); }
	long GetNumItems(void) { return numItems; }
	void SetNumItems(long n) { numItems = n; }
	int IsEmpty(void) const { return numItems == 0; }

	void Store(ListElement *t, long index);

	virtual void Insert(ListElement *t, long index);
	virtual void DeleteItem(long index);
	virtual void Append(ListElement *t);
	virtual void Prepend(ListElement *t);
	virtual void Remove(ListElement *t);
	virtual void InsertAfter(ListElement *t, ListElement *after);
	virtual void BringFront(ListElement *t);
	virtual void SendBack(ListElement *t);

	void MoveTo(long from, long to);
	long IndexOf(ListElement *t) const;

private:
	void Resize(long numSlots);
};

class CJListIterator {
private:
	CJList *itsList;
	int index;

public:
	CJListIterator(CJList *list);

	void Reset(void);
	ListElement *operator()();
};

#endif
