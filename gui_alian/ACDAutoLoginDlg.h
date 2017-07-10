#if !defined(AFX_ACDAUTOLOGINDLG_H__E0C53C70_568C_40CB_842A_489C1160D41D__INCLUDED_)
#define AFX_ACDAUTOLOGINDLG_H__E0C53C70_568C_40CB_842A_489C1160D41D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ACDAutoLoginDlg.h : header file
//

#include "lib\BkDialog.h"
/////////////////////////////////////////////////////////////////////////////
// CACDAutoLoginDlg dialog

class CACDAutoLoginDlg : public CBkDialog
{
// Construction
public:
	BOOL m_bEnter;
	int m_iTime;
	CACDAutoLoginDlg(CWnd* pParent = NULL);   // standard constructor
    CButton	m_btnClose;
// Dialog Data
	//{{AFX_DATA(CACDAutoLoginDlg)
	enum { IDD = IDD_DLG_ACDAUTOLOGIN };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CACDAutoLoginDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL
    
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CACDAutoLoginDlg)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBtnClose();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ACDAUTOLOGINDLG_H__E0C53C70_568C_40CB_842A_489C1160D41D__INCLUDED_)
