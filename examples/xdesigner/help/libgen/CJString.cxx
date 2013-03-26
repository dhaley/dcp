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
static char *sccsid = {"@(#)helpGuru/libgen/CJString.cxx	1.3"} ; /* 96/01/19 */
#endif /* lint && NOSCCS */

/*
** CJString:
**
** A simple variable-length String class
**
** Jeremy Huxtable 1992
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "CJString.h"

#ifndef TRUE
#define TRUE	1
#define FALSE	0
#endif

CJString::CJString(void)
{
	data = 0;
	length = 0;
}

CJString::CJString(const CJString &s)
{
	data = 0;
	length = 0;
	SetText(s.GetData());
}

CJString::CJString(const char *s)
{
	data = 0;
	length = 0;
	SetText(s);
}

CJString::CJString(const char *s, int aLength)
{
	data = 0;
	length = 0;
	SetText(s, aLength);
}

CJString::CJString( int aNumber )
{
    data = 0 ;
    length = 0 ;
    char *tmp = new char[128] ;
    sprintf( tmp, "%d", aNumber ) ;
    SetText( tmp ) ;
    delete tmp ;
}

CJString::~CJString(void)
{
	if (data)
		free(data);
}

void
CJString::SetText(const char *s)
{
	if (s && Resize(strlen(s)))
		strcpy(data, s);
}

void
CJString::SetText(const char *s, int aLength)
{
	if (s && Resize(aLength))
		strncpy(data, s, aLength);
}

void
CJString::GetSubstring(int first, int last, CJString &subString) const
{
	subString.ReplaceText(0, subString.GetLength(), data+first, last-first);
}

void
CJString::GetText(int first, int last, char *text) const
{
	int i = 0;
	while (first <= last)
		text[i++] = data[first++];
}

void
CJString::ReplaceText(int first, int last, const char *text, int textLength)
{
	int oldLength = length;
	int delta;

	delta = textLength - (last - first);
	length += delta;
	if (!data) {
		Resize(length);
		first = last = 0;
		data[length] = 0;
		delta = 0;
	}
	if (delta > 0) {
		Resize(length);
		memmove(data+first+delta, data+first, oldLength-first+1);
	} else if (delta < 0) {
		memmove(data+first, data+first-delta, oldLength-first+delta+1);
		Resize(length);
	}
	memmove(data+first, text, textLength);
}

CJString&
CJString::operator+=(const char* s)
{
	ReplaceText(length, length, s, strlen(s));
	return *this;
}

CJString&
CJString::operator+=(char c)
{
	char ch = c;
	ReplaceText(length, length, &ch, 1);
	return *this;
}

char&
CJString::operator[](int i)
{
	if (i > length)
		Resize(i);
	return data[i];
}

int
CJString::operator==(const char *s) const
{
	return strcmp(data, s) == 0;
}

int
CJString::operator<(const char *s) const
{
	return strcmp(data, s) < 0;
}

int
CJString::operator>(const char *s) const
{
	return strcmp(data, s) > 0;
}

int
CJString::Resize(int newLength)
{
	char *newData = data ? (char *)realloc(data, newLength+1) : (char *)malloc(newLength+1);
	if (newData) {
		data = newData;
		length = newLength;
		data[length] = 0;
		return TRUE;
	}
	return FALSE;
}

char *
CJString::GetData(void) const
{
	return data;
}

int
CJString::GetLength(void) const
{
	return length;
}

CJString::operator char*() const
{
	return GetData();
}

int
CJString::Find(char c, int start)
{
	char *p = data+start;
	while (*p && *p != c)
		p++;
	return *p ? p-data : -1;
}

CJString&
CJString::operator=(const CJString& s)
{
	if (&s != this)
		ReplaceText(0, GetLength(), s.data, s.length);
	return *this;
}

