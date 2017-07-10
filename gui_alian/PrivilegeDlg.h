#if !defined(AFX_PRIVILEGEDLG_H__B35CFBD8_A086_4577_B223_1C76CCA7AC7C__INCLUDED_)
#define AFX_PRIVILEGEDLG_H__B35CFBD8_A086_4577_B223_1C76CCA7AC7C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PrivilegeDlg.h : header file
//
#include "resource.h"
#include "PrivilegeDlg.h"
#include "lib\BkDialog.h"
#include "XPButton.h"

/////////////////////////////////////////////////////////////////////////////
// CPrivilegeDlg dialog

class CPrivilegeDlg : public CBkDialog
{
// Construction
public:
	CPrivilegeDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPrivilegeDlg)
	enum { IDD = IDD_DLG_PRIVILEGE };
	CComboBox	m_boxUserName;
	CString	m_strPassword;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPrivilegeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPrivilegeDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	// 
	CString m_strUserName;
	// 用户登录
	BOOL AdjustPrivilege();
	// 用户
	CStringArray m_arrPrivUser;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRIVILEGEDLG_H__B35CFBD8_A086_4577_B223_1C76CCA7AC7C__INCLUDED_)
