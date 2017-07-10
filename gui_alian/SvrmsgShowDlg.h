#if !defined(AFX_SVRMSGSHOWDLG_H__2BFFCB21_451F_4511_BA42_5481F0444105__INCLUDED_)
#define AFX_SVRMSGSHOWDLG_H__2BFFCB21_451F_4511_BA42_5481F0444105__INCLUDED_

#include "lib\BkDialog.h"
#include "XPButton.h"

/////////////////////////////////////////////////////////////////////////////
// CSvrmsgShowDlg dialog

class CSvrmsgShowDlg : public CBkDialog
{
// Construction
public:
	CSvrmsgShowDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSvrmsgShowDlg)
	enum { IDD = IDD_DLG_SVRMSGSHOW };
	CXPButton	m_btOK;
	BOOL	m_bShowCheck;
	CString	m_strContent;
	CString	m_strSender;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSvrmsgShowDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSvrmsgShowDlg)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CBrush m_brushBack;
	BOOL m_bVisShowBox;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SVRMSGSHOWDLG_H__2BFFCB21_451F_4511_BA42_5481F0444105__INCLUDED_)
