#if !defined(AFX_KILLSELFDLG_H__0FF6BC28_C6ED_4828_8B6E_56059F11E599__INCLUDED_)
#define AFX_KILLSELFDLG_H__0FF6BC28_C6ED_4828_8B6E_56059F11E599__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// KillselfDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CKillselfDlg dialog

class CKillselfDlg : public CDialog
{
// Construction
public:
	CKillselfDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CKillselfDlg)
	enum { IDD = IDD_DLG_KILLSELF };
	CButton	m_btnOK;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKillselfDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CKillselfDlg)
	afx_msg void OnBtnOk();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	int m_iCurrentTime;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KILLSELFDLG_H__0FF6BC28_C6ED_4828_8B6E_56059F11E599__INCLUDED_)
