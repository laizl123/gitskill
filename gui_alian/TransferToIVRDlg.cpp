// TransferToIVRDlg.cpp : implementation file
//

#include "stdafx.h"
#include "icservingagentclient.h"
#include "TransferToIVRDlg.h"
#include "MainFrm.h"
#include "Spliter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTransferToIVRDlg dialog
CTransferToIVRDlg::CTransferToIVRDlg(CWnd* pParent /*=NULL*/)
	: CBkDialog(CTransferToIVRDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTransferToIVRDlg)
	m_strTransferToIVR = _T("");
	m_strLanguageType = _T("");
	m_strOperationType = _T("");	
	//}}AFX_DATA_INIT
}


void CTransferToIVRDlg::DoDataExchange(CDataExchange* pDX)
{
	CBkDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTransferToIVRDlg)
	DDX_Control(pDX, IDC_BTN_SEND_IVR_UUIDATA, m_btnSendIVRuuidata);
	DDX_Text(pDX, IDC_EDIT_TRANSFER_TO_IVR, m_strTransferToIVR);
	DDX_Control(pDX, IDC_COMBO_OPERATION_TYPE, m_cobOperationType);
	DDX_Control(pDX, IDC_COMBO_LANGUAGE_TYPE, m_cobLanguageType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTransferToIVRDlg, CBkDialog)
	//{{AFX_MSG_MAP(CTransferToIVRDlg)
	ON_BN_CLICKED(IDC_BTN_SEND_IVR_UUIDATA, OnBtnSendIvrUuidata)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTransferToIVRDlg message handlers
void CTransferToIVRDlg::OnOK(){}
void CTransferToIVRDlg::OnCancel(){}

BOOL CTransferToIVRDlg::OnInitDialog() 
{
	CBkDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetBitmap(IDB_BMP_BG);
	
	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	CString str = pFrame->m_pLoginDlg->m_AgentPanelOcx.GetTransferToIVRParamsInfo();
	int index = str.Find("#.#");
	string sIvrLangType = str.Left(index);
	string sOperationType = str.Right(str.GetLength() - index - 3);
	
	CSpliter split(sIvrLangType, ";");
	int iSize = split.GetSize();
	int i = 0;
	for (; i < iSize; i++)
	{
		CSpliter split2(split[i], ",");
		if (split2.GetSize() != 2)
		{
			continue;
		}
		m_cobLanguageType.AddString(split2[1].c_str());
	}
	if (m_cobLanguageType.GetCurSel() != CB_ERR)
		m_cobLanguageType.SetCurSel(0);

	CSpliter split3(sOperationType, ";");
	iSize = split3.GetSize();
	for (i = 0; i < iSize; i++)
	{
		CSpliter split4(split3[i], ",");
		if (split4.GetSize() != 2)
		{
			continue;
		}
		m_cobOperationType.AddString(split4[1].c_str());
	}
	if (m_cobOperationType.GetCurSel() != CB_ERR)
		m_cobOperationType.SetCurSel(0);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
 

void CTransferToIVRDlg::OnBtnSendIvrUuidata() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	
	if (m_cobLanguageType.GetCurSel() != CB_ERR)
		m_cobLanguageType.GetLBText(m_cobLanguageType.GetCurSel(), m_strLanguageType);
	if (m_cobOperationType.GetCurSel() != CB_ERR)
		m_cobOperationType.GetLBText(m_cobOperationType.GetCurSel(), m_strOperationType);
	
	CBkDialog::OnOK();
}

HBRUSH CTransferToIVRDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CBkDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if(nCtlColor==CTLCOLOR_STATIC)   
	{   
		hbr = (HBRUSH)GetStockObject(NULL_BRUSH);//对于static来说，使用空刷子
		pDC->SetBkMode(TRANSPARENT);
	}
	
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_IVR_TITLE)
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
