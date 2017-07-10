#if !defined(AFX_CLREDIT_H__9FF101AD_DED4_4F21_9357_08028D7C641B__INCLUDED_)
#define AFX_CLREDIT_H__9FF101AD_DED4_4F21_9357_08028D7C641B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ClrEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CClrEdit window

class CClrEdit : public CEdit
{
// Construction
public:
	CClrEdit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClrEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CClrEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CClrEdit)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	//}}AFX_MSG
	HBRUSH	m_hBakBrush;
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLREDIT_H__9FF101AD_DED4_4F21_9357_08028D7C641B__INCLUDED_)
