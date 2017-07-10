#if !defined(AFX_SENDSMSDLG_H__D95D805F_90D1_4C86_B2A0_AD06AE9F2455__INCLUDED_)
#define AFX_SENDSMSDLG_H__D95D805F_90D1_4C86_B2A0_AD06AE9F2455__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SendSMSDlg.h : header file
//
#include "lib\BkDialog.h"
#include "XPButton.h"
/////////////////////////////////////////////////////////////////////////////
// CSendSMSDlg dialog

class CSendSMSDlg : public CBkDialog
{
// Construction
public:
	CSendSMSDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSendSMSDlg)
	enum { IDD = IDD_DLG_SENDSMS };
	CXPButton	m_btnOK;
	CXPButton	m_btnCancel;
	CString	m_sSendNumber;
	CString	m_sSMSContent;
	//}}AFX_DATA
public:
	void SetPhoneNum(CString sendnum);
	

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSendSMSDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSendSMSDlg)
	virtual void OnOK();
	afx_msg LRESULT OnSMSSendSuccess(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnSMSSendFailed(WPARAM wParam,LPARAM lParam);
	virtual void OnCancel();
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	afx_msg void OnSetfocusSmsContent();
	afx_msg void OnKillfocusSmsContent();
	virtual BOOL OnInitDialog();
	afx_msg UINT OnNcHitTest(CPoint point);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBtnSend();
	afx_msg void OnBtnCancel();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SENDSMSDLG_H__D95D805F_90D1_4C86_B2A0_AD06AE9F2455__INCLUDED_)
