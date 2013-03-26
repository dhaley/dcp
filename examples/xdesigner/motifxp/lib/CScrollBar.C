#include <Xm/Xm.h>
#include <Xm/ScrollBar.h>
#include <xdclass.h>

int CScrollBar::GetScrollPos(void) const
{
    if (_xd_rootwidget != NULL)
    {
	int value = 0 ;

	XtVaGetValues(_xd_rootwidget, XmNvalue, &value, NULL);

	return value;
    }

    return 0;
}

void CScrollBar::GetScrollRange(LPINT lpMinPos, LPINT lpMaxPos) const
{
    int minpos=0, maxpos=0;

    if (_xd_rootwidget != NULL)
	XtVaGetValues(_xd_rootwidget, XmNminimum, &minpos, XmNmaximum, &maxpos, NULL);

    *lpMinPos = minpos;
    *lpMaxPos = maxpos;
}

int CScrollBar::SetScrollPos(int nPos, BOOL)
{
    if (_xd_rootwidget != NULL)
    {
	int oldpos = 0 ;

	XtVaGetValues(_xd_rootwidget, XmNvalue, &oldpos, NULL);
	XtVaSetValues(_xd_rootwidget, XmNvalue, nPos, NULL);

	return oldpos;
    }

    return 0;
}

void CScrollBar::SetScrollRange(int nMinPos, int nMaxPos, BOOL)
{
    if (_xd_rootwidget != NULL)
	XtVaSetValues(_xd_rootwidget, XmNminimum, nMinPos, XmNmaximum, nMaxPos, NULL);
}

void CScrollBar::ShowScrollBar(BOOL bShow)
{
    if (_xd_rootwidget != NULL)
	if (bShow)
	    XtManageChild(_xd_rootwidget);
	else
	    XtUnmanageChild(_xd_rootwidget);
}
