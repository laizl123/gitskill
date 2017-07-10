#if !defined(AFX_VOLUMEEARPHONE_H__8301A05F_E7CD_4091_9A3A_03538CE92D4F__INCLUDED_)
#define AFX_VOLUMEEARPHONE_H__8301A05F_E7CD_4091_9A3A_03538CE92D4F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VolumeEarphone.h : header file
//
#include "MyBkDialog.h"
#include "MixerModuleBase.h"

/////////////////////////////////////////////////////////////////////////////
// CVolumeEarphoneDlg dialog

class CVolumeEarphoneDlg : public CMyBkDialog
{
// Construction
public:
	CVolumeEarphoneDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CVolumeEarphoneDlg)
	enum { IDD = IDD_DLG_VOLUME_EARPHONE };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVolumeEarphoneDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CVolumeEarphoneDlg)
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnReleasedcaptureSliderEarphone(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CMixerVolume m_mixerEarphone;
	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VOLUMEEARPHONE_H__8301A05F_E7CD_4091_9A3A_03538CE92D4F__INCLUDED_)
