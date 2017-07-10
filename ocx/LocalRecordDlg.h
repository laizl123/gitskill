#if !defined(AFX_LOCALRECORDDLG_H__3B922175_17D5_4948_9742_0B840F4FE5CD__INCLUDED_)
#define AFX_LOCALRECORDDLG_H__3B922175_17D5_4948_9742_0B840F4FE5CD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LocalRecordDlg.h : header file
//

#include "BkDialog.h"
#include "XPButton.h"
#include "MyIniFile.h"
/////////////////////////////////////////////////////////////////////////////
// CLocalRecordDlg dialog

class CLocalRecordDlg : public CBkDialog
{
// Construction
public:
	CLocalRecordDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLocalRecordDlg)
	enum { IDD = IDD_DLG_LOCALRECORD };
		// NOTE: the ClassWizard will add data members here
	CXPButton m_btnChangeRecPath;
	CXPButton m_btnLocalRecordClose;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLocalRecordDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLocalRecordDlg)
		// NOTE: the ClassWizard will add member functions here
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnBtnLocalRecordClose();
	afx_msg void OnBtnChangeRecPath();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CString m_strLocalRecPath;
	CMyIniFile m_config;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOCALRECORDDLG_H__3B922175_17D5_4948_9742_0B840F4FE5CD__INCLUDED_)
