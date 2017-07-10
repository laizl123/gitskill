#if !defined(AFX_AGENTPANELOCXPPG_H__548F5990_E23C_454F_9B9F_54D840551A6C__INCLUDED_)
#define AFX_AGENTPANELOCXPPG_H__548F5990_E23C_454F_9B9F_54D840551A6C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// AgentPanelOcxPpg.h : Declaration of the CAgentPanelOcxPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CAgentPanelOcxPropPage : See AgentPanelOcxPpg.cpp.cpp for implementation.

class CAgentPanelOcxPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CAgentPanelOcxPropPage)
	DECLARE_OLECREATE_EX(CAgentPanelOcxPropPage)

// Constructor
public:
	CAgentPanelOcxPropPage();

// Dialog Data
	//{{AFX_DATA(CAgentPanelOcxPropPage)
	enum { IDD = IDD_PROPPAGE_AGENTPANELOCX };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CAgentPanelOcxPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AGENTPANELOCXPPG_H__548F5990_E23C_454F_9B9F_54D840551A6C__INCLUDED)
