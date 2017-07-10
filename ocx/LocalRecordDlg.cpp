// LocalRecordDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AgentPanelOcxCtl.h"
#include "LocalRecordDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CLocalRecordDlg dialog
CLocalRecordDlg::CLocalRecordDlg(CWnd* pParent /*=NULL*/)
: CBkDialog(CLocalRecordDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLocalRecordDlg)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CLocalRecordDlg::DoDataExchange(CDataExchange* pDX)
{
	CBkDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLocalRecordDlg)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX, IDC_BTN_LOCAL_RECORD_CLOSE, m_btnLocalRecordClose);
	DDX_Control(pDX, IDC_BTN_CHANGE_RECPATH, m_btnChangeRecPath);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLocalRecordDlg, CBkDialog)
//{{AFX_MSG_MAP(CLocalRecordDlg)
// NOTE: the ClassWizard will add message map macros here
ON_WM_CTLCOLOR()
ON_BN_CLICKED(IDC_BTN_LOCAL_RECORD_CLOSE, OnBtnLocalRecordClose)
ON_BN_CLICKED(IDC_BTN_CHANGE_RECPATH, OnBtnChangeRecPath)
ON_WM_NCHITTEST()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLocalRecordDlg message handlers
BOOL CLocalRecordDlg::OnInitDialog() 
{
	CBkDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_config.SetFileName(GetDataFilesPath() + "\\DISCO_Client.ini");
	m_strLocalRecPath = m_config.GetProfileString("LocalRecordSettings", "Path", "");
	if (m_strLocalRecPath == "")
		m_strLocalRecPath = GetDataFilesPath();

	SetBitmap(IDB_BMP_BG);

	GetDlgItem(IDC_STATIC_LOCAL_RECORD_TITLE)->SetWindowText("开启本地录音");
	GetDlgItem(IDC_EDIT_LOCAL_RECORD_CONTENT)->SetWindowText("录音文件存储目录：\r\n" + m_strLocalRecPath + "\\RecordFiles\\座席帐号\\年月日\\录音文件名\r\n\r\n录音文件名：\r\n\"通话对方电话号码(座席名)\"+\"_\"+\"时分秒\".wav");

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
void CLocalRecordDlg::OnOK()
{
	CBkDialog::OnOK();
}

void CLocalRecordDlg::OnCancel(){}

void CLocalRecordDlg::OnBtnChangeRecPath()
{
	CString str;
	BROWSEINFO bi;
	char name[MAX_PATH];
	ZeroMemory(&bi,sizeof(BROWSEINFO));
	bi.hwndOwner=GetSafeHwnd();
	bi.pszDisplayName=name;
	bi.lpszTitle="Select folder";
	bi.ulFlags=BIF_USENEWUI;
	LPITEMIDLIST idl=SHBrowseForFolder(&bi);
	if(idl==NULL)
		return;
	SHGetPathFromIDList(idl,str.GetBuffer(MAX_PATH));
	str.ReleaseBuffer();
	m_strLocalRecPath=str;

	GetDlgItem(IDC_EDIT_LOCAL_RECORD_CONTENT)->SetWindowText("录音文件存储目录：\r\n" + m_strLocalRecPath + "\\RecordFiles\\座席帐号\\年月日\\录音文件名\r\n\r\n录音文件名：\r\n\"通话对方电话号码(座席名)\"+\"_\"+\"时分秒\".wav");
}

void CLocalRecordDlg::OnBtnLocalRecordClose()
{
	// TODO: Add your control notification handler code here
	m_config.WriteProfileString("LocalRecordSettings", "Path", m_strLocalRecPath);

	CBkDialog::OnCancel();
}

HBRUSH CLocalRecordDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CBkDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_LOCAL_RECORD_TITLE)
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
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

LRESULT CLocalRecordDlg::OnNcHitTest(CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	return HTCAPTION;
	//return CBkDialog::OnNcHitTest(point);
}
