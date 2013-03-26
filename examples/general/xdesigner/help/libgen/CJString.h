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
** sccsid = "@(#)helpGuru/libgen/CJString.h	1.2" -- 96/01/08
*/

/*
** CJString:
**
** A simple variable-length String class
**
** Jeremy Huxtable 1992
*/

#ifndef _H_CJString
#define _H_CJString

class CJString {
public:
	char *data;
	int length;

	/* Construction */
	CJString(void);
	CJString(const char *s);
	CJString(const char *s, int aLength);
	CJString(const CJString &s);
	CJString(int aNumber ) ;
	virtual ~CJString(void);

	virtual void SetText(const char *s);
	virtual void SetText(const char *s, int aLength);
	
	virtual void GetSubstring(int first, int last, CJString &subString) const;
	virtual void ReplaceText(int first, int last, const char *text, int textLength);
	virtual void GetText(int first, int last, char *text) const;
	virtual char *GetData(void) const;
	virtual int GetLength(void) const;
	void SetLength(int newLength) { Resize(newLength); }

	/* Operators */
	virtual operator char*() const;

	CJString& operator=(const CJString& s);

	CJString& operator+=(char c);
	CJString& operator+=(const char *s);
	CJString& operator+=(const CJString& s) { return operator+=(s.GetData());}

	int operator==(const char* s) const;
	int operator!=(const char* s) const { return !operator==(s); }
	int operator< (const char* s) const;
	int operator> (const char* s) const;
	int operator<=(const char* s) const { return !operator>(s); }
	int operator>=(const char* s) const { return !operator<(s); }

	int operator==(const CJString& s) const { return  operator==(s.GetData()); }
	int operator!=(const CJString& s) const { return !operator==(s.GetData()); }
	int operator< (const CJString& s) const { return  operator< (s.GetData()); }
	int operator> (const CJString& s) const { return  operator> (s.GetData()); }
	int operator<=(const CJString& s) const { return !operator> (s.GetData()); }
	int operator>=(const CJString& s) const { return !operator< (s.GetData()); }

	char operator[](int index) const { return data[index]; }
	char& operator[](int index);

	int Find(char c, int start = 0);

	virtual int Resize(int length);
};

#endif
