// ShowWarnDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ICServingAgentClient.h"
#include "ShowWarnDlg.h"
#include "MainFrm.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShowWarnDlg dialog

extern int g_nDlgShowWarnSecNumber;
extern CMainFrame *g_pMainFrame;
CShowWarnDlg::CShowWarnDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CShowWarnDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CShowWarnDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CShowWarnDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShowWarnDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX, IDC_BTN_SHOWWARN_CLOSE, m_btnClose);

	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CShowWarnDlg, CDialog)
	//{{AFX_MSG_MAP(CShowWarnDlg)
		// NOTE: the ClassWizard will add message map macros here
		ON_WM_TIMER()
		ON_WM_CTLCOLOR()
		ON_BN_CLICKED(IDC_BTN_SHOWWARN_CLOSE, OnBtnClose)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CShowWarnDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	CDialog::OnTimer(nIDEvent);
}
/////////////////////////////////////////////////////////////////////////////
// CShowWarnDlg message handlers

HBRUSH CShowWarnDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	HBRUSH hbrDlg;
	if(nCtlColor==CTLCOLOR_STATIC)   
	{   
		pDC->SetBkColor(RGB(255,255,255));
		hbrDlg=CreateSolidBrush(RGB(255, 255, 255));
		return hbrDlg;   
	}   		
	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CShowWarnDlg::OnBtnClose()
{
	ShowWindow(SW_HIDE);
    g_pMainFrame->m_pLoginDlg->m_AgentPanelOcx.ActionLogout();
}
BOOL CShowWarnDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_KEYDOWN)
	{
		if(pMsg->wParam == VK_RETURN)
		{
			ShowWindow(SW_HIDE);
			g_pMainFrame->m_pLoginDlg->m_AgentPanelOcx.ActionLogout();
		}
		if(GetKeyState(VK_CONTROL)>=0)
		{
			return TRUE;
		}
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}