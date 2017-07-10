// NewSettingsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AgentPanelOcxCtl.h"
#include "NewSettingsDlg.h"
#include "HelpTipDlg.h"
#include "Environment.h"
#include "log.h"
#include "LocalRecordDlg.h"
#include "../../LibAudioTest/src/AudioDeviceTest.h"

using namespace audioDeviceTest;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CWnd* g_pMainFrame;
extern CString g_sAutoTransferNum;
extern PRODUCT_VER_INFO g_tagProductVerInfo;
extern CString g_strLogFilePath;
/////////////////////////////////////////////////////////////////////////////
// CNewSettingsDlg dialog
// add by lh.wang date:2016.02.15
int _stdcall VolumeNotify(int  nType,int  nVolume)
{
	
	return 1;
}
//end add

CNewSettingsDlg::CNewSettingsDlg(CWnd* pParent /*=NULL*/)
: CBkDialog(CNewSettingsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNewSettingsDlg)
	m_nBeepIndex =0;	
	m_bCaptureaudioTest = false;
	m_bRenderaudioTest  = false;
	//}}AFX_DATA_INIT
}

CNewSettingsDlg::~CNewSettingsDlg()
{
	RelaseAudioDeviceTest();
}

void CNewSettingsDlg::DoDataExchange(CDataExchange* pDX)
{
	CBkDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewSettingsDlg)
	DDX_Control(pDX, IDC_EDIT_FREQ, m_editFreq);
	DDX_Control(pDX, IDC_EDIT_DURA, m_editDura);
	DDX_Control(pDX, IDC_RADIO_BEEP1, m_radioBeep);
	DDX_Control(pDX, IDC_EDIT_OUTDIAL_HEAD_2, m_editOutdialHead2);
	DDX_Control(pDX, IDC_EDIT_OUTDIAL_HEAD_1, m_editOutdialHead1);
	DDX_Control(pDX, IDC_CHK_OUTDIAL_HEAD_2, m_chkOutdialHead2);
	DDX_Control(pDX, IDC_CHK_OUTDIAL_HEAD_1, m_chkOutdialHead1);
	DDX_Control(pDX, IDC_CHK_TRANSFER_TO_IVR, m_chkTransferToIVR);
	DDX_Control(pDX, IDC_BTN_CONFIRM, m_btnConfirm);
	DDX_Control(pDX, IDC_BTN_CANCEL, m_btnCancel);
	DDX_Control(pDX, IDC_EDIT_AUTOTRANSFER, m_editAutotransfer);
	DDX_Control(pDX, IDC_CHK_AUTOTRANSFER, m_chkAutotransfer);
	DDX_Control(pDX, IDC_CHK_RECORDER_SAVE_LOCAL, m_chkRecordLocalSave);
	DDX_Control(pDX, IDC_CHK_PC_SPEAKER, m_chkPCSpeaker);
	DDX_Control(pDX, IDC_CHK_AUTO_OFFHOOK, m_chkAutoOffhook);
	DDX_Control(pDX, IDC_BTN_LOCALRECORD_HELP, m_btnLocalrecordHelp);
	DDX_Control(pDX, IDC_BTN_INCOMINGCALL_HELP, m_btnIncomingcallHelp);
	DDX_Control(pDX, IDC_BTN_BEEP_HELP, m_btnBeepHelp);
	DDX_Control(pDX, IDC_BTN_BEEP_LISTEN, m_btnBeepListen);
	DDX_Radio(pDX, IDC_RADIO_BEEP1, m_nBeepIndex);
	DDX_Control(pDX, IDC_COMBO_DEVICE_AUDIO_RENDERERS, mComboAudioRenderDevices);
	DDX_Control(pDX, IDC_COMBO_DEVICE_AUDIO, mComboAudioDevices);
	DDX_Control(pDX, IDC_EDIT_START_URL, m_editStartUrl);
	DDX_Control(pDX, IDC_BTN_AUDIO_HELP, m_btnAudioHelp);
	DDX_Control(pDX, IDC_BTN_CAPTUREAUDIO_TEST, m_btnCaptureAudioTest);
	DDX_Control(pDX, IDC_BTN_RENDERAUDIO_TEST, m_btnRenderAudioTest);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CNewSettingsDlg, CBkDialog)
//{{AFX_MSG_MAP(CNewSettingsDlg)
ON_BN_CLICKED(IDC_BTN_LOCALRECORD_HELP, OnBtnLocalrecordHelp)
ON_BN_CLICKED(IDC_BTN_INCOMINGCALL_HELP, OnBtnIncomingcallHelp)
ON_BN_CLICKED(IDC_BTN_BEEP_HELP, OnBtnBeepHelp)
ON_WM_CTLCOLOR()
ON_BN_CLICKED(IDC_BTN_CANCEL, OnBtnCancel)
ON_BN_CLICKED(IDC_BTN_CONFIRM, OnBtnConfirm)
ON_BN_CLICKED(IDC_CHK_AUTOTRANSFER, OnChkAutotransfer)
ON_WM_NCHITTEST()
ON_BN_CLICKED(IDC_CHK_OUTDIAL_HEAD_1, OnChkOutdialHead1)
ON_BN_CLICKED(IDC_CHK_OUTDIAL_HEAD_2, OnChkOutdialHead2)
ON_BN_CLICKED(IDC_RADIO_BEEP1, OnRadioBeep1)
ON_BN_CLICKED(IDC_RADIO_BEEP2, OnRadioBeep2)
ON_BN_CLICKED(IDC_RADIO_BEEP3, OnRadioBeep3)
ON_BN_CLICKED(IDC_RADIO_BEEP4, OnRadioBeep4)
ON_BN_CLICKED(IDC_BTN_BEEP_LISTEN, OnButtonListen)
ON_BN_CLICKED(IDC_CHK_PC_SPEAKER, OnChkPcSpeaker)
ON_CBN_DROPDOWN(IDC_COMBO_DEVICE_AUDIO_RENDERERS, OnDropdownCombo)
ON_BN_CLICKED(IDC_BTN_AUDIO_HELP, OnButtonAudioHelp)
ON_BN_CLICKED(IDC_BTN_CAPTUREAUDIO_TEST, OnBtnCaptureaudioTest)
ON_BN_CLICKED(IDC_BTN_RENDERAUDIO_TEST, OnBtnRenderaudioTest)
ON_CBN_DROPDOWN(IDC_COMBO_DEVICE_AUDIO, OnDropdownCombo)
ON_WM_TIMER()
//}}AFX_MSG_MAP

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewSettingsDlg message handlers
// 2014-10-21
void CNewSettingsDlg::OnDropdownCombo() 
{
	// TODO: Add your control notification handler code here
	RenderDevicesUpdate();
	DevicesUpdate();
}

void CNewSettingsDlg::OnBtnLocalrecordHelp() 
{
	// TODO: Add your control notification handler code here
	CLocalRecordDlg dlg;
	dlg.DoModal();
}

void CNewSettingsDlg::OnBtnIncomingcallHelp() 
{
	// TODO: Add your control notification handler code here
	CHelpTipDlg dlg("开启自动接听", "开启此功能后，有电话呼入时，2秒钟后系统能够自动接听该呼入电话。");
	dlg.DoModal();
}

void CNewSettingsDlg::OnBtnBeepHelp() 
{
	// TODO: Add your control notification handler code here
	CHelpTipDlg dlg("蜂鸣器来电振铃", "开启此功能后，电脑主机上蜂鸣器将在来电时发出蜂鸣声。");
	dlg.DoModal();
}

BOOL CNewSettingsDlg::OnInitDialog() 
{
	CBkDialog::OnInitDialog();

	// TODO: Add extra initialization here
	SetBitmap(IDB_BMP_BG);
	
	SetValue();

	InitAudioDeviceTest();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH CNewSettingsDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		switch (pWnd->GetDlgCtrlID())
		{
		case IDC_STATIC_SETTING_TITLE:
			{
				CFont font;
				LOGFONT lf;
				memset(&lf, 0, sizeof(LOGFONT));       // zero out structure
				lf.lfHeight = 15;
				lf.lfWeight = FW_BOLD;
				strcpy(lf.lfFaceName, "宋体");        // request a face name "Arial"
				VERIFY(font.CreateFontIndirect(&lf));  // create the font
				pDC->SelectObject(&font);

				hbr = (HBRUSH)GetStockObject(NULL_BRUSH);//对于static来说，使用空刷子
				pDC->SetBkMode(TRANSPARENT);
			}
			break;
		default:
			{
				hbr=CreateSolidBrush(RGB(206, 227, 255));   
				pDC->SetTextColor(RGB(1, 1, 1));
				pDC->SetBkMode(TRANSPARENT); 
			}
			break;
		}
	}
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CNewSettingsDlg::OnBtnCancel() 
{
	// TODO: Add your control notification handler code here
	if(m_bCaptureaudioTest)
	{		
		CString strDeviceName;
		mComboAudioDevices.GetLBText(mComboAudioDevices.GetCurSel(),strDeviceName);
		StopTestAudioDevice();
		m_bCaptureaudioTest = false;
		m_btnCaptureAudioTest.SetWindowText("麦克风测试");
		m_btnRenderAudioTest.EnableWindow(TRUE);
	}
    
	if(m_bRenderaudioTest)
	{
		CString strDeviceName;
		mComboAudioRenderDevices.GetLBText(mComboAudioRenderDevices.GetCurSel(),strDeviceName);
		StopTestAudioDevice();
		m_btnRenderAudioTest.SetWindowText("扬声器测试");
		m_btnCaptureAudioTest.EnableWindow(TRUE);
		m_bRenderaudioTest= false;
	}
	
	ShowWindow(SW_HIDE);
}

void CNewSettingsDlg::OnBtnConfirm() 
{
	// TODO: Add your control notification handler code here
	DoUpdate();
	CEnvironment &env = CEnvironment::Instance();
	if (env.m_bOneKeyToPhone)
	{
		if (env.m_sOutPhoneNum == "")
		{
			CString sTitle = "";
			if(sTitle == "")
			{
				if (g_tagProductVerInfo.nVersionType & VerType_IPCC)
					sTitle = "警告--讯鸟座席端";
				else
					sTitle = "警告--启通宝";
			}
			
			MessageBox(sTitle, "自动转移到电话设置不能为空", MB_OK);
			
			return;
		}
		else
		{
			g_sAutoTransferNum = env.m_sOutPhoneNum.c_str();
		}
	}
	
	if(m_bCaptureaudioTest)
	{		
		CString strDeviceName;
		mComboAudioDevices.GetLBText(mComboAudioDevices.GetCurSel(),strDeviceName);
		StopTestAudioDevice();
		m_bCaptureaudioTest = false;
		m_btnCaptureAudioTest.SetWindowText("麦克风测试");
		m_btnRenderAudioTest.EnableWindow(TRUE);
	}
    
	if(m_bRenderaudioTest)
	{
		CString strDeviceName;
		mComboAudioRenderDevices.GetLBText(mComboAudioRenderDevices.GetCurSel(),strDeviceName);
		StopTestAudioDevice();
		m_btnRenderAudioTest.SetWindowText("扬声器测试");
		m_btnCaptureAudioTest.EnableWindow(TRUE);
		m_bRenderaudioTest= false;
	}
	
	ShowWindow(SW_HIDE);	
}

void CNewSettingsDlg::DoUpdate()
{
	UpdateData(TRUE);

	CEnvironment& env = CEnvironment::Instance();
	
	CString str;
	//record loacal save
	if(BST_CHECKED == m_chkRecordLocalSave.GetCheck())
		env.m_structRecorderSet.nRecorderMode = needRecorderAndSaveLocal;
	else
		env.m_structRecorderSet.nRecorderMode = noRecorder;
	//auto transfer
	env.m_bOneKeyToPhone = m_chkAutotransfer.GetCheck();
	m_editAutotransfer.GetWindowText(str);
	env.m_sOutPhoneNum = str;
	//auto offhook
	env.m_bAutoOffhook = m_chkAutoOffhook.GetCheck();
	env.m_bTransferToIVR = m_chkTransferToIVR.GetCheck();
	//pc speaker
	env.m_bPCSpeaker = m_chkPCSpeaker.GetCheck();
	//device
	int iIndex = mComboAudioDevices.GetCurSel();
	if (iIndex != -1)
	{
		env.m_nAudioCapDev = iIndex;
		CString deviceName;
		mComboAudioDevices.GetLBText(env.m_nAudioCapDev, deviceName);
		env.m_strAudioCapDevName = deviceName;		
	}
	
	iIndex = mComboAudioRenderDevices.GetCurSel();
	if (iIndex != -1)
	{
		env.m_nAudioRenderDev = iIndex;
		CString deviceName = "";
		mComboAudioRenderDevices.GetLBText(env.m_nAudioRenderDev, deviceName);
		env.m_strAudioRenderDevName = deviceName;
	}
	//outdial
	if (m_chkOutdialHead1.GetCheck())
	{
		m_editOutdialHead1.GetWindowText(str);
		env.m_strOutDialHead1 = str;
	}
	else
	{
		env.m_strOutDialHead1 = "";
	}

	if (m_chkOutdialHead2.GetCheck())
	{
		m_editOutdialHead2.GetWindowText(str);		
		env.m_strOutDialHead2 = str;
	}
	else
	{
		env.m_strOutDialHead2 = "";
	}
	
	m_editStartUrl.GetWindowText(str);
	env.m_strWebLoginUrl = str;
	
	// Beep
	env.m_nBeepIndex = m_nBeepIndex;
	
	CString strData;
	m_editFreq.GetWindowText(strData);
	int nFreq = atoi((const char* )strData);
	env.m_nBeepFreq = nFreq;
	
	m_editDura.GetWindowText(strData);
	int nDura = atoi((const char* )strData);
	env.m_nBeepDura = nDura;
	env.SaveEnvironmentToFile(GetDataFilesPath() + "\\Config.ini");
	((CAgentPanelOcxCtrl *)g_pMainFrame)->UpdateSettings();
}

void CNewSettingsDlg::SetValue()
{
	FillAudioDevices();
	FillAudioRenderDevices();
	
	CEnvironment& env = CEnvironment::Instance();
	//record loacal save	
	if(env.m_structRecorderSet.nRecorderMode == needRecorderAndSaveLocal)
		m_chkRecordLocalSave.SetCheck(BST_CHECKED);
	//auto transfer	
	m_chkAutotransfer.SetCheck(env.m_bOneKeyToPhone);
	if (env.m_bOneKeyToPhone)
		m_editAutotransfer.EnableWindow(TRUE);
	else
		m_editAutotransfer.EnableWindow(FALSE);
	m_editAutotransfer.SetWindowText(env.m_sOutPhoneNum.c_str());
	//auto offhook
	m_chkAutoOffhook.SetCheck(env.m_bAutoOffhook);
	m_chkTransferToIVR.SetCheck(env.m_bTransferToIVR);
	//pc speaker
	m_chkPCSpeaker.SetCheck(env.m_bPCSpeaker);
	//device	
	CString strItem;
	int iCount = mComboAudioDevices.GetCount();
	if (iCount > 0)
	{
		BOOL bFindAudioCapDev = FALSE;
		for(int i=1;i<=iCount;i++)
		{	
			env.m_nAudioCapDev = i-1;
			mComboAudioDevices.GetLBText(env.m_nAudioCapDev, strItem);
			if(strItem == env.m_strAudioCapDevName.c_str())   //如果从设备列表中找到了配置文件中的设备
			{
				bFindAudioCapDev = TRUE;
				env.m_strAudioCapDevName = strItem;
				break;
			}
		}
		if (!bFindAudioCapDev)  //如果设备列表中找不到配置文件中的设备，就选用默认设备，并刷新配置文件
		{
			env.m_nAudioCapDev=0;
			mComboAudioDevices.GetLBText(0, strItem);
			env.m_strAudioCapDevName = strItem;
		}
		
        mComboAudioDevices.SetCurSel(env.m_nAudioCapDev);
	}
	else
	{
		env.m_nAudioCapDev = 0;
		env.m_strAudioCapDevName = "";
	}
	
	iCount = mComboAudioRenderDevices.GetCount();
	if (iCount > 0)
	{
		BOOL bFindAudioRenderDev = FALSE;
		for(int i=1;i<=iCount;i++)
		{	
			env.m_nAudioRenderDev = i-1;
			mComboAudioRenderDevices.GetLBText(env.m_nAudioRenderDev, strItem);
			if(strItem == env.m_strAudioRenderDevName.c_str()) //如果从设备列表中找到了配置文件中的设备
			{
				bFindAudioRenderDev = TRUE;
				env.m_strAudioRenderDevName = strItem;
				break;
			}
		}
		if (!bFindAudioRenderDev)//如果设备列表中找不到配置文件中的设备，就选用默认设备，并刷新配置文件
		{
			env.m_nAudioRenderDev = 0;
			mComboAudioRenderDevices.GetLBText(env.m_nAudioRenderDev, strItem);
			env.m_strAudioRenderDevName = strItem;
		}
		
		mComboAudioRenderDevices.SetCurSel(env.m_nAudioRenderDev);
	}
	else
	{
		env.m_nAudioRenderDev = 0;
		env.m_strAudioRenderDevName = "";
	}
	//broswer
	m_editStartUrl.SetWindowText(env.m_strWebLoginUrl.c_str());
	
	//outdial
	if (env.m_strOutDialHead1 != "")
	{
		m_chkOutdialHead1.SetCheck(BST_CHECKED);
		m_editOutdialHead1.EnableWindow(TRUE);
		m_editOutdialHead1.SetWindowText(env.m_strOutDialHead1.c_str());
	}
	if (env.m_strOutDialHead2 != "")
	{
		m_chkOutdialHead2.SetCheck(BST_CHECKED);
		m_editOutdialHead2.EnableWindow(TRUE);
		m_editOutdialHead2.SetWindowText(env.m_strOutDialHead2.c_str());
	}
	
	//Beep
	m_nBeepIndex = env.m_nBeepIndex;

	CString strData;
	strData.Format("%d", env.m_nBeepFreq);
	m_editFreq.SetWindowText(strData);

	strData.Format("%d", env.m_nBeepDura);
	m_editDura.SetWindowText(strData);
	// 
	BOOL bEnable = env.m_bPCSpeaker;
	GetDlgItem(IDC_RADIO_BEEP1)->EnableWindow(bEnable);
	GetDlgItem(IDC_RADIO_BEEP2)->EnableWindow(bEnable);
	GetDlgItem(IDC_RADIO_BEEP3)->EnableWindow(bEnable);
	GetDlgItem(IDC_RADIO_BEEP4)->EnableWindow(bEnable);
	
	if(bEnable == TRUE && m_nBeepIndex == 3)
	{
		m_editDura.EnableWindow(TRUE);
		m_editFreq.EnableWindow(TRUE);		
	}
	else
	{
		m_editDura.EnableWindow(FALSE);
		m_editFreq.EnableWindow(FALSE);		
	}
	UpdateData(FALSE);
	
	env.SaveEnvironmentToFile(GetDataFilesPath() + "\\Config.ini");
}

void CNewSettingsDlg::OnOK(){}
void CNewSettingsDlg::OnCancel(){}


void CNewSettingsDlg::FillAudioDevices(void)
{
	mComboAudioDevices.ResetContent();
	
	vector<string> captureDeviceList;
	GetAudioRecordDeviceList(captureDeviceList);
	for (int i = 0; i < captureDeviceList.size(); i++){
		mComboAudioDevices.AddString(captureDeviceList[i].c_str());
	}

}

void CNewSettingsDlg::FillAudioRenderDevices( void )
{
	mComboAudioRenderDevices.ResetContent();

	vector<string> playOutDeviceList;
	GetAudioPlayOutDeviceList(playOutDeviceList);
	for (int i = 0; i < playOutDeviceList.size(); i++){
		mComboAudioRenderDevices.AddString(playOutDeviceList[i].c_str());
	}
}

void CNewSettingsDlg::OnChkAutotransfer() 
{
	// TODO: Add your control notification handler code here
	if (m_chkAutotransfer.GetCheck() == BST_CHECKED)
		m_editAutotransfer.EnableWindow(TRUE);
	else
		m_editAutotransfer.EnableWindow(FALSE);
}

LRESULT CNewSettingsDlg::OnNcHitTest(CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	return HTCAPTION;
	//return CBkDialog::OnNcHitTest(point);
}

void CNewSettingsDlg::OnChkOutdialHead1() 
{
	// TODO: Add your control notification handler code here
	if (m_chkOutdialHead1.GetCheck() == BST_CHECKED)
		m_editOutdialHead1.EnableWindow(TRUE);
	else
		m_editOutdialHead1.EnableWindow(FALSE);
}

void CNewSettingsDlg::OnChkOutdialHead2() 
{
	// TODO: Add your control notification handler code here
	if (m_chkOutdialHead2.GetCheck() == BST_CHECKED)
		m_editOutdialHead2.EnableWindow(TRUE);
	else
		m_editOutdialHead2.EnableWindow(FALSE);
}

void CNewSettingsDlg::OnRadioBeepSelect() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_nBeepIndex == 3)
	{
		m_editFreq.EnableWindow(TRUE);
		m_editDura.EnableWindow(TRUE);
	}
	else
	{
		m_editFreq.EnableWindow(FALSE);
		m_editDura.EnableWindow(FALSE);
	}
}

void CNewSettingsDlg::OnRadioBeep1() 
{
	// TODO: Add your control notification handler code here
	OnRadioBeepSelect(); 
}

void CNewSettingsDlg::OnRadioBeep2() 
{
	// TODO: Add your control notification handler code here
	OnRadioBeepSelect(); 
}

void CNewSettingsDlg::OnRadioBeep3() 
{
	// TODO: Add your control notification handler code here
	OnRadioBeepSelect(); 
}

void CNewSettingsDlg::OnRadioBeep4() 
{
	// TODO: Add your control notification handler code here
	OnRadioBeepSelect(); 
}

void CNewSettingsDlg::OnButtonListen() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	CString strData;
	m_editFreq.GetWindowText(strData);
	int nFreq = atoi((const char* )strData);
	
	m_editDura.GetWindowText(strData);
	int nDura = atoi((const char* )strData);
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			MyBeep(m_nBeepIndex, nFreq, nDura);
		}
		Sleep(200);
	}
}

void CNewSettingsDlg::OnChkPcSpeaker() 
{
	// TODO: Add your control notification handler code here
	BOOL bEnable = FALSE;
	if(m_chkPCSpeaker.GetCheck() == BST_CHECKED)
	{
		bEnable = TRUE;
	}
	GetDlgItem(IDC_RADIO_BEEP1)->EnableWindow(bEnable);
	GetDlgItem(IDC_RADIO_BEEP2)->EnableWindow(bEnable);
	GetDlgItem(IDC_RADIO_BEEP3)->EnableWindow(bEnable);
	GetDlgItem(IDC_RADIO_BEEP4)->EnableWindow(bEnable);
	GetDlgItem(IDC_BTN_LISTEN)->EnableWindow(bEnable);
	
	if(bEnable == TRUE && m_nBeepIndex == 3)
	{
		m_editDura.EnableWindow(TRUE);
		m_editFreq.EnableWindow(TRUE);		
	}
	else
	{
		m_editDura.EnableWindow(FALSE);
		m_editFreq.EnableWindow(FALSE);		
	}
}

void CNewSettingsDlg::MyBeep(int nIndex, int freq, int dura)
{
	if(nIndex == 0)
	{
		Beep(3800, 120);
	}
	else if(nIndex == 1)
	{
		Beep(3800, 240);
	}
	else if(nIndex == 2)
	{
		Beep(3800, 480);
	}
	else
	{
		Beep(freq, dura);
	}
	Sleep(40);
}

void CNewSettingsDlg::DevicesUpdate()
{
	CEnvironment& env = CEnvironment::Instance();
	
	FillAudioDevices();
	int iCount = mComboAudioDevices.GetCount();
	if (iCount > 0)
	{
		CString strTemp;
		BOOL bMatched = FALSE;
		for (int i=0; i<iCount; i++)
		{
			mComboAudioDevices.GetLBText(i, strTemp);
			if (strTemp == env.m_strAudioCapDevName.c_str())
			{
				mComboAudioDevices.SetCurSel(i);
				bMatched = TRUE;
				break;
			}
		}
		
		if (!bMatched)
			mComboAudioDevices.SetCurSel(0);
	}
	
	DoUpdate();
}

void CNewSettingsDlg::RenderDevicesUpdate()
{
	CEnvironment& env = CEnvironment::Instance();
	FillAudioRenderDevices();
	int iCount = mComboAudioRenderDevices.GetCount();
	if (iCount > 0)
	{
		CString strTemp;
		BOOL bMatched = FALSE;
		for (int i=0; i<iCount; i++)
		{
			mComboAudioRenderDevices.GetLBText(i, strTemp);
			if (strTemp == env.m_strAudioRenderDevName.c_str())
			{
				mComboAudioRenderDevices.SetCurSel(i);
				bMatched = TRUE;
				break;
			}
		}
		
		if (!bMatched)
			mComboAudioRenderDevices.SetCurSel(0);
	}
	
	DoUpdate();
}

void CNewSettingsDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == 100)
	{
		KillTimer(100);
		RenderDevicesUpdate();
		DevicesUpdate();
	}
	
	CBkDialog::OnTimer(nIDEvent);
}

void CNewSettingsDlg::OnButtonAudioHelp() 
{
	// TODO: Add your control notification handler code here
	CHelpTipDlg dlg("音频设备说明", "(1),请点麦克风测试，对麦克风说话进行试听；\n (2),请点扬声器测试，试试能否听到声音。");
	dlg.DoModal();
}

void CNewSettingsDlg::OnBtnCaptureaudioTest() 
{
	// TODO: Add your control notification handler code here
	CString strCaptureDeviceName;
	mComboAudioDevices.GetLBText(mComboAudioDevices.GetCurSel(), strCaptureDeviceName);
	
	CString strRenderDeviceName;
	mComboAudioRenderDevices.GetLBText(mComboAudioRenderDevices.GetCurSel(), strRenderDeviceName);

	if(!m_bCaptureaudioTest)
	{
		TestAudioRecordDevice((string)strRenderDeviceName, (string)strCaptureDeviceName);
		m_bCaptureaudioTest = true;
		m_btnCaptureAudioTest.SetWindowText("停止测试");
		m_btnRenderAudioTest.EnableWindow(FALSE);
	}
	else
	{
		StopTestAudioDevice();
		m_bCaptureaudioTest = false;
		m_btnCaptureAudioTest.SetWindowText("麦克风测试");
		m_btnRenderAudioTest.EnableWindow(TRUE);
	}
}

void CNewSettingsDlg::OnBtnRenderaudioTest() 
{
	// TODO: Add your control notification handler code here
	CString strRenderDeviceName;
	mComboAudioRenderDevices.GetLBText(mComboAudioRenderDevices.GetCurSel(), strRenderDeviceName);
	
	if(!m_bRenderaudioTest)
	{
		TestAudioPlayOutDevice((string)strRenderDeviceName);
		m_bRenderaudioTest = true;
		m_btnRenderAudioTest.SetWindowText("停止测试");
		m_btnCaptureAudioTest.EnableWindow(FALSE);
	}
	else
	{
		StopTestAudioDevice();
		m_bRenderaudioTest = false;
		m_btnRenderAudioTest.SetWindowText("扬声器测试");
		m_btnCaptureAudioTest.EnableWindow(TRUE);
	}
}
