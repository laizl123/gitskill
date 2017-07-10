#if !defined(AFX_UPDATEDOWNPAGE_H__F9E811A9_EDB1_465A_89C0_AB17518C0797__INCLUDED_)
#define AFX_UPDATEDOWNPAGE_H__F9E811A9_EDB1_465A_89C0_AB17518C0797__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UpdateDownPage.h : header file
//
#include "DownloadFile.h"
/////////////////////////////////////////////////////////////////////////////
// CUpdateDownPage dialog
string CreateTempPath();

#define WM_GET_DOWN_INFO		WM_USER+1044
#define WM_DOWNLOAD_FINISH		WM_USER+1045
#define WM_DOWNLOAD_ERROR		WM_USER+1046

#define Update_TimeOut_TimerID	0x552

class CUpdateDownPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CUpdateDownPage)

// Construction
public:
	void SetForceUpdate(BOOL bForceUpdate=TRUE) {	m_bForceUpdate=bForceUpdate;	} 
	void SetUpdateFile(CString sUpdateFile) {	m_sUpdateFileName=sUpdateFile;	} 
	void SetClearReg(BOOL bClear=TRUE) { m_bClearReg = bClear;	}
	CUpdateDownPage();
	~CUpdateDownPage();

// Dialog Data
	//{{AFX_DATA(CUpdateDownPage)
	enum { IDD = IDD_UPDATE_DOWN };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA
public:
	static UINT ThreadDownSingleFile(LPVOID pParam );
	UINT func_Dwonload();
	DWORD SuspendThread();
	DWORD ResumeThread();
	DWORD ExitThread();
// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CUpdateDownPage)
	public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CDownloadFile m_DownFile;
	BOOL m_bForceUpdate;
	int m_iFullSize;
	int m_iCurrentSize;
	
	CString m_sUpdateFilePack;
	CString m_sUpdateFileName;

	// Generated message map functions
	//{{AFX_MSG(CUpdateDownPage)
	afx_msg LRESULT OnGetDownInfo(WPARAM wParam,LPARAM lParam);	
	afx_msg LRESULT OnDownloadFinish(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnDownloadError(WPARAM wParam,LPARAM lParam);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	CWinThread* m_pUpdateThread;
	BOOL m_bTerminateThread;
	BOOL m_bClearReg;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UPDATEDOWNPAGE_H__F9E811A9_EDB1_465A_89C0_AB17518C0797__INCLUDED_)
