
#include <sstream>
#ifndef __ICSERVING_MSG__
#define __ICSERVING_MSG__

#define WM_LOGIN_MSG			WM_USER+201
#define WM_START_CHECK_NAT		WM_USER+202

#define WM_PREOUTDIAL_END		WM_USER+203
#define WM_BACKPROCESS_NOTIFY	WM_USER+204

#define WM_DISPOSECLIENT_TEXT	WM_USER+710
#define WM_DISPOSECLIENT_STATUS WM_USER+711
#define WM_ICONNOTIFY			WM_USER+712
#define WM_DISPOSE_QUEUECOUNT	WM_USER+713
#define WM_ECHOREMOVE			WM_USER+714

#define WM_INCOME_CALL			WM_USER+722   ///座席弹屏消息
#define WM_REFRESH_TALKTIME		WM_USER+723


#define WM_SMS_SENDSUCCES		WM_USER+730
#define WM_SMS_SENDFAILED		WM_USER+731
#define WM_SMS_SENDTIMEOUT		WM_USER+732
#define WM_SMS_SENDFAILEDNUM	WM_USER+733

#define REFRESH_TALKTIME_NCPAINT 0x0cc01
#define REFRESH_TALKTIME_NOPAINT 0x0cc02

#define WM_CALL_MSG				WM_USER+731

#define WM_UNPROCESS_OUTDIAL	WM_USER+732
///外拨时获取空闲座席或者部门
#define WM_CALL_GET_TARGER		WM_USER+740

#define WM_STOPMEDIADATA		WM_USER+980
#define WM_DEACTIVEVIDEO		WM_USER+981
#define WM_ACTIVEVIDEO			WM_USER+982
#define WM_STARTSENDDATA		WM_USER+983
#define WM_PAUSE_MEDIA			WM_USER+984
#define WM_RESUME_MEDIA			WM_USER+985
#define WM_MEDIA_RESET			WM_USER+986
#define WM_STOP_MEDIA_THREAD	WM_USER+987


#define WM_REFRESH_WINDOW		WM_USER+1021

#define WM_START_PLAYSOUND		WM_USER+1031
#define WM_STOP_PLAYSOUND		WM_USER+1032

#define WM_LOGIN_FAILE			WM_USER+1201

#define WebPSTN_Login_Faile		0x02
#define WM_LOGIN_SUCC			WM_USER+1202
#define WM_PROCESSCTRL_POS		WM_USER+1203

 
#define WM_CHECK_VERSION		WM_USER+1204
#define WM_DOWN_UPDATE			WM_USER+1205


#define WM_WEB_REDIRECT			WM_USER+1210
#define WEB_REDIRECT_AGENT_LOGIN 0x01
#define WEB_REDIRECT_CALL_IN	 0x02

#define LOGIN_FAILE_MSG_NET		0x01
#define LOGIN_FAILE_MSG_INPUT	0x02
#define LOGIN_FAILE_MSG_NoAct	0x03
#define LOGIN_WEBPSTN_FAILE		0x04

//#define WM_FILE_CONNECTED		WM_USER+3044
//#define WM_SHOW_FILEDLG			WM_USER+3045

#define WM_MEDIANEGOTIATE_SUCC	WM_USER+4001
//#define WM_MEDIAREADY			WM_USER+4002
#define WM_TRY_CONNECT_COUNT	WM_USER+4003

#define WM_SETMEDIAHEAD			WM_USER+5001
#define WM_ENABLE_BTN			WM_USER+5002

#define WM_START_REC			WM_USER+6001
#define WM_STOP_REC				WM_USER+6002

#define WM_ALWAYSONTOP			WM_USER+6010

#define WM_WEBCALL				WM_USER+6011
#define WM_ACD_AgentLoginSucc_OCX	WM_USER + 7000	// + [7/6/2007 lixg]
#define WM_ACD_AgentLogoutConf_OCX	WM_USER + 7001	// + [7/6/2007 lixg]
#define WM_ACD_AgentMakeCallConf_OCX	WM_USER + 7002	// + [7/11/2007 lixg]
#define WM_ClientStateChanged_OCX	WM_USER + 7003	// + [7/12/2007 lixg]
#define WM_ACD_CallDelivered_OCX	WM_USER + 7004	// + [7/13/2007 lixg]
#define WM_TextChatMsg_OCX			WM_USER + 7005	// + [8/8/2007 lixg]
#define WM_ACD_AgentLoginFailed_OCX	WM_USER + 7006	// + [8/8/2007 lixg]
#define WM_ACD_DepartNAgentInfo_OCX	WM_USER + 7007	// + [8/8/2007 lixg]
#define WM_ACD_TalkingAgentInfo_OCX WM_USER + 7008  //by dido  08/07/14

#define WM_AudDevSwiPag_GetUsbPhoneVolumes	WM_USER + 7100	// + [9/18/2007 lixg]
#define WM_MainFrame_UsbPhoneVolumes		WM_USER + 7101	// + [9/18/2007 lixg]
#define WM_AudDevSwiPag_SET_INPUT_VOLUME	WM_USER + 7102	// + [9/18/2007 lixg] 
#define WM_AudDevSwiPag_SET_OUTPUT_VOLUME	WM_USER + 7103	// + [9/18/2007 lixg]
#define WM_AudDevSwiPag_GetUsbPhoneOpenedState	WM_USER + 7104	// + [9/18/2007 lixg]
#define WM_MainFrame_UsbPhoneOpenedState	WM_USER + 7105	// + [9/18/2007 lixg]

#define AGENT_STATE_COUNT	150
#define USER_STATE_COUNT	100
#define IPCC_MSG_COUNT		1000


enum __soundtype{
	sound_RING= 0,
	sound_DIAL,
	sound_Queuing,
	sound_Stop,
	sound_User_Hangup,	
};

/*
enum __callTargerType{
	Type_unknow = -1,
	Type_user =0,
	Type_agent,
	Type_group,
	Type_Other_agent,
	Type_Other_group,
	Type_pstn,
};
*/
enum RoleAdminState
{
	RoleAdminState_None,
	RoleAdminState_NoActive,
	RoleAdminState_Run,
	RoleAdminState_Pause,
	RoleAdminState_Stop,
};


#define WEB2TXTCHATinterval 10
#define PHONENUM_REGEX_NUM	17
#define PHONENUM_REGEX_SIZE 255
const char phonenum_regex[PHONENUM_REGEX_NUM][PHONENUM_REGEX_SIZE] =
{
	"^[0][1-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9]",				//01087654321,01117654321,区号3位号码8位,区号4位号码7位
	"^[1][3][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9]",					//手机 
	"^[0][1][3][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9]",				//手机 
	"^[0][2-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9]",			///区号4位号码8位
	"^[0][1-9][0-9][-][1-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9]",			//010-87654321
	"^[0][1-9][0-9][0-9][-][1-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9]",		//0111-76543210
	"^\\+[8][6][1-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9]",			//+861086627890
	"^\\+[8][6][-][1-9][0-9][-][1-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9]",	//+86-10-86627890
	"^[8][6][-][1-9][0-9][-][1-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9]",		//86-10-86627890
	"^[8][6][1-9][0-9][-][1-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9]",			//8610-86627890
	"^\\+[8][6][-][1-9][0-9][0-9][-][1-9][0-9][0-9][0-9][0-9][0-9][0-9]",	//+86-428-6627890
	"^[8][6][-][1-9][0-9][0-9][-][1-9][0-9][0-9][0-9][0-9][0-9][0-9]",		//86-428-6627890
	"^[8][6][-][1-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9]",			//86-4286627890
	"^[8][6][1-9][0-9][0-9][-][1-9][0-9][0-9][0-9][0-9][0-9][0-9]",			//86428-6627890


	"^[8][0][0][-][0-9][0-9][0-9][-][0-9][0-9][0-9][0-9]",					//800-858-2339
	"^[8][0][0][0-9][0-9][0-9][0-9][0-9][0-9][0-9]",						//8008582339
	"^[9][0-9][0-9][0-9][0-9]",												//95585
};

#include <string>
using namespace std;

#define CALLMESSAGE_COPYDATA_MSG  0x0100
typedef struct __CallMessage {
	int iCallType;
	char sCallTarger[256];
} CallMessage;

#define FREEAGENTLIST_COPYDATA_MSG 0x0101
typedef struct __FreeAgentList{
	BOOL bEnd;
	string sDepartment;
	string sFreeAgent;
} FreeAgentList;

#define TEXTCHAT_COPYDATA_MSG 0x0102
typedef struct __TextChatStruct {
	string sTalker;
	string sChatWord;
	BOOL bIsCallInfo;
}TextChatStruct;

#define GETPHONENUM_COPYDATA_MSG 0x0103
typedef struct __GetPhoneNumStruct {
	string sPhoneNum;
} GetPhoneNumStruct;

#define INCOMECALL_COPYDATA_MSG 0x0104
typedef struct __InComeCallStruct {
	string sWebUrl;
	string sCallID;
	string sUUIData;
	string sKeyword;
	string sUser;
} InComeCallStruct;

#define SMSLINKMAN_COPYDATA_MSG 0x0105
typedef struct __SMSLinkManStruct {
	string sLinkManID;
	string sLinkManName;
	string sPhoneNum;
	string sDescription;
} SMSLinkManStruct, *lpSMSLinkManStruct;

#define SMSSENDCONF_COPYDATA_MSG 0x0106
typedef struct __SMSSendConfStruct {
	bool   bSucc;
	string sPhoneNum;
} SMSSendConf, *lpSMSSendConf;

#define NEW_EXPLORER_WINDOW_COPYDATA_MSG 0x0107
//##ModelId=4610717F008C
typedef struct __NewExplorerWindowStruct {
	void* ppDisp;
	string sUrl;
} NewExplorerWindowStruct, *lpNewExplorerWindowStruct;

#define CLOSING_EXPLORER_WINDOW_COPYDATA_MSG 0x0108
typedef struct __ClosingExplorerWindowStruct {
	void* pView;
} ClosingExplorerWindowStruct, *lpClosingExplorerWindowStruct;

struct AgentURLStruct
{
	string agentURL;
	string loginName;
	string loginPwd;
	int haveVerifyCode;
	string remark1;
	string remark2;
	string remark3;
	string urlSign;
};

#define AGENT_PREOPEN_URL_COPYDATE_MSG 0x0109
typedef struct __AgentPreOpenURLStruct{
	AgentURLStruct* pAgentURL;
} AgentPreOpenURLStruct, *lpAgentPreOpenURLStruct;

#define TALKAGENTLIST_COPYDATA_MSG 0x010A
typedef struct __TalkAgentList{
//	BOOL bEnd;
//	string sDepartment;
	string sTalkAgent;
} TalkAgentList;

#define MONITMESSAGE_COPYDATA_MSG  0x010B
typedef struct __MonitMessage {
	string sAgent;
	unsigned long iIp;
	unsigned short iPort;
} MonitMessage;

#define WEBCALL_COPYDATA_MSG 0x010C
typedef struct __WebCallStruct {
	string sPhoneNo;
} WebCallStruct, *lpWebCallStruct;

struct SystemValue
{
	string AgentID;
	string Group;
	string CallerID;
	string CalleeID;
	string PrivateData;
	int CallType;	//-1未知,0网关呼入,1呼叫PSTN,2客户呼入,3座席呼坐席
	string CallID;

	SystemValue()
	{
		AgentID = "";
		Group = "";
		CallerID = "";
		CalleeID = "";
		PrivateData = "";
		CallType = -1;
		CallID = "";
	};

	void ReSet(bool bResetGroup = true)
	{
		CallerID = "";
		CalleeID = "";
		PrivateData = "";
		CallType = -1;
		if ( bResetGroup )
			Group = "";
		CallID = "";
	}

	void FromString(string sValue)
	{
		int iPosBegin = 0;
		int iPosEnd = sValue.find( "%^#", iPosBegin );
		if ( iPosEnd != string::npos )
		{
			CallerID = sValue.substr( iPosBegin, iPosEnd - iPosBegin );
			iPosBegin = iPosEnd + 3;
		}
		else
		{
			CallerID = "";
		}
		iPosEnd = sValue.find( "%^#", iPosBegin );
		if ( iPosEnd != string::npos )
		{
			CalleeID = sValue.substr( iPosBegin, iPosEnd - iPosBegin );
			iPosBegin = iPosEnd + 3;
		}
		else
		{
			CalleeID = "";
		}
		iPosEnd = sValue.find( "%^#", iPosBegin );
		if ( iPosEnd != string::npos )
		{
			PrivateData = sValue.substr( iPosBegin, iPosEnd - iPosBegin );
			iPosBegin = iPosEnd + 3;
			CallType = atoi( sValue.substr( iPosBegin ).c_str() );
		}
		else
		{
			PrivateData = sValue.substr( iPosBegin );
			CallType = -1;
		}
//		iPosEnd = sValue.find( "%^#", iPosBegin );
//		if ( iPosEnd != string::npos )
//		{
//			CallID = sValue.substr( iPosBegin, iPosEnd - iPosBegin );
//			iPosBegin = iPosEnd + 3;
//		}
//		else
//		{
//			CallID = "";
//		}
	};

	string ToString()
	{
		ostringstream s;
		s << CallerID << "%^#" << CalleeID << "%^#" << PrivateData << "%^#" << CallType/* << "%^#" << CallID*/;
		return s.str();
	};

};



#endif