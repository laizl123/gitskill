#if !defined(AFX_HELPTIPDLG_H__1FAF7BC5_CB63_4839_92B8_B95EB4ECE8C0__INCLUDED_)
#define AFX_HELPTIPDLG_H__1FAF7BC5_CB63_4839_92B8_B95EB4ECE8C0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HelpTipDlg.h : header file
//
#include "resource.h"
#include "BkDialog.h"
#include "XPButton.h"
/////////////////////////////////////////////////////////////////////////////
// CHelpTipDlg dialog

class CHelpTipDlg : public CBkDialog
{
	// Construction
public:
	CHelpTipDlg(CWnd* pParent = NULL);   // standard constructor
	CHelpTipDlg(CString strTitle, CString strContent, CWnd* pParent = NULL);
	
	// Dialog Data
	//{{AFX_DATA(CHelpTipDlg)
	enum { IDD = IDD_DLG_HELPTIP };
	// NOTE: the ClassWizard will add data members here
	CString	m_strContent;
	CString	m_strTitle;
	CXPButton m_btnHelptipClose;
	//}}AFX_DATA
	
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHelpTipDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	
	// Generated message map functions
	//{{AFX_MSG(CHelpTipDlg)
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBtnHelptipClose();
	afx_msg LRESULT OnNcHitTest(CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HELPTIPDLG_H__1FAF7BC5_CB63_4839_92B8_B95EB4ECE8C0__INCLUDED_)
