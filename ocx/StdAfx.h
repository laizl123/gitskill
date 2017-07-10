#ifndef AFX_STDAFX_H__CA445DC7_49FC_46A6_BF79_29DB15AC0D84__INCLUDED_
#define AFX_STDAFX_H__CA445DC7_49FC_46A6_BF79_29DB15AC0D84__INCLUDED_



#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define _CRT_SECURE_NO_WARNINGS
#define NO_WARN_MBCS_MFC_DEPRECATION
// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#define _WIN32_WINNT  0x0501
#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers
#define _WIN32_DCOM 
#include <afxctl.h>         // MFC support for ActiveX Controls
#include <afxext.h>         // MFC extensions
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

// Delete the two includes below if you do not wish to use the MFC
//  database classes

#include <string>
using namespace std;
#pragma warning(disable:4786)

#include "AgentPanelOcxHead.h"
#include "AgentPanelOcxGlobal.h"
#include "resource.h"
#include "IPCCMessage.h"

#define WM_MY_GET_GROUPINFO WM_USER+900
#define WM_MY_GET_FULLFREEAGENTINFO WM_USER+901
#define WM_MY_GET_ONEGROUPFREEAGENTINFO WM_USER+902
#define WM_MY_GET_TALKINGAGENTINFO WM_USER+903
#define WM_ENTER_SEND_CHAT WM_USER+998
#define WM_INIT_DTMF WM_USER+997
#define WM_MY_MONIT_RETRY WM_USER+999
#define WM_MY_UPDATE_ALLSETTINGS WM_USER+1000
#define WM_GO_URL	0
#define WM_SEND		1
const int CREDITUDP_BUFFER_SIZE = 800;
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

#define OPTION_CRYPT
#ifdef OPTION_CRYPT
static bool g_bCryptCudp = true;
static unsigned char g_CudpCryptKey[] = {35,10,106,188,99,201,246,4,13,135,204,143,126,60,216,49,141,115,69,242,110,160,136,6,215,180,161,0,98,239,157,66,51,245,96,184,218,37,161,198,122,38,54,126,43,194,146,23,158,248,140,154,0,76,98,223,32,98,253,184,211,203,118,108,152,31,218,103,120,76,42,47,48,45,166,154,146,95,75,63,41,80,155,42,28,152,156,212,84,141,35,82,225,17,82,204,154,175,96,49,4,231,152,41,118,197,165,75,122,185,12,145,117,162,250,8,139,44,64,204,189,92,156,52,84,105,58,74,131,206,122,126,72,157,244,155,147,22,186,249,170,120,220,245,204,23,50,158,20,175,85,177,161,248,239,200,244,122,53,206,153,163,177,182,10,23,69,108,208,71,109,12,235,69,196,83,116,215,202,83,129,202,228,106,73,136,164,116,137,237,75,64,38,87,140,65,19,252,147,134,117,129,70,236,5,200,203,147,182,9,74,142,153,36,244,223,253,53,68,162,218,105,132,136,112,17,148,135,43,245,231,208,202,235,206,2,192,168,249,157,218,213,58,185,35,102,141,248,5,39,86,185,176,151,233,142};
static bool g_bCryptAudio = false;
static unsigned char g_AudioCryptKey[] = {60,36,4,12,170,155,149,178,237,120,84,182,89,9,98,138,45,225,26,231,201,53,232,89,27,134,94,253,91,128,132,137,248,35,112,142,210,32,23,250,169,134,99,225,213,157,134,125,56,18,141,115,114,85,56,87,83,64,9,115,150,249,155,196,204,25,53,70,150,14,159,114,23,190,52,4,169,108,57,1,207,224,109,249,108,194,225,137,50,72,10,37,92,17,21,20,160,80,122,188,95,44,212,32,32,103,240,167,60,62,36,31,218,145,226,1,30,68,140,247,158,229,138,155,22,143,155,130,92,14,104,121,150,67,95,14,170,202,190,83,246,219,238,222,66,110,19,20,242,163,225,168,128,96,177,94,42,60,212,21,232,156,39,4,161,27,231,68,158,48,199,142,63,11,64,71,237,191,41,185,79,166,135,164,193,1,166,245,2,224,105,213,44,66,222,229,234,124,21,200,229,223,51,227,127,149,194,96,196,204,75,121,157,23,39,243,71,16,146,232,4,67,1,202,17,71,182,165,215,46,145,164,101,32,41,215,30,66,27,51,175,220,162,219,69,188,104,158,252,213,156,192,154,44,69,253};
#endif

#define DEFAULT_AECERL 50

#include <afxsock.h>


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__CA445DC7_49FC_46A6_BF79_29DB15AC0D84__INCLUDED_)
