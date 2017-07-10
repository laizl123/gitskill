// XPBitmapButton.cpp : implementation file
//

#include "stdafx.h"
#include "XPBitmapButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXPBitmapButton

CXPBitmapButton::CXPBitmapButton()
{
	m_bOver = FALSE;
	m_bTracking = FALSE;
	m_clrBack = RGB(255, 255, 255);
	memset(m_aBitmap, sizeof(m_aBitmap), 0); 
}

CXPBitmapButton::~CXPBitmapButton()
{
	int nSize = sizeof(m_aBitmap)/sizeof(HBITMAP);
	for(int i = 1; i < nSize; i++)
	{
		if(m_aBitmap[i] != m_aBitmap[0] && m_aBitmap[i] != NULL)
		{
			DeleteObject(m_aBitmap[i]);
			m_aBitmap[i] = NULL;
		}
	}
	if(m_aBitmap[0] != NULL)
	{
		DeleteObject(m_aBitmap[0]);
		m_aBitmap[0] = NULL;
	}
}

void CXPBitmapButton::LoadBitmaps(HBITMAP hBmpLeave, 
				 HBITMAP hBmpHover/* = NULL*/, 
				 HBITMAP hBmpClick/* = NULL*/, 
				 HBITMAP hBmpDisable/* = NULL*/)
{
	int nSize = sizeof(m_aBitmap)/sizeof(HBITMAP);
	for(int i = 1; i < nSize; i++)
	{
		if(m_aBitmap[i] != m_aBitmap[0] && m_aBitmap[i] != NULL)
		{
			DeleteObject(m_aBitmap[i]);
			m_aBitmap[i] = NULL;
		}
	}
	if(m_aBitmap[0] != NULL)
	{
		DeleteObject(m_aBitmap[0]);
		m_aBitmap[0] = NULL;
	}
	ASSERT(hBmpLeave != NULL);

	m_aBitmap[0] = hBmpLeave;

	if(hBmpHover != NULL)
		m_aBitmap[1] = hBmpHover;
	else
		m_aBitmap[1] = hBmpLeave;

	if(hBmpClick != NULL)
		m_aBitmap[2] = hBmpClick;
	else
		m_aBitmap[2] = hBmpLeave;

	if(hBmpDisable != NULL)
		m_aBitmap[3] = hBmpDisable;
	else
		m_aBitmap[3] = hBmpLeave;

}

void CXPBitmapButton::LoadBitmaps(UINT nIDBmpLeave, UINT nIDBmpHover, UINT nIDBmpClick, UINT nIDBmpDisable)
{
	int nSize = sizeof(m_aBitmap)/sizeof(HBITMAP);
	for(int i = 1; i < nSize; i++)
	{
		if(m_aBitmap[i] != m_aBitmap[0] && m_aBitmap[i] != NULL)
		{
			DeleteObject(m_aBitmap[i]);
			m_aBitmap[i] = NULL;
		}
	}
	if(m_aBitmap[0] != NULL)
	{
		DeleteObject(m_aBitmap[0]);
		m_aBitmap[0] = NULL;
	}

	ASSERT(nIDBmpLeave != 0);
	m_aBitmap[0] = LoadBitmap(::AfxGetInstanceHandle(), MAKEINTRESOURCE(nIDBmpLeave));
	if(nIDBmpHover != 0)
	{
		m_aBitmap[1] = LoadBitmap(::AfxGetInstanceHandle(), MAKEINTRESOURCE(nIDBmpHover));
	}
	if(m_aBitmap[1] == NULL)
	{
		m_aBitmap[1] = m_aBitmap[0];
	}
	//
	if(nIDBmpClick != 0)
	{
		m_aBitmap[2] = LoadBitmap(::AfxGetInstanceHandle(), MAKEINTRESOURCE(nIDBmpClick));
	}
	if(m_aBitmap[2] == NULL)
	{
		m_aBitmap[2] = m_aBitmap[0];
	}
	//
	if(nIDBmpDisable != 0)
	{
		m_aBitmap[3] = LoadBitmap(::AfxGetInstanceHandle(), MAKEINTRESOURCE(nIDBmpDisable));
	}
	if(m_aBitmap[3] == NULL)
	{
		m_aBitmap[3] = m_aBitmap[0];
	}
}	

void CXPBitmapButton::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (!m_bTracking)
	{
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(tme);
		tme.hwndTrack = m_hWnd;
		tme.dwFlags = TME_LEAVE | TME_HOVER;
		tme.dwHoverTime = 1;
		m_bTracking = _TrackMouseEvent(&tme);
	}
	
	CButton::OnMouseMove(nFlags, point);
}

LRESULT CXPBitmapButton::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	m_bOver = FALSE;
	m_bTracking = FALSE;
	InvalidateRect(NULL, FALSE);
	return 0;
}

LRESULT CXPBitmapButton::OnMouseHover(WPARAM wParam, LPARAM lParam)
{
	m_bOver = TRUE;
	InvalidateRect(NULL);
	return 0;
}

BEGIN_MESSAGE_MAP(CXPBitmapButton, CButton)
	//{{AFX_MSG_MAP(CXPBitmapButton)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_MESSAGE(WM_MOUSEHOVER, OnMouseHover)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXPBitmapButton message handlers

void CXPBitmapButton::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class	
	CButton::PreSubclassWindow();
	ModifyStyle(0, BS_OWNERDRAW);
}

void CXPBitmapButton::SetBkColor(COLORREF clr)
{
	m_clrBack = clr;
}


void CXPBitmapButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your code to draw the specified item
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	UINT state = lpDrawItemStruct->itemState;

	HBITMAP bitmapNow = NULL;
	if (state & ODS_DISABLED)
	{
		bitmapNow = m_aBitmap[3];	
	}
	else if(state & ODS_SELECTED)
	{
		bitmapNow = m_aBitmap[2];	
	}
	else if(m_bOver == TRUE)
	{
		bitmapNow = m_aBitmap[1];	
	}
	else
	{
		bitmapNow = m_aBitmap[0];	
	}
	// 填充背景
	CRect rcCtrl;
	GetClientRect(&rcCtrl);
	pDC->FillSolidRect(rcCtrl, m_clrBack);
	// 绘制图标
	if(bitmapNow != NULL)
	{
		BITMAP info;
		GetObject(bitmapNow, sizeof(info), &info);
		// 计算起点
		int nXBgn = rcCtrl.CenterPoint().x - info.bmWidth/2;
		int nYBgn = rcCtrl.CenterPoint().y - info.bmHeight/2;
		HDC hDCNow = ::CreateCompatibleDC(pDC->m_hDC);
		SelectObject(hDCNow, bitmapNow);
		BitBlt(pDC->m_hDC, nXBgn, nYBgn, info.bmWidth, info.bmHeight, hDCNow, 0, 0, SRCCOPY);		
		DeleteDC(hDCNow);		
	}
}
