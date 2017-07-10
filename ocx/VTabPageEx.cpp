// VTabPageEx.cpp : implementation file
//

#include "stdafx.h"

#include "VTabPageEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVTabPageEx dialog
CVTabPageEx::CVTabPageEx()
{
}

CVTabPageEx::CVTabPageEx(UINT nIDTemplate, CWnd* pParent /*=NULL*/)
	: CDialog(nIDTemplate, pParent),m_nIDTemplate(nIDTemplate)
{
	//{{AFX_DATA_INIT(CVTabPageEx)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CVTabPageEx::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVTabPageEx)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CVTabPageEx, CDialog)
	//{{AFX_MSG_MAP(CVTabPageEx)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVTabPageEx message handlers


void CVTabPageEx::OnOK() 
{
	
}

void CVTabPageEx::OnCancel() 
{

}

BOOL CVTabPageEx::Create(UINT nIDTemplate,CWnd* pParent) 
{
	m_nIDTemplate = nIDTemplate;
	return CDialog::Create(nIDTemplate, pParent);
}

BOOL CVTabPageEx::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
	BOOL bReturn = CDialog::OnCmdMsg (nID, nCode, pExtra, pHandlerInfo);

	return GetParent ()->OnCmdMsg (nID, nCode, pExtra, pHandlerInfo);
}



LRESULT CVTabPageEx::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	if(message == WM_HSCROLL|| message == WM_SYSKEYDOWN)
	{
		::SendMessage(GetParent()->GetSafeHwnd(), message, wParam, lParam);
	}
	
	return CDialog::DefWindowProc(message, wParam, lParam);
}
