// PrivilegeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "icservingagentclient.h"
#include "PrivilegeDlg.h"
#include "PrivilegeAdjust.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPrivilegeDlg dialog


CPrivilegeDlg::CPrivilegeDlg(CWnd* pParent /*=NULL*/)
	: CBkDialog(CPrivilegeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPrivilegeDlg)
	m_strPassword = _T("");
	//}}AFX_DATA_INIT
}


void CPrivilegeDlg::DoDataExchange(CDataExchange* pDX)
{
	CBkDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPrivilegeDlg)
	DDX_Control(pDX, IDC_COMBO_USERNAME, m_boxUserName);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_strPassword);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPrivilegeDlg, CBkDialog)
	//{{AFX_MSG_MAP(CPrivilegeDlg)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPrivilegeDlg message handlers

void CPrivilegeDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	m_boxUserName.GetWindowText(m_strUserName);
	CBkDialog::OnOK();
}

// 用户登录
BOOL CPrivilegeDlg::AdjustPrivilege()
{
	if(CPrivilegeAdjust::IsHasPrivilege() == TRUE)
		return TRUE;
	// 得到用户名和密码
	CString strUser, strPswd;
	CPrivilegeAdjust::GetPrivilegeInfo(strUser, strPswd);
	if(strUser.IsEmpty() == FALSE && CPrivilegeAdjust::SetThreadPrivilege(strUser, strPswd) == TRUE)
	{
		return TRUE;
	}
	// 得到用户
	CPrivilegeAdjust::GetPrivilegeUser(m_arrPrivUser);
	if(m_arrPrivUser.GetSize() == 0)
	{
		return FALSE;
	}
	// 
	while(DoModal() == IDOK)
	{
		if(CPrivilegeAdjust::SetThreadPrivilege(m_strUserName, m_strPassword) == FALSE)
		{
			AfxMessageBox("提升权限失败,请重新输入密码!");
			continue;
		}
		else
		{
			RevertToSelf();
			CPrivilegeAdjust::SavePrivilegeInfo(m_strUserName, m_strPassword);
			AfxMessageBox("提升权限成功,需要重新登陆!");
			return FALSE;
		}
	}
	return  FALSE;
}

BOOL CPrivilegeDlg::OnInitDialog() 
{
	CBkDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetBitmap(IDB_BMP_BG);
	//CRect rcBtnOK, rect;
	//m_btnOK.GetWindowRect(rcBtnOK);
	//ScreenToClient(rcBtnOK);
	//GetWindowRect(rect);
	//m_btnOK.MoveWindow((rect.Width() - rcBtnOK.Width()) / 2, rcBtnOK.top, rcBtnOK.Width(), rcBtnOK.Height());
	//m_btnCancel.ShowWindow(SW_HIDE);

	int nSize = m_arrPrivUser.GetSize();
	for(int i = 0; i < nSize; i++)
	{
		m_boxUserName.AddString(m_arrPrivUser.GetAt(i));
	}
	if(m_boxUserName.GetCount() != 0)
		m_boxUserName.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH CPrivilegeDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CBkDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if (CTLCOLOR_STATIC == nCtlColor)
	{
		hbr = (HBRUSH)GetStockObject(NULL_BRUSH);//对于static来说，使用空刷子
		pDC->SetBkMode(TRANSPARENT);
	}
	
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_TITLE)
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
