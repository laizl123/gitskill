// Environment.h: interface for the CEnvironment class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENVIRONMENT_H__7E58F607_6B91_4ED2_9B93_ED657FC4E126__INCLUDED_)
#define AFX_ENVIRONMENT_H__7E58F607_6B91_4ED2_9B93_ED657FC4E126__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "iniFile.h"
#include <string>
#include "WinDef.h"	// Added by ClassView
using namespace std;

//hqh 2016.1.12 
#ifdef _ALIAN
#define DEFURL "http://alyw.infobird.com/jump"
#define DEFUPDATEURL "alsj.infobird.com"
#else
#define DEFURL "http://qitongbao-al.infobird.com/jump"
#define DEFUPDATEURL "update.infobird.com"
#endif

typedef enum __enmuOUTDIALTYPE
{
	dialError			 = -1,
	dialDefault			 = 0,
	dialDeparment		 = 1,
	dialAgent			 = 2,
	dialOtherDeparment,
	dialOtherAgent,
	dialPSTN,
	dialExtNo,
} OutDialType;

enum __enumRECORDERMODE
{
	recorderError			 = -1,
	noRecorder				 = 0,
	needRecorderAndSaveLocal = 1,
	needRecorderAndSaveServer= 2,
};

typedef struct tagCUSTOMIZEPORT 
{
	BOOL bUseDefine;			//是否使用自定义服务器设置
	UINT nMainPort;				//主通讯端口，命令信息端口
	UINT nAssistantPort1;		//辅助通讯端口1，主语音端口
	UINT nAssistantPort2;		//辅助通讯端口1，转移时用的语音端口
	int iUseDefineIP;			//自定义服务器方式
	string szCustomizeIP;		//自定义服务器IP
	string szCustomizeDomain;	//自定义服务器域名
} CustomizePort, *lpCustomizePort;

typedef struct tagRECORDERSET 
{
	int nRecorderMode;
	string szRecorderServerIP;
	string szRecordPath;

	tagRECORDERSET()
	{
		nRecorderMode = 1;
		szRecorderServerIP = "";
		szRecordPath = "";
	}
}RecorderSet,*lpRecorderSet;


class CEnvironment  
{
public:
	CEnvironment();
	virtual ~CEnvironment();
	
public:
	string m_sDataTransIP;		// 语音中转IP
	int    m_iDataTransPort;	// 语音中转port
	CustomizePort m_structCSTPort;
	RecorderSet m_structRecorderSet;
	int m_nOutDialMode;
	int m_iAecErl;
	BOOL m_bUseTCPTransfer;	///TCP中转
	BOOL m_bUserAECERL;		///回声消除
	BOOL m_bIsLanAgent;		///内网座席
	string m_sAgentPartNo;	///区号
	BOOL m_bMicBost;
	BOOL m_bMicCtrl;
	BOOL m_bPCSpeaker;
	BOOL m_bDirectConnectToGateway;  //是否客户端直接连接网关
	BOOL m_bUseAutoAreaNum;
	string m_sAreaNum;
	BOOL m_bOneKeyToPhone;
	string m_sOutPhoneNum;
	BOOL m_bOutDialMobileAddZero;
	int m_iLoginType;
	BOOL m_bMicBoost;
	DWORD m_dwMainVolume;
	DWORD m_dwMicphoneValue;
	BOOL m_bEchoRemove;
	BOOL m_bAutoOffhook;   //自动摘机
	BOOL m_bMicAttenuation;  //音量减弱
	BOOL m_bAlwaysTrans;
	DWORD m_dDtmfVolume;
	BOOL m_bUseLocalVad;
	//////////////////////////////////////////////////////////////////////////
	// + [9/12/2007 lixg]
	int m_nAudioCapDev;		
	string m_strAudioCapDevName;	
	int m_nAudioRenderDev;
	string m_strAudioRenderDevName;
	string m_strOutDialHead1;
	string m_strOutDialHead2;
	BOOL m_bTransferToIVR;
	//////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////
	//by dido 09/01/05
	BOOL m_bUseSipPhone;
	string m_sSipPhoneIP;
	int m_iSipPhonePort;
	string m_sSipPhoneRTPPort;
	string m_sSipPhoneRTCPPort;
	////////////////////////////////////////////////////////////////////////////	
	//by dido 09/04/16
	float m_fAgentVolume;
	float m_fClientVolume;
	BOOL m_bUsingVADMode;  //是否开启VAD模式
	
	int m_iGUISupportIEVersion;  //IE版本取值：0(自动匹配), 1(IE11), 2(IE11标准), 3(IE10), 4(IE10标准), 5(IE9), 6(IE9标准), 7(IE8), 8(IE8标准), 9(IE7标准), (10)chrome版本；
	string m_sLongXingKey;
	string m_sSmartOutDialHead;
	BOOL m_bOutDialMobileGetAreaCode;
	int m_iAutoReset;
	int m_iOnHookDelay;
	BOOL m_bRecordRespectively;
	BOOL m_bEncodeUUIData;
	BOOL m_bServiceRunDebug;
	string m_strCustomWebUrl;  //用户自定义额外弹屏页面
	BOOL m_bTransferWithCallNum;
	string m_sSMSServerIP;
	BOOL m_bOpenWebpageNew;
	BOOL m_bLoginSavePsw;
	BOOL m_bLoginSaveInfo;
	string m_strLoginCorp;
	string m_strLoginUser;
	string m_strLoginPsw;

	static CEnvironment& Instance();
	BOOL SaveEnvironmentToFile(LPCSTR szFileName = "Config.ini");
	BOOL LoadEnvironmentFromFile(LPCSTR szFileName = "Config.ini");

	float m_fCaptureZoom;
	float m_fPlayZoom;
	// 服务器端口
	UINT m_uAgentOcxPort;   //OCX
	UINT m_uServicePort;	
	// 蜂鸣音
	int m_nBeepIndex;
	int m_nBeepFreq;
	int m_nBeepDura;
	// 本地具有标准权限以上的用户名和密码
	string m_strUser;
	string m_strPwd;
	//指定登陆ip和业务系统域地址
	string	m_strWebLoginUrl;
	string	m_strFirstUrl;
	string	m_strWebmainUrl;
	string	m_strLoginServerIP;
	BOOL	m_bUseUserDefinedServer;
	BOOL	m_bUseUserDefinedWebPage;
	BOOL	m_bUseUserDefinedWebMain;

	BOOL m_bUseURLEncode; //hqh 弹屏url编码2016.11.16
	BOOL m_bAcdAndUserState;	// 是否支持合并ACD和UserState版本[scq/2010-07-27]
	BOOL m_bCaptureInfo;	//是否采集客户端网络信息20121122
	BOOL m_bIVRToAgentPrompt;
	BOOL m_bSendHeartPack;
    BOOL m_bChangePort; //是否开启换端口功能，默认不开启
  	int	 m_nChangePortIntervalTime; //换端口间隔时间，默认5分钟
	BOOL m_bDatatransChangePort; //是否开启Datatrans换端口功能,向Datatrans重新申请语音端口，默认不开启
  	int	 m_nDatatransChangePortIntervalTime; //换Datatrans端口间隔时间，默认5分钟
    int  m_ncanredundancy; //语音包冗余深度 0表示没有冗余，1表示有一个冗余包(默认)
    BOOL m_bvadmute; //是否开启VAD静音2秒后数据包才丢弃
	BOOL m_bInboundPlayAgentID;
	BOOL m_bOutboundPlayAgentID;

	BOOL m_bTCPSelfDefine;
	string m_sTCPProxyIP;
	DWORD m_nTCPProxyPort;
	BOOL m_bVirtualApp;
	string	m_strVirtualOCXIP;
	int  m_nACDAutoLoginTime;//ACD重启后，需要比较长时间加载ACD,时间配置
	// 2014-9-1 add by syb
	BOOL m_bDeliverClipBoard;
};

#endif // !defined(AFX_ENVIRONMENT_H__7E58F607_6B91_4ED2_9B93_ED657FC4E126__INCLUDED_)
