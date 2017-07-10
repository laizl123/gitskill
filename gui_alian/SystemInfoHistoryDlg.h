#if !defined(AFX_SYSTEMINFOHISTORYDLG_H__9C50031F_8E48_4FBB_9E7D_8DA410CA1EC1__INCLUDED_)
#define AFX_SYSTEMINFOHISTORYDLG_H__9C50031F_8E48_4FBB_9E7D_8DA410CA1EC1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SystemInfoHistoryDlg.h : header file
//
#include "lib\BkDialog.h"
#include "lib\BtnST.h"
/////////////////////////////////////////////////////////////////////////////
// CSystemInfoHistoryDlg dialog

class CSystemInfoHistoryDlg : public CBkDialog
{
// Construction
public:
	CSystemInfoHistoryDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSystemInfoHistoryDlg)
	enum { IDD = IDD_DLG_SYSINFO_HISTORY };
	CButtonST	m_btnSysInfoClose;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSystemInfoHistoryDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSystemInfoHistoryDlg)
	afx_msg UINT OnNcHitTest(CPoint point);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSysinfoClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CRichEditCtrl m_editSysInfoHistory;

public:
	void AddSysInfoHistory(CString strContent);

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SYSTEMINFOHISTORYDLG_H__9C50031F_8E48_4FBB_9E7D_8DA410CA1EC1__INCLUDED_)
