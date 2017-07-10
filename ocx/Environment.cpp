// Environment.cpp: implementation of the CEnvironment class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Environment.h"
#include "resource.h"
#include "log.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
BOOL g_bMakelog = TRUE;
PRODUCT_VER_INFO g_tagProductVerInfo;
extern CString g_strLogFilePath;

CEnvironment::CEnvironment()
{
	if (g_tagProductVerInfo.nVersionType & VerType_IPCC)
	{
		m_structCSTPort.iUseDefineIP = 1;
	}
	else
	{
		m_structCSTPort.iUseDefineIP = 0;
	}
	m_bAlwaysTrans = TRUE;
	m_bEchoRemove = FALSE;
	m_bTransferWithCallNum = FALSE;
	m_bOutDialMobileAddZero = FALSE;
	m_bLoginSaveInfo = TRUE;
	m_bLoginSavePsw = FALSE;
	m_strLoginUser = "";
	m_strLoginPsw = "";

	m_structCSTPort.nMainPort = 0;
	m_iAecErl = 30;
	m_structCSTPort.bUseDefine = false;
	m_bUseTCPTransfer = FALSE;
	m_bUserAECERL = TRUE;
	m_bIsLanAgent = FALSE;
	m_bDirectConnectToGateway = FALSE;
	m_sAgentPartNo = "";
	m_bPCSpeaker = TRUE;
	m_bUseAutoAreaNum = FALSE;
	m_sAreaNum = "";
	m_bOneKeyToPhone=FALSE;
	m_sOutPhoneNum="";
	m_iLoginType = LoginType_OnlyWeb;
	m_bAutoOffhook = FALSE;
	m_bMicAttenuation = FALSE;	
	m_bMicBoost = FALSE;
	m_dwMainVolume = 65535*2/3;
	m_dwMicphoneValue = 65535/3;
	m_nAudioCapDev = 0;	// +[9/12/2007 lixg]
	m_nAudioRenderDev = 0;// +[9/12/2007 lixg]	
	m_dDtmfVolume = 2000;
	m_bUseLocalVad = TRUE;
	m_bEncodeUUIData = TRUE;
	m_strOutDialHead1 = "";
	m_strOutDialHead2 = "";
	m_bTransferToIVR = FALSE;
	m_sSMSServerIP = "219.234.83.35";
	m_strCustomWebUrl = "";
	//RTP Added
	if (g_tagProductVerInfo.nVersionType & VerType_RTP)
	{
		m_fAgentVolume = 2.0000;
		m_fClientVolume = 1.5000;
		m_fCaptureZoom = 2.0000;
		m_fPlayZoom = 2.0000;

		m_bUseSipPhone = FALSE;
		m_sSipPhoneIP = "0.0.0.0";
		m_iSipPhonePort = 0;
		m_sSipPhoneRTPPort = "";
		m_sSipPhoneRTCPPort = "";
	}
	else
	{
		m_fAgentVolume = 1.0000;
		m_fClientVolume = 1.0000;
		m_fCaptureZoom = 1.0000;
		m_fPlayZoom = 1.0000;

		m_bUseSipPhone = FALSE;
		m_sSipPhoneIP = "0.0.0.0";
		m_iSipPhonePort = 0;
	}

	m_bServiceRunDebug = FALSE;
	m_iAutoReset = 1;
	m_bUsingVADMode = TRUE;
	m_bOpenWebpageNew = TRUE;
	m_iOnHookDelay = 0;
	// 蜂鸣音
	m_nBeepIndex = 0;
	m_nBeepFreq = 3800;
	m_nBeepDura = 120;
	// LocalAdmin
	m_strUser = "";
	m_strPwd = "";
	m_bRecordRespectively = FALSE;

	//RTP Added End	
	m_uAgentOcxPort = 57498;
	m_uServicePort = 57499;
	
	m_strWebLoginUrl = "";
	m_strFirstUrl = "";
	m_strWebmainUrl = "";
	m_strLoginServerIP = "";
	m_bUseUserDefinedServer = FALSE;
	m_bUseUserDefinedWebPage = FALSE;
	m_bUseUserDefinedWebMain = FALSE;
	m_bAcdAndUserState = FALSE;
	m_bOutDialMobileGetAreaCode = TRUE;
	m_sSmartOutDialHead = "";
	m_sLongXingKey = "infobirdlongxing";
	m_iGUISupportIEVersion = 0;

	m_bCaptureInfo = FALSE;
	m_bIVRToAgentPrompt = FALSE;
	m_bSendHeartPack=FALSE;
	m_bChangePort=FALSE;
  	m_nChangePortIntervalTime=300;
	m_bDatatransChangePort=FALSE;
  	m_nDatatransChangePortIntervalTime=300;
	m_ncanredundancy=0;
	m_bvadmute=FALSE;
	m_bInboundPlayAgentID = TRUE;
	m_bOutboundPlayAgentID = FALSE;

	m_bTCPSelfDefine = FALSE;
	m_sTCPProxyIP = "";
	m_nTCPProxyPort = 0;
	m_bVirtualApp=FALSE;
	m_strVirtualOCXIP="0.0.0.0";
	m_nACDAutoLoginTime=60;
	// 2014-9-1
	m_bDeliverClipBoard = TRUE;
	m_bUseURLEncode = FALSE;
}

CEnvironment::~CEnvironment()
{
	
}

CEnvironment& CEnvironment::Instance()
{
	static CEnvironment envir;

	return envir;
}

BOOL CEnvironment::SaveEnvironmentToFile(LPCSTR szFileName)
{
	//by hqh 2015.6.18 加锁
	HANDLE mutexRW = CreateMutex(NULL, FALSE, TEXT("INFOBIRD_CLIENT_ENVFILE_MUTEX"));
	if (mutexRW)
		WaitForSingleObject(mutexRW, INFINITE);

	CIniFile ini(szFileName);

	//保存本次 最优中转服务器ip及Port
	ini.SetValue("DataTrans", "ServerIP", m_sDataTransIP);
	ini.SetValueI("DataTrans", "ServerPort", m_iDataTransPort);
	//Login
	ini.SetValueB("PortSettings", "UsePort", (bool)m_structCSTPort.bUseDefine);
	ini.SetValueI("PortSettings", "AgentPort", m_structCSTPort.nMainPort);
	ini.SetValueI("PortSettings", "AudioPort1", m_structCSTPort.nAssistantPort1);
	ini.SetValueI("PortSettings", "AudioPort2", m_structCSTPort.nAssistantPort2);
	ini.SetValueB("PortSettings", "TCPTransfer", m_bUseTCPTransfer);
	ini.SetValueB("PortSettings", "DirectConnectToGateway", m_bDirectConnectToGateway);
	ini.SetValueB("PortSettings", "DirectTransmit", m_bAlwaysTrans);
	ini.SetValueI("LoginSettings", "define", m_structCSTPort.iUseDefineIP);
	ini.SetValue("LoginSettings", "customizeip", m_structCSTPort.szCustomizeIP);
	ini.SetValue("LoginSettings", "customizedomain", m_structCSTPort.szCustomizeDomain);
	ini.SetValueB("LoginSettings", "AgentType", m_bIsLanAgent);
	ini.SetValueI("LoginSettings", "LoginType", m_iLoginType);
	ini.SetValueB("LoginSettings", "LoginSaveInfo", m_bLoginSaveInfo);
	ini.SetValueB("LoginSettings", "LoginSavePsw", m_bLoginSavePsw);
	ini.SetValue("LoginSettings", "LoginUserName", m_strLoginUser);
	ini.SetValue("LoginSettings", "LoginPassWord", m_strLoginPsw);
	ini.SetValue("LoginSettings", "LoginCorporat", m_strLoginCorp);
	ini.SetValueB("LoginSettings", "UseUserDefinedServer", m_bUseUserDefinedServer);
	ini.SetValueB("LoginSettings", "UseUserDefinedWebPage", m_bUseUserDefinedWebPage);
	ini.SetValueB("LoginSettings", "UseUserDefinedWebMain", m_bUseUserDefinedWebMain);
	ini.SetValue("LoginSettings", "WebLoginFirstUrl", m_strWebLoginUrl);
	ini.SetValue("LoginSettings", "UserDefinedFirstUrl", m_strFirstUrl);
	ini.SetValue("LoginSettings", "UserDefinedWebmainUrl", m_strWebmainUrl);
	ini.SetValue("LoginSettings", "UserDefinedLoginServerIP", m_strLoginServerIP);
	
	ini.SetValueI("RecSettings", "RecOption", m_structRecorderSet.nRecorderMode );
	ini.SetValue("RecSettings", "RecServerIP", m_structRecorderSet.szRecorderServerIP);
	ini.SetValueB("RecSettings", "RecordRespectively", m_bRecordRespectively);
	ini.SetValue("RecSettings", "RecPath", m_structRecorderSet.szRecordPath);

	ini.SetValueI("OutDialMode", "OutDialMode", m_nOutDialMode);
	ini.SetValue("OutDialMode", "AgentPartNo", m_sAgentPartNo);
	ini.SetValueB("OutDialMode", "UseAreaNo", m_bUseAutoAreaNum);
	ini.SetValue("OutDialMode", "AreaNo", m_sAreaNum);
	ini.SetValueB("OutDialMode", "OneKeyToPhone", m_bOneKeyToPhone);
	ini.SetValue("OutDialMode", "PhoneNo", m_sOutPhoneNum);
	ini.SetValueB("OutDialMode", "OutdialMobileAddZero", m_bOutDialMobileAddZero);
	ini.SetValueB("OutDialMode", "AutoOffhook", m_bAutoOffhook);
	ini.SetValueB("OutDialMode", "TransferWithCallNum", m_bTransferWithCallNum);
	ini.SetValueB("OutDialMode", "EncodeUUIData", m_bEncodeUUIData);

	ini.SetValueB("Sound", "UserAecErl", m_bUserAECERL);
	ini.SetValueI("Sound", "AecErl", m_iAecErl);
	ini.SetValueB("Sound", "MicBost", m_bMicBost);
	ini.SetValueB("Sound", "PCSpeaker", m_bPCSpeaker);
	ini.SetValueB("Sound", "MicBoost", m_bMicBoost);
	ini.SetValueI("Sound", "Volume", m_dwMainVolume);
	ini.SetValueI("Sound", "Micphone", m_dwMicphoneValue);
	ini.SetValueB("Sound", "EchoRemove", m_bEchoRemove );
	ini.SetValueB("Sound", "MicAttenuation", m_bMicAttenuation);
	ini.SetValueI("Sound", "DTMFVolume", m_dDtmfVolume);
	ini.SetValueB("Sound", "LocalUseVAD", m_bUseLocalVad);
	ini.SetValueB("Sound", "UsingVADMode", m_bUsingVADMode);
	
	ini.SetValueB("WebURL", "OpenWebpageInNewTag", m_bOpenWebpageNew);
	ini.SetValue("WebURL", "CustomWebUrl", m_strCustomWebUrl);
	ini.SetValueI("WebURL", "GUISupportIEVersion", m_iGUISupportIEVersion);
	ini.SetValueB("WebURL", "UrlEncode", m_bUseURLEncode);

	ini.SetValueB("Sound", "MicCtrl", m_bMicCtrl);

	//////////////////////////////////////////////////////////////////////////
	// +在这存audio设备。 [9/12/2007 lixg]
	ini.SetValueI("AudioDev", "AudioCapDev", m_nAudioCapDev);	
	ini.SetValue("AudioDev", "AudioCapDevName", m_strAudioCapDevName);
	ini.SetValueI("AudioDev", "AudioRenderDev", m_nAudioRenderDev);
	ini.SetValue("AudioDev", "AudioRenderDevName", m_strAudioRenderDevName);
	//////////////////////////////////////////////////////////////////////////
	ini.SetValue("OutDialMode","OutDialHead1", m_strOutDialHead1);
	ini.SetValue("OutDialMode","OutDialHead2", m_strOutDialHead2);
	ini.SetValueB("OutDialMode", "TransferToIVR", m_bTransferToIVR);
	ini.SetValueI("OutDialMode", "OnHookDelay", m_iOnHookDelay);
	ini.SetValueB("OutDialMode", "OutDialMobileGetAreaCode", m_bOutDialMobileGetAreaCode);
	ini.SetValue("OutDialMode", "SmartOutDialHead", m_sSmartOutDialHead);
	
	ini.SetValueB("Log", "MakeLog", g_bMakelog);
	ini.SetValue("SMS", "SMSServerIP", m_sSMSServerIP);
	ini.SetValueB("System", "RunningMode", m_bServiceRunDebug);
	ini.SetValueI("System", "AutoReset", m_iAutoReset);
	ini.SetValue("System", "LongXingKey", m_sLongXingKey);
	ini.SetValueB("System", "IVRToAgentPrompt", m_bIVRToAgentPrompt);
//	ini.SetValueB("System", "CaptureInfo", m_bCaptureInfo);
	
	ini.SetValueB("System", "TCPSelfDefine", m_bTCPSelfDefine);
	ini.SetValue("System", "TCPProxyIP", m_sTCPProxyIP);
	ini.SetValueI("System", "TCPProxyPort", m_nTCPProxyPort);
	// 2014-9-1
	ini.SetValueB("System","DeliverClipBoard",m_bDeliverClipBoard);

	//by dido 09/04/16
	ini.SetValueF("Volume", "AgentVolume", m_fAgentVolume);
	ini.SetValueF("Volume", "ClientVolume", m_fClientVolume);
	ini.SetValueF("Volume", "CaptureZoom", m_fCaptureZoom);
	ini.SetValueF("Volume", "PlayZoom", m_fPlayZoom);
	
	//RTP Added
	if (g_tagProductVerInfo.nVersionType & VerType_RTP)
	{
		//by dido 09/01/05
		ini.SetValueB("SipPhone", "UseSipPhone", m_bUseSipPhone);
		ini.SetValue("SipPhone", "SipPhoneIP", m_sSipPhoneIP);
		ini.SetValueI("SipPhone", "SipPhonePort", m_iSipPhonePort);
		ini.SetValue("SipPhone", "SipPhoneRTPPort", m_sSipPhoneRTPPort);
		ini.SetValue("SipPhone", "SipPhoneRTCPPort", m_sSipPhoneRTCPPort);
	}
	else
	{
		ini.SetValueB("SipPhone", "UseSipPhone", m_bUseSipPhone);
		ini.SetValue("SipPhone", "SipPhoneIP", m_sSipPhoneIP);
		ini.SetValueI("SipPhone", "SipPhonePort", m_iSipPhonePort);
	}
	
	ini.SetValueI("AgentOcxPort", "OcxPort", m_uAgentOcxPort);
	ini.SetValueI("AgentOcxPort", "ServicePort", m_uServicePort);
	
	// BeepSet
	ini.SetValueI("BeepSet", "Index", m_nBeepIndex);
	ini.SetValueI("BeepSet", "Freq", m_nBeepFreq);
	ini.SetValueI("BeepSet", "Dura", m_nBeepDura);
	// LocalAdmin
	ini.SetValue("LocalAdmin", "User", m_strUser);
	ini.SetValue("LocalAdmin", "Pwd", m_strPwd);

	// 是否支持合并ACD和UserState版本
	ini.SetValueB("AcdAndUserState", "Enable", m_bAcdAndUserState);	// [scq/2010-07-26]
	ini.SetValueB("SendHeartPack", "Enable", m_bSendHeartPack);

    ini.SetValueB("ChangePort", "Enable", m_bChangePort);
	ini.SetValueI("ChangePort", "IntervalTime", m_nChangePortIntervalTime);
	ini.SetValueB("ChangePort", "DatatransEnable", m_bDatatransChangePort);
	ini.SetValueI("ChangePort", "DatatransIntervalTime", m_nDatatransChangePortIntervalTime);

    ini.SetValueI("redundancy", "redundancyRate", m_ncanredundancy);

	ini.SetValueB("VadMute", "Enable", m_bvadmute);
	ini.SetValueB("VirtualApp", "Enable", m_bVirtualApp);
	ini.SetValue("VirtualApp", "VirtualOCXIP", m_strVirtualOCXIP);
    ini.SetValueI("ACDAutoLoginTime", "time", m_nACDAutoLoginTime);

	//by hqh 2015.6.18 加锁
	bool bReturn = ini.WriteFile();
	if (mutexRW)
	{
		ReleaseMutex(mutexRW);
		CloseHandle(mutexRW);
	}

	return bReturn;
}

BOOL CEnvironment::LoadEnvironmentFromFile(LPCSTR szFileName)
{
	//by hqh 2015.6.18 加锁
	HANDLE mutexRW = CreateMutex(NULL, FALSE, TEXT("INFOBIRD_CLIENT_ENVFILE_MUTEX"));
	if (mutexRW)
		WaitForSingleObject(mutexRW, INFINITE);

	CIniFile ini(szFileName);
	if(!ini.ReadFile())
	{
		if (mutexRW)
		{
			ReleaseMutex(mutexRW);
			CloseHandle(mutexRW);
		}
		return FALSE;
	}

	//读取上一次保存的 最优中转服务器ip及Port
	m_sDataTransIP = ini.GetValue("DataTrans", "ServerIP","");
	m_iDataTransPort = ini.GetValueI("DataTrans", "ServerPort",0);
	
	//Login
	m_structCSTPort.bUseDefine = ini.GetValueB( "PortSettings", "UsePort" );
	m_structCSTPort.nMainPort = ini.GetValueI( "PortSettings", "AgentPort", 0);
	m_structCSTPort.nAssistantPort1 = ini.GetValueI( "PortSettings", "AudioPort1" );
	m_structCSTPort.nAssistantPort2 = ini.GetValueI( "PortSettings", "AudioPort2" );
	m_bUseTCPTransfer = ini.GetValueB("PortSettings","TCPTransfer");
	m_bDirectConnectToGateway = ini.GetValueB("PortSettings", "DirectConnectToGateway");
	m_bAlwaysTrans = ini.GetValueB("PortSettings", "DirectTransmit", TRUE);
	m_structCSTPort.iUseDefineIP = ini.GetValueI("LoginSettings", "define", 1);
	m_structCSTPort.szCustomizeIP = ini.GetValue("LoginSettings", "customizeip");
	m_structCSTPort.szCustomizeDomain = ini.GetValue("LoginSettings", "customizedomain");
	m_bIsLanAgent = ini.GetValueB("LoginSettings", "AgentType", FALSE);
	m_iLoginType = ini.GetValueI("LoginSettings", "LoginType", 0);
	m_bLoginSaveInfo = ini.GetValueB("LoginSettings", "LoginSaveInfo", TRUE);
	m_bLoginSavePsw = ini.GetValueB("LoginSettings", "LoginSavePsw", FALSE);
	m_strLoginUser = ini.GetValue("LoginSettings", "LoginUserName");
	m_strLoginPsw = ini.GetValue("LoginSettings", "LoginPassWord");
	m_strLoginCorp = ini.GetValue("LoginSettings", "LoginCorporat");
	m_bUseUserDefinedServer = ini.GetValueB("LoginSettings", "UseUserDefinedServer", FALSE);
	m_bUseUserDefinedWebPage = ini.GetValueB("LoginSettings", "UseUserDefinedWebPage", FALSE);
	m_bUseUserDefinedWebMain = ini.GetValueB("LoginSettings", "UseUserDefinedWebMain", FALSE);
	m_strWebLoginUrl = ini.GetValue("LoginSettings", "WebLoginFirstUrl");
	m_strFirstUrl = ini.GetValue("LoginSettings", "UserDefinedFirstUrl");
	m_strWebmainUrl = ini.GetValue("LoginSettings", "UserDefinedWebmainUrl");
	m_strLoginServerIP = ini.GetValue("LoginSettings", "UserDefinedLoginServerIP");

	m_structRecorderSet.nRecorderMode = ini.GetValueI("RecSettings", "RecOption" );
	m_structRecorderSet.szRecorderServerIP = ini.GetValue("RecSettings", "RecServerIP" );
	m_bRecordRespectively = ini.GetValueB("RecSettings", "RecordRespectively", FALSE);
	m_structRecorderSet.szRecordPath = ini.GetValue("RecSettings", "RecPath");

	m_nOutDialMode = ini.GetValueI("OutDialMode", "OutDialMode", 0 );
	m_sAgentPartNo = ini.GetValue("OutDialMode", "AgentPartNo", "");

	m_bUseAutoAreaNum = ini.GetValueB("OutDialMode", "UseAreaNo");
	m_sAreaNum = ini.GetValue("OutDialMode", "AreaNo");
	m_bOneKeyToPhone = ini.GetValueB("OutDialMode", "OneKeyToPhone");
	m_sOutPhoneNum = ini.GetValue("OutDialMode", "PhoneNo");
	m_bOutDialMobileAddZero = ini.GetValueB("OutDialMode", "OutdialMobileAddZero", FALSE);
	m_bAutoOffhook = ini.GetValueB("OutDialMode", "AutoOffhook", FALSE);
	m_bTransferWithCallNum = ini.GetValueB("OutDialMode", "TransferWithCallNum", FALSE);

	m_bUserAECERL = ini.GetValueB("Sound", "UserAecErl", TRUE);
	m_bMicBost = ini.GetValueB("Sound", "MicBost", FALSE);
	m_bPCSpeaker = ini.GetValueB("Sound", "PCSpeaker", FALSE);
	m_bMicBoost = ini.GetValueB("Sound", "MicBoost", FALSE );
	m_dwMainVolume = ini.GetValueI("Sound", "Volume", 65535*2/3 );
	m_dwMicphoneValue = ini.GetValueI("Sound", "Micphone", 65535);
	m_bEchoRemove = ini.GetValueB("Sound", "EchoRemove", FALSE );
	m_bMicAttenuation = ini.GetValueB("Sound", "MicAttenuation", TRUE);
	m_dDtmfVolume = ini.GetValueI("Sound", "DTMFVolume", 2000);
	m_bUseLocalVad = ini.GetValueB("Sound", "LocalUseVAD", TRUE);
	m_bUsingVADMode = ini.GetValueB("Sound", "UsingVADMode", TRUE);
	m_strCustomWebUrl = ini.GetValue("WebURL", "CustomWebUrl");

	m_bMicCtrl = ini.GetValueB("Sound", "MicCtrl", TRUE);
	m_bOpenWebpageNew = ini.GetValueB("WebURL", "OpenWebpageInNewTag", TRUE);
	m_iGUISupportIEVersion = ini.GetValueI("WebURL", "GUISupportIEVersion");
	m_bUseURLEncode = ini.GetValueB("WebURL", "UrlEncode", FALSE);
	//////////////////////////////////////////////////////////////////////////
	// + [9/12/2007 lixg]
	m_nAudioCapDev = ini.GetValueI("AudioDev", "AudioCapDev");	
	m_strAudioCapDevName = ini.GetValue("AudioDev", "AudioCapDevName", "");
	m_nAudioRenderDev = ini.GetValueI("AudioDev", "AudioRenderDev");
	m_strAudioRenderDevName = ini.GetValue("AudioDev", "AudioRenderDevName", "");
	//////////////////////////////////////////////////////////////////////////

	m_strOutDialHead1 = ini.GetValue("OutDialMode","OutDialHead1", "");
	m_strOutDialHead2 = ini.GetValue("OutDialMode","OutDialHead2", "");
	m_bTransferToIVR = ini.GetValueB("OutDialMode", "TransferToIVR", FALSE);
	m_bEncodeUUIData = ini.GetValueB("OutDialMode", "EncodeUUIData", TRUE);
	m_iOnHookDelay = ini.GetValueI("OutDialMode", "OnHookDelay");
	m_bOutDialMobileGetAreaCode = ini.GetValueB("OutDialMode", "OutDialMobileGetAreaCode", TRUE);
	m_sSmartOutDialHead = ini.GetValue("OutDialMode", "SmartOutDialHead");
	g_bMakelog = ini.GetValueB("Log", "MakeLog");
	
	m_sSMSServerIP = ini.GetValue("SMS", "SMSServerIP");
	m_bServiceRunDebug = ini.GetValueB("System", "RunningMode");
	m_iAutoReset = ini.GetValueI("System", "AutoReset");
	m_sLongXingKey = ini.GetValue("System", "LongXingKey");
	m_bIVRToAgentPrompt = ini.GetValueB("System", "IVRToAgentPrompt");
//	m_bCaptureInfo = ini.GetValueB("System", "CaptureInfo");

	m_bTCPSelfDefine = ini.GetValueB("System", "TCPSelfDefine");
	m_sTCPProxyIP = ini.GetValue("System", "TCPProxyIP");
	m_nTCPProxyPort = ini.GetValueI("System", "TCPProxyPort");
	// 2014-9-1 
	m_bDeliverClipBoard = ini.GetValueB("System","DeliverClipBoard",TRUE);

	//RTP Added	
	if (g_tagProductVerInfo.nVersionType & VerType_RTP)
	{
		m_fAgentVolume = ini.GetValueF("Volume", "AgentVolume", 2.0000);
		m_fClientVolume = ini.GetValueF("Volume", "ClientVolume", 1.5000);
		m_fCaptureZoom = ini.GetValueF("Volume", "CaptureZoom", 2.0000);
		m_fPlayZoom = ini.GetValueF("Volume", "PlayZoom", 2.0000);

		m_bUseSipPhone = ini.GetValueB("SipPhone", "UseSipPhone");
		m_sSipPhoneIP = ini.GetValue("SipPhone", "SipPhoneIP");
		m_iSipPhonePort = ini.GetValueI("SipPhone", "SipPhonePort");
		m_sSipPhoneRTPPort = ini.GetValue("SipPhone", "SipPhoneRTPPort");
		m_sSipPhoneRTCPPort = ini.GetValue("SipPhone", "SipPhoneRTCPPort");
	}
	else
	{
		m_fAgentVolume = ini.GetValueF("Volume", "AgentVolume", 1.0000);
		m_fClientVolume = ini.GetValueF("Volume", "ClientVolume", 1.0000);
		m_fCaptureZoom = ini.GetValueF("Volume", "CaptureZoom", 1.0000);
		m_fPlayZoom = ini.GetValueF("Volume", "PlayZoom", 1.0000);

		m_bUseSipPhone = ini.GetValueB("SipPhone", "UseSipPhone");
		m_sSipPhoneIP = ini.GetValue("SipPhone", "SipPhoneIP");
		m_iSipPhonePort = ini.GetValueI("SipPhone", "SipPhonePort");
	}
	
	m_uAgentOcxPort = ini.GetValueI("AgentOcxPort", "OcxPort", 57498);
	m_uServicePort = ini.GetValueI("AgentOcxPort", "ServicePort", 57499);

	// BeepSet
	m_nBeepIndex = ini.GetValueI("BeepSet", "Index", 0);
	m_nBeepFreq = ini.GetValueI("BeepSet", "Freq", 3800);
	m_nBeepDura = ini.GetValueI("BeepSet", "Dura", 120);

	// LocalAdmin
	m_strUser = ini.GetValue("LocalAdmin", "User", "");
	m_strPwd = ini.GetValue("LocalAdmin", "Pwd", "");
	
	// 是否支持合并ACD和UserState版本
	m_bAcdAndUserState = ini.GetValueB("AcdAndUserState", "Enable", FALSE);	// [scq/2010-07-26]

	//是否支持通话中发送心跳，默认不支持
	m_bSendHeartPack=ini.GetValueB("SendHeartPack", "Enable", FALSE);	// [zb/2013-02-28]
	//动态换端口
	m_bChangePort=ini.GetValueB("ChangePort", "Enable", FALSE);	// [zb/2013-05-10]; 
  	m_nChangePortIntervalTime=ini.GetValueI("ChangePort", "IntervalTime", 300); // [zb/2013-05-10]; 
	m_bDatatransChangePort=ini.GetValueB("ChangePort", "DatatransEnable", FALSE);	// [zb/2013-08-22]; 
  	m_nDatatransChangePortIntervalTime=ini.GetValueI("ChangePort", "DatatransIntervalTime", 300); // [zb/2013-08-22]; 
    m_ncanredundancy=ini.GetValueI("redundancy", "redundancyRate", 1);
	m_bvadmute=ini.GetValueB("VadMute", "Enable", FALSE);
	m_bVirtualApp=ini.GetValueB("VirtualApp", "Enable", FALSE);
	m_strVirtualOCXIP= ini.GetValue("VirtualApp", "VirtualOCXIP");
	m_nACDAutoLoginTime=ini.GetValueI("ACDAutoLoginTime", "time", 60);
	ini.Clear();

	//by hqh 2015.6.18 加锁
	if (mutexRW)
	{
		ReleaseMutex(mutexRW);
		CloseHandle(mutexRW);
	}

	return TRUE;
}