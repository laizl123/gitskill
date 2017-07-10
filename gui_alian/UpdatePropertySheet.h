#if !defined(AFX_UPDATEPROPERTYSHEET_H__C4D4EE8F_9BC8_4FCB_B1AD_DD13AE95EE77__INCLUDED_)
#define AFX_UPDATEPROPERTYSHEET_H__C4D4EE8F_9BC8_4FCB_B1AD_DD13AE95EE77__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UpdatePropertySheet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUpdatePropertySheet
#define WM_DESTROYWIZARD WM_USER+934

class CUpdatePropertySheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CUpdatePropertySheet)

// Construction
public:
	CUpdatePropertySheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CUpdatePropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	void SetForceUpdate(BOOL bForceUpdate=TRUE) {	m_bForceUpdate=bForceUpdate;	} 
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUpdatePropertySheet)
	public:
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CUpdatePropertySheet();

	// Generated message map functions
protected:
	BOOL m_bForceUpdate;
	//{{AFX_MSG(CUpdatePropertySheet)
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg LRESULT OnDestroyWizard(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UPDATEPROPERTYSHEET_H__C4D4EE8F_9BC8_4FCB_B1AD_DD13AE95EE77__INCLUDED_)
