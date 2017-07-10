// AgentPanelOcxPpg.cpp : Implementation of the CAgentPanelOcxPropPage property page class.

#include "stdafx.h"
#include "AgentPanelOcx.h"
#include "AgentPanelOcxPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CAgentPanelOcxPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CAgentPanelOcxPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CAgentPanelOcxPropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CAgentPanelOcxPropPage, "AGENTPANELOCX.AgentPanelOcxPropPage.1",
	0xd35ff789, 0xe7f6, 0x4353, 0x8b, 0x24, 0x2f, 0xf6, 0x63, 0xe4, 0x7a, 0xf)


/////////////////////////////////////////////////////////////////////////////
// CAgentPanelOcxPropPage::CAgentPanelOcxPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CAgentPanelOcxPropPage

BOOL CAgentPanelOcxPropPage::CAgentPanelOcxPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_AGENTPANELOCX_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CAgentPanelOcxPropPage::CAgentPanelOcxPropPage - Constructor

CAgentPanelOcxPropPage::CAgentPanelOcxPropPage() :
	COlePropertyPage(IDD, IDS_AGENTPANELOCX_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CAgentPanelOcxPropPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CAgentPanelOcxPropPage::DoDataExchange - Moves data between page and properties

void CAgentPanelOcxPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CAgentPanelOcxPropPage)
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CAgentPanelOcxPropPage message handlers
