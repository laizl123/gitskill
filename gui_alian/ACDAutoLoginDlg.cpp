// ACDAutoLoginDlg.cpp : implementation file
//

#include "stdafx.h"
#include "icservingagentclient.h"
#include "ACDAutoLoginDlg.h"
#include "Log.h"
#include "MainFrm.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CACDAutoLoginDlg dialog
extern CString g_strLogFilePath;
extern CMainFrame *g_pMainFrame;
CACDAutoLoginDlg::CACDAutoLoginDlg(CWnd* pParent /*=NULL*/)
	: CBkDialog(CACDAutoLoginDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(ACDAutoLoginDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_iTime = 58;
	m_bEnter = FALSE;
}


void CACDAutoLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CBkDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CACDAutoLoginDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX, IDC_BTN_CLOSE_ACDAUTOLOGIN, m_btnClose);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CACDAutoLoginDlg, CBkDialog)
	//{{AFX_MSG_MAP(CACDAutoLoginDlg)
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
    ON_BN_CLICKED(IDC_BTN_CLOSE_ACDAUTOLOGIN, OnBtnClose)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CACDAutoLoginDlg message handlers
void CACDAutoLoginDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_iTime == 0)
	{
		KillTimer(1);
		GetDlgItem(IDC_STATIC_ACDAUTOLOGIN)->SetWindowText("自动故障排除：0s后座席可点击确定按钮重新登录。");
		m_btnClose.EnableWindow(TRUE);
		m_btnClose.SetFocus();
		m_bEnter = TRUE;
	}
	else
	{
		m_bEnter = FALSE;
		CString str;
		str.Format("自动故障排除：%ds后座席可点击确定按钮重新登录。",m_iTime--);
		GetDlgItem(IDC_STATIC_ACDAUTOLOGIN)->SetWindowText(str);
	}
	CBkDialog::OnTimer(nIDEvent);
}

void CACDAutoLoginDlg::OnBtnClose() 
{
	// TODO: Add your control notification handler code here
	ShowWindow(SW_HIDE);
	g_pMainFrame->m_pLoginDlg->m_AgentPanelOcx.ActionACDAutoLogin();
}
BOOL CACDAutoLoginDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_KEYDOWN)
	{
		if(pMsg->wParam == VK_RETURN)
		{
		   if(m_bEnter)
		   {
			   ShowWindow(SW_HIDE);
               g_pMainFrame->m_pLoginDlg->m_AgentPanelOcx.ActionACDAutoLogin();
		   }
		   else
		      return TRUE;
		}
		if(GetKeyState(VK_CONTROL)>=0)
		{
			return TRUE;
		}
	}
	return CBkDialog::PreTranslateMessage(pMsg);
}

HBRUSH CACDAutoLoginDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CBkDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_ACDAUTOLOGIN_TITLE)
	{
		CFont font;
		LOGFONT lf;
		memset(&lf, 0, sizeof(LOGFONT));       // zero out structure
		lf.lfHeight = 15;
		lf.lfWeight = FW_BOLD;
		strcpy(lf.lfFaceName, "宋体");        // request a face name "Arial"
		VERIFY(font.CreateFontIndirect(&lf));  // create the font
		
		pDC->SelectObject(&font);

		hbr = (HBRUSH)GetStockObject(NULL_BRUSH);//对于static来说，使用空刷子
		pDC->SetBkMode(TRANSPARENT);
	}
	else if (pWnd->GetDlgCtrlID() == IDC_STATIC_ACDAUTOLOGIN)
	{
		pDC->SetBkColor(RGB(206, 227, 255));
		HBRUSH brush = CreateSolidBrush(RGB(206, 227, 255));
		return brush;
	}
	// TODO: Return a different brush if the default is not desired
	return hbr;
}


BOOL CACDAutoLoginDlg::OnInitDialog() 
{
	CBkDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetBitmap(IDB_BMP_BG);
	GetDlgItem(IDC_STATIC_ACDAUTOLOGIN_TITLE)->SetWindowText("错误");
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
