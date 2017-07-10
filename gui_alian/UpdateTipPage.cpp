// UpdateTipPage.cpp : implementation file
//

#include "stdafx.h"
#include "ICServingAgentClient.h"
#include "UpdateTipPage.h"

#include "Resources.h"
#include "DynamicResource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUpdateTipPage property page
IMPLEMENT_DYNCREATE(CUpdateTipPage, CPropertyPage)

CUpdateTipPage::CUpdateTipPage() : CPropertyPage(CUpdateTipPage::IDD)
{
	//{{AFX_DATA_INIT(CUpdateTipPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(m_sWhatNews,0,1024);
}

CUpdateTipPage::~CUpdateTipPage()
{
}

void CUpdateTipPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUpdateTipPage)
	DDX_Control(pDX, IDC_UPDATE_TIP, m_richWhatNews);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUpdateTipPage, CPropertyPage)
	//{{AFX_MSG_MAP(CUpdateTipPage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUpdateTipPage message handlers

BOOL CUpdateTipPage::OnSetActive() 
{
	HBITMAP bmBg = CResources::GetImageResource(CDynamicResource::s_ImageUpdateBg);
	if(bmBg != NULL)
	{
		CStatic* p =  (CStatic*)GetDlgItem(IDC_STATIC_BG);
		p->SetBitmap(bmBg);
	}
	return TRUE;
}

void CUpdateTipPage::SetWhatNews(LPSTR szWhatNews)
{
	if (szWhatNews)
		strcpy(m_sWhatNews, szWhatNews);
}

BOOL CUpdateTipPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	CPropertySheet* pParent= (CPropertySheet*)GetParent();
	if (pParent)
	{
		pParent->SetWizardButtons( PSWIZB_NEXT );
		pParent->GetDlgItem(ID_WIZBACK)->ShowWindow(SW_HIDE);
		pParent->GetDlgItem(ID_WIZNEXT)->SetWindowText("是(&Y)");
		pParent->GetDlgItem(IDCANCEL)->SetWindowText("否(&N)");
	}
	
	if(m_bForceUpdate)
	{
		GetDlgItem(IDC_MSG)->SetWindowText("发现必须更新版本，新版本更新内容如下：");
	}
	m_richWhatNews.SetSel(-1,-1);
	m_richWhatNews.ReplaceSel(m_sWhatNews);
	m_richWhatNews.SetSel(-1,-1);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
