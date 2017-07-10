#if !defined(AFX_GETTALKAGENTDLG_H__B974C459_AF7D_4B5C_A0C8_925583E7C237__INCLUDED_)
#define AFX_GETTALKAGENTDLG_H__B974C459_AF7D_4B5C_A0C8_925583E7C237__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GetTalkAgentDlg.h : header file
//

#include <map>
using namespace std;
#include "ConsoleMessageDef.h"
#include "Spliter.h"

/////////////////////////////////////////////////////////////////////////////
// CGetTalkAgentDlg dialog

class CGetTalkAgentDlg : public CDialog
{
	// Construction
public:
	CGetTalkAgentDlg(CWnd* pParent = NULL);   // standard constructor
	
	// Dialog Data
	//{{AFX_DATA(CGetTalkAgentDlg)
	enum { IDD = IDD_DLG_TALK_AGENT };
	CTreeCtrl	m_TalkAgentTree;
	//}}AFX_DATA
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGetTalkAgentDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	
	// Generated message map functions
	//{{AFX_MSG(CGetTalkAgentDlg)
	afx_msg void OnBtnMonit();
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	HTREEITEM FindItemByName(LPCSTR szItemName);
	void MonitAgent(HTREEITEM& hTreeItem);
	void ClearTreeItem();
	map<string, pair<unsigned long, unsigned short> > m_ItemMap;
	
private:
	CWnd* m_pParent;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GETTALKAGENTDLG_H__B974C459_AF7D_4B5C_A0C8_925583E7C237__INCLUDED_)
