// CompanyHistoryDlg.cpp : implementation file
//

#include "stdafx.h"
#include "icservingagentclient.h"
#include "CompanyHistoryDlg.h"
#include "LoginDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define IDC_BTN_MY_COMPANY 22000
extern CButton* g_pBtnLastMouseLeave;
extern COLORREF g_hicr;
extern COLORREF g_midcr;
extern COLORREF g_locr;


/////////////////////////////////////////////////////////////////////////////
// CCompanyHistoryDlg dialog


CCompanyHistoryDlg::CCompanyHistoryDlg(CWnd* pParent /*=NULL*/)
	: CMyBkDialog(CCompanyHistoryDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCompanyHistoryDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_nBtnIDIndex = 0;
	m_iCompanyCount = 0;
	memset(m_pBtnCompany, 0, COMPANY_HISTORY_COUNT * sizeof(CButtonST *));
	memset((void *)m_nBtnID, 0, COMPANY_HISTORY_COUNT * sizeof(int));
}


void CCompanyHistoryDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyBkDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCompanyHistoryDlg)
	DDX_Control(pDX, IDC_BTN_COMPANY_CLEAR, m_btnClearCompany);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCompanyHistoryDlg, CMyBkDialog)
	//{{AFX_MSG_MAP(CCompanyHistoryDlg)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_COMPANY_CLEAR, OnBtnCompanyClear)
	//}}AFX_MSG_MAP
	ON_COMMAND_RANGE(IDC_BTN_MY_COMPANY, IDC_BTN_MY_COMPANY + COMPANY_HISTORY_COUNT, OnBtnCompany)
	ON_MESSAGE(WM_BTNST_MY_DELETE, OnBtnDelete)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCompanyHistoryDlg message handlers

BOOL CCompanyHistoryDlg::OnInitDialog() 
{
	CMyBkDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//SetBitmap(IDB_BMP_BG);

	m_btnClearCompany.GetClientRect(&m_rcBtnClearCompany);
	m_btnClearCompany.SetBaseColor(g_hicr, g_midcr, g_locr);
	m_btnClearCompany.SetShade(CShadeButtonST::SHS_HSHADE);//,8,COMPANY_HISTORY_COUNT,5,RGB(55,55,255)
	
	//CEnvironment& env = CEnvironment::Instance();
	CConfigFile& env = CICServingAgentClientApp::m_ConfigFile;
	env.GetCompanyHistory();

	int i = 0;
	CString strTemp;
	m_iCompanyCount = env.m_saCompanyHistory.GetSize();
	for (i=0; i<m_iCompanyCount; i++)
	{
		m_pBtnCompany[i] = new CMyShadeButtonST(ES_DELETE);
		m_pBtnCompany[i]->Create(env.m_saCompanyHistory.GetAt(i), 
			WS_CHILD|WS_VISIBLE|BS_TEXT|BS_LEFT, 
			CRect(0, 
			m_rcBtnClearCompany.Height() * i, 
			m_rcBtnClearCompany.Width(), 
			m_rcBtnClearCompany.Height() * (i+1)), 
			this, IDC_BTN_MY_COMPANY + m_nBtnIDIndex);
		m_pBtnCompany[i]->SetFont(GetFont());
		m_pBtnCompany[i]->SetBaseColor(g_hicr, g_midcr, g_locr);
		m_pBtnCompany[i]->SetShade(CShadeButtonST::SHS_HSHADE);//,8,COMPANY_HISTORY_COUNT,5,RGB(55,55,255)	
		m_nBtnID[i] = IDC_BTN_MY_COMPANY + m_nBtnIDIndex;
		++m_nBtnIDIndex;
	}

	m_btnClearCompany.MoveWindow(0, m_rcBtnClearCompany.Height() * m_iCompanyCount, m_rcBtnClearCompany.Width(), m_rcBtnClearCompany.Height());

	GetWindowRect(&m_rcWindow);
	MoveWindow(m_rcWindow.left, m_rcWindow.top, m_rcWindow.Width(), m_rcBtnClearCompany.Height() * (m_iCompanyCount+1)+2);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCompanyHistoryDlg::OnOK(){}
void CCompanyHistoryDlg::OnCancel(){}

void CCompanyHistoryDlg::OnDestroy() 
{
	CMyBkDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	int i = 0;
	for (; i<m_iCompanyCount; i++)
	{
			m_pBtnCompany[i]->DestroyWindow();
			delete m_pBtnCompany[i];
			m_pBtnCompany[i] = NULL;
	}
}

void CCompanyHistoryDlg::OnBtnCompanyClear() 
{
	// TODO: Add your control notification handler code here
	int i = 0;
	for (; i<m_iCompanyCount; i++)
	{
			m_pBtnCompany[i]->DestroyWindow();
			delete m_pBtnCompany[i];
			m_pBtnCompany[i] = NULL;
	}

	m_btnClearCompany.MoveWindow(0, 0, m_rcBtnClearCompany.Width(), m_rcBtnClearCompany.Height());
	CRect rcWindow;
	GetWindowRect(&rcWindow);
	MoveWindow(rcWindow.left, rcWindow.top, rcWindow.Width(), m_rcBtnClearCompany.Height()+2);
	m_iCompanyCount = 0;

	//CEnvironment& env = CEnvironment::Instance();
	CConfigFile& env = CICServingAgentClientApp::m_ConfigFile;

	env.m_saCompanyHistory.RemoveAll();
	env.SetCompanyHistory();

	ShowWindow(SW_HIDE);
}

void CCompanyHistoryDlg::AddCompanyToHistory(CString strCompany)
{
	//CEnvironment& env = CEnvironment::Instance();
	CConfigFile& env = CICServingAgentClientApp::m_ConfigFile;

	
	if (m_iCompanyCount >= COMPANY_HISTORY_COUNT)
	{
		int i = 0;
		for (i=0; i<COMPANY_HISTORY_COUNT; i++)
		{
			if (strcmp(strCompany, env.m_saCompanyHistory.GetAt(i)) == 0)
			{
				return;
			}
		}
		
		for (i=COMPANY_HISTORY_COUNT-1; i>0; i--)
		{
			env.m_saCompanyHistory.SetAt(i, env.m_saCompanyHistory.GetAt(i-1));
		}
		env.m_saCompanyHistory.SetAt(0, strCompany);
		env.SetCompanyHistory();

		return;
	}
		
	int i = 0;
	for (i=0; i<m_iCompanyCount; i++)
	{
		if (strcmp(strCompany, env.m_saCompanyHistory.GetAt(i)) == 0)
		{
			return;
		}
	}

	if (m_iCompanyCount > 0)
	{
		env.m_saCompanyHistory.Add(env.m_saCompanyHistory.GetAt(m_iCompanyCount-1));
		for (i=m_iCompanyCount-1; i>0; i--)
		{
			env.m_saCompanyHistory.SetAt(i, env.m_saCompanyHistory.GetAt(i-1));
		}
		env.m_saCompanyHistory.SetAt(0, strCompany);
	}
	else
	{
		env.m_saCompanyHistory.Add(strCompany);
	}
	env.SetCompanyHistory();

}

void CCompanyHistoryDlg::OnBtnCompany(UINT nID)
{
	for (int i=0; i<m_iCompanyCount; i++)
	{
		if (nID == m_nBtnID[i])
		{
			CString strTemp;
			m_pBtnCompany[i]->GetWindowText(strTemp);
			((CLoginDlg *)GetParent())->m_editCompany.SetWindowText(strTemp);
			ShowWindow(SW_HIDE);
			break;
		}
	}
}

LRESULT CCompanyHistoryDlg::OnBtnDelete(WPARAM wParam, LPARAM lParam)
{
	int i = 0;
	for (i=0; i<m_iCompanyCount; i++)
	{
		if (m_pBtnCompany[i] == (CMyShadeButtonST *)wParam)
		{
			if (m_pBtnCompany[i] == g_pBtnLastMouseLeave)
			{
				g_pBtnLastMouseLeave = NULL;
			}
			m_pBtnCompany[i]->DestroyWindow();
			delete m_pBtnCompany[i];
			m_pBtnCompany[i] = NULL;
			for (; i<m_iCompanyCount-1; i++)
			{
				m_pBtnCompany[i] = m_pBtnCompany[i+1];
				m_nBtnID[i] = m_nBtnID[i+1];
			}
			m_pBtnCompany[m_iCompanyCount-1] = NULL;
			m_nBtnID[m_iCompanyCount-1] = 0;				
			--m_iCompanyCount;
			
			break;
		}
	}
	
	//CEnvironment& env = CEnvironment::Instance();
	CConfigFile& env = CICServingAgentClientApp::m_ConfigFile;
	
	env.m_saCompanyHistory.RemoveAll();

	
	for (i=0; i<m_iCompanyCount; i++)
	{
		m_pBtnCompany[i]->MoveWindow(0, 
			m_rcBtnClearCompany.Height() * i, 
			m_rcBtnClearCompany.Width(), 
			m_rcBtnClearCompany.Height());
		CString strTemp;
		m_pBtnCompany[i]->GetWindowText(strTemp);
		env.m_saCompanyHistory.Add(strTemp);
	}
	env.SetCompanyHistory();
	
	
	m_btnClearCompany.MoveWindow(0, m_rcBtnClearCompany.Height() * m_iCompanyCount, m_rcBtnClearCompany.Width(), m_rcBtnClearCompany.Height());
	
	GetWindowRect(&m_rcWindow);
	MoveWindow(m_rcWindow.left, m_rcWindow.top, m_rcWindow.Width(), m_rcBtnClearCompany.Height() * (m_iCompanyCount+1)+2);
	
	return 0;
}
