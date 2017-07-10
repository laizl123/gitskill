// VTabCtrl.cpp : implementation file
//

#include "stdafx.h"

#include "VTabCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVTabCtrl

CVTabCtrl::CVTabCtrl()
{
	m_ImageList.Create(16,16,ILC_COLOR24|ILC_MASK,1,0);
}

CVTabCtrl::~CVTabCtrl()
{

}


BEGIN_MESSAGE_MAP(CVTabCtrl, CTabCtrl)
	//{{AFX_MSG_MAP(CVTabCtrl)
	ON_NOTIFY_REFLECT(TCN_SELCHANGE, OnSelchange)
	ON_NOTIFY_REFLECT(TCN_SELCHANGING, OnSelchanging)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVTabCtrl message handlers

int CVTabCtrl::AddTabPage(LPCSTR pszTitle, int nPageID, UINT nTemplateID, UINT nIconID)
{

	ASSERT(pszTitle!=NULL);
	ASSERT(nPageID >= 0);
	ASSERT(nTemplateID >0 );

	CVTabPageEx* pTabPage = new CVTabPageEx();
	ASSERT(pTabPage);

	if(!pTabPage->Create(nTemplateID, this))
	{
		delete pTabPage;
		return -1;
	}

	return AddTabPage(pszTitle, nPageID, pTabPage, nIconID);
}

int CVTabCtrl::AddTabPage(LPCTSTR pszTitle, int nPageID, CVTabPageEx *pTabPage, UINT nIconID)
{
	ASSERT(pszTitle!=NULL);
	ASSERT(nPageID >= 0);
	ASSERT(pTabPage != NULL );


	SetImageList(&m_ImageList);

	int iImage = -1;
	if(nIconID > 0)
		iImage = m_ImageList.Add(LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(nIconID)));

	TCITEM tcItem;
	tcItem.mask = iImage==-1?TCIF_TEXT:TCIF_IMAGE|TCIF_TEXT;
	tcItem.pszText = (LPTSTR)pszTitle;
	tcItem.iImage = iImage;
	
	if(InsertItem(nPageID,&tcItem) == -1)
		return -1;

	int nIndex = m_arTabPage.Add(pTabPage);
	if(nIndex == 0)
		pTabPage->ShowWindow(SW_SHOW);


	CRect rect;
	GetClientRect (&rect);
	
	if (rect.Width () > 0 && rect.Height () > 0)
		ResizeDialog (nPageID, rect.Width (), rect.Height ());

	return 0;
}


void CVTabCtrl::OnSelchange(NMHDR* pNMHDR, LRESULT* pResult) 
{
//	NM_TREEVIEW
	int nIndex = GetCurSel ();
	if (nIndex == -1)
		return;
	CVTabPageEx* pTabPage = m_arTabPage.GetAt(nIndex);
	ASSERT(pTabPage);
	pTabPage->ShowWindow(SW_SHOW);
	
	
//	::SetFocus (m_hFocusWnd[nIndex]);
	CRect rect;
	GetClientRect (&rect);
	ResizeDialog (nIndex, rect.Width (), rect.Height ());
	pTabPage->ShowWindow (SW_SHOW);
	
	*pResult = 0;
}

void CVTabCtrl::ResizeAll()
{
	CRect rect;
	GetClientRect (&rect);
	for(int i=0; i<GetItemCount(); i++)
	{
		ResizeDialog (i, rect.Width (), rect.Height ());
	}
}

void CVTabCtrl::ResizeDialog (int nIndex, int cx, int cy) {
	if (nIndex != -1) 
	{
		CVTabPageEx* pTabPage = m_arTabPage[nIndex];
		if (pTabPage != NULL) 
		{
			CRect rect;
			GetItemRect (nIndex, &rect);

			int x, y, nWidth, nHeight;
			DWORD dwStyle = GetStyle ();

			if (dwStyle & TCS_VERTICAL) 
			{ // Vertical tabs
				int nTabWidth =
					rect.Width () * GetRowCount ();
				x = (dwStyle & TCS_RIGHT) ? 4 : nTabWidth + 4;
				y = 4;
				nWidth = cx - nTabWidth - 8;
				nHeight = cy - 8;
			}
			else 
			{ // Horizontal tabs
				int nTabHeight =
					rect.Height () * GetRowCount ();
				x = 4;
				y = (dwStyle & TCS_BOTTOM) ? 4 : nTabHeight + 4;
				nWidth = cx - 8;
				nHeight = cy - nTabHeight - 8;
			}
			pTabPage->SetWindowPos (NULL, x, y, nWidth, nHeight, SWP_NOZORDER);
		}
	}
}


void CVTabCtrl::OnSelchanging(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int nIndex = GetCurSel ();
	if (nIndex == -1)
		return;

	CVTabPageEx* pTabPage = m_arTabPage.GetAt(nIndex);
	ASSERT(pTabPage);
	pTabPage->ShowWindow(SW_HIDE);
	
	*pResult = 0;
}


CWnd* CVTabCtrl::GetTabPageItem(UINT nTemplateID, UINT nItemID)
{
	ASSERT(nTemplateID > 0 );
	ASSERT(nItemID > 0);
	CWnd* pWnd = NULL;
	for(int i=0; i < m_arTabPage.GetSize(); i++)
	{	
		CVTabPageEx* pTabPage = m_arTabPage[i];
		if((UINT)pTabPage->m_nIDTemplate == nTemplateID)
		{
			pWnd = pTabPage->GetDlgItem(nItemID);
		}
	}
	return pWnd;
}

CWnd* CVTabCtrl::GetTabPageItem(int nIndexPage, UINT nItemID)
{
	ASSERT(nIndexPage >= 0 );
	ASSERT(nItemID > 0);
	ASSERT(m_arTabPage.GetSize() > nIndexPage);
	CWnd* pWnd = NULL;
	CVTabPageEx* pTabPage = m_arTabPage[nIndexPage];

	pWnd = pTabPage->GetDlgItem(nItemID);
	return pWnd;
}

CWnd* CVTabCtrl::GetTabPage(UINT nTemplateID)
{
	ASSERT(nTemplateID > 0 );
	CWnd* pWnd = NULL;
	for(int i=0; i < m_arTabPage.GetSize(); i++)
	{	
		CVTabPageEx* pTabPage = m_arTabPage[i];
		if((UINT)pTabPage->m_nIDTemplate == nTemplateID)
		{
			pWnd = (CWnd*)pTabPage;
		}
	}
	return pWnd;
}
CWnd* CVTabCtrl::GetTabPage(int nIndexPage)
{
	ASSERT(nIndexPage >= 0 );
	ASSERT(m_arTabPage.GetSize() > nIndexPage);
	CWnd* pWnd = (CWnd*)m_arTabPage[nIndexPage];
	return pWnd;
}

BOOL CVTabCtrl::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
	CTabCtrl::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);

	return GetParent()->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}



void CVTabCtrl::OnDestroy() 
{	
	for(int i=0; i<m_arTabPage.GetSize(); i++)
	{
		CVTabPageEx* pTabPage = m_arTabPage[i];
		ASSERT(pTabPage);
		pTabPage->DestroyWindow();
		delete pTabPage;
	}
	m_arTabPage.RemoveAll();
	
	CTabCtrl::OnDestroy();
}

BOOL CVTabCtrl::PreTranslateMessage(MSG* pMsg) 
{
//	GetParent()->PreTranslateMessage(pMsg);
	if(pMsg->message == WM_HSCROLL)
		int a =0;
	
	return CTabCtrl::PreTranslateMessage(pMsg);
}

LRESULT CVTabCtrl::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	if(message == WM_HSCROLL)
	{
	//	::SendMessage(GetParent()->GetSafeHwnd(), message, wParam, lParam);
		return 1;
	}
	
	return CTabCtrl::DefWindowProc(message, wParam, lParam);
}
