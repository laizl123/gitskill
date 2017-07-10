#if !defined(AFX_TRANSFERTOIVRDLG_H__3EF36FB6_AF10_4A24_9C33_1266587940C5__INCLUDED_)
#define AFX_TRANSFERTOIVRDLG_H__3EF36FB6_AF10_4A24_9C33_1266587940C5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TransferToIVRDlg.h : header file
//

#include "lib\BkDialog.h"
#include "XPButton.h"

/////////////////////////////////////////////////////////////////////////////
// CTransferToIVRDlg dialog

class CTransferToIVRDlg : public CBkDialog
{
// Construction
public:
	CTransferToIVRDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTransferToIVRDlg)
	enum { IDD = IDD_DLG_TRANSFER_TO_IVR };
	CXPButton	m_btnSendIVRuuidata;
	CString	m_strTransferToIVR;
	CString m_strLanguageType;
	CString m_strOperationType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTransferToIVRDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTransferToIVRDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSendIvrUuidata();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CComboBox	m_cobOperationType;
	CComboBox	m_cobLanguageType;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRANSFERTOIVRDLG_H__3EF36FB6_AF10_4A24_9C33_1266587940C5__INCLUDED_)
