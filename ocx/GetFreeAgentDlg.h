#if !defined(AFX_GETFREEAGENTDLG_H__5E553B72_83C1_4CD4_A707_36C8B27C9FE9__INCLUDED_)
#define AFX_GETFREEAGENTDLG_H__5E553B72_83C1_4CD4_A707_36C8B27C9FE9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GetFreeAgentDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGetFreeAgentDlg dialog

class CGetFreeAgentDlg : public CDialog
{
// Construction
public:
	void ClearTreeItem();
	HTREEITEM FindItemByName(LPCSTR szItemName);
	void CallFreeAgent(HTREEITEM& hTreeItem);
	CGetFreeAgentDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGetFreeAgentDlg)
	enum { IDD = IDD_DLG_FREE_AGENT };
	CTreeCtrl	m_FreeAgentTree;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGetFreeAgentDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGetFreeAgentDlg)
	afx_msg void OnBtnCall();
	afx_msg void OnDblclkListFreeAgent(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	afx_msg void OnSelchangedListFreeAgent(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickListFreeAgent(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CWnd* m_pParent;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GETFREEAGENTDLG_H__5E553B72_83C1_4CD4_A707_36C8B27C9FE9__INCLUDED_)
