// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__71309824_847B_4C60_8E02_3B31F5B5D4A1__INCLUDED_)
#define AFX_STDAFX_H__71309824_847B_4C60_8E02_3B31F5B5D4A1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define    _WIN32_WINNT  0x0500
#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers
#define _WIN32_DCOM 
#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT
#include <afxhtml.h>			// MFC HTML view support
#include <transact.h>
#pragma warning(disable:4786)

#include <Afxctl.h>

#define _ATL_APARTMENT_THREADED
#include <atlbase.h>
extern CComModule _Module;
#include <atlcom.h>
#include <afxsock.h>
#include <Nb30.h>
#include "GlobalOperation.h"
#include "ConsoleMessageDef.h"
#include <mshtml.h>
#include <Mshtmdid.h>

#define WM_MY_ADD_FAVORITE_URL WM_USER + 500
#define WM_MY_IETOOLBAR_SET_URL WM_USER + 501
#define WM_MY_SEND_CHAT WM_USER + 655
#define WM_BTNST_MY_MODIFY WM_USER + 650
#define WM_BTNST_MY_DELETE WM_USER + 651
#define WM_MY_CLEAR_CONSULTATION_TRANSFER_STATUS WM_USER + 664
#define WM_MY_IE_TAB_NOTIFY WM_USER + 665
#define WM_WEB_MONIT WM_USER + 666
#define WM_WEB_STOP_MONIT WM_USER + 667
#define WM_WEB_TEXT_NOTIFY WM_USER + 668
#define WM_MY_OUTDIALOPENURL WM_USER +669
#define WM_WEB_TWICECHECK WM_USER + 670
#define WM_WEB_TRANSFERTOIVR WM_USER + 671
#define WM_WEB_TRANSFERTOIVR_EX WM_USER + 672
#define WM_WEB_OPENURLWITHDEFAULTBROSWER WM_USER + 673
#define WM_WEB_QUERYALLTALKINGAGENTSINFO WM_USER + 674
#define WM_WEB_QUERYALLFREEAGENTSINFO WM_USER + 675
#define WM_WEB_ACTION WM_USER + 676
#define WM_MY_VOLUME_UPDATESETTINGS WM_USER + 677
#define WM_WEB_LOGIN WM_USER + 678
#define WM_WEB_LOGIN_SECURITY WM_USER + 679
#define WM_WEB_STARTCONFERENCE  WM_USER + 680
#define WM_WEB_STOPCONFERENCE  WM_USER + 681
#define WM_WEB_PAYCONFERENCE  WM_USER + 682
#define WM_DELNEWSETDLG		  WM_USER + 683	

#define COMPANY_HISTORY_COUNT 5
#define LOGINNAME_HISTORY_COUNT 10
#define PHONENUM_HISTORY_COUNT 10

enum ENUM_EXT_STYLE {ES_NULL, ES_MODIFY, ES_DELETE, ES_MODI_DEL};
enum {VerType_QITONGBAO = 0x0001, VerType_IPCC = 0x0002, VerType_RTP = 0x0004};   //准备使用位运算来进行版本组合
typedef struct ProductVersionInfo
{
	UINT nVersionType;
	CString strVersionNum;
	ProductVersionInfo::ProductVersionInfo()
	{
		nVersionType = VerType_QITONGBAO;
		strVersionNum = "";
	}
}PRODUCT_VER_INFO;

typedef struct tagSettings
{
	bool bUseUserDefinedServer;
	bool bUseUserDefinedWebPage;
	char cLoginServerIP[20];
	char cFirstUrl[MAX_PATH];
	tagSettings()
	{
		bUseUserDefinedServer = false;
		bUseUserDefinedWebPage = false;
		memset(cLoginServerIP, 0, sizeof(char)*20);
		memset(cFirstUrl, 0, sizeof(char)*MAX_PATH);
	}
}MY_SETTINGS;


UINT _MyMsgBox(CString strTitle, CString strContent, UINT nType);

typedef struct __IPCCNetInfo
{
//	long			callID;
	string			m_ip_Local;
	
	///用户登陆服务器
	unsigned long	m_ip_LoginServer;
	unsigned short	m_port_LoginServer;
	///用户呼叫引导服务器
	unsigned long	m_ip_GuideServer;
	unsigned short	m_port_GuideServer;
	///排队服务器
	unsigned long	m_ip_ACDServer;
	unsigned short	m_port_ACDServer;
	///P2P协作服务器
	unsigned long	m_ip_RelayServer;
	unsigned short	m_port_RelayServer;
	
	///测试NAT类型服务器1
	unsigned long	m_ip_CheckNatServer1;
	///测试NAT类型服务器2
	unsigned long	m_ip_CheckNatServer2;

	unsigned short	m_port_CheckNatServerA;
	unsigned short	m_port_CheckNatServerB;

	unsigned long m_ip_TransmitServer;
	unsigned short m_port_TransmitServer;
	
	unsigned long m_ip_UserStateServer;
	unsigned short m_port_UserStateServer;

	unsigned long m_ip_RecordServer;
	unsigned short m_port_RecordServer;
	unsigned long m_ip_AudioRecorder;
	unsigned short m_port_AudioRecorder;

	unsigned long m_ip_RouteServer;
	unsigned short m_port_RouteServer;
	
	unsigned long m_ip_GwMgrServer;
	unsigned short m_port_GwMgrServer;
	
	unsigned long m_ip_TextChatServer;
	unsigned short m_port_TextChatServer;
	
	unsigned long m_ip_DelayStrategyServer;
	unsigned short m_port_DelayStrategyServer;
	
	unsigned long m_ip_TollQueryServer;
	unsigned short m_port_TollQueryServer;
	
	unsigned long m_ip_DataCenterServer;
	unsigned long m_ip_DataRouteServer;
	///本地
	int	m_port_NetLocal;
//	int m_port_LocalText;
//	int	m_port_LocalVideo;
//	int	m_port_LocalAudio;


//	unsigned long	m_ip_UserMain;		///用户主 sock
//	unsigned short	m_port_UserMain;
//	
//	unsigned long	m_ip_AgentMain;		///座席主 sock
//	unsigned short	m_port_AgentMain;	
//
//	unsigned long	m_ip_UserText;		//用户文本
//	unsigned short	m_port_UserText;	
//
//	unsigned long	m_ip_AgentText;		//座席文本
//	unsigned short	m_port_AgentText;	
//	
//	unsigned long	m_ip_UserVideo;		///用户视频
//	unsigned short	m_port_UserVideo;
//	
//	unsigned long	m_ip_UserAudio;		///用户音频
//	unsigned short	m_port_UserAudio;
//	
//	unsigned long	m_ip_AgentVideo;	///Agent视频
//	unsigned short	m_port_AgentVideo;
//	
//	unsigned long	m_ip_AgentAudio;	///Agent音频
//	unsigned short	m_port_AgentAudio;

//	unsigned long	m_ip_RemoteText;	///对方文本
//	unsigned short	m_port_RemoteText;
//
//	unsigned long	m_ip_RemoteAudio;	///对方音频
//	unsigned short	m_port_RemoteAudio;
//
//	unsigned long	m_ip_RemoteVideo;	///对方视频
//	unsigned short	m_port_RemoteVideo;
	
//	unsigned long	m_ip_RemoteFile;	//对方文件
//	unsigned short	m_port_RemoteFile;
	
//	CString			m_ip_sProxyServer;	///代理服务器
//	int				m_port_ProxyServer;
//	///代理服务器协商以后使用的端口
//	unsigned short	m_port_ProxyServer_Main;
//	unsigned short	m_port_ProxyServer_Audio;
//	unsigned short	m_port_ProxyServer_Video;
	
	char loginKey[32];
	
//	unsigned long m_ip_AgentFile;
//	unsigned short m_port_AgentFile;
//
//	unsigned long m_ip_UserFile;
//	unsigned short m_port_UserFile;

//	int	m_port_LocalFile;
	int m_iNatType;
	
	string m_sCallerNoForSend;
	string m_sNickName;
}IPCCNetInfo;

struct PortConfig
{
	bool UseCustomPort;
	unsigned short AgentPort;
	unsigned short AudioPort1;
	unsigned short AudioPort2;
};

#define OPTION_CRYPT
#ifdef OPTION_CRYPT
static bool g_bCryptCudp = true;
static unsigned char g_CudpCryptKey[] = {35,10,106,188,99,201,246,4,13,135,204,143,126,60,216,49,141,115,69,242,110,160,136,6,215,180,161,0,98,239,157,66,51,245,96,184,218,37,161,198,122,38,54,126,43,194,146,23,158,248,140,154,0,76,98,223,32,98,253,184,211,203,118,108,152,31,218,103,120,76,42,47,48,45,166,154,146,95,75,63,41,80,155,42,28,152,156,212,84,141,35,82,225,17,82,204,154,175,96,49,4,231,152,41,118,197,165,75,122,185,12,145,117,162,250,8,139,44,64,204,189,92,156,52,84,105,58,74,131,206,122,126,72,157,244,155,147,22,186,249,170,120,220,245,204,23,50,158,20,175,85,177,161,248,239,200,244,122,53,206,153,163,177,182,10,23,69,108,208,71,109,12,235,69,196,83,116,215,202,83,129,202,228,106,73,136,164,116,137,237,75,64,38,87,140,65,19,252,147,134,117,129,70,236,5,200,203,147,182,9,74,142,153,36,244,223,253,53,68,162,218,105,132,136,112,17,148,135,43,245,231,208,202,235,206,2,192,168,249,157,218,213,58,185,35,102,141,248,5,39,86,185,176,151,233,142};
static bool g_bCryptAudio = false;
static unsigned char g_AudioCryptKey[] = {60,36,4,12,170,155,149,178,237,120,84,182,89,9,98,138,45,225,26,231,201,53,232,89,27,134,94,253,91,128,132,137,248,35,112,142,210,32,23,250,169,134,99,225,213,157,134,125,56,18,141,115,114,85,56,87,83,64,9,115,150,249,155,196,204,25,53,70,150,14,159,114,23,190,52,4,169,108,57,1,207,224,109,249,108,194,225,137,50,72,10,37,92,17,21,20,160,80,122,188,95,44,212,32,32,103,240,167,60,62,36,31,218,145,226,1,30,68,140,247,158,229,138,155,22,143,155,130,92,14,104,121,150,67,95,14,170,202,190,83,246,219,238,222,66,110,19,20,242,163,225,168,128,96,177,94,42,60,212,21,232,156,39,4,161,27,231,68,158,48,199,142,63,11,64,71,237,191,41,185,79,166,135,164,193,1,166,245,2,224,105,213,44,66,222,229,234,124,21,200,229,223,51,227,127,149,194,96,196,204,75,121,157,23,39,243,71,16,146,232,4,67,1,202,17,71,182,165,215,46,145,164,101,32,41,215,30,66,27,51,175,220,162,219,69,188,104,158,252,213,156,192,154,44,69,253};
#endif

CString GetMoudlePath();
CString GetDataFilesPath();


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__71309824_847B_4C60_8E02_3B31F5B5D4A1__INCLUDED_)
