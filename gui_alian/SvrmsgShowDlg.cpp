// SvrmsgShowDlg.cpp : implementation file
//

#include "stdafx.h"
#include "icservingagentclient.h"
#include "SvrmsgShowDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSvrmsgShowDlg dialog


CSvrmsgShowDlg::CSvrmsgShowDlg(CWnd* pParent /*=NULL*/)
	: CBkDialog(CSvrmsgShowDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSvrmsgShowDlg)
	m_bShowCheck = FALSE;
	m_strContent = _T("");
	m_strSender = _T("");
	//}}AFX_DATA_INIT
	m_brushBack.CreateSolidBrush(RGB(206, 227, 255));
	m_bVisShowBox = TRUE;
}


void CSvrmsgShowDlg::DoDataExchange(CDataExchange* pDX)
{
	CBkDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSvrmsgShowDlg)
	DDX_Control(pDX, IDOK, m_btOK);
	DDX_Check(pDX, IDC_CHECK_SHOW, m_bShowCheck);
	DDX_Text(pDX, IDC_EDIT_MSGCONTENT, m_strContent);
	DDX_Text(pDX, IDC_EDIT_SENDER, m_strSender);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSvrmsgShowDlg, CBkDialog)
	//{{AFX_MSG_MAP(CSvrmsgShowDlg)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSvrmsgShowDlg message handlers

HBRUSH CSvrmsgShowDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CBkDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if(nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);
	}
	else if(pWnd->GetDlgCtrlID() == IDC_CHECK_SHOW)
	{
		pDC->SetBkMode(TRANSPARENT);
	}
	return hbr;
}

BOOL CSvrmsgShowDlg::OnInitDialog() 
{
	CBkDialog::OnInitDialog();
	if(m_bVisShowBox == FALSE)
	{
		GetDlgItem(IDC_CHECK_SHOW)->ShowWindow(SW_HIDE);
	}	
	// TODO: Add extra initialization here
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
