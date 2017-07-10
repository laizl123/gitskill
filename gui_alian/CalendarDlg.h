//{{AFX_INCLUDES()
#include "lib\calendar.h"
//}}AFX_INCLUDES
#if !defined(AFX_CALENDARDLG_H__1A949BE7_7D50_4F1E_95BE_13AA6D75CB8E__INCLUDED_)
#define AFX_CALENDARDLG_H__1A949BE7_7D50_4F1E_95BE_13AA6D75CB8E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CalendarDlg.h : header file
//
#include "lib\BkDialog.h"
#include "FPSMiniCalendarCtrl.h"
#define WM_UPDATE_TODAY_STATIC WM_USER+888
/////////////////////////////////////////////////////////////////////////////
// CCalendarDlg dialog

#include "WinDef.h"	// Added by ClassView
class CCalendarDlg : public CBkDialog
{
// Construction
public:
	BOOL m_bUpdatedData;
	CCalendarDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCalendarDlg)
	enum { IDD = IDD_DLG_CALENDAR };
	CStatic	m_staticParkCount;
	CStatic	m_staticOutdialCount;
	CStatic	m_staticAvgProcessTimelength;
	CStatic	m_staticAvgCallTimelength;
	CFPSMiniCalendarCtrl m_calendarNow;

	void UpdatetatisticInfo(string& str);

	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCalendarDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCalendarDlg)
	virtual BOOL OnInitDialog();
	afx_msg UINT OnNcHitTest(CPoint point);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
//	afx_msg void OnClickCalendarNow();
//	afx_msg void OnKeyDownCalendarNow(short FAR* KeyCode, short Shift);
	afx_msg LRESULT OnUpdateTodayStatic(WPARAM wParam, LPARAM lParam);
	afx_msg void OnClickCalend(NMHDR* pNMHDR, LRESULT* pResult);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	CBrush m_brushBack;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CALENDARDLG_H__1A949BE7_7D50_4F1E_95BE_13AA6D75CB8E__INCLUDED_)
