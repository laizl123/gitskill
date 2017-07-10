#if !defined(AFX_NEWSETTINGSDLG_H__40F3223A_FB2A_44F7_85D3_0817F55D7A99__INCLUDED_)
#define AFX_NEWSETTINGSDLG_H__40F3223A_FB2A_44F7_85D3_0817F55D7A99__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewSettingsDlg.h : header file
//
#include "BkDialog.h"
#include "XPButton.h"
#include "resource.h"
/////////////////////////////////////////////////////////////////////////////
// CNewSettingsDlg dialog

class CNewSettingsDlg : public CBkDialog
{
// Construction
public:
	void RenderDevicesUpdate();
	void DevicesUpdate();
	CNewSettingsDlg(CWnd* pParent = NULL);   // standard constructor
	~CNewSettingsDlg();
// Dialog Data
	//{{AFX_DATA(CNewSettingsDlg)
	enum { IDD = IDD_DLG_MY_SETTINGS };
	CXPButton	m_btnAudioHelp;
	CXPButton	m_btnCaptureAudioTest;
	CXPButton	m_btnRenderAudioTest;
	bool    m_bCaptureaudioTest;
	bool    m_bRenderaudioTest;
	CEdit	m_editFreq;
	CEdit	m_editDura;
	CButton	m_radioBeep;
	CEdit	m_editOutdialHead2;
	CEdit	m_editOutdialHead1;
	CButton	m_chkOutdialHead2;
	CButton	m_chkOutdialHead1;
	CButton	m_chkTransferToIVR;
	CXPButton	m_btnConfirm;
	CXPButton	m_btnCancel;
	CEdit	m_editAutotransfer;
	CButton	m_chkAutotransfer;
	CButton	m_chkRecordLocalSave;
	CButton	m_chkPCSpeaker;
	CButton	m_chkAutoOffhook;
	CXPButton	m_btnLocalrecordHelp;
	CXPButton	m_btnIncomingcallHelp;
	CXPButton	m_btnBeepHelp;
	CXPButton	m_btnBeepListen;
	int		m_nBeepIndex;
	CEdit	m_editStartUrl;
	//}}AFX_DATA
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewSettingsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNewSettingsDlg)
	afx_msg void OnBtnLocalrecordHelp();
	afx_msg void OnBtnIncomingcallHelp();
	afx_msg void OnBtnBeepHelp();
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBtnCancel();
	afx_msg void OnBtnConfirm();
	afx_msg void OnChkAutotransfer();
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnChkOutdialHead1();
	afx_msg void OnChkOutdialHead2();
	afx_msg void OnRadioBeep1();
	afx_msg void OnRadioBeep2();
	afx_msg void OnRadioBeep3();
	afx_msg void OnRadioBeep4();
	afx_msg void OnButtonListen();
	afx_msg void OnChkPcSpeaker();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDropdownCombo();
	afx_msg void OnButtonAudioHelp();
	afx_msg void OnBtnCaptureaudioTest();
	afx_msg void OnBtnRenderaudioTest();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void SetValue();
	void DoUpdate();
	void FillAudioDevices(void);
	void FillAudioRenderDevices( void );
	void OnRadioBeepSelect();
	void MyBeep(int nIndex, int freq, int dura);

	CComboBox mComboAudioRenderDevices;
	CComboBox mComboAudioDevices;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWSETTINGSDLG_H__40F3223A_FB2A_44F7_85D3_0817F55D7A99__INCLUDED_)
