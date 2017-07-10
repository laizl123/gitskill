#if !defined(AFX_UPDATETIPPAGE_H__6D2BBCBF_8543_459A_8193_79EF78D7DC09__INCLUDED_)
#define AFX_UPDATETIPPAGE_H__6D2BBCBF_8543_459A_8193_79EF78D7DC09__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UpdateTipPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUpdateTipPage dialog

class CUpdateTipPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CUpdateTipPage)

// Construction
public:
	CUpdateTipPage();
	~CUpdateTipPage();
	void SetForceUpdate(BOOL bForceUpdate=TRUE) {	m_bForceUpdate=bForceUpdate;	} 
	void SetWhatNews(LPSTR szWhatNews);
// Dialog Data
	//{{AFX_DATA(CUpdateTipPage)
	enum { IDD = IDD_UPDATE_TIP };
	CRichEditCtrl	m_richWhatNews;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CUpdateTipPage)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL m_bForceUpdate;
	CHAR m_sWhatNews[1024];
	// Generated message map functions
	//{{AFX_MSG(CUpdateTipPage)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UPDATETIPPAGE_H__6D2BBCBF_8543_459A_8193_79EF78D7DC09__INCLUDED_)
