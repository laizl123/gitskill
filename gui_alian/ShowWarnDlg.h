#if !defined(AFX_SHOWWARN_H__207C06BE_1A7F_48E1_A2CD_9BA1C65D1970__INCLUDED_)
#define AFX_SHOWWARN_H__207C06BE_1A7F_48E1_A2CD_9BA1C65D1970__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ShowWarnDlg.h : header file
//

#include "XPButton.h"

/////////////////////////////////////////////////////////////////////////////
// CShowWarnDlg dialog

class CShowWarnDlg : public CDialog
{
// Construction
public:
	CShowWarnDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CShowWarnDlg)
	enum { IDD = IDD_DLG_SHOWWARN };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
	CXPButton m_btnClose;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShowWarnDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CShowWarnDlg)
		// NOTE: the ClassWizard will add member functions here
	afx_msg void OnBtnClose();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
		
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHOWWARN_H__207C06BE_1A7F_48E1_A2CD_9BA1C65D1970__INCLUDED_)
