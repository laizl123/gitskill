// VolumeMicDlg.cpp : implementation file
//

#include "stdafx.h"
#include "icservingagentclient.h"
#include "VolumeMicDlg.h"
#include "Environment.h"
#include "Log.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern BOOL g_bMakelog;
/////////////////////////////////////////////////////////////////////////////
// CVolumeMicDlg dialog


CVolumeMicDlg::CVolumeMicDlg(CWnd* pParent /*=NULL*/)
	: CMyBkDialog(CVolumeMicDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVolumeMicDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CVolumeMicDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyBkDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVolumeMicDlg)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CVolumeMicDlg, CMyBkDialog)
	//{{AFX_MSG_MAP(CVolumeMicDlg)
	ON_WM_CTLCOLOR()
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_MIC, OnReleasedcaptureSliderMic)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVolumeMicDlg message handlers

BOOL CVolumeMicDlg::OnInitDialog() 
{
	CMyBkDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetBitmap(IDB_BMP_VOLUME);
	
	m_mixerMic.SubclassDlgItem( IDC_SLIDER_MIC, this );
	if(m_mixerMic.Init( MIXERLINE_COMPONENTTYPE_DST_WAVEIN,
		MIXERLINE_COMPONENTTYPE_SRC_MICROPHONE,
					   MIXERCONTROL_CONTROLTYPE_VOLUME, 
					   CMixerVolume::MAIN ) == 0)
	{
		m_mixerMic.Init( MIXERLINE_COMPONENTTYPE_DST_WAVEIN,
			NO_SOURCE,
			MIXERCONTROL_CONTROLTYPE_VOLUME, 
			CMixerVolume::MAIN );
	}
//	GetDlgItem(IDC_STATIC_MIC)->SetWindowText(m_mixerMic.GetLineName());

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CVolumeMicDlg::OnOK(){}
void CVolumeMicDlg::OnCancel(){}
HBRUSH CVolumeMicDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CMyBkDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	HBRUSH hbrDlg;
	if(nCtlColor==CTLCOLOR_STATIC)   
	{   
		hbrDlg=CreateSolidBrush(RGB(241, 247, 253));   
		pDC->SetBkColor(RGB(241, 247, 253));   
		pDC->SetTextColor(RGB(1, 1, 1));   
		return hbrDlg;   
	}   		
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CVolumeMicDlg::OnReleasedcaptureSliderMic(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here	
	CEnvironment &env = CEnvironment::Instance();

	CMixerValuer micphoneValue;
	if(micphoneValue.Init( MIXERLINE_COMPONENTTYPE_DST_WAVEIN,
		MIXERLINE_COMPONENTTYPE_SRC_MICROPHONE,
					   MIXERCONTROL_CONTROLTYPE_VOLUME, 
					   CMixerVolume::MAIN ) == 0)
	{
		if(micphoneValue.Init( MIXERLINE_COMPONENTTYPE_DST_WAVEIN,
			NO_SOURCE,
			MIXERCONTROL_CONTROLTYPE_VOLUME, 
			CMixerVolume::MAIN ))
		{
			env.m_dwMicphoneValue = micphoneValue.GetMixerValue();
		}
	}
	else
	{
		env.m_dwMicphoneValue = micphoneValue.GetMixerValue();
	}
	
	env.SaveEnvironmentToFile(GetDataFilesPath() + "\\Config.ini");

	AfxGetMainWnd()->PostMessage(WM_MY_VOLUME_UPDATESETTINGS, 2, env.m_dwMicphoneValue);
	*pResult = 0;
}
