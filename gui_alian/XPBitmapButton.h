#if !defined(AFX_XPBITMAPBUTTON_H__4D09E092_48C2_4BC5_9FBB_ECDB8928673B__INCLUDED_)
#define AFX_XPBITMAPBUTTON_H__4D09E092_48C2_4BC5_9FBB_ECDB8928673B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// XPBitmapButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CXPBitmapButton window

class CXPBitmapButton : public CButton
{
// Construction
public:
	CXPBitmapButton();

// Attributes
public:
	void SetBkColor(COLORREF clr);
	void LoadBitmaps(UINT nIDBmpLeave, UINT nIDBmpHover = 0, UINT nIDBmpClick = 0, UINT nIDBmpDisable = 0);	

	void LoadBitmaps(HBITMAP hBmpLeave, HBITMAP hBmpHover = NULL, HBITMAP hBmpClick = NULL, HBITMAP hBmpDisable = NULL);	
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXPBitmapButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CXPBitmapButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(CXPBitmapButton)
		// NOTE - the ClassWizard will add and remove member functions here.
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMouseHover(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG


	DECLARE_MESSAGE_MAP()

protected:
	// 设置背景色
	COLORREF m_clrBack;
	// 是否在上面
	BOOL m_bOver;
	// 跟踪鼠标
	BOOL m_bTracking;
	// BITMAP位图
	HBITMAP m_aBitmap[4];
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XPBITMAPBUTTON_H__4D09E092_48C2_4BC5_9FBB_ECDB8928673B__INCLUDED_)
