#if !defined(AFX_VTABCTRL_H__30EB90FF_C517_403F_8D9F_3F346508EDD1__INCLUDED_)
#define AFX_VTABCTRL_H__30EB90FF_C517_403F_8D9F_3F346508EDD1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VTabCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVTabCtrl window
#include <Afxtempl.h>
#include "VTabPageEx.h"

class CVTabCtrl : public CTabCtrl
{
// Construction
public:
	CVTabCtrl();

// Attributes
public:

// Operations
public:
	void ResizeAll();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVTabCtrl)
	public:
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

protected:
	CArray<CVTabPageEx*,CVTabPageEx*> m_arTabPage;
	CImageList m_ImageList;

// Implementation
public:
	int AddTabPage(LPCTSTR pszTitle, int nPageID, CVTabPageEx* pTabPage, UINT nIconID = 0);
	int AddTabPage(LPCTSTR pszTitle, int nPageID, UINT nTemplateID, UINT nIconID = 0);
	void ResizeDialog (int nIndex, int cx, int cy);
	CWnd* GetTabPageItem(UINT nTemplateID, UINT nItemID);
	CWnd* GetTabPageItem(int nIndexPage, UINT nItemID);

	CWnd* GetTabPage(UINT nTemplateID);
	CWnd* GetTabPage(int nIndexPage);
	
	virtual ~CVTabCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CVTabCtrl)
	afx_msg void OnSelchange(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchanging(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VTABCTRL_H__30EB90FF_C517_403F_8D9F_3F346508EDD1__INCLUDED_)
