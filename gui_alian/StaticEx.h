#if !defined(AFX_STATICEX_H__87FC600E_DE3D_487C_A1C8_047BD0460E33__INCLUDED_)
#define AFX_STATICEX_H__87FC600E_DE3D_487C_A1C8_047BD0460E33__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StaticEx.h : header file
//

#define WM_MY_DEPARTS_CLICKED WM_USER + 1032
/////////////////////////////////////////////////////////////////////////////
// CStaticEx window

class CStaticEx : public CStatic
{
	// Construction
public:
	CStaticEx(CString strText, CRect rcFrame, int iType = 1);
	
	// Attributes
public:
	
	// Operations
public:
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStaticEx)
public:
	virtual void PreSubclassWindow();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL
	
	// Implementation
public:
	virtual ~CStaticEx();
	
	// Generated message map functions
protected:
	BOOL m_bHover;
	//{{AFX_MSG(CStaticEx)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	//}}AFX_MSG
	afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMouseHover(WPARAM wParam, LPARAM lParam);
	
	DECLARE_MESSAGE_MAP()
		
public:
	void SetStaticText(CString strText);
	BOOL GetStaticShow();
	void SetStaticShow(BOOL bShow);
	void Move(CRect &rc, BOOL bRedraw = FALSE);
	
	CStaticEx *m_pNextStatic;
	CStaticEx *m_pPrevStatic;
	CString m_strName;   //优先姓名，没有姓名就是账号
	CString m_strAccount;  //账号
	CString m_strDepart;  //部门名称
	BOOL m_bExpand;
	int m_iType;
	CRect m_rcFrame;

private:
	CDC * m_pMemDC;
	CBitmap * m_pMemBitmap;
	CRect m_rcBtn;
	CRect m_rcText;
	CRect m_rcLogo;
	CString m_strText;   //完整名称
	BOOL m_bShow;
	BOOL m_bHotTrack;
	BOOL m_bHoverBtn;
	BOOL m_bMouseTrack;
	/*
	CToolTipCtrl m_tooltip;
	CToolInfo m_toolinfo;
	*/
	CFont fontDepart, fontAgent;
	CBrush brushBG, brushBGHover, brushBMP;
	CPen penBG, penBGNormal;
	CBrush brushFreeDepart, brushFreeDepartNormal;
	CBrush brushFreeAgent, brushFreeAgentNormal;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATICEX_H__87FC600E_DE3D_487C_A1C8_047BD0460E33__INCLUDED_)
