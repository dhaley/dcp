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
static char *sccsid = {"@(#)helpGuru/libgen/CSearcher.cxx	1.2"} ; /* 96/05/07 */
#endif /* lint && NOSCCS */

/*
** CSearcher:
**
** A class which searches for text in a string.
**
** Jeremy Huxtable 1992
*/

#include <string.h>
#include "CSearcher.h"

/*
** Boyer-Moore string searching algorithm.
*/
CSearcher::CSearcher(const char *aPattern, long aPatlength)
{
	patLength = aPatlength;
	pattern = new char[patLength];
	back = new long[patLength+1];
	strncpy(pattern, aPattern, patLength);
	SetupBackPointers();
}

CSearcher::~CSearcher(void)
{
	delete [] pattern;
	delete [] back;
}

void
CSearcher::SetupBackPointers(void)
{
	long i = 0;
	long j = -1;

	back[0] = 0;
	do {
		if (j < 0 || pattern[i] == pattern[j])
			back[++i] = ++j + 1;
		else
			j = back[j] - 1;
	} while (i < patLength);
}

long
CSearcher::TextContainsPattern(char *text, long textlen)
{
	long i = 0, j = 0;

	do {
		if (j < 0 || text[i] == pattern[j]) {
			i++;
			j++;
		} else
			j = back[j] - 1;
	} while (j < patLength && i < textlen);
	return j >= patLength;
}

