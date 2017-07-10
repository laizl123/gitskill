// BkDialog.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "BkDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CBkDialog::CBkDialog(CWnd* pParent /*=NULL*/)
{
	//{{AFX_DATA_INIT(CBkDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


CBkDialog::CBkDialog(UINT uResourceID, CWnd* pParent)
	: CDialog(uResourceID, pParent)
{
}


CBkDialog::CBkDialog(LPCTSTR pszResourceID, CWnd* pParent)
	: CDialog(pszResourceID, pParent)
{
}


CBkDialog::~CBkDialog()
{
}


void CBkDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBkDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBkDialog, CDialog)
	//{{AFX_MSG_MAP(CBkDialog)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL CBkDialog::OnEraseBkgnd(CDC* pDC) 
{
	CRect rc;

	GetClientRect(rc);

	m_pDC = pDC;

	if (TileBitmap(pDC, rc) == TRUE)
		return TRUE;
	else
		return CDialog::OnEraseBkgnd(pDC);
} // End of OnEraseBkgnd


LRESULT CBkDialog::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
    LRESULT lrst=CDialog::DefWindowProc(message, wParam, lParam);
    
    if (!::IsWindow(m_hWnd))
        return lrst;
    
    if (message==WM_MOVE||message==WM_PAINT||message==WM_NCPAINT||message==WM_NCACTIVATE ||message == WM_NOTIFY)
    {
        CDC* pWinDC = GetWindowDC();
        if (pWinDC)
            DrawBorder(pWinDC);
        ReleaseDC(pWinDC);
    }
    return lrst;
    
    return CDialog::DefWindowProc(message, wParam, lParam);
}

// ÖØ»­±ß¿òµÄ¾ßÌå´úÂë
void CBkDialog::DrawBorder(CDC *pDC)
{
    if (m_hWnd )
    {
		CBrush Brush(RGB(113, 111, 100));
//		CBrush Brush(RGB(245, 245, 245));
        CBrush* pOldBrush = pDC->SelectObject(&Brush);
		CBrush bottombrush(RGB(145,155,156));
		CBrush shadebrush(RGB(222, 222, 222));
        CRect rtWnd;
        GetWindowRect(&rtWnd); 
        
        CPoint point;
/*
        //Ìî³ä¶¥²¿¿ò¼Ü
        point.x = rtWnd.Width();
        point.y = GetSystemMetrics(SM_CYFRAME)+1;
        pDC->PatBlt(0, 0, point.x, point.y, PATCOPY);
        //Ìî³ä×ó²à¿ò¼Ü
        point.x = GetSystemMetrics(SM_CXFRAME);
        point.y = rtWnd.Height();
        pDC->PatBlt(0, 0, point.x, point.y, PATCOPY);
        //Ìî³äµ×²¿¿ò¼Ü
        point.x = rtWnd.Width(); 
        point.y = GetSystemMetrics(SM_CYFRAME) + 1;
        pDC->PatBlt(0, rtWnd.Height()-point.y, point.x, point.y, PATCOPY);
        //Ìî³äÓÒ²à¿ò¼Ü
        point.x = GetSystemMetrics(SM_CXFRAME);
        point.y = rtWnd.Height();
        pDC->PatBlt(rtWnd.Width()-point.x, 0, point.x, point.y, PATCOPY);
*/
		//Ìî³ä¶¥²¿¿ò¼Ü
        point.x = rtWnd.Width();
        point.y = GetSystemMetrics(SM_CYFRAME)-3;
        pDC->PatBlt(0, 0, point.x, point.y, PATCOPY);
        //Ìî³ä×ó²à¿ò¼Ü
        point.x = GetSystemMetrics(SM_CXFRAME)-3;
        point.y = rtWnd.Height();
        pDC->PatBlt(0, 0, point.x, point.y, PATCOPY);
        //Ìî³äµ×²¿¿ò¼Ü
		point.x = rtWnd.Width(); 
        point.y = GetSystemMetrics(SM_CYFRAME)-3;
        pDC->PatBlt(0, rtWnd.Height()-point.y, point.x, point.y, PATCOPY);
        //Ìî³äÓÒ²à¿ò¼Ü
        point.x = GetSystemMetrics(SM_CXFRAME)-3;
        point.y = rtWnd.Height();
        pDC->PatBlt(rtWnd.Width()-point.x, 0, point.x, point.y, PATCOPY);
	/*	
		pDC->SelectObject(pOldBrush);
		pOldBrush = pDC->SelectObject(&bottombrush);

        //Ìî³äµ×²¿¿ò¼Ü
		point.x = rtWnd.Width(); 
        point.y = GetSystemMetrics(SM_CYFRAME)-3;
        pDC->PatBlt(0, rtWnd.Height()-point.y - 1, point.x, point.y, PATCOPY);
        //Ìî³äÓÒ²à¿ò¼Ü
        point.x = GetSystemMetrics(SM_CXFRAME)-3;
        point.y = rtWnd.Height();
        pDC->PatBlt(rtWnd.Width()-point.x - 1, 0, point.x, point.y, PATCOPY);

		pDC->SelectObject(pOldBrush);
		pOldBrush = pDC->SelectObject(&shadebrush);

        //Ìî³äµ×²¿¿ò¼Ü
		point.x = rtWnd.Width(); 
        point.y = GetSystemMetrics(SM_CYFRAME)-3;
        pDC->PatBlt(0, rtWnd.Height()-point.y, point.x, point.y, PATCOPY);
        //Ìî³äÓÒ²à¿ò¼Ü
        point.x = GetSystemMetrics(SM_CXFRAME)-3;
        point.y = rtWnd.Height();
        pDC->PatBlt(rtWnd.Width()-point.x, 0, point.x, point.y, PATCOPY);
*/		
    }
}
