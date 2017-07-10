// AgentPanelOcxCtl.cpp : Implementation of the CAgentPanelOcxCtrl ActiveX Control class.

#include "stdafx.h"
#include "AgentPanelOcx.h"
#include "AgentPanelOcxCtl.h"
#include "AgentPanelOcxPpg.h"
#include <comdef.h>
#include "Log.h"
#include "Environment.h"
#include "SmsSendModule.h"
#include "KillselfDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CWnd* g_pMainFrame;
extern BOOL g_bMakelog;
extern BOOL g_bIsSuper;
extern BOOL g_bIsMasterSuper;
extern CString g_strCorp;
extern CString g_strDepartment;
extern CString g_strManagerID;
extern short g_iClientState;
extern int g_iSuperAgentType;
extern CString g_strAccount;
extern PRODUCT_VER_INFO g_tagProductVerInfo;
extern string SMSSend_URL;
extern CString g_strLogFilePath;
extern long g_iSourceIp;
extern long g_iSourcePort;


bool g_bPackIntegrity = true;
bool ChechPackIntegrity()
{
	const int nFileCount = 1;
	CString sFileNames[nFileCount] = {
		"IPCCService.exe"
	};
	
	HANDLE hFind;
	for (int i=0; i<nFileCount; i++)
	{
		WIN32_FIND_DATAA FindFileData;
		CString sFilePathName = GetMoudlePath() + "\\" + sFileNames[i];
		hFind = FindFirstFileA(sFilePathName, &FindFileData);
		if (hFind == INVALID_HANDLE_VALUE) 
			return false;
	}
	
	FindClose(hFind);
	return true;
}

/////////////////////////////////////////////////////////////////////////////   
//   DllGetClassObject   
extern   "C" 
STDAPI   DllGetClassObject(REFCLSID   rclsid,   REFIID   riid,   LPVOID*   ppv)   
{   
	AFX_MANAGE_STATE(AfxGetStaticModuleState());   
	return AfxDllGetClassObject(rclsid,   riid,   ppv);   
}   

/////////////////////////////////////////////////////////////////////////////   
//   DllCanUnloadNow   

extern   "C"   
STDAPI   DllCanUnloadNow(void)   
{   
	AFX_MANAGE_STATE(AfxGetStaticModuleState());   
	return AfxDllCanUnloadNow();   
}

IMPLEMENT_DYNCREATE(CAgentPanelOcxCtrl, COleControl)

/////////////////////////////////////////////////////////////////////////////
// Message map
BOOL CAgentPanelOcxCtrl::m_bStopBeep = FALSE;

BEGIN_MESSAGE_MAP(CAgentPanelOcxCtrl, COleControl)
//{{AFX_MSG_MAP(CAgentPanelOcxCtrl)
ON_WM_DESTROY()
ON_WM_TIMER()
ON_WM_CREATE()
ON_WM_COPYDATA()
//}}AFX_MSG_MAP
ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
ON_MESSAGE(WM_SOCKMSG, OnSockMsg)
ON_MESSAGE(WM_SMS_SENDSUCCES, OnSMSSendSuccess)
ON_MESSAGE(WM_SMS_SENDFAILED, OnSMSSendFailed)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CAgentPanelOcxCtrl, COleControl)
//{{AFX_DISPATCH_MAP(CAgentPanelOcxCtrl)
DISP_FUNCTION(CAgentPanelOcxCtrl, "ActionLogon", ActionLogon, VT_EMPTY, VTS_BSTR VTS_BSTR VTS_I2 VTS_BSTR)
DISP_FUNCTION(CAgentPanelOcxCtrl, "ActionLogon2", ActionLogon2, VT_EMPTY, VTS_BSTR VTS_BSTR VTS_BSTR VTS_I2 VTS_BSTR)
DISP_FUNCTION(CAgentPanelOcxCtrl, "ActionReset", ActionReset, VT_EMPTY, VTS_NONE)
DISP_FUNCTION(CAgentPanelOcxCtrl, "ActionLogout", ActionLogout, VT_EMPTY, VTS_NONE)
DISP_FUNCTION(CAgentPanelOcxCtrl, "ActionLogonAgain", ActionLogonAgain, VT_EMPTY, VTS_NONE)
DISP_FUNCTION(CAgentPanelOcxCtrl, "ActionCallDepartment", ActionCallDepartment, VT_EMPTY, VTS_BSTR)
DISP_FUNCTION(CAgentPanelOcxCtrl, "ActionCallAgent", ActionCallAgent, VT_EMPTY, VTS_BSTR)
DISP_FUNCTION(CAgentPanelOcxCtrl, "ActionCallOtherAgent", ActionCallOtherAgent, VT_EMPTY, VTS_BSTR)
DISP_FUNCTION(CAgentPanelOcxCtrl, "ActionCallPstn", ActionCallPstn, VT_EMPTY, VTS_BSTR)
DISP_FUNCTION(CAgentPanelOcxCtrl, "ActionCallExtNum", ActionCallExtNum, VT_EMPTY, VTS_BSTR)
DISP_FUNCTION(CAgentPanelOcxCtrl, "ActionCallOtherDepartment", ActionCallOtherDepartment, VT_EMPTY, VTS_BSTR)
DISP_FUNCTION(CAgentPanelOcxCtrl, "ActionOnHook", ActionOnHook, VT_EMPTY, VTS_NONE)
DISP_FUNCTION(CAgentPanelOcxCtrl, "ActionOffHook", ActionOffHook, VT_EMPTY, VTS_NONE)
DISP_FUNCTION(CAgentPanelOcxCtrl, "ActionPark", ActionPark, VT_EMPTY, VTS_NONE)
DISP_FUNCTION(CAgentPanelOcxCtrl, "ActionUnPark", ActionUnPark, VT_EMPTY, VTS_NONE)
DISP_FUNCTION(CAgentPanelOcxCtrl, "ActionProcess", ActionProcess, VT_EMPTY, VTS_NONE)
DISP_FUNCTION(CAgentPanelOcxCtrl, "ActionUnProcess", ActionUnProcess, VT_EMPTY, VTS_NONE)
DISP_FUNCTION(CAgentPanelOcxCtrl, "ActionHold", ActionHold, VT_EMPTY, VTS_NONE)
DISP_FUNCTION(CAgentPanelOcxCtrl, "ActionUnHold", ActionUnHold, VT_EMPTY, VTS_NONE)
DISP_FUNCTION(CAgentPanelOcxCtrl, "ActionTransfer", ActionTransfer, VT_EMPTY, VTS_NONE)
DISP_FUNCTION(CAgentPanelOcxCtrl, "ActionAutoTransfer", ActionAutoTransfer, VT_EMPTY, VTS_NONE)
DISP_FUNCTION(CAgentPanelOcxCtrl, "ActionStartMonit", ActionStartMonit, VT_EMPTY, VTS_BSTR VTS_BSTR VTS_BSTR)
DISP_FUNCTION(CAgentPanelOcxCtrl, "ActionStopMonit", ActionStopMonit, VT_EMPTY, VTS_NONE)
DISP_FUNCTION(CAgentPanelOcxCtrl, "ActionForceDisconnect", ActionForceDisconnect, VT_EMPTY, VTS_BSTR)
DISP_FUNCTION(CAgentPanelOcxCtrl, "ActionGetFullFreeAgentInfo", ActionGetFullFreeAgentInfo, VT_EMPTY, VTS_NONE)
DISP_FUNCTION(CAgentPanelOcxCtrl, "ActionGetGroupInfo", ActionGetGroupInfo, VT_EMPTY, VTS_NONE)
DISP_FUNCTION(CAgentPanelOcxCtrl, "ActionGetOneGroupFreeAgentInfo", ActionGetOneGroupFreeAgentInfo, VT_EMPTY, VTS_BSTR)
DISP_FUNCTION(CAgentPanelOcxCtrl, "ActionGetTalkingAgent", ActionGetTalkingAgent, VT_EMPTY, VTS_NONE)
DISP_FUNCTION(CAgentPanelOcxCtrl, "ActionSendDTMF", ActionSendDTMF, VT_EMPTY, VTS_I2)
DISP_FUNCTION(CAgentPanelOcxCtrl, "ActionChangePassword", ActionChangePassword, VT_EMPTY, VTS_BSTR VTS_BSTR VTS_BSTR)
DISP_FUNCTION(CAgentPanelOcxCtrl, "ActionChangeEarphoneVolume", ActionChangeEarphoneVolume, VT_EMPTY, VTS_I2)
DISP_FUNCTION(CAgentPanelOcxCtrl, "ActionChangeMicVolume", ActionChangeMicVolume, VT_EMPTY, VTS_I2)
DISP_FUNCTION(CAgentPanelOcxCtrl, "ActionSendSMS", ActionSendSMS, VT_EMPTY, VTS_BSTR VTS_BSTR)
DISP_FUNCTION(CAgentPanelOcxCtrl, "ActionSendChat", ActionSendChat, VT_EMPTY, VTS_BSTR)
DISP_FUNCTION(CAgentPanelOcxCtrl, "ConfigPortSettings", ConfigPortSettings, VT_EMPTY, VTS_BOOL VTS_I4 VTS_I4 VTS_I4 VTS_BOOL VTS_BOOL)
DISP_FUNCTION(CAgentPanelOcxCtrl, "ConfigRecSettings", ConfigRecSettings, VT_EMPTY, VTS_BOOL)
DISP_FUNCTION(CAgentPanelOcxCtrl, "ConfigOutDialSettings", ConfigOutDialSettings, VT_EMPTY, VTS_BOOL VTS_BOOL VTS_BSTR VTS_BSTR)
DISP_FUNCTION(CAgentPanelOcxCtrl, "ConfigSoundSettings", ConfigSoundSettings, VT_EMPTY, VTS_BOOL VTS_BOOL VTS_BOOL VTS_BOOL)
DISP_FUNCTION(CAgentPanelOcxCtrl, "GetLoginManner", GetLoginManner, VT_I2, VTS_NONE)
DISP_FUNCTION(CAgentPanelOcxCtrl, "GetDeptment", GetDeptment, VT_BSTR, VTS_NONE)
DISP_FUNCTION(CAgentPanelOcxCtrl, "GetCorp", GetCorp, VT_BSTR, VTS_NONE)
DISP_FUNCTION(CAgentPanelOcxCtrl, "GetCallType", GetCallType, VT_I2, VTS_NONE)
DISP_FUNCTION(CAgentPanelOcxCtrl, "GetCallFrom", GetCallFrom, VT_BSTR, VTS_NONE)
DISP_FUNCTION(CAgentPanelOcxCtrl, "GetPrivateData", GetPrivateData, VT_BSTR, VTS_NONE)
DISP_FUNCTION(CAgentPanelOcxCtrl, "GetRecInvokeID", GetRecInvokeID, VT_BSTR, VTS_NONE)
DISP_FUNCTION(CAgentPanelOcxCtrl, "GetClientState", GetClientState, VT_I2, VTS_NONE)
DISP_FUNCTION(CAgentPanelOcxCtrl, "GetLogonType", GetLogonType, VT_I2, VTS_NONE)
DISP_FUNCTION(CAgentPanelOcxCtrl, "GetCallPartyType", GetCallPartyType, VT_I2, VTS_NONE)
DISP_FUNCTION(CAgentPanelOcxCtrl, "GetAgentHasLogon", GetAgentHasLogon, VT_BOOL, VTS_NONE)
DISP_FUNCTION(CAgentPanelOcxCtrl, "Initialize", Initialize, VT_BOOL, VTS_I2 VTS_BSTR)
DISP_FUNCTION(CAgentPanelOcxCtrl, "Exit", Exit, VT_EMPTY, VTS_NONE)
DISP_FUNCTION(CAgentPanelOcxCtrl, "GetRoleInCompany", GetRoleInCompany, VT_I2, VTS_NONE)
DISP_FUNCTION(CAgentPanelOcxCtrl, "GetAgentAccount", GetAgentAccount, VT_BSTR, VTS_NONE)
DISP_FUNCTION(CAgentPanelOcxCtrl, "GetIsCCNUser", GetIsCCNUser, VT_BOOL, VTS_NONE)
DISP_FUNCTION(CAgentPanelOcxCtrl, "GetAgentType", GetAgentType, VT_I2, VTS_NONE)
DISP_FUNCTION(CAgentPanelOcxCtrl, "GetIsSMSEnabled", GetIsSMSEnabled, VT_BOOL, VTS_NONE)
DISP_FUNCTION(CAgentPanelOcxCtrl, "GetAgentExtNum", GetAgentExtNum, VT_BSTR, VTS_NONE)
DISP_FUNCTION(CAgentPanelOcxCtrl, "GetAgentPhoneNo", GetAgentPhoneNo, VT_BSTR, VTS_NONE)
DISP_FUNCTION(CAgentPanelOcxCtrl, "GetManagerID", GetManagerID, VT_BSTR, VTS_NONE)
DISP_FUNCTION(CAgentPanelOcxCtrl, "GetIsSuperAgent", GetIsSuperAgent, VT_BOOL, VTS_NONE)
DISP_FUNCTION(CAgentPanelOcxCtrl, "GetIsMasterSuperAgent", GetIsMasterSuperAgent, VT_BOOL, VTS_NONE)
DISP_FUNCTION(CAgentPanelOcxCtrl, "ActionSendStrMsg", ActionSendStrMsg, VT_EMPTY, VTS_BSTR VTS_BSTR)
DISP_FUNCTION(CAgentPanelOcxCtrl, "GetRemindTime", GetRemindTime, VT_BSTR, VTS_NONE)
DISP_FUNCTION(CAgentPanelOcxCtrl, "ActionSettings", ActionSettings, VT_EMPTY, VTS_NONE)
DISP_FUNCTION(CAgentPanelOcxCtrl, "ActionMonit", ActionMonit, VT_EMPTY, VTS_NONE)
DISP_FUNCTION(CAgentPanelOcxCtrl, "ActionAgentOutDial", ActionAgentOutDial, VT_EMPTY, VTS_BSTR VTS_I2)
DISP_FUNCTION(CAgentPanelOcxCtrl, "GetIsMonit", GetIsMonit, VT_BOOL, VTS_NONE)
DISP_FUNCTION(CAgentPanelOcxCtrl, "GetSMSParamsInfo", GetSMSParamsInfo, VT_BSTR, VTS_NONE)
DISP_FUNCTION(CAgentPanelOcxCtrl, "GetAllSettings", GetAllSettings, VT_BSTR, VTS_NONE)
DISP_FUNCTION(CAgentPanelOcxCtrl, "GetBriefStatisticInfo", GetBriefStatisticInfo, VT_BSTR, VTS_BSTR)
DISP_FUNCTION(CAgentPanelOcxCtrl, "ActionSaveBriefStatisticInfo", ActionSaveBriefStatisticInfo, VT_EMPTY, VTS_NONE)
DISP_FUNCTION(CAgentPanelOcxCtrl, "ActionSetMuteMode", ActionSetMuteMode, VT_EMPTY, VTS_BOOL)
DISP_FUNCTION(CAgentPanelOcxCtrl, "ActionTransferToIVR", ActionTransferToIVR, VT_EMPTY, VTS_BSTR VTS_BOOL VTS_BSTR VTS_BSTR VTS_I2)
DISP_FUNCTION(CAgentPanelOcxCtrl, "GetTransferToIVRParamsInfo", GetTransferToIVRParamsInfo, VT_BSTR, VTS_NONE)
DISP_FUNCTION(CAgentPanelOcxCtrl, "GetIsCallFromACD", GetIsCallFromACD, VT_BOOL, VTS_NONE)
DISP_FUNCTION(CAgentPanelOcxCtrl, "ActionUpdateSettings", ActionUpdateSettings, VT_EMPTY, VTS_NONE)
DISP_FUNCTION(CAgentPanelOcxCtrl, "GetIsOutDialOpenURL", GetIsOutDialOpenURL, VT_BOOL, VTS_NONE)
DISP_FUNCTION(CAgentPanelOcxCtrl, "GetIVRReturn", GetIVRReturn, VT_I2, VTS_NONE)
DISP_FUNCTION(CAgentPanelOcxCtrl, "SetProductVersion", SetProductVersion, VT_EMPTY, VTS_I2 VTS_BSTR)
DISP_FUNCTION(CAgentPanelOcxCtrl, "GetRecInvokePath", GetRecInvokePath, VT_BSTR, VTS_NONE)
DISP_FUNCTION(CAgentPanelOcxCtrl, "GetAgentID", GetAgentID, VT_BSTR, VTS_NONE)
DISP_FUNCTION(CAgentPanelOcxCtrl, "SetOriginalData", SetOriginalData, VT_EMPTY, VTS_BSTR)
DISP_FUNCTION(CAgentPanelOcxCtrl, "ActionOutDial", ActionOutDial, VT_EMPTY, VTS_BSTR)
DISP_FUNCTION(CAgentPanelOcxCtrl, "SetSelectGroup", SetSelectGroup, VT_EMPTY, VTS_BSTR)
DISP_FUNCTION(CAgentPanelOcxCtrl, "ActionAutoTransferEx", ActionAutoTransferEx, VT_EMPTY, VTS_BSTR)
DISP_FUNCTION(CAgentPanelOcxCtrl, "ActionOutDialWithRecSetting", ActionOutDialWithRecSetting, VT_EMPTY, VTS_BSTR VTS_BSTR)
DISP_FUNCTION(CAgentPanelOcxCtrl, "ActionOffHookWithRecSetting", ActionOffHookWithRecSetting, VT_EMPTY, VTS_BSTR)
DISP_FUNCTION(CAgentPanelOcxCtrl, "GetIsCallInOpenURL", GetIsCallInOpenURL, VT_BOOL, VTS_NONE)
DISP_FUNCTION(CAgentPanelOcxCtrl, "GetParkReasons", GetParkReasons, VT_BSTR, VTS_NONE)
DISP_FUNCTION(CAgentPanelOcxCtrl, "SetParkReason", SetParkReason, VT_EMPTY, VTS_I2)
DISP_FUNCTION(CAgentPanelOcxCtrl, "SetCallerSendingInDialing", SetCallerSendingInDialing, VT_EMPTY, VTS_BSTR)
DISP_FUNCTION(CAgentPanelOcxCtrl, "ActionJoinOutDialMode", ActionJoinOutDialMode, VT_EMPTY, VTS_BOOL)
DISP_FUNCTION(CAgentPanelOcxCtrl, "GetIsOutDialMode", GetIsOutDialMode, VT_BOOL, VTS_NONE)
DISP_FUNCTION(CAgentPanelOcxCtrl, "GetMoudleFilePath", GetMoudleFilePath, VT_BSTR, VTS_NONE)
DISP_FUNCTION(CAgentPanelOcxCtrl, "ActionSetMuteModeEx", ActionSetMuteModeEx, VT_EMPTY, VTS_I4 VTS_I4 VTS_BOOL)
DISP_FUNCTION(CAgentPanelOcxCtrl, "ActionStartConference", ActionStartConference, VT_EMPTY,VTS_NONE)
DISP_FUNCTION(CAgentPanelOcxCtrl, "ActionEndConference",ActionEndConference,VT_EMPTY,VTS_NONE)
DISP_FUNCTION(CAgentPanelOcxCtrl, "GetCanConference", GetCanConference, VT_BOOL, VTS_NONE)
DISP_FUNCTION(CAgentPanelOcxCtrl, "StopPlayAgentID", StopPlayAgentID, VT_EMPTY, VTS_NONE)
DISP_FUNCTION(CAgentPanelOcxCtrl, "ActionACDAutoLogin", ActionACDAutoLogin, VT_EMPTY, VTS_NONE)
DISP_FUNCTION(CAgentPanelOcxCtrl, "SetLogonMode", SetLogonMode, VT_EMPTY, VTS_I2)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CAgentPanelOcxCtrl, COleControl)
//{{AFX_EVENT_MAP(CAgentPanelOcxCtrl)
EVENT_CUSTOM("OnLogin", FireOnLogin, VTS_BOOL VTS_I2)
EVENT_CUSTOM("OnAgentLoginSucc", FireOnAgentLoginSucc, VTS_BOOL  VTS_BSTR  VTS_I2)
EVENT_CUSTOM("OnAgentLogoutConf", FireOnAgentLogoutConf, VTS_I2)
EVENT_CUSTOM("OnAgentMakeCallConf", FireOnAgentMakeCallConf, VTS_I2)
EVENT_CUSTOM("OnClientStateChange", FireOnClientStateChange, VTS_I2)
EVENT_CUSTOM("OnCallDelivered", FireOnCallDelivered, VTS_BSTR  VTS_BSTR  VTS_BSTR  VTS_BSTR)
EVENT_CUSTOM("OnSystemStatusInfo", FireOnSystemStatusInfo, VTS_BSTR)
EVENT_CUSTOM("OnChatMsgDelivered", FireOnChatMsgDelivered, VTS_BSTR  VTS_BSTR  VTS_BOOL)
EVENT_CUSTOM("OnQueueSize", FireOnQueueSize, VTS_I4)
EVENT_CUSTOM("OnGetGroupInfo", FireOnGetGroupInfo, VTS_BSTR)
EVENT_CUSTOM("OnGetOneGroupFreeAgentInfo", FireOnGetOneGroupFreeAgentInfo, VTS_BSTR)
EVENT_CUSTOM("OnGetFullFreeAgentInfo", FireOnGetFullFreeAgentInfo, VTS_BSTR)
EVENT_CUSTOM("OnGetFullTalkingAgentInfo", FireOnGetFullTalkingAgentInfo, VTS_BSTR)
EVENT_CUSTOM("OnAudioLostRate", FireOnAudioLostRate, VTS_BSTR)
EVENT_CUSTOM("OnAgentLoginFailed", FireOnAgentLoginFailed, VTS_BSTR)
EVENT_CUSTOM("OnServiceStateChange", FireOnServiceStateChange, VTS_I2)
EVENT_CUSTOM("OnPreOutDialEnd", FireOnPreOutDialEnd, VTS_BSTR)
EVENT_CUSTOM("OnUserLoginInfo", FireOnUserLoginInfo, VTS_I2  VTS_BSTR)
EVENT_CUSTOM("OnAgentOutdialConf", FireOnAgentOutdialConf, VTS_BSTR)
EVENT_CUSTOM("OnACDSendStrMsg", FireOnACDSendStrMsg, VTS_BSTR  VTS_BSTR)
EVENT_CUSTOM("OnLoginSendStrMsg", FireOnLoginSendStrMsg, VTS_I4  VTS_BSTR  VTS_BSTR)
EVENT_CUSTOM("OnIVRReturnToAgentConf", FireOnIVRReturnToAgentConf, VTS_BSTR)
EVENT_CUSTOM("OnNotifyAgentLoginConf", FireOnNotifyAgentLoginConf, VTS_BSTR)
EVENT_CUSTOM("OnAddTalkToWebChat", FireOnAddTalkToWebChat, VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR)
//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CAgentPanelOcxCtrl, 1)
PROPPAGEID(CAgentPanelOcxPropPage::guid)
END_PROPPAGEIDS(CAgentPanelOcxCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid
IMPLEMENT_OLECREATE_EX(CAgentPanelOcxCtrl, "AGENTPANELOCX.AgentPanelOcxCtrl.1",
					   0xea5bbe, 0xd690, 0x489f, 0x98, 0xc5, 0xcf, 0xee, 0xce, 0x85, 0xd9, 0x30)
					   
					   
					   /////////////////////////////////////////////////////////////////////////////
					   // Type library ID and version
					   
					   IMPLEMENT_OLETYPELIB(CAgentPanelOcxCtrl, _tlid, _wVerMajor, _wVerMinor)
					   
					   
					   /////////////////////////////////////////////////////////////////////////////
					   // Interface IDs
					   
					   const IID BASED_CODE IID_DAgentPanelOcx = { 0x5d1c8f4d, 0x6440, 0x4496, { 0xbe, 0xfb, 0xa7, 0xb8, 0xae, 0x55, 0x4, 0x44 } };

const IID BASED_CODE IID_DAgentPanelOcxEvents = { 0xa3378169, 0xb79c, 0x41ee, { 0xbc, 0x73, 0xda, 0x3a, 0x5d, 0x88, 0xad, 0xdf } };



/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwAgentPanelOcxOleMisc =
OLEMISC_ACTIVATEWHENVISIBLE |
OLEMISC_SETCLIENTSITEFIRST |
OLEMISC_INSIDEOUT |
OLEMISC_CANTLINKINSIDE |
OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CAgentPanelOcxCtrl, IDS_AGENTPANELOCX, _dwAgentPanelOcxOleMisc)

/////////////////////////////////////////////////////////////////////////////
// CAgentPanelOcxCtrl::CAgentPanelOcxCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CAgentPanelOcxCtrl

BOOL CAgentPanelOcxCtrl::CAgentPanelOcxCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegApartmentThreading to 0.
	
	if (bRegister)
		return AfxOleRegisterControlClass(
		AfxGetInstanceHandle(),
		m_clsid,
		m_lpszProgID,
		IDS_AGENTPANELOCX,
		IDB_AGENTPANELOCX,
		afxRegApartmentThreading,
		_dwAgentPanelOcxOleMisc,
		_tlid,
		_wVerMajor,
		_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// CAgentPanelOcxCtrl::CAgentPanelOcxCtrl - Constructor

CAgentPanelOcxCtrl::CAgentPanelOcxCtrl()
{
	InitializeIIDs(&IID_DAgentPanelOcx, &IID_DAgentPanelOcxEvents);
	
	// TODO: Initialize your control's instance data here.
	m_bRestartSrv = FALSE;
	m_bMonit = FALSE;
	m_bTalkingAgentDlgShow = FALSE;	
	m_bFreeAgentDlgShow = FALSE;
	m_pCallTargerListDlg = NULL;
	m_pMonitTargerListDlg = NULL;
	m_pSettingsDlg = NULL;
	m_sSPNumber = "";
	m_sShortName = "";
	
	m_bLogonSucc = FALSE;
	m_bInit = false;
	m_bInitMsgRecv = false;
	m_bDestroyWindow = false;

	g_bPackIntegrity = ChechPackIntegrity();		
}


/////////////////////////////////////////////////////////////////////////////
// CAgentPanelOcxCtrl::~CAgentPanelOcxCtrl - Destructor

CAgentPanelOcxCtrl::~CAgentPanelOcxCtrl()
{
	this->Exit();

	if (!m_bDestroyWindow)
		this->DestroyWindow();
}


/////////////////////////////////////////////////////////////////////////////
// CAgentPanelOcxCtrl::OnDraw - Drawing function

void CAgentPanelOcxCtrl::OnDraw(
								CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	// TODO: Replace the following code with your own drawing code.
	pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	pdc->Ellipse(rcBounds);
}


/////////////////////////////////////////////////////////////////////////////
// CAgentPanelOcxCtrl::DoPropExchange - Persistence support

void CAgentPanelOcxCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);
	
	// TODO: Call PX_ functions for each persistent custom property.
}


/////////////////////////////////////////////////////////////////////////////
// CAgentPanelOcxCtrl::OnResetState - Reset control to default state

void CAgentPanelOcxCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange
	
	// TODO: Reset any other control state here.
}

/////////////////////////////////////////////////////////////////////////////
// CAgentPanelOcxCtrl message handlers
void CAgentPanelOcxCtrl::OnDestroy() 
{
	COleControl::OnDestroy();
}

static BOOL bIsDisconnnect = FALSE;

void CAgentPanelOcxCtrl::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	switch (nIDEvent)
	{
	case 1:
		{
			KillTimer(1);
			if (m_sAccount != "" && m_sPassword != ""){
				FireOnChatMsgDelivered("system", "<LC>STRING_CLIENT_LOGIN_AGAIN</LC>", 0); 
				ActionLogon2(m_sCorp, m_sAccount, m_sPassword, m_iLoginServerOpt, m_sLoginServer);
			}
		}
		break;
	case 2:
		{
			if (QueryProcessExsit("IPCCService.exe"))
			{	
				KillTimer(2);
				if (m_sAccount != "" && m_sPassword != ""){
					FireOnServiceStateChange(1);
					FireOnChatMsgDelivered("system", "<LC>STRING_CLIENT_LOGIN_AGAIN</LC>", 0);
					ActionLogon2(m_sCorp, m_sAccount, m_sPassword, m_iLoginServerOpt, m_sLoginServer);
				}
			}
		}
		break;
	default:
		{}
	}
	
	COleControl::OnTimer(nIDEvent);
}

int CAgentPanelOcxCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (COleControl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!g_bPackIntegrity)
	{
		CLog::DirectWriteFile((string)g_strLogFilePath, "Infobird_ocx.log", "CAgentPanelOcxCtrl::OnCreate 客户端构件不全，直接停止运行。");
		return 0;
	}
	
	if (g_bMakelog)
		CLog::DirectWriteFile((string)g_strLogFilePath, "Infobird_ocx.log", "CAgentPanelOcxCtrl::OnCreate");

	CEnvironment &env = CEnvironment::Instance();
	CString strIni = GetDataFilesPath() + "\\Config.ini";
	if (env.LoadEnvironmentFromFile(strIni))
		env.SaveEnvironmentToFile(strIni);

	g_pMainFrame = this;
	return 0;
}

LRESULT CAgentPanelOcxCtrl::OnSockMsg(WPARAM wParam, LPARAM lParam)
{
	char* pData = (char*)wParam;
	int nLen = (int)lParam;
	if(pData == NULL)
		return 0;
	HandleRecvMsg(pData, nLen);
	delete[] pData;
	return 0;
}

void CAgentPanelOcxCtrl::HandleRecvMsg(char* data, int nlen)
{
	if(nlen < 8)
		return;
	int nMsgClass = *(int*)data;
	switch(nMsgClass)
	{
	case Class_FuncReturn:
		HandleFuncReturn(data, nlen);
		break;
	case Class_FuncEvent:
		HandleFuncEvent(data, nlen);
		break;
	case Class_OCXHeart:
		HandleIPCCHeartBeat(data, nlen);
		break;
	case Class_OCXService:
		HandleOCXService(data, nlen);	
		break;
	default:
		break;
	}
}
// 处理心跳信息
void CAgentPanelOcxCtrl::HandleIPCCHeartBeat(char* data, int nlen)
{

	//收到了来自ipccservice的心跳
	m_bInitMsgRecv = true;
	m_tLastRecvTime = GetTickCount();
	CString strData;
	CTime tm = CTime::GetCurrentTime();
	strData.Format("收到心跳:%d分%d秒 \n", tm.GetMinute(), tm.GetSecond());
	AfxTrace("%s", strData);
	SendHeartResp();

}	
void CAgentPanelOcxCtrl::SendHeartResp()
{
	//CLog::DirectWriteFile((string)g_strLogFilePath, "Infobird_ocx.log", "收到心跳");
	SIPCCMsg_OCXHeartResp resp;
	char *pc;
	int nlen = resp.FillBuf(pc);
	m_AgentSock.SendUDPData(pc, nlen);
}

// 处理函数返回
void CAgentPanelOcxCtrl:: HandleFuncReturn(char* data, int nlen)
{
	int nMsgType = *(int*)(data + 4);
	switch(nMsgType)
	{
	case dispidGetLoginManner:
		HandlereturnGetLoginManner(data, nlen);
		break;
	case dispidGetDeptment:
		HandlereturnGetDeptment(data, nlen);
		break;
	case dispidGetCorp:
		HandlereturnGetCorp(data, nlen);
		break;
	case dispidGetCallType:
		HandlereturnGetCallType(data, nlen);
		break;
	case dispidGetCallFrom:
		HandlereturnGetCallFrom(data, nlen);
		break;
	case dispidGetPrivateData:
		HandlereturnGetPrivateData(data, nlen);
		break;
	case dispidGetRecInvokeID:
		HandlereturnGetRecInvokeID(data, nlen);
		break;
	case dispidGetClientState:
		HandlereturnGetClientState(data, nlen);
		break;
	case dispidGetLogonType:
		HandlereturnGetLogonType(data, nlen);
		break;
	case dispidGetCallPartyType:
		HandlereturnGetCallPartyType(data, nlen);
		break;
	case dispidGetAgentHasLogon:
		HandlereturnGetAgentHasLogon(data, nlen);
		break;
	case dispidGetRoleInCompany:
		HandlereturnGetRoleInCompany(data, nlen);
		break;
	case dispidGetAgentAccount: 
		HandlereturnGetAgentAccount(data, nlen);
		break; 
	case dispidGetIsCCNUser: 
		HandlereturnGetIsCCNUser(data, nlen);
		break;
	case dispidGetAgentType: 
		HandlereturnGetAgentType(data, nlen);
		break; 
	case dispidGetIsSMSEnabled: 
		HandlereturnGetIsHasSMS(data, nlen);
		break; 
	case dispidGetAgentExtNum: 
		HandlereturnGetAgentExtNum(data, nlen);
		break;
	case dispidGetAgentPhoneNo: 
		HandlereturnGetAgentPhoneNo(data, nlen);
		break; 
	case dispidGetManagerID:
		HandlereturnGetManagerID(data, nlen);
		break;
	case dispidGetIsSuperAgent:
		HandlereturnGetIsSuperAgent(data, nlen);
		break;
	case dispidGetIsMasterSuperAgent:
		HandlereturnGetIsMasterSuperAgent(data, nlen);
		break;
	case dispidGetRemindTime:
		HandlereturnGetRemindTime(data, nlen);
		break;
	case dispidGetIsMonit:
		HandlereturnGetIsMonit(data, nlen);
		break;
	case dispidGetSMSParamsInfo:
		HandlereturnGetSMSParamsInfo(data, nlen);
		break;
	case dispidGetBriefStatisticInfo:
		HandlereturnGetBriefStatisticInfo(data, nlen);
		break;
	case dispidGetIsCallFromACD: 
		HandlereturnGetIsCallFromACD(data, nlen);
		break; 
	case dispidGetIsOutDialOpenURL:
		HandlereturnGetIsOutdailOpenUrl(data, nlen);
		break;
	case dispidGetIsCallInOpenURL:
		HandlereturnGetIsCallInOpenUrl(data, nlen);
		break;
	case dispidGetIVRReturn:
		HandlereturnGetIVRReturn(data, nlen);
		break;
	case dispidGetRecInvokePath:
		HandlereturnGetRecInvokePath(data, nlen);
		break;
	case dispidGetAgentID:
		HandlereturnGetAgentID(data, nlen);
		break;
	case dispidGetParkReasons:
		HandlereturnGetParkReasons(data, nlen);
		break;
	case dispidGetIsOutDialMode:
		HandlereturnGetIsOutDialMode(data, nlen);
		break;
	case dispidGetCanConference:
		HandlereturnGetCanConference(data,nlen);
		break;
	default:
		break;
	}
}
void CAgentPanelOcxCtrl::HandlereturnGetLoginManner(char* data, int nlen)
{	
	short bReturn = 0;
	SIPCCMsg_OCXFuncHead head;
	int len1 = head.ReadOurBuf(data, nlen);
	memcpy(&bReturn, data+len1, sizeof(bReturn));
	len1 += sizeof(bReturn);
	// 处理返回值
	CFuncReturnObject* pObj = NULL;
	m_LockMapFunc.Lock();
	m_mapFuncRtn.Lookup(head.invokeId.c_str(), (void* &)pObj);
	if(pObj != NULL)
	{
		pObj->m_varReturn = (short)bReturn;
		SetEvent(pObj->m_hWaitEvent);
	}
	m_LockMapFunc.Unlock();
}

void CAgentPanelOcxCtrl:: HandlereturnGetDeptment(char* data, int nlen)
{
	string sReturn;
	SIPCCMsg_OCXFuncHead head;
	int len1 = head.ReadOurBuf(data, nlen);
	len1 += head.GetString(data+len1, sReturn);
	// 处理返回值
	CFuncReturnObject* pObj = NULL;
	m_LockMapFunc.Lock();
	m_mapFuncRtn.Lookup(head.invokeId.c_str(), (void* &)pObj);
	if(pObj != NULL)
	{
		pObj->m_varReturn = (_bstr_t)sReturn.c_str();
		SetEvent(pObj->m_hWaitEvent);
	}
	m_LockMapFunc.Unlock();
}

void CAgentPanelOcxCtrl:: HandlereturnGetCorp(char* data, int nlen)
{
	string sReturn;
	SIPCCMsg_OCXFuncHead head;
	int len1 = head.ReadOurBuf(data, nlen);
	len1 += head.GetString(data+len1, sReturn);
	// 处理返回值
	CFuncReturnObject* pObj = NULL;
	m_LockMapFunc.Lock();
	m_mapFuncRtn.Lookup(head.invokeId.c_str(), (void* &)pObj);
	if(pObj != NULL)
	{
		pObj->m_varReturn = (_bstr_t)sReturn.c_str();
		SetEvent(pObj->m_hWaitEvent);
	}
	m_LockMapFunc.Unlock();
}

void CAgentPanelOcxCtrl:: HandlereturnGetCallType(char* data, int nlen)
{
	short bReturn = 0;
	SIPCCMsg_OCXFuncHead head;
	int len1 = head.ReadOurBuf(data, nlen);
	memcpy(&bReturn, data+len1, sizeof(bReturn));
	len1 += sizeof(bReturn);
	// 处理返回值
	CFuncReturnObject* pObj = NULL;
	m_LockMapFunc.Lock();
	m_mapFuncRtn.Lookup(head.invokeId.c_str(), (void* &)pObj);
	if(pObj != NULL)
	{
		pObj->m_varReturn = (short)bReturn;
		SetEvent(pObj->m_hWaitEvent);
	}
	m_LockMapFunc.Unlock();
}

void CAgentPanelOcxCtrl:: HandlereturnGetCallFrom(char* data, int nlen)
{
	string sReturn;
	SIPCCMsg_OCXFuncHead head;
	int len1 = head.ReadOurBuf(data, nlen);
	len1 += head.GetString(data+len1, sReturn);
	// 处理返回值
	CFuncReturnObject* pObj = NULL;
	m_LockMapFunc.Lock();
	m_mapFuncRtn.Lookup(head.invokeId.c_str(), (void* &)pObj);
	if(pObj != NULL)
	{
		pObj->m_varReturn = (_bstr_t)sReturn.c_str();
		SetEvent(pObj->m_hWaitEvent);
	}
	m_LockMapFunc.Unlock();
}
void CAgentPanelOcxCtrl:: HandlereturnGetPrivateData(char* data, int nlen)
{
	string sReturn;
	SIPCCMsg_OCXFuncHead head;
	int len1 = head.ReadOurBuf(data, nlen);
	len1 += head.GetString(data+len1, sReturn);
	// 处理返回值
	CFuncReturnObject* pObj = NULL;
	m_LockMapFunc.Lock();
	m_mapFuncRtn.Lookup(head.invokeId.c_str(), (void* &)pObj);
	if(pObj != NULL)
	{
		pObj->m_varReturn = (_bstr_t)sReturn.c_str();
		SetEvent(pObj->m_hWaitEvent);
	}
	m_LockMapFunc.Unlock();
}

void CAgentPanelOcxCtrl:: HandlereturnGetRecInvokeID(char* data, int nlen)
{
	string sReturn;
	SIPCCMsg_OCXFuncHead head;
	int len1 = head.ReadOurBuf(data, nlen);
	len1 += head.GetString(data+len1, sReturn);
	// 处理返回值
	CFuncReturnObject* pObj = NULL;
	m_LockMapFunc.Lock();
	m_mapFuncRtn.Lookup(head.invokeId.c_str(), (void* &)pObj);
	if(pObj != NULL)
	{
		pObj->m_varReturn = (_bstr_t)sReturn.c_str();
		SetEvent(pObj->m_hWaitEvent);
	}
	m_LockMapFunc.Unlock();
}

void CAgentPanelOcxCtrl:: HandlereturnGetClientState(char* data, int nlen)
{
	short bReturn = 0;
	SIPCCMsg_OCXFuncHead head;
	int len1 = head.ReadOurBuf(data, nlen);
	memcpy(&bReturn, data+len1, sizeof(bReturn));
	len1 += sizeof(bReturn);
	// 处理返回值
	CFuncReturnObject* pObj = NULL;
	m_LockMapFunc.Lock();
	m_mapFuncRtn.Lookup(head.invokeId.c_str(), (void* &)pObj);
	if(pObj != NULL)
	{
		pObj->m_varReturn = (short)bReturn;
		SetEvent(pObj->m_hWaitEvent);
	}
	m_LockMapFunc.Unlock();
}

void CAgentPanelOcxCtrl::HandlereturnGetLogonType(char* data, int nlen)
{
	short bReturn = 0;
	SIPCCMsg_OCXFuncHead head;
	int len1 = head.ReadOurBuf(data, nlen);
	memcpy(&bReturn, data+len1, sizeof(bReturn));
	len1 += sizeof(bReturn);
	// 处理返回值
	CFuncReturnObject* pObj = NULL;
	m_LockMapFunc.Lock();
	m_mapFuncRtn.Lookup(head.invokeId.c_str(), (void* &)pObj);
	if(pObj != NULL)
	{
		pObj->m_varReturn = (short)bReturn;
		SetEvent(pObj->m_hWaitEvent);
	}
	m_LockMapFunc.Unlock();
}

void CAgentPanelOcxCtrl:: HandlereturnGetCallPartyType(char* data, int nlen)
{
	short bReturn = 0;
	SIPCCMsg_OCXFuncHead head;
	int len1 = head.ReadOurBuf(data, nlen);
	memcpy(&bReturn, data+len1, sizeof(bReturn));
	len1 += sizeof(bReturn);
	// 处理返回值
	CFuncReturnObject* pObj = NULL;
	m_LockMapFunc.Lock();
	m_mapFuncRtn.Lookup(head.invokeId.c_str(), (void* &)pObj);
	if(pObj != NULL)
	{
		pObj->m_varReturn = (short)bReturn;
		SetEvent(pObj->m_hWaitEvent);
	}
	m_LockMapFunc.Unlock();
}

void CAgentPanelOcxCtrl:: HandlereturnGetAgentHasLogon(char* data, int nlen)
{
	BOOL bReturn = FALSE;
	SIPCCMsg_OCXFuncHead head;
	int len1 = head.ReadOurBuf(data, nlen);
	memcpy(&bReturn, data+len1, sizeof(bReturn));
	len1 += sizeof(bReturn);
	// 处理返回值
	CFuncReturnObject* pObj = NULL;
	m_LockMapFunc.Lock();
	m_mapFuncRtn.Lookup(head.invokeId.c_str(), (void* &)pObj);
	if(pObj != NULL)
	{
		pObj->m_varReturn = (bool)bReturn;
		SetEvent(pObj->m_hWaitEvent);
	}
	m_LockMapFunc.Unlock();
}


void  CAgentPanelOcxCtrl::HandlereturnGetIsSuperAgent(char* data, int nlen)
{
	BOOL bReturn = FALSE;
	SIPCCMsg_OCXFuncHead head;
	int len1 = head.ReadOurBuf(data, nlen);
	memcpy(&bReturn, data+len1, sizeof(bReturn));
	len1 += sizeof(bReturn);
	// 处理返回值
	CFuncReturnObject* pObj = NULL;
	m_LockMapFunc.Lock();
	m_mapFuncRtn.Lookup(head.invokeId.c_str(), (void* &)pObj);
	if(pObj != NULL)
	{
		pObj->m_varReturn = (bool)bReturn;
		SetEvent(pObj->m_hWaitEvent);
	}
	m_LockMapFunc.Unlock();
}
void  CAgentPanelOcxCtrl::HandlereturnGetIsMasterSuperAgent(char* data, int nlen)
{
	BOOL bReturn = FALSE;
	SIPCCMsg_OCXFuncHead head;
	int len1 = head.ReadOurBuf(data, nlen);
	memcpy(&bReturn, data+len1, sizeof(bReturn));
	len1 += sizeof(bReturn);
	// 处理返回值
	CFuncReturnObject* pObj = NULL;
	m_LockMapFunc.Lock();
	m_mapFuncRtn.Lookup(head.invokeId.c_str(), (void* &)pObj);
	if(pObj != NULL)
	{
		pObj->m_varReturn = (bool)bReturn;
		SetEvent(pObj->m_hWaitEvent);
	}
	m_LockMapFunc.Unlock();
}
void  CAgentPanelOcxCtrl::HandlereturnGetRemindTime(char* data, int nlen)
{
	string sReturn;
	SIPCCMsg_OCXFuncHead head;
	int len1 = head.ReadOurBuf(data, nlen);
	len1 += head.GetString(data+len1, sReturn);
	// 处理返回值
	CFuncReturnObject* pObj = NULL;
	m_LockMapFunc.Lock();
	m_mapFuncRtn.Lookup(head.invokeId.c_str(), (void* &)pObj);
	if(pObj != NULL)
	{
		pObj->m_varReturn = (_bstr_t)sReturn.c_str();
		SetEvent(pObj->m_hWaitEvent);
	}
	m_LockMapFunc.Unlock();
}
void  CAgentPanelOcxCtrl::HandlereturnGetIsMonit(char* data, int nlen)
{
	BOOL sReturn = FALSE;
	SIPCCMsg_OCXFuncHead head;
	int len1 = head.ReadOurBuf(data, nlen);
	memcpy(&sReturn, data+len1, sizeof(sReturn));
	len1 += sizeof(sReturn);
	
	// 处理返回值
	CFuncReturnObject* pObj = NULL;
	m_LockMapFunc.Lock();
	m_mapFuncRtn.Lookup(head.invokeId.c_str(), (void* &)pObj);
	if(pObj != NULL)
	{
		pObj->m_varReturn = (bool)sReturn;
		SetEvent(pObj->m_hWaitEvent);
	}
	m_LockMapFunc.Unlock();
}

// 处理函数事件
void CAgentPanelOcxCtrl::HandleFuncEvent(char* data, int nlen)
{
	int nMsgType = *(int*)(data + 4);
	
	switch(nMsgType)
	{
	case eventidOnLogin:		
		HandleeventOnLogin(data, nlen);	
		break;
	case eventidOnAgentLoginSucc:
		HandleeventOnAgentLoginSucc(data, nlen);		
		break;
	case eventidOnAgentLoginFailed:
		HandleeventOnAgentLoginFailed(data, nlen);
		break;
	case eventidOnAgentLogoutConf:
		HandleeventOnAgentLogoutConf(data, nlen);
		break;
	case eventidOnAgentMakeCallConf:
		HandleeventOnAgentMakeCallConf(data, nlen);
		break;
	case eventidOnClientStateChange:
		HandleeventOnClientStateChange(data, nlen);
		break;
	case eventidOnCallDelivered:
		HandleeventOnCallDelivered(data, nlen);
		break;
	case eventidOnSystemStatusInfo:
		HandleeventOnSystemStatusInfo(data, nlen);
		break;	
	case eventidOnChatMsgDelivered:
		HandleeventOnChatMsgDelivered(data, nlen);
		break;
	case eventidOnQueueSize:
		HandleeventOnQueueSize(data, nlen);
		break;
	case eventidOnGetGroupInfo:
		HandleeventOnGetGroupInfo(data, nlen);
		break;
	case eventidOnGetOneGroupFreeAgentInfo:
		HandleeventOnGetOneGroupFreeAgentInfo(data, nlen);
		break;
	case eventidOnGetFullFreeAgentInfo:
		HandleeventOnGetFullFreeAgentInfo(data, nlen);
		break;
	case eventidOnGetFullTalkingAgentInfo:
		HandleeventOnGetFullTalkingAgentInfo(data, nlen);
		break;
	case eventidOnAudioLostRate:
		HandleeventOnAudioLostRate(data, nlen);
		break;
	case eventidOnPreOutDialEnd:
		HandleeventOnPreOutDialEnd(data, nlen);
		break;
	case eventidOnUserLoginInfo:
		HandleeventOnUserLoginInfo(data, nlen);
		break;
	case eventidOnAgentOutdialConf:
		HandleeventOnAgentOutdialConf(data, nlen);
		break;
	case eventidOnACDSendStrMsg:
		HandleeventOnACDSendStrMsg(data, nlen);
		break;
	case eventidOnLoginSendStrMsg:
		HandleeventOnLoginSendStrMsg(data, nlen);
		break;
	case eventidOnIVRReturnToAgentConf:
		HandleeventOnIVRReturnToAgentConf(data, nlen);
		break;
	case eventidOnNotifyAgentLoginConf:
		HandleeventOnNotifyAgentLoginConf(data, nlen);
		break;
	case eventidOnAddTalkToWebChat://hqh 2017.6.12 把多渠道消息独立出来
		HandleeventOnAddTalkToWebChat(data, nlen);
		break;
	default:
		break;
	}
}

void CAgentPanelOcxCtrl::HandleeventOnLogin(char* data, int nlen)
{
	BOOL bSucc = FALSE;
	short iState = 0;
	SIPCCMsg_OCXFuncHead head;
	int len1 = head.ReadOurBuf(data, nlen);
	memcpy(&bSucc, data+len1, sizeof(bSucc));
	len1 += sizeof(bSucc);
	
	memcpy(&iState, data+len1, sizeof(iState));
	len1 += sizeof(iState);	
	FireOnLogin(bSucc, iState);
	
	if (bSucc)
	{
		m_bLogonSucc = TRUE;
	}
}

void CAgentPanelOcxCtrl::HandleeventOnAgentLoginSucc(char* data, int nlen)
{
	SIPCCMsg_OCXFuncHead head;
	int len1 = head.ReadOurBuf(data, nlen);
	BOOL bAgentExist = FALSE;
	memcpy(&bAgentExist, data+len1, sizeof(bAgentExist));
	len1 += sizeof(bAgentExist);
	
	string sAgentId;
	len1 += head.GetString(data+len1, sAgentId);
	
	short iClientState;
	memcpy(&iClientState, data+len1, sizeof(iClientState));
	len1 += sizeof(iClientState);
	FireOnAgentLoginSucc(bAgentExist, sAgentId.c_str(), iClientState);
	
	m_sManagerID = GetManagerID();
	g_strAccount = GetAgentAccount();
	g_iSuperAgentType = GetRoleInCompany();
	//为了统一ocx和service中web绑登录失败而转到onlyweb模式
	CEnvironment &env = CEnvironment::Instance();
	env.LoadEnvironmentFromFile(GetDataFilesPath() + "\\Config.ini");
}

void CAgentPanelOcxCtrl::HandleeventOnAgentLoginFailed(char* data, int nlen)
{
	SIPCCMsg_OCXFuncHead head;
	int len1 = head.ReadOurBuf(data, nlen);
	
	string sInfo;
	len1 += head.GetString(data+len1, sInfo);
	
	FireOnAgentLoginFailed(sInfo.c_str());
}

void CAgentPanelOcxCtrl::HandleeventOnAgentLogoutConf(char* data, int nlen)
{ 
	short iClientState = 0;
	SIPCCMsg_OCXFuncHead head;
	int len1 = head.ReadOurBuf(data, nlen);
	memcpy(&iClientState, data+len1, sizeof(iClientState));
	len1 += sizeof(iClientState);
	FireOnAgentLogoutConf(iClientState);
}
void CAgentPanelOcxCtrl::HandleeventOnAgentMakeCallConf(char* data, int nlen)
{
	short iCallingState = 0;
	SIPCCMsg_OCXFuncHead head;
	int len1 = head.ReadOurBuf(data, nlen);
	memcpy(&iCallingState, data+len1, sizeof(iCallingState));
	len1 += sizeof(iCallingState);
	FireOnAgentMakeCallConf(iCallingState);
}
void CAgentPanelOcxCtrl::HandleeventOnClientStateChange(char* data, int nlen)
{
	short iClientState = 0;
	SIPCCMsg_OCXFuncHead head;
	int len1 = head.ReadOurBuf(data, nlen);
	memcpy(&iClientState, data+len1, sizeof(iClientState));
	len1 += sizeof(iClientState);
	FireOnClientStateChange(iClientState);
	// 振铃
	CEnvironment& env = CEnvironment::Instance();
	if(iClientState == Agent_Ringing && env.m_bPCSpeaker)
	{
		m_bStopBeep = FALSE;
		CreateThread(NULL, 0, BeepThread, this, 0, NULL);
	}
	else
	{
		m_bStopBeep = TRUE;
	}
}
void CAgentPanelOcxCtrl::HandleeventOnCallDelivered(char* data, int nlen)
{
	SIPCCMsg_OCXFuncHead head;
	int len1 = head.ReadOurBuf(data, nlen);
	
	string sCallID;
	len1 += head.GetString(data+len1, sCallID);
	string sCaller;
	len1 += head.GetString(data+len1, sCaller);
	string sCallee;
	len1 += head.GetString(data+len1, sCallee);
	string sOriginalData;
	len1 += head.GetString(data+len1, sOriginalData);
	FireOnCallDelivered(sCallID.c_str(), sCaller.c_str(), sCallee.c_str(), sOriginalData.c_str());
}
void CAgentPanelOcxCtrl::HandleeventOnSystemStatusInfo(char* data, int nlen)
{
	SIPCCMsg_OCXFuncHead head;
	int len1 = head.ReadOurBuf(data, nlen);
	
	string sWords;
	len1 += head.GetString(data+len1, sWords);
	FireOnSystemStatusInfo(sWords.c_str());
}
void CAgentPanelOcxCtrl::HandleeventOnChatMsgDelivered(char* data, int nlen)
{
	SIPCCMsg_OCXFuncHead head;
	int len1 = head.ReadOurBuf(data, nlen);
	
	string sTalker;
	len1 += head.GetString(data+len1, sTalker);
	string sChatContent;
	len1 += head.GetString(data+len1, sChatContent);
	
	BOOL bIsCallInfo = FALSE;
	memcpy(&bIsCallInfo, data+len1, sizeof(bIsCallInfo));
	len1 += sizeof(bIsCallInfo);
	FireOnChatMsgDelivered(sTalker.c_str(), sChatContent.c_str(), bIsCallInfo);
}

void CAgentPanelOcxCtrl::HandleeventOnQueueSize(char* data, int nlen)
{
	SIPCCMsg_OCXFuncHead head;
	int len1 = head.ReadOurBuf(data, nlen);
	
	long lQueueSize = 0;
	memcpy(&lQueueSize, data+len1, sizeof(lQueueSize));
	len1 += sizeof(lQueueSize);
	FireOnQueueSize(lQueueSize);
}

void CAgentPanelOcxCtrl::HandleeventOnGetGroupInfo(char* data, int nlen)
{ 
	static CString _strFullFreeAgentInfo = "";
	
	SIPCCMsg_OCXFuncHead head;
	int len1 = head.ReadOurBuf(data, nlen);
	
	string sGroupList;
	len1 += head.GetString(data+len1, sGroupList);
	
	CSpliter sp(sGroupList, "::");
	if (sp[0] == "0")
	{			
		_strFullFreeAgentInfo += sp[3].c_str();
		return;
	}
	else 
		_strFullFreeAgentInfo += sp[3].c_str();
	
	if (g_bMakelog)
		CLog::DirectWriteFile((string)g_strLogFilePath, "Infobird_ocx.log", "OCX 技能组：" + (string)_strFullFreeAgentInfo);
	
	FireOnGetGroupInfo(_strFullFreeAgentInfo);
	
	//如果需要界面支持，就显示此界面
	if (m_bFreeAgentDlgShow)
	{
		ASSERT(m_pCallTargerListDlg);
		if(IsWindow(m_pCallTargerListDlg->GetSafeHwnd()) &&
			!m_pCallTargerListDlg->IsWindowVisible())
			m_pCallTargerListDlg->ShowWindow(SW_SHOW);
		
		while(!IsWindow(m_pCallTargerListDlg->GetSafeHwnd()))
			Sleep(100);
		
		COPYDATASTRUCT FreeAgentListCDS;
		FreeAgentList freeAgentList;	
		freeAgentList.bEnd = true;
		freeAgentList.sFreeAgent = _strFullFreeAgentInfo;
		freeAgentList.sDepartment= "";
		FreeAgentListCDS.cbData = sizeof( freeAgentList );  // size of data
		FreeAgentListCDS.lpData = &freeAgentList;
		FreeAgentListCDS.dwData = FREEAGENTLIST_COPYDATA_MSG;
		
		::SendMessage(m_pCallTargerListDlg->GetSafeHwnd(),WM_COPYDATA,
			(LPARAM)(LPVOID)m_pCallTargerListDlg, (LPARAM)(LPVOID)&FreeAgentListCDS);
		
		m_bFreeAgentDlgShow = FALSE;
	}
	
	_strFullFreeAgentInfo = "";
}

void CAgentPanelOcxCtrl::HandleeventOnGetOneGroupFreeAgentInfo(char* data, int nlen)
{
	static CString _strFullFreeAgentInfo = "";
	
	SIPCCMsg_OCXFuncHead head;
	int len1 = head.ReadOurBuf(data, nlen);
	
	string sAgentList;
	len1 += head.GetString(data+len1, sAgentList);
	
	CSpliter sp(sAgentList, "::");
	if (sp[0] == "0")
	{	
		_strFullFreeAgentInfo += sp[3].c_str();
		return;
	}
	else
		_strFullFreeAgentInfo += sp[3].c_str();
	
	if (g_bMakelog)
		CLog::DirectWriteFile((string)g_strLogFilePath, "Infobird_ocx.log", "OCX 单技能组空闲坐席：" + (string)_strFullFreeAgentInfo);
	
	FireOnGetOneGroupFreeAgentInfo(_strFullFreeAgentInfo);
	
	//如果需要界面支持，就显示此界面
	if (m_bFreeAgentDlgShow)
	{
		ASSERT(m_pCallTargerListDlg);
		if(IsWindow(m_pCallTargerListDlg->GetSafeHwnd()) &&
			!m_pCallTargerListDlg->IsWindowVisible())
			m_pCallTargerListDlg->ShowWindow(SW_SHOW);
		
		while(!IsWindow(m_pCallTargerListDlg->GetSafeHwnd()))
			Sleep(100);
		
		COPYDATASTRUCT FreeAgentListCDS;
		FreeAgentList freeAgentList;	
		freeAgentList.bEnd = true;
		freeAgentList.sFreeAgent = _strFullFreeAgentInfo;
		freeAgentList.sDepartment= "";
		FreeAgentListCDS.cbData = sizeof( freeAgentList );  // size of data
		FreeAgentListCDS.lpData = &freeAgentList;
		FreeAgentListCDS.dwData = FREEAGENTLIST_COPYDATA_MSG;
		
		::SendMessage(m_pCallTargerListDlg->GetSafeHwnd(),WM_COPYDATA,
			(LPARAM)(LPVOID)m_pCallTargerListDlg, (LPARAM)(LPVOID)&FreeAgentListCDS);
		
		m_bFreeAgentDlgShow = FALSE;
	}
	
	_strFullFreeAgentInfo = "";
}

void CAgentPanelOcxCtrl::HandleeventOnGetFullFreeAgentInfo(char* data, int nlen)
{
	static CString _strFullFreeAgentInfo = "";
	
	SIPCCMsg_OCXFuncHead head;
	int len1 = head.ReadOurBuf(data, nlen);
	
	string sAgentList;
	len1 += head.GetString(data+len1, sAgentList);
	CSpliter sp(sAgentList, "::");
	if (sp[0] == "0")
	{
		if (((string)sp[3]).find("Dept_400CallBack", 0) == string::npos)
		{
			if (sp[2] != "")
				sp[3] = (string)sp[2] + "/" + (string)sp[3];
			
			_strFullFreeAgentInfo += "|";
			_strFullFreeAgentInfo += sp[3].c_str();
		}
		return;
	}
	if (g_bMakelog)
		CLog::DirectWriteFile((string)g_strLogFilePath, "Infobird_ocx.log", "OCX 空闲坐席：" + (string)_strFullFreeAgentInfo);
	
	FireOnGetFullFreeAgentInfo(_strFullFreeAgentInfo);
	
	//如果需要界面支持，就显示此界面
	if (m_bFreeAgentDlgShow)
	{
		ASSERT(m_pCallTargerListDlg);
		if(IsWindow(m_pCallTargerListDlg->GetSafeHwnd()) &&
			!m_pCallTargerListDlg->IsWindowVisible())
			m_pCallTargerListDlg->ShowWindow(SW_SHOW);
		
		while(!IsWindow(m_pCallTargerListDlg->GetSafeHwnd()))
			Sleep(100);
		
		COPYDATASTRUCT FreeAgentListCDS;
		FreeAgentList freeAgentList;	
		freeAgentList.bEnd = true;
		freeAgentList.sFreeAgent = _strFullFreeAgentInfo;
		freeAgentList.sDepartment= "";
		FreeAgentListCDS.cbData = sizeof( freeAgentList );  // size of data
		FreeAgentListCDS.lpData = &freeAgentList;
		FreeAgentListCDS.dwData = FREEAGENTLIST_COPYDATA_MSG;
		
		::SendMessage(m_pCallTargerListDlg->GetSafeHwnd(),WM_COPYDATA,
			(LPARAM)(LPVOID)m_pCallTargerListDlg, (LPARAM)(LPVOID)&FreeAgentListCDS);
		
		m_bFreeAgentDlgShow = FALSE;
	}
	
	_strFullFreeAgentInfo = "";
}

void CAgentPanelOcxCtrl::HandleeventOnGetFullTalkingAgentInfo(char* data, int nlen)
{
	static CString _strFullTalkingAgentInfo = "";
	
	SIPCCMsg_OCXFuncHead head;
	int len1 = head.ReadOurBuf(data, nlen);
	
	string sAgentList;
	len1 += head.GetString(data+len1, sAgentList);
	
	CSpliter sp(sAgentList, "::");
	if (sp[0] == "0")
	{	
		_strFullTalkingAgentInfo += sp[1].c_str();
		return;
	}
	else 
		_strFullTalkingAgentInfo += sp[1].c_str();
	
	if (g_bMakelog)
		CLog::DirectWriteFile((string)g_strLogFilePath, "Infobird_ocx.log", "OCX 通话坐席：" + (string)_strFullTalkingAgentInfo);
	FireOnGetFullTalkingAgentInfo(_strFullTalkingAgentInfo);
	
	//如果需要界面支持，就显示此界面
	if (m_bTalkingAgentDlgShow)
	{
		ASSERT(m_pMonitTargerListDlg);
		if(IsWindow(m_pMonitTargerListDlg->GetSafeHwnd()) &&
			!m_pMonitTargerListDlg->IsWindowVisible())
			m_pMonitTargerListDlg->ShowWindow(SW_SHOW);
		
		while(!IsWindow(m_pMonitTargerListDlg->GetSafeHwnd()))
			Sleep(100);
		
		COPYDATASTRUCT cds;
		TalkAgentList theList;	
		theList.sTalkAgent = _strFullTalkingAgentInfo;
		cds.cbData = sizeof( theList );  // size of data
		cds.lpData = &theList;
		cds.dwData = TALKAGENTLIST_COPYDATA_MSG;
		
		::SendMessage(m_pMonitTargerListDlg->GetSafeHwnd(),WM_COPYDATA,
			(LPARAM)(LPVOID)m_pMonitTargerListDlg, (LPARAM)(LPVOID)&cds);
		
		m_bTalkingAgentDlgShow = FALSE;
	}
	_strFullTalkingAgentInfo = "";
}

void CAgentPanelOcxCtrl::HandleeventOnAudioLostRate(char* data, int nlen)
{ 
	SIPCCMsg_OCXFuncHead head;
	int len1 = head.ReadOurBuf(data, nlen);
	
	string sRate;
	len1 += head.GetString(data+len1, sRate);
	FireOnAudioLostRate(sRate.c_str());
}
void CAgentPanelOcxCtrl::HandleeventOnPreOutDialEnd(char* data, int nlen)
{
	SIPCCMsg_OCXFuncHead head;
	int len1 = head.ReadOurBuf(data, nlen);
	
	string strInfo;
	len1 += head.GetString(data+len1, strInfo);
	FireOnPreOutDialEnd(strInfo.c_str());

	//hqh 2017.4.17 ipccservice通知ocx acd心跳超时，由ocx触发重登
	if (strInfo == "3000"){
		CLog::DirectWriteFile((string)g_strLogFilePath, "Infobird_ocx.log", "ipccservcie接收ACD心跳超时，由ocx执行重登");
		ActionReset();
	}
}
void CAgentPanelOcxCtrl::HandleeventOnUserLoginInfo(char* data, int nlen)
{
	SIPCCMsg_OCXFuncHead head;
	int len1 = head.ReadOurBuf(data, nlen);
	
	short iType;
	memcpy(&iType, data+len1, sizeof(iType));
	len1 += sizeof(iType);
	string sReason;
	len1 += head.GetString(data+len1, sReason);	
	FireOnUserLoginInfo(iType, sReason.c_str());
}
BOOL CAgentPanelOcxCtrl::WaitFuncReturn(CFuncReturnObject& obj)
{
	// 消息回复
	DWORD dwResult = WaitForSingleObject(obj.m_hWaitEvent, TIMEOUT_WAITFUNC);
	m_LockMapFunc.Lock();
	m_mapFuncRtn.RemoveKey(obj.m_nSeqenceID);
	m_LockMapFunc.Unlock();
	CloseHandle(obj.m_hWaitEvent);
	obj.m_hWaitEvent = NULL;
	return dwResult == WAIT_OBJECT_0;
}

void CAgentPanelOcxCtrl::AddFuncToWait(CFuncReturnObject& obj)
{
	obj.m_hWaitEvent = CreateEvent(NULL, TRUE, FALSE, "");
	m_LockMapFunc.Lock();
	m_mapFuncRtn.SetAt(obj.m_nSeqenceID, &obj);
	m_LockMapFunc.Unlock();	
}

void CAgentPanelOcxCtrl::ActionLogon(LPCTSTR sAccount, LPCTSTR sPassword, short iLoginServerOpt, LPCTSTR sLoginServerHost) 
{
	// TODO: Add your dispatch handler code here
	m_bLogonSucc = FALSE;
	
	//登录前的服务器ip或者域名的验证和保存
	CEnvironment& env = CEnvironment::Instance();
	CString strIniFile = GetDataFilesPath() + "\\Config.ini";
	env.LoadEnvironmentFromFile(strIniFile);
	
	env.m_structCSTPort.iUseDefineIP = iLoginServerOpt;
	switch(iLoginServerOpt)
	{
	case 1:
		{
			env.m_structCSTPort.szCustomizeIP = sLoginServerHost; //服务器IP
		}
		break;
	case 2:
		{
			env.m_structCSTPort.szCustomizeDomain = sLoginServerHost;  //域名
			
			struct hostent * pHost;
			pHost = gethostbyname( sLoginServerHost );
			if ( pHost == NULL || pHost->h_addrtype != AF_INET )
			{
				env.m_structCSTPort.iUseDefineIP = 0;
				::MessageBox(NULL, "login fail.DNS error", "msg", MB_OK);
				return;
			}
		}
		break;
	default:
		break;
	}
	env.SaveEnvironmentToFile(strIniFile);
	ActionUpdateSettings();
	
	//////////////////////////////////////////////////////////////////////////
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidActionLogon;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	nLen += head.FillString(szBuf+nLen, sAccount);
	nLen += head.FillString(szBuf+nLen, sPassword);
	// 
	memcpy(szBuf+nLen, &iLoginServerOpt, sizeof(iLoginServerOpt));
	nLen +=  sizeof(iLoginServerOpt);
	nLen += head.FillString(szBuf+nLen, sLoginServerHost);
	m_AgentSock.SendUDPData(szBuf, nLen);
	
	m_sAccount = sAccount;
	m_sPassword = sPassword;
	m_sLoginServer = sLoginServerHost;
	m_iLoginServerOpt = iLoginServerOpt;
}

void CAgentPanelOcxCtrl::ActionLogon2(LPCTSTR sCorp, LPCTSTR sAccount, LPCTSTR sPassword, short iLoginServerOpt, LPCTSTR sLoginServerHost) 
{
	// TODO: Add your dispatch handler code here
	if (g_bMakelog)
		CLog::DirectWriteFile((string)g_strLogFilePath, "Infobird_ocx.log", "CAgentPanelOcxCtrl::ActionLogon2");

	m_bLogonSucc = FALSE;
	
	CEnvironment& env = CEnvironment::Instance();
	CString strIniFile = GetDataFilesPath() + "\\Config.ini";
	env.LoadEnvironmentFromFile(strIniFile);
	
	env.m_structCSTPort.iUseDefineIP = iLoginServerOpt;
	switch(iLoginServerOpt)
	{
	case 1:
		{
			env.m_structCSTPort.szCustomizeIP = sLoginServerHost; //服务器IP
		}
		break;
	case 2:
		{
			env.m_structCSTPort.szCustomizeDomain = sLoginServerHost;  //域名
			
			struct hostent * pHost;
			pHost = gethostbyname( sLoginServerHost );
			if ( pHost == NULL || pHost->h_addrtype != AF_INET )
			{
				env.m_structCSTPort.iUseDefineIP = 0;
				::MessageBox(NULL, "login fail.DNS error", "msg", MB_OK);
				return;
			}
		}
		break;
	default:
		break;
	}
	env.SaveEnvironmentToFile(strIniFile);
	ActionUpdateSettings();
	
	//////////////////////////////////////////////////////////////////////////
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidActionLogon2;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	nLen += head.FillString(szBuf+nLen, sCorp);
	nLen += head.FillString(szBuf+nLen, sAccount);
	nLen += head.FillString(szBuf+nLen, sPassword);
	// 
	memcpy(szBuf+nLen, &iLoginServerOpt, sizeof(iLoginServerOpt));
	nLen +=  sizeof(iLoginServerOpt);
	nLen += head.FillString(szBuf+nLen, sLoginServerHost);
	m_AgentSock.SendUDPData(szBuf, nLen);
	
	m_sCorp = sCorp;
	m_sAccount = sAccount;
	m_sPassword = sPassword;
	m_sLoginServer = sLoginServerHost;
	m_iLoginServerOpt = iLoginServerOpt;
}

void CAgentPanelOcxCtrl::ActionReset() 
{
	if (!g_bPackIntegrity)
		return;

	CEnvironment &env = CEnvironment::Instance();
	env.LoadEnvironmentFromFile(GetDataFilesPath() + "\\Config.ini");

	ActionLogout();
	FireOnClientStateChange(0);	
	Sleep(200);

	m_tLastRecvTime = GetCurrentTime();

	SetTimer(2,2000,NULL);
		
	SetProductVersion(g_tagProductVerInfo.nVersionType, g_tagProductVerInfo.strVersionNum);

}

void CAgentPanelOcxCtrl::ActionLogout() 
{
	// TODO: Add your dispatch handler code here
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidActionLogout;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	m_AgentSock.SendUDPData(szBuf, nLen);
}

void CAgentPanelOcxCtrl::ActionLogonAgain() 
{
	// TODO: Add your dispatch handler code here
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidActionLogonAgain;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	m_AgentSock.SendUDPData(szBuf, nLen);
}

void CAgentPanelOcxCtrl::ActionCallDepartment(LPCTSTR sCallTarget) 
{
	// TODO: Add your dispatch handler code here
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidActionCallDepartment;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	nLen += head.FillString(szBuf+nLen, sCallTarget);
	m_AgentSock.SendUDPData(szBuf, nLen);
}

void CAgentPanelOcxCtrl::ActionCallAgent(LPCTSTR sCallTarget) 
{
	// TODO: Add your dispatch handler code here
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidActionCallAgent;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	nLen += head.FillString(szBuf+nLen, sCallTarget);
	m_AgentSock.SendUDPData(szBuf, nLen);
}

void CAgentPanelOcxCtrl::ActionCallOtherAgent(LPCTSTR sCallTarget) 
{
	// TODO: Add your dispatch handler code here
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidActionCallOtherAgent;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	nLen += head.FillString(szBuf+nLen, sCallTarget);
	m_AgentSock.SendUDPData(szBuf, nLen);
}

void CAgentPanelOcxCtrl::ActionCallPstn(LPCTSTR sCallTarget) 
{
	// TODO: Add your dispatch handler code here
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidActionCallPstn;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	nLen += head.FillString(szBuf+nLen, sCallTarget);
	m_AgentSock.SendUDPData(szBuf, nLen);
}

void CAgentPanelOcxCtrl::ActionCallExtNum(LPCTSTR sCallTarget) 
{
	// TODO: Add your dispatch handler code here
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidActionCallExtNum;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	nLen += head.FillString(szBuf+nLen, sCallTarget);
	m_AgentSock.SendUDPData(szBuf, nLen);
}

void CAgentPanelOcxCtrl::ActionOnHook() 
{
	// TODO: Add your dispatch handler code here
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidActionOnHook;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	m_AgentSock.SendUDPData(szBuf, nLen);
}

void CAgentPanelOcxCtrl::ActionOffHook() 
{
	// TODO: Add your dispatch handler code here
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidActionOffHook;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	m_AgentSock.SendUDPData(szBuf, nLen);
}

void CAgentPanelOcxCtrl::ActionPark() 
{
	// TODO: Add your dispatch handler code here
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidActionPark;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	m_AgentSock.SendUDPData(szBuf, nLen);
}

void CAgentPanelOcxCtrl::ActionUnPark() 
{
	// TODO: Add your dispatch handler code here
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidActionUnPark;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	m_AgentSock.SendUDPData(szBuf, nLen);
}

void CAgentPanelOcxCtrl::ActionProcess() 
{
	// TODO: Add your dispatch handler code here
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidActionProcess;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	m_AgentSock.SendUDPData(szBuf, nLen);
}

void CAgentPanelOcxCtrl::ActionUnProcess() 
{
	// TODO: Add your dispatch handler code here
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidActionUnProcess;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	m_AgentSock.SendUDPData(szBuf, nLen);
}

void CAgentPanelOcxCtrl::ActionHold() 
{
	// TODO: Add your dispatch handler code here
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidActionHold;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	m_AgentSock.SendUDPData(szBuf, nLen);
}

void CAgentPanelOcxCtrl::ActionUnHold() 
{
	// TODO: Add your dispatch handler code here
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidActionUnHold;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	m_AgentSock.SendUDPData(szBuf, nLen);
}

void CAgentPanelOcxCtrl::ActionTransfer() 
{
	// TODO: Add your dispatch handler code here
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidActionTransfer;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	m_AgentSock.SendUDPData(szBuf, nLen);
}

void CAgentPanelOcxCtrl::ActionAutoTransfer() 
{
	// TODO: Add your dispatch handler code here
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidActionAutoTransfer;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	m_AgentSock.SendUDPData(szBuf, nLen);
}

void CAgentPanelOcxCtrl::ActionTransferToIVR(LPCTSTR sPrivateData, BOOL bUseDefaultTypes, LPCTSTR sLanguageType, LPCTSTR sOperationType, short iWorkingMode) 
{
	// TODO: Add your dispatch handler code here
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidActionTransferToIVR;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	
	nLen += head.FillString(szBuf+nLen, sPrivateData);
	
	memcpy(szBuf+nLen, &bUseDefaultTypes, sizeof(bUseDefaultTypes));
	nLen +=  sizeof(bUseDefaultTypes);
	
	nLen += head.FillString(szBuf+nLen, sLanguageType);
	nLen += head.FillString(szBuf+nLen, sOperationType);
	
	memcpy(szBuf+nLen, &iWorkingMode, sizeof(iWorkingMode));	
	nLen +=  sizeof(iWorkingMode);	
	
	m_AgentSock.SendUDPData(szBuf, nLen);
}

void CAgentPanelOcxCtrl::ActionStartMonit(LPCTSTR sAgentID, LPCTSTR sIP, LPCTSTR sPort) 
{
	// TODO: Add your dispatch handler code here
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidActionStartMonit;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	nLen += head.FillString(szBuf+nLen, sAgentID);
	nLen += head.FillString(szBuf+nLen, sIP);
	nLen += head.FillString(szBuf+nLen, sPort);
	m_AgentSock.SendUDPData(szBuf, nLen);
	m_bMonit = TRUE;
}

void CAgentPanelOcxCtrl::ActionStopMonit() 
{
	// TODO: Add your dispatch handler code here
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidActionStopMonit;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	m_AgentSock.SendUDPData(szBuf, nLen);
	
	m_bMonit = FALSE;
}

void CAgentPanelOcxCtrl::ActionForceDisconnect(LPCTSTR sAgentID) 
{
	// TODO: Add your dispatch handler code here
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidActionForceDisconnect;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	nLen += head.FillString(szBuf+nLen, sAgentID);
	m_AgentSock.SendUDPData(szBuf, nLen);
}

void CAgentPanelOcxCtrl::ActionGetFullFreeAgentInfo() 
{
	// TODO: Add your dispatch handler code here
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidActionGetFullFreeAgentInfo;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	m_AgentSock.SendUDPData(szBuf, nLen);
}

void CAgentPanelOcxCtrl::ActionGetGroupInfo() 
{
	// TODO: Add your dispatch handler code here
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidActionGetGroupInfo;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	m_AgentSock.SendUDPData(szBuf, nLen);
}

void CAgentPanelOcxCtrl::ActionGetOneGroupFreeAgentInfo(LPCTSTR sGroupName) 
{
	// TODO: Add your dispatch handler code here
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidActionGetOneGroupFreeAgentInfo;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	nLen += head.FillString(szBuf+nLen, sGroupName);
	m_AgentSock.SendUDPData(szBuf, nLen);
}

void CAgentPanelOcxCtrl::ActionGetTalkingAgent() 
{
	// TODO: Add your dispatch handler code here
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidActionGetTalkingAgent;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	m_AgentSock.SendUDPData(szBuf, nLen);
}

void CAgentPanelOcxCtrl::ActionSendDTMF(short iDTMFCode) 
{
	// TODO: Add your dispatch handler code here
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidActionSendDTMF;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	
	memcpy(szBuf+nLen, &iDTMFCode, sizeof(iDTMFCode));
	nLen +=  sizeof(iDTMFCode);
	m_AgentSock.SendUDPData(szBuf, nLen);
}

void CAgentPanelOcxCtrl::ActionChangePassword(LPCTSTR sAccount, LPCTSTR sOldPassword, LPCTSTR sNewPassword) 
{
	// TODO: Add your dispatch handler code here
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidActionChangePassword;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	nLen += head.FillString(szBuf+nLen, sAccount);
	nLen += head.FillString(szBuf+nLen, sOldPassword);
	nLen += head.FillString(szBuf+nLen, sNewPassword);
	
	m_AgentSock.SendUDPData(szBuf, nLen);
}

void CAgentPanelOcxCtrl::ActionChangeEarphoneVolume(short iNewVolume) 
{
	// TODO: Add your dispatch handler code here
	
}

void CAgentPanelOcxCtrl::ActionChangeMicVolume(short iNewVolume) 
{
	// TODO: Add your dispatch handler code here
	
}

void CAgentPanelOcxCtrl::ActionSendSMS(LPCTSTR sTargetNum, LPCTSTR sSMSContent) 
{
	// TODO: Add your dispatch handler code here
	CSmsSendModule::Instance()->SendSMS(sTargetNum, sSMSContent, m_sManagerID, m_sAccount,
		m_sPassword, ""/*m_sSPNumber*/, ""/*m_sShortName*/,	this->m_hWnd);
}

void CAgentPanelOcxCtrl::ActionSendChat(LPCTSTR sChatContent) 
{
	// TODO: Add your dispatch handler code here
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidActionSendChat;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	
	nLen += head.FillString(szBuf+nLen, sChatContent);
	m_AgentSock.SendUDPData(szBuf, nLen);
}

void CAgentPanelOcxCtrl::ConfigPortSettings(BOOL bCustomizePort, long lAgentPort, long lAudioPort1, long lAudioPort2, BOOL bRequireTCPTransfer, BOOL bIsLanUser) 
{
	// TODO: Add your dispatch handler code here
	CEnvironment& env = CEnvironment::Instance();
	if (bCustomizePort)
	{
		if (lAgentPort == 0)
		{
			::MessageBox(NULL, "main port can not be 0! please set again.", "error", MB_OK);
			return;
		}
		env.m_structCSTPort.nMainPort = lAgentPort;
		env.m_structCSTPort.nAssistantPort1 = lAudioPort1;
		env.m_structCSTPort.nAssistantPort2 = lAudioPort2;
		env.m_bUseTCPTransfer = bRequireTCPTransfer;
		env.m_bIsLanAgent = bIsLanUser;
	}
	env.SaveEnvironmentToFile(GetDataFilesPath() + "\\Config.ini");
	ActionUpdateSettings();
}

void CAgentPanelOcxCtrl::ConfigRecSettings(BOOL bLocalRecord)
{
	// TODO: Add your dispatch handler code here
	CEnvironment& env = CEnvironment::Instance();
	if (bLocalRecord)
		env.m_structRecorderSet.nRecorderMode = needRecorderAndSaveLocal;
	else
		env.m_structRecorderSet.nRecorderMode = noRecorder;
	env.SaveEnvironmentToFile(GetDataFilesPath() + "\\Config.ini");	
	ActionUpdateSettings();
}

void CAgentPanelOcxCtrl::ConfigOutDialSettings(BOOL bAutoOffhook, BOOL bOutDialMobileAddZero, LPCTSTR sAreaNum, LPCTSTR sOneKeyNum) 
{
	// TODO: Add your dispatch handler code here
	CEnvironment& env = CEnvironment::Instance();
	env.m_bOutDialMobileAddZero = bOutDialMobileAddZero;
	CString strAreaNum = sAreaNum;
	if (!strAreaNum.IsEmpty())
	{
		env.m_bUseAutoAreaNum = TRUE;
		env.m_sAreaNum = string(strAreaNum);
	}
	CString strOneKeyNum = sOneKeyNum;
	if (!strOneKeyNum.IsEmpty())
	{
		env.m_bOneKeyToPhone = TRUE;
		env.m_sOutPhoneNum = string(strOneKeyNum);
	}
	env.SaveEnvironmentToFile(GetDataFilesPath() + "\\Config.ini");
	ActionUpdateSettings();
}

short CAgentPanelOcxCtrl::GetLoginManner() 
{
	// TODO: Add your dispatch handler code here
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidGetLoginManner;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	// 发送并等待返回
	
	CFuncReturnObject obj;
	obj.m_nFuncdispID = head.msgType;
	obj.m_nSeqenceID = head.invokeId.c_str();
	
	AddFuncToWait(obj);
	m_AgentSock.SendUDPData(szBuf, nLen);
	if(WaitFuncReturn(obj) == TRUE)
	{
		return short(obj.m_varReturn);
	}
	return 0;
}

BSTR CAgentPanelOcxCtrl::GetDeptment() 
{
	CString strResult;
	// TODO: Add your dispatch handler code here
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidGetDeptment;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	
	CFuncReturnObject obj;
	obj.m_nFuncdispID = head.msgType;
	obj.m_nSeqenceID = head.invokeId.c_str();
	
	AddFuncToWait(obj);
	m_AgentSock.SendUDPData(szBuf, nLen);
	if(WaitFuncReturn(obj) == TRUE)
	{
		return ::SysAllocString((_bstr_t)obj.m_varReturn);
	}
	return strResult.AllocSysString();
}

BSTR CAgentPanelOcxCtrl::GetCorp() 
{
	CString strResult;
	// TODO: Add your dispatch handler code here
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidGetCorp;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	
	CFuncReturnObject obj;
	obj.m_nFuncdispID = head.msgType;
	obj.m_nSeqenceID = head.invokeId.c_str();
	
	AddFuncToWait(obj);
	m_AgentSock.SendUDPData(szBuf, nLen);
	if(WaitFuncReturn(obj) == TRUE)
	{
		return ::SysAllocString((_bstr_t)obj.m_varReturn);
	}
	return strResult.AllocSysString();
}

short CAgentPanelOcxCtrl::GetCallType() 
{
	// TODO: Add your dispatch handler code here
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidGetCallType;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	
	CFuncReturnObject obj;
	obj.m_nFuncdispID = head.msgType;
	obj.m_nSeqenceID = head.invokeId.c_str();
	
	AddFuncToWait(obj);
	m_AgentSock.SendUDPData(szBuf, nLen);
	if(WaitFuncReturn(obj) == TRUE)
	{
		return short(obj.m_varReturn);
	}
	return 0;
}

BSTR CAgentPanelOcxCtrl::GetCallFrom() 
{
	CString strResult;
	// TODO: Add your dispatch handler code here
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidGetCallFrom;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	
	CFuncReturnObject obj;
	obj.m_nFuncdispID = head.msgType;
	obj.m_nSeqenceID = head.invokeId.c_str();
	
	AddFuncToWait(obj);
	m_AgentSock.SendUDPData(szBuf, nLen);
	if(WaitFuncReturn(obj) == TRUE)
	{
		return ::SysAllocString((_bstr_t)obj.m_varReturn);
	}
	return strResult.AllocSysString();
}

BSTR CAgentPanelOcxCtrl::GetPrivateData() 
{
	CString strResult;
	// TODO: Add your dispatch handler code here
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidGetPrivateData;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	
	CFuncReturnObject obj;
	obj.m_nFuncdispID = head.msgType;
	obj.m_nSeqenceID = head.invokeId.c_str();
	
	AddFuncToWait(obj);
	m_AgentSock.SendUDPData(szBuf, nLen);
	if(WaitFuncReturn(obj) == TRUE)
	{
		return ::SysAllocString((_bstr_t)obj.m_varReturn);
	}
	return strResult.AllocSysString();
}

BSTR CAgentPanelOcxCtrl::GetRecInvokeID() 
{
	CString strResult;
	// TODO: Add your dispatch handler code here
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidGetRecInvokeID;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	
	CFuncReturnObject obj;
	obj.m_nFuncdispID = head.msgType;
	obj.m_nSeqenceID = head.invokeId.c_str();
	
	AddFuncToWait(obj);
	m_AgentSock.SendUDPData(szBuf, nLen);
	if(WaitFuncReturn(obj) == TRUE)
	{
		return ::SysAllocString((_bstr_t)obj.m_varReturn);
	}
	return strResult.AllocSysString();
}

short CAgentPanelOcxCtrl::GetClientState() 
{
	// TODO: Add your dispatch handler code here
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidGetClientState;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	
	CFuncReturnObject obj;
	obj.m_nFuncdispID = head.msgType;
	obj.m_nSeqenceID = head.invokeId.c_str();
	
	AddFuncToWait(obj);
	m_AgentSock.SendUDPData(szBuf, nLen);
	if(WaitFuncReturn(obj) == TRUE)
	{
		return short(obj.m_varReturn);
	}
	return 0;
}

short CAgentPanelOcxCtrl::GetLogonType() 
{
	// TODO: Add your dispatch handler code here
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidGetLogonType;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	
	CFuncReturnObject obj;
	obj.m_nFuncdispID = head.msgType;
	obj.m_nSeqenceID = head.invokeId.c_str();
	
	AddFuncToWait(obj);
	m_AgentSock.SendUDPData(szBuf, nLen);
	if(WaitFuncReturn(obj) == TRUE)
	{
		return short(obj.m_varReturn);
	}
	return 0;
}

short CAgentPanelOcxCtrl::GetCallPartyType() 
{
	// TODO: Add your dispatch handler code here
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidGetCallPartyType;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	
	CFuncReturnObject obj;
	obj.m_nFuncdispID = head.msgType;
	obj.m_nSeqenceID = head.invokeId.c_str();
	
	AddFuncToWait(obj);
	m_AgentSock.SendUDPData(szBuf, nLen);
	if(WaitFuncReturn(obj) == TRUE)
	{
		return short(obj.m_varReturn);
	}
	return 0;
}

BOOL CAgentPanelOcxCtrl::GetAgentHasLogon() 
{
	// TODO: Add your dispatch handler code here
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidGetAgentHasLogon;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	
	CFuncReturnObject obj;
	obj.m_nFuncdispID = head.msgType;
	obj.m_nSeqenceID = head.invokeId.c_str();
	
	AddFuncToWait(obj);
	m_AgentSock.SendUDPData(szBuf, nLen);
	if(WaitFuncReturn(obj) == TRUE)
	{
		return bool(obj.m_varReturn);
	}
	return FALSE;
}
int func_GetRadomPort()
{
	int iRet = 0;
	while ( 1 )
	{
		iRet = GetRandomPort();
		if (abs((int)(iRet - CEnvironment::Instance().m_uAgentOcxPort)) > 32)
		{
			break;
		}
	}
	return iRet;
}
BOOL CAgentPanelOcxCtrl::Initialize(short iVersionType, LPCTSTR sVersionNum)
{
	//hqh 2017.4.6 已经初始化过，就不需要重复去初始化了
	if (m_bInit == true){
		return true;
	}
	

	string sErrInfo;
	if ( !m_AgentSock.m_CreditUDP.Init(0, 4096, 4096, "AgentOcx", false, sErrInfo, 1) )
	{
		::MessageBox(NULL, "Socket initialization failed!", "Error", MB_OK);  //初始化失败,初始化Socket失败!
		return FALSE;
	}

	m_tLastRecvTime = GetCurrentTime();
	g_tagProductVerInfo.nVersionType = iVersionType;
	g_tagProductVerInfo.strVersionNum = sVersionNum;

	m_AgentSock.m_pSockHandle = this;
	m_AgentSock.m_pMessageWnd = this;
	if ( m_AgentSock.CreateThread() == FALSE )
	{
		::MessageBox(NULL, "Communication thread initialization failed!", "Error", MB_OK);   //   初始化失败,启动通讯线程失败!
		return FALSE;
	}
	m_AgentSock.m_bSendHeart = TRUE;
	m_bInitMsgRecv = false;

	int useTime = 0;
	while (useTime < 4000){
		//如果3秒都还没有成功，再来启动一次进程。
		if (useTime == 0 || useTime == 2000){
			KillTheProcess("IPCCService.exe");
			StartTheProcess(GetMoudlePath() + "\\IPCCService.exe", to_string(m_AgentSock.m_CreditUDP.GetPort()));
		}

		if (m_bInitMsgRecv == true){
			break;
		}

		Sleep(50);
		useTime += 50;
	}


	if (m_bInitMsgRecv == true){
		char szBuf[SIZE_FUNCBUF] = "\0";
		SIPCCMsg_OCXFuncHead head;
		head.msgType = dispidInitialize;
		head.invokeId = NewGlobalInvokeID();
		int nLen = head.FillOurBuf(szBuf);
		memcpy(szBuf + nLen, &iVersionType, sizeof(iVersionType));
		nLen += sizeof(iVersionType);
		nLen += head.FillString(szBuf + nLen, sVersionNum);
		m_AgentSock.SendUDPData(szBuf, nLen);
		m_bInit = true;
		return TRUE;
	}
	else
	{
		Exit();
		m_bInit = false;
		return FALSE;
	}
}


void CAgentPanelOcxCtrl::Exit() 
{
	if (m_bInit == false){
		return;
	}

	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidExit;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	m_AgentSock.SendUDPData(szBuf, nLen);
	
	m_AgentSock.StopThread();
	if (WaitForSingleObject(m_AgentSock.m_hThread, 2000) == WAIT_TIMEOUT){
		TerminateThread(m_AgentSock.m_hThread, 0);
	}
	m_AgentSock.m_CreditUDP.Release();



	m_bInit = false;
}

void CAgentPanelOcxCtrl::ConfigSoundSettings(BOOL bMicAutoCtrl, BOOL bEchoRemove, BOOL bMicBostUp, BOOL bUsePCSpeaker) 
{
	// TODO: Add your dispatch handler code here
	CEnvironment& env = CEnvironment::Instance();
	env.m_bMicCtrl = bMicAutoCtrl;
	env.m_bMicBost = bMicBostUp;
	env.m_bPCSpeaker = bUsePCSpeaker;
	
	env.SaveEnvironmentToFile(GetDataFilesPath() + "\\Config.ini");
	ActionUpdateSettings();
	/*
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidConfigSoundSettings;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	
	  //
	  memcpy(szBuf+nLen, &bMicAutoCtrl, sizeof(bMicAutoCtrl));
	  nLen +=  sizeof(bMicAutoCtrl);
	  //
	  memcpy(szBuf+nLen, &bEchoRemove, sizeof(bEchoRemove));
	  nLen +=  sizeof(bEchoRemove);
	  //
	  memcpy(szBuf+nLen, &bMicBostUp, sizeof(bMicBostUp));
	  nLen +=  sizeof(bMicBostUp);
	  //
	  memcpy(szBuf+nLen, &bUsePCSpeaker, sizeof(bUsePCSpeaker));
	  nLen +=  sizeof(bUsePCSpeaker);
	  m_AgentSock.SendUDPData(szBuf, nLen);
	*/
}

void CAgentPanelOcxCtrl::ActionCallOtherDepartment(LPCTSTR sCallTarget) 
{
	// TODO: Add your dispatch handler code here
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidActionCallOtherDepartment;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	nLen += head.FillString(szBuf+nLen, sCallTarget);
	m_AgentSock.SendUDPData(szBuf, nLen);
}

short CAgentPanelOcxCtrl::GetRoleInCompany()
{
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidGetRoleInCompany;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	
	CFuncReturnObject obj;
	obj.m_nFuncdispID = head.msgType;
	obj.m_nSeqenceID = head.invokeId.c_str();
	
	AddFuncToWait(obj);
	m_AgentSock.SendUDPData(szBuf, nLen);
	if(WaitFuncReturn(obj) == TRUE)
	{
		return short(obj.m_varReturn);
	}
	return 0;
}

BSTR CAgentPanelOcxCtrl::GetAgentAccount()
{
	CString strResult;
	// TODO: Add your dispatch handler code here
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidGetAgentAccount;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	
	CFuncReturnObject obj;
	obj.m_nFuncdispID = head.msgType;
	obj.m_nSeqenceID = head.invokeId.c_str();
	
	AddFuncToWait(obj);
	m_AgentSock.SendUDPData(szBuf, nLen);
	if(WaitFuncReturn(obj) == TRUE)
	{
		return ::SysAllocString((_bstr_t)obj.m_varReturn);
	}
	return strResult.AllocSysString();
}

BOOL CAgentPanelOcxCtrl::GetIsCCNUser()
{
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidGetIsCCNUser;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	
	CFuncReturnObject obj;
	obj.m_nFuncdispID = head.msgType;
	obj.m_nSeqenceID = head.invokeId.c_str();
	
	AddFuncToWait(obj);
	m_AgentSock.SendUDPData(szBuf, nLen);
	if(WaitFuncReturn(obj) == TRUE)
	{
		return bool(obj.m_varReturn);
	}
	return FALSE;
}

short CAgentPanelOcxCtrl::GetAgentType()
{
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidGetAgentType;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	
	CFuncReturnObject obj;
	obj.m_nFuncdispID = head.msgType;
	obj.m_nSeqenceID = head.invokeId.c_str();
	
	AddFuncToWait(obj);
	m_AgentSock.SendUDPData(szBuf, nLen);
	if(WaitFuncReturn(obj) == TRUE)
	{
		return short(obj.m_varReturn);
	}
	return 0;
}

BOOL CAgentPanelOcxCtrl::GetIsSMSEnabled()
{
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidGetIsSMSEnabled;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	
	CFuncReturnObject obj;
	obj.m_nFuncdispID = head.msgType;
	obj.m_nSeqenceID = head.invokeId.c_str();
	
	AddFuncToWait(obj);
	m_AgentSock.SendUDPData(szBuf, nLen);
	if(WaitFuncReturn(obj) == TRUE)
	{
		return bool(obj.m_varReturn);
	}
	return FALSE;
}

BSTR CAgentPanelOcxCtrl::GetAgentExtNum()
{
	CString strResult;
	// TODO: Add your dispatch handler code here
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidGetAgentExtNum;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	
	CFuncReturnObject obj;
	obj.m_nFuncdispID = head.msgType;
	obj.m_nSeqenceID = head.invokeId.c_str();
	
	AddFuncToWait(obj);
	m_AgentSock.SendUDPData(szBuf, nLen);
	if(WaitFuncReturn(obj) == TRUE)
	{
		return ::SysAllocString((_bstr_t)obj.m_varReturn);
	}
	return strResult.AllocSysString();
}

BSTR CAgentPanelOcxCtrl::GetAgentPhoneNo()
{
	CString strResult;
	// TODO: Add your dispatch handler code here
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidGetAgentPhoneNo;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	
	CFuncReturnObject obj;
	obj.m_nFuncdispID = head.msgType;
	obj.m_nSeqenceID = head.invokeId.c_str();
	
	AddFuncToWait(obj);
	m_AgentSock.SendUDPData(szBuf, nLen);
	if(WaitFuncReturn(obj) == TRUE)
	{
		return ::SysAllocString((_bstr_t)obj.m_varReturn);
	}
	return strResult.AllocSysString();
}

BSTR CAgentPanelOcxCtrl::GetManagerID()
{
	CString strResult;
	// TODO: Add your dispatch handler code here
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidGetManagerID;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	
	CFuncReturnObject obj;
	obj.m_nFuncdispID = head.msgType;
	obj.m_nSeqenceID = head.invokeId.c_str();
	
	AddFuncToWait(obj);
	m_AgentSock.SendUDPData(szBuf, nLen);
	if(WaitFuncReturn(obj) == TRUE)
	{
		return ::SysAllocString((_bstr_t)obj.m_varReturn);
	}
	return strResult.AllocSysString();
}

BOOL CAgentPanelOcxCtrl::GetIsMonit() 
{
	CString strResult;
	// TODO: Add your dispatch handler code here
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidGetIsMonit;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	
	CFuncReturnObject obj;
	obj.m_nFuncdispID = head.msgType;
	obj.m_nSeqenceID = head.invokeId.c_str();
	
	AddFuncToWait(obj);
	m_AgentSock.SendUDPData(szBuf, nLen);
	if(WaitFuncReturn(obj) == TRUE)
	{
		m_bMonit = bool(obj.m_varReturn);
		return bool(obj.m_varReturn);
	}
	return FALSE;
}

void  CAgentPanelOcxCtrl::HandlereturnGetRoleInCompany(char* data, int nlen)
{
	short bReturn = 0;
	SIPCCMsg_OCXFuncHead head;
	int len1 = head.ReadOurBuf(data, nlen);
	memcpy(&bReturn, data+len1, sizeof(bReturn));
	len1 += sizeof(bReturn);
	// 处理返回值
	CFuncReturnObject* pObj = NULL;
	m_LockMapFunc.Lock();
	m_mapFuncRtn.Lookup(head.invokeId.c_str(), (void* &)pObj);
	if(pObj != NULL)
	{
		pObj->m_varReturn = (short)bReturn;
		SetEvent(pObj->m_hWaitEvent);
	}
	m_LockMapFunc.Unlock();
}
void  CAgentPanelOcxCtrl::HandlereturnGetAgentAccount(char* data, int nlen)
{
	string strReturn;
	SIPCCMsg_OCXFuncHead head;
	int len1 = head.ReadOurBuf(data, nlen);
	head.GetString(data+len1, strReturn);
	// 处理返回值
	CFuncReturnObject* pObj = NULL;
	m_LockMapFunc.Lock();
	m_mapFuncRtn.Lookup(head.invokeId.c_str(), (void* &)pObj);
	if(pObj != NULL)
	{
		pObj->m_varReturn = (_bstr_t)strReturn.c_str();
		SetEvent(pObj->m_hWaitEvent);
	}
	m_LockMapFunc.Unlock();
} 

void  CAgentPanelOcxCtrl::HandlereturnGetIsCCNUser(char* data, int nlen)
{
	BOOL bReturn = FALSE;
	SIPCCMsg_OCXFuncHead head;
	int len1 = head.ReadOurBuf(data, nlen);
	memcpy(&bReturn, data+len1, sizeof(bReturn));
	len1 += sizeof(bReturn);
	// 处理返回值
	CFuncReturnObject* pObj = NULL;
	m_LockMapFunc.Lock();
	m_mapFuncRtn.Lookup(head.invokeId.c_str(), (void* &)pObj);
	if(pObj != NULL)
	{
		pObj->m_varReturn = (bool)bReturn;
		SetEvent(pObj->m_hWaitEvent);
	}
	m_LockMapFunc.Unlock();
	
}
void  CAgentPanelOcxCtrl::HandlereturnGetAgentType(char* data, int nlen)
{
	short bReturn;
	SIPCCMsg_OCXFuncHead head;
	int len1 = head.ReadOurBuf(data, nlen);
	memcpy(&bReturn, data+len1, sizeof(bReturn));
	len1 += sizeof(bReturn);
	// 处理返回值
	CFuncReturnObject* pObj = NULL;
	m_LockMapFunc.Lock();
	m_mapFuncRtn.Lookup(head.invokeId.c_str(), (void* &)pObj);
	if(pObj != NULL)
	{
		pObj->m_varReturn = (short)bReturn;
		SetEvent(pObj->m_hWaitEvent);
	}
	m_LockMapFunc.Unlock();
	
} 
void  CAgentPanelOcxCtrl::HandlereturnGetIsHasSMS(char* data, int nlen)
{
	BOOL bReturn = FALSE;
	SIPCCMsg_OCXFuncHead head;
	int len1 = head.ReadOurBuf(data, nlen);
	memcpy(&bReturn, data+len1, sizeof(bReturn));
	len1 += sizeof(bReturn);
	// 处理返回值
	CFuncReturnObject* pObj = NULL;
	m_LockMapFunc.Lock();
	m_mapFuncRtn.Lookup(head.invokeId.c_str(), (void* &)pObj);
	if(pObj != NULL)
	{
		pObj->m_varReturn = (bool)bReturn;
		SetEvent(pObj->m_hWaitEvent);
	}
	m_LockMapFunc.Unlock();
} 

void  CAgentPanelOcxCtrl::HandlereturnGetAgentExtNum(char* data, int nlen)
{
	string strReturn;
	SIPCCMsg_OCXFuncHead head;
	int len1 = head.ReadOurBuf(data, nlen);
	head.GetString(data+len1, strReturn);
	// 处理返回值
	CFuncReturnObject* pObj = NULL;
	m_LockMapFunc.Lock();
	m_mapFuncRtn.Lookup(head.invokeId.c_str(), (void* &)pObj);
	if(pObj != NULL)
	{
		pObj->m_varReturn = (_bstr_t)strReturn.c_str();
		SetEvent(pObj->m_hWaitEvent);
	}
	m_LockMapFunc.Unlock();
} 
void  CAgentPanelOcxCtrl::HandlereturnGetAgentPhoneNo(char* data, int nlen)
{
	string strReturn;
	SIPCCMsg_OCXFuncHead head;
	int len1 = head.ReadOurBuf(data, nlen);
	head.GetString(data+len1, strReturn);
	// 处理返回值
	CFuncReturnObject* pObj = NULL;
	m_LockMapFunc.Lock();
	m_mapFuncRtn.Lookup(head.invokeId.c_str(), (void* &)pObj);
	if(pObj != NULL)
	{
		pObj->m_varReturn = (_bstr_t)strReturn.c_str();
		SetEvent(pObj->m_hWaitEvent);
	}
	m_LockMapFunc.Unlock();
} 
void  CAgentPanelOcxCtrl::HandlereturnGetManagerID(char* data, int nlen)
{
	string strReturn;
	SIPCCMsg_OCXFuncHead head;
	int len1 = head.ReadOurBuf(data, nlen);
	head.GetString(data+len1, strReturn);
	// 处理返回值
	CFuncReturnObject* pObj = NULL;
	m_LockMapFunc.Lock();
	m_mapFuncRtn.Lookup(head.invokeId.c_str(), (void* &)pObj);
	if(pObj != NULL)
	{
		pObj->m_varReturn = (_bstr_t)strReturn.c_str();
		SetEvent(pObj->m_hWaitEvent);
	}
	m_LockMapFunc.Unlock();
}

BOOL CAgentPanelOcxCtrl::GetIsSuperAgent() 
{
	// TODO: Add your dispatch handler code here
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidGetIsSuperAgent;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	
	CFuncReturnObject obj;
	obj.m_nFuncdispID = head.msgType;
	obj.m_nSeqenceID = head.invokeId.c_str();
	
	AddFuncToWait(obj);
	m_AgentSock.SendUDPData(szBuf, nLen);
	if(WaitFuncReturn(obj) == TRUE)
	{
		return bool(obj.m_varReturn);
	}
	return FALSE;
}

BOOL CAgentPanelOcxCtrl::GetIsMasterSuperAgent() 
{
	// TODO: Add your dispatch handler code here
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidGetIsMasterSuperAgent;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	
	CFuncReturnObject obj;
	obj.m_nFuncdispID = head.msgType;
	obj.m_nSeqenceID = head.invokeId.c_str();
	
	AddFuncToWait(obj);
	m_AgentSock.SendUDPData(szBuf, nLen);
	if(WaitFuncReturn(obj) == TRUE)
	{
		return bool(obj.m_varReturn);
	}
	return FALSE;
}

void CAgentPanelOcxCtrl::ActionSendStrMsg(LPCTSTR sTargets, LPCTSTR sContent) 
{
	// TODO: Add your dispatch handler code here
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidActionSendStrMsg;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	nLen += head.FillString(szBuf+nLen, sTargets);
	nLen += head.FillString(szBuf+nLen, sContent);
	// 
	m_AgentSock.SendUDPData(szBuf, nLen);
}

BSTR CAgentPanelOcxCtrl::GetRemindTime() 
{
	CString strResult;	
	// TODO: Add your dispatch handler code here
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidGetRemindTime;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	
	CFuncReturnObject obj;
	obj.m_nFuncdispID = head.msgType;
	obj.m_nSeqenceID = head.invokeId.c_str();
	
	AddFuncToWait(obj);
	m_AgentSock.SendUDPData(szBuf, nLen);
	if(WaitFuncReturn(obj) == TRUE)
	{
		return ::SysAllocString((_bstr_t)obj.m_varReturn);
	}
	return strResult.AllocSysString();
}

void CAgentPanelOcxCtrl::ActionSettings() 
{
	// TODO: Add your dispatch handler code here
	ASSERT(m_pSettingsDlg);
	if(IsWindow(m_pSettingsDlg->GetSafeHwnd()) &&
		!m_pSettingsDlg->IsWindowVisible())
		m_pSettingsDlg->ShowWindow(SW_SHOW);
}

void CAgentPanelOcxCtrl::ActionMonit() 
{
	// TODO: Add your dispatch handler code here
	if (m_bMonit)
	{
		ActionStopMonit();
	}
	else
	{
		m_bTalkingAgentDlgShow = TRUE;
		ActionGetTalkingAgent();
	}
}

BOOL CAgentPanelOcxCtrl::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct) 
{
	switch(pCopyDataStruct->dwData) 
	{
	case FREEAGENTLIST_COPYDATA_MSG:
		{
		}
		break;
	case TALKAGENTLIST_COPYDATA_MSG:
		{
		}
		break;
	case CALLMESSAGE_COPYDATA_MSG:
		{
			CallMessage* pCallMsg = (CallMessage*)pCopyDataStruct->lpData;
			ASSERT(pCallMsg);
			ActionAgentOutDial(pCallMsg->sCallTarger, pCallMsg->iCallType);
		}
		break;	
	case MONITMESSAGE_COPYDATA_MSG:
		{
			MonitMessage* pCallMsg = (MonitMessage*)pCopyDataStruct->lpData;
			ASSERT(pCallMsg);
			string sMonitAgentID;
			int index = pCallMsg->sAgent.find('(');
			if (index != string::npos)
			{	
				sMonitAgentID = pCallMsg->sAgent.substr(0, index);
			}
			CString strIP, strPort;
			strIP.Format("%d", pCallMsg->iIp);
			strPort.Format("%d", pCallMsg->iPort);
			ActionStartMonit(sMonitAgentID.c_str(), strIP, strPort);
		}
		break;
	case WM_SMS_SENDFAILEDNUM:
		{
			CString sTemp = ""; 
			sTemp.Format("send msg error。 fial NO: %s", (LPCTSTR)pCopyDataStruct->lpData);
			CLog::DirectWriteFile((string)g_strLogFilePath, "Infobird_ocx.log", (string)sTemp);
			::MessageBox(NULL, sTemp, "msg", MB_OK);
		}
		break;
	default:
		break;
	}
	
	return COleControl::OnCopyData(pWnd, pCopyDataStruct);
}

void CAgentPanelOcxCtrl::ActionAgentOutDial(LPCTSTR sCallTarget, short iCallType) 
{
	// TODO: Add your dispatch handler code here
	CString strCallTarget(sCallTarget);
	if (strCallTarget == "")
	{
		m_bFreeAgentDlgShow = TRUE;
		switch (iCallType)
		{
		case dialError:
			break;
		case dialAgent:
		case dialOtherAgent:
			ActionGetFullFreeAgentInfo();
			break;
		case dialDeparment:
		case dialOtherDeparment:
			ActionGetGroupInfo();
			break;
		default:
			break;
		}
		return;
	}
	switch(iCallType) 
	{
	case dialError:
		break;
	case dialDeparment:
		ActionCallDepartment(sCallTarget);
		break;
	case dialAgent:
		ActionCallAgent(sCallTarget);
		break;
	case dialOtherDeparment:
		ActionCallOtherDepartment(sCallTarget);
		break;
	case dialOtherAgent:
		ActionCallOtherAgent(sCallTarget);
		break;
	case dialPSTN:
		ActionCallPstn(sCallTarget);
		break;
	case dialExtNo:
		ActionCallExtNum(sCallTarget);
		break;
	default:
		break;
	}
}

BOOL CAgentPanelOcxCtrl::DestroyWindow() 
{
	if (g_bMakelog)
		CLog::DirectWriteFile((string)g_strLogFilePath, "Infobird_ocx.log", "CAgentPanelOcxCtrl::DestroyWindow");

	this->Exit();

	
	if(m_pCallTargerListDlg && IsWindow(m_pCallTargerListDlg->GetSafeHwnd()))
		m_pCallTargerListDlg->DestroyWindow();
	if(m_pCallTargerListDlg)
	{
		delete m_pCallTargerListDlg;
		m_pCallTargerListDlg = NULL;
	}
	
	if(m_pMonitTargerListDlg && IsWindow(m_pMonitTargerListDlg->GetSafeHwnd()))
		m_pMonitTargerListDlg->DestroyWindow();
	if(m_pMonitTargerListDlg)
	{
		delete m_pMonitTargerListDlg;
		m_pMonitTargerListDlg = NULL;
	}
	
	m_bDestroyWindow = true;
	return COleControl::DestroyWindow();
}

BSTR CAgentPanelOcxCtrl::GetSMSParamsInfo() 
{
	CString strResult;	
	// TODO: Add your dispatch handler code here
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidGetSMSParamsInfo;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	
	CFuncReturnObject obj;
	obj.m_nFuncdispID = head.msgType;
	obj.m_nSeqenceID = head.invokeId.c_str();
	
	AddFuncToWait(obj);
	m_AgentSock.SendUDPData(szBuf, nLen);
	if(WaitFuncReturn(obj) == TRUE)
	{
	/*		//暂时spnumber和shortname都没有用处
	//by dido 09/07/14
	CString strSMSParamsInfo = ::SysAllocString((_bstr_t)obj.m_varReturn);
	int iFind = strSMSParamsInfo.Find("#.#");
	m_sSPNumber = strSMSParamsInfo.Left(iFind);
	iFind +=3;
	m_sShortName = strSMSParamsInfo.Right(strSMSParamsInfo.GetLength() - iFind);
	if (g_bMakelog)
	{
	CString str;
	str.Format("strSMSParamsInfo = %s, m_sSPNumber = %s, m_sShortName = %s", strSMSParamsInfo, m_sSPNumber, m_sShortName);
	CLog::DirectWriteFile("c:\\", "Infobird_ocx.log", "CAgentPanelOcxCtrl::GetSMSParamsInfo " + (string)str);
	}
		*/
		return ::SysAllocString((_bstr_t)obj.m_varReturn);
	}
	return strResult.AllocSysString();
}

BSTR CAgentPanelOcxCtrl::GetAllSettings() 
{
	CString strResult;
	return strResult.AllocSysString();
}

BSTR CAgentPanelOcxCtrl::GetBriefStatisticInfo(LPCTSTR sDayTime) 
{
	CString strResult;
	// TODO: Add your dispatch handler code here
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidGetBriefStatisticInfo;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	nLen += head.FillString(szBuf+nLen, sDayTime);
	
	
	CFuncReturnObject obj;
	obj.m_nFuncdispID = head.msgType;
	obj.m_nSeqenceID = head.invokeId.c_str();
	
	AddFuncToWait(obj);
	m_AgentSock.SendUDPData(szBuf, nLen);
	if(WaitFuncReturn(obj) == TRUE)
	{
		return ::SysAllocString((_bstr_t)obj.m_varReturn);
	}	
	return strResult.AllocSysString();
}

void CAgentPanelOcxCtrl::ActionSaveBriefStatisticInfo() 
{
	// TODO: Add your dispatch handler code here
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidActionSaveBriefStatisticInfo;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	m_AgentSock.SendUDPData(szBuf, nLen);
}

void CAgentPanelOcxCtrl::ActionSetMuteMode(BOOL bSetMute) 
{
	// TODO: Add your dispatch handler code here
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidActionSetMuteMode;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	memcpy(szBuf+nLen, &bSetMute, sizeof(bSetMute));
	nLen +=  sizeof(bSetMute);
	
	m_AgentSock.SendUDPData(szBuf, nLen);	
}

BSTR CAgentPanelOcxCtrl::GetTransferToIVRParamsInfo() 
{
	CString strResult;
	// TODO: Add your dispatch handler code here
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidGetTransferToIVRParamsInfo;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	
	CFuncReturnObject obj;
	obj.m_nFuncdispID = head.msgType;
	obj.m_nSeqenceID = head.invokeId.c_str();
	
	AddFuncToWait(obj);
	m_AgentSock.SendUDPData(szBuf, nLen);
	if(WaitFuncReturn(obj) == TRUE)
	{
		return ::SysAllocString((_bstr_t)obj.m_varReturn);
	}	
	return strResult.AllocSysString();
}

void CAgentPanelOcxCtrl::HandlereturnGetSMSParamsInfo(char* data, int nlen)
{
	string sReturn;
	SIPCCMsg_OCXFuncHead head;
	int len1 = head.ReadOurBuf(data, nlen);
	len1 += head.GetString(data+len1, sReturn);
	// 处理返回值
	CFuncReturnObject* pObj = NULL;
	m_LockMapFunc.Lock();
	m_mapFuncRtn.Lookup(head.invokeId.c_str(), (void* &)pObj);
	if(pObj != NULL)
	{
		pObj->m_varReturn = (_bstr_t)sReturn.c_str();
		SetEvent(pObj->m_hWaitEvent);
	}
	m_LockMapFunc.Unlock();
}

void CAgentPanelOcxCtrl::HandlereturnGetBriefStatisticInfo(char *data, int nlen)
{
	string sReturn;
	SIPCCMsg_OCXFuncHead head;
	int len1 = head.ReadOurBuf(data, nlen);
	len1 += head.GetString(data+len1, sReturn);
	// 处理返回值
	CFuncReturnObject* pObj = NULL;
	m_LockMapFunc.Lock();
	m_mapFuncRtn.Lookup(head.invokeId.c_str(), (void* &)pObj);
	if(pObj != NULL)
	{
		pObj->m_varReturn = (_bstr_t)sReturn.c_str();
		SetEvent(pObj->m_hWaitEvent);
	}
	m_LockMapFunc.Unlock();
}

void CAgentPanelOcxCtrl::ActionUpdateSettings() 
{
	// TODO: Add your dispatch handler code here
	CEnvironment& env = CEnvironment::Instance();
	env.LoadEnvironmentFromFile(GetDataFilesPath() + "\\Config.ini");
	// 发送给服务
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidActionUpdateSettings;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	m_AgentSock.SendUDPData(szBuf, nLen);	
}

void CAgentPanelOcxCtrl::HandleHeartTimeOut()
{
	//CLog::DirectWriteFile((string)g_strLogFilePath, "Infobird_ocx.log", "HandleHeartTimeOut");

	
	// 发送心跳
	DWORD tTimeNow = GetTickCount();

	// 回复检测
	if(tTimeNow - m_tLastRecvTime > TIMEOUT_HEARTBEAT)
	{
		FireOnServiceStateChange(0);
		
#ifndef	NO_IPCCSERVICE
		//hqh 2017.2.13 以后执行ActionReset不重启ipccservice，只有在心跳超时才会去执行
		// 看看进程是否存在
		KillTheProcess("IPCCService.exe");
		if (QueryProcessExsit("IPCCService.exe")){
			Sleep(500);
		}
		KillTheProcess("IPCCService.exe");
		if (QueryProcessExsit("IPCCService.exe")){
			Sleep(500);
		}
		StartTheProcess(GetMoudlePath() + "\\IPCCService.exe", to_string(m_AgentSock.m_CreditUDP.GetPort()));
#endif //
		if (CEnvironment::Instance().m_iAutoReset == 0)
		{
			FireOnUserLoginInfo(9, "12313");
		}
		else if (CEnvironment::Instance().m_iAutoReset == 1)
		{
			if (g_bMakelog)
				CLog::DirectWriteFile((string)g_strLogFilePath, "Infobird_ocx.log", "ocx接受service心跳超时！");
			FireOnChatMsgDelivered("system", "<LC>STRING_CLIENT_ERROR_LOGIN_AGAIN</LC>", 0);  
			ActionReset();
		}
		else if (CEnvironment::Instance().m_iAutoReset == 2)   //让界面自动reset
		{
			FireOnUserLoginInfo(10, "12313");
		}
	}
}

BOOL CAgentPanelOcxCtrl::GetIsCallFromACD() 
{
	// TODO: Add your dispatch handler code here
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidGetIsCallFromACD;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	
	CFuncReturnObject obj;
	obj.m_nFuncdispID = head.msgType;
	obj.m_nSeqenceID = head.invokeId.c_str();
	
	AddFuncToWait(obj);
	m_AgentSock.SendUDPData(szBuf, nLen);
	if(WaitFuncReturn(obj) == TRUE)
	{
		return bool(obj.m_varReturn);
	}
	return FALSE;
}

void  CAgentPanelOcxCtrl::HandlereturnGetIsCallFromACD(char* data, int nlen)
{
	BOOL bReturn = FALSE;
	SIPCCMsg_OCXFuncHead head;
	int len1 = head.ReadOurBuf(data, nlen);
	memcpy(&bReturn, data+len1, sizeof(bReturn));
	len1 += sizeof(bReturn);
	// 处理返回值
	CFuncReturnObject* pObj = NULL;
	m_LockMapFunc.Lock();
	m_mapFuncRtn.Lookup(head.invokeId.c_str(), (void* &)pObj);
	if(pObj != NULL)
	{
		pObj->m_varReturn = (bool)bReturn;
		SetEvent(pObj->m_hWaitEvent);
	}
	m_LockMapFunc.Unlock();
}

BOOL CAgentPanelOcxCtrl::GetIsOutDialOpenURL() 
{
	// TODO: Add your dispatch handler code here
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidGetIsOutDialOpenURL;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	
	CFuncReturnObject obj;
	obj.m_nFuncdispID = head.msgType;
	obj.m_nSeqenceID = head.invokeId.c_str();
	
	AddFuncToWait(obj);
	m_AgentSock.SendUDPData(szBuf, nLen);
	if(WaitFuncReturn(obj) == TRUE)
	{
		return bool(obj.m_varReturn);
	}
	return FALSE;
}

BOOL CAgentPanelOcxCtrl::GetIsCallInOpenURL() 
{
	// TODO: Add your dispatch handler code here
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidGetIsCallInOpenURL;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	
	CFuncReturnObject obj;
	obj.m_nFuncdispID = head.msgType;
	obj.m_nSeqenceID = head.invokeId.c_str();
	
	AddFuncToWait(obj);
	m_AgentSock.SendUDPData(szBuf, nLen);
	if(WaitFuncReturn(obj) == TRUE)
	{
		return bool(obj.m_varReturn);
	}
	return FALSE;
}

LRESULT CAgentPanelOcxCtrl::OnUpdateAllSettings(WPARAM wParam, LPARAM lParam)
{
	ActionUpdateSettings();
	return 0;
}

void CAgentPanelOcxCtrl::HandleeventOnAgentOutdialConf(char *data, int nlen)
{
	SIPCCMsg_OCXFuncHead head;
	int len1 = head.ReadOurBuf(data, nlen);
	
	string sCallID;
	len1 += head.GetString(data+len1, sCallID);
	FireOnAgentOutdialConf(sCallID.c_str());
}

void CAgentPanelOcxCtrl::HandlereturnGetIsOutdailOpenUrl(char *data, int nlen)
{
	BOOL bReturn = FALSE;
	SIPCCMsg_OCXFuncHead head;
	int len1 = head.ReadOurBuf(data, nlen);
	memcpy(&bReturn, data+len1, sizeof(bReturn));
	len1 += sizeof(bReturn);
	// 处理返回值
	CFuncReturnObject* pObj = NULL;
	m_LockMapFunc.Lock();
	m_mapFuncRtn.Lookup(head.invokeId.c_str(), (void* &)pObj);
	if(pObj != NULL)
	{
		pObj->m_varReturn = (bool)bReturn;
		SetEvent(pObj->m_hWaitEvent);
	}
	m_LockMapFunc.Unlock();
}

void CAgentPanelOcxCtrl::HandlereturnGetIsCallInOpenUrl(char* data, int nlen)
{
	BOOL bReturn = FALSE;
	SIPCCMsg_OCXFuncHead head;
	int len1 = head.ReadOurBuf(data, nlen);
	memcpy(&bReturn, data+len1, sizeof(bReturn));
	len1 += sizeof(bReturn);
	// 处理返回值
	CFuncReturnObject* pObj = NULL;
	m_LockMapFunc.Lock();
	m_mapFuncRtn.Lookup(head.invokeId.c_str(), (void* &)pObj);
	if(pObj != NULL)
	{
		pObj->m_varReturn = (bool)bReturn;
		SetEvent(pObj->m_hWaitEvent);
	}
	m_LockMapFunc.Unlock();
}

void CAgentPanelOcxCtrl::HandlereturnGetIsOutDialMode(char *data, int nlen)
{
	BOOL bReturn = FALSE;
	SIPCCMsg_OCXFuncHead head;
	int len1 = head.ReadOurBuf(data, nlen);
	memcpy(&bReturn, data+len1, sizeof(bReturn));
	len1 += sizeof(bReturn);
	// 处理返回值
	CFuncReturnObject* pObj = NULL;
	m_LockMapFunc.Lock();
	m_mapFuncRtn.Lookup(head.invokeId.c_str(), (void* &)pObj);
	if(pObj != NULL)
	{
		pObj->m_varReturn = (bool)bReturn;
		SetEvent(pObj->m_hWaitEvent);
	}
	m_LockMapFunc.Unlock();
}

short CAgentPanelOcxCtrl::GetIVRReturn() 
{
	// TODO: Add your dispatch handler code here
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidGetIVRReturn;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	// 发送并等待返回
	
	CFuncReturnObject obj;
	obj.m_nFuncdispID = head.msgType;
	obj.m_nSeqenceID = head.invokeId.c_str();
	
	AddFuncToWait(obj);
	m_AgentSock.SendUDPData(szBuf, nLen);
	if(WaitFuncReturn(obj) == TRUE)
	{
		return short(obj.m_varReturn);
	}
	return 0;
}

void CAgentPanelOcxCtrl::HandlereturnGetIVRReturn(char *data, int nlen)
{
	short bReturn = -1;
	SIPCCMsg_OCXFuncHead head;
	int len1 = head.ReadOurBuf(data, nlen);
	memcpy(&bReturn, data+len1, sizeof(bReturn));
	len1 += sizeof(bReturn);
	// 处理返回值
	CFuncReturnObject* pObj = NULL;
	m_LockMapFunc.Lock();
	m_mapFuncRtn.Lookup(head.invokeId.c_str(), (void* &)pObj);
	if(pObj != NULL)
	{
		pObj->m_varReturn = (short)bReturn;
		SetEvent(pObj->m_hWaitEvent);
	}
	m_LockMapFunc.Unlock();
}

BOOL CAgentPanelOcxCtrl::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class

     CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);

	//界面支持
	m_pCallTargerListDlg = new CGetFreeAgentDlg(this);
	m_pCallTargerListDlg->Create(IDD_DLG_FREE_AGENT, this);
	m_pCallTargerListDlg->ShowWindow(SW_HIDE);

	CRect rectFreeAgentDlg;
	m_pCallTargerListDlg->GetWindowRect(&rectFreeAgentDlg);
	m_pCallTargerListDlg->SetWindowPos(&CWnd::wndTopMost, rectFreeAgentDlg.left, rectFreeAgentDlg.top, rectFreeAgentDlg.Width(), rectFreeAgentDlg.Height(), SWP_HIDEWINDOW);
	m_pMonitTargerListDlg = new CGetTalkAgentDlg(this);
	m_pMonitTargerListDlg->Create(IDD_DLG_TALK_AGENT, this);
	m_pMonitTargerListDlg->ShowWindow(SW_HIDE);	
	
	m_pSettingsDlg = new CNewSettingsDlg(this);
	m_pSettingsDlg->Create(IDD_DLG_MY_SETTINGS, this);
	m_pSettingsDlg->ShowWindow(SW_HIDE);
	//////////////////////////////////////////////////////////////////////////

	 return TRUE;
}

void CAgentPanelOcxCtrl::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	COleControl::PreSubclassWindow();
}

void CAgentPanelOcxCtrl::HandleOCXService(char* data, int nlen)
{
	int nMsgType = *(int*)(data + 4);
	switch(nMsgType)
	{
	case Type_OCXService_SubTrans:
		SIPCCMsg_OCXService_SubTrans subTrans;
		subTrans.AnalyzeBuf(data, nlen);
		HandleSubTrans(subTrans);
		break;
	}	
}

void CAgentPanelOcxCtrl::HandleSubTrans(SIPCCMsg_OCXService_SubTrans& sub)
{
	//	if (g_bMakelog)
	//	{
	//		CString str;
	//		str.Format("sub.PackID = %d, sub.NowNum = %d, m_SubPackData.m_nPackID = %d, m_SubPackData.m_nNowNum = %d", sub.PackID, sub.NowNum, m_SubPackData.m_nPackID, m_SubPackData.m_nNowNum);
	//		CLog::DirectWriteFile("c:\\", "Infobird_ocx.log", "CAgentPanelOcxCtrl::HandleSubTrans " + (string)str);
	//	}
	
	if((sub.PackID != m_SubPackData.m_nPackID) && (sub.NowNum == 1))
	{
		if(m_SubPackData.m_pMsgData != NULL)
		{
			delete[] m_SubPackData.m_pMsgData;
			m_SubPackData.m_pMsgData = NULL;
		}
		m_SubPackData.m_nMsgLen = 0;
		
		//		if (g_bMakelog)
		//		{
		//			SIPCCMsg_OCXFuncHead head;
		//			int len1 = head.ReadOurBuf(sub.DataBuf, sub.DataLen);
		//			
		//			char cAgentList[CREDITUDP_BUFFER_SIZE] = {0};
		//			memcpy(cAgentList, sub.DataBuf + len1, CREDITUDP_BUFFER_SIZE-len1);
		//			
		//			CString str;
		//			str.Format("m_SubPackData.m_nPackID=%d, m_SubPackData.m_nNowNum=%d, sub.TotNum=%d, sub.DataLen=%d, sub.DataBuf=%s", m_SubPackData.m_nPackID, m_SubPackData.m_nNowNum, sub.TotNum, sub.DataLen, cAgentList);
		//			CLog::DirectWriteFile("c:\\", "Infobird_ocx.log", "第一次接收包 " + (string)str);
		//		}
		// 接收数据
		m_SubPackData.m_nPackID = sub.PackID;
		m_SubPackData.m_nNowNum = 1;
		m_SubPackData.m_nTotNum = sub.TotNum;
		m_SubPackData.m_pMsgData = new char[sub.TotNum*sizeof(sub.DataBuf)];
		memcpy(m_SubPackData.m_pMsgData, sub.DataBuf, sub.DataLen);
		m_SubPackData.m_nMsgLen = sub.DataLen;
	}
	else if((sub.PackID == m_SubPackData.m_nPackID) && (sub.NowNum == m_SubPackData.m_nNowNum+1))
	{
		//		if (g_bMakelog)
		//		{
		//			CString str;
		//			char cAgentList[CREDITUDP_BUFFER_SIZE+1] = {0};
		//			memcpy(cAgentList, sub.DataBuf, CREDITUDP_BUFFER_SIZE);
		//			
		//			str.Format("m_SubPackData.m_nPackID=%d, m_SubPackData.m_nNowNum=%d, sub.DataLen=%d, sub.DataBuf=%s", m_SubPackData.m_nPackID, m_SubPackData.m_nNowNum, sub.DataLen, cAgentList);
		//			CLog::DirectWriteFile("c:\\", "Infobird_ocx.log", "连续接收包 " + (string)str);
		//		}
		m_SubPackData.m_nNowNum = sub.NowNum;
		memcpy(m_SubPackData.m_pMsgData+m_SubPackData.m_nMsgLen, sub.DataBuf, sub.DataLen);
		m_SubPackData.m_nMsgLen += sub.DataLen;
		// 数据完成
		if(m_SubPackData.m_nNowNum == m_SubPackData.m_nTotNum)
		{
			HandleRecvMsg(m_SubPackData.m_pMsgData, m_SubPackData.m_nMsgLen);
		}
	}
}

LRESULT CAgentPanelOcxCtrl::OnSMSSendSuccess(WPARAM wParam,LPARAM lParam)
{
	FireOnUserLoginInfo(100, "send msg suc!");
	return 1;
}

LRESULT CAgentPanelOcxCtrl::OnSMSSendFailed(WPARAM wParam,LPARAM lParam)
{
	FireOnUserLoginInfo(101, "send msg fail");
	return 1;
}

void CAgentPanelOcxCtrl::SetProductVersion(short iVersionType, LPCTSTR sVersionNum) 
{
	// TODO: Add your dispatch handler code here
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidSetProductVersion;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	
	memcpy(szBuf+nLen, &iVersionType, sizeof(iVersionType));
	nLen += sizeof(iVersionType);
	nLen += head.FillString(szBuf+nLen, sVersionNum);
	m_AgentSock.SendUDPData(szBuf, nLen);
	
	g_tagProductVerInfo.nVersionType = iVersionType;
	g_tagProductVerInfo.strVersionNum = sVersionNum;
}

DWORD WINAPI CAgentPanelOcxCtrl::BeepThread(LPVOID lpThis)
{
	//hqh 2017.4.28 增加一个单例,保证同一时间只有一个线程处理
	static bool bProcess = false;
	if (bProcess == true){
		return 0;
	}
	bProcess = true;
	CEnvironment &env = CEnvironment::Instance();
	while(1)
	{
		for(int i = 0; i < 3; i++)
		{
			if(m_bStopBeep == TRUE) 
				return 1;
			MyBeep(env.m_nBeepIndex, env.m_nBeepFreq, env.m_nBeepDura);
			Sleep(40);
		}
		Sleep(200);
	}
	bProcess = false;
	return 1;
}

void CAgentPanelOcxCtrl::MyBeep(int nIndex, int freq, int dura)
{
	if(nIndex == 0)
	{
		Beep(2000, 50);
	}
	else if(nIndex == 1)
	{
		Beep(2000, 250);
	}
	else if(nIndex == 2)
	{
		Beep(2000, 500);
	}
	else
	{
		Beep(freq, dura);
	}
	Sleep(40);
}

BSTR CAgentPanelOcxCtrl::GetRecInvokePath() 
{
	CString strResult;
	// TODO: Add your dispatch handler code here
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidGetRecInvokePath;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	
	CFuncReturnObject obj;
	obj.m_nFuncdispID = head.msgType;
	obj.m_nSeqenceID = head.invokeId.c_str();
	
	AddFuncToWait(obj);
	m_AgentSock.SendUDPData(szBuf, nLen);
	if(WaitFuncReturn(obj) == TRUE)
	{
		return ::SysAllocString((_bstr_t)obj.m_varReturn);
	}
	return strResult.AllocSysString();
}

void CAgentPanelOcxCtrl:: HandlereturnGetRecInvokePath(char* data, int nlen)
{
	string sReturn;
	SIPCCMsg_OCXFuncHead head;
	int len1 = head.ReadOurBuf(data, nlen);
	len1 += head.GetString(data+len1, sReturn);
	// 处理返回值
	CFuncReturnObject* pObj = NULL;
	m_LockMapFunc.Lock();
	m_mapFuncRtn.Lookup(head.invokeId.c_str(), (void* &)pObj);
	if(pObj != NULL)
	{
		pObj->m_varReturn = (_bstr_t)sReturn.c_str();
		SetEvent(pObj->m_hWaitEvent);
	}
	m_LockMapFunc.Unlock();
}

BSTR CAgentPanelOcxCtrl::GetAgentID() 
{
	CString strResult;
	// TODO: Add your dispatch handler code here
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidGetAgentID;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	
	CFuncReturnObject obj;
	obj.m_nFuncdispID = head.msgType;
	obj.m_nSeqenceID = head.invokeId.c_str();
	
	AddFuncToWait(obj);
	m_AgentSock.SendUDPData(szBuf, nLen);
	if(WaitFuncReturn(obj) == TRUE)
	{
		return ::SysAllocString((_bstr_t)obj.m_varReturn);
	}
	return strResult.AllocSysString();
}

void CAgentPanelOcxCtrl::HandlereturnGetAgentID(char* data, int nlen)
{
	string sReturn;
	SIPCCMsg_OCXFuncHead head;
	int len1 = head.ReadOurBuf(data, nlen);
	len1 += head.GetString(data+len1, sReturn);
	// 处理返回值
	CFuncReturnObject* pObj = NULL;
	m_LockMapFunc.Lock();
	m_mapFuncRtn.Lookup(head.invokeId.c_str(), (void* &)pObj);
	if(pObj != NULL)
	{
		pObj->m_varReturn = (_bstr_t)sReturn.c_str();
		SetEvent(pObj->m_hWaitEvent);
	}
	m_LockMapFunc.Unlock();
}

void CAgentPanelOcxCtrl::HandleeventOnACDSendStrMsg(char* data, int nlen)
{
	SIPCCMsg_OCXFuncHead head;
	int len1 = head.ReadOurBuf(data, nlen);
	
	string stheSender;
	len1 += head.GetString(data+len1, stheSender);
	string smsgContent;
	len1 += head.GetString(data+len1, smsgContent);
	FireOnACDSendStrMsg(stheSender.c_str(), smsgContent.c_str());
}

void CAgentPanelOcxCtrl::HandleeventOnLoginSendStrMsg(char* data, int nlen)
{
	SIPCCMsg_OCXFuncHead head;
	int len1 = head.ReadOurBuf(data, nlen);
	
	long nStrMsgID;
	memcpy(&nStrMsgID, data+len1, sizeof(nStrMsgID));
	len1 += sizeof(nStrMsgID);
	
	string stheSender;
	len1 += head.GetString(data+len1, stheSender);
	string smsgContent;
	len1 += head.GetString(data+len1, smsgContent);
	FireOnLoginSendStrMsg(nStrMsgID, stheSender.c_str(), smsgContent.c_str());
}

void CAgentPanelOcxCtrl::HandleeventOnIVRReturnToAgentConf(char* data, int nlen)
{
	SIPCCMsg_OCXFuncHead head;
	int len1 = head.ReadOurBuf(data, nlen);
	
	string sIVRPrivateData;
	len1 += head.GetString(data+len1, sIVRPrivateData);
	
	FireOnIVRReturnToAgentConf(sIVRPrivateData.c_str());
}

void CAgentPanelOcxCtrl::SetOriginalData(LPCTSTR sOriginalData) 
{
	// TODO: Add your dispatch handler code here
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidSetOriginalData;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	
	nLen += head.FillString(szBuf+nLen, sOriginalData);
	m_AgentSock.SendUDPData(szBuf, nLen);
}

void CAgentPanelOcxCtrl::ActionOutDial(LPCTSTR sCallTarget) 
{
	// TODO: Add your dispatch handler code here
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidActionOutDial;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	
	nLen += head.FillString(szBuf+nLen, sCallTarget);
	m_AgentSock.SendUDPData(szBuf, nLen);
}
void CAgentPanelOcxCtrl::SetSelectGroup(LPCTSTR sGroup) 
{
	// TODO: Add your dispatch handler code here
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidSetSelectGroup;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	
	nLen += head.FillString(szBuf+nLen, sGroup);
	m_AgentSock.SendUDPData(szBuf, nLen);
}

void CAgentPanelOcxCtrl::HandleeventOnNotifyAgentLoginConf(char* data, int nlen)
{
	SIPCCMsg_OCXFuncHead head;
	int len1 = head.ReadOurBuf(data, nlen);
	
	string sAgentLoginInfo;
	len1 += head.GetString(data+len1, sAgentLoginInfo);
	
	FireOnNotifyAgentLoginConf(sAgentLoginInfo.c_str());
	
	CSpliter split(sAgentLoginInfo, "|");
	SMSSend_URL = split[1];
}

//hqh 2017.6.12
void CAgentPanelOcxCtrl::HandleeventOnAddTalkToWebChat(char* data, int nlen){
	SIPCCMsg_OCXFuncHead head;
	int len1 = head.ReadOurBuf(data, nlen);

	string sCallType;
	len1 += head.GetString(data + len1, sCallType);
	string sCaller;
	len1 += head.GetString(data + len1, sCaller);
	string sCallee;
	len1 += head.GetString(data + len1, sCallee);
	string sCallid;
	len1 += head.GetString(data + len1, sCallid);
	string sOriginalData;
	len1 += head.GetString(data + len1, sOriginalData);
	string sCallerType;
	len1 += head.GetString(data + len1, sCallerType);
	string sKeyword;
	len1 += head.GetString(data + len1, sKeyword);
	FireOnAddTalkToWebChat(sCallType.c_str(), sCaller.c_str(), sCallee.c_str(), sCallid.c_str(), sOriginalData.c_str(), sCallerType.c_str(), sKeyword.c_str());
}


void CAgentPanelOcxCtrl::ActionAutoTransferEx(LPCTSTR sCallTarget) 
{
	// TODO: Add your dispatch handler code here
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidActionAutoTransferEx;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	
	nLen += head.FillString(szBuf+nLen, sCallTarget);
	m_AgentSock.SendUDPData(szBuf, nLen);
}

void CAgentPanelOcxCtrl::ActionOutDialWithRecSetting(LPCTSTR sTarget, LPCTSTR sRecPath) 
{
	// TODO: Add your dispatch handler code here
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidActionOutDialWithRecSetting;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	nLen += head.FillString(szBuf+nLen, sTarget);
	nLen += head.FillString(szBuf+nLen, sRecPath);
	// 
	m_AgentSock.SendUDPData(szBuf, nLen);
}

void CAgentPanelOcxCtrl::ActionOffHookWithRecSetting(LPCTSTR sRecPath) 
{
	// TODO: Add your dispatch handler code here
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidActionOffHookWithRecSetting;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	nLen += head.FillString(szBuf+nLen, sRecPath);
	m_AgentSock.SendUDPData(szBuf, nLen);
}

BSTR CAgentPanelOcxCtrl::GetParkReasons() 
{
	CString strResult;
	// TODO: Add your dispatch handler code here
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidGetParkReasons;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	
	CFuncReturnObject obj;
	obj.m_nFuncdispID = head.msgType;
	obj.m_nSeqenceID = head.invokeId.c_str();
	
	AddFuncToWait(obj);
	m_AgentSock.SendUDPData(szBuf, nLen);
	if(WaitFuncReturn(obj) == TRUE)
	{
		return ::SysAllocString((_bstr_t)obj.m_varReturn);
	}
	return strResult.AllocSysString();
}

void CAgentPanelOcxCtrl::SetParkReason(short iParkReasonID) 
{
	// TODO: Add your dispatch handler code here
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidSetParkReason;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	
	memcpy(szBuf+nLen, &iParkReasonID, sizeof(iParkReasonID));
	nLen += sizeof(iParkReasonID);
	m_AgentSock.SendUDPData(szBuf, nLen);
}

void CAgentPanelOcxCtrl::HandlereturnGetParkReasons(char* data, int nlen)
{
	string sReturn;
	SIPCCMsg_OCXFuncHead head;
	int len1 = head.ReadOurBuf(data, nlen);
	len1 += head.GetString(data+len1, sReturn);
	// 处理返回值
	CFuncReturnObject* pObj = NULL;
	m_LockMapFunc.Lock();
	m_mapFuncRtn.Lookup(head.invokeId.c_str(), (void* &)pObj);
	if(pObj != NULL)
	{
		pObj->m_varReturn = (_bstr_t)sReturn.c_str();
		SetEvent(pObj->m_hWaitEvent);
	}
	m_LockMapFunc.Unlock();
}

void CAgentPanelOcxCtrl::SetCallerSendingInDialing(LPCTSTR sCaller) 
{
	// TODO: Add your dispatch handler code here
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidSetCallerSendingInDialing;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	nLen += head.FillString(szBuf+nLen, sCaller);
	m_AgentSock.SendUDPData(szBuf, nLen);
}

void CAgentPanelOcxCtrl::ActionJoinOutDialMode(BOOL bJoinOutDialMode) 
{
	// TODO: Add your dispatch handler code here
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidActionJoinOutDialMode;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	memcpy(szBuf+nLen, &bJoinOutDialMode, sizeof(bJoinOutDialMode));
	nLen +=  sizeof(bJoinOutDialMode);
	
	m_AgentSock.SendUDPData(szBuf, nLen);	
}

BOOL CAgentPanelOcxCtrl::GetIsOutDialMode() 
{
	// TODO: Add your dispatch handler code here
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidGetIsOutDialMode;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	
	CFuncReturnObject obj;
	obj.m_nFuncdispID = head.msgType;
	obj.m_nSeqenceID = head.invokeId.c_str();
	
	AddFuncToWait(obj);
	m_AgentSock.SendUDPData(szBuf, nLen);
	if(WaitFuncReturn(obj) == TRUE)
	{
		return bool(obj.m_varReturn);
	}
	return FALSE;
}

void CAgentPanelOcxCtrl::UpdateSettings()
{
	ActionUpdateSettings();
}

BSTR CAgentPanelOcxCtrl::GetMoudleFilePath() 
{
	CString strResult;
	// TODO: Add your dispatch handler code here
	strResult = GetMoudlePath();
	return strResult.AllocSysString();
}

void CAgentPanelOcxCtrl::ActionSetMuteModeEx(long nDev, long nVolume, BOOL bSet) 
{
	// TODO: Add your dispatch handler code here
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidActionSetMuteModeEx;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	memcpy(szBuf+nLen, &nDev, sizeof(nDev));
	nLen +=  sizeof(nDev);
	memcpy(szBuf+nLen, &nVolume, sizeof(nVolume));
	nLen +=  sizeof(nVolume);
	memcpy(szBuf+nLen, &bSet, sizeof(bSet));
	nLen +=  sizeof(bSet);
	
	m_AgentSock.SendUDPData(szBuf, nLen);
}
// add by lh.wang date:2012.11.08 第三方 
void CAgentPanelOcxCtrl::ActionStartConference()
{
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidActionStartConference;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	m_AgentSock.SendUDPData(szBuf, nLen);
}

void CAgentPanelOcxCtrl::ActionEndConference()
{
    char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidActionEndConference;
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	m_AgentSock.SendUDPData(szBuf, nLen);
}

void CAgentPanelOcxCtrl::HandlereturnGetCanConference(char *data,int nlen)
{
	bool bReturn = 0;
	SIPCCMsg_OCXFuncHead head;
	int len1 = head.ReadOurBuf(data, nlen);
	memcpy(&bReturn, data+len1, sizeof(bReturn));
	len1 += sizeof(bReturn);
	// 处理返回值
	CFuncReturnObject* pObj = NULL;
	m_LockMapFunc.Lock();
	m_mapFuncRtn.Lookup(head.invokeId.c_str(), (void* &)pObj);
	if(pObj != NULL)
	{
		pObj->m_varReturn = (bool)bReturn;
		SetEvent(pObj->m_hWaitEvent);
	}
	m_LockMapFunc.Unlock();
}

BOOL CAgentPanelOcxCtrl::GetCanConference()
{
	char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidGetCanConference;              
	head.invokeId = NewGlobalInvokeID();
	int nLen = head.FillOurBuf(szBuf);
	// 发送并等待返回
	
	CFuncReturnObject obj;
	obj.m_nFuncdispID = head.msgType;
	obj.m_nSeqenceID = head.invokeId.c_str();
	
	AddFuncToWait(obj);
	m_AgentSock.SendUDPData(szBuf, nLen);
	if(WaitFuncReturn(obj) == TRUE)
	{
		bool b = obj.m_varReturn;
		return bool(obj.m_varReturn);
	}
	return FALSE;
}
// end add 

void CAgentPanelOcxCtrl::StopPlayAgentID()
{
    char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidStopPlayAgentID;
	head.invokeId = NewGlobalInvokeID();
	
	int nLen = head.FillOurBuf(szBuf);
	
	m_AgentSock.SendUDPData(szBuf, nLen);
}

void CAgentPanelOcxCtrl::ActionACDAutoLogin()
{
    char szBuf[SIZE_FUNCBUF] = "\0";
	SIPCCMsg_OCXFuncHead head;
	head.msgType = dispidActionACDAutoLogin;
	head.invokeId = NewGlobalInvokeID();
	
	int nLen = head.FillOurBuf(szBuf);
	
	m_AgentSock.SendUDPData(szBuf, nLen);
}

void CAgentPanelOcxCtrl::SetLogonMode(short nLoginMode) 
{
	// TODO: Add your dispatch handler code here
	CEnvironment &env = CEnvironment::Instance();
	if (nLoginMode == 1)
		env.m_iLoginType = LoginType_WebPSTN;
	else 
		env.m_iLoginType = LoginType_OnlyPSTN;
	env.SaveEnvironmentToFile(GetDataFilesPath() + "\\Config.ini");
}
