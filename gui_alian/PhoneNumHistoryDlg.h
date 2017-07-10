#if !defined(AFX_PHONENUMHISTORY_H__D6337934_DF4E_4B2E_A9BC_D68936A87E54__INCLUDED_)
#define AFX_PHONENUMHISTORY_H__D6337934_DF4E_4B2E_A9BC_D68936A87E54__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PhoneNumHistory.h : header file
//

#include "lib\BkDialog.h"
#include "MyShadeButtonST.h"
#include "WinDef.h"	// Added by ClassView

/////////////////////////////////////////////////////////////////////////////
// CPhoneNumHistoryDlg dialog

class CPhoneNumHistoryDlg : public CMyBkDialog
{
// Construction
public:
	CPhoneNumHistoryDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPhoneNumHistoryDlg)
	enum { IDD = IDD_DLG_PHONENUM_HISTROY };
	CMyShadeButtonST m_btnClearAllPhoneNum;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPhoneNumHistoryDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPhoneNumHistoryDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnBtnPhonenumClear();
	//}}AFX_MSG
	afx_msg void OnBtnPhoneNum(UINT nID);
	
	DECLARE_MESSAGE_MAP()


public:
	afx_msg LRESULT OnBtnDelete(WPARAM wParam, LPARAM lParam);
	void AddPhoneNumToHistory(CString strPhoneNum);

private:
	CMyShadeButtonST *m_pBtnPhoneNum[PHONENUM_HISTORY_COUNT];
	int m_iPhoneNumCount;
	CRect m_rcBtnClearPhoneNum;
	CRect m_rcWindow;

	UINT m_nBtnID[PHONENUM_HISTORY_COUNT];
	int m_nBtnIDIndex;	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PHONENUMHISTORY_H__D6337934_DF4E_4B2E_A9BC_D68936A87E54__INCLUDED_)
