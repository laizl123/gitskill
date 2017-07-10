#if !defined(AFX_COMPANYHISTORYDLG_H__2C50F0B1_A257_402F_B18B_B5FEF8C77CE5__INCLUDED_)
#define AFX_COMPANYHISTORYDLG_H__2C50F0B1_A257_402F_B18B_B5FEF8C77CE5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CompanyHistoryDlg.h : header file
//

#include "MyBkDialog.h"
#include "MyShadeButtonST.h"

/////////////////////////////////////////////////////////////////////////////
// CCompanyHistoryDlg dialog

class CCompanyHistoryDlg : public CMyBkDialog
{
// Construction
public:
	CCompanyHistoryDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCompanyHistoryDlg)
	enum { IDD = IDD_DLG_LOGIN_COMPANY };
	CMyShadeButtonST	m_btnClearCompany;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCompanyHistoryDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCompanyHistoryDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnBtnCompanyClear();
	//}}AFX_MSG
	afx_msg void OnBtnCompany(UINT nID);
	DECLARE_MESSAGE_MAP()
		
public:
	afx_msg LRESULT OnBtnDelete(WPARAM wParam, LPARAM lParam);
	void AddCompanyToHistory(CString strCompany);

private:
	UINT m_nBtnID[COMPANY_HISTORY_COUNT];
	CMyShadeButtonST *m_pBtnCompany[COMPANY_HISTORY_COUNT];
	int m_iCompanyCount;
	CRect m_rcBtnClearCompany;
	CRect m_rcWindow;
	int m_nBtnIDIndex;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMPANYHISTORYDLG_H__2C50F0B1_A257_402F_B18B_B5FEF8C77CE5__INCLUDED_)
