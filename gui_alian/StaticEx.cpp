// StaticEx.cpp : implementation file
//

#include "stdafx.h"
#include "ICServingAgentClient.h"
#include "StaticEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStaticEx
CStaticEx::CStaticEx(CString strText, CRect rcFrame, int iType)
{
	m_pNextStatic = NULL;
	m_pPrevStatic = NULL;

	m_bExpand = TRUE;
	m_bShow = TRUE;
	m_bMouseTrack = TRUE;
	m_bHotTrack = TRUE;
	m_bHover = FALSE;
	
	m_pMemDC = NULL;
	m_pMemDC = new CDC;
	m_pMemBitmap = NULL;
	m_pMemBitmap = new CBitmap;
	
	VERIFY(fontDepart.CreateFont(
		13,                        // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_BOLD,                 // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		ANSI_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		"Verdana"));                 // lpszFacename
	
	VERIFY(fontAgent.CreateFont(
		13,                        // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_NORMAL,                 // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		ANSI_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		"Verdana"));                 // lpszFacename	
	
	CBitmap bm;
	bm.LoadBitmap(IDB_BMP_OUTDIAL_AGENT_CALL);
	brushBMP.CreatePatternBrush(&bm);
	brushBGHover.CreateSolidBrush(RGB(234, 245, 253));
	brushBG.CreateSolidBrush(RGB(255, 255, 255));
	penBG.CreatePen(PS_SOLID, 1, RGB(234, 245, 253));
	penBGNormal.CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	CBitmap bmFreeAgent,bmFreeDepart,bmFreeAgentNormal,bmFreeDepartNormal;
	bmFreeAgent.LoadBitmap(IDB_BMP_OUTDIAL_FREEAGENT);
	brushFreeAgent.CreatePatternBrush(&bmFreeAgent);
	bmFreeAgentNormal.LoadBitmap(IDB_BMP_OUTDIAL_FREEAGENT_NORMAL);
	brushFreeAgentNormal.CreatePatternBrush(&bmFreeAgentNormal);
	bmFreeDepart.LoadBitmap(IDB_BMP_OUTDIAL_FREEDEPART);
	brushFreeDepart.CreatePatternBrush(&bmFreeDepart);
	bmFreeDepartNormal.LoadBitmap(IDB_BMP_OUTDIAL_FREEDEPART_NORMAL);
	brushFreeDepartNormal.CreatePatternBrush(&bmFreeDepartNormal);

	m_rcFrame = rcFrame;
	m_strText = strText;
	SetStaticText(m_strText);
	m_iType = iType;
}

CStaticEx::~CStaticEx()
{
	fontDepart.DeleteObject();
	fontAgent.DeleteObject();
}


BEGIN_MESSAGE_MAP(CStaticEx, CStatic)
//{{AFX_MSG_MAP(CStaticEx)
ON_WM_MOUSEMOVE()
ON_WM_CREATE()
ON_WM_PAINT()
//}}AFX_MSG_MAP
ON_MESSAGE(WM_MOUSEHOVER, OnMouseHover)
ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStaticEx message handlers

void CStaticEx::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (m_bMouseTrack)    //若允许追踪，则。
	{
		TRACKMOUSEEVENT csTME;
		csTME.cbSize = sizeof(csTME);
		csTME.dwFlags = TME_LEAVE|TME_HOVER;
		csTME.hwndTrack = m_hWnd;//指定要追踪的窗口
		csTME.dwHoverTime = 10;  //鼠标在按钮上停留超过10ms，才认为状态为HOVER
		::_TrackMouseEvent(&csTME); //开启Windows的WM_MOUSELEAVE，WM_MOUSEHOVER事件支持
		m_bMouseTrack = FALSE;   //若已经追踪，则停止追踪
	}
	
	if (m_bHover) //鼠标离开static
	{ 
		CRect rc = CRect(0, 0, m_rcFrame.Width(), m_rcFrame.Height());
		if (!rc.PtInRect(point))
		{ 
			m_bHover = FALSE;
			Invalidate();
			::ReleaseCapture();
		}
	}
	else //鼠标在static上
	{ 
		m_bHover = TRUE;
		Invalidate();
		if (m_bHotTrack)
		{
			
		}
	}
	CRect rc(m_rcBtn);
	if (m_rcBtn.PtInRect(point))
	{
		m_bHoverBtn = TRUE;
		SetCapture();
		::SetCursor(::LoadCursor(NULL, MAKEINTRESOURCE(IDC_HAND)));
	}
	else
	{
		m_bHoverBtn = FALSE;
		::ReleaseCapture();
	}
	
	CStatic::OnMouseMove(nFlags, point);
}

int CStaticEx::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CStatic::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	return 0;
}
void CStaticEx::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	if (!m_pMemDC || !m_pMemDC->GetSafeHdc())
	{
		m_pMemDC->CreateCompatibleDC(&dc);
		///////////////////////////////////////////////////////////////////////////////////////
		if (m_iType == 1)
		{
			//m_rcLogo = CRect(0, 0, 20, 16);
			m_rcLogo = CRect(0, 0, 15, 13);
			m_rcLogo.OffsetRect(4, (m_rcFrame.Height() - 14) / 2);
		}
		else if (m_iType == 2)
		{
			//m_rcLogo = CRect(0, 0, 16, 20);
			//m_rcLogo.OffsetRect(2, (m_rcFrame.Height() - 20) / 2);
			m_rcLogo = CRect(0, 0, 0, 0);
		}
		CSize size = m_pMemDC->GetTextExtent(m_strName);
		m_rcText = CRect(0, 0, size.cx, m_rcFrame.Height());
		m_rcText.OffsetRect(m_rcLogo.right + 4, 0);
		
	//	m_rcBtn = CRect(0, 0, 23, 22);
		m_rcBtn = CRect(0, 0, 18, 18);
		m_rcBtn.OffsetRect(m_rcText.right + 4, (m_rcFrame.Height() - 17) / 2 - 1);
		
		if (m_iType == 2)
			m_rcFrame.InflateRect(0, 0, m_rcBtn.right + 4 - m_rcFrame.Width(), 0);
		///////////////////////////////////////////////////////////////////////////////////////
	}
	if (!m_pMemBitmap || !m_pMemBitmap->GetSafeHandle())
		m_pMemBitmap->CreateCompatibleBitmap(&dc, m_rcFrame.Width(), m_rcFrame.Height());
	
	CBitmap *pOldBitmap = m_pMemDC->SelectObject(m_pMemBitmap);
	
	m_pMemDC->SetBkMode(TRANSPARENT);
	m_pMemDC->SetMapMode(MM_TEXT);
	
	CPen *pOldPen, Pen;
	CBrush *pOldBrush, Brush;
	
	CFont *pOldFont;
	if (m_iType == 1)
	{	
		pOldFont = m_pMemDC->SelectObject(&fontDepart);
	}
	else
	{
		pOldFont = m_pMemDC->SelectObject(&fontAgent);
	}
	
	if (m_bHover)  //鼠标在static上
	{
		Pen.CreatePen(PS_DOT, 1, RGB(128, 128, 128));
		pOldPen = m_pMemDC->SelectObject(&Pen);
		pOldBrush = m_pMemDC->SelectObject(&brushBGHover);
		
		m_pMemDC->RoundRect(0, 0, m_rcFrame.Width(), m_rcFrame.Height(), 5, 5);		
		m_pMemDC->SelectObject(pOldBrush);
		m_pMemDC->SelectObject(pOldPen);
		
		pOldPen = m_pMemDC->SelectObject(&penBG);
		
		if (m_iType == 1) //图片大小 20*16
		{
			//鼠标在static上，画技能组logo
			pOldBrush = m_pMemDC->SelectObject(&brushFreeDepart);
			POINT pt;
			SetBrushOrgEx(m_pMemDC->GetSafeHdc(), m_rcLogo.left + 1, m_rcLogo.top + 1, &pt);
			m_pMemDC->Rectangle(m_rcLogo.left, m_rcLogo.top, m_rcLogo.right + 1, m_rcLogo.bottom + 1);
			SetBrushOrgEx(m_pMemDC->GetSafeHdc(), pt.x, pt.y, NULL);
			m_pMemDC->SelectObject(pOldBrush);
		}
		else if (m_iType == 2) //图片大小 16*20
		{		
//			pOldBrush = m_pMemDC->SelectObject(&brushFreeAgent);
//			POINT pt;
//			SetBrushOrgEx(m_pMemDC->GetSafeHdc(), 2, m_rcFrame.Height() / 2 - 10, &pt);
//			m_pMemDC->Rectangle(2, m_rcFrame.Height() / 2 - 11, 18, m_rcFrame.Height() / 2 + 11);
//			SetBrushOrgEx(m_pMemDC->GetSafeHdc(), pt.x, pt.y, NULL);
//			m_pMemDC->SelectObject(pOldBrush);
		}
		
		//鼠标在static上，画外呼图标
		pOldBrush = m_pMemDC->SelectObject(&brushBMP);
		POINT pt;
		SetBrushOrgEx(m_pMemDC->GetSafeHdc(), m_rcBtn.left + 1, m_rcBtn.top + 1, &pt);
		m_pMemDC->Rectangle(m_rcBtn.left, m_rcBtn.top, m_rcBtn.right + 1, m_rcBtn.bottom + 1);
		SetBrushOrgEx(m_pMemDC->GetSafeHdc(), pt.x, pt.y, NULL);
		m_pMemDC->SelectObject(pOldBrush);
		m_pMemDC->SelectObject(pOldPen);
	}
	else  //鼠标移出static
	{
		//鼠标未在static上，画白色圆角边线
		Pen.CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
		pOldPen = m_pMemDC->SelectObject(&Pen);
		pOldBrush = m_pMemDC->SelectObject(&brushBG);
		m_pMemDC->Rectangle(0, 0, m_rcFrame.Width(), m_rcFrame.Height());
		m_pMemDC->SelectObject(pOldBrush);
		m_pMemDC->SelectObject(pOldPen);
		
		if (m_iType == 1)
		{
			//鼠标未在static上，贴技能组logo图
			pOldPen = m_pMemDC->SelectObject(&penBGNormal);
			pOldBrush = m_pMemDC->SelectObject(&brushFreeDepartNormal);
			POINT pt;
			SetBrushOrgEx(m_pMemDC->GetSafeHdc(), m_rcLogo.left + 1, m_rcLogo.top + 1, &pt);
			m_pMemDC->Rectangle(m_rcLogo.left, m_rcLogo.top, m_rcLogo.right + 1, m_rcLogo.bottom + 1);
			SetBrushOrgEx(m_pMemDC->GetSafeHdc(), pt.x, pt.y, NULL);
			m_pMemDC->SelectObject(pOldBrush);
			m_pMemDC->SelectObject(pOldPen);

			//鼠标未在static上，画技能组底线
			CPen Pen(PS_SOLID, 1, RGB(215, 222, 233));
			pOldPen = m_pMemDC->SelectObject(&Pen);
			m_pMemDC->MoveTo(2, m_rcFrame.Height() - 2);
			m_pMemDC->LineTo(m_rcFrame.Width() - 2, m_rcFrame.Height() - 2);
			m_pMemDC->SelectObject(pOldPen);
		}
		else if (m_iType == 2)
		{
//			pOldPen = m_pMemDC->SelectObject(&penBGNormal);
//			pOldBrush = m_pMemDC->SelectObject(&brushFreeAgentNormal);
//			POINT pt;
//			SetBrushOrgEx(m_pMemDC->GetSafeHdc(), 2, m_rcFrame.Height() / 2 - 10, &pt);
//			m_pMemDC->Rectangle(2, m_rcFrame.Height() / 2 - 11, 18, m_rcFrame.Height() / 2 + 11);
//			SetBrushOrgEx(m_pMemDC->GetSafeHdc(), pt.x, pt.y, NULL);
//			m_pMemDC->SelectObject(pOldBrush);
//			m_pMemDC->SelectObject(pOldPen);
		}
	}
	
	if (m_iType == 1)
	{
		CPen Pen, *pOldPen;
		Pen.CreatePen(PS_SOLID, 1, RGB(1, 1, 1));
		pOldPen = m_pMemDC->SelectObject(&Pen);
		if (!m_bExpand)    //收拢，向下的两个三角箭头
		{
			m_pMemDC->MoveTo(m_rcFrame.Width() - 7 - 2, m_rcFrame.Height() / 2 - 2);
			m_pMemDC->LineTo(m_rcFrame.Width() - 7, m_rcFrame.Height() / 2);
			m_pMemDC->LineTo(m_rcFrame.Width() - 7 + 3, m_rcFrame.Height() / 2 - 3);
			
			m_pMemDC->MoveTo(m_rcFrame.Width() - 7 - 2, m_rcFrame.Height() / 2);
			m_pMemDC->LineTo(m_rcFrame.Width() - 7, m_rcFrame.Height() / 2 + 2 );
			m_pMemDC->LineTo(m_rcFrame.Width() - 7 + 3, m_rcFrame.Height() / 2 - 1);
		}
		else				//展开，向上的两个三角箭头
		{
			m_pMemDC->MoveTo(m_rcFrame.Width() - 7 - 2, m_rcFrame.Height() / 2);
			m_pMemDC->LineTo(m_rcFrame.Width() - 7, m_rcFrame.Height() / 2 - 2);
			m_pMemDC->LineTo(m_rcFrame.Width() - 7 + 3, m_rcFrame.Height() / 2 + 1);
			
			m_pMemDC->MoveTo(m_rcFrame.Width() - 7 - 2, m_rcFrame.Height() / 2 + 2);
			m_pMemDC->LineTo(m_rcFrame.Width() - 7, m_rcFrame.Height() / 2);
			m_pMemDC->LineTo(m_rcFrame.Width() - 7 + 3, m_rcFrame.Height() / 2 + 3);
		}
		m_pMemDC->SelectObject(pOldPen);
	}
	if (m_iType == 1) 
	{
		m_pMemDC->SetTextColor(RGB(68, 91, 114));
		m_pMemDC->DrawText(m_strName, m_rcText, DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);	
	}
	else if (m_iType == 2) 
	{
		m_pMemDC->SetTextColor(RGB(43, 49, 72));
		m_pMemDC->DrawText(m_strName, m_rcText, DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);
	}

	dc.BitBlt(0, 0, m_rcFrame.Width(), m_rcFrame.Height(), m_pMemDC, 0, 0, SRCCOPY);
	m_pMemDC->SelectObject(pOldBitmap);
	m_pMemDC->SelectObject(pOldFont);
	
	// Do not call CStatic::OnPaint() for painting messages
}

LRESULT CStaticEx::OnMouseHover(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

LRESULT CStaticEx::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	m_bHover = FALSE;
	m_bMouseTrack=TRUE;
	
	Invalidate();
	::ReleaseCapture();
	
	return 0;
}


void CStaticEx::PreSubclassWindow()
{ 
	DWORD dwStyle = this->GetStyle();
	::SetWindowLong(this->GetSafeHwnd(), GWL_STYLE, dwStyle | SS_NOTIFY);
	
	CStatic::PreSubclassWindow();
}

void CStaticEx::Move(CRect &rc, BOOL bRedraw)
{
	m_rcFrame = rc;
	MoveWindow(rc);
	if (bRedraw)
	{	
		ShowWindow(SW_SHOW);
	}
	else
	{
		ShowWindow(SW_HIDE);
	}
	Invalidate();
}

BOOL CStaticEx::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_LBUTTONDOWN)
	{
		if (m_iType != 1 && !m_bHoverBtn)
			return TRUE;
		
		if (m_iType == 1 && m_bHoverBtn)
		{
			GetParent()->PostMessage(WM_MY_DEPARTS_CLICKED, (WPARAM)(LPCTSTR)m_strName);
			return TRUE;
		}
		Invalidate();
	}
	
	return CStatic::PreTranslateMessage(pMsg);
}

void CStaticEx::SetStaticShow(BOOL bShow)
{
	m_bShow = bShow;
}

BOOL CStaticEx::GetStaticShow()
{
	return m_bShow;
}

void CStaticEx::SetStaticText(CString strText)
{
	m_strText = strText;
	string stemp = strText;
	int iFind1 = stemp.find_first_of("(", 0);
	int iFind2 = stemp.find_last_of(")", -1);
	if (iFind1 != string::npos && iFind2 != string::npos)
	{
		int iFind = strText.Find("(");
		if (iFind != -1)
			m_strAccount = strText.Left(iFind);
		
		string str = stemp.substr(iFind1 + 1, iFind2 - iFind1 - 1);
		if (str != "")
		{
			m_strName = str.c_str();
			if(m_strName.GetLength()>8)
			{
              m_strName=m_strName.Left(8)+"...";
			}
		}
		else
		{
			m_strName = m_strAccount;
			if(m_strName.GetLength()>8)
			{
				m_strName=m_strName.Left(8)+"...";
			}
		}
	}
	else
	{
		m_strName = m_strAccount = m_strText;
	}
}