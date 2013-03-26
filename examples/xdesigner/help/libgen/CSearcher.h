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
** sccsid = "@(#)helpGuru/libgen/CSearcher.h	1.2" -- 96/05/13
*/

/*
** CSearcher:
**
** A class which searches for text in a string.
**
** Jeremy Huxtable 1992
*/

#ifndef _H_CSearcher
#define _H_CSearcher

class CSearcher {
public:
	CSearcher(const char *aPattern, long aPatlength);
	~CSearcher();

	long TextContainsPattern(char *text, long textlen);

private:
	long patLength;
	char *pattern;
	long *back;
	int found;
	int index;

	void SetupBackPointers(void);
};

#endif
