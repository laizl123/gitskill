// KillselfDlg.cpp : implementation file
//

#include "stdafx.h"
#include "agentpanelocx.h"
#include "KillselfDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CKillselfDlg dialog


CKillselfDlg::CKillselfDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CKillselfDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CKillselfDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CKillselfDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CKillselfDlg)
	DDX_Control(pDX, IDC_BTN_OK, m_btnOK);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CKillselfDlg, CDialog)
	//{{AFX_MSG_MAP(CKillselfDlg)
	ON_BN_CLICKED(IDC_BTN_OK, OnBtnOk)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKillselfDlg message handlers

void CKillselfDlg::OnBtnOk() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}

BOOL CKillselfDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_iCurrentTime = 5;
	SetTimer(1, 1000, 0);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CKillselfDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == 1)
	{
		if (m_iCurrentTime < 2)
		{
			KillTimer(1);
			OnBtnOk();
		}
		else
		{
			--m_iCurrentTime;			
			CString str;
			str.Format("关闭(%d秒后自动关闭)", m_iCurrentTime);
			m_btnOK.SetWindowText(str);
		}
	}
	CDialog::OnTimer(nIDEvent);
}
