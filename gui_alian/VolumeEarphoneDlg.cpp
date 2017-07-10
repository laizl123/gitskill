// VolumeEarphone.cpp : implementation file
//

#include "stdafx.h"
#include "icservingagentclient.h"
#include "VolumeEarphoneDlg.h"
#include "Environment.h"
#include "Log.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern BOOL g_bMakelog;
/////////////////////////////////////////////////////////////////////////////
// CVolumeEarphoneDlg dialog
CVolumeEarphoneDlg::CVolumeEarphoneDlg(CWnd* pParent /*=NULL*/)
	: CMyBkDialog(CVolumeEarphoneDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVolumeEarphoneDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CVolumeEarphoneDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyBkDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVolumeEarphoneDlg)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CVolumeEarphoneDlg, CMyBkDialog)
	//{{AFX_MSG_MAP(CVolumeEarphoneDlg)
	ON_WM_CTLCOLOR()
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_EARPHONE, OnReleasedcaptureSliderEarphone)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVolumeEarphoneDlg message handlers

BOOL CVolumeEarphoneDlg::OnInitDialog() 
{
	CMyBkDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetBitmap(IDB_BMP_VOLUME);

	m_mixerEarphone.SubclassDlgItem(IDC_SLIDER_EARPHONE, this);
	m_mixerEarphone.Init( MIXERLINE_COMPONENTTYPE_DST_SPEAKERS,
		NO_SOURCE,
		MIXERCONTROL_CONTROLTYPE_VOLUME, 
					   CMixerVolume::MAIN );
//	GetDlgItem(IDC_STATIC_EARPHONE)->SetWindowText(m_mixerEarphone.GetLineName());

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CVolumeEarphoneDlg::OnOK(){}
void CVolumeEarphoneDlg::OnCancel(){}

HBRUSH CVolumeEarphoneDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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

void CVolumeEarphoneDlg::OnReleasedcaptureSliderEarphone(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CEnvironment &env = CEnvironment::Instance();
	
	CMixerValuer volumeValue;
	if(volumeValue.Init( MIXERLINE_COMPONENTTYPE_DST_SPEAKERS,
		NO_SOURCE,
		MIXERCONTROL_CONTROLTYPE_VOLUME, 
					   CMixerVolume::MAIN ))
	{
		env.m_dwMainVolume = volumeValue.GetMixerValue();
	}

	env.SaveEnvironmentToFile(GetDataFilesPath() + "\\Config.ini");
	
	AfxGetMainWnd()->PostMessage(WM_MY_VOLUME_UPDATESETTINGS, 1, env.m_dwMainVolume);
	*pResult = 0;
}
