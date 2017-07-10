#if !defined(AFX_VTABPAGEEX_H__449AE1CE_30EB_498D_B70E_FD3C54FFAE85__INCLUDED_)
#define AFX_VTABPAGEEX_H__449AE1CE_30EB_498D_B70E_FD3C54FFAE85__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VTabPageEx.h : header file
//
#include "EasySize.h"
/////////////////////////////////////////////////////////////////////////////
// CVTabPageEx dialog

class CVTabPageEx : public CDialog
{
// Construction
public:
//	int AddTabPage(LPCTSTR pszTitle, int nPageID, UINT nTemplateID);
	CVTabPageEx();
	CVTabPageEx(UINT nIDTemplate,CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CVTabPageEx)

		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
	
	UINT m_nIDTemplate;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVTabPageEx)
	public:
	virtual BOOL Create(UINT nIDTemplate,CWnd* pParent=NULL);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CVTabPageEx)
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VTABPAGEEX_H__449AE1CE_30EB_498D_B70E_FD3C54FFAE85__INCLUDED_)
