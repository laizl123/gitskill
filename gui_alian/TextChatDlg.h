#if !defined(AFX_TEXTCHATCHILDDLG_H__C63BFC9F_E8B5_45CB_AB2C_9146EADA29E3__INCLUDED_)
#define AFX_TEXTCHATCHILDDLG_H__C63BFC9F_E8B5_45CB_AB2C_9146EADA29E3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TextChatChildDlg.h : header file
//
#include "lib\BkDialog.h"
#include "XPButton.h"

/////////////////////////////////////////////////////////////////////////////
// CTextChatDlg dialog

class CTextChatDlg : public CBkDialog
{
public:
	CTextChatDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTextChatDlg)
	enum { IDD = IDD_DLG_TEXTCHAT };
	CXPButton	m_btnSend;
	CXPButton	m_btnCancel;
	CRichEditCtrl	m_OleTextChatSay;
	CRichEditCtrl	m_OleTextChatHistory;
	//}}AFX_DATA
	int m_nPageToLine;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTextChatDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support	
	virtual void OnOK();
	virtual void OnCancel();

	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTextChatDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeTextchatSay();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg UINT OnNcHitTest(CPoint point);
	afx_msg void OnBtnSend();
	afx_msg void OnBtnCancel();
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()

public:
	void PutChatContent(CString sChater, CString sChatContent,BOOL bSysmsg = FALSE,BOOL bClearSay = FALSE, BOOL bLocalAgentChat = TRUE);

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEXTCHATCHILDDLG_H__C63BFC9F_E8B5_45CB_AB2C_9146EADA29E3__INCLUDED_)
