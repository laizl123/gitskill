// HelpTipDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AgentPanelOcxCtl.h"
#include "HelpTipDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHelpTipDlg dialog


CHelpTipDlg::CHelpTipDlg(CWnd* pParent /*=NULL*/)
: CBkDialog(CHelpTipDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHelpTipDlg)
	m_strContent = _T("");
	m_strTitle = _T("");
	//}}AFX_DATA_INIT
}

CHelpTipDlg::CHelpTipDlg(CString strTitle, CString strContent, CWnd* pParent /*=NULL*/)
: m_strTitle(strTitle), m_strContent(strContent), CBkDialog(CHelpTipDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHelpTipDlg)
	//}}AFX_DATA_INIT
}

void CHelpTipDlg::DoDataExchange(CDataExchange* pDX)
{
	CBkDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHelpTipDlg)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Text(pDX, IDC_STATIC_HELPTIP_CONTENT, m_strContent);
	DDX_Text(pDX, IDC_STATIC_HELPTIP_TITLE, m_strTitle);
	DDX_Control(pDX, IDC_BTN_HELPTIP_CLOSE, m_btnHelptipClose);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHelpTipDlg, CBkDialog)
//{{AFX_MSG_MAP(CHelpTipDlg)
ON_WM_CTLCOLOR()
ON_BN_CLICKED(IDC_BTN_HELPTIP_CLOSE, OnBtnHelptipClose)
	ON_WM_NCHITTEST()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHelpTipDlg message handlers
BOOL CHelpTipDlg::OnInitDialog() 
{
	CBkDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetBitmap(IDB_BMP_BG);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
void CHelpTipDlg::OnOK()
{
	CBkDialog::OnOK();
}

void CHelpTipDlg::OnCancel(){}
HBRUSH CHelpTipDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CBkDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if (CTLCOLOR_STATIC == nCtlColor)
	{
		hbr = (HBRUSH)GetStockObject(NULL_BRUSH);//对于static来说，使用空刷子
		pDC->SetBkMode(TRANSPARENT);
	}

	if (pWnd->GetDlgCtrlID() == IDC_STATIC_HELPTIP_TITLE)
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

void CHelpTipDlg::OnBtnHelptipClose() 
{
	// TODO: Add your control notification handler code here
	CBkDialog::OnCancel();
}

LRESULT CHelpTipDlg::OnNcHitTest(CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	return HTCAPTION;
	//return CBkDialog::OnNcHitTest(point);
}
