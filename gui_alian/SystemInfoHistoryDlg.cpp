// SystemInfoHistoryDlg.cpp : implementation file
//

#include "stdafx.h"
#include "icservingagentclient.h"
#include "SystemInfoHistoryDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSystemInfoHistoryDlg dialog
CSystemInfoHistoryDlg::CSystemInfoHistoryDlg(CWnd* pParent /*=NULL*/)
	: CBkDialog(CSystemInfoHistoryDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSystemInfoHistoryDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void CSystemInfoHistoryDlg::DoDataExchange(CDataExchange* pDX)
{
	CBkDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSystemInfoHistoryDlg)
	DDX_Control(pDX, IDC_BTN_SYSINFO_CLOSE, m_btnSysInfoClose);
	DDX_Control(pDX, IDC_RICHEDIT_SYSINFO, m_editSysInfoHistory);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSystemInfoHistoryDlg, CBkDialog)
	//{{AFX_MSG_MAP(CSystemInfoHistoryDlg)
	ON_WM_CTLCOLOR()
	ON_WM_NCHITTEST()
	ON_BN_CLICKED(IDC_BTN_SYSINFO_CLOSE, OnBtnSysinfoClose)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSystemInfoHistoryDlg message handlers
void CSystemInfoHistoryDlg::OnOK(){}
void CSystemInfoHistoryDlg::OnCancel(){ ShowWindow(SW_HIDE); }

void CSystemInfoHistoryDlg::AddSysInfoHistory(CString strContent)
{
//	if (!IsWindowVisible())
//	{
//		ShowWindow(SW_SHOW);	
//	}

	CTime time = CTime::GetCurrentTime();
	CString strCurrentTime;
	strCurrentTime.Format("%02d月%02d日%02d:%02d:%02d", time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond());
	
	int iFirstLine = m_editSysInfoHistory.GetLineCount();
	int iLength = m_editSysInfoHistory.GetWindowTextLength();
	m_editSysInfoHistory.SetSel(-1, -1);
	m_editSysInfoHistory.ReplaceSel(strCurrentTime + "   " + strContent + "\n");			

	CHARFORMAT cf;
	cf.cbSize		= sizeof(CHARFORMAT);
	cf.dwMask		= CFM_COLOR | CFM_UNDERLINE | CFM_BOLD | CFE_ITALIC;
	cf.dwEffects	= (unsigned long)~( CFE_AUTOCOLOR | CFE_UNDERLINE | CFM_STRIKEOUT | CFE_ITALIC | CFE_BOLD);
	//	cf.dwEffects	|= CFE_ITALIC;
	cf.crTextColor	= RGB(0, 0, 0);
	m_editSysInfoHistory.SetSelectionCharFormat(cf); 
	m_editSysInfoHistory.HideSelection(TRUE, FALSE);
	
	int iMin, iMax;
	m_editSysInfoHistory.GetScrollRange(SB_VERT, &iMin, &iMax);
	if(iMax > iMin)
	{		
		m_editSysInfoHistory.SendMessage(WM_VSCROLL, SB_BOTTOM, 0);
	}
}

UINT CSystemInfoHistoryDlg::OnNcHitTest(CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	return HTCAPTION;
}

BOOL CSystemInfoHistoryDlg::OnInitDialog() 
{
	CBkDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetBitmap(IDB_BMP_BG);	
	m_editSysInfoHistory.SetReadOnly();

	m_btnSysInfoClose.SetIcon(IDI_ICON_IECLOSEALL_1, IDI_ICON_IECLOSEALL_2, IDI_ICON_IECLOSEALL_3, IDI_ICON_IECLOSEALL_3);
	m_btnSysInfoClose.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, 30);
	m_btnSysInfoClose.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnSysInfoClose.SetColor(CButtonST::BTNST_COLOR_BK_FOCUS, RGB(206, 227, 255));
	m_btnSysInfoClose.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(0, 0, 255));
	m_btnSysInfoClose.SetColor(CButtonST::BTNST_COLOR_BK_OUT, RGB(206, 227, 255));	
	m_btnSysInfoClose.SetColor(CButtonST::BTNST_COLOR_BK_IN, RGB(206, 227, 255));	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSystemInfoHistoryDlg::OnBtnSysinfoClose() 
{
	// TODO: Add your control notification handler code here
	ShowWindow(SW_HIDE);
}

HBRUSH CSystemInfoHistoryDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CBkDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if(nCtlColor==CTLCOLOR_STATIC)   
	{   
		hbr = (HBRUSH)GetStockObject(NULL_BRUSH);//对于static来说，使用空刷子
		pDC->SetBkMode(TRANSPARENT);
	}
	
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_SYSINFOHISTORY_TITLE)
	{
		CFont font;
		LOGFONT lf;
		memset(&lf, 0, sizeof(LOGFONT));       // zero out structure
		lf.lfHeight = 15;
		lf.lfWeight = FW_BOLD;
		strcpy(lf.lfFaceName, "宋体");        // request a face name "Arial"
		VERIFY(font.CreateFontIndirect(&lf));  // create the font
		
		pDC->SelectObject(&font);
	}
	// TODO: Return a different brush if the default is not desired
	return hbr;
}
