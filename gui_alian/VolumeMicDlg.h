#if !defined(AFX_VOLUMEMICDLG_H__EAD304A2_940F_4BC3_909A_96F39F803995__INCLUDED_)
#define AFX_VOLUMEMICDLG_H__EAD304A2_940F_4BC3_909A_96F39F803995__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VolumeMicDlg.h : header file
//

#include "MyBkDialog.h"
#include "MixerModuleBase.h"

/////////////////////////////////////////////////////////////////////////////
// CVolumeMicDlg dialog

class CVolumeMicDlg : public CMyBkDialog
{
// Construction
public:
	CVolumeMicDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CVolumeMicDlg)
	enum { IDD = IDD_DLG_VOLUME_MIC };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVolumeMicDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CVolumeMicDlg)
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnReleasedcaptureSliderMic(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CMixerVolume m_mixerMic;
	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VOLUMEMICDLG_H__EAD304A2_940F_4BC3_909A_96F39F803995__INCLUDED_)
