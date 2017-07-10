#pragma once

#include "stdafx.h"
#include "GlobalOperation.h"

#include <string>
#include <vector>
#include <map>
#include<list>
#include<sstream>
using namespace std;

extern bool g_bIsACDServer;

#define host_to_network_long htonl
#define network_to_host_long ntohl
#define host_to_network_short htons
#define network_to_host_short ntohs

//typedef int int32_t;
//typedef unsigned int uint32_t;
//typedef unsigned short uint16_t;
typedef unsigned __int64 uint64_t;

class Ntoh{
public:
	static uint64_t ntohll(uint64_t num);
	
};
class Hton{
public:
	static uint64_t htonll(uint64_t num);
};



#pragma warning(disable:4786)
enum DeptType
{
	DeptType_Skill = 0,
	DeptType_Mobile = 1,
	DeptType_PBX = 2,
};

//haoy:看名字推测，OutDialType应该是描述呼叫的类型，
//呼叫的类型信息应与呼叫有关系，而不是和设备有关系，
//所以不应该把呼叫类型放在设备的属性中
enum _OutDialType
{
	OutDialType_Normal,
	OutDialType_RingAgentExt,	//WEB绑电话，坐席呼电话，已被WebPSTNDial取代
	OutDialType_WebPSTNDial,
	OutDialType_WapDial,
	OutDialType_DialAgentExt,	//WEB绑电话，外线呼坐席
};

enum _SetAgentStateOperType
{
	SetAgentStateOperType_Unknown=0,
	SetAgentStateOperType_TransPSTNFromVoipAgent,
};

enum __ForceLogoutCause
{
	ForceLogoutCause_ReLogin = 0,
	ForceLogoutCause_NoExist,
	ForceLogoutCause_SwitchDept,
	ForceLogoutCause_ChangeLoginType,
	ForceLogoutCause_DelAgent,
	ForceLogoutCause_ChangeAgentInfo,
};

//客户类型
enum __ClientType
{
	ClientType_User=0,		//用户
	ClientType_Agent,		//座席
	ClientType_LanAgent,	//内网座席
	ClientType_UserOCX,	

	ClientType_Enterprise,	//企业版客户端
	ClientType_Disco,		//运营版客户端
	ClientType_AgentV3,		//座席(包含发送时间)
};

enum __CallPartyType
{
	CallParty_UnKnown=-1,
	CallParty_User,			//用户
	CallParty_Agent,		//座席
	CallParty_VoiceGateWay,	//语音网关

	CallParty_KeyWord,		//关键字
	CallParty_Department,	//业务组
	CallParty_WebPstnAgent,

	CallParty_IVR,			//IVR流程

	CallParty_CClient,
};

enum __CalledPartyType
{
	CalledPartyType_UnKnown=-1,
	CalledPartyType_WebUser,		//用户
	CalledPartyType_PSTNUser,		//座席
	CalledPartyType_WebAgent,		//语音网关
	CalledPartyType_WpAgent,		//关键字
	CalledPartyType_Department,		//业务组
};

enum __RouteTactic
{
	RouteTactic_Unknown = -1,
	RouteTactic_NoResponse = 0,
	RouteTactic_Reject,
	RouteTactic_RouteToAgent,
	RouteTactic_RouteToGroup,
};

enum __UserStatus
{
	UserStatus_NewUser = 0,
	UserStatus_OldUser,
	UserStatus_BlackList,
};

enum __AgentJoinType
{
	AgentJoin_UnKnown=-1,
	AgentJoin_Active=0,	//主控座席
	AgentJoin_Passive,
};

enum __WpAgentLineOperType
{
	WpAgentLineOperType_None=-1,
	WpAgentLineOperType_UserCallIn,
	WpAgentLineOperType_CallOut2User,
	WpAgentLineOperType_AgentCallIn,
	WpAgentLineOperType_CallOut2Agent,
};

//座席状态定义
enum __AgentState
{
	Agent_NoLogin=0,		//未登录
	Agent_Waiting,			//等待
	Agent_Ringing,			//震铃
	Agent_Parking,			//小休
	Agent_Talking,			//通话

	Agent_OpTalking,		//被动席间通话
	Agent_ForeProcess,		//话前处理
	Agent_BackProcess,		//话后处理
	Agent_Holding,			//保持
	Agent_Held,				//被保持
	Agent_Dialing,			//拨号
	Agent_DialUnderHold,	//保持下拨号
	Agent_TalkUnderHold,	//保持下通话
	Agent_ConnSucc_NoSend,	
	Agent_PreDial,			//预拨号
	Agent_ConferencePreside, //会议主持
	Agent_ConferenceJoin,    //会议参与者

	Agent_IVRnWait			//座席转IVR后保持
};

enum DialPSTNState
{
	DIALPSTN_READY,
	DIALPSTN_AREAQUERY,
	DIALPSTN_QueryGW,
	DIALPSTN_AgentQuery
};

enum __UserState		//用户状态
{
	User_Idle=0,		//空闲
	User_Queuing,		//排队
	User_Ringing,		//震铃

	User_Dialing,
	User_Dial_Queueing,
	User_Dial_Arrived,
	User_Talking,
	User_Held,			//被保持
};

enum __ConnectState
{
	Conn_None = 0,		//初始状态
	Conn_Try,			//尝试连接
	Conn_NoSend,		//连接成功，未发送数据
	Conn_Send,			//连接成功，发送数据。文本不会达到本状态。
	Conn_Tran_Try,		//尝试中转
	Conn_Tran_NoSend,	//中转成功，未发送数据
	Conn_Tran_Send,		//中转成功，发送数据
};

enum __EMediaType
{
	Type_TextChat=0,
	Type_Video,
	Type_Audio,
	Type_FileTransmit,
	Type_RemoteCtrl,
};

enum __UserCallingState
{
	UserCalling_Failed=0,	//失败
	UserCalling_Queuing,	//排队中...
	UserCalling_Ringing,	//座席震铃中...
	UserCalling_Nobody,		//无人登录

	UserCalling_AgentNoLogon,
	UserCalling_AgentBusy,

};

enum __AgentCallingState
{
	AgentCalling_UserNoLogin=0,		//用户未登录
	AgentCalling_UserBusy,			//用户忙
	AgentCalling_UserRinging,		//用户震铃中
	AgentCalling_UserQueuing,		//用户排队(网关)

	AgentCalling_AgentNoLogin,		//座席未等录
	AgentCalling_AgentBusy,			//座席忙
	AgentCalling_AgentQueuing,		//排队中
	AgentCalling_AgentRinging,		//座席震铃中...

	AgentCalling_DepartmentInexistence,	//组不存在

	AgentCalling_MakeCallNoAllowed,	//外拨不允许
};

enum __NatType
{
	NatType_None = 0,				//无

	NatType_Cone_Ip,				//锥形，限制IP
	NatType_Cone_Port,				//锥形，限制端口
	NatType_Symm_Ip_PerTarget,		//对称，每目的+1
	NatType_Symm_Ip_PerPack,		//对称，每包+1
	NatType_Symm_Special,			//对称，特殊，限制端口，出端口=。。。

	NatType_Unknown = 99,			//未知
};

enum __MediaType
{
	MediaType_None = 0,
	MediaType_Audio = 1,
	MediaType_Video = 2,
	MediaType_All   = 3,
};

enum __GetDepartNAgentMode
{
	Mode_MyDepart=0,
	Mode_MyDepartIdleAgents,
	Mode_OtherDeparts,
	Mode_OtherDepartsIdleAgents,
	Mode_AllDepartsNAgents,
};

enum __AgentStateEvent
{
	Event_DialFailed = 0,	//拨号失败	
};

enum __ServerType
{
	ServerType_UState = 0,
	ServerType_Guide,
	ServerType_ACD,
	ServerType_Realy,
	ServerType_Nat,
	ServerType_Transmit,
	ServerType_SmartRoute,
	ServerType_GWMgr,
	ServerType_ScanKeyWord,
};

enum __IPCCCallType	//呼叫类型
{
	IPCCCallType_Internet = 0,
	IPCCCallType_PSTN,
	IPCCCallType_Agent,
};

enum __VDNEndCause
{
	VDNEndCause_Normal,		//正常
	VDNEndCause_Overflow,	//溢出
	VDNEndCause_CallAbandon	//呼损
};

enum __CallUserFailedCause
{
	CallUserFailedCause_None=0,
	CallUserFailedCause_UserBusy,
	CallUserFailedCause_UserNullNumber,
	CallUserFailedCause_UserNoAnswer,
	CallUserFailedCause_UserReject,
	CallUserFailedCause_Unknown
};

enum __NotifyErrorType
{
	NotifyErrorType_SS7LinkErr=0,
};

enum TrunkState
{
	Trunk_Idle,
	Trunk_Out,
	Trunk_In,
};

enum DlyStrategyType
{
	Type_agent2GwDelay = 0,
	Type_gw2CalledDelay,
};

enum LoginType
{
	LoginType_OnlyWeb=0,
	LoginType_WebPSTN,
	LoginType_OnlyPSTN,
};

enum AlertType
{
	AlertType_Record_HardDisk = 0,
	AlertType_Annunciator,	// +报警服务器发来的 [5/7/2008 lixg]
};

enum AlertMode
{
	AlertMode_Telephone=0,
	AlertMode_SMS,
};

enum __LicenceType
{
	LicenceType_Agent = 0, //Agent
	LicenceType_Line  = 1, //Line
};

/*
enum TollType
{
TollType_CCN=0,
TollType_Disco,
TollType_400P2P,
};
*/

//大类型定义
enum __EIPCCMsgClass
{
	Class_Login=0,			//登录服务器
	Class_Guide=1,			//呼叫引导服务器
	Class_ACD=2,			//部门呼叫控制服务器(ACD)
	Class_DataCollection=3,	//数据采集
	Class_UserMark=4,		//用户反馈服务器
	Class_Relay=5,			//通讯协作服务器
	Class_SysManage=6,		//系统维护程序
	Class_Client=7,			//客户端程序
	Class_P2P=8,			//P2P通讯相关信令

	Class_EndEgn=9,			//结束引擎
	Class_HeartBeat=10,		//心跳

	Class_Transmit=11,		//中转
	Class_UState=12,		//用户状态
	Class_File=13,			//文件传输
	Class_Record=14,		//录音
	Class_SmartRoute=15,	//智能路由
	Class_Gateway=16,		//语音网关
	Class_TextChat=17,		//文本交谈
	Class_GwMonit=18,		//网关监控
	Class_Redirect=19,		//重定向
	Class_DlyStrategy=20,	//延迟策略
	Class_TollQuery=21,		//费用查询

	Class_SMS=22,			//短信息
	Class_Toll=23,			//计费
	Class_PhoneSearch=24,	//号码检索
	Class_Wap=25,
	Class_DataRoute=26,
	Class_DataTrans=27,
	Class_Alert=28,
	Class_OutDial=29,
	Class_Notify=30,
	// 刘永辉
	Class_FuncCall=31,
	Class_FuncReturn=32,
	Class_FuncEvent=33,
	Class_OCXHeart=34,
	Class_Autodetector=35,	// cs版容错程序间的消息 [6/16/2009 lixg] 
	Class_OCXService=36,	// 定义OCX和Service之间的通信
	Class_Operator=37,		// 运营商发送通知消息 [10/10/2009 lixg]
	Class_Monitor=38,
	Class_Log=39,			// 构件向日志服务器发送日志 [6/1/2010 lixg]

	Class_AreaCode=40,			
	Class_alarm=41,
	Class_AgentRecord=42,	// 席间通话录音  [5/31/2011 lixg]

	Class_ServerProxy=43,   //By Guojf

	Class_SAMPLER=44,		// by wangh
	Class_CallControl=45,	// haoy, 万达项目用来限制网关外呼并发数量
	Class_DIDControl=46,	// haoy, 呼入号码关联的策略控制消息

	Class_OneKeySwitch=47,	// hongh, 一键切换中心

	Class_License = 48,		// By Guojf 许可认证
	Class_GCTI = 49,		// By HYJ GlobolctiEngine
	Class_Board=50,         // by hyj Board message
	Class_Timer = 51,		//By caodt 时间同步

	Class_CID = 52,			//客户行为探测
	Class_ClientCapture=53, //客户端信息采集
	Class_VoiceRecognition=54,
	Class_TTS = 55,			// TTS
	Class_batExtRec = 56,	// 批量抽取保险业务录音

	Class_CClient = 57,		// C 端客户端
	Class_CProxy = 58,		// CProxyServer

	Class_RouteSelect = 59,  //
	Class_FileTransfer = 60, // 文件传输
};

//具体消息类型定义
enum __EIPCCMsgType
{
	//Client (客户端: user & agent)
	Type_Client_UserLogin=0,					//用户登录 (->登录服务器)
	Type_Client_UserQueryCall=1,				//用户呼叫询问 (->引导服务器)
	Type_Client_UserMakeCall=2,					//用户发起呼叫 (->ACD服务器)
	Type_Client_UserHangupCall=3,				//用户挂断呼叫 (->ACD服务器)
	Type_Client_UserMark=4,						//用户评价(->用户反馈服务器)
	Type_Client_AgentLogin=5,					//座席登录 (->ACD服务器)
	Type_Client_AgentLogout=6,					//座席注销 (->ACD服务器)
	Type_Client_AgentPark=7,					//座席小休 (->ACD服务器)
	Type_Client_AgentUnPark=8,					//座席取消小休 (->ACD服务器)
	Type_Client_AgentAnswerCall=9,				//座席应答呼叫(->ACD服务器)
	Type_Client_AgentHangupCall=10,				//座席挂机(->ACD服务器)
	Type_Client_TextChatWords=11,				//文本交谈内容(->Client界面程序)
	Type_Client_MediaRequest=12,				//用户发起的媒体通讯请求(->ACD服务器)
	Type_Client_MediaRequestConf=13,			//座席回复ACD媒体通讯请求确认(->ACD服务器)
	Type_Client_MediaReady=14,					//14 用户和座席互相通知对方自己的媒体就绪 

	//Login(登录服务器)
	Type_Login_UserLoginSucc=15,				//用户登录成功(->用户)
	Type_Login_UserLoginFailed=16,				//用户登录失败(->用户)

	//Guide(引导服务器)
	Type_Guide_ACDInfo=17,						//引导服务器ACD-net信息(->用户)
	Type_Guide_AddKeyConf=18,					//增加关键字确认消息(->系统维护程序)
	Type_Guide_DelKeyConf=19,					//删除关键字确认消息
	Type_Guide_LoadKeyWords=20,					//20 启动 GuideServer 的时候加载部门信息(->系统维护程序)

	//SysManage(系统维护程序相关信令)
	Type_SysManage_AddKey=21,					//增加关键字(->给引导服务器)
	Type_SysManage_DelKey=22,					//删除关键字(->给引导服务器)
	Type_SysManage_AddDepartment=23,			//增加部门(->给ACD服务器)
	Type_SysManage_DelDepartment=24,			//删除部门(->给ACD服务器)

	//ACD (呼叫控制服务器相关信令)
	Type_ACD_AgentLoginSucc=25,					//座席登录成功
	Type_ACD_AgentLoginFailed=26,				//座席登录失败
	Type_ACD_AgentLogoutConf=27,				//座席注销确认
	Type_ACD_AgentParkConf=28,					//座席小休确认
	Type_ACD_AgentUnParkConf=29,				//座席取消小休确认
	Type_ACD_UserMakeCallConf=30,				//30 用户呼叫确认
	Type_ACD_CallDelivered=31,					//31 呼叫到达(->座席)
	Type_ACD_CallEstablished=32,				//32 呼叫建立(->座席)
	Type_ACD_CallAnswered=33,					//33 呼叫应答(->用户)
	Type_ACD_CallReleased=34,					//呼叫释放(->座席)
	Type_ACD_CallHanguped=35,					//呼叫释放(->用户)
	Type_ACD_AgentStateInfo=36,					//座席状态信息(->数据采集服务器)
	Type_ACD_AddDepartmentConf=37,				//增加部门的确认消息(->系统维护程序)
	Type_ACD_DelDepartmentConf=38,				//删除部门的确认消息(->系统维护程序)
	Type_ACD_LoadDepartments=39,				//启动 ACDServer 的时候加载部门信息(->系统维护程序)
	Type_ACD_MediaRequest=40,					//40 用户的媒体请求(->座席)
	Type_ACD_MediaRequestConf=41,				//41 ACD媒体请求确认(->用户)

	//P2P
	Type_P2P_ConnRequest=42,					//42 用户或座席发起P2P连接请求(用户或座系->Relay)
	Type_P2P_MakeHoleCmd=43,					//43 RelayServer通知座席打洞(Relay->座席)
	Type_P2P_MakeHoleCmdConf=44,				//44 打洞确认(座席->Relay)
	Type_P2P_MakeHoleMsg=45,					//45 打洞消息(座席->用户 此消息将被丢弃)
	Type_P2P_ConnRequestConf=46,				//46 连接请求确认消息(Relay->用户)
	Type_P2P_TestMsg=47,						//47 P2P测试消息(用户->座席)
	Type_P2P_TestMsgConf=48,					//48 P2P测试确认消息(座席->用户)
	Type_P2P_DirectConn=49,						//49 直连

	Type_HeartBeat=50,							//心跳消息
	Type_EndEgn=51,								//结束引擎

	Type_P2P_ChechNatRequest=52,				//查询Nat类型请求
	Type_P2P_ChechNatConf=53,					//查询Nat类型回应
	Type_P2P_ConnDifficultMsg=54,				//通知连接方不容易连接

	Type_P2P_ReInitSockCmd=55,					//命令客户端从指定端口初始化
	Type_P2P_ReInitSockFailed=56,				//重新初始化端口失败

	Type_Trans_TransmitRequest=57,				//中转请求

	Type_Trans_TransmitRequestConf=58,			//中转请求确认
	Type_Trans_TransmitStopRequest=59,			//中转结束请求
	Type_Trans_TransmitRejected=60,				//60中转请求被拒绝

	Type_ACD_CallArriveToAgent=61,				//呼叫到达对方座席(座席呼座席:区分排队音/震铃音)
	Type_ACD_CallingQueueInfo=62,				//用户呼叫队列信息
	Type_ACD_AgentQueryStateConf=63,			//座席请求状态确认(成功/失败)

	Type_Client_AgentCallReceived=64,			//座席收到呼叫后通知对方将排队音换成震铃音
	Type_Client_GetCallingQueueInfo=65,			//获取用户排队数
	Type_Client_AgentQueryState=66,				//座席请求状态
	Type_Client_UserQueryState=67,				//用户请求状态
	Type_Client_AgentMakeCall=68,				//座席发起呼叫

	Type_Client_UserReset=69,					//用户复位
	Type_Client_AgentReset=70,					//70座席复位

	Type_UState_AgentMakeCallConf=71,			//用户收到呼叫
	Type_UState_CallReceived=72,				//用户收到呼叫
	Type_UState_CallArriveToAgent=73,			//呼叫到达对方座席(用户呼座席:区分排队音/震铃音)
	Type_UState_UserQueryStateConf=74,			//用户请求状态确认(成功/失败)

	Type_File_TransRequest=75,					//文件传输请求
	Type_File_TransRequestConf=76,				//文件传输请求应答
	Type_File_TransReady=77,					//文件传输等待接收

	Type_P2P_MediaNegotiate=78,					//媒体协商
	Type_P2P_MediaNegotiateConf=79,				//媒体协商回复

	Type_Client_UserLoginStateSvr=80,			//80用户登录到UStateServer
	Type_Client_UserLogoutStateSvr=81,			//用户从UStateServer logout
	Type_Client_UserAnswerCall=82,				//用户应答

	Type_UState_UserLoginConf=83,				//用户登录确认
	Type_UState_UserLogoutConf=84,				//用户退认确认
	Type_UState_CallHanguped=85,				//座席挂机
	Type_UState_MediaRequest=86,				//媒体请求
	Type_UState_CallAnswered=87,				//座席应答

	Type_ACD_AgentMakeCallConf=88,				//座席外呼确认

	Type_File_UnConnect=89,						//文件传输中止连接

	Type_UState_CallReleased=90,				//90座席挂机确认消息
	Type_UState_CallEstablished=91,				//呼叫建立

	Type_Client_CallUserConf=92,				//呼叫用户失败(网关)
	Type_ACD_CallUserConf=93,					//呼叫用户确认(网关)

	//Record
	Type_Record_Login=94,						//登录
	Type_Record_LoginConf=95,					//登录确认
	Type_Record_StartRecord=96,					//开始录音
	Type_Record_StopRecord=97,					//停止录音

	Type_UState_UserNoResponse=98,				//用户无响应

	Type_File_FileRequest=99,					//传输（特定）文件请求
	Type_File_FileRequestConf=100,				//100 请求回应
	Type_File_FileReceived=101,					//文件全部收到
	Type_File_FileStopped=102,					//文件传输停止（通知）
	Type_File_FileReceiveInfo=103,				//收到文件信息

	Type_Record_StartRecordConf=104,			//开始录音回应

	Type_Client_AgentHoldCall=105,				//保持
	Type_Client_AgentUnHoldCall=106,			//取消保持

	Type_ACD_AgentHoldCall=107,			
	Type_ACD_AgentUnHoldCall=108,
	Type_ACD_AgentHoldCallConf=109,

	Type_UState_AgentHoldCall=110,				//110
	Type_UState_AgentUnHoldCall=111,
	Type_UState_AgentHoldCallConf=112,

	Type_ACD_NotifyDataCollect=113,				//数据采集器入库通知

	Type_Client_CallUserFailed=114,				//呼叫用户失败
	Type_ACD_CallUserFailed=115,

	//SmartRoute
	Type_SmartRoute_QueryUserStatus=116,		//查询用户身份
	Type_SmartRoute_QueryUserStatusConf=117,	
	Type_SmartRoute_LoadSmartRouteTactic=118,
	Type_SmartRoute_BlackListTactic=119,
	Type_SmartRoute_NewUserTactic=120,			//120
	Type_SmartRoute_OldUserTactic=121,
	Type_SmartRoute_RouteTactic=122,			//返回路有策略

	Type_Client_QueryRouteTactic=123,	

	Type_Collect_RegisteConf=124,				//入库服务注册成功
	Type_Collect_StatProcess=125,				//处理座席状态日志以及统计

	Type_Storage_Registe=126,					//入库服务请求注册
	Type_Storage_UnRegiste=127,					//入库服务断开

	Type_Client_PrepareTransfer=128,
	Type_ACD_PrepareTransfer=129,
	Type_UState_PrepareTransfer=130,			//130
	Type_Client_TransReady=131,
	Type_ACD_TransReady=132,
	Type_UState_TransReady=133,
	Type_Client_TransferCall=134,
	Type_ACD_TransferCall=135,
	Type_UState_TransferCall=136,

	Type_Client_ClearPreConnection=137,			//清除预连接
	Type_ACD_ClearPreConnection=138,
	Type_UState_ClearPreConnection=139,			//139

	Type_Gateway_Login=140,						//140
	Type_Gateway_LoginConf=141,					//先发 corporationInfo 给网关，再发 LoginConf
	Type_Gateway_LoadInfo=142,
	Type_Gateway_SetBaseInfo=143,
	Type_Gateway_AddPrefixNoInfo=144,
	Type_Gateway_SetCorporationInfo=145,
	Type_Gateway_DelCorporationInfo=146,
	Type_Gateway_Logout=147,
	Type_Gateway_QueryGWConf=148,				//
	Type_Gateway_CallInQuery=149,				//呼入查询
	Type_Gateway_CallInQueryConf=150,			//150
	Type_Gateway_SetTrunkState=151,
	Type_Gateway_SyncTrunkState=152,			//同步
	Type_Gateway_AgentTestNetConf=153,			//153

	Type_Client_QueryGW=154,					//根据公司查询 gw
	Type_Client_AgentTestNet=155,
	Type_Client_AgentTestNetConf=156,
	Type_Client_LanPortApprize=157,				//157
	Type_Client_QueryGWLanInfo=158,

	Type_Gateway_QueryGWLanInfoConf=159,

	Type_Client_GetDepartNAgentInfo=160,		//160
	Type_ACD_DepartNAgentInfo=161,

	Type_Gateway_ReConnect=162,

	Type_Client_GetGroupRequest=163,			//公司、部门信息请求
	Type_ACD_GroupInfo=164,						//公司、部门信息

	Type_ACD_NotifyAgentStateEvent=165,
	Type_Login_ServerRegister=166,				//服务器登录到LoginServer
	Type_Login_ServerRegisterConf=167,			//服务器登录回复，ScanKeyWord位置

	Type_ACD_VDNStatusInfo=168,

	Type_SysManage_ModifyKeyword=169,			//修改关键字
	Type_SysManage_ModifyKeyDepart=170,			//170修改关键字对应部门
	Type_SysManage_ModifyDepart=171,			//修改部门

	Type_SysManage_AddGatewayInfo=172,			//网关操作
	Type_SysManage_DelGatewayInfo=173,
	Type_SysManage_AddGWCorp=174,				//增加公司
	Type_SysManage_DelGWCorp=175,

	Type_Client_LoginToText=176,
	Type_Client_LogoutFromText=177,
	Type_Client_TextChat=178,

	Type_Text_TextChat=179,

	Type_ACD_MediaReady=180,					//180
	Type_UState_MediaReady=181,

	Type_SysManage_AddGWTG=182,					//增加组
	Type_SysManage_AddDeptTG=183,				//增加部门组
	Type_SysManage_AddDialRule=184,

	Type_HeartBeatResponse=185,

	Type_SysManage_DelACDCorp=186,

	Type_GwMonit_GetGwInfo=187,
	Type_GwMonit_GetGwInfoConf=188,
	Type_GwMonit_RegMonit=189,
	Type_GwMonit_TrunkState=190,				//190
	Type_GwMonit_ComputerInfo=191,
	Type_GwMonit_LicenceInfo=192,

	Type_Redirect_LoadCorpInfo=193,
	Type_Redirect_LoadCorpInfoConf=194,
	Type_Redirect_LoadPlatformInfo=195,
	Type_Redirect_LoadPlatformInfoConf=196,
	Type_Redirect_SearchPlatform=197,
	Type_Redirect_SearchPlatformConf=198,		//198
	Type_Redirect_GetPlatformList=199,
	Type_Redirect_GetPlatformListConf=200,		//200
	Type_Redirect_CorpRegister=201,
	Type_Redirect_GetCorpInfo=202,
	Type_Redirect_GetCorpInfoConf=203,
	Type_Redirect_AddCorpInfo=204,
	Type_Redirect_DelCorpInfo=205,
	Type_Redirect_AddPlatformInfo=206,
	Type_Redirect_DelPlatformInfo=207,

	//DlyStrategy
	Type_DlyStrategy_QueryStrategy=208,
	Type_DlyStrategy_QueryStrategyConf=209,
	Type_DlyStrategy_AddStrategy=210,			//210
	Type_DlyStrategy_DelStrategy=211,
	Type_DlyStrategy_LoadStrategy=212,
	Type_DlyStrategy_LoadStrategyConf=213,
	Type_DlyStrategy_GetStrategy=214,
	Type_DlyStrategy_GetStrategyConf=215,

	Type_Gateway_AgentTalkBegin=216,
	Type_Gateway_AgentTalkEnd=217,

	Type_TollQuery_TollQuery=218,
	Type_TollQuery_TollQueryConf=219,

	Type_ACD_ForceLogout=220,					//220
	Type_Client_BeforeTransfer=221,
	Type_UState_BeforeTransfer=222,

	Type_Gateway_SetRecord=223,
	Type_Gateway_SetRecordConf=224,

	Type_UState_CallUserConf=225,
	Type_UState_CallUserFailed=226,
	Type_UState_UserMakeCallConf=227,
	Type_Client_UserMakeCallPSTN=228,

	Type_SMS_AddLinkman=229,
	Type_SMS_DelLinkman=230,
	Type_SMS_ModifyLinkman=231,
	Type_SMS_Send=232,
	Type_SMS_SendConf=233,
	Type_SMS_QueryLinkmanList=234,
	Type_SMS_QueryLinkmanListConf=235,

	Type_Gateway_GetTrunkState=236,
	Type_Gateway_GetTrunkStateConf=237,

	Type_TollQuery_GwTollQuery=238,
	Type_TollQuery_GwTollQueryConf=239,

	Type_Client_AgentMakeCall2=240,				//240
	Type_UState_CallReceived2=241,

	Type_Gateway_ForceHangup=242,
	Type_Gateway_DisableSth=243,

	Type_Client_UserMakeCallPSTN2=244,

	Type_Client_PreConfercene=245,
	Type_Client_PreConferceneConf=246,
	Type_Client_Conference=247,
	Type_ACD_PreConfercene=248,
	Type_ACD_Conference=249,
	Type_ACD_PreConferceneConf=250,				//250
	Type_UState_PreConfercene=251,
	Type_UState_Confercene=252,
	Type_UState_PreConferceneConf=253,

	Type_Toll_400TrunkConnected=254,
	Type_Toll_400TrunkDisconnected=255,
	Type_Toll_400P2PTalkBegin=256,
	Type_Toll_400P2PTalkEnd=257,

	Type_PhoneSearch_IncomingCall=258,
	Type_PhoneSearch_IncomingCallConf=259,
	Type_PhoneSearch_ExtNoInfo=260,
	Type_PhoneSearch_ExtNoInfoConf=261,
	Type_PhoneSearch_400CallIn=262,

	Type_Gateway_400CallBackCmd=263,

	Type_Toll_400CBPreTalkBegin=264,
	Type_Toll_400CBPreTalkEnd=265,
	Type_Toll_400CBTransTalkBegin=266,
	Type_Toll_400CBTransTalkEnd=267,

	Type_Toll_TollInfo=268,
	Type_Toll_TollInfoAck=269,

	Type_Record_StartTrunkP2ARecord=270,		//开始录音270
	Type_Record_StopTrunkP2ARecord=271,			//停止录音
	Type_Record_StartTrunkP2PRecord=272,		//开始录音
	Type_Record_StopTrunkP2PRecord=273,			//停止录音

	Type_Toll_AgentTransP2PTalkBegin=274,
	Type_Toll_AgentTransP2PTalkEnd=275,

	Type_Toll_UniversalInfo=276,

	Type_Record_LoadManageInfo=277,
	Type_Record_LoadManageInfoConf=278,
	Type_Record_AddRecCorp=279,
	Type_Record_DelRecCorp=280,
	Type_ACD_UserMakeCallPSTN=281,
	Type_ACD_UserMakeCallPSTN2=282,
	Type_ACD_RingAgentExt=283,
	Type_ACD_RingAgentExt2=284,

	Type_ACD_QueryGW=285,

	Type_UState_RingAgentExt=286,
	Type_UState_RingAgentExt2=287,
	Type_Gateway_RingAgentExtConf=288,
	Type_Gateway_RingAgentExtFailed=289,
	Type_Gateway_AgentAnswerCall=290,			//290
	Type_Gateway_AgentHangupCall=291,

	Type_ACD_StopRingAgentExt=292,
	Type_Gateway_StopRingAgentExtConf=293,
	Type_Gateway_QueryAgentInfo=294,
	Type_PhoneSearch_QueryAgentInfoConf=295,

	Type_Gateway_CancelRingAgentExt=296,

	Type_Gateway_IsAgentLogin=297,
	Type_ACD_IsAgentLoginConf=298,

	Type_Wap_CallOut=299,
	Type_Client_WebPSTNDial=300,				//300

	Type_Gateway_CallAgentExtFailed=301,
	Type_Gateway_AgentExtCallerFailed=302,

	Type_Gateway_AgentExtCallSucc=303,

	Type_ACD_NotifyAgent=304,

	Type_PhoneSearch_QueryBlackList=305,
	Type_PhoneSearch_QueryBlackListConf=306,

	Type_ACD_AddCorpNDeptInfo=307,

	Type_Toll_SMS=308,
	Type_Toll_SMSAck=309,

	Type_Gateway_UnAnsweredCall=310,

	Type_ACD_SetClientAgentState=311,

	Type_Client_WebPSTNAgentHoldCall=312,
	Type_Client_WebPSTNAgentUnHoldCall=313,
	Type_UState_WebPSTNAgentHoldCall=314,
	Type_UState_WebPSTNAgentHoldCallConf=315,
	Type_UState_WebPSTNAgentUnHoldCall=316,

	Type_ACD_CallAnswered_WebPstnAgent=317,

	Type_Client_WpAgentTrans2VoipAgent=318,
	Type_UState_WpAgentTrans2VoipAgent=319,

	Type_Gateway_UserHangupCall=320,			//320
	Type_ACD_CallReleased_WpAgent=321,

	Type_Gateway_CallAgentConf=322,
	Type_ACD_RingWpAgentExtFailed=323,

	Type_Gateway_CallAgentFailed=324,
	Type_ACD_CallWpAgentConf=325,

	Type_ACD_TransferCall_WpAgent=326,
	Type_ACD_BeforeTransferCall_WpAgent=327,

	Type_ACD_CallWpAgentExtFailed=328,
	Type_Gateway_CallUserFailed_WpAgent=329,

	Type_PhoneSearch_QueryTestKeyword=330,
	Type_PhoneSearch_QueryTestKeywordConf=331,

	Type_Gateway_CallCleared=332,

	Type_Client_EchoRemoveCtrl=333,
	Type_UState_EchoRemoveCtrl=334,

	Type_PhoneSearch_QueryManagerId=335,
	Type_PhoneSearch_QueryManagerIdConf=336,

	Type_Client_QueryTransServer=337,
	Type_DataRoute_QueryTransServerConf=338,
	Type_DataTrans_Register=339,
	Type_DataTrans_UnRegister=340,				// 340

	Type_DataTrans_StartTrans=341,
	Type_DataTrans_StartTransConf=342,
	Type_DataTrans_StopTrans=343,

	Type_Client_AgentLoadURL=344,
	Type_Login_AgentLoadURLConf=345,

	Type_ACD_CallEnterVDN=346,
	Type_ACD_CallLeaveVDN=347,

	Type_Collect_StatProcessConf=348,
	Type_Collect_BeatHeart=349,					// 存储服务->采集服务

	Type_Client_GetTalkingAgent=350,
	Type_ACD_GetTalkingAgentConf=351,
	Type_Client_MonitRequest=352,
	Type_Client_MonitRequestConf=353,

	Type_Record_RecInfo2ACD=354,
	Type_ACD_RecInfo2Client=355,

	Type_Client_StopMonit=356,

	Type_Toll_TollTransation=357,				// 357 

	Type_Gateway_GetDeptQueueNum=358,			// begin---libh 2007/12/28
	Type_ACD_GetDeptQueueNumConf=359,
	Type_Gateway_GetAgentState=360,
	Type_ACD_GetAgentStateConf=361,				// end---libh 2007/12/28

	Type_ACD_MonitRequest=362,
	Type_ACD_MonitRequestConf=363,

	Type_Client_MediaRequest_Monit=364,
	Type_ACD_MediaRequest_Monit=365,
	Type_Client_MediaReady_Monit=366,

	Type_Alert_NotifyInfo=367,
	Type_Gateway_Valid=368,						// +容错中心设置网关有效或无效（没有心跳） [12/25/2007 lixg]

	Type_Client_SuperDisconnect=369,
	Type_ACD_SuperDisconnect=370,

	Type_Gateway_GetGetwayInfo=371,
	Type_Gateway_GetGetwayInfoConf=372,

	Type_Gateway_AddRecordForTH=373,
	Type_Gateway_DelRecordForTH=374,
	Type_Gateway_DelAllRecordForTH=375,

	Type_ACD_MediaReady_Monit=376,
	Type_ACD_StopMonit=377,
	Type_Client_GetParkReasons=378,
	Type_Login_GetParkReasonsConf=379,

	Type_DataRoute_QueryTransServer_IP=380,
	Type_DataRoute_QueryTransServerConf_IP=381,
	Type_DataTrans_StartTrans_IP=382,
	Type_DataTrans_StartTransConf_IP=383,
	Type_DataTrans_StopTrans_IP=384,

	Type_Gateway_GetDeptWaitingAgentNum=385,
	Type_ACD_GetDeptWaitingAgentNumConf=386,

	Type_Client_SendDtmf=387,
	Type_ACD_DelDepartment=388,

	Type_Client_GetTrunkCount=389,
	Type_Gateway_GetTrunkCountConf=390,

	Type_ACD_SetTalkSpan=391,
	Type_ACD_SetAgentCount=392,
	Type_Client_SetOutDialResult=393,

	Type_SysManage_NotifyACDLicence=394,

	Type_Client_UserAnswerCall_Real=395,	//用户真正开始应答
	Type_ACD_CallEstablished_Real=396,

	Type_Gateway_GetDeptOverflow=397,
	Type_ACD_GetDeptOverflowConf=398,

	Type_Client_ChangePassword=399,
	Type_Login_ChangePasswordConf=400,

	Type_Client_SetOutdialCase=401,

	Type_PhoneSearch_QueryDelieverNo=402,		// begin---yany 2008/11/20
	Type_PhoneSearch_QueryDelieverNoConf=403,	// end---yany 2008/11/20

	Type_Client_ReceiveDtmf=404,

	Type_OutDial_SetAgentCount=405,
	Type_OutDial_DialCmd=406,
	Type_OutDial_DialResult=407,
	Type_OutDial_AnalyzeResult=408,
	Type_OutDial_TransResult=409,
	Type_OutDial_EndTalk=410,
	Type_OutDial_EndProcess=411,
	Type_OutDial_GwLineSynchronize=412,
	Type_OutDial_TaskStateCtrl=413,
	Type_OutDial_SetMaxBotherRate=414,

	Type_Notify_ErrorOccurred=415,

	Type_Client_SendStrMsg=416,	//	[3/2/2009 lixg]
	Type_ACD_SendStrMsg=417,		//  [3/2/2009 lixg]	

	Type_OutDial_SetForecastIntensity=418,
	Type_OutDial_SetForecastIntensityConf=419,

	Type_Client_QueryIncrementFunc=420,
	Type_Login_QueryIncrementFuncConf=421,

	Type_Gateway_LoadDataConf=422,

	// OCX心跳
	Type_OCXHeart_Send=423,
	Type_OCXHeart_Resp=424,
	Type_Autodetector_Logon=425,	//  [6/17/2009 lixg]
	Type_Autodetector_LogonACK=426,	//  [6/17/2009 lixg]

	Type_Client_ReturnToAgent=427,
	Type_ACD_ReturnToAgent=428,
	Type_Autodetector_Heartbeat=429,
	Type_Autodetector_HeartbeatACK=430,
	Type_Autodetector_ReportError=431,
	Type_Autodetector_RebootProc=432,
	Type_Autodetector_RebootProcACK=433,
	//
	Type_SMS_OperServerLogin=434,
	Type_SMS_OperServerLoginConf=435,
	Type_SMS_OperServerLogout=436,
	Type_SMS_OperServerLogoutConf=437,
	Type_SMS_Recved=438,
	Type_SMS_RecvedConf=439,
	Type_OCXService_SubTrans=440, // 分包传输
	Type_Autodetector_ReportCompStat=441,	//  [7/24/2009 lixg]
	Type_Autodetector_heartbeatFromComp=442,
	Type_Autodetector_Log=443,
	Type_Autodetector_Subscribe=444,
	Type_Autodetector_Subscribe_Resp=445,
	Type_Autodetector_Subscribe_Data=446,
	Type_Autodetector_Unsubscri=447,
	Type_Autodetector_Unsubscri_Resp=448,

	Type_PhoneSearch_GetCallTarget=449,
	Type_PhoneSearch_GetCallTargetConf=450,

	Type_Gateway_GetDeptLoginAgentNum=451,
	Type_ACD_GetDeptLoginAgentNumConf=452,

	Type_Operator2ACD_SendStrMsg=453,
	Type_Operator2Login_SendStrMsg=454,
	Type_Operator2Login_GetStrMsg=455,
	Type_Login_GetStrMsgRes=456,
	Type_Operator2Login_CancelStrMsg=457,

	Type_Login_SendStrMsg=458,

	Type_Gateway_TrunkStat=459,
	Type_Gateway_TrunkSeizeRate=460,

	Type_Gateway_CallInStat=461,
	Type_Gateway_CallOutStat=462,

	Type_Monitor_SrvLogin=463,
	Type_Monitor_SrvLoginConf=464,
	Type_Monitor_SrvLogout=465,
	Type_Monitor_SrvLogoutConf=466,
	Type_Monitor_UpdateCliCount=467,

	Type_Client_NotifyAgentLogin=468,
	Type_Login_NotifyAgentLoginConf=469,

	Type_OutDial_HeartBeat=470,
	Type_OutDial_ToGw=471,
	Type_OutDial_FromGw=472,

	Type_Client_AgentLogoutDeparts=473,			// 座席登录多个技能组后注销部分技能组 (->ACD服务器)	[ scq/2010-04-23]
	Type_ACD_AgentLogoutDepartsConf=474,		// 座席登录多个技能组后注销部分技能组回码 (->座席)	[ scq/2010-04-23]

	Type_OutDial_ResultStorage=475, 

	Type_OutDial_TaskStatus=476,
	Type_OutDial_TaskStatusConf=477,
	Type_Log=478,	// 用于构件向日志服务器发送日志 [6/1/2010 lixg]

	Type_Client_WpAgentHanupCall=479,
	Type_UState_WpAgentHanupCall=480,
	Type_UState_WpAgentHanupCallConf=481,

	Type_Gateway_WpAgent_LineNo=482,
	Type_ACD_WpAgent_LineNo=483,

	Type_Gateway_WpAgentRelease=484,
	Type_Gateway_WebPSTNDialConf=485,
	Type_Client_WpAgentMakeCall=486,
	Type_UState_WpAgentMakeCall=487,
	Type_Gateway_WpAgentCallAnswerred=488,

	Type_ACD_ResetDataCollect=489,
	Type_ACD_ResetMonitor=490,

	Type_AreaCode_AreaQuery=491,
	Type_AreaCode_AreaAnswer=492,

	Type_OutDial_GwLogin=493,
	Type_Client_QueryNowVersion=494,

	Type_Client_UserReLoginStateSvr=495,
	Type_AreaCode_QueryNowVersionConf=496,

	Type_Gateway_IVRStat=497,

	Type_PhoneSearch_GetWaitingMusic=498,
	Type_PhoneSearch_GetWaitingMusicConf=499,

	Type_alarm_alarmRequest=500,

	Type_Gateway_CallInOutStat=501,

	Type_Record_AgentRecordQueryPort=502, 
	Type_Record_AgentRecordQueryPortConf=503, 
	Type_Record_AgentRecordStart=504, 
	Type_Record_AgentRecordStop=505,

	Type_ServerProxy_LoadServerInfo = 506,
	Type_SysManage_LoadServerInfoConf=507,

	Type_ACD_SAMPLER_Query=508,
	Type_ACD_SAMPLER_Agreed=509,
	Type_SAMPLER_Query=510,
	Type_SAMPLER_Agreed=511,
	Type_SAMPLER_REPORT=512,
	Type_SAMPLER_NetDelay=513,

	Type_OutDial_SetOutdialGroup=514,
	 
	Type_CallControl_GetTrunkGroupSetting=515,	//网关查询中继组控制配置
	Type_CallControl_SetTrunkGroupSetting=516,	//控制服务设置中继组控制配置
	Type_CallControl_KeepAlive=517,				//心跳消息
	Type_CallControl_CallDetail=518,

	Type_OutDial_ExitOutDial=519,
	Type_OutDial_JoinOutDial=520,

	Type_SysManage_MoveAgent=521,
	Type_ACD_SwitchDept=522,

	Type_DIDControl_QueryGatewayConfig=523,
	Type_DIDControl_Response=524,
	Type_DIDControl_QueryDIDConfig=525,
	
	Type_Gateway_NotifyTrunkState=526,

	Type_OneKeySwitch_HeartBeatRegister=527,		//心跳服务注册
	Type_OneKeySwitch_GetServerHeartBeatServer=528,		//获取网关心跳服务
	Type_OneKeySwitch_GetServerHeartBeatServerConf=529,	//获取网关心跳服务回应
	Type_OneKeySwitch_GetClientHeartBeatServer=530,		//获取坐席心跳服务
	Type_OneKeySwitch_GetClientHeartBeatServerConf=531,		//获取坐席心跳服务回应
	Type_OneKeySwitch_ServerHeartBeat=532,		//网关心跳
	Type_OneKeySwitch_ClientHeartBeat=533,		//坐席心跳
	Type_OneKeySwitch_ClientHeartBeatConf=534,		//坐席心跳回应
	Type_OneKeySwitch_GetGwList=535,		//获取网关列表
	Type_OneKeySwitch_GetGwListConf=536,		//获取网关列表回应（每个网关一条）
	Type_OneKeySwitch_GetAcdList=537,		//获取企业中心列表
	Type_OneKeySwitch_GetAcdListConf=538,	//获取企业中心列表回应（每个Acd一条）
	Type_OneKeySwitch_SwitchCenter_Ctrl=539,	//网关切换服务通知-控制到心跳
	Type_OneKeySwitch_SwitchAcd_Ctrl=540,		//坐席切换acd通知-控制到心跳
	Type_OneKeySwitch_SwitchRedirect_Ctrl=541,		//坐席切换redirect通知-控制到心跳
	Type_OneKeySwitch_SwitchCenter=542,		//网关切换服务通知-心跳到网关
	Type_OneKeySwitch_SwitchAcd=543,		//坐席切换acd通知-心跳到坐席
	Type_OneKeySwitch_SwitchRedirect=544,		//坐席切换redirect通知-心跳到坐席

	Type_Record_ACK=545, // 录音信令的ack

	Type_OneKeySwitch_UserLoginStateSvrConf=546,	//IPCCAgent登录回应
	Type_OneKeySwitch_ConfirmGW=547,	//确认网关
	Type_Gateway_ConfirmGWConf=548,		//确认网关回应
	Type_Gateway_HeartBeatConfirm=549,	//确认网关心跳服务
	Type_OneKeySwitch_HeartBeatConfirmConf=550,		//确认网关心跳服务回应
	Type_Gateway_GetHeartBeat=551,		//获取网关心跳服务的Ip和Port
	Type_OneKeySwitch_GetHeartBeatConf=552,			//获取网关心跳服务的Ip和Port回应
	Type_OneKeySwitch_GWLogout=553,		//网关登出
	Type_UState_GWLogoutConf=554,		//网关登出回应
	Type_Gateway_GWLogoutConf=555,		//网关登出回应
	Type_Gateway_GWMRegister=556,		//GWManageServer向注册中心注册
	Type_UState_USRegister=557,			//UStateServer向注册中心注册
	Type_OneKeySwitch_RegisterConf=558,	//注册中心注册回应
	Type_OneKeySwitch_GWLogin=559,		//注册中心转发网关登录
	Type_OneKeySwitch_UserLogin=560,	//注册中心转发IPCCAgent登录
	Type_Client_GetUSnGWM=561,			//获取UStateServer和GWManageServer的地址
	Type_OneKeySwitch_GetUSnGWMConf=562,			//获取UStateServer和GWManageServer的地址回应
	Type_Client_UStateConfirm=563,		//确认UStateServer
	Type_Client_GWManageConfirm=564,	//确认GWManageServer
	Type_UState_ConfirmConf=565,		//确认UStateServer回应
	Type_Gateway_GWMConfirmConf=566,	//确认GWManageServer回应
	Type_Gateway_LoadGWCorpInfo=567,	//GWManageServer获取公司-技能组-中继组信息
	Type_OneKeySwitch_LoadGWInfo=568,	//注册中心获取网关信息
	Type_OneKeySwitch_ServerHeartBeatConf=569,		//网关心跳服务回应
	Type_OneKeySwitch_Synchronization=570,			//注册中心同步
	Type_OneKeySwitch_USRegister=571,	//注册中心同步UStateServer注册信息
	Type_OneKeySwitch_GWMRegister=572,	//注册中心同步GWManageServer注册信息
	Type_OneKeySwitch_GWLoginConf=573,	//注册中心同步时的网关登录信息回应

	Type_Licence_Query = 574,  ///许可请求
	Type_Licence_QueryConf = 575, ///许可请求回复

	Type_Client_LoginOverrun = 576, ///三次登录失败

	Type_OneKeySwitch_SetTrunkDeviecList=577,	//设置外呼可选中继列表	
	Type_Gateway_SetTrunkDeviecListConf=578,	//设置外呼可选中继列表回应

    Type_GCTI_MonitorDevice=579,
	Type_GCTI_GCTI_AnswerCall=580,
	Type_GCTI_GCTI_MakeCall=581,
	Type_GCTI_ClearConnection=582,
	Type_GCTI_IVRReturnTransferToAgent=583,
	Type_GCTI_HoldCall=584,
	Type_GCTI_MonitorConfEvent=585,
	Type_GCTI_MakeCallConfEvent=586,
	Type_GCTI_UniversalFailureConfEvent=587,
	Type_GCTI_DeliveredEvent=588,
	Type_GCTI_EstablishedEvent=589,
	Type_GCTI_NetworkReachedEvent=590,
	Type_GCTI_ServiceInitiatedEvent=591,
	Type_GCTI_HeldEvent=592,
	Type_GCTI_RetrievedEvent=593,
	Type_GCTI_TransferredEvent=594,
	Type_GCTI_ConnectionClearedEvent=595,
	Type_GCTI_FailedEvent=596,
	Type_GCTI_OriginatedEvent=597,
	Type_GCTI_ForceHangupEvent=598,
	Type_GCTI_SetAgentEvent=599,
	Type_GCTI_TransferredToIVREvent=600,
	Type_GCTI_ResetHoldCall=601,
	Type_GCTI_DriverMediaPlay=602,
	Type_GCTI_DriverMediaPlayWithASR=603,
	Type_GCTI_DriverMediaRecord=604,
	Type_GCTI_DriverMediaSendDTMF=605,
	Type_GCTI_DriverMediaReceiveDTMF=606,
	Type_GCTI_DriverMediaSendFax=607,
	Type_GCTI_DriverMediaReceiveFax=608,
	Type_GCTI_DriverMediaCLRBuf=609,
	Type_GCTI_DriverMediaStopWork=610,
	Type_GCTI_DriverSetCostStatus=611,
    Type_GCTI_TransferCall=612,
	Type_Board_DriverConnectConfEvent=613,
	Type_Board_DriverDisconnectConfEvent=614,
	Type_Board_DriverTrunkOffHookConfEvent=615,
	Type_Board_DriverTrunkOnHookConfEvent=616,
	Type_Board_DriverTrunkResetConfEvent=617,
	Type_Board_DriverConferenceDestroyConfEvent=618,
	Type_Board_DriverUniversalFailureConfEvent=619,
	Type_Board_DriverReportTrunkStateEvent=620,
	Type_Board_DriverInBoundCallEvent=621,
	Type_Board_DriverUserHangupEvent=622,
	Type_Board_DriverDialRingingEvent=623,
	Type_Board_DriverDialSuccessEvent=624,
	Type_Board_DriverDialSuccessTollEvent=625,
	Type_Board_DriverTrunkSeizedEvent=626,
	Type_Board_DriverFailedEvent=627,
	Type_Board_DriverMediaEvent=628,
	Type_GCTI_AgentTransferToIVR=629,
	Type_GCTI_AlternateCall=630,
	Type_GCTI_ClearCall=631,
	Type_GCTI_ReconnectCall=632,
	Type_GCTI_RejectCall=633,
	Type_GCTI_RetrieveCall=634,
	Type_GCTI_MonitorStop=635,
	Type_GCTI_SnapshotDevice=636,
	Type_Inner_AlertingRequest=637,
	Type_Inner_MakeCallRequest=638,
	Type_Inner_TimerEvent=639,
	Type_Bord_DriverConnect=640,
	Type_Bord_DriverDisconnect=641,
	Type_Bord_DriverDial=642,
	Type_Bord_DriverTrunkOffHook=643,
	Type_Bord_DriverTrunkOnHook=644,
	Type_Bord_DriverTrunkReset=645,
	Type_Bord_DriverEchoRemoveCtrl=646,
	Type_Bord_DriverAddRecordForTH=647,
	Type_Bord_DriverDelRecordForTH=648,
	Type_GCTI_Meaage=649,
	Type_Session_Meaage=650,
	Type_SysManage_SwitchAcdConf=651,
	Type_SysManage_AddTDDistributeServer=652,
	Type_SysManage_AddGWtoTDDS=653,
	Type_TrunkData_DSLoadInfo=654,
	Type_SysManage_AddTDCollectServer=655,
	Type_SysManage_AddComptoTDCS=656,
	Type_SysManage_AddGWtoTDCS=657,
	Type_SysManage_AddComptoConnNo=658,
	Type_TrunkData_NotifyTrunkState=659,

	Type_OutDial_CheckAlive = 660,
	Type_OutDial_CheckAliveConf = 661,

	Type_Timer_Synchronization = 662,
	Type_Timer_SynchronizationConf = 663,

	Type_Client_ConferenceCall = 664,
	Type_Client_ConferenceCallConf = 665,
	Type_Client_ConferenceCallEnd = 666,


	// 
	Type_OneKeySwitch_ServiceRegister=667,//begin hyj  2012-9-10
	Type_OneKeySwitch_ServiceRegisterConf=668,
	Type_OneKeySwitch_ServiceConfirm=669,
	Type_OneKeySwitch_ServiceConfirmConf=670,
	Type_OneKeySwitch_GetHeartBeat=671,
	Type_OneKeySwitch_GetService=672,
	Type_OneKeySwitch_GetServiceConf=673,
	Type_OneKeySwitch_ServiceTimeout=674,
	Type_OneKeySwitch_SynchronizationRegister=675,
	Type_OneKeySwitch_SynchronizationRegisterConf=676,
	Type_OneKeySwitch_LoadRegisterInfo=677,
	Type_SysManage_AddRegisterInfo=678,
	Type_OneKeySwitch_AddRegisterInfoConf=689,
	
	Type_Client_ConferenceStart=690,
	Type_ACD_ConferenceStart=691,
	Type_UState_ConferenceStart=692,
	Type_Client_ConferenceEnd=693,
	Type_ACD_ConferenceEnd=694,
	Type_UState_ConferenceEnd=695,
	Type_SysManage_GetServerList=696,
	Type_SysManage_GetServerListConf=697,
	Type_OneKeySwitch_HotAddService=698,

	Type_CID_DialCmd = 699,
	Type_CID_Result = 700,

	Type_Gateway_ConferenceStartConf=701,
	Type_ACD_ConferenceStartConf=702,
	Type_Gateway_UserLeaveConference=703,
	Type_ACD_UserLeaveConference=704,
	Type_Record_StartConferenceRecord=705,
	Type_Record_StopConferenceRecord=706,
	Type_OneKeySwitch_GWLogOutConf=707,	//注册中心同步时的网关登录信息回应

	Type_CID_CheckAlive = 708,
	Type_CID_CheckAliveConf = 709,
	Type_OneKeySwitch_SwitchService_Ctrl=710,
	Type_OneKeySwitch_SwitchService_CtrlConf=711,
	Type_OneKeySwitch_SwitchService=712,
	Type_OneKeySwitch_SwitchServiceConf=713,
	Type_Gateway_SubscribeTGStatus=714,
	Type_TrunkData_NotifyTGStatus=715,
	Type_SysManage_AddDeptTGRoute=716,
	Type_SysManage_DelDeptTGRoute=717,
	Type_UnAnsweredAgentCall=718,

	Type_DataTrans_SwitchPort=719,
	Type_DataTrans_SwitchPortConf=720,

	Type_SysManage_AddGWIADG=721,
	Type_SysManage_DelGWIADG=722,
	Type_SysManage_AddIAD=723,
	Type_SysManage_DelIAD=724,
	Type_OneKeySwitch_SynchronizationTimeout=725,
	Type_OneKeySwitch_SynchronizationTimeoutConf=726,

	Type_SysManage_AddSkillGroup=727,
	Type_SysManage_DelSkillGroup=728,
	Type_OneKeySwitch_SyncHeatBeatRelation=729,
	Type_OneKeySwitch_SyncHeatBeatRelationConfirm=730,
	Type_OneKeySwitch_SyncHeatBeatRelationConfirmconf=731,
	Type_OneKeySwitch_GetServerHeartBeatServerInfo=732,
	Type_SysManage_AddBanCall=733,
	Type_SysManage_DelBanCall=734,
	Type_SysManage_AddAreaBan=735,
	Type_SysManage_DelAreaBan=736,

	Type_ClientCapture_SessionEnd=737,
	Type_ClientCapture_SRSend=738,
	Type_ClientCapture_RRSend=739,
	Type_ClientCapture_GetRtpStatistics=740,
	Type_WebService_QueryCalloutInfo=741,
	Type_WebService_QueryCalloutInfoConf=742,
	Type_WebService_HangupCall=743,
	Type_WebService_RecordInfo=744,
	Type_WebService_DialingCall=745,
	Type_WebService_RingingCall=746,
	Type_WebService_TalkingCall=747,

	Type_SysManage_AddRecInfo=748,
	Type_SysManage_DelRecInfo=749,
	Type_Gateway_InsertDateOperation=750,

	Type_VoiceRecognition_RequestRecognition=751,
	Type_VoiceRecognition_ResponseRecognition=752,


	Type_WebService_InterfaceToMessage=753,
	Type_WebService_InterfaceToMessageConf=754,
	Type_WebService_RequestService=755,
	Type_WebService_RequestServiceConf=756,
	Type_WebService_HeartBeat=757,
	Type_WebService_HeartBeatConf=758,

	Type_voiceRecognition_AudioPacket=759,
	
	Type_ACD_SMSInfo=760,
	Type_PhoneSearch_SMSInfoConf=761,
	
	Type_Gateway_UnAnsweredCallConf=762,//add code hyj 2014-6-13
	Type_UnAnsweredAgentCallConf=763,
	Type_Gateway_InsertDateOperationConf=764,
	
	Type_Record_AgentTestStartRecord=765,
	Type_Record_AgentTestStartRecordConf=766,
	Type_Record_AgentTestStartPlayback=767,
	Type_Record_AgentTestStartPlaybackConf=768,
	
	Type_Client_SendErrCodeInfo=769,
	
	Type_ACD_RefreshSkillGroupConf=770,
	Type_ACD_NotifyACDLicenceConf=771,
	Type_Guide_RefreshKeywordConf=772,
	Type_ServerProxy_LoadServerInfoConfConf=773,
	Type_OneKeySwitch_RefreshGatewayInfoConf=774,
	Type_OneKeySwitch_RefreshRegisterInfoConf=775,
	
	Type_SysManage_LoadGWCorpInfoConf=776,
	Type_SysManage_LoadConfigInfoConf=777,
	
	Type_File_Register=778,
	Type_File_SendData=779,
	
	Type_Client_AgentToken=780,
	Type_File_Request=781,
    Type_File_Respond=782,
	// TTS
	Type_TTS_Request=783,
	Type_TTS_Result=784,
	
	Type_batExtRec_searchRecByInvokeId=785,
	Type_batExtRec_foundByInvokeId=786,
	
	Type_TTS_Cancel=787,
	Type_batExtRec_transferFileToMe=788,
	
	Type_OneKeySwitch_GetServerHeartBeatServerInfoConf=789,
	Type_SysManage_AgentInfoChange=790,

	Type_Redirect_GetService=791,
	Type_Redirect_GetServiceConf=792,
	Type_CClient_Login=793,
	Type_Login_CCLoginConf=794,
	Type_CClient_HeartBeat=795,
	Type_CProxy_HeartBeatConf=796,
	Type_CClient_CMakeCall=797,
	Type_CProxy_CMakeCallConf=798,
	Type_CProxy_CMakeCall=799,
	Type_CProxy_CallDelivered=800,
	Type_CClient_CallArrived=801,
	Type_CProxy_CallArrived=802,
	Type_CClient_CallAnswered=803,
	Type_CProxy_CallAnswered=804,
	Type_CProxy_CallStart=805,
	Type_CProxy_QueryGW=806,
	Type_CProxy_CMakeCall2=807,
	Type_SysManage_RefreshRedis=808,
	Type_SysManage_RefreshRedisConf=809,

	//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
	//Type_RouteSelect_Register,
	//Type_RouteSelect_AddGw,
	//Type_RouteSelect_RegisterConf,
	//Type_RouteSelect_NetTestReport,
	//Type_RouteSelect_NetTestReportConf,
	Type_RouteSelect_RouteSelect=810,
	Type_RouteSelect_RouteSelectConf=811,
	Type_RouteSelect_RouteRequest=812,
	Type_RouteSelect_RouteRequestConf=813,
	//Type_RouteSelect_RouteTrans,
	//Type_RouteSelect_RouteTransConf,
	Type_RouteSelect_RouteStop=814,
	Type_RouteSelect_RouteStopConf=815,
	//Type_RouteSelect_RouteStopTrans,
	//Type_RouteSelect_RouteStopTransConf,
	//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
	
	Type_CClient_HangupCall=816,
	Type_CProxy_HangupCall=817,
	Type_CClient_HangupCallConf=818,
	Type_CProxy_HangupCallConf=819,
	Type_ACD_CHangupCallConf=820,
	Type_CProxy_CallHanguped=821,
	Type_CClient_ToCProxyHeartBeat = 822,

	Type_FileTransfer=823,//hqh 2016.1.28  add
	Type_FileTransfer_UploadRequest=824,
    Type_FileTransfer_StartUpload=825,
    Type_FileTransfer_UploadCompleted=826,
    Type_FileTransfer_FileData=827,
	Type_NoType		//请保持这个在最后一个

};
enum ESeverType//STRATEGY 
{
	EST_ACDServer=1,
	EST_ACDProxyServer=2,
	EST_UStateServer=3,
	EST_GWManageServer=4,
	EST_LoginServer=5,
	EST_TollServer=6,
	EST_DataCollectServe=7,
	EST_EnterpriseTrunkDataCollectServer=8,//（DataCollectServe构件功能分支）
	EST_GatewayTrunkDataCollectServer=9,//（DataCollectServe构件功能分支）
	EST_MonitiorServer=10,//（DataCollectServe构件功能分支）
	EST_DataCenterServer=11,
	EST_TrunkDataDistributeServer=12,
	EST_IPCCDataDistributeServer=13,
	EST_GuideServer=14,
    EST_AreaCodeServer=15,
	EST_ConfigurationServer=16,
    EST_OneKeyWitchCtrl=17,
	ESI_RedirectServer=18,

	EST_RegisterServer=51,
	EST_ClientHeartBeatServer=52,   //（客户）
	EST_GW_ServerHeartBeatServer=53,//（网关）
	EST_CC_ServerHeartBeatServer=54,//（控制中心）

	EST_Softacd=101,
	EST_InfobirdAcd=102,
	EST_TollTransactionServer=103,
	EST_GlobalCTI=104,
	EST_DataGWServer=105,
	EST_CaptureNetInfoDataCollect=106,
	EST_IPCCRecorder=107,

	EST_Client=200,
	EST_TcpProxyServer=201,
	EST_CClinet=202,
	EST_CProxyServer=203,
	EST_DataTransServer = 204,
	EST_envInfoColServer = 205,

	EST_MainRedisA_Write=300,
	EST_MainRedisA_Read=301,
	EST_UpdateRedisA_Write=302,
	EST_UpdateRedisA_Read=303,

	EST_MainRedisB_Write=304,
	EST_MainRedisB_Read=305,
	EST_UpdateRedisB_Write=306,
	EST_UpdateRedisB_Read=307,

	EST_MainRedisC_Write=308,
	EST_MainRedisC_Read=309,
	EST_UpdateRedisC_Write=310,
	EST_UpdateRedisC_Read=311,
	EST_TcpTransServer = 312,

};

#define HEAD_LEN 8	
#define CORPNAME_LEN 50
#define CORPNDEPT_LEN 100
#define DEPTID_LEN   50
#define OVERFLOWDEST_LEN 50
#define INVOKEID_LEN 1500
#define MANAGERID_LEN 50
#define SENDER_LEN 50
#define KEYWORD_LEN 150
#define USERNAME_LEN 100
#define UUIDATA_LEN 600
#define GWPARTNO_LEN 50
#define COMSYMBOL_LEN 50
#define CALLTRANSID_LEN 50
#define THEOTHERPARTY_LEN 100
#define AGENTID_LEN 50
#define CALLID_LEN 50
#define EXTPHONENO_LEN 50
#define AGENTEXTNO_LEN 50
#define CALLEDNO_LEN 50
#define CALLERNOFORSEND_LEN 50
#define CURVERSION_LEN 50
#define OUTDIALPREFIXNO_LEN 50
#define ORIGINALDATA_LEN 600
#define THEPARTY_LEN 100
#define OTHERPARTY_LEN 100
#define PRESIDEAGENT_LEN 50
#define AGENTNAMESRC_LEN 50
#define AGENTNAMEDEST_LEN 50
#define IPNOAGENTEXT_LEN 50
#define AGENTLINENO_LEN 50
#define AGENTLINE_LEN 50
#define USERLINE_LEN 50
#define USERLINENO_LEN 50
#define FULLPATHFILENAME_LEN 300
#define AGENTNAME_LEN 50
//#define DEPTNAME_LEN 50
#define THESENDER_LEN 50
#define TRANS_LEN 50
//#define CODEC_LEN 50
#define AGENTPHONENO_LEN 50
#define NICKNAME_LEN 50
#define TARGETNAME_LEN 100
#define PARKREASON_LEN 100
#define NEWAGENTPHONENO_LEN 50
#define CALLERPARTY_LEN 50
#define TARGETPOSITION_LEN 100
#define READYPARTY_LEN 50
#define NOTIFIEDPARTY_LEN 50
#define NOTIFIER_LEN 100
#define GWNAME_LEN 50
#define NEWPHONENO_LEN 50
#define GWAREACODE_LEN 50
#define GROUP_LEN 1500
#define MSGCONTENT_LEN 1500
#define DESTAGENTS_LEN 1500
#define LICENCE_LEN 1500
#define ACCOUNT_LEN 50
#define PASSWORD_LEN 50
#define PREFIXLIST_LEN 50
#define PREFIX_LEN 50
#define AREACODE_LEN 50
#define IPPHONENO_LEN 50
#define PHONENO_LEN 50
#define TRUNKNO_LEN 50
#define STATELIST_LEN 1500
#define TRUNKGROUP_LEN 50
#define MAPPINGNAME_LEN 50
#define CHECKEDPREFIX_LEN 50
#define MANAGECONNECTNO_LEN 50
//#define TIME_LEN 50
#define SESSIONID_LEN 150
#define MANAGERSIGN_LEN 50
#define CURTIME_LEN 50
#define AGENTSTATE_LEN 50
#define CALLTARGER_LEN 150
#define MINUTE_LEN 61 
#define CURRENTHOUR_LEN 50
#define COLLECTDATE_LEN 50
#define TRUNKSTAT_LEN 1500
#define GROUPSEIZE_LEN 1500
#define TRUNKLINECOUT_LEN 1800
#define CALLEENUM_LEN 50
#define ROUTEDEST_LEN 200 
#define STATSQL_LEN 10000
#define IPADDRESS_LEN 16
#define FIELD_LEN 1500
#define GENERAL_LARGE_FIELD_LEN 1500
#define QUERYTAG_LEN 64

const int TIME_LEN = 25;
const int COMMENT_LEN = 10;
const int RECORDFILEPATH_LEN = 1500;
const int TARGETNUMS_LEN = 120;
const int LEVEL_LEN = 10;
const int ENTERPRISENAME_LEN = CORPNAME_LEN;
const int MEMBER1_LEN = 100;
const int MEMBER2_LEN = 100;
const int MEMBER3_LEN = 100;
const int MEMBER4_LEN = 100;
const int MEMBER5_LEN = 100;
const int MEMBER6_LEN = 100;
const int HANGUPTIME_LEN=30;
const int CODEC_LEN=50;
const int PACKED_SIZE=1500;
const int SEQUENCE_LEN=1500;
const int DESCRIPTION_LEN=1500;

struct S_RouteSelect_Node
{
	int Id;
	int Type;
	unsigned long Ip;
	unsigned short MainPort;
	unsigned short TestPort;
};

class CAudioStreamDescription
{
public:
    typedef std::string key_type;
    typedef std::string value_type;
    typedef std::pair<key_type, value_type> item_type;
    typedef std::vector<item_type>::size_type size_type;
private:
    typedef std::vector<item_type>::iterator iterator;

public:
    item_type& operator[] (size_type n);
    size_type size() const;
    void push_back (const item_type& val);
    void clear();
    bool empty();
    value_type getFirst(const key_type & key);
    void getAll(const key_type & key, vector<value_type> &values);

	int GetMemSize();
	int Serialize(char* thebuf, int bufSize);
	int Deserialize(char* thebuf, int bufSize);
    string to_str();
private:
    std::vector<item_type> streamAttributes;

};

/// IPCCMessage结构
struct SIPCCMessage	//基本消息结构
{
	SIPCCMessage(){};
	SIPCCMessage(int clazz,int type):msgClass(clazz),msgType(type){};
	virtual ~SIPCCMessage()
	{
		ReleaseMemory();
	}
	
	int			msgClass;	//消息种类(大类型)
	int			msgType;	//消息类型(小类型)
	virtual void ReleaseMemory(){}
	
	virtual int FillBuf(char*& thebuf) = 0;
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0) = 0;
	int FillMsgHead(char*& thebuf);
	int AnalyzeMsgHead(char* thebuf);
	virtual int GetMyMemSize() = 0;
	int FillMsgHead_net(char*& thebuf);
	int AnalyzeMsgHead_net(char* thebuf);
};

/// msgExchanger
class CIPCCMsgExchanger
{
public:
	void DeSerializeDlyStrategyMsg(char* pmsg, int msgsize, int &msgtype, SIPCCMessage &msg, unsigned long ip=0, unsigned short port=0);
	void SerializeDlyStrategyMsg(SIPCCMessage& msg, char*& thebuf, int& thebufcontent);
	void DeSerializeRedirectMsg(char* pmsg, int msgsize, int &msgtype, SIPCCMessage &msg, unsigned long ip=0, unsigned short port=0);
	void SerializeRedirectMsg(SIPCCMessage& msg, char*& thebuf, int& thebufcontent);
	void DeSerializeGatewayMsg(char* pmsg, int msgsize, int &msgtype, SIPCCMessage &msg, unsigned long ip=0, unsigned short port=0);
	void SerializeGatewayMsg(SIPCCMessage& msg, char*& thebuf, int& thebufcontent);
	CIPCCMsgExchanger();
	virtual ~CIPCCMsgExchanger();

	static bool static_GetMsgHeader(const char* msg, int msgsize, __EIPCCMsgClass& msgClass, __EIPCCMsgType& msgType);
	static void	static_SerializeMsg(SIPCCMessage& msg, char*& thebuf, int& thebufcontent);
	static void	static_DeSerializeMsg(char* pmsg, int msgsize, SIPCCMessage& msg, unsigned long ip=0, unsigned short port=0);

	bool	GetMsgHeader(const char* msg, int msgsize, __EIPCCMsgClass& msgClass, __EIPCCMsgType& msgType);
	void	SerializeMsg(SIPCCMessage& msg, char*& thebuf, int& thebufcontent);
	void	DeSerializeMsg(char* pmsg, int msgsize, SIPCCMessage& msg, unsigned long ip=0, unsigned short port=0);
	
private:
	void	SerializeSmartRouteMsg(SIPCCMessage& msg, char*& thebuf, int& thebufcontent);
	void	SerializeRecordMsg(SIPCCMessage& msg, char*& thebuf, int& thebufcontent);
	//	void	SerializeRecordMsg(SIPCCMessage& msg, char*& thebuf, int& thebufcontent);
	void	SerializeUStateMsg(SIPCCMessage& msg, char*& thebuf, int& thebufcontent);
	void	SerializeHeartBeatMsg(SIPCCMessage& msg, char*& thebuf, int& thebufcontent);
	void	SerializeLoginMsg(SIPCCMessage& msg, char*& thebuf, int& thebufcontent);
	void	SerializeGuideMsg(SIPCCMessage& msg, char*& thebuf, int& thebufcontent);
	void	SerializeACDMsg(SIPCCMessage& msg, char*& thebuf, int& thebufcontent);
	void	SerializeDataCollectionMsg(SIPCCMessage& msg, char*& thebuf, int& thebufcontent);
	//	void	SerializeUserMarkMsg(SIPCCMessage& msg, char*& thebuf, int& thebufcontent);
	void	SerializeRelayMsg(SIPCCMessage& msg, char*& thebuf, int& thebufcontent);
	void	SerializeSysManageMsg(SIPCCMessage& msg, char*& thebuf, int& thebufcontent);
	void	SerializeClientMsg(SIPCCMessage& msg, char*& thebuf, int& thebufcontent);
	void	SerializeP2PMsg(SIPCCMessage& msg, char*& thebuf, int& thebufcontent);
	void	SerializeEndEgnMsg(SIPCCMessage& msg, char*& thebuf, int& thebufcontent);
	void	SerializePhoneSearchMsg(SIPCCMessage& msg, char*& thebuf, int& thebufcontent);
	void	SerializeWapMsg(SIPCCMessage& msg, char*& thebuf, int& thebufcontent);
	
	void	DeSerializeSmartRouteMsg(char* pmsg, int msgsize, int &msgtype, SIPCCMessage &msg, unsigned long ip=0, unsigned short port=0);
	void	DeSerializeRecordMsg(char* pmsg, int msgsize, int &msgtype, SIPCCMessage &msg, unsigned long ip=0, unsigned short port=0);
	void	DeSerializeHeartBeatMsg(char* pmsg, int msgsize, int &msgtype, SIPCCMessage &msg, unsigned long ip=0, unsigned short port=0);
	//	void	DeSerializeRecordMsg(char* pmsg, int msgsize, int &msgtype, SIPCCMessage &msg, unsigned long ip=0, unsigned short port=0);
	void	DeSerializeUStateMsg(char* pmsg, int msgsize, int &msgtype, SIPCCMessage &msg, unsigned long ip=0, unsigned short port=0);
	void	DeSerializeLoginMsg(char* pmsg, int msgsize, int &msgtype, SIPCCMessage &msg, unsigned long ip=0, unsigned short port=0);
	void	DeSerializeGuideMsg(char* pmsg, int msgsize, int &msgtype, SIPCCMessage &msg, unsigned long ip=0, unsigned short port=0);
	void	DeSerializeACDMsg(char* pmsg, int msgsize, int &msgtype, SIPCCMessage &msg, unsigned long ip=0, unsigned short port=0);
	void	DeSerializeDataCollectionMsg(char* pmsg, int msgsize, int &msgtype, SIPCCMessage &msg, unsigned long ip=0, unsigned short port=0);
	void	DeSerializeUserMarkMsg(char* pmsg, int msgsize, int &msgtype, SIPCCMessage &msg, unsigned long ip=0, unsigned short port=0);
	void	DeSerializeRelayMsg(char* pmsg, int msgsize, int &msgtype, SIPCCMessage &msg, unsigned long ip=0, unsigned short port=0);
	void	DeSerializeSysManageMsg(char* pmsg, int msgsize, int &msgtype, SIPCCMessage &msg, unsigned long ip=0, unsigned short port=0);
	void	DeSerializeClientMsg(char* pmsg, int msgsize, int &msgtype, SIPCCMessage &msg, unsigned long ip=0, unsigned short port=0);
	void	DeSerializeP2PMsg(char* pmsg, int msgsize, int &msgtype, SIPCCMessage &msg, unsigned long ip=0, unsigned short port=0);
	void	DeSerializeEndEgnMsg(char* pmsg, int msgsize, int &msgtype, SIPCCMessage &msg, unsigned long ip=0, unsigned short port=0);
	void	DeSerializePhoneSearchMsg(char* pmsg, int msgsize, int &msgtype, SIPCCMessage &msg, unsigned long ip=0, unsigned short port=0);
	void	DeSerializeWapMsg(char* pmsg, int msgsize, int &msgtype, SIPCCMessage &msg, unsigned long ip=0, unsigned short port=0);
	
	void	DeSerializeTransmitMsg(char* pmsg, int msgsize, int &msgtype, SIPCCMessage &msg, unsigned long ip=0, unsigned short port=0);
	void	SerializeTransmitMsg(SIPCCMessage& msg, char*& thebuf, int& thebufcontent);
	
	void	DeSerializeFileMsg(char* pmsg, int msgsize, int &msgtype, SIPCCMessage &msg, unsigned long ip=0, unsigned short port=0);
	void	SerializeFileMsg(SIPCCMessage& msg, char*& thebuf, int& thebufcontent);
	
	void	DeSerializeTextMsg(char* pmsg, int msgsize, int &msgtype, SIPCCMessage &msg, unsigned long ip=0, unsigned short port=0);
	void	SerializeTextMsg(SIPCCMessage& msg, char*& thebuf, int& thebufcontent);
	
	void	SerializeGwMonitMsg(SIPCCMessage& msg, char*& thebuf, int& thebufcontent);
	void	DeSerializeGwMonitMsg(char* pmsg, int msgsize, int &msgtype, SIPCCMessage &msg, unsigned long ip=0, unsigned short port=0);
	
	void	SerializeTollQueryMsg(SIPCCMessage& msg, char*& thebuf, int& thebufcontent);
	void	DeSerializeTollQueryMsg(char* pmsg, int msgsize, int &msgtype, SIPCCMessage &msg, unsigned long ip=0, unsigned short port=0);
	
	void	SerializeSmsMsg(SIPCCMessage& msg, char*& thebuf, int& thebufcontent);
	void	DeSerializeSmsMsg(char* pmsg, int msgsize, int &msgtype, SIPCCMessage &msg, unsigned long ip=0, unsigned short port=0);
	
	void	SerializeTollMsg(SIPCCMessage& msg, char*& thebuf, int& thebufcontent);
	void	DeSerializeTollMsg(char* pmsg, int msgsize, int &msgtype, SIPCCMessage &msg, unsigned long ip=0, unsigned short port=0);
	
	void	SerializeDataRouteMsg(SIPCCMessage& msg, char*& thebuf, int& thebufcontent);
	void	DeSerializeDataRouteMsg(char* pmsg, int msgsize, int &msgtype, SIPCCMessage &msg, unsigned long ip=0, unsigned short port=0);
	
	void	SerializeDataTransMsg(SIPCCMessage& msg, char*& thebuf, int& thebufcontent);
	void	DeSerializeDataTransMsg(char* pmsg, int msgsize, int &msgtype, SIPCCMessage &msg, unsigned long ip=0, unsigned short port=0);
	
	void	SerializeSamplerMsg(SIPCCMessage& msg, char*& thebuf, int& thebufcontent);
	void	DeSerializeSamplerMsg(char* pmsg, int msgsize, int &msgtype, SIPCCMessage &msg, unsigned long ip=0, unsigned short port=0);

	void	SerializeAlertMsg(SIPCCMessage& msg, char*& thebuf, int& thebufcontent);
	void	SerializeAutodetectorMsg(SIPCCMessage& msg, char*& thebuf, int& thebufcontent)
	{
		thebufcontent = msg.FillBuf( thebuf );
	}
	void	SerializeOperatorMsg(SIPCCMessage& msg, char*& thebuf, int& thebufcontent)
	{
		thebufcontent = msg.FillBuf( thebuf );
	}
	void SerializeLogMsg(SIPCCMessage& msg, char*& thebuf, int& thebufcontent)	//  [6/1/2010 lixg]
	{
		thebufcontent = msg.FillBuf( thebuf );
	}
	void	DeSerializeOperatorMsg(char* pmsg, int msgsize, int &msgtype, SIPCCMessage &msg, unsigned long ip=0, unsigned short port=0)
	{
		msg.AnalyzeBuf(pmsg, msgsize, ip, port);
	}
	void DeSerializeLogMsg(char* pmsg, int msgsize, int &msgtype, SIPCCMessage &msg, unsigned long ip=0, unsigned short port=0)	//  [6/1/2010 lixg]
	{
		msg.AnalyzeBuf(pmsg, msgsize, ip, port);
	}
	void	DeSerializeAlertMsg(char* pmsg, int msgsize, int &msgtype, SIPCCMessage &msg, unsigned long ip=0, unsigned short port=0);
	void	DeSerializeAutodetectorMsg(char* pmsg, int msgsize, int &msgtype, SIPCCMessage &msg, unsigned long ip=0, unsigned short port=0)
	{
		msg.AnalyzeBuf(pmsg, msgsize, ip, port);
	}


	//ClientCapture
	void DeSerializeClientCaptureMsg(char* pmsg,int msgsize,int &msgtype,SIPCCMessage &msg,unsigned long ip=0,unsigned short port=0);
	void SerializeClientCaptureMsg(SIPCCMessage& msg,char*& thebuf,int& thebufcontent);

	//VoiceRecognition
	void DeSerializeVoiceRecognitionMsg(char* pmsg,int msgsize,int &msgtype,SIPCCMessage &msg,unsigned long ip=0,unsigned short port=0);
	void SerializeVoiceRecognitionMsg(SIPCCMessage& msg,char*& thebuf,int& thebufcontent);

	// TTS
	void DeSerializeTTSMsg(char* pmsg,int msgsize,int &msgtype,SIPCCMessage &msg,unsigned long ip=0,unsigned short port=0);
	void SerializeTTSMsg(SIPCCMessage& msg,char*& thebuf,int& thebufcontent);
};

///////////////////////////////////////////////////////////////////////////
///Class_Client
struct SIPCCMsg_Client : public SIPCCMessage
{
	SIPCCMsg_Client();
	~SIPCCMsg_Client()
	{
		ReleaseMemory();
	};
	SIPCCMsg_Client(int cla,int typ):SIPCCMessage(cla,typ){};
	
	virtual int GetMyMemSize(){return 0;}
	virtual int FillBuf(char*& thebuf){return 0;}
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0){}
	virtual void ReleaseMemory(){}
};

///////////////////////////////////////////////////////////////////////////
///Class_Wap
struct SIPCCMsg_Wap : public SIPCCMessage
{
	SIPCCMsg_Wap();
	~SIPCCMsg_Wap()
	{
		ReleaseMemory();
	};
	
	virtual int GetMyMemSize(){return 0;}
	virtual int FillBuf(char*& thebuf){return 0;}
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0){}
	virtual void ReleaseMemory(){}
};

///Type_Client_UserLogin
struct SIPCCMsg_Client_UserLogin : public SIPCCMsg_Client
{
	SIPCCMsg_Client_UserLogin();
	~SIPCCMsg_Client_UserLogin()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(userName!=NULL)	delete userName;	
		userName = NULL;
		userNameLen = 0;
		if(thePassword!=NULL)	delete thePassword;	
		thePassword = NULL;
		thePasswordLen = 0;
		loginType=LoginType_OnlyWeb;
	}
	
	void SetUserName(string username);
	string GetUserName()
	{
		if(userNameLen == 0)	return "";
		return string(userName);
	}
	void SetThePassword(char* thepassword, int thepasswordlen);
	void GetThePassword(char* thepassword)
	{
		if(thePasswordLen > 0)
			memmove(thepassword, thePassword, thePasswordLen);
	}
	unsigned long localIP;		//
	unsigned short localPort;	//
	
	int userType;
	int loginType;
	string corpInfo;
	string userOrigin;
	int versionType;
	
	char bMultiGroup;
	string localtime;  //座席登录loginserver时的机器时间。格式为：YYYY-MM-DD HH:MM:SS，也即(年-月-日 时:分:秒)
	string handleId;//操作唯一标识

	string token;	//"token":"xxx"

private:
	char* userName;
	int userNameLen;
	char* thePassword;
	int thePasswordLen;
	virtual int GetMyMemSize();
};

///Type_Client_UserQueryCall
struct SIPCCMsg_Client_UserQueryCall : public SIPCCMsg_Client
{
	SIPCCMsg_Client_UserQueryCall();
	~SIPCCMsg_Client_UserQueryCall()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(keyWord!=NULL)	delete  keyWord;
		keyWord = NULL;
		keyWordLen = 0;
		invokeID = 0;
	}
	void SetKeyWord(string keyword);
	string GetKeyWord()	
	{
		if(keyWordLen == 0)	return "";
		return string(keyWord);
	}
	
	int invokeID;
private:
	char* keyWord;
	int keyWordLen;
	virtual int GetMyMemSize();
};

///Type_Client_UserMakeCall
struct SIPCCMsg_Client_UserMakeCall : public SIPCCMsg_Client
{
	SIPCCMsg_Client_UserMakeCall();
	~SIPCCMsg_Client_UserMakeCall()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(userName!=NULL)	delete userName;
		userName = NULL;
		userNameLen = 0;
		if(theDepartment!=NULL)	delete theDepartment;
		theDepartment = NULL;
		theDepartmentLen = 0;
		if(keyWord!=NULL)	delete keyWord;
		keyWord = NULL;
		keyWordLen = 0;
		natType = NatType_Unknown;
		if(uuiData!=NULL)	delete uuiData;
		uuiData = NULL;
		uuiDataLen = 0;
		userType = -1;
		audioIP = 0;
		audioPort = 0;
		
		comSymbol = "";
		
		sipBoardIP = 0;
		sipBoardRtpPort = 0;
		sipBoardRtcpPort = 0;
		
		sipTransIP = 0;   //中转IP
		sipTransRtpPort = 0;  //中转RtpPort
		sipTransRtcpPort = 0;  //中转rtcpPort
	}
	void SetUserName(string userName);
	string GetUserName()
	{
		if(userNameLen==0)	return "";
		if ( !(VerifyData(userNameLen, USERNAME_LEN)) ) {return "";}
		return string(userName);
	}
	void SetTheDepartment(string thedepartment);
	string GetTheDepartment()	
	{
		if(theDepartmentLen==0)	return "";
		if ( !(VerifyData(theDepartmentLen, CORPNDEPT_LEN)) ) {return "";}
		return string(theDepartment);
	}
	void SetKeyWord(string keyword);
	string GetKeyWord()	
	{
		if(keyWordLen==0)	return "";
		if ( !(VerifyData(keyWordLen, KEYWORD_LEN)) ) {return "";}
		return string(keyWord);
	}
	void SetUUIData(string uuidata);
	string GetUUIData()	
	{
		if(uuiDataLen==0)	return "";
		if ( !(VerifyData(uuiDataLen, UUIDATA_LEN)) ) {return "";}
		return string(uuiData);
	}
	
	int natType;
	int userType;
	unsigned long audioIP;
	unsigned short audioPort;
	unsigned long lanIP;
	
	string gwPartNo;
	
	string comSymbol;
	
	string  callTransID;
	
	unsigned long sipTransIP;   //中转IP
	unsigned short sipTransRtpPort;  //中转RtpPort
	unsigned short sipTransRtcpPort;  //中转rtcpPort
	unsigned long sipBoardIP;  //交换机ip板IP
	unsigned short sipBoardRtpPort;  //交换机ip板Port
	unsigned short sipBoardRtcpPort;  //话机的rtcpPort

	string  managerId;
	string  connectPhoneNo;
	string  handleId;
	
	unsigned short conferencePort1;		//座席端用于会议的端口1
	unsigned short conferencePort2;		//座席端用于会议的端口2

	string SkillGroupID;
	int UserLevel;
	int CallTargetType;

    CAudioStreamDescription audioStreamDescription;

private:
	char* userName;
	int userNameLen;
	char* theDepartment;
	int theDepartmentLen;
	char* keyWord;
	int keyWordLen;
	char* uuiData;
	int uuiDataLen;
	
	
	virtual int GetMyMemSize();
	
public:
	/////////////////媒体信息描述/////////////////
	//传输方式，决定包格式
	//UDP/OLD	固定长度包，根据协商的编码和单位时间决定包长度
	//UDP/V1	变长包，包自身可以表述负载大小，暂时不用
	string trans;
	//编码方式
	//G729
	//ILBC
	string codec;
	//单位时间
	size_t unit;
	///////////////////////////////////////////////
	
};

///Type_Client_UserHangupCall
struct SIPCCMsg_Client_UserHangupCall : public SIPCCMsg_Client
{
	SIPCCMsg_Client_UserHangupCall();
	~SIPCCMsg_Client_UserHangupCall()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(userName!=NULL)	delete userName;
		userName = NULL;
		userNameLen = 0;
		if(theOtherParty!=NULL)	delete theOtherParty;
		theOtherParty = NULL;
		theOtherPartyLen = 0;
		bAgentAssigned = 0;
	}
	void SetUserName(string userName);
	string GetUserName()	
	{
		if(userNameLen==0)	return "";
		if ( !(VerifyData(userNameLen, USERNAME_LEN)) ) {return "";}
		return string(userName);
	}
	void SetTheOtherParty(string theOtherParty);
	string GetTheOtherParty()	
	{
		if(theOtherPartyLen==0)	return "";
		if ( !(VerifyData(theOtherPartyLen, THEOTHERPARTY_LEN)) ) {return "";}
		return string(theOtherParty);
	}
	
	char bAgentAssigned;
	int outDialType;
	
	int toAcdOrUserState;	// [scq/2010-05-24] 目的地类型
	char bIvrHangupCall;
	
	string  managerId;
	string  connectPhoneNo;
	string  handleId;

	//发送给cproxy时需要填写callID
	string callID;

	string netPath;

private:
	char* userName;
	int userNameLen;
	char* theOtherParty;
	int theOtherPartyLen;
	virtual int GetMyMemSize();
};

///Type_Client_UserMark
struct SIPCCMsg_Client_UserMark : public SIPCCMsg_Client
{
	SIPCCMsg_Client_UserMark();
	~SIPCCMsg_Client_UserMark()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	/*
	if(callID!=NULL)	delete callID;
	callID = NULL;
	callIDLen = 0;
	if(userName!=NULL)	delete userName;
	userName = NULL;
	userNameLen = 0;
	if(agentID!=NULL)	delete agentID;
	agentID = NULL;
	agentIDLen = 0;
	markLevel = -1;
		*/
	}
	/*
	void SetCallID(string callid);
	string GetCallID()	
	{
	if(callIDLen==0)	return "";
	return string(callID);
	}
	void SetUserName(string userName);
	string GetUserName()	
	{
	if(userNameLen==0)	return "";
	return string(userName);
	}
	void SetAgentID(string agentid);
	string GetAgentID()	
	{
	if(agentID==0)	return "";
	return string(agentID);
	}
	int agentIDLen;
	int markLevel;
	*/
private:
/*
char* callID;
int callIDLen;
char* userName;
int userNameLen;
char* agentID;
	*/
	virtual int GetMyMemSize();
};

///Type_Client_AgentLogin
struct SIPCCMsg_Client_AgentLogin : public SIPCCMsg_Client
{
	SIPCCMsg_Client_AgentLogin();
	~SIPCCMsg_Client_AgentLogin()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(agentID!=NULL)	delete agentID;
		agentID = NULL;
		agentIDLen = 0;
		if(theDepartment!=NULL)	delete theDepartment;
		theDepartment = NULL;
		theDepartmentLen = 0;
		loginType = LoginType_OnlyWeb;
	}
	void SetAgentID(string agentid);
	string GetAgentID()	
	{
		if(agentIDLen==0)	return "";
		if ( !(VerifyData(agentIDLen, AGENTID_LEN)) ) {return "";}
		return string(agentID);
	}
	void SetTheDepartment(string theDepartment);
	string GetTheDepartment()	
	{
		if(theDepartmentLen==0)	return "";
		if ( !(VerifyData(theDepartmentLen, CORPNDEPT_LEN)) ) {return "";}
		return string(theDepartment);
	}
	
	int natType;
	
	unsigned long lanIP;
	unsigned short lanMainSockPort;
	
	int loginType;
	string agentPhoneNo;
	string nickName;
	int iNeedDisposal;
	int iLoginSuccMode;		//登录成功后座席状态模式

	string  connectPhoneNo;
	string  handleId;

	string extNo;

	string SkillGroupID;
	
	int HaveHBtoACD;
	
private:
	char* agentID;
	int agentIDLen;
	char* theDepartment;
	int theDepartmentLen;
	virtual int GetMyMemSize();
};

///Type_Client_AgentLogout
struct SIPCCMsg_Client_AgentLogout : public SIPCCMsg_Client
{
	SIPCCMsg_Client_AgentLogout();
	~SIPCCMsg_Client_AgentLogout()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(agentID!=NULL)	delete agentID;
		agentID = NULL;
		agentIDLen = 0;
	}
	void SetAgentID(string agentID);
	string GetAgentID()	
	{
		if(agentIDLen==0)	return "";
		if ( !(VerifyData(agentIDLen, AGENTID_LEN)) ) {return "";}
		return string(agentID);
	}
	
	int loginType;

	string  connectPhoneNo;
	string  handleId;

private:
	char* agentID;
	int agentIDLen;
	virtual int GetMyMemSize();
};

// [scq/start/2010-04-23] 
// Type_Client_AgentLogoutDeparts
struct SIPCCMsg_Client_AgentLogoutDeparts : public SIPCCMsg_Client
{
	SIPCCMsg_Client_AgentLogoutDeparts();
	~SIPCCMsg_Client_AgentLogoutDeparts()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if ( NULL!=agentID )	
		{
			delete agentID;
		}
		agentID = NULL;
		agentIDLen = 0;
		
		if( NULL!=theDepartment )	
		{
			delete theDepartment;
		}
		theDepartment = NULL;
		theDepartmentLen = 0;
		
		loginType = LoginType_OnlyWeb;
	}
	void SetAgentID(string agentID);
	string GetAgentID()	
	{
		if ( 0==agentIDLen )	
		{
			return "";
		}
		if ( !(VerifyData(agentIDLen, AGENTID_LEN)) ) {return "";}
		return string(agentID);
	}
	void SetTheDepartment(string theDepartment);
	string GetTheDepartment()	
	{
		if ( 0==theDepartmentLen )	
		{
			return "";
		}
		if ( !(VerifyData(theDepartmentLen, CORPNDEPT_LEN)) ) {return "";}
		return string(theDepartment);
	}
	
	int loginType;
private:
	char* agentID;
	int agentIDLen;
	char* theDepartment;
	int theDepartmentLen;
	virtual int GetMyMemSize();
};
// [scq/end/2010-04-23] 

///Type_Client_AgentPark
struct SIPCCMsg_Client_AgentPark : public SIPCCMsg_Client
{
	SIPCCMsg_Client_AgentPark();
	~SIPCCMsg_Client_AgentPark()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(agentID!=NULL)	delete agentID;
		agentID = NULL;
		agentIDLen = 0;
		if(theDepartment!=NULL)	delete theDepartment;
		theDepartment = NULL;
		theDepartmentLen = 0;		
	}
	void SetAgentID(string agentID);
	string GetAgentID()	
	{
		if(agentIDLen==0)	return "";
		if ( !(VerifyData(agentIDLen, AGENTID_LEN)) ) {return "";}
		return string(agentID);
	}
	void SetTheDepartment(string theDepartment);
	string GetTheDepartment()	
	{
		if(theDepartmentLen==0)	return "";
		if ( !(VerifyData(theDepartmentLen, CORPNDEPT_LEN)) ) {return "";}
		return string(theDepartment);
	}
private:
	char* agentID;
	int agentIDLen;
	char* theDepartment;
	int theDepartmentLen;
	virtual int GetMyMemSize();
};

///Type_Client_AgentUnPark
struct SIPCCMsg_Client_AgentUnPark : public SIPCCMsg_Client
{
	SIPCCMsg_Client_AgentUnPark();
	~SIPCCMsg_Client_AgentUnPark()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(agentID!=NULL)	delete agentID;
		agentID = NULL;
		agentIDLen = 0;
		if(theDepartment!=NULL)	delete theDepartment;
		theDepartment = NULL;
		theDepartmentLen = 0;
	}
	void SetAgentID(string agentID);
	string GetAgentID()	
	{
		if(agentIDLen==0)	return "";
		if ( !(VerifyData(agentIDLen, AGENTID_LEN)) ) {return "";}
		return string(agentID);
	}
	void SetTheDepartment(string theDepartment);
	string GetTheDepartment()	
	{
		if(theDepartmentLen==0)	return "";
		if ( !(VerifyData(theDepartmentLen, CORPNDEPT_LEN)) ) {return "";}
		return string(theDepartment);
	}
private:
	char* agentID;
	int agentIDLen;
	char* theDepartment;
	int theDepartmentLen;
	virtual int GetMyMemSize();
};

///Type_Client_AgentMakeCall
struct SIPCCMsg_Client_AgentMakeCall : public SIPCCMsg_Client
{
	SIPCCMsg_Client_AgentMakeCall();
	~SIPCCMsg_Client_AgentMakeCall()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(callID!=NULL)	delete callID;
		callID = NULL;
		callIDLen = 0;
		if(agentID!=NULL)	delete agentID;
		agentID = NULL;
		agentIDLen = 0;
		if(targetPosition!=NULL)	delete targetPosition;
		targetPosition = NULL;
		targetPositionLen = 0;
		if(uuiData!=NULL)	delete uuiData;
		uuiData = NULL;
		uuiDataLen = 0;
		if(corporationName != NULL)	delete corporationName;
		corporationName = NULL;
		corporationNameLen = 0;
		uuiData2 = "";
		agentUUIData = "";	//  [2/23/2009 lixg]
	}
	void SetCallID(string callid);
	string GetCallID()
	{
		if(callIDLen==0)	return "";
		if ( !(VerifyData(callIDLen, CALLID_LEN)) ) {return "";}
		return string(callID);
	}
	void SetAgentID(string agentid);
	string GetAgentID()
	{
		if(agentIDLen==0)	return "";
		if ( !(VerifyData(agentIDLen, AGENTID_LEN)) ) {return "";}
		return string(agentID);
	}
	void SetTargetPosition(string targetposition);
	string GetTargetPosition()
	{
		if(targetPositionLen==0)	return "";
		if ( !(VerifyData(targetPositionLen, TARGETPOSITION_LEN)) ) {return "";}
		return string(targetPosition);
	}
	void SetUUIData(string uuidata);
	string GetUUIData()	
	{
		if(uuiDataLen==0)	return "";
		if ( !(VerifyData(uuiDataLen, UUIDATA_LEN)) ) {return "";}
		return string(uuiData);
	}
	void SetCorporationName(string corporationname);
	string GetCorporationName()
	{
		if(corporationNameLen==0)	return "";
		if ( !(VerifyData(corporationNameLen, CORPNAME_LEN)) ) {return "";}
		return string(corporationName);
	}
	std::string AgentUUIData() const { return agentUUIData; }	//  [2/23/2009 lixg]
	void AgentUUIData(std::string &val) { agentUUIData = val; }	//  [2/23/2009 lixg]
	
	int targetType;
	
	string callerNoForSend;
	string curVersion;
	
	string userLineNo;
	unsigned long userLineIp;
	unsigned short userLinePort;
	
	string wpAgentID;
	string uuiData2;
	
	string outdialPrefixNo;
	string originalData;		//待转移的原数据
	
	unsigned long sipBoardIP;   //交换机ip板IP
	unsigned short sipBoardRtpPort;  //交换机ip板RtpPort
	unsigned short sipBoardRtcpPort;  //交换机ip板rtcpPort
	unsigned long sipTransIP;   //中转IP
	unsigned short sipTransRtpPort;  //中转RtpPort
	unsigned short sipTransRtcpPort;  //中转rtcpPort
	
	unsigned long sipAgentPhoneIP1;   		//主叫座席端话机IP
	unsigned short sipAgentPhoneRtpPort1;	//主叫座席端话机RtpPort
	unsigned short sipAgentPhoneRtcpPort1;  //主叫座席端话机rtcpPort
	
	string comSymbol;

	string operatorsInfo;
	
	int toAcdOrUserState;	// [scq/2010-06-02] 若是发给ACDServer则赋值为ServerType_ACD，若是发给UserStateServer则赋值为ServerType_UState。

	string managerId;

    CAudioStreamDescription audioStreamDescription;
	
private:
	char* callID;	//座席呼座席、座席呼 skillGroup 用,带给被叫/被分配座席,记报表
	int callIDLen;
	char* agentID;
	int agentIDLen;
	char* targetPosition;
	int targetPositionLen;
	char* uuiData;
	int uuiDataLen;
	char* corporationName;
	int corporationNameLen;
	string agentUUIData;	// 随路数据 [2/23/2009 lixg]
	
	virtual int GetMyMemSize();
};

///Type_Client_AgentMakeCall2
struct SIPCCMsg_Client_AgentMakeCall2 : public SIPCCMsg_Client
{
	SIPCCMsg_Client_AgentMakeCall2();
	~SIPCCMsg_Client_AgentMakeCall2()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(callID!=NULL)	delete callID;
		callID = NULL;
		callIDLen = 0;
		if(agentID!=NULL)	delete agentID;
		agentID = NULL;
		agentIDLen = 0;
		if(targetPosition!=NULL)	delete targetPosition;
		targetPosition = NULL;
		targetPositionLen = 0;
		if(uuiData!=NULL)	delete uuiData;
		uuiData = NULL;
		uuiDataLen = 0;
		if(corporationName != NULL)	delete corporationName;
		corporationName = NULL;
		corporationNameLen = 0;
	}
	void SetCallID(string callid);
	string GetCallID()
	{
		if(callIDLen==0)	return "";
		if ( !(VerifyData(callIDLen, CALLID_LEN)) ) {return "";}
		return string(callID);
	}
	void SetAgentID(string agentid);
	string GetAgentID()
	{
		if(agentIDLen==0)	return "";
		if ( !(VerifyData(agentIDLen, AGENTID_LEN)) ) {return "";}
		return string(agentID);
	}
	void SetTargetPosition(string targetposition);
	string GetTargetPosition()
	{
		if(targetPositionLen==0)	return "";
		if ( !(VerifyData(targetPositionLen, TARGETPOSITION_LEN)) ) {return "";}
		return string(targetPosition);
	}
	void SetUUIData(string uuidata);
	string GetUUIData()	
	{
		if(uuiDataLen==0)	return "";
		if ( !(VerifyData(uuiDataLen, UUIDATA_LEN)) ) {return "";}
		return string(uuiData);
	}
	void SetCorporationName(string corporationname);
	string GetCorporationName()
	{
		if(corporationNameLen==0)	return "";
		if ( !(VerifyData(corporationNameLen, CORPNAME_LEN)) ) {return "";}
		return string(corporationName);
	}
	int targetType;
	
	string callerNoForSend;
	string curVersion;
	string invokeID;
	int usableTime;
	
	unsigned long lanIp;
	
	int calledOperType;
	
	string wpAgentID;
	
	string callTransID;
	
	string managerId;
	string corpName;
	string extPhoneNo;   // 分机号码
	string recordFilePath;   // 录音文件目录名

	string LowLevelPrefixNo;	//出局使用前缀

	string nickName;
	int RecordMode;

	bool		the2nd_dial_valid;
	string		the2nd_dial_digit;
	bool		the3rd_media_valid;//客户端与sip模拟网关直连
	string		the3rd_media_address;//坐席与sip模拟网关直连地址
	unsigned short the3rd_media_port;//坐席使用的RTP语音端口

    CAudioStreamDescription audioStreamDescription;

	string token;	//"token":"xxx"

private:
	char* callID;	//座席呼座席、座席呼 skillGroup 用,带给被叫/被分配座席,记报表
	int callIDLen;
	char* agentID;
	int agentIDLen;
	char* targetPosition;
	int targetPositionLen;
	char* uuiData;
	int uuiDataLen;
	char* corporationName;
	int corporationNameLen;
	
	virtual int GetMyMemSize();
};

///Type_Client_UserMakeCallPSTN
struct SIPCCMsg_Client_UserMakeCallPSTN : public SIPCCMsg_Client
{
	SIPCCMsg_Client_UserMakeCallPSTN();
	~SIPCCMsg_Client_UserMakeCallPSTN()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(callID!=NULL)	delete callID;
		callID = NULL;
		callIDLen = 0;
		if(userName!=NULL)	delete userName;
		userName = NULL;
		userNameLen = 0;
		if(targetPosition!=NULL)	delete targetPosition;
		targetPosition = NULL;
		targetPositionLen = 0;
		if(uuiData!=NULL)	delete uuiData;
		uuiData = NULL;
		uuiDataLen = 0;
		if(corporationName != NULL)	delete corporationName;
		corporationName = NULL;
		corporationNameLen = 0;
	}
	void SetCallID(string callid);
	string GetCallID()
	{
		if(callIDLen==0)	return "";
		if ( !(VerifyData(callIDLen, CALLID_LEN)) ) {return "";}
		return string(callID);
	}
	void SetUserName(string username);
	string GetUserName()
	{
		if(userNameLen==0)	return "";
		if ( !(VerifyData(userNameLen, USERNAME_LEN)) ) {return "";}
		return string(userName);
	}
	void SetTargetPosition(string targetposition);
	string GetTargetPosition()
	{
		if(targetPositionLen==0)	return "";
		if ( !(VerifyData(targetPositionLen, TARGETPOSITION_LEN)) ) {return "";}
		return string(targetPosition);
	}
	void SetUUIData(string uuidata);
	string GetUUIData()	
	{
		if(uuiDataLen==0)	return "";
		if ( !(VerifyData(uuiDataLen, UUIDATA_LEN)) ) {return "";}
		return string(uuiData);
	}
	void SetCorporationName(string corporationname);
	string GetCorporationName()
	{
		if(corporationNameLen==0)	return "";
		if ( !(VerifyData(corporationNameLen, CORPNAME_LEN)) ) {return "";}
		return string(corporationName);
	}
	int targetType;
	
	string callerNoForSend;
	string curVersion;
	
private:
	char* callID;	//座席呼座席、座席呼 skillGroup 用,带给被叫/被分配座席,记报表
	int callIDLen;
	char* userName;
	int userNameLen;
	char* targetPosition;
	int targetPositionLen;
	char* uuiData;
	int uuiDataLen;
	char* corporationName;
	int corporationNameLen;
	
	virtual int GetMyMemSize();
};

///Type_Client_UserMakeCallPSTN2
struct SIPCCMsg_Client_UserMakeCallPSTN2 : public SIPCCMsg_Client
{
	SIPCCMsg_Client_UserMakeCallPSTN2();
	~SIPCCMsg_Client_UserMakeCallPSTN2()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(callID!=NULL)	delete callID;
		callID = NULL;
		callIDLen = 0;
		if(userName!=NULL)	delete userName;
		userName = NULL;
		userNameLen = 0;
		if(targetPosition!=NULL)	delete targetPosition;
		targetPosition = NULL;
		targetPositionLen = 0;
		if(uuiData!=NULL)	delete uuiData;
		uuiData = NULL;
		uuiDataLen = 0;
		if(corporationName != NULL)	delete corporationName;
		corporationName = NULL;
		corporationNameLen = 0;
	}
	void SetCallID(string callid);
	string GetCallID()
	{
		if(callIDLen==0)	return "";
		if ( !(VerifyData(callIDLen, CALLID_LEN)) ) {return "";}
		return string(callID);
	}
	void SetUserName(string username);
	string GetUserName()
	{
		if(userNameLen==0)	return "";
		if ( !(VerifyData(userNameLen, USERNAME_LEN)) ) {return "";}
		return string(userName);
	}
	void SetTargetPosition(string targetposition);
	string GetTargetPosition()
	{
		if(targetPositionLen==0)	return "";
		if ( !(VerifyData(targetPositionLen, TARGETPOSITION_LEN)) ) {return "";}
		return string(targetPosition);
	}
	void SetUUIData(string uuidata);
	string GetUUIData()	
	{
		if(uuiDataLen==0)	return "";
		if ( !(VerifyData(uuiDataLen, UUIDATA_LEN)) ) {return "";}
		return string(uuiData);
	}
	void SetCorporationName(string corporationname);
	string GetCorporationName()
	{
		if(corporationNameLen==0)	return "";
		if ( !(VerifyData(corporationNameLen, CORPNAME_LEN)) ) {return "";}
		return string(corporationName);
	}
	int targetType;
	
	string callerNoForSend;
	string curVersion;
	string invokeID;
	
private:
	char* callID;	//座席呼座席、座席呼 skillGroup 用,带给被叫/被分配座席,记报表
	int callIDLen;
	char* userName;
	int userNameLen;
	char* targetPosition;
	int targetPositionLen;
	char* uuiData;
	int uuiDataLen;
	char* corporationName;
	int corporationNameLen;
	
	virtual int GetMyMemSize();
};

///Type_Client_AgentAnswerCall
struct SIPCCMsg_Client_AgentAnswerCall : public SIPCCMsg_Client
{
	SIPCCMsg_Client_AgentAnswerCall();
	~SIPCCMsg_Client_AgentAnswerCall()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(agentID!=NULL)	delete agentID;
		agentID = NULL;
		agentIDLen = 0;
		if(theOtherParty!=NULL)	delete theOtherParty;
		theOtherParty = NULL;
		theOtherPartyLen = 0;
		theotherPartyType = CallParty_UnKnown;
	}
	void SetAgentID(string agentid);
	string GetAgentID()
	{
		if(agentIDLen==0)	return "";
		if ( !(VerifyData(agentIDLen, AGENTID_LEN)) ) {return "";}
		return string(agentID);
	}
	void SetTheOtherParty(string theotherparty);
	string GetTheOTherParty()	
	{
		if(theOtherPartyLen==0)	return "";
		if ( !(VerifyData(theOtherPartyLen, THEOTHERPARTY_LEN)) ) {return "";}
		return string(theOtherParty);
	}
	
	int theotherPartyType;
	
	string callId;
	
	string managerId;
	string corpName;
	int toAcdOrUserState; // [scq/2010-05-21]
	string extPhoneNo;   // 分机号码
	string recordFilePath;   // 录音文件目录名

	int RecordMode;

	bool	the3rd_media_valid;
	string	the3rd_media_address;
	unsigned short the3rd_media_port;

	string token;	//"token":"xxx"
private:
	char* agentID;
	int agentIDLen;
	char* theOtherParty;
	int theOtherPartyLen;
	virtual int GetMyMemSize();
};

///Type_Client_AgentCallReceived
struct SIPCCMsg_Client_AgentCallReceived : public SIPCCMsg_Client
{
	SIPCCMsg_Client_AgentCallReceived();
	~SIPCCMsg_Client_AgentCallReceived()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(agentID!=NULL)	delete agentID;
		agentID = NULL;
		agentIDLen = 0;
		if(theOtherParty!=NULL)	delete theOtherParty;
		theOtherParty = NULL;
		theOtherPartyLen = 0;
	}
	void SetAgentID(string agentid);
	string GetAgentID()
	{
		if(agentIDLen==0)	return "";
		if ( !(VerifyData(agentIDLen, AGENTID_LEN)) ) {return "";}
		return string(agentID);
	}
	void SetTheOtherParty(string oppname);
	string GetTheOtherParty()	
	{
		if(theOtherPartyLen==0)	return "";
		if ( !(VerifyData(theOtherPartyLen, THEOTHERPARTY_LEN)) ) {return "";}
		return string(theOtherParty);
	}
	
	unsigned long lanIp;
	
	string agentExtNo;
	
	unsigned long sipAgentPhoneIP1;   		//主叫座席端话机IP
	unsigned short sipAgentPhoneRtpPort1;	//主叫座席端话机RtpPort
	unsigned short sipAgentPhoneRtcpPort1;  //主叫座席端话机rtcpPort
	
	int toAcdOrUserState;	// [scq/2010-05-21] 目的地类型

	string nickName;
	
    CAudioStreamDescription audioStreamDescription;
private:
	char* agentID;
	int agentIDLen;
	char* theOtherParty;	//对方名称(userName/agentID)
	int theOtherPartyLen;
	
	virtual int GetMyMemSize();
};

///Type_Client_AgentHangupCall
struct SIPCCMsg_Client_AgentHangupCall : public SIPCCMsg_Client
{
	SIPCCMsg_Client_AgentHangupCall();
	~SIPCCMsg_Client_AgentHangupCall()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(agentID!=NULL)	delete agentID;
		agentID = NULL;
		agentIDLen = 0;
		if(theOtherParty!=NULL)	delete theOtherParty;
		theOtherParty = NULL;
		theOtherPartyLen = 0;
		if(callID!=NULL)	delete callID;
		callID = NULL;
		callIDLen = 0;
		agentJoinType = AgentJoin_UnKnown;
		bAgentAssigned = 0;
	}
	void SetAgentID(string agentid);
	string GetAgentID()
	{
		if(agentIDLen==0)	return "";
		if ( !(VerifyData(agentIDLen, AGENTID_LEN)) ) {return "";}
		return string(agentID);
	}
	void SetTheOtherParty(string oppname);
	string GetTheOtherParty()
	{
		if(theOtherPartyLen==0)	return "";
		if ( !(VerifyData(theOtherPartyLen, THEOTHERPARTY_LEN)) ) {return "";}
		return string(theOtherParty);
	}
	void SetCallID(string callid);
	string GetCallID()
	{
		if(callIDLen==0)	return "";
		if ( !(VerifyData(callIDLen, CALLID_LEN)) ) {return "";}
		return string(callID);
	}
	int agentJoinType;
	char bAgentAssigned;
	int toAcdOrUserState;	// [scq/2010-05-21] 区分类型
private:
	char* agentID;
	int agentIDLen;
	char* theOtherParty;
	int theOtherPartyLen;
	char* callID;	//呼网关
	int callIDLen;
	virtual int GetMyMemSize();
};

///Type_Client_MediaRequest
struct SIPCCMsg_Client_MediaRequest : public SIPCCMsg_Client
{
	SIPCCMsg_Client_MediaRequest();
	~SIPCCMsg_Client_MediaRequest()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(callID!=NULL)	delete callID;
		callID = NULL;
		callIDLen = 0;
		if(targetName!=NULL)	delete targetName;
		targetName = NULL;
		targetNameLen = 0;
		mediaType = -1;
	}
	void SetCallID(string callid);
	string GetCallID()	
	{
		if(callIDLen==0)	return "";
		if ( !(VerifyData(callIDLen, CALLID_LEN)) ) {return "";}
		return string(callID);
	}
	void SetTargetName(string targetname);
	string GetTargetName()	
	{
		if(targetNameLen==0)	return "";
		if ( !(VerifyData(targetNameLen, TARGETNAME_LEN)) ) {return "";}
		return string(targetName);
	}
	
	int mediaType;
	int seq;
	int toAcdOrUserState;	// [scq/2010-05-21]

	string  account;              //发起方账号
	unsigned long transmitServerIP;    //指定使用的transmitserver ip
	unsigned short transmitServerPort;  //指定使用的transmitserver port
	string  netPath;              //网络路径

private:
	char* callID;
	int callIDLen;
	char* targetName;
	int targetNameLen;
	virtual int GetMyMemSize();
};

///Type_Client_MediaRequestConf
struct SIPCCMsg_Client_MediaRequestConf : public SIPCCMsg_Client
{
	SIPCCMsg_Client_MediaRequestConf();
	~SIPCCMsg_Client_MediaRequestConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(callID!=NULL)	delete callID;
		callID = NULL;
		callIDLen = 0;
		mediaType = -1;
	}
	void SetCallID(string callid);
	string GetCallID()	
	{
		if(callIDLen==0)	return "";
		return string(callID);
	}
	
	int mediaType;
private:
	char* callID;
	int callIDLen;
	virtual int GetMyMemSize();
};

///Type_Client_TextChatWords
struct SIPCCMsg_Client_TextChatWords : public SIPCCMsg_Client
{
	SIPCCMsg_Client_TextChatWords();
	~SIPCCMsg_Client_TextChatWords()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(chatWords!=NULL)	delete chatWords;
		chatWords = NULL;
		chatWordsLen = 0;
	}
	
	void SetChatWords(string chatwords);
	string GetChatWords()
	{
		if(chatWordsLen==0)	return "";
		return string(chatWords);
	}
private:
	char* chatWords;
	int chatWordsLen;
	virtual int GetMyMemSize();
};

///Type_Client_MediaReady
struct SIPCCMsg_Client_MediaReady : public SIPCCMsg_Client
{
	SIPCCMsg_Client_MediaReady();
	~SIPCCMsg_Client_MediaReady()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(targetName!=NULL)	delete targetName;
		targetName = NULL;
		targetNameLen = 0;
	}
	
	void SetTargetName(string targetname);
	string GetTargetName()	
	{
		if(targetNameLen==0)	return "";
		if ( !(VerifyData(targetNameLen, TARGETNAME_LEN)) ) {return "";}
		return string(targetName);
	}
	
	int toAcdOrUserState;	// [scq/2010-05-24] 目的地类型
	
private:
	virtual int GetMyMemSize();
	char* targetName;
	int targetNameLen;
};

///Type_Client_GetCallingQueueInfo
struct SIPCCMsg_Client_GetCallingQueueInfo : public SIPCCMsg_Client
{
	SIPCCMsg_Client_GetCallingQueueInfo();
	~SIPCCMsg_Client_GetCallingQueueInfo()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(theDepartment!=NULL)	delete theDepartment;
		theDepartment = NULL;
		theDepartmentLen = 0;
		if(userName!=NULL)	delete userName;
		userName = NULL;
		userNameLen = 0;
	}
	void SetTheDepartment(string theDepartment);
	string GetTheDepartment()	
	{
		if(theDepartmentLen==0)	return "";
		if ( !(VerifyData(theDepartmentLen, CORPNDEPT_LEN)) ) {return "";}
		return string(theDepartment);
	}
	void SetUserName(string userName);
	string GetUserName()	
	{
		if(userNameLen==0)	return "";
		if ( !(VerifyData(userNameLen, USERNAME_LEN)) ) {return "";}
		return string(userName);
	}
	
	string invokeID;
	
private:
	char* theDepartment;
	int theDepartmentLen;
	char* userName;
	int userNameLen;
	virtual int GetMyMemSize();
};

///Type_Client_AgentQueryState
struct SIPCCMsg_Client_AgentQueryState : public SIPCCMsg_Client
{
	SIPCCMsg_Client_AgentQueryState();
	~SIPCCMsg_Client_AgentQueryState()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(agentID!=NULL)	delete agentID;
		agentID = NULL;
		agentIDLen = 0;
		if (parkReason != NULL) delete parkReason;
		parkReason = NULL;
		parkReasonLen = 0;
		agentState = Agent_NoLogin;
	}
	void SetAgentID(string agentid);
	string GetAgentID()
	{
		if(agentIDLen==0)	return "";
		if ( !(VerifyData(agentIDLen, AGENTID_LEN)) ) {return "";}
		return string(agentID);
	}
	
	int agentState;
	char bPSTNCall;		//pstnCall
	char bInnerCall;	//内部，外部
	int  parkReasonID;		//id
	string comSymbol;
	string newAgentPhoneNo;

	string GetParkReason()  //具体原因
	{
		if (parkReasonLen == 0) return "";
		if ( !(VerifyData(parkReasonLen, PARKREASON_LEN)) ) {return "";}
		return string(parkReason);
	}		
	void SetParkReason(string parkreason)
	{
		int iAgentIDLen = parkreason.length();
		parkReasonLen = iAgentIDLen + 1;
		parkReason = new char[parkReasonLen];
		memset(parkReason, 0, parkReasonLen);
		memcpy(parkReason, parkreason.c_str(), iAgentIDLen);
	}
	string handleId;		//操作唯一标识
private:
	char* agentID;
	int agentIDLen;
	int parkReasonLen;
	char *parkReason;
	
	virtual int GetMyMemSize();
};

///Type_Client_UserQueryState
struct SIPCCMsg_Client_UserQueryState : public SIPCCMsg_Client
{
	SIPCCMsg_Client_UserQueryState();
	~SIPCCMsg_Client_UserQueryState()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(userName!=NULL)	delete userName;
		userName = NULL;
		userNameLen = 0;
		userState = -1;
	}
	void SetUserName(string userName);
	string GetUserName()	
	{
		if(userNameLen==0)	return "";
		if ( !(VerifyData(userNameLen, USERNAME_LEN)) ) {return "";}
		return string(userName);
	}
	
	int userState;
private:
	char* userName;
	int userNameLen;
	
	virtual int GetMyMemSize();
};

///Type_Client_UserReset
struct SIPCCMsg_Client_UserReset : public SIPCCMsg_Client
{
	SIPCCMsg_Client_UserReset();
	~SIPCCMsg_Client_UserReset()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(userName!=NULL)	delete userName;
		userName = NULL;
		userNameLen = 0;
	}
	void SetUserName(string userName);
	string GetUserName()	
	{
		if(userNameLen==0)	return "";
		if ( !(VerifyData(userNameLen, USERNAME_LEN)) ) {return "";}
		return string(userName);
	}
	
	int toAcdOrUserState;	// [scq/2010-05-21] 目的地类型
	
private:
	char* userName;
	int userNameLen;
	
	virtual int GetMyMemSize();
};

///Type_Client_AgentReset
struct SIPCCMsg_Client_AgentReset : public SIPCCMsg_Client
{
	SIPCCMsg_Client_AgentReset();
	~SIPCCMsg_Client_AgentReset()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(agentID!=NULL)	delete agentID;
		agentID = NULL;
		agentIDLen = 0;
	}
	void SetAgentID(string agentid);
	string GetAgentID()
	{
		if(agentIDLen==0)	return "";
		if ( !(VerifyData(agentIDLen, AGENTID_LEN)) ) {return "";}
		return string(agentID);
	}
private:
	char* agentID;
	int agentIDLen;
	
	virtual int GetMyMemSize();
};

///Type_Client_UserLoginStateSvr
struct SIPCCMsg_Client_UserLoginStateSvr : public SIPCCMsg_Client
{
	SIPCCMsg_Client_UserLoginStateSvr();	
	~SIPCCMsg_Client_UserLoginStateSvr()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(userName!=NULL)	delete userName;
		userName = NULL;
		userNameLen = 0;
		natType = NatType_Unknown;
	}
	void SetUserName(string userName);
	string GetUserName()	
	{
		if(userNameLen==0)	return "";
		if ( !(VerifyData(userNameLen, USERNAME_LEN)) ) {return "";}
		return string(userName);
	}
	
	int natType;
	unsigned long localIP;
	unsigned short localPort;

	string GwName;
	string ComputerSymbol;
	string allUserName;
	int	indexNum;

	unsigned long wanIP;
	unsigned short wanPort;

	string handleId;

	int totalIndex;

private:
	char* userName;
	int userNameLen;
	
	virtual int GetMyMemSize();
};

//Type_Client_UserLogoutStateSvr
struct SIPCCMsg_Client_UserLogoutStateSvr : public SIPCCMsg_Client
{
	SIPCCMsg_Client_UserLogoutStateSvr();
	~SIPCCMsg_Client_UserLogoutStateSvr()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(userName!=NULL)	delete userName;
		userName = NULL;
		userNameLen = 0;
	}
	void SetUserName(string userName);
	string GetUserName()	
	{
		if(userNameLen==0)	return "";
		if ( !(VerifyData(userNameLen, USERNAME_LEN)) ) {return "";}
		return string(userName);
	}
	
private:
	char* userName;
	int userNameLen;
	
	virtual int GetMyMemSize();
};

//Type_Client_UserAnswerCall
struct SIPCCMsg_Client_UserAnswerCall : public SIPCCMsg_Client
{
	SIPCCMsg_Client_UserAnswerCall();
	~SIPCCMsg_Client_UserAnswerCall()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(userName!=NULL)	delete userName;
		userName = NULL;
		userNameLen = 0;
		if(theOtherParty!=NULL) delete theOtherParty;
		theOtherParty = NULL;
		theOtherPartyLen = 0;
		theotherPartyType = CallParty_UnKnown;
	}
	void SetUserName(string userName);
	string GetUserName()	
	{
		if(userNameLen==0)	return "";
		if ( !(VerifyData(userNameLen, USERNAME_LEN)) ) {return "";}
		return string(userName);
	}
	void SetTheOtherParty(string theotherparty);
	string GetTheOTherParty()	
	{
		if(theOtherPartyLen==0)	return "";
		if ( !(VerifyData(theOtherPartyLen, THEOTHERPARTY_LEN)) ) {return "";}
		return string(theOtherParty);
	}
	
	int theotherPartyType;
	int outDialType;
	
	string userLineNo;
	unsigned long userLineIp;
	unsigned short userLinePort;
	
	int toAcdOrUserState;	// [scq/2010-05-24] 目的地类型
	
	string  managerId;
	string  connectPhoneNo;
	string  handleId;
	string privateData;			//私有数据字符串，填写WebPSTNDial的相关信息
	int lineType;				//0是客户，1是座席

    CAudioStreamDescription audioStreamDescription;

	string netPath;

private:
	char* userName;
	int userNameLen;
	char* theOtherParty;
	
	int theOtherPartyLen;
	virtual int GetMyMemSize();
};

//Type_Client_UserAnswerCall_Real
struct SIPCCMsg_Client_UserAnswerCall_Real : public SIPCCMsg_Client
{
	SIPCCMsg_Client_UserAnswerCall_Real();
	~SIPCCMsg_Client_UserAnswerCall_Real()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(userName!=NULL)	delete userName;
		userName = NULL;
		userNameLen = 0;
		if(theOtherParty!=NULL) delete theOtherParty;
		theOtherParty = NULL;
		theOtherPartyLen = 0;
		theotherPartyType = CallParty_UnKnown;
	}
	void SetUserName(string userName);
	string GetUserName()	
	{
		if(userNameLen==0)	return "";
		if ( !(VerifyData(userNameLen, USERNAME_LEN)) ) {return "";}
		return string(userName);
	}
	void SetTheOtherParty(string theotherparty);
	string GetTheOTherParty()	
	{
		if(theOtherPartyLen==0)	return "";
		if ( !(VerifyData(theOtherPartyLen, THEOTHERPARTY_LEN)) ) {return "";}
		return string(theOtherParty);
	}
	
	int theotherPartyType;
	int outDialType;
	
	string userLineNo;
	unsigned long userLineIp;
	unsigned short userLinePort;

	string  managerId;
	string  connectPhoneNo;
	string  handleId;

	string netPath;

private:
	char* userName;
	int userNameLen;
	char* theOtherParty;
	
	int theOtherPartyLen;
	virtual int GetMyMemSize();
};

//Type_ACD_CallEstablished_Real
struct SIPCCMsg_ACD_CallEstablished_Real : public SIPCCMsg_Client
{
	SIPCCMsg_ACD_CallEstablished_Real();
	~SIPCCMsg_ACD_CallEstablished_Real()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(userName!=NULL)	delete userName;
		userName = NULL;
		userNameLen = 0;
		if(theOtherParty!=NULL) delete theOtherParty;
		theOtherParty = NULL;
		theOtherPartyLen = 0;
		theotherPartyType = CallParty_UnKnown;
	}
	void SetUserName(string userName);
	string GetUserName()	
	{
		if(userNameLen==0)	return "";
		return string(userName);
	}
	void SetTheOtherParty(string theotherparty);
	string GetTheOTherParty()	
	{
		if(theOtherPartyLen==0)	return "";
		return string(theOtherParty);
	}
	
	int theotherPartyType;
	int outDialType;
	
	string userLineNo;
	unsigned long userLineIp;
	unsigned short userLinePort;
private:
	char* userName;
	int userNameLen;
	char* theOtherParty;
	
	int theOtherPartyLen;
	virtual int GetMyMemSize();
};

///Type_Client_CallUserConf
struct SIPCCMsg_Client_CallUserConf : public SIPCCMsg_Client
{
	SIPCCMsg_Client_CallUserConf();
	~SIPCCMsg_Client_CallUserConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(userName!=NULL)	delete userName;	
		userName = NULL;
		userNameLen = 0;
		if(callerParty!=NULL)	delete callerParty;
		callerParty = NULL;
		callerPartyLen = 0;
		bCallFailed = 1;
		audioIP = 0;
		audioPort = 0;
		if(calledNo!=NULL)	delete calledNo;
		calledNo = NULL;
		calledNoLen = 0;
		sipBoardIP = 0;   //交换机ip板IP
		sipBoardRtpPort = 0;  //交换机ip板RtpPort
		sipBoardRtcpPort = 0;  //交换机ip板rtcpPort
		sipTransIP = 0;   //中转IP
		sipTransRtpPort = 0;  //中转RtpPort
		sipTransRtcpPort = 0;  //中转rtcpPort
		
		trans = "";
		codec = "";
		unit = 0;
		
	}
	void SetUserName(string username);
	string GetUserName()
	{
		if(userNameLen == 0)			return "";
		if ( !(VerifyData(userNameLen, USERNAME_LEN)) ) {return "";}
		return string(userName);
	}
	void SetCallerParty(string callerparty);
	string GetCallerParty()
	{
		if(callerPartyLen==0)	return "";
		if ( !(VerifyData(callerPartyLen, CALLERPARTY_LEN)) ) {return "";}
		return string(callerParty);
	}
	void SetCalledNo(string calledno);
	string GetCalledNo()
	{
		if(calledNoLen==0)	return "";
		if ( !(VerifyData(calledNoLen, CALLEDNO_LEN)) ) {return "";}
		return string(calledNo);
	}
	
	int failedCause;
	char bCallFailed;
	unsigned long audioIP;
	unsigned short audioPort;
	unsigned long lanIP;
	
	string invokeID;
	
	int outDialType;
	
	unsigned long sipBoardIP;   //交换机ip板IP
	unsigned short sipBoardRtpPort;  //交换机ip板RtpPort
	unsigned short sipBoardRtcpPort;  //交换机ip板rtcpPort
	unsigned long sipTransIP;   //中转IP
	unsigned short sipTransRtpPort;  //中转RtpPort
	unsigned short sipTransRtcpPort;  //中转rtcpPort
	
	int toAcdOrUserState;	// [scq/2010-05-24] 目的地类型

	string  managerId;
	string  connectPhoneNo;

	unsigned short conferencePort1;		//座席端用于会议的端口1
	unsigned short conferencePort2;		//座席端用于会议的端口2

	string netPath;
	
private:
	char* userName;
	int userNameLen;
	char* callerParty;
	int callerPartyLen;
	char* calledNo;
	int calledNoLen;
	
	virtual int GetMyMemSize();
	
public:
	/////////////////媒体信息描述/////////////////
	//传输方式，决定包格式
	//UDP/OLD	固定长度包，根据协商的编码和单位时间决定包长度
	//UDP/V1	变长包，包自身可以表述负载大小，暂时不用
	string trans;
	//编码方式
	//G729
	//ILBC
	string codec;
	//单位时间
	size_t unit;
	///////////////////////////////////////////////
public:	
	 string calleeNo;
};

///Type_Client_CallUserFailed
struct SIPCCMsg_Client_CallUserFailed : public SIPCCMsg_Client
{
	SIPCCMsg_Client_CallUserFailed();
	~SIPCCMsg_Client_CallUserFailed()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(userName!=NULL)	delete userName;	
		userName = NULL;
		userNameLen = 0;
		if(callerParty!=NULL)	delete callerParty;
		callerParty = NULL;
		callerPartyLen = 0;
		if(calledNo!=NULL)	delete calledNo;
		calledNo = NULL;
		calledNoLen = 0;
	}
	void SetUserName(string username);
	string GetUserName()
	{
		if(userNameLen == 0)			return "";
		if ( !(VerifyData(userNameLen, USERNAME_LEN)) ) {return "";}
		return string(userName);
	}
	void SetCallerParty(string vallerparty);
	string GetCallerParty()
	{
		if(callerPartyLen==0)	return "";
		if ( !(VerifyData(callerPartyLen, CALLERPARTY_LEN)) ) {return "";}
		return string(callerParty);
	}
	void SetCalledNo(string calledno);
	string GetCalledNo()
	{
		if(calledNoLen==0)	return "";
		if ( !(VerifyData(calledNoLen, CALLEDNO_LEN)) ) {return "";}
		return string(calledNo);
	}
	
	int failedCause;
	int outDialType;
	int toAcdOrUserState;	// [scq/2010-05-24] 目的地类型

	string  managerId;
	string  connectPhoneNo;
	
private:
	char* userName;
	int userNameLen;
	char* callerParty;
	int callerPartyLen;
	char* calledNo;
	int calledNoLen;
	
	virtual int GetMyMemSize();
};

///Type_Client_AgentHoldCall
struct SIPCCMsg_Client_AgentHoldCall : public SIPCCMsg_Client
{
	SIPCCMsg_Client_AgentHoldCall();
	~SIPCCMsg_Client_AgentHoldCall()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(heldParty!=NULL)	delete heldParty;	
		heldParty = NULL;
		heldPartyLen = 0;
	}
	void SetHeldParty(string heldparty);
	string GetHeldParty()
	{
		if(heldPartyLen == 0)			return "";
		if ( !(VerifyData(heldPartyLen, THEPARTY_LEN)) ) {return "";}
		return string(heldParty);
	}
	
	string ManagerID;
	int toAcdOrUserState;	// [scq/2010-05-24] 目的地类型
	
private:
	char* heldParty;
	int heldPartyLen;
	
	virtual int GetMyMemSize();
};

///Type_Client_AgentUnHoldCall
struct SIPCCMsg_Client_AgentUnHoldCall : public SIPCCMsg_Client
{
	SIPCCMsg_Client_AgentUnHoldCall();
	~SIPCCMsg_Client_AgentUnHoldCall()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(heldParty!=NULL)	delete heldParty;	
		heldParty = NULL;
		heldPartyLen = 0;
	}
	void SetHeldParty(string heldparty);
	string GetHeldParty()
	{
		if(heldPartyLen == 0)			return "";
		if ( !(VerifyData(heldPartyLen, THEPARTY_LEN)) ) {return "";}
		return string(heldParty);
	}
	
	int toAcdOrUserState;	// [scq/2010-05-24] 目的地类型
	
private:
	char* heldParty;
	int heldPartyLen;
	
	virtual int GetMyMemSize();
};

///Type_Client_QueryRouteTactic
struct SIPCCMsg_Client_QueryRouteTactic : public SIPCCMsg_Client
{
	SIPCCMsg_Client_QueryRouteTactic();
	~SIPCCMsg_Client_QueryRouteTactic()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(userName!=NULL)	delete userName;	
		userName = NULL;
		userNameLen = 0;
		if(theCorporation!=NULL)	delete theCorporation;	
		theCorporation = NULL;
		theCorporationLen = 0;
		if(routeDest!=NULL)	delete routeDest;	
		routeDest = NULL;
		routeDestLen = 0;
	}
	void SetUserName(string username);
	string GetUserName()
	{
		if(userNameLen == 0)			return "";
		return string(userName);
	}
	
	void SetTheCorporation(string thecorporation);
	string GetTheCorporation()
	{
		if(theCorporationLen == 0)			return "";
		return string(theCorporation);
	}
	
	void SetRouteDest(string routedest);
	string GetRouteDest()
	{
		if(routeDestLen == 0)			return "";
		return string(routeDest);
	}
	
private:
	char* userName;
	int userNameLen;
	char* theCorporation;
	int theCorporationLen;
	char* routeDest;
	int routeDestLen;
	
	virtual int GetMyMemSize();
};

///Type_Client_PrepareTransfer
struct SIPCCMsg_Client_PrepareTransfer : public SIPCCMsg_Client
{
	SIPCCMsg_Client_PrepareTransfer();
	~SIPCCMsg_Client_PrepareTransfer()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(callID!=NULL)	delete callID;	
		callID = NULL;
		callIDLen = 0;
		if(otherParty!=NULL)	delete otherParty;	
		otherParty = NULL;
		otherPartyLen = 0;
		if(theParty!=NULL)	delete theParty;	
		theParty = NULL;
		thePartyLen = 0;
	}
	void SetCallID(string callid);
	string GetCallID()
	{
		if(callIDLen == 0)			return "";
		if ( !(VerifyData(callIDLen, CALLID_LEN)) ) {return "";}
		return string(callID);
	}
	void SetTheParty(string theparty);
	string GetTheParty()
	{
		if(thePartyLen == 0)			return "";
		if ( !(VerifyData(thePartyLen, THEPARTY_LEN)) ) {return "";}
		return string(theParty);
	}
	void SetOtherParty(string otherParty);
	string GetOtherParty()
	{
		if(otherPartyLen == 0)			return "";
		if ( !(VerifyData(otherPartyLen, OTHERPARTY_LEN)) ) {return "";}
		return string(otherParty);
	}
public:
	int otherPartyType;
	unsigned long AudioIp;
	unsigned short AudioPort;
	unsigned long lanIP;
	int toAcdOrUserState;	// [scq/2010-05-24] 目的地类型
private:
	char* callID;
	int callIDLen;
	char* theParty;
	int thePartyLen;
	char* otherParty;
	int otherPartyLen;
	
	virtual int GetMyMemSize();
};

///Type_Client_TransReady
struct SIPCCMsg_Client_TransReady : public SIPCCMsg_Client
{
	SIPCCMsg_Client_TransReady();
	~SIPCCMsg_Client_TransReady()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(presideAgent!=NULL)	delete presideAgent;	
		presideAgent = NULL;
		presideAgentLen = 0;
		if(readyParty!=NULL)	delete readyParty;	
		readyParty = NULL;
		readyPartyLen = 0;
	}
	
	void SetPresideAgent(string presideagent);
	string GetPresideAgent()
	{
		if(presideAgentLen == 0)			return "";
		if ( !(VerifyData(presideAgentLen, PRESIDEAGENT_LEN)) ) {return "";}
		return string(presideAgent);
	}
	void SetReadyParty(string readyparty);
	string GetReadyParty()
	{
		if(readyPartyLen == 0)			return "";
		if ( !(VerifyData(readyPartyLen, READYPARTY_LEN)) ) {return "";}
		return string(readyParty);
	}
	
	int toAcdOrUserState;	// [scq/2010-05-24] 目的地类型
	
private:
	char* presideAgent;
	int presideAgentLen;
	char* readyParty;
	int readyPartyLen;
	
	virtual int GetMyMemSize();
};

///Type_Client_TransferCall
struct SIPCCMsg_Client_TransferCall : public SIPCCMsg_Client
{
	SIPCCMsg_Client_TransferCall();
	~SIPCCMsg_Client_TransferCall()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(theParty!=NULL)	delete theParty;	
		theParty = NULL;
		thePartyLen = 0;
		if(presideAgent!=NULL)	delete presideAgent;	
		presideAgent = NULL;
		presideAgentLen = 0;
		if(otherParty!=NULL)	delete otherParty;	
		otherParty = NULL;
		otherPartyLen = 0;
	}
	
	void SetTheParty(string theparty);
	string GetTheParty()
	{
		if(thePartyLen == 0)			return "";
		if ( !(VerifyData(thePartyLen, THEPARTY_LEN)) ) {return "";}
		return string(theParty);
	}
	void SetPresideAgent(string presideagent);
	string GetPresideAgent()
	{
		if(presideAgentLen == 0)			return "";
		if ( !(VerifyData(presideAgentLen, PRESIDEAGENT_LEN)) ) {return "";}
		return string(presideAgent);
	}
	void SetOtherParty(string otherparty);
	string GetOtherParty()
	{
		if(otherPartyLen == 0)			return "";
		if ( !(VerifyData(otherPartyLen, OTHERPARTY_LEN)) ) {return "";}
		return string(otherParty);
	}
public:
	int otherPartyType;
	
	string userLineNo;
	unsigned long userLineIp;
	unsigned short userLinePort;
	
	int thePartyType;
	string agentUUIData;
	
	char needReturn;
	char IsWebPSTNAgent;
	
	int toAcdOrUserState;	// [scq/2010-05-24] 目的地
private:
	char* theParty;
	int thePartyLen;
	char* presideAgent;
	int presideAgentLen;
	char* otherParty;
	int otherPartyLen;
	
	virtual int GetMyMemSize();
	
public:
	/////////////////媒体信息描述/////////////////
	//传输方式，决定包格式
	//UDP/OLD	固定长度包，根据协商的编码和单位时间决定包长度
	//UDP/V1	变长包，包自身可以表述负载大小，暂时不用
	string trans;
	//编码方式
	//G729
	//ILBC
	string codec;
	//单位时间
	size_t unit;
	///////////////////////////////////////////////
};

///Type_Client_BeforeTransfer
struct SIPCCMsg_Client_BeforeTransfer : public SIPCCMsg_Client
{
	SIPCCMsg_Client_BeforeTransfer();
	~SIPCCMsg_Client_BeforeTransfer()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(theParty!=NULL)	delete theParty;	
		theParty = NULL;
		thePartyLen = 0;
		if(presideAgent!=NULL)	delete presideAgent;	
		presideAgent = NULL;
		presideAgentLen = 0;
		if(otherParty!=NULL)	delete otherParty;	
		otherParty = NULL;
		otherPartyLen = 0;
	}
	
	void SetTheParty(string theparty);
	string GetTheParty()
	{
		if(thePartyLen == 0)			return "";
		if ( !(VerifyData(thePartyLen, THEPARTY_LEN)) ) {return "";}
		return string(theParty);
	}
	void SetPresideAgent(string presideagent);
	string GetPresideAgent()
	{
		if(presideAgentLen == 0)			return "";
		if ( !(VerifyData(presideAgentLen, PRESIDEAGENT_LEN)) ) {return "";}
		return string(presideAgent);
	}
	void SetOtherParty(string otherparty);
	string GetOtherParty()
	{
		if(otherPartyLen == 0)			return "";
		if ( !(VerifyData(otherPartyLen, OTHERPARTY_LEN)) ) {return "";}
		return string(otherParty);
	}
public:
	int otherPartyType;
	int toAcdOrUserState;	// [scq/2010-05-24] 目的地类型
	
private:
	char* theParty;
	int thePartyLen;
	char* presideAgent;
	int presideAgentLen;
	char* otherParty;
	int otherPartyLen;
	
	virtual int GetMyMemSize();
};

///Type_Client_ClearPreConnection
struct SIPCCMsg_Client_ClearPreConnection : public SIPCCMsg_Client
{
	SIPCCMsg_Client_ClearPreConnection();
	~SIPCCMsg_Client_ClearPreConnection()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(notifiedParty!=NULL)	delete notifiedParty;	
		notifiedParty = NULL;
		notifiedPartyLen = 0;
		
		if(notifier!=NULL)	delete notifier;	
		notifier = NULL;
		notifierLen = 0;
	}
	
	void SetNotifiedParty(string notifiedparty);
	string GetNotifiedParty()
	{
		if(notifiedPartyLen == 0)			return "";
		if ( !(VerifyData(notifiedPartyLen, NOTIFIEDPARTY_LEN)) ) {return "";}
		return string(notifiedParty);
	}
	
	void SetNotifier(string theNotifier);
	string GetNotifier()
	{
		if(notifierLen == 0)			return "";
		if ( !(VerifyData(notifierLen, NOTIFIER_LEN)) ) {return "";}
		return string(notifier);
	}
	
	int toAcdOrUserState;	// [scq/2010-05-24] 目的地类型
	
private:
	char* notifiedParty;
	int notifiedPartyLen;
	
	char* notifier;
	int notifierLen;
	
	virtual int GetMyMemSize();
};

///SIPCCMsg_Client_AgentTestNet
struct SIPCCMsg_Client_AgentTestNet : public SIPCCMsg_Client
{
	SIPCCMsg_Client_AgentTestNet();
	~SIPCCMsg_Client_AgentTestNet()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(oppName!=NULL)	delete oppName;	
		oppName = NULL;
		oppNameLen = 0;
	}
	void SetOppName(string oppname);
	string GetOppName()
	{
		if(oppNameLen == 0)			return "";
		return string(oppName);
	}
private:
	char* oppName;
	int oppNameLen;
	virtual int GetMyMemSize();
};

///Type_Client_AgentTestNetConf
struct SIPCCMsg_Client_AgentTestNetConf : public SIPCCMsg_Client
{
	SIPCCMsg_Client_AgentTestNetConf();
	~SIPCCMsg_Client_AgentTestNetConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(oppName!=NULL)	delete oppName;	
		oppName = NULL;
		oppNameLen = 0;
	}
	void SetOppName(string oppname);
	string GetOppName()
	{
		if(oppNameLen == 0)			return "";
		return string(oppName);
	}
private:
	char* oppName;
	int oppNameLen;
	virtual int GetMyMemSize();
};

///Type_Client_LanPortApprize
struct SIPCCMsg_Client_LanPortApprize : public SIPCCMsg_Client
{
	SIPCCMsg_Client_LanPortApprize();
	~SIPCCMsg_Client_LanPortApprize()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	unsigned short lanTextPort;
	unsigned short lanAudioPort;
private:
	virtual int GetMyMemSize();
};

///Type_Client_QueryGW
struct SIPCCMsg_Client_QueryGW : public SIPCCMsg_Client
{
	SIPCCMsg_Client_QueryGW();
	~SIPCCMsg_Client_QueryGW()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}

	string corporationName;
	string departName;
	string calledNo;
	string sPrefix;		//座席拨号前缀
	string sPhoneNum;   //座席呼叫号码，未组合前缀的号码
	string sAreaCode;   //区位码服务器上匹配的结果。如果此值为空，就代表区位码服务器没有找到匹配结果或者客户端没有收到区位码服务器匹配结果
	int iMatchResult;   //0代表区位码服务器匹配结果是依据前缀得出的，1代表区位码服务器匹配结果是依据座席呼叫号码得出的。
	int internationalCallUnallowed;	//1代表不允许国际长途  0代表允许国际长途
	int iUseBackupTG;	//0代表不指定使用备份中继组，1代表指定使用
	int TGRouteType;		//默认为0，为1时表示使用按运营商选择中继组功能；
	string operatorsInfo;	//外拨号码的所属运营商，可选"移动、联通、电信"
	string agentID;

	int calloutByIAD;

	int haveCallerNoQuestion;
	string callerNoForSend;

private:
	virtual int GetMyMemSize();
};

///Type_Client_QueryGWLanInfo
struct SIPCCMsg_Client_QueryGWLanInfo : public SIPCCMsg_Client
{
	SIPCCMsg_Client_QueryGWLanInfo();
	~SIPCCMsg_Client_QueryGWLanInfo()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	string corpName;
	string deptName;
	
private:
	virtual int GetMyMemSize();
};

///Type_Client_LoginToText
struct SIPCCMsg_Client_LoginToText : public SIPCCMsg_Client
{
	SIPCCMsg_Client_LoginToText();
	~SIPCCMsg_Client_LoginToText()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	string UserName;
private:
	virtual int GetMyMemSize();
};

///Type_Client_LogoutFromText
struct SIPCCMsg_Client_LogoutFromText : public SIPCCMsg_Client
{
	SIPCCMsg_Client_LogoutFromText();
	~SIPCCMsg_Client_LogoutFromText()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	string UserName;
private:
	virtual int GetMyMemSize();
};

///Type_Client_TextChat
struct SIPCCMsg_Client_TextChat : public SIPCCMsg_Client
{
	SIPCCMsg_Client_TextChat();
	~SIPCCMsg_Client_TextChat()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	};
	
	string Sender;
	string Receiver;
	string ChatWords;
	
private:
	virtual int GetMyMemSize();
};

///Client_PreConference
struct SIPCCMsg_Client_PreConference : public SIPCCMsg_Client
{
	SIPCCMsg_Client_PreConference();
	~SIPCCMsg_Client_PreConference()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	};
	
	string presideParty;
	int presidePartyType;
	unsigned long presidePartyIP;
	unsigned short presidePartyPort;
	string otherJoinParty;
	int otherJoinPartyType;
	unsigned long otherJoinPartyIP;
	unsigned short otherJoinPartyPort;
	
private:
	virtual int GetMyMemSize();
};

///Client_Conference 
struct SIPCCMsg_Client_Conference : public SIPCCMsg_Client
{
	SIPCCMsg_Client_Conference();
	~SIPCCMsg_Client_Conference()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	};
	
	string presideParty;
	int presidePartyType;
	string otherJoinParty;
	int otherJoinPartyType;
	
private:
	virtual int GetMyMemSize();
};


//Type_Client_QueryTransServer
struct SIPCCMsg_Client_QueryTransServer : public SIPCCMsg_Client
{
	SIPCCMsg_Client_QueryTransServer() 
	{
		msgType = Type_Client_QueryTransServer;
	}
	~SIPCCMsg_Client_QueryTransServer()
	{
		ReleaseMemory();
	};
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	};
	unsigned long clientIP;
	unsigned long gwServerIP;
private:
	virtual int GetMyMemSize();
};

//Type_Client_AgentLoadURL
struct SIPCCMsg_Client_AgentLoadURL : public SIPCCMsg_Client
{
	SIPCCMsg_Client_AgentLoadURL()
	{
		msgType = Type_Client_AgentLoadURL;
		agentName = "";
		corpName = "";
	}
	~SIPCCMsg_Client_AgentLoadURL()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	};
	string agentName;
	string corpName;
private:
	virtual int GetMyMemSize();
};

//Type_Client_SuperDisconnect
struct SIPCCMsg_Client_SuperDisconnect : public SIPCCMsg_Client
{
	SIPCCMsg_Client_SuperDisconnect()
	{
		msgType = Type_Client_SuperDisconnect;
		agentID = "";
	}
	~SIPCCMsg_Client_SuperDisconnect()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	};
	string agentID;
private:
	virtual int GetMyMemSize();
};

//Type_Client_GetParkReasons
struct SIPCCMsg_Client_GetParkReasons : public SIPCCMsg_Client
{
	SIPCCMsg_Client_GetParkReasons()
	{
		msgType = Type_Client_GetParkReasons;
		managerid = "";
		invokeID = "";
	}
	~SIPCCMsg_Client_GetParkReasons()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	};
	string managerid;
	string invokeID;
	
private:
	virtual int GetMyMemSize();
};

///Type_Client_ChangePassword
struct SIPCCMsg_Client_ChangePassword : public SIPCCMsg_Client
{
	SIPCCMsg_Client_ChangePassword()
	{
		msgType = Type_Client_ChangePassword;
		username = "";
		oldpassword = "";
		newpassword = "";
	}
	
	~SIPCCMsg_Client_ChangePassword()
	{
		ReleaseMemory();
	};
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	string username;
	string oldpassword;
	string newpassword;
	
private:
	virtual int GetMyMemSize();
};

///Type_Client_ReturnToAgent
struct SIPCCMsg_Client_ReturnToAgent : public SIPCCMsg_Client
{
	SIPCCMsg_Client_ReturnToAgent();
	~SIPCCMsg_Client_ReturnToAgent()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		agentID = "";
		IVRUUIData = "";
		bIsSuccess = 0;
	}
	
	string agentID;
	string IVRUUIData;
	char bIsSuccess;

	string  managerId;
	string  connectPhoneNo;
	string  handleId;
	
private:
	virtual int GetMyMemSize();
};

///Type_Client_GetUSnGWM
struct SIPCCMsg_Client_GetUSnGWM : public SIPCCMsg_Client
{
	SIPCCMsg_Client_GetUSnGWM();
	~SIPCCMsg_Client_GetUSnGWM()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		InvokeId = "";
		UStateServerIp = 0;
		UStateServerPort = 0;
		GWManageServerIp = 0;
		GWManageServerPort = 0;
	}

	string InvokeId;
	unsigned long UStateServerIp;
	unsigned short UStateServerPort;
	unsigned long GWManageServerIp;
	unsigned short GWManageServerPort;
private:
	virtual int GetMyMemSize();
};

///Type_Client_UStateConfirm
struct SIPCCMsg_Client_UStateConfirm : public SIPCCMsg_Client
{
	SIPCCMsg_Client_UStateConfirm();
	~SIPCCMsg_Client_UStateConfirm()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}

	string invokeID;
private:
	virtual int GetMyMemSize();
};

///Type_Client_GWManageConfirm
struct SIPCCMsg_Client_GWManageConfirm : public SIPCCMsg_Client
{
	SIPCCMsg_Client_GWManageConfirm();
	~SIPCCMsg_Client_GWManageConfirm()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}

	string invokeID;
private:
	virtual int GetMyMemSize();
};


///Type_Client_LoginOverrun
struct SIPCCMsg_Client_LoginOverrun : public SIPCCMsg_Client
{
	SIPCCMsg_Client_LoginOverrun();
	~SIPCCMsg_Client_LoginOverrun()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}

	string overrunAgent;

private:
	virtual int GetMyMemSize();
};

///Class_Client
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
///Class_Login
struct SIPCCMsg_Login : public SIPCCMessage
{
	SIPCCMsg_Login();
	~SIPCCMsg_Login()
	{
		ReleaseMemory();
	};
	
	virtual int GetMyMemSize(){return 0;}
	virtual int FillBuf(char*& thebuf){return 0;}
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0){}
	virtual void ReleaseMemory(){}
};

///Type_Login_LoginSucc
struct SIPCCMsg_Login_UserLoginSucc : public SIPCCMsg_Login
{
	SIPCCMsg_Login_UserLoginSucc();
	~SIPCCMsg_Login_UserLoginSucc()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(departmentInfo!=NULL)	delete departmentInfo;
		departmentInfo = NULL;
		departmentInfoLen = 0;
		agentID = "";
	}
	void SetDepartmentInfo(string departmentinfo);
	string GetDepartmentInfo()	
	{
		if(departmentInfoLen == 0)	return "";
		return string(departmentInfo);
	}
	
	unsigned long uStateServerIP;
	unsigned long guideServerIP;
	unsigned long acdServerIP;
	unsigned long relayServerIP;
	unsigned long markServerIP;
	
	unsigned long natServer1IP;
	unsigned long natServer2IP;
	
	unsigned long transmitServerIP;
	unsigned long routeServerIP;
	unsigned long gwMgrServerIP;
	
	unsigned long textChatServerIP;
	unsigned long dlyStrategyServerIP;
	
	string callerNoForSend;
	
	unsigned long tollQueryServerIP;
	unsigned long phoneBookServerIP;
	unsigned long dataRouteServerIP;
	
	string agentID;
	
	string agentPhoneNo;
	
	unsigned long dataCenterServerIP;
	
	string managerID;
	string spNumber;
	string shortName;
	
	int autoFinishProcess;
	char bIsSuper;
	
	string nickName;
	
	string outdialPrefixNo;
	
	char bAutoTransfer;
	char bHasSMS;    //是否有短信支持
	
	unsigned long transSererIp;   //中转服务器IP
	unsigned short transServerPort;  //中转服务器端口
	char bPermitPlayAgentID;
	char bIsMasterSuper;     //高级班长席
	
	string agentName_Return;
	
	int remindTalkTime;
	int remindProcessTime;
	
	int user_role;
	int agentType;
	int managerFlag;
	
	int isOutDial;
	
	string managerPassKey;
	
	int iNeedDisposal;
	
	int funcConfigure; 
	
	string extNo;
	
	char bClientNeedUpdate;
	
	char bOutDialOpenURL; //去电是否弹屏
	
	int iSms_Type;
	
	unsigned long mainproxyip;
	
	unsigned short mainproxyport;
	unsigned long audioproxyip;
	
	unsigned short audioproxyport;
	
	char bSelectSkillGroup;
	int iLoginSuccMode;		//登录成功后座席状态模式
	char bCallInOpenURL;   //来电是否弹屏

	char isPhoneNoEditBoxDisabled;
	
	char  internationalCallUnallowed;

	char bHidePhone;

	string ACDServerIP;

	unsigned long samplerServerIP;

	int iReDailUseBackupTG;

	unsigned long RegisterServerA_Ip;
	unsigned short RegisterServerA_Port;
	unsigned long RegisterServerB_Ip;
	unsigned short RegisterServerB_Port;

	string ACDServerID; ///放了ServerName

	int	 MuiltACDServerID; ///这是对应ACDServerIp，读取的是T_CorpToService表
	
	int calloutByIAD;

	string SkillGroupID;
	string handleId;		//操作唯一标识

	unsigned short ACDServerPort;

    int LoginConfType;
    int agent_TollStatus;		//1表示正常使用；11表示关闭呼入接听和外呼功能；12表示客户端需要每隔2小时向LoginServer发送一次Client_UserLogin；13表示月账号当天到期，运行时间超过需自动登出；
    string loginTime;			//座席登录成功的服务端时间

private:
	char* departmentInfo;
	int departmentInfoLen;
	virtual int GetMyMemSize();
};

///Type_Login_LoginFailed
struct SIPCCMsg_Login_UserLoginFailed : public SIPCCMsg_Login
{
	SIPCCMsg_Login_UserLoginFailed();
	~SIPCCMsg_Login_UserLoginFailed()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(failedCause!=NULL)	delete failedCause;
		failedCause = NULL;
		failedCauseLen = 0;
	}
	void SetFailedCause(string failedcause);
	string GetFailedCause()	
	{
		if(failedCauseLen==0)	return "";
		return string(failedCause);
	}
	string handleId;//
private:
	char* failedCause;
	int failedCauseLen;
	virtual int GetMyMemSize();
};

///Type_Login_ServerRegister
struct SIPCCMsg_Login_ServerRegister : public SIPCCMsg_Login
{
	SIPCCMsg_Login_ServerRegister();
	~SIPCCMsg_Login_ServerRegister()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		ServerType = -1;
	}
	
	int ServerType;
	
private:
	virtual int GetMyMemSize();
};

///Type_Login_ServerRegisterConf
struct SIPCCMsg_Login_ServerRegisterConf : public SIPCCMsg_Login
{
	SIPCCMsg_Login_ServerRegisterConf();
	~SIPCCMsg_Login_ServerRegisterConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		ScanKeyWordIP = 0;
	}
	
	unsigned long ScanKeyWordIP;
private:
	virtual int GetMyMemSize();
};

///Type_Login_AgentLoadURLConf
struct SIPCCMsg_Login_AgentLoadURLConf : public SIPCCMsg_Login
{
	SIPCCMsg_Login_AgentLoadURLConf()
	{
		msgType = Type_Login_AgentLoadURLConf;
		agentURL = "";
		loginName = "";
		loginPwd = "";
		haveVerifyCode = 1;
		remark1 = "";
		remark2 = "";
		remark3 = "";
		urlSign = "";
	}
	~SIPCCMsg_Login_AgentLoadURLConf()
	{
		ReleaseMemory();
	};
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	string agentURL;
	string loginName;
	string loginPwd;
	int haveVerifyCode;
	string remark1;
	string remark2;
	string remark3;
	string urlSign;
private:
	virtual int GetMyMemSize();
};

///Type_Login_GetParkReasonsConf
struct SIPCCMsg_Login_GetParkReasonsConf : public SIPCCMsg_Login
{
	SIPCCMsg_Login_GetParkReasonsConf()
	{
		msgType = Type_Login_GetParkReasonsConf;
		parkReasons = "";
	}
	
	~SIPCCMsg_Login_GetParkReasonsConf()
	{
		ReleaseMemory();
	};
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	string parkReasons;
	
private:
	virtual int GetMyMemSize();
};

///Type_Login_ChangePasswordConf
struct SIPCCMsg_Login_ChangePasswordConf : public SIPCCMsg_Login
{
	SIPCCMsg_Login_ChangePasswordConf()
	{
		msgType = Type_Login_ChangePasswordConf;
		result = -1;
	}
	
	~SIPCCMsg_Login_ChangePasswordConf()
	{
		ReleaseMemory();
	};
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	int result;
	
private:
	virtual int GetMyMemSize();
};

///Type_Login_QueryIncrementFuncConf
struct SIPCCMsg_Login_QueryIncrementFuncConf : public SIPCCMsg_Login
{
	SIPCCMsg_Login_QueryIncrementFuncConf()
	{
		msgType = Type_Login_QueryIncrementFuncConf;
		funcID = -1;
		funcName = "";
		defaultLangTypeID = -1;
		defaultOperTypeID = -1;
		ivrLangType = "";
		operationType = "";
	}
	
	~SIPCCMsg_Login_QueryIncrementFuncConf()
	{
		ReleaseMemory();
	};
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	int funcID;
	string funcName;
	int defaultLangTypeID;
	int defaultOperTypeID;
	
	string ivrLangType;
	string operationType;
	
private:
	virtual int GetMyMemSize();
};

///Type_Login_SendStrMsg
struct SIPCCMsg_Login_SendStrMsg  : public SIPCCMsg_Login
{
	SIPCCMsg_Login_SendStrMsg()
	{
		msgType = Type_Login_SendStrMsg;
	}
	
	~SIPCCMsg_Login_SendStrMsg()
	{
		ReleaseMemory();
	};
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	int nStrMsgId;
	string theSender;
	string msgContent;
private:
	virtual int GetMyMemSize();
};

///Type_Client_QueryIncrementFunc
struct SIPCCMsg_Client_QueryIncrementFunc : public SIPCCMsg_Client
{
	SIPCCMsg_Client_QueryIncrementFunc()
	{
		msgType = Type_Client_QueryIncrementFunc;
		agentName = "";
		departName = "";
		corpName = "";
	}
	
	~SIPCCMsg_Client_QueryIncrementFunc()
	{
		ReleaseMemory();
	};
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	string agentName;
	string departName;
	string corpName;
	
private:
	virtual int GetMyMemSize();
};

///Type_Login_NotifyAgentLoginConf
struct SIPCCMsg_Login_NotifyAgentLoginConf  : public SIPCCMsg_Login
{
	SIPCCMsg_Login_NotifyAgentLoginConf()
	{
		msgType = Type_Login_NotifyAgentLoginConf;

		managerTransPort = 0;
		needCollectNetInfo = 0;
		CanConference=0;
		TGRouteType=0;
		iHaveBlackList_Callout=0;
		canredundancy = 0;

		bProcedure_CallIn = false;
		bProcedure_CallOut = false;

		CaptureNetInfoDataCollectIP = 0;
		CaptureNetInfoDataCollectPort = 0;

		tcpProxyServerIP =0;
		tcpProxyServerPort=0;
		haveCallerNoQuestion = 0;

		HaveHBtoACD = 1;
		HaveHBtoHBServer = 1;
		RegisterServerAdd = "";
		generalConfiguration = "";

        threshold_packetlossrate = 0;
        threshold_delay = 0;
        threshold_jitter = 0;

		RouteSelectIp = 0;
		RouteSelectPort = 0;
		OtherServerList.clear();
		VoiceRouteDetect = 0;
        NeedTCPProxy = 0;
	}
	
	~SIPCCMsg_Login_NotifyAgentLoginConf()
	{
		ReleaseMemory();
	};
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	string departName;
	string popScript;
	string smsServer;

	char cIsAgentRecord;		//1录音，其他值不录音
	string strAgentRecServerIP;	//从表 T_Agent. agentRecServerSymbol= T_RecServer .ServerSymbol ，获取 T_RecServer .ServerIP
	string strRecServerSymbol;	//录音服务器标识

	string transserverList;
	
	int threshold_packetlossrate;
	int threshold_delay;
	int threshold_jitter;

	int agentRecServerPort;

	string managerTransIP;
	int managerTransPort;

	unsigned long CaptureNetInfoDataCollectIP;
	unsigned short CaptureNetInfoDataCollectPort;

	int needCollectNetInfo;
	int     CanConference;
	
	// 2013-01-04  参考《SIP-BOX集成至QTB平台技术方案》
	string primary_username;
	int  TGRouteType;		//默认为0，为1时表示使用按运营商选择中继组功能；

	int iHaveBlackList_Callout;

	int canredundancy;

	bool bProcedure_CallIn;
	bool bProcedure_CallOut;

	unsigned long tcpProxyServerIP;
	unsigned short tcpProxyServerPort;

	string defaultTG_DialUnderHold;

	int haveCallerNoQuestion;

	int HaveHBtoACD;
	int HaveHBtoHBServer;
	string RegisterServerAdd;
	string generalConfiguration;

	//RouteSelect
	unsigned long RouteSelectIp ;
   	unsigned short  RouteSelectPort;
	list<S_RouteSelect_Node> OtherServerList;
	// 2015-8-26 syb
	short VoiceRouteDetect;
	unsigned long NeedTCPProxy;
	string the2ndDomainName;
private:
	virtual int GetMyMemSize();
};

///Class_Login
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
///Class_Guide
struct SIPCCMsg_Guide : public SIPCCMessage
{
	SIPCCMsg_Guide();
	~SIPCCMsg_Guide()
	{
		ReleaseMemory();
	};
	
	virtual int GetMyMemSize(){return 0;}
	virtual int FillBuf(char*& thebuf){return 0;}
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0){}
	virtual void ReleaseMemory(){}
};

///Type_Guide_ACDInfo
struct SIPCCMsg_Guide_ACDInfo : public SIPCCMsg_Guide
{
	SIPCCMsg_Guide_ACDInfo();
	~SIPCCMsg_Guide_ACDInfo()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(theDepartment!=NULL)	delete theDepartment;
		theDepartment = NULL;
		theDepartmentLen = 0;
		acdServerIP = 0;
		acdServerPort = 0;
		invokeID = 0;
		UserLevel = 3;
		CallTargetType = 0;
	}
	void SetTheDepartment(string thedepartment);
	string GetTheDepartment()	
	{
		if(theDepartmentLen==0)	return "";
		return string(theDepartment);
	}
	
	unsigned long acdServerIP;
	unsigned short acdServerPort;
	int invokeID;

	int UserLevel;
	int CallTargetType;
private:
	char* theDepartment;
	int theDepartmentLen;
	virtual int GetMyMemSize();
};

///Type_Guide_AddKeyConf
struct SIPCCMsg_Guide_AddKeyConf : public SIPCCMsg_Guide
{
	SIPCCMsg_Guide_AddKeyConf();
	~SIPCCMsg_Guide_AddKeyConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(keyWord!=NULL)	delete keyWord;
		keyWord = NULL;
		keyWordLen = 0;
	}
	void SetKeyWord(string keyword);
	string GetKeyWord()	
	{
		if(keyWordLen==0)	return "";
		return string(keyWord);
	}
private:
	char* keyWord;
	int keyWordLen;	
	virtual int GetMyMemSize();
};

///Type_Guide_DelKeyConf
struct SIPCCMsg_Guide_DelKeyConf : public SIPCCMsg_Guide
{
	SIPCCMsg_Guide_DelKeyConf();
	~SIPCCMsg_Guide_DelKeyConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(keyWord!=NULL)	delete keyWord;
		keyWord = NULL;
		keyWordLen = 0;
	}
	void SetKeyWord(string keyword);
	string GetKeyWord()	
	{
		if(keyWordLen==0)	return "";
		return string(keyWord);
	}
private:
	char* keyWord;
	int keyWordLen;	
	virtual int GetMyMemSize();
};

///Type_Guide_LoadKeyWords
struct SIPCCMsg_Guide_LoadKeyWords : public SIPCCMsg_Guide
{
	SIPCCMsg_Guide_LoadKeyWords();
	~SIPCCMsg_Guide_LoadKeyWords()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}

	string invokeId;
private:
	virtual int GetMyMemSize();
};
///Class_Guide
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
///Class_SysManage
struct SIPCCMsg_SysManage : public SIPCCMessage
{
	SIPCCMsg_SysManage();
	~SIPCCMsg_SysManage()
	{
		ReleaseMemory();
	};
	
	virtual int GetMyMemSize(){return 0;}
	virtual int FillBuf(char*& thebuf){return 0;}
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0){}
	virtual void ReleaseMemory(){}
};

///Type_SysManage_AddKey
struct SIPCCMsg_SysManage_AddKey : public SIPCCMsg_SysManage
{
	SIPCCMsg_SysManage_AddKey();
	~SIPCCMsg_SysManage_AddKey()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(keyWord!=NULL)	delete keyWord;
		keyWord = NULL;
		keyWordLen = 0;
		if(theDepartment!=NULL)	delete theDepartment;
		theDepartment = NULL;
		theDepartmentLen = 0;
		acdServerIP = 0;
		acdServerPort = 0;
	}
	unsigned long acdServerIP;
	unsigned short acdServerPort;

	string SkillGroupID;
	int UserLevel;
public:
	void SetKeyWord(string keyword);
	string GetKeyWord()	
	{
		if(keyWordLen==0)	return "";
		return string(keyWord);
	}
	void SetTheDepartment(string theDepartment);
	string GetTheDepartment()	
	{
		if(theDepartmentLen==0)	return "";
		return string(theDepartment);
	}
private:
	char* keyWord;
	int keyWordLen;
	char* theDepartment;
	int theDepartmentLen;
	virtual int GetMyMemSize();
};

///Type_SysManage_DelKey
struct SIPCCMsg_SysManage_DelKey : public SIPCCMsg_SysManage
{
	SIPCCMsg_SysManage_DelKey();
	~SIPCCMsg_SysManage_DelKey()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(keyWord!=NULL)	delete keyWord;
		keyWord = NULL;
		keyWordLen = 0;
		acdServerIP = 0;
		acdServerPort = 0;
	}
	unsigned long acdServerIP;
	unsigned short acdServerPort;
public:
	void SetKeyWord(string keyword);
	string GetKeyWord()	
	{
		if(keyWordLen==0)	return "";
		return string(keyWord);
	}
	
private:
	char* keyWord;
	int keyWordLen;
	virtual int GetMyMemSize();
};

///Type_SysManage_AddDepartment
struct SIPCCMsg_SysManage_AddDepartment : public SIPCCMsg_SysManage
{
	SIPCCMsg_SysManage_AddDepartment();
	~SIPCCMsg_SysManage_AddDepartment()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(theDepartment!=NULL)	delete theDepartment;
		theDepartment = NULL;
		theDepartmentLen = 0;
	}
	void SetTheDepartment(string thedepartment);
	string GetTheDepartment()	
	{
		if(theDepartmentLen==0)	return "";
		if ( !(VerifyData(theDepartmentLen, CORPNDEPT_LEN)) ) {return "";}
		return string(theDepartment);
	}
	
	int timeoutValue;		//溢出超时时限
	string overFlowDest;		//溢出目的地
	int overFlowDestType;	//溢出类型(0:技能组 1:手机群 2:IVR 3:分机 4:指定电话)
	int maxRingTime;
	
	int deptType;
	int isOutDial;
	int outdialGroupID;
	string invokeID;
	
	string managerid;
	string deptid;

	string nickname;
	string	generalConfiguration;		//通用配置项，配置项间用分号“；”分割；
private:
	char* theDepartment;
	int theDepartmentLen;
	virtual int GetMyMemSize();
};

///Type_SysManage_DelDepartment
struct SIPCCMsg_SysManage_DelDepartment : public SIPCCMsg_SysManage
{
	SIPCCMsg_SysManage_DelDepartment();
	~SIPCCMsg_SysManage_DelDepartment()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(theDepartment!=NULL)	delete theDepartment;
		theDepartment = NULL;
		theDepartmentLen = 0;
	}
	void SetTheDepartment(string thedepartment);
	string GetTheDepartment()	
	{
		if(theDepartmentLen==0)	return "";
		if ( !(VerifyData(theDepartmentLen, CORPNDEPT_LEN)) ) {return "";}
		return string(theDepartment);
	}
private:
	char* theDepartment;
	int theDepartmentLen;
	virtual int GetMyMemSize();
};

///Type_SysManage_ModifyKeyword
struct SIPCCMsg_SysManage_ModifyKeyword : public SIPCCMsg_SysManage
{
	SIPCCMsg_SysManage_ModifyKeyword();
	~SIPCCMsg_SysManage_ModifyKeyword()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(originKeyword!=NULL)	delete originKeyword;
		originKeyword = NULL;
		originKeywordLen = 0;
		if(newKeyword!=NULL)	delete newKeyword;
		newKeyword = NULL;
		newKeywordLen = 0;
	}
	void SetOriginKeyword(string originkeyword);
	string GetOriginKeyword()	
	{
		if(originKeywordLen==0)	return "";
		return string(originKeyword);
	}
	void SetNewKeyword(string newkeyword);
	string GetNewKeyword()	
	{
		if(newKeywordLen==0)	return "";
		return string(newKeyword);
	}
private:
	char* originKeyword;
	int originKeywordLen;
	char* newKeyword;
	int newKeywordLen;
	virtual int GetMyMemSize();
};

///Type_SysManage_ModifyKeyDepart
struct SIPCCMsg_SysManage_ModifyKeyDepart : public SIPCCMsg_SysManage
{
	SIPCCMsg_SysManage_ModifyKeyDepart();
	~SIPCCMsg_SysManage_ModifyKeyDepart()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(theKeyword!=NULL)	delete theKeyword;
		theKeyword = NULL;
		theKeywordLen = 0;
		if(theDepart!=NULL)	delete theDepart;
		theDepart = NULL;
		theDepartLen = 0;
	}
	void SetTheKeyword(string thekeyword);
	string GetTheKeyword()	
	{
		if(theKeywordLen==0)	return "";
		return string(theKeyword);
	}
	void SetTheDepart(string thedepart);
	string GetTheDepart()	
	{
		if(theDepartLen==0)	return "";
		return string(theDepart);
	}
private:
	char* theKeyword;
	int theKeywordLen;
	char* theDepart;
	int theDepartLen;
	virtual int GetMyMemSize();
};

///Type_SysManage_ModifyDepart
struct SIPCCMsg_SysManage_ModifyDepart : public SIPCCMsg_SysManage
{
	SIPCCMsg_SysManage_ModifyDepart();
	~SIPCCMsg_SysManage_ModifyDepart()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(theKeyword!=NULL)	delete theKeyword;
		theKeyword = NULL;
		theKeywordLen = 0;
		if(theDepart!=NULL)	delete theDepart;
		theDepart = NULL;
		theDepartLen = 0;
	}
	void SetTheKeyword(string thekeyword);
	string GetTheKeyword()	
	{
		if(theKeywordLen==0)	return "";
		return string(theKeyword);
	}
	void SetTheDepart(string thedepart);
	string GetTheDepart()	
	{
		if(theDepartLen==0)	return "";
		return string(theDepart);
	}
private:
	char* theKeyword;
	int theKeywordLen;
	char* theDepart;
	int theDepartLen;
	virtual int GetMyMemSize();
};

///Type_SysManage_AddGatewayInfo
struct SIPCCMsg_SysManage_AddGatewayInfo : public SIPCCMsg_SysManage
{
	SIPCCMsg_SysManage_AddGatewayInfo();
	~SIPCCMsg_SysManage_AddGatewayInfo()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	string gwName;
	string theAccount;
	string thePassword;
	int	   dtmfEN;
	string invokeID;
	string gwAreaCode;	// 网关所在地区号
private:
	virtual int GetMyMemSize();
};

///Type_SysManage_DelGatewayInfo
struct SIPCCMsg_SysManage_DelGatewayInfo : public SIPCCMsg_SysManage
{
	SIPCCMsg_SysManage_DelGatewayInfo();
	~SIPCCMsg_SysManage_DelGatewayInfo()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	string gwName;
	string invokeID;
private:
	virtual int GetMyMemSize();
};

///Type_SysManage_AddGWCorp
struct SIPCCMsg_SysManage_AddGWCorp : public SIPCCMsg_SysManage
{
	SIPCCMsg_SysManage_AddGWCorp();
	~SIPCCMsg_SysManage_AddGWCorp()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	string corpName;
	string defaultTG;	//默认中继组
	char enableDialNoRule;
	
	string invokeID;
private:
	virtual int GetMyMemSize();
};

///Type_SysManage_DelGWCorp
struct SIPCCMsg_SysManage_DelGWCorp : public SIPCCMsg_SysManage
{
	SIPCCMsg_SysManage_DelGWCorp();
	~SIPCCMsg_SysManage_DelGWCorp()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	string corpName;
	
	string invokeID;
private:
	virtual int GetMyMemSize();
};

///Type_SysManage_DelACDCorp
struct SIPCCMsg_SysManage_DelACDCorp : public SIPCCMsg_SysManage
{	
	SIPCCMsg_SysManage_DelACDCorp();
	~SIPCCMsg_SysManage_DelACDCorp()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	string corpName;
private:
	virtual int GetMyMemSize();	
};

///Type_SysManage_AddGWTG
struct SIPCCMsg_SysManage_AddGWTG : public SIPCCMsg_SysManage
{
	SIPCCMsg_SysManage_AddGWTG();
	~SIPCCMsg_SysManage_AddGWTG()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	
	string tgName;
	string gwName;
	string corpName;
	string calledNo;
	int callinLicence;
	int calloutLicence;
	string mappingName;
	
	string invokeID;
	string tgPrefix;

     string computerSymbol;
     string areaCode;
     string operatorsInfo;
     int allowCallType;			//默认为0
     int trunkCount;				//默认为0
	 int lowerLimitNum;

private:
	virtual int GetMyMemSize();
};

///Type_SysManage_AddDeptTG
struct SIPCCMsg_SysManage_AddDeptTG : public SIPCCMsg_SysManage
{
	SIPCCMsg_SysManage_AddDeptTG();
	~SIPCCMsg_SysManage_AddDeptTG()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	string corpName;
	string deptName;
	string specialTGName;
	string innerTGName;
	string backupTGName;	//  备份中继组或者叫备份网关[1/11/2008 lixg]
	string longDisTGName;
	
	char enableDialNoRule;
	
	string invokeID;

	string defaultIADGName;
private:
	virtual int GetMyMemSize();
};

///Type_SysManage_AddDialRule
struct SIPCCMsg_SysManage_AddDialRule : public SIPCCMsg_SysManage
{
	SIPCCMsg_SysManage_AddDialRule();
	~SIPCCMsg_SysManage_AddDialRule()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	string corpName;
	string checkedPrefix;	//检查前缀
	string tgName;
	int delPrefixLen;		//删除前缀长度
	string addPrefix;		//增加前缀
	
	string invokeID;
private:
	virtual int GetMyMemSize();
};

///Type_SysManage_NotifyACDLicence
struct SIPCCMsg_SysManage_NotifyACDLicence : public SIPCCMsg_SysManage
{
	SIPCCMsg_SysManage_NotifyACDLicence();
	~SIPCCMsg_SysManage_NotifyACDLicence()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	string licence;
	string invokeID;

private:
	virtual int GetMyMemSize();
};


///Type_SysManage_LoadServerInfoConf
struct SIPCCMsg_SysManage_LoadServerInfoConf : public SIPCCMsg_SysManage
{
	SIPCCMsg_SysManage_LoadServerInfoConf();
	~SIPCCMsg_SysManage_LoadServerInfoConf()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}


	string ManagerID;
	string CorpName;
	string ACDServerIP;
	string PhoneNo;

	string DataCollectServerIP;
	string DataCollectServerPort;

	// 0：删除  1：加载
	int bLoad;
	string InvokeId;
	int indexnum;
	int bSwitchACD;		//0是普通加载，1是切换ACD时更新

private:
	virtual int GetMyMemSize();
};



///Class_SysManage
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
///Class_ACD
struct SIPCCMsg_ACD : public SIPCCMessage
{
	SIPCCMsg_ACD();
	~SIPCCMsg_ACD()
	{
		ReleaseMemory();
	};
	
	virtual int GetMyMemSize(){return 0;}
	virtual int FillBuf(char*& thebuf){return 0;}
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0){}
	virtual void ReleaseMemory(){};
};

///Type_ACD_AgentLoginSucc
struct SIPCCMsg_ACD_AgentLoginSucc : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_AgentLoginSucc();
	~SIPCCMsg_ACD_AgentLoginSucc()
	{
		ReleaseMemory();
	};
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	char bAgentExist;
	string agentId;
	int iLoginSuccMode;		//登录成功后座席状态模式

	string  handleId;

	string deptNickname;
private:
	virtual int GetMyMemSize();
};

///Type_ACD_AgentLoginFailed
struct SIPCCMsg_ACD_AgentLoginFailed : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_AgentLoginFailed();
	~SIPCCMsg_ACD_AgentLoginFailed()
	{
		ReleaseMemory();
	};
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	string agentId;
	string failedCause;

	string  handleId;

private:
	virtual int GetMyMemSize();
};

///Type_ACD_AgentLogoutConf
struct SIPCCMsg_ACD_AgentLogoutConf : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_AgentLogoutConf();
	~SIPCCMsg_ACD_AgentLogoutConf()
	{
		ReleaseMemory();
	};
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	string agentId;

	string  handleId;

private:
	virtual int GetMyMemSize();
};

// [scq/start/2010-04-23]
///Type_ACD_AgentLogoutDepartsConf
struct SIPCCMsg_ACD_AgentLogoutDepartsConf : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_AgentLogoutDepartsConf();
	~SIPCCMsg_ACD_AgentLogoutDepartsConf()
	{
		ReleaseMemory();
	};
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	string agentId;
	string theDepartmentFailed;		// 在bLogoutSuccess为false时，则为注销失败的技能组名称，否则为空
	string theDepartmentSuccess;	// 在bLogoutSuccess为false时，则为注销成功的技能组名称，否则为空
	bool bLogoutSuccess;			// 在所有技能组都注销成功后，则为true；如果有一个或者以上技能组注销失败，则为false。
private:
	virtual int GetMyMemSize();
};
// [scq/end/2010-04-23]

///Type_ACD_AgentParkConf
struct SIPCCMsg_ACD_AgentParkConf : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_AgentParkConf();
	~SIPCCMsg_ACD_AgentParkConf()
	{
		ReleaseMemory();
	};
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
private:
	virtual int GetMyMemSize();
};

///Type_ACD_AgentUnparkConf
struct SIPCCMsg_ACD_AgentUnParkConf : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_AgentUnParkConf();
	~SIPCCMsg_ACD_AgentUnParkConf()
	{
		ReleaseMemory();
	};
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
private:
	virtual int GetMyMemSize();
};

///Type_ACD_UserMakeCallConf
struct SIPCCMsg_ACD_UserMakeCallConf : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_UserMakeCallConf();
	~SIPCCMsg_ACD_UserMakeCallConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		callingState = 0;
		userNumInQueue = 0;
		if(userName!=NULL)	delete userName;	
		userName = NULL;
		userNameLen = 0;
		userNumInQueue = 0;
		if(agentID!=NULL)	delete agentID;
		agentID = NULL;
		agentIDLen = 0;
	}
	void SetUserName(string username);
	string GetUserName()
	{
		if(userNameLen == 0)			return "";
		return string(userName);
	}
	void SetAgentID(string agentid);
	string GetAgentID()
	{
		if(agentIDLen==0)	return "";
		return string(agentID);
	}
	
	int callingState;
	int userNumInQueue;	//排队数

	string  handleId;
private:
	char* userName;
	int userNameLen;
	char* agentID;
	int agentIDLen;	
	virtual int GetMyMemSize();
public:
	/////////////////媒体信息描述/////////////////
	//传输方式，决定包格式
	//UDP/OLD	固定长度包，根据协商的编码和单位时间决定包长度
	//UDP/V1	变长包，包自身可以表述负载大小，暂时不用
	string trans;
	//编码方式
	//G729
	//ILBC
	string codec;
	//单位时间
	size_t unit;
	///////////////////////////////////////////////
};

///SIPCCMsg_ACD_CallArriveToAgent
struct SIPCCMsg_ACD_CallArriveToAgent : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_CallArriveToAgent();
	~SIPCCMsg_ACD_CallArriveToAgent()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(agentID != NULL)	delete agentID;
		agentID = NULL;		
		agentIDLen = 0;
	}
	void SetAgentID(string agentID);
	string GetAgentID()	
	{
		if(agentIDLen==0)	return "";
		return string(agentID);
	}
	unsigned long lanIP;
	unsigned short lanMainSockPort;
	
	unsigned long sipAgentPhoneIP1;   		//被叫座席端话机IP
	unsigned short sipAgentPhoneRtpPort1;	//被叫座席端话机RtpPort
	unsigned short sipAgentPhoneRtcpPort1;  //被叫座席端话机rtcpPort
	
	string agentExtNo;

    CAudioStreamDescription audioStreamDescription;

private:
	char* agentID;
	int agentIDLen;
	virtual int GetMyMemSize();
};

///Type_ACD_CallDelivered
struct SIPCCMsg_ACD_CallDelivered : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_CallDelivered();
	~SIPCCMsg_ACD_CallDelivered()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory();
	void SetCallID(string callid);
	string GetCallID()	
	{
		if(callIDLen==0)	return "";
		return string(callID);
	}
	void SetCallerName(string callername);
	string GetCallerName()	
	{
		if(callerNameLen==0)	return "";
		return string(callerName);
	}
	void SetKeyWord(string keyword);
	string GetKeyWord()	
	{
		if(keyWordLen==0)	return "";
		return string(keyWord);
	}
	void SetUUIData(string uuidata);
	string GetUUIData()	
	{
		if(uuiDataLen==0)	return "";
		return string(uuiData);
	}
	//  [2/23/2009 lixg]
	std::string AgentUUIData() const { return agentUUIData; }
	void AgentUUIData(std::string &val) { agentUUIData = val; }
	
	int callerType;
	unsigned long audioIP;		//pstnAgent呼叫座席时，充当 pstnAgentLineIP
	unsigned short audioPort;	//pstnAgent呼叫座席时，充当 pstnAgentLinePort
	unsigned long lanIP;
	unsigned short lanMainSockPort;
	
	string gwPartNo;
	
	string wPstnAgentLineNo;
	string userLineNo;
	unsigned long userLineIP;
	unsigned short userLinePort;
	
	string comSymbol;
	string uuiData2;
	char bIsFromDept;
	
	string originalData;	//待转移的原数据
	
	unsigned long sipBoardIP;
	unsigned short sipBoardRtpPort;
	unsigned short sipBoardRtcpPort;
    unsigned long sipTransIP;   //中转IP
    unsigned short sipTransRtpPort;  //中转RtpPort
    unsigned short sipTransRtcpPort;  //中转rtcpPort
	
	unsigned long sipAgentPhoneIP1;   		//主叫座席端话机IP
	unsigned short sipAgentPhoneRtpPort1;	//主叫座席端话机RtpPort
	unsigned short sipAgentPhoneRtcpPort1;  //主叫座席端话机rtcpPort

	unsigned short conferencePort1;		//座席端用于会议的端口1
	unsigned short conferencePort2;		//座席端用于会议的端口2

	string SkillGroupID;
	string SkillGroupName;
	
    CAudioStreamDescription audioStreamDescription;
private:
	char* callID;
	int callIDLen;
	char* callerName;
	int callerNameLen;
	char* keyWord;
	int keyWordLen;
	char* uuiData;
	int uuiDataLen;
	string agentUUIData;	// 随路数据 [2/23/2009 lixg]
	
	virtual int GetMyMemSize();
public:
	/////////////////媒体信息描述/////////////////
	//传输方式，决定包格式
	//UDP/OLD	固定长度包，根据协商的编码和单位时间决定包长度
	//UDP/V1	变长包，包自身可以表述负载大小，暂时不用
	string trans;
	//编码方式
	//G729
	//ILBC
	string codec;
	//单位时间
	size_t unit;
	///////////////////////////////////////////////
};

///Type_ACD_CallEstablished
struct SIPCCMsg_ACD_CallEstablished : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_CallEstablished();
	~SIPCCMsg_ACD_CallEstablished()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(theOtherParty!=NULL)	delete theOtherParty;
		theOtherParty = NULL;
		theOtherPartyLen = 0;
		relayIP = 0;
		relayPort = 0;
	}
	void SetTheOtherParty(string theotherparty);
	string GetTheOtherParty()	
	{
		if(theOtherPartyLen==0)	return "";
		return string(theOtherParty);
	}
	
	unsigned long relayIP;
	unsigned short relayPort;
	int remoteNatType;
	
	int outDialType;
	string ipPhoneNo_User;
	string ipPhoneNo_AgentExt;
	
	string userLineNo;
	unsigned long userLineIp;
	unsigned short userLinePort;

	string  handleId;

	string nickName;
	char* theOtherParty;
    CAudioStreamDescription audioStreamDescription;
private:
	
	int theOtherPartyLen;
	virtual int GetMyMemSize();
};

///Type_ACD_CallAnswered
struct SIPCCMsg_ACD_CallAnswered : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_CallAnswered();
	~SIPCCMsg_ACD_CallAnswered()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		relayIP = 0;
		relayPort = 0;
		if(userName!=NULL)	delete userName;	
		userName = NULL;
		userNameLen = 0;
		callId = "";
	}
	void SetUserName(string username);
	string GetUserName()
	{
		if(userNameLen == 0)			return "";
		return string(userName);
	}
	
	unsigned long relayIP;		//备用
	unsigned short relayPort;	//备用
	
	int remoteNatType;
	string callId;

	string  handleId;
private:
	char* userName;
	int userNameLen;
	virtual int GetMyMemSize();
};

///Type_ACD_CallReleased
struct SIPCCMsg_ACD_CallReleased : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_CallReleased();
	~SIPCCMsg_ACD_CallReleased()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(releasedParty!=NULL)	delete releasedParty;
		releasedParty = NULL;
		releasedPartyLen = 0;
	}
	void SetReleasedParty(string releasedparty);
	string GetReleasedParty()	
	{
		if(releasedPartyLen==0)	return "";
		return string(releasedParty);
	}
public:
	char bIsPresideAgent;	//离开座席是否为会议主控座席

	string callID;
	string agentName;

private:
	char* releasedParty;
	int releasedPartyLen;
	
	virtual int GetMyMemSize();
};

///Type_ACD_CallHanguped
struct SIPCCMsg_ACD_CallHanguped : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_CallHanguped();
	~SIPCCMsg_ACD_CallHanguped()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(userName!=NULL)	delete userName;	
		userName = NULL;
		userNameLen = 0;
		if(releasedParty!=NULL)	delete releasedParty;
		releasedParty = NULL;
		releasedPartyLen = 0;
	}
	void SetUserName(string username);
	string GetUserName()
	{
		if(userNameLen == 0)			return "";
		return string(userName);
	}
	void SetReleasedParty(string releasedparty);
	string GetReleasedParty()	
	{
		if(releasedPartyLen==0)	return "";
		return string(releasedParty);
	}

	string  handleId;
private:
	char* userName;
	int userNameLen;
	char* releasedParty;
	int releasedPartyLen;
	virtual int GetMyMemSize();
};

///Type_ACD_AgentStateInfo
struct SIPCCMsg_ACD_AgentStateInfo : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_AgentStateInfo();
	~SIPCCMsg_ACD_AgentStateInfo()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(curTime!=NULL)	delete curTime;
		curTime = NULL;
		curTimeLen = 0;
		if(callID!=NULL)	delete callID;
		callID = NULL;
		callIDLen = 0;
		if(agentID!=NULL)	delete agentID;
		agentID = NULL;
		agentIDLen = 0;
		if(corporationName != NULL)	delete corporationName;
		corporationName = NULL;
		corporationNameLen = 0;
		if(theDepartment!=NULL)	delete theDepartment;
		theDepartment = NULL;
		theDepartmentLen = 0;
		if(userName!=NULL)	delete userName;
		userName = NULL;
		userNameLen = 0;
		if(keyWord!=NULL)	delete keyWord;
		keyWord = NULL;
		if (parkReason != NULL) delete parkReason;
		parkReason = NULL;
		parkReasonLen = 0;
		keyWordLen = 0;
		agentState = -1;

	}
	void SetCallID(string callid);
	string GetCallID()	
	{
		if(callIDLen==0)	return "";
		if ( !(VerifyData(callIDLen, CALLID_LEN)) ) {return "";}
		return string(callID);
	}
	void SetAgentID(string agentID);
	string GetAgentID()	
	{
		if(agentIDLen==0)	return "";
		if ( !(VerifyData(agentIDLen, AGENTID_LEN)) ) {return "";}
		return string(agentID);
	}
	void SetCorporationName(string corporationname);
	string GetCorporationName()
	{
		if(corporationNameLen==0)	return "";
		if ( !(VerifyData(corporationNameLen, CORPNAME_LEN)) ) {return "";}
		return string(corporationName);
	}
	void SetTheDepartment(string thedepartment);
	string GetTheDepartment()	
	{
		if(theDepartmentLen==0)	return "";
		if ( !(VerifyData(theDepartmentLen, CORPNDEPT_LEN)) ) {return "";}
		return string(theDepartment);
	}
	void SetUserName(string userName);
	string GetUserName()	
	{
		if(userNameLen==0)	return "";
		if ( !(VerifyData(userNameLen, USERNAME_LEN)) ) {return "";}
		return string(userName);
	}
	void SetKeyWord(string keyword);
	string GetKeyWord()	
	{
		if(keyWordLen==0)	return "";
		if ( !(VerifyData(keyWordLen, KEYWORD_LEN)) ) {return "";}
		return string(keyWord);
	}
	void SetCurTime(string curtime);
	string GetCurTime()	
	{
		if(curTimeLen==0)	return "";
		if ( !(VerifyData(curTimeLen, CURTIME_LEN)) ) {return "";}
		return string(curTime);
	}
	int agentState;
	char bCallIn;			//呼入，呼出
	char bInnerCall;		//内部，外部
	char bPSTNCall;			//电话，网络
	int  parkReasonID;		//报表用
	string GetParkReason() 	//监控用 	
	{
		if (parkReasonLen == 0) return "";
		if ( !(VerifyData(parkReasonLen, PARKREASON_LEN)) ) {return "";}
		return string(parkReason);
	}	
	void SetParkReason(string parkreason)
	{
		int iAgentIDLen = parkreason.length();
		parkReasonLen = iAgentIDLen + 1;
		parkReason = new char[parkReasonLen];
		memset(parkReason, 0, parkReasonLen);
		memcpy(parkReason, parkreason.c_str(), iAgentIDLen);
	}
	string callerID;
	string calleeID;
	char bAgentLogin;	//是否为座席登陆状态
	
	string managerid;
	string deptid;

	char bCallOutTypeUnderHold;		//保持下呼出，区分内部或外部 
	string nickName;
	string extNo;

	string SkillGroupID;
	string SkillGroupName;

	string SkillGroupID_Original;
	string SkillGroupName_Original;

	int UserLevel;
	string sData;

private:
	char* curTime;
	int curTimeLen;
	char* callID;
	int callIDLen;
	char* agentID;
	int agentIDLen;
	char* corporationName;
	int corporationNameLen;
	char* theDepartment;
	int theDepartmentLen;
	char* keyWord;
	int keyWordLen;
	char* userName;		//用于统计用户通话
	int userNameLen;
	
	char *parkReason;
	int parkReasonLen;
	
	virtual int GetMyMemSize();
};

///Type_ACD_AddDepartmentConf
struct SIPCCMsg_ACD_AddDepartmentConf : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_AddDepartmentConf();
	~SIPCCMsg_ACD_AddDepartmentConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(theDepartment != NULL)	delete theDepartment;
		theDepartment = NULL;
		theDepartmentLen = 0;
	}
	void SetTheDepartment(string thedepartment);
	string GetTheDepartment()	
	{
		if(theDepartmentLen == 0)	return "";
		return string(theDepartment);
	}
	string invokeID;
private:
	char* theDepartment;
	int theDepartmentLen;
	virtual int GetMyMemSize();
};

///Type_ACD_DelDepartmentConf
struct SIPCCMsg_ACD_DelDepartmentConf : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_DelDepartmentConf();
	~SIPCCMsg_ACD_DelDepartmentConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(theDepartment != NULL)	delete theDepartment;
		theDepartment = NULL;
		theDepartmentLen = 0;
	}
	void SetTheDepartment(string thedepartment);
	string GetTheDepartment()	
	{
		if(theDepartmentLen==0)	return "";
		return string(theDepartment);
	}
private:
	char* theDepartment;
	int theDepartmentLen;
	virtual int GetMyMemSize();
};

///Type_ACD_MediaRequest
struct SIPCCMsg_ACD_MediaRequest : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_MediaRequest();
	~SIPCCMsg_ACD_MediaRequest()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(callID!=NULL)	delete callID;
		callID = NULL;
		callIDLen = 0;
		mediaType = -1;
	}
	void SetCallID(string callid);
	string GetCallID()	
	{
		if(callIDLen==0)	return "";
		return string(callID);
	}
	
	int mediaType;
	int seq;
private:
	char* callID;
	int callIDLen;
	virtual int GetMyMemSize();
};

///Type_ACD_MediaRequestConf
struct SIPCCMsg_ACD_MediaRequestConf : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_MediaRequestConf();
	~SIPCCMsg_ACD_MediaRequestConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(callID!=NULL)	delete callID;
		callID = NULL;
		callIDLen = 0;
		mediaType = -1;
	}
	void SetCallID(string callid);
	string GetCallID()	
	{
		if(callIDLen==0)	return "";
		return string(callID);
	}
	
	int mediaType;
private:
	char* callID;
	int callIDLen;
	virtual int GetMyMemSize();
};

///Type_ACD_ReloadDepartments
struct SIPCCMsg_ACD_LoadDepartments : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_LoadDepartments();
	~SIPCCMsg_ACD_LoadDepartments()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	string serverIP;
	int acdserverID;
private:
	virtual int GetMyMemSize();
};

///Type_ACD_CallingQueueInfo
struct SIPCCMsg_ACD_CallingQueueInfo : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_CallingQueueInfo();
	~SIPCCMsg_ACD_CallingQueueInfo()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		userNumInQueue = 0;
		agentNumInTheDepartment = 0;

		userNumInQueues = "";
		agentNumInSkillGroups = "";
	}
	
	int userNumInQueue;
	int agentNumInTheDepartment;
	string invokeID;

	string userNumInQueues;
	string agentNumInSkillGroups;
private:
	virtual int GetMyMemSize();
};

///Type_ACD_AgentQueryStateConf
struct SIPCCMsg_ACD_AgentQueryStateConf : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_AgentQueryStateConf();
	~SIPCCMsg_ACD_AgentQueryStateConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		agentState = Agent_NoLogin;
		bQuerySucess = 0;
		
		if(additionalInfo!=NULL)	delete additionalInfo;
		additionalInfo = NULL;
		additionalInfoLen = 0;
	}
	void SetAdditionalInfo(string additionalinfo);
	string GetAdditionalInfo()	
	{
		if(additionalInfoLen==0)	return "";
		return string(additionalInfo);
	}
	int agentState;
	char bQuerySucess;
	
	string callTransID;
	string handleId;		//操作唯一标识
private:
	char* additionalInfo;
	int additionalInfoLen;
	virtual int GetMyMemSize();
};

///Type_ACD_AgentMakeCallConf
struct SIPCCMsg_ACD_AgentMakeCallConf : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_AgentMakeCallConf();
	~SIPCCMsg_ACD_AgentMakeCallConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		callingState = AgentCalling_AgentNoLogin;
		userNumInQueue = 0;
		audioIP = 0;
		audioPort = 0;
		if(calledParty!=NULL)	delete calledParty;
		calledParty = NULL;
		calledPartyLen = 0;
	}
	
	int callingState;
	int userNumInQueue;
	unsigned long audioIP;
	unsigned short audioPort;
	
	void SetCalledParty(string calledparty);
	string GetCalledParty()	
	{
		if(calledPartyLen==0)	return "";
		return string(calledParty);
	}
	
	unsigned long lanIP;
	unsigned short lanMainSockPort;
	
	string agentExtNo;
private:
	char* calledParty;
	int calledPartyLen;
	virtual int GetMyMemSize();
};

///Type_ACD_CallUserConf
struct SIPCCMsg_ACD_CallUserConf : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_CallUserConf();
	~SIPCCMsg_ACD_CallUserConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(userName!=NULL)	delete userName;	
		userName = NULL;
		userNameLen = 0;
		bCallFailed = 1;
		audioIP = 0;
		audioPort = 0;
		sipBoardIP = 0;   //交换机ip板IP
		sipBoardRtpPort = 0;  //交换机ip板RtpPort
		sipBoardRtcpPort = 0;  //交换机ip板rtcpPort
		sipTransIP = 0;   //中转IP
		sipTransRtpPort = 0;  //中转RtpPort
		sipTransRtcpPort = 0;  //中转rtcpPort
	}
	void SetUserName(string username);
	string GetUserName()
	{
		if(userNameLen == 0)			return "";
		return string(userName);
	}
	
	int failedCause;
	char bCallFailed;
	unsigned long audioIP;
	unsigned short audioPort;
	unsigned long lanIP;
	
	string invokeID;
	
	unsigned long sipBoardIP;   //交换机ip板IP
	unsigned short sipBoardRtpPort;  //交换机ip板RtpPort
	unsigned short sipBoardRtcpPort;  //交换机ip板rtcpPort
	unsigned long sipTransIP;   //中转IP
	unsigned short sipTransRtpPort;  //中转RtpPort
	unsigned short sipTransRtcpPort;  //中转rtcpPort

	unsigned short conferencePort1;		//座席端用于会议的端口1
	unsigned short conferencePort2;		//座席端用于会议的端口2
private:
	char* userName;
	int userNameLen;
	
	virtual int GetMyMemSize();
public:
	/////////////////媒体信息描述/////////////////
	//传输方式，决定包格式
	//UDP/OLD	固定长度包，根据协商的编码和单位时间决定包长度
	//UDP/V1	变长包，包自身可以表述负载大小，暂时不用
	string trans;
	//编码方式
	//G729
	//ILBC
	string codec;
	//单位时间
	size_t unit;
	///////////////////////////////////////////////
};

///Type_ACD_CallUserFailed
struct SIPCCMsg_ACD_CallUserFailed : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_CallUserFailed();
	~SIPCCMsg_ACD_CallUserFailed()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(userName!=NULL)	delete userName;	
		userName = NULL;
		userNameLen = 0;
	}
	void SetUserName(string username);
	string GetUserName()
	{
		if(userNameLen == 0)			return "";
		return string(userName);
	}
	
	int failedCause;
	
private:
	char* userName;
	int userNameLen;
	
	virtual int GetMyMemSize();
};

///Type_ACD_AgentHoldCall
struct SIPCCMsg_ACD_AgentHoldCall : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_AgentHoldCall();
	~SIPCCMsg_ACD_AgentHoldCall()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(heldParty!=NULL)	delete heldParty;	
		heldParty = NULL;
		heldPartyLen = 0;
	}
	void SetHeldParty(string heldparty);
	string GetHeldParty()
	{
		if(heldPartyLen == 0)			return "";
		return string(heldParty);
	}
	
private:
	char* heldParty;
	int heldPartyLen;
	
	virtual int GetMyMemSize();
};

///Type_ACD_AgentUnHoldCall
struct SIPCCMsg_ACD_AgentUnHoldCall : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_AgentUnHoldCall();
	~SIPCCMsg_ACD_AgentUnHoldCall()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(heldParty!=NULL)	delete heldParty;	
		heldParty = NULL;
		heldPartyLen = 0;
	}
	void SetHeldParty(string heldparty);
	string GetHeldParty()
	{
		if(heldPartyLen == 0)			return "";
		return string(heldParty);
	}
	
private:
	char* heldParty;
	int heldPartyLen;
	
	virtual int GetMyMemSize();
};

///Type_ACD_AgentHoldCallConf
struct SIPCCMsg_ACD_AgentHoldCallConf : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_AgentHoldCallConf();
	~SIPCCMsg_ACD_AgentHoldCallConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		bHoldSucc = 0;
	}
	
	char bHoldSucc;
	
private:
	virtual int GetMyMemSize();
};

///Type_ACD_NotifyDataCollect
struct SIPCCMsg_ACD_NotifyDataCollect : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_NotifyDataCollect();
	~SIPCCMsg_ACD_NotifyDataCollect()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		theMinute = -1;
		CurrentHour = 0;
	}
	
	int theMinute;
	int CurrentHour;
	
	string collectDate;
	string sData;
private:
	virtual int GetMyMemSize();
};

///Type_ACD_PrepareTransfer
struct SIPCCMsg_ACD_PrepareTransfer : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_PrepareTransfer();
	~SIPCCMsg_ACD_PrepareTransfer()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(callID!=NULL)	delete callID;	
		callID = NULL;
		callIDLen = 0;
		if(otherParty!=NULL)	delete otherParty;	
		otherParty = NULL;
		otherPartyLen = 0;
	}
	void SetCallID(string callid);
	string GetCallID()
	{
		if(callIDLen == 0)			return "";
		return string(callID);
	}
	
	void SetOtherParty(string otherParty);
	string GetOtherParty()
	{
		if(otherPartyLen == 0)			return "";
		return string(otherParty);
	}
public:
	int otherPartyType;
	unsigned long AudioIp;
	unsigned short AudioPort;
	unsigned long lanIP;
private:
	char* callID;
	int callIDLen;
	char* otherParty;
	int otherPartyLen;
	virtual int GetMyMemSize();
};

///Type_ACD_TransReady
struct SIPCCMsg_ACD_TransReady : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_TransReady();
	~SIPCCMsg_ACD_TransReady()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(readyParty!=NULL)	delete readyParty;	
		readyParty = NULL;
		readyPartyLen = 0;
	}
	
	void SetReadyParty(string readyparty);
	string GetReadyParty()
	{
		if(readyPartyLen == 0)			return "";
		return string(readyParty);
	}
	
private:
	char* readyParty;
	int readyPartyLen;
	
	virtual int GetMyMemSize();
};

///Type_ACD_TransferCall
struct SIPCCMsg_ACD_TransferCall : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_TransferCall();
	~SIPCCMsg_ACD_TransferCall()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(presideAgent!=NULL)	delete presideAgent;	
		presideAgent = NULL;
		presideAgentLen = 0;
		if(otherParty!=NULL)	delete otherParty;	
		otherParty = NULL;
		otherPartyLen = 0;
		if(theParty!=NULL)	delete theParty;	
		theParty = NULL;
		thePartyLen = 0;
	}
	void SetPresideAgent(string presideagent);
	string GetPresideAgent()
	{
		if(presideAgentLen == 0)			return "";
		return string(presideAgent);
	}
	void SetOtherParty(string otherparty);
	string GetOtherParty()
	{
		if(otherPartyLen == 0)			return "";
		return string(otherParty);
	}
	void SetTheParty(string theparty);
	string GetTheParty()
	{
		if(thePartyLen == 0)			return "";
		return string(theParty);
	}
public:
	int otherPartyType;
	
	string userLineNo;
	unsigned long userLineIp;
	unsigned short userLinePort;
private:
	char* theParty;
	int thePartyLen;
	char* presideAgent;
	int presideAgentLen;
	char* otherParty;
	int otherPartyLen;
	
	virtual int GetMyMemSize();
public:
	/////////////////媒体信息描述/////////////////
	//传输方式，决定包格式
	//UDP/OLD	固定长度包，根据协商的编码和单位时间决定包长度
	//UDP/V1	变长包，包自身可以表述负载大小，暂时不用
	string trans;
	//编码方式
	//G729
	//ILBC
	string codec;
	//单位时间
	size_t unit;
	///////////////////////////////////////////////	
};

///Type_ACD_ClearPreConnection
struct SIPCCMsg_ACD_ClearPreConnection : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_ClearPreConnection();
	~SIPCCMsg_ACD_ClearPreConnection()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(notifier!=NULL)	delete notifier;	
		notifier = NULL;
		notifierLen = 0;
	}
	
	void SetNotifier(string theNotifier);
	string GetNotifier()
	{
		if(notifierLen == 0)			return "";
		return string(notifier);
	}
	
private:
	char* notifier;
	int notifierLen;
	virtual int GetMyMemSize();
};

///Type_ACD_DepartNAgentInfo
struct SIPCCMsg_ACD_DepartNAgentInfo : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_DepartNAgentInfo();
	~SIPCCMsg_ACD_DepartNAgentInfo()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(theInfo!=NULL)	delete theInfo;	
		theInfo = NULL;
		theInfoLen = 0;
	}
	
	void SetTheInfo(string theinfo);
	string GetTheInfo()
	{
		if(theInfoLen == 0)			return "";
		return string(theInfo);
	}
	
	char bEnd;
	string invokeID;
	string deptNickname;
private:
	char* theInfo;
	int theInfoLen;
	virtual int GetMyMemSize();
};

///Type_ACD_GroupInfo
struct SIPCCMsg_ACD_GroupInfo : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_GroupInfo();
	~SIPCCMsg_ACD_GroupInfo()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(corporationName != NULL)	delete corporationName;
		corporationName = NULL;
		corporationNameLen = 0;
		if(theInfo!=NULL)	delete theInfo;	
		theInfo = NULL;
		theInfoLen = 0;
	}
	void SetCorporationName(string corporationname);
	string GetCorporationName()
	{
		if(corporationNameLen==0)	return "";
		return string(corporationName);
	}
	void SetTheInfo(string theinfo);
	string GetTheInfo()
	{
		if(theInfoLen == 0)			return "";
		return string(theInfo);
	}
	
	int groupNum;
	int currentTime;
	string invokeID;
private:
	char* corporationName;
	int corporationNameLen;
	char* theInfo;
	int theInfoLen;
	virtual int GetMyMemSize();
};

///Type_ACD_NotifyAgentStateEvent
struct SIPCCMsg_ACD_NotifyAgentStateEvent : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_NotifyAgentStateEvent();
	~SIPCCMsg_ACD_NotifyAgentStateEvent()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(corporationName != NULL)	delete corporationName;
		corporationName = NULL;
		corporationNameLen = 0;
		if(theDepartment!=NULL)	delete theDepartment;
		theDepartment = NULL;
		theDepartmentLen = 0;
		if(agentID!=NULL)	delete agentID;
		agentID = NULL;
		agentIDLen = 0;
		if(curTime!=NULL)	delete curTime;
		curTime = NULL;
		curTimeLen =0;
		if(callTarger!=NULL)	delete callTarger;
		callTarger = NULL;
		callTargerLen = 0;
	}
	
	void SetCurrentTime(string currenttime);
	string GetCurrentTime()
	{
		if (curTimeLen == 0) return"";
		if ( !(VerifyData(curTimeLen, CURTIME_LEN)) ) {return "";}
		return string(curTime);
	}
	
	void SetCallTarger(string calltarger);
	string GetCallTarger()
	{
		if(callTargerLen == 0) return "";
		if ( !(VerifyData(callTargerLen, CALLTARGER_LEN)) ) {return "";}
		return string(callTarger);
	}
	
	void SetCorporationName(string corporationname);
	string GetCorporationName()
	{
		if(corporationNameLen==0)	return "";
		if ( !(VerifyData(corporationNameLen, CORPNAME_LEN)) ) {return "";}
		return string(corporationName);
	}
	void SetTheDepartment(string thedepartment);
	string GetTheDepartment()	
	{
		if(theDepartmentLen==0)	return "";
		if ( !(VerifyData(theDepartmentLen, CORPNDEPT_LEN)) ) {return "";}
		return string(theDepartment);
	}
	void SetAgentID(string agentID);
	string GetAgentID()	
	{
		if(agentIDLen==0)	return "";
		if ( !(VerifyData(agentIDLen, AGENTID_LEN)) ) {return "";}
		return string(agentID);
	}
	
	int stateEvent;
private:
	char* curTime;			//事件发生时间
	int curTimeLen;
	char* callTarger;		//目标
	int callTargerLen;		
	char* corporationName;
	int corporationNameLen;
	char* theDepartment;
	int theDepartmentLen;
	char* agentID;
	int agentIDLen;
	virtual int GetMyMemSize();
};

///Type_ACD_VDNStatusInfo
struct SIPCCMsg_ACD_VDNStatusInfo : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_VDNStatusInfo();
	~SIPCCMsg_ACD_VDNStatusInfo()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(endTime != NULL)	delete endTime;
		endTime = NULL;
		endTimeLen = 0;
		if(callerNo!=NULL)	delete callerNo;
		callerNo = NULL;
		callerNoLen = 0;
		if(calledNo!=NULL)	delete calledNo;
		calledNo = NULL;
		calledNoLen = 0;
		if(corporationName!=NULL)	delete corporationName;
		corporationName = NULL;
		corporationNameLen =0;
		if(theDepartment!=NULL)	delete theDepartment;
		theDepartment = NULL;
		theDepartmentLen = 0;
		if(agentID!=NULL)	delete agentID;
		agentID = NULL;
		agentIDLen = 0;
	}
	
	void SetEndTime(string endtime);
	string GetEndTime()
	{
		if (endTimeLen == 0) return"";
		return string(endTime);
	}
	void SetCallerNo(string callerNo);
	string GetCallerNo()
	{
		if(callerNoLen == 0) return "";
		return string(callerNo);
	}
	void SetCalledNo(string calledNo);
	string GetCalledNo()
	{
		if(calledNoLen == 0) return "";
		return string(calledNo);
	}
	void SetCorporationName(string corporationname);
	string GetCorporationName()
	{
		if(corporationNameLen==0)	return "";
		return string(corporationName);
	}
	void SetTheDepartment(string thedepartment);
	string GetTheDepartment()	
	{
		if(theDepartmentLen==0)	return "";
		return string(theDepartment);
	}
	void SetAgentID(string agentID);
	string GetAgentID()	
	{
		if(agentIDLen==0)	return "";
		return string(agentID);
	}
	
	int callType;			//呼叫类型
	int endCause;
	int queueTimeSpan;		//排队时长
	int responseTimeSpan;	//响应时长
private:
	char* endTime;			//事件发生时间
	int endTimeLen;
	char* callerNo;			//主叫
	int callerNoLen;
	char* calledNo;			//被叫
	int calledNoLen;
	char* corporationName;	
	int corporationNameLen;	
	char* theDepartment;
	int theDepartmentLen;
	char* agentID;
	int agentIDLen;
	virtual int GetMyMemSize();
};

///Type_ACD_MediaReady
struct SIPCCMsg_ACD_MediaReady : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_MediaReady();
	~SIPCCMsg_ACD_MediaReady()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
private:
	virtual int GetMyMemSize();
};

///Type_ACD_ForceLogout
struct SIPCCMsg_ACD_ForceLogout : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_ForceLogout();
	~SIPCCMsg_ACD_ForceLogout()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	string agentName;
	int cause;
private:
	virtual int GetMyMemSize();
};

///ACD_PreConference
struct SIPCCMsg_ACD_PreConference : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_PreConference();
	~SIPCCMsg_ACD_PreConference()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	};
	
	string presideParty;
	int presidePartyType;
	unsigned long presidePartyIP;
	unsigned short presidePartyPort;
	string otherJoinParty;
	int otherJoinPartyType;
	unsigned long otherJoinPartyIP;
	unsigned short otherJoinPartyPort;
	
private:
	virtual int GetMyMemSize();
};

///ACD_Conference
struct SIPCCMsg_ACD_Conference : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_Conference();
	~SIPCCMsg_ACD_Conference()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	};
	
	string presideParty;
	int presidePartyType;
	string otherJoinParty;
	int otherJoinPartyType;
	
private:
	virtual int GetMyMemSize();
};

///Type_ACD_UserMakeCallPSTN
struct SIPCCMsg_ACD_UserMakeCallPSTN : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_UserMakeCallPSTN();
	~SIPCCMsg_ACD_UserMakeCallPSTN()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(callID!=NULL)	delete callID;
		callID = NULL;
		callIDLen = 0;
		if(userName!=NULL)	delete userName;
		userName = NULL;
		userNameLen = 0;
		if(targetPosition!=NULL)	delete targetPosition;
		targetPosition = NULL;
		targetPositionLen = 0;
		if(uuiData!=NULL)	delete uuiData;
		uuiData = NULL;
		uuiDataLen = 0;
		if(corporationName != NULL)	delete corporationName;
		corporationName = NULL;
		corporationNameLen = 0;
	}
	void SetCallID(string callid);
	string GetCallID()
	{
		if(callIDLen==0)	return "";
		return string(callID);
	}
	void SetUserName(string username);
	string GetUserName()
	{
		if(userNameLen==0)	return "";
		return string(userName);
	}
	void SetTargetPosition(string targetposition);
	string GetTargetPosition()
	{
		if(targetPositionLen==0)	return "";
		return string(targetPosition);
	}
	void SetUUIData(string uuidata);
	string GetUUIData()	
	{
		if(uuiDataLen==0)	return "";
		return string(uuiData);
	}
	void SetCorporationName(string corporationname);
	string GetCorporationName()
	{
		if(corporationNameLen==0)	return "";
		return string(corporationName);
	}
	int targetType;
	
	string callerNoForSend;
	string curVersion;
	
private:
	char* callID;	//座席呼座席、座席呼 skillGroup 用,带给被叫/被分配座席,记报表
	int callIDLen;
	char* userName;
	int userNameLen;
	char* targetPosition;
	int targetPositionLen;
	char* uuiData;
	int uuiDataLen;
	char* corporationName;
	int corporationNameLen;
	
	virtual int GetMyMemSize();
};


///Type_ACD_UserMakeCallPSTN2
struct SIPCCMsg_ACD_UserMakeCallPSTN2 : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_UserMakeCallPSTN2();
	~SIPCCMsg_ACD_UserMakeCallPSTN2()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(callID!=NULL)	delete callID;
		callID = NULL;
		callIDLen = 0;
		if(userName!=NULL)	delete userName;
		userName = NULL;
		userNameLen = 0;
		if(targetPosition!=NULL)	delete targetPosition;
		targetPosition = NULL;
		targetPositionLen = 0;
		if(uuiData!=NULL)	delete uuiData;
		uuiData = NULL;
		uuiDataLen = 0;
		if(corporationName != NULL)	delete corporationName;
		corporationName = NULL;
		corporationNameLen = 0;
	}
	void SetCallID(string callid);
	string GetCallID()
	{
		if(callIDLen==0)	return "";
		return string(callID);
	}
	void SetUserName(string username);
	string GetUserName()
	{
		if(userNameLen==0)	return "";
		return string(userName);
	}
	void SetTargetPosition(string targetposition);
	string GetTargetPosition()
	{
		if(targetPositionLen==0)	return "";
		return string(targetPosition);
	}
	void SetUUIData(string uuidata);
	string GetUUIData()	
	{
		if(uuiDataLen==0)	return "";
		return string(uuiData);
	}
	void SetCorporationName(string corporationname);
	string GetCorporationName()
	{
		if(corporationNameLen==0)	return "";
		return string(corporationName);
	}
	int targetType;
	
	string callerNoForSend;
	string curVersion;
	string invokeID;
	
private:
	char* callID;	//座席呼座席、座席呼 skillGroup 用,带给被叫/被分配座席,记报表
	int callIDLen;
	char* userName;
	int userNameLen;
	char* targetPosition;
	int targetPositionLen;
	char* uuiData;
	int uuiDataLen;
	char* corporationName;
	int corporationNameLen;
	
	virtual int GetMyMemSize();
};


///Type_ACD_RingAgentExt
struct SIPCCMsg_ACD_RingAgentExt : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_RingAgentExt();
	~SIPCCMsg_ACD_RingAgentExt()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(callID!=NULL)	delete callID;
		callID = NULL;
		callIDLen = 0;
		if(agentID!=NULL)	delete agentID;
		agentID = NULL;
		agentIDLen = 0;
		if(targetPosition!=NULL)	delete targetPosition;
		targetPosition = NULL;
		targetPositionLen = 0;
		if(uuiData!=NULL)	delete uuiData;
		uuiData = NULL;
		uuiDataLen = 0;
		if(corporationName != NULL)	delete corporationName;
		corporationName = NULL;
		corporationNameLen = 0;
	}
	void SetCallID(string callid);
	string GetCallID()
	{
		if(callIDLen==0)	return "";
		if ( !(VerifyData(callIDLen, CALLID_LEN)) ) {return "";}
		return string(callID);
	}
	void SetAgentID(string agentid);
	string GetAgentID()
	{
		if(agentIDLen==0)	return "";
		if ( !(VerifyData(agentIDLen, AGENTID_LEN)) ) {return "";}
		return string(agentID);
	}
	void SetTargetPosition(string targetposition);
	string GetTargetPosition()
	{
		if(targetPositionLen==0)	return "";
		if ( !(VerifyData(targetPositionLen, TARGETPOSITION_LEN)) ) {return "";}
		return string(targetPosition);
	}
	void SetUUIData(string uuidata);
	string GetUUIData()	
	{
		if(uuiDataLen==0)	return "";
		if ( !(VerifyData(uuiDataLen, UUIDATA_LEN)) ) {return "";}
		return string(uuiData);
	}
	void SetCorporationName(string corporationname);
	string GetCorporationName()
	{
		if(corporationNameLen==0)	return "";
		if ( !(VerifyData(corporationNameLen, CORPNAME_LEN)) ) {return "";}
		return string(corporationName);
	}
	int targetType;
	
	string callerNoForSend;
	string curVersion;
	
	string ipPhoneNo_User;
	char IsOutCall;

	string  managerId;

private:
	char* callID;	//座席呼座席、座席呼 skillGroup 用,带给被叫/被分配座席,记报表
	int callIDLen;
	char* agentID;
	int agentIDLen;
	char* targetPosition;
	int targetPositionLen;
	char* uuiData;
	int uuiDataLen;
	char* corporationName;
	int corporationNameLen;
	
	virtual int GetMyMemSize();
};

///Type_ACD_RingAgentExt2
struct SIPCCMsg_ACD_RingAgentExt2 : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_RingAgentExt2();
	~SIPCCMsg_ACD_RingAgentExt2()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(callID!=NULL)	delete callID;
		callID = NULL;
		callIDLen = 0;
		if(agentID!=NULL)	delete agentID;
		agentID = NULL;
		agentIDLen = 0;
		if(targetPosition!=NULL)	delete targetPosition;
		targetPosition = NULL;
		targetPositionLen = 0;
		if(uuiData!=NULL)	delete uuiData;
		uuiData = NULL;
		uuiDataLen = 0;
		if(corporationName != NULL)	delete corporationName;
		corporationName = NULL;
		corporationNameLen = 0;
	}
	void SetCallID(string callid);
	string GetCallID()
	{
		if(callIDLen==0)	return "";
		if ( !(VerifyData(callIDLen, CALLID_LEN)) ) {return "";}
		return string(callID);
	}
	void SetAgentID(string agentid);
	string GetAgentID()
	{
		if(agentIDLen==0)	return "";
		if ( !(VerifyData(agentIDLen, AGENTID_LEN)) ) {return "";}
		return string(agentID);
	}
	void SetTargetPosition(string targetposition);
	string GetTargetPosition()
	{
		if(targetPositionLen==0)	return "";
		if ( !(VerifyData(targetPositionLen, TARGETPOSITION_LEN)) ) {return "";}
		return string(targetPosition);
	}
	void SetUUIData(string uuidata);
	string GetUUIData()	
	{
		if(uuiDataLen==0)	return "";
		if ( !(VerifyData(uuiDataLen, UUIDATA_LEN)) ) {return "";}
		return string(uuiData);
	}
	void SetCorporationName(string corporationname);
	string GetCorporationName()
	{
		if(corporationNameLen==0)	return "";
		if ( !(VerifyData(corporationNameLen, CORPNAME_LEN)) ) {return "";}
		return string(corporationName);
	}
	int targetType;
	
	string callerNoForSend;
	string curVersion;
	string invokeID;
	int usableTime;
	
	unsigned long lanIp;
	
	int outDialType;
	
	string CalledAgentID;
	string calledAgentLineNo;
	unsigned long calledAgentLineIp;
	unsigned short calledAgentLinePort;
	
	string  callTransID;

	string  managerId;

private:
	char* callID;	//座席呼座席、座席呼 skillGroup 用,带给被叫/被分配座席,记报表
	int callIDLen;
	char* agentID;
	int agentIDLen;
	char* targetPosition;
	int targetPositionLen;
	char* uuiData;
	int uuiDataLen;
	char* corporationName;
	int corporationNameLen;
	
	virtual int GetMyMemSize();
};

///Type_ACD_QueryGW
struct SIPCCMsg_ACD_QueryGW : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_QueryGW();
	~SIPCCMsg_ACD_QueryGW()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	string corporationName;
	string departName;
	string calledNo;
	string agentID;
private:
	virtual int GetMyMemSize();
};

///Type_ACD_IsAgentLoginConf
struct SIPCCMsg_ACD_IsAgentLoginConf : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_IsAgentLoginConf();
	~SIPCCMsg_ACD_IsAgentLoginConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	string agentID;
	char bIsAgentLogin;
	int agentState;
	int loginType;
	
	int invokeType;
	string invokeId;

	string  handleId;

private:
	virtual int GetMyMemSize();
};

///Type_ACD_NotifyAgent
struct SIPCCMsg_ACD_NotifyAgent : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_NotifyAgent();
	~SIPCCMsg_ACD_NotifyAgent()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	string notificationInfo;
private:
	virtual int GetMyMemSize();
};

///Type_ACD_CallEnterVDN
struct SIPCCMsg_ACD_CallEnterVDN : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_CallEnterVDN()
	{
		msgType=Type_ACD_CallEnterVDN;
		corpName = "";
		vdnNo = "";
		vdnName = "";
		callID = "";
		callerID = "";
		calleeID = "";
		callSrc = "";
		extDevID = "";
		enterTime = "";
		status = -1;
		callType = -1;
		bIsOverflow = 0;
		managerid = "";
		deptid = "";
		CurQueueNum = 0;
		bInnerCall = 0;
		bIntoQueue = 1;

		SkillGroupID = "";
		SkillGroupName = "";
		UserLevel = 3;
		sData="";
	}
	~SIPCCMsg_ACD_CallEnterVDN()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	string corpName;
	string vdnNo;
	string vdnName;
	string callID;
	string callerID;
	string calleeID;
	string callSrc;
	string extDevID;
	string enterTime;
	int status;
	int callType;
	char bIsOverflow;
	string managerid;
	string deptid;
	int CurQueueNum;	// 当前组内排队数
	char bInnerCall;
	char bIntoQueue;	// 是否进入队列

	string SkillGroupID;
	string SkillGroupName;
	int UserLevel;
	string sData;
private:
	virtual int GetMyMemSize();
};

///Type_ACD_CallLeaveVDN
struct SIPCCMsg_ACD_CallLeaveVDN : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_CallLeaveVDN()
	{
		msgType=Type_ACD_CallLeaveVDN;
		vdnNo = "";
		callID = "";
		leaveTime = "";
		leaveCause = -1;
		corpName = "";
		managerid = "";
		deptid = "";
		bIntoQueue = 1;
		CurQueueNum = 0;

		SkillGroupID = "";
		SkillGroupName = "";
		UserLevel = 3;
		sData="";
	}
	~SIPCCMsg_ACD_CallLeaveVDN()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	string vdnNo;
	string callID;
	string leaveTime;
	int leaveCause;
	string corpName;
	string managerid;
	string deptid;
	string LeaveQueueTime;   //出队列时间，放弃和溢出时= leaveTime;响应时= leaveTime-振铃时长
	string agentID;          //如果座席应答或座席振铃时放弃，则填入AgentID
	char bIntoQueue;	// 是否进入队列
	int CurQueueNum;	// 当前组内排队数

	string SkillGroupID;
	string SkillGroupName;
	int UserLevel;
	string sData;
private:
	virtual int GetMyMemSize();
};

///Type_ACD_RecInfo2Client
struct SIPCCMsg_ACD_RecInfo2Client : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_RecInfo2Client()
	{
		msgType=Type_ACD_RecInfo2Client;
		invokeID = "";
		fullPathFileName = "";
	}
	~SIPCCMsg_ACD_RecInfo2Client()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	string invokeID;
	string fullPathFileName;
private:
	virtual int GetMyMemSize();
};

///Type_ACD_SuperDisconnect
struct SIPCCMsg_ACD_SuperDisconnect : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_SuperDisconnect()
	{
		msgType=Type_ACD_SuperDisconnect;
	}
	~SIPCCMsg_ACD_SuperDisconnect()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
private:
	virtual int GetMyMemSize();
};

///Type_ACD_ReturnToAgent
struct SIPCCMsg_ACD_ReturnToAgent : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_ReturnToAgent();
	~SIPCCMsg_ACD_ReturnToAgent()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		IVRUUIData = "";
		bIsSuccess = 0;
		bIsAgentWaiting = 0;
	}
	
	string IVRUUIData;
	char bIsSuccess;
	char bIsAgentWaiting;

	string  handleId;
	
private:
	virtual int GetMyMemSize();
};


///Class_ACD
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
///Class_P2P
struct SIPCCMsg_P2P : public SIPCCMessage
{
	SIPCCMsg_P2P();
	~SIPCCMsg_P2P()
	{
		ReleaseMemory();
	};
	
	virtual int GetMyMemSize(){return 0;}
	virtual int FillBuf(char*& thebuf){return 0;}
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0){}
	virtual void ReleaseMemory(){}
};

///Type_P2P_ConnRequest
struct SIPCCMsg_P2P_ConnRequest : public SIPCCMsg_P2P
{
	SIPCCMsg_P2P_ConnRequest();
	~SIPCCMsg_P2P_ConnRequest()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(callID!=NULL)	delete callID;
		callID = NULL;
		callIDLen = 0;
		//		clientType = 0;
		mediaType = -1;
		localIP = 0;
		localPort = 0;
		natType = -1;
	}
	void SetCallID(string callid);
	string GetCallID()	
	{
		if(callIDLen==0)	return "";
		return string(callID);
	}
	
	//	int clientType;		//用户还是座席
	int mediaType;
	unsigned long localIP;
	unsigned short localPort;
	int natType;
	int seq;
	char lastReqIsTest; //上次请求时是否首先发出TestMsg的一方
private:
	char* callID;
	int callIDLen;
	virtual int GetMyMemSize();
};

///Type_P2P_MakeHoleCmd
struct SIPCCMsg_P2P_MakeHoleCmd : public SIPCCMsg_P2P
{
	SIPCCMsg_P2P_MakeHoleCmd();
	~SIPCCMsg_P2P_MakeHoleCmd()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		targetIP = 0;
		targetPort = 0;
		
		if (callID != NULL)	delete callID;
		callID = NULL;
		callIDLen = 0;
		
		bNeedGuess = 0;
	}
	
	void SetCallID(string callid)
	{
		int iCallIDLen = callid.length();
		this->callIDLen = iCallIDLen + 1;
		this->callID = new char[callIDLen];
		memset(callID, 0, callIDLen);
		memcpy(callID, callid.c_str(), iCallIDLen);
	}
	string GetCallID()	
	{
		if(callIDLen==0)	return "";
		return string(callID);
	}
	
	unsigned long targetIP;
	unsigned short targetPort;
	char bNeedGuess;
private:
	char* callID;
	int callIDLen;	
	virtual int GetMyMemSize();
};

///Type_P2P_MakeHoleCmdConf
struct SIPCCMsg_P2P_MakeHoleCmdConf : public SIPCCMsg_P2P
{
	SIPCCMsg_P2P_MakeHoleCmdConf();
	~SIPCCMsg_P2P_MakeHoleCmdConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		//userIP = 0;
		//userPort = 0;
		
		if (callID != NULL)	delete callID;
		callID = NULL;
		callIDLen = 0;
	}
	//unsigned long userIP;
	//unsigned short userPort;
	
	void SetCallID(string callid)
	{
		int iCallIDLen = callid.length();
		this->callIDLen = iCallIDLen + 1;
		this->callID = new char[callIDLen];
		memset(callID, 0, callIDLen);
		memcpy(callID, callid.c_str(), iCallIDLen);
	}
	string GetCallID()	
	{
		if(callIDLen==0)	return "";
		return string(callID);
	}
private:
	char* callID;
	int callIDLen;
	virtual int GetMyMemSize();
};

///Type_P2P_MakeHoleMsg
struct SIPCCMsg_P2P_MakeHoleMsg : public SIPCCMsg_P2P
{
	SIPCCMsg_P2P_MakeHoleMsg();
	~SIPCCMsg_P2P_MakeHoleMsg()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
private:
	virtual int GetMyMemSize();
};

///Type_P2P_ConnRequestConf
struct SIPCCMsg_P2P_ConnRequestConf : public SIPCCMsg_P2P
{
	SIPCCMsg_P2P_ConnRequestConf();
	~SIPCCMsg_P2P_ConnRequestConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		//agentIP = 0;
		//agentPort = 0;
		
		targetIP = 0;
		targetPort = 0;
	}
	//unsigned long agentIP;
	//unsigned short agentPort;
	
	unsigned long targetIP;
	unsigned short targetPort;
	char bNeedGuess;
private:
	virtual int GetMyMemSize();
};

///Type_P2P_TestMsg
struct SIPCCMsg_P2P_TestMsg : public SIPCCMsg_P2P
{
	SIPCCMsg_P2P_TestMsg();
	~SIPCCMsg_P2P_TestMsg()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		seq = 0;
	}
	unsigned char seq;
private:
	virtual int GetMyMemSize();
};

///Type_P2P_TestMsgConf
struct SIPCCMsg_P2P_TestMsgConf : public SIPCCMsg_P2P
{
	SIPCCMsg_P2P_TestMsgConf();
	~SIPCCMsg_P2P_TestMsgConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(mediaHeadData != NULL)	delete mediaHeadData;
		mediaHeadData = NULL;
		mediaHeadDataLen = 0;
		seq = 0;
	}
	void SetMediaHeadData(char* mediaheaddata, int len);
	int GetMediaHeadData(char* mediaheaddata)
	{
		if(mediaHeadDataLen>0)
			memcpy(mediaheaddata, mediaHeadData, mediaHeadDataLen);
		return mediaHeadDataLen;
	}
	
	unsigned char seq;
private:
	virtual int GetMyMemSize();
	char* mediaHeadData;
	int mediaHeadDataLen;
};

///Type_P2P_DirectConn
struct SIPCCMsg_P2P_DirectConn : public SIPCCMsg_P2P
{
	SIPCCMsg_P2P_DirectConn();
	~SIPCCMsg_P2P_DirectConn()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		oppIP = 0;
		oppPort = 0;
	}
	
	unsigned long oppIP;
	unsigned short oppPort;
private:
	virtual int GetMyMemSize();
};

///SIPCCMsg_P2P_ConnDifficultMsg
struct SIPCCMsg_P2P_ConnDifficultMsg : public SIPCCMsg_P2P
{
	SIPCCMsg_P2P_ConnDifficultMsg();
	~SIPCCMsg_P2P_ConnDifficultMsg()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		natType = -1;
	}
	int natType;
private:
	virtual int GetMyMemSize();
};

struct SIPCCMsg_P2P_CheckNatRequest : public SIPCCMsg_P2P
{
	SIPCCMsg_P2P_CheckNatRequest();
	~SIPCCMsg_P2P_CheckNatRequest()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		RequestID = 0;
		RequestSeq = 0;
		ConfSeq = 0;
	}
	int RequestID;
	int RequestSeq;
	char ConfSeq;
private:
	virtual int GetMyMemSize();
};

struct SIPCCMsg_P2P_CheckNatConf : public SIPCCMsg_P2P
{
	SIPCCMsg_P2P_CheckNatConf();
	~SIPCCMsg_P2P_CheckNatConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		RequestID = 0;
		RequestSeq = 0;
		WanIP = 0;
		WanPort = 0;
	}
	
	int RequestID;
	int RequestSeq;
	unsigned long WanIP;
	unsigned short WanPort;
private:
	virtual int GetMyMemSize();
};

struct SIPCCMsg_P2P_ReInitSockCmd : public SIPCCMsg_P2P
{
	SIPCCMsg_P2P_ReInitSockCmd();
	~SIPCCMsg_P2P_ReInitSockCmd()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		Port = 0;
	}
	unsigned short Port;
private:
	virtual int GetMyMemSize();
};

struct SIPCCMsg_P2P_ReInitSockFailed : public SIPCCMsg_P2P
{
	SIPCCMsg_P2P_ReInitSockFailed();
	~SIPCCMsg_P2P_ReInitSockFailed()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(callID!=NULL)	delete callID;
		callID = NULL;
		callIDLen = 0;
		mediaType = -1;
		seq = 0;
	}
	void SetCallID(string callid);
	string GetCallID()	
	{
		if(callIDLen==0)	return "";
		return string(callID);
	}
	
	int mediaType;
	unsigned char seq;
private:
	char* callID;
	int callIDLen;
	virtual int GetMyMemSize();
};

struct SIPCCMsg_P2P_MediaNegotiate : public SIPCCMsg_P2P
{
	SIPCCMsg_P2P_MediaNegotiate();
	~SIPCCMsg_P2P_MediaNegotiate()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		MediaCapability = 0;
	};
	virtual int GetMyMemSize();
	
	unsigned char MediaCapability;
};

struct SIPCCMsg_P2P_MediaNegotiateConf : public SIPCCMsg_P2P
{
	SIPCCMsg_P2P_MediaNegotiateConf();
	~SIPCCMsg_P2P_MediaNegotiateConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		MediaCapability = 0;
	};
	virtual int GetMyMemSize();
	
	unsigned char MediaCapability;
};
///Class_P2P
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
///Class_EndEgn
struct SIPCCMsg_EndEgn : public SIPCCMessage
{
	SIPCCMsg_EndEgn();
	~SIPCCMsg_EndEgn()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){}
	
private:
	virtual int GetMyMemSize();
};
///Class_EndEgn
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
///Class_HeartBeat

///Type_HeartBeat
struct SIPCCMsg_HeartBeat : public SIPCCMessage
{
	SIPCCMsg_HeartBeat();
	~SIPCCMsg_HeartBeat()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if (theSender != NULL)	delete theSender;
		theSender = NULL;
		theSenderLen = 0;
		clientType = ClientType_Agent;	// [scq/2010-05-18]
		redundancyRate = 1;
	}
	
	void SetTheSender(string thesender)
	{
		int iLen = thesender.length();
		this->theSenderLen = iLen + 1;
		this->theSender = new char[theSenderLen];
		memset(theSender, 0, theSenderLen);
		memcpy(theSender, thesender.c_str(), theSenderLen);
	}
	string GetTheSender()	
	{
		if(theSenderLen==0)	return "";
		if ( !(VerifyData(theSenderLen, SENDER_LEN)) ) {return "";}
		return string(theSender);
	}
	
	// [scq/start/2010-05-18]
	void SetClientType(int clienttype)
	{
		clientType = clienttype;
	}
	int GetClientType()
	{
		return clientType;
	}
	// [scq/end/2010-05-18]

	int GetRedundancyRate()
	{
		return redundancyRate;
	}

	void SetRedundancyRate(int redundancy)
	{
		redundancyRate = redundancy;
	}
	
	unsigned long sipPhoneIP;	
	unsigned short sipPhoneRtpPort;	
	unsigned short sipPhoneRtcpPort;	
private:
	char* theSender;
	int theSenderLen;
	int clientType;	// [scq/2010-05-18] 心跳客户类型是用户还是座席，若是用户则为ClientType_User=0，若是座席则为ClientType_Agent=1
	int redundancyRate; // 语音包冗余深度 0表示没有冗余，1表示有一个冗余包。。。
	
	virtual int GetMyMemSize();
};

///Type_HeartBeatResponse
struct SIPCCMsg_HeartBeatResponse : public SIPCCMessage
{
	SIPCCMsg_HeartBeatResponse();
	~SIPCCMsg_HeartBeatResponse()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}	

	int ServiceCode;
private:
	virtual int GetMyMemSize();
};

///Class_HeartBeat
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
///Class_Transmit
struct SIPCCMsg_Transmit : public SIPCCMessage
{
	SIPCCMsg_Transmit();
	~SIPCCMsg_Transmit()
	{
		ReleaseMemory();
	};
	
	virtual int GetMyMemSize(){return 0;}
	virtual int FillBuf(char*& thebuf){return 0;}
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0){}
	virtual void ReleaseMemory(){}
};

///Type_Trans_TransmitRequest
struct SIPCCMsg_Trans_TransmitRequest : public SIPCCMsg_Transmit
{
	SIPCCMsg_Trans_TransmitRequest();
	~SIPCCMsg_Trans_TransmitRequest()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if (callID != NULL)	delete callID;
		callID = NULL;
		callIDLen = 0;
		if(mediaHeadData != NULL)	delete mediaHeadData;
		mediaHeadData = NULL;
		mediaHeadDataLen = 0;
	}
	
	void SetCallID(string callid)
	{
		int iCallIDLen = callid.length();
		this->callIDLen = iCallIDLen + 1;
		this->callID = new char[callIDLen];
		memset(callID, 0, callIDLen);
		memcpy(callID, callid.c_str(), iCallIDLen);
	}
	string GetCallID()	
	{
		if(callIDLen==0)	return "";
		return string(callID);
	}
	void SetMediaHeadData(char* mediaheaddata, int len);
	int GetMediaHeadData(char* mediaheaddata)
	{
		if(mediaHeadDataLen>0)
			memcpy(mediaheaddata, mediaHeadData, mediaHeadDataLen);
		return mediaHeadDataLen;
	}
	char* mediaHeadData;
	int mediaHeadDataLen;
private:
	char* callID;
	int callIDLen;
	virtual int GetMyMemSize();
public:
	int nSeq;				// 同一个invokeID的计数标记
	char cIsAgentRecord;	// 1录音，其他值不录音； 此字段被动通话方座席置0即可
	unsigned long ulRecServerIP;	// 录音IP网络字节序，由用户端通知到中转Server
	int nRecServerPort;		// 录音端口网络字节序，由用户端通知到中转Server

	string strPresideAgentAccount; // 主动方座席账号
	string strCodec;  // 编码格式
	bool bOldFormat; // 是否oldFormat,给CAudioData::structurize用的
	int m_nPackedSize; // 包大小,给CAudioData::structurize用的

	CAudioStreamDescription audioStreamDescription;
};

///Type_Trans_TransmitRequestConf
struct SIPCCMsg_Trans_TransmitRequestConf : public SIPCCMsg_Transmit
{
	SIPCCMsg_Trans_TransmitRequestConf();
	~SIPCCMsg_Trans_TransmitRequestConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(mediaHeadData != NULL)	delete mediaHeadData;
		mediaHeadData = NULL;
		mediaHeadDataLen = 0;
		textPort = 0;
		audioPort = 0;
	}
	
	void SetMediaHeadData(char* mediaheaddata, int len);
	int GetMediaHeadData(char* mediaheaddata)
	{
		if(mediaHeadDataLen>0)
			memcpy(mediaheaddata, mediaHeadData, mediaHeadDataLen);
		return mediaHeadDataLen;
	};
	char* mediaHeadData;
	int mediaHeadDataLen;
	unsigned short textPort;
	unsigned short audioPort;
	
	virtual int GetMyMemSize();
};

///Type_Trans_TransmitStopRequest
struct SIPCCMsg_Trans_TransmitStopRequest : public SIPCCMsg_Transmit
{
	SIPCCMsg_Trans_TransmitStopRequest();
	~SIPCCMsg_Trans_TransmitStopRequest()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if (callID != NULL)	delete callID;
		callID = NULL;
		callIDLen = 0;
	}
	
	void SetCallID(string callid)
	{
		int iCallIDLen = callid.length();
		this->callIDLen = iCallIDLen + 1;
		this->callID = new char[callIDLen];
		memset(callID, 0, callIDLen);
		memcpy(callID, callid.c_str(), iCallIDLen);
	}
	string GetCallID()	
	{
		if(callIDLen==0)	return "";
		return string(callID);
	}
	
private:
	char* callID;
	int callIDLen;
	
	virtual int GetMyMemSize();
};

///Type_Trans_TransmitRejected
struct SIPCCMsg_Trans_TransmitRejected : public SIPCCMsg_Transmit
{
	SIPCCMsg_Trans_TransmitRejected();
	~SIPCCMsg_Trans_TransmitRejected()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	virtual int GetMyMemSize();
};
///Class_Transmit
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
///Class_UState
struct SIPCCMsg_UState : public SIPCCMessage
{
	SIPCCMsg_UState();
	~SIPCCMsg_UState()
	{
		ReleaseMemory();
	};
	
	virtual int GetMyMemSize(){return 0;}
	virtual int FillBuf(char*& thebuf){return 0;}
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0){}
	virtual void ReleaseMemory(){}
};

///Type_UState_CallArriveToAgent
struct SIPCCMsg_UState_CallArriveToAgent : public SIPCCMsg_UState
{
	SIPCCMsg_UState_CallArriveToAgent();
	~SIPCCMsg_UState_CallArriveToAgent()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if ( agentID != NULL )	delete agentID;
		agentID = NULL;
		agentIDLen = 0;
		if(userName!=NULL)	delete userName;	
		userName = NULL;
		userNameLen = 0;
	}
	void SetAgentID(string agentID);
	string GetAgentID()	
	{
		if(agentIDLen==0)	return "";
		return string(agentID);
	}
	void SetUserName(string username);
	string GetUserName()
	{
		if(userNameLen == 0)			return "";
		return string(userName);
	}
	
	unsigned long lanIp;
	unsigned long wanIp;

	string nickName;

	string gatewayName;

	string computerSymbol;
	
    CAudioStreamDescription audioStreamDescription;
private:
	char* agentID;
	int agentIDLen;
	char* userName;
	int userNameLen;
	virtual int GetMyMemSize();
};

///Type_UState_CallReceived
struct SIPCCMsg_UState_CallReceived : public SIPCCMsg_UState
{
	SIPCCMsg_UState_CallReceived();
	~SIPCCMsg_UState_CallReceived()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(callerParty!=NULL)	delete callerParty;
		callerParty = NULL;
		callerPartyLen = 0;
		if(uuiData!=NULL)	delete uuiData;
		uuiData = NULL;
		uuiDataLen = 0;
		if(callID!=NULL)	delete callID;
		callID = NULL;
		callIDLen = 0;
		if(corporationName != NULL)	delete corporationName;
		corporationName = NULL;
		corporationNameLen = 0;
	}
	void SetCallerParty(string callerparty);
	string GetCallerParty()
	{
		if(callerPartyLen==0)	return "";
		return string(callerParty);
	}
	void SetUUIData(string uuidata);
	string GetUUIData()	
	{
		if(uuiDataLen==0)	return "";
		return string(uuiData);
	}
	void SetCallID(string callid);
	string GetCallID()
	{
		if(callIDLen==0)	return "";
		return string(callID);
	}
	void SetCorporationName(string corporationname);
	string GetCorporationName()
	{
		if(corporationNameLen==0)	return "";
		return string(corporationName);
	}
	
	string callerNoForSend;	
	int callerPartyType;
	
	string wpAgentID;
	string outdialPrefixNo;

	string uuiData2;

	string operatorsInfo;

	string managerId;

	string gatewayName;

	string computerSymbol;

	string netPath;
	
private:
	char* callerParty;
	int callerPartyLen;
	char* uuiData;
	int uuiDataLen;
	char* callID;	//座席过早挂机
	int callIDLen;
	char* corporationName;
	int corporationNameLen;
	virtual int GetMyMemSize();
};

///Type_UState_CallReceived2
struct SIPCCMsg_UState_CallReceived2 : public SIPCCMsg_UState
{
	SIPCCMsg_UState_CallReceived2();
	~SIPCCMsg_UState_CallReceived2()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(callerParty!=NULL)	delete callerParty;
		callerParty = NULL;
		callerPartyLen = 0;
		if(uuiData!=NULL)	delete uuiData;
		uuiData = NULL;
		uuiDataLen = 0;
		if(callID!=NULL)	delete callID;
		callID = NULL;
		callIDLen = 0;
		if(corporationName != NULL)	delete corporationName;
		corporationName = NULL;
		corporationNameLen = 0;
	}
	void SetCallerParty(string callerparty);
	string GetCallerParty()
	{
		if(callerPartyLen==0)	return "";
		return string(callerParty);
	}
	void SetUUIData(string uuidata);
	string GetUUIData()	
	{
		if(uuiDataLen==0)	return "";
		return string(uuiData);
	}
	void SetCallID(string callid);
	string GetCallID()
	{
		if(callIDLen==0)	return "";
		return string(callID);
	}
	void SetCorporationName(string corporationname);
	string GetCorporationName()
	{
		if(corporationNameLen==0)	return "";
		return string(corporationName);
	}
	
	string callerNoForSend;	
	int callerPartyType;
	
	string invokeID;
	int usableTime;
	string userName;
	
	unsigned long lanIp;
	unsigned long wanIp;
	
	int outDialType;
	
	int calledOperType;
	
	string wpAgentID;
	
	string callTransID;
	
	string managerId;
	string corpName;
	string extPhoneNo;   // 分机号码
	string recordFilePath;   // 录音文件目录名

	string LowLevelPrefixNo;	//出局使用前缀

	string nickName;

	int RecordMode;

	bool		the2nd_dial_valid;
	string		the2nd_dial_digit;
	bool		the3rd_media_valid;//客户端与sip模拟网关直连
	string		the3rd_media_address;//坐席与sip模拟网关直连地址
	unsigned short the3rd_media_port;//坐席使用的RTP语音端口

	string gatewayName;

	string computerSymbol;

    CAudioStreamDescription audioStreamDescription;

	string token;		//"token":"xxx"
private:
	char* callerParty;
	int callerPartyLen;
	char* uuiData;
	int uuiDataLen;
	char* callID;	//座席过早挂机
	int callIDLen;
	char* corporationName;
	int corporationNameLen;
	virtual int GetMyMemSize();
};

///Type_UState_UserQueryStateConf
struct SIPCCMsg_UState_UserQueryStateConf : public SIPCCMsg_UState
{
	SIPCCMsg_UState_UserQueryStateConf();
	~SIPCCMsg_UState_UserQueryStateConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		userState = -1;
		bQuerySucess = 0;
		
		if(additionalInfo!=NULL)	delete additionalInfo;
		additionalInfo = NULL;
		additionalInfoLen = 0;
	}
	void SetAdditionalInfo(string additionalinfo);
	string GetAdditionalInfo()	
	{
		if(additionalInfoLen==0)	return "";
		return string(additionalInfo);
	}
	int userState;
	char bQuerySucess;
private:
	char* additionalInfo;
	int additionalInfoLen;
	virtual int GetMyMemSize();
};

///Type_UState_UserLoginConf
struct SIPCCMsg_UState_UserLoginConf : public SIPCCMsg_UState
{
	SIPCCMsg_UState_UserLoginConf();
	~SIPCCMsg_UState_UserLoginConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
private:
	virtual int GetMyMemSize();
};

///Type_UState_UserLogoutConf
struct SIPCCMsg_UState_UserLogoutConf : public SIPCCMsg_UState
{
	SIPCCMsg_UState_UserLogoutConf();
	~SIPCCMsg_UState_UserLogoutConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
private:
	virtual int GetMyMemSize();
};

///Type_UState_AgentMakeCallConf
struct SIPCCMsg_UState_AgentMakeCallConf : public SIPCCMsg_UState
{
	SIPCCMsg_UState_AgentMakeCallConf();
	~SIPCCMsg_UState_AgentMakeCallConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		callingState = -1;
	}
	
	int callingState;
private:
	virtual int GetMyMemSize();
};

///Type_UState_UserMakeCallConf
struct SIPCCMsg_UState_UserMakeCallConf : public SIPCCMsg_UState
{
	SIPCCMsg_UState_UserMakeCallConf();
	~SIPCCMsg_UState_UserMakeCallConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		callingState = -1;
	}
	
	int callingState;
private:
	virtual int GetMyMemSize();
};

///Type_UState_CallHanguped
struct SIPCCMsg_UState_CallHanguped : public SIPCCMsg_UState
{
	SIPCCMsg_UState_CallHanguped();
	~SIPCCMsg_UState_CallHanguped()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(userName!=NULL)	delete userName;	
		userName = NULL;
		userNameLen = 0;
		if(callID!=NULL)	delete callID;
		callID = NULL;
		callIDLen = 0;
		if(releasedParty!=NULL)	delete releasedParty;
		releasedParty = NULL;
		releasedPartyLen = 0;
	}
	void SetUserName(string username);
	string GetUserName()
	{
		if(userNameLen == 0)			return "";
		return string(userName);
	}
	void SetCallID(string callid);
	string GetCallID()
	{
		if(callIDLen==0)	return "";
		return string(callID);
	}
	void SetReleasedParty(string releasedparty);
	string GetReleasedParty()	
	{
		if(releasedPartyLen==0)	return "";
		return string(releasedParty);
	}

	string  handleId;


	string gatewayName;

	string computerSymbol;

private:
	char* callID;	//座席呼座席、座席呼 skillGroup 用,带给被叫/被分配座席,记报表
	int callIDLen;
	char* userName;
	int userNameLen;
	char* releasedParty;
	int releasedPartyLen;
	virtual int GetMyMemSize();
};

///Type_UState_MediaRequest
struct SIPCCMsg_UState_MediaRequest : public SIPCCMsg_UState
{
	SIPCCMsg_UState_MediaRequest();
	~SIPCCMsg_UState_MediaRequest()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(callID!=NULL)	delete callID;
		callID = NULL;
		callIDLen = 0;
		mediaType = -1;
	}
	void SetCallID(string callid);
	string GetCallID()	
	{
		if(callIDLen==0)	return "";
		return string(callID);
	}
	
	int mediaType;
	int seq;
private:
	char* callID;
	int callIDLen;
	virtual int GetMyMemSize();
};

///Type_UState_CallAnswered
struct SIPCCMsg_UState_CallAnswered : public SIPCCMsg_UState
{
	SIPCCMsg_UState_CallAnswered();
	~SIPCCMsg_UState_CallAnswered()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(userName!=NULL)	delete userName;	
		userName = NULL;
		userNameLen = 0;
	}
	void SetUserName(string username);
	string GetUserName()
	{
		if(userNameLen == 0)			return "";
		return string(userName);
	}
	
	int remoteNatType;
	string callId;
	
	string managerId;
	string corpName;
	string agentId;      // 座席名
	string extPhoneNo;   // 分机号码
	string recordFilePath;   // 录音文件目录名

	int RecordMode;

	bool	the3rd_media_valid;
	string	the3rd_media_address;
	unsigned short the3rd_media_port;

	string gatewayName;

	string computerSymbol;

	string token;	//"token":"xxx"
private:
	char* userName;
	int userNameLen;
	virtual int GetMyMemSize();
};

///Type_UState_CallReleased
struct SIPCCMsg_UState_CallReleased : public SIPCCMsg_UState
{
	SIPCCMsg_UState_CallReleased();
	~SIPCCMsg_UState_CallReleased()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(theOtherParty!=NULL)	delete theOtherParty;
		theOtherParty = NULL;
		theOtherPartyLen = 0;
	}
	void SetTheOtherParty(string theotherparty);
	string GetTheOtherParty()	
	{
		if(theOtherPartyLen==0)	return "";
		return string(theOtherParty);
	}
private:
	char* theOtherParty;
	int theOtherPartyLen;
	virtual int GetMyMemSize();
};

///Type_UState_CallEstablished
struct SIPCCMsg_UState_CallEstablished : public SIPCCMsg_UState
{
	SIPCCMsg_UState_CallEstablished();
	~SIPCCMsg_UState_CallEstablished()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(theOtherParty!=NULL)	delete theOtherParty;
		theOtherParty = NULL;
		theOtherPartyLen = 0;
	}
	void SetTheOtherParty(string theotherparty);
	string GetTheOtherParty()	
	{
		if(theOtherPartyLen==0)	return "";
		return string(theOtherParty);
	}
private:
	char* theOtherParty;
	int theOtherPartyLen;
	virtual int GetMyMemSize();
};

///Type_UState_UserNoResponse
struct SIPCCMsg_UState_UserNoResponse : public SIPCCMsg_UState
{
	SIPCCMsg_UState_UserNoResponse();
	~SIPCCMsg_UState_UserNoResponse()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(userName!=NULL)	delete userName;	
		userName = NULL;
		userNameLen = 0;
	}
	void SetUserName(string username);
	string GetUserName()
	{
		if(userNameLen == 0)			return "";
		if ( !(VerifyData(userNameLen, USERNAME_LEN)) ) {return "";}
		return string(userName);
	}
	
private:
	char* userName;
	int userNameLen;
	virtual int GetMyMemSize();
};

///Type_UState_AgentHoldCall
struct SIPCCMsg_UState_AgentHoldCall : public SIPCCMsg_UState
{
	SIPCCMsg_UState_AgentHoldCall();
	~SIPCCMsg_UState_AgentHoldCall()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(heldParty!=NULL)	delete heldParty;	
		heldParty = NULL;
		heldPartyLen = 0;
	}
	void SetHeldParty(string heldparty);
	string GetHeldParty()
	{
		if(heldPartyLen == 0)			return "";
		return string(heldParty);
	}
	
	string ManagerID;
	string gatewayName;

	string computerSymbol;
	
private:
	char* heldParty;
	int heldPartyLen;
	
	virtual int GetMyMemSize();
};

///Type_UState_AgentUnHoldCall
struct SIPCCMsg_UState_AgentUnHoldCall : public SIPCCMsg_UState
{
	SIPCCMsg_UState_AgentUnHoldCall();
	~SIPCCMsg_UState_AgentUnHoldCall()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(heldParty!=NULL)	delete heldParty;	
		heldParty = NULL;
		heldPartyLen = 0;
	}
	void SetHeldParty(string heldparty);
	string GetHeldParty()
	{
		if(heldPartyLen == 0)			return "";
		return string(heldParty);
	}
public:
	string gatewayName;
	string computerSymbol;
private:
	char* heldParty;
	int heldPartyLen;
	
	virtual int GetMyMemSize();
};

///Type_UState_AgentHoldCallConf
struct SIPCCMsg_UState_AgentHoldCallConf : public SIPCCMsg_UState
{
	SIPCCMsg_UState_AgentHoldCallConf();
	~SIPCCMsg_UState_AgentHoldCallConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		bHoldSucc = 0;
	}
	
	char bHoldSucc;
	
private:
	virtual int GetMyMemSize();
};

///Type_Ustate_PrepareTransfer
struct SIPCCMsg_UState_PrepareTransfer : public SIPCCMsg_UState
{
	SIPCCMsg_UState_PrepareTransfer();
	~SIPCCMsg_UState_PrepareTransfer()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(callID!=NULL)	delete callID;	
		callID = NULL;
		callIDLen = 0;
		if(otherParty!=NULL)	delete otherParty;	
		otherParty = NULL;
		otherPartyLen = 0;
	}
	void SetCallID(string callid);
	string GetCallID()
	{
		if(callIDLen == 0)			return "";
		return string(callID);
	}
	
	void SetOtherParty(string otherParty);
	string GetOtherParty()
	{
		if(otherPartyLen == 0)			return "";
		return string(otherParty);
	}
public:
	int otherPartyType;
	unsigned long AudioIp;
	unsigned short AudioPort;
	unsigned long lanIP;

	string gatewayName;

	string computerSymbol;


private:
	char* callID;
	int callIDLen;
	char* otherParty;
	int otherPartyLen;
	virtual int GetMyMemSize();
};

///Type_UState_TransReady
struct SIPCCMsg_UState_TransReady : public SIPCCMsg_UState
{
	SIPCCMsg_UState_TransReady();
	~SIPCCMsg_UState_TransReady()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(readyParty!=NULL)	delete readyParty;	
		readyParty = NULL;
		readyPartyLen = 0;
	}
	
	void SetReadyParty(string readyparty);
	string GetReadyParty()
	{
		if(readyPartyLen == 0)			return "";
		return string(readyParty);
	}
	
private:
	char* readyParty;
	int readyPartyLen;
	
	virtual int GetMyMemSize();
};

///Type_UState_TransferCall
struct SIPCCMsg_UState_TransferCall : public SIPCCMsg_UState
{
	SIPCCMsg_UState_TransferCall();
	~SIPCCMsg_UState_TransferCall()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(presideAgent!=NULL)	delete presideAgent;	
		presideAgent = NULL;
		presideAgentLen = 0;
		if(otherParty!=NULL)	delete otherParty;	
		otherParty = NULL;
		otherPartyLen = 0;
		if(theParty!=NULL)	delete theParty;	
		theParty = NULL;
		thePartyLen = 0;
	}
	
	void SetPresideAgent(string presideagent);
	string GetPresideAgent()
	{
		if(presideAgentLen == 0)			return "";
		return string(presideAgent);
	}
	void SetOtherParty(string otherparty);
	string GetOtherParty()
	{
		if(otherPartyLen == 0)			return "";
		return string(otherParty);
	}
	void SetTheParty(string theparty);
	string GetTheParty()
	{
		if(thePartyLen == 0)			return "";
		return string(theParty);
	}
public:
	int otherPartyType;
	int thePartyType;
	string agentUUIData;
	char needReturn;
	char IsWebPSTNAgent;

	string gatewayName;
	string computerSymbol;
private:
	char* presideAgent;
	int presideAgentLen;
	char* otherParty;
	int otherPartyLen;
	char* theParty;
	int thePartyLen;	
	
	virtual int GetMyMemSize();
};

///Type_UState_BeforeTransfer
struct SIPCCMsg_UState_BeforeTransfer : public SIPCCMsg_UState
{
	SIPCCMsg_UState_BeforeTransfer();
	~SIPCCMsg_UState_BeforeTransfer()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(presideAgent!=NULL)	delete presideAgent;	
		presideAgent = NULL;
		presideAgentLen = 0;
		if(otherParty!=NULL)	delete otherParty;	
		otherParty = NULL;
		otherPartyLen = 0;
		if(theParty!=NULL)	delete theParty;	
		theParty = NULL;
		thePartyLen = 0;
	}
	
	void SetPresideAgent(string presideagent);
	string GetPresideAgent()
	{
		if(presideAgentLen == 0)			return "";
		return string(presideAgent);
	}
	void SetOtherParty(string otherparty);
	string GetOtherParty()
	{
		if(otherPartyLen == 0)			return "";
		return string(otherParty);
	}
	void SetTheParty(string theparty);
	string GetTheParty()
	{
		if(thePartyLen == 0)			return "";
		return string(theParty);
	}
public:
	int otherPartyType;
	string gatewayName;

	string computerSymbol;

private:
	char* presideAgent;
	int presideAgentLen;
	char* otherParty;
	int otherPartyLen;
	char* theParty;
	int thePartyLen;	
	
	virtual int GetMyMemSize();
};

///Type_UState_ClearPreConnection
struct SIPCCMsg_UState_ClearPreConnection : public SIPCCMsg_UState
{
	SIPCCMsg_UState_ClearPreConnection();
	~SIPCCMsg_UState_ClearPreConnection()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(notifier!=NULL)	delete notifier;	
		notifier = NULL;
		notifierLen = 0;
	}
	
	void SetNotifier(string theNotifier);
	string GetNotifier()
	{
		if(notifierLen == 0)			return "";
		return string(notifier);
	}
	
private:
	char* notifier;
	int notifierLen;
	virtual int GetMyMemSize();
};

///Type_UState_MediaReady
struct SIPCCMsg_UState_MediaReady : public SIPCCMsg_UState
{
	SIPCCMsg_UState_MediaReady();
	~SIPCCMsg_UState_MediaReady()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
private:
	virtual int GetMyMemSize();
};

///Type_UState_CallUserConf
struct SIPCCMsg_UState_CallUserConf : public SIPCCMsg_UState
{
	SIPCCMsg_UState_CallUserConf();
	~SIPCCMsg_UState_CallUserConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		userName = "";
		bCallFailed = 1;
		audioIP = 0;
		audioPort = 0;
		
		invokeID = "";
	}
	
	string userName;
	string invokeID;
	int failedCause;
	char bCallFailed;
	unsigned long audioIP;
	unsigned short audioPort;
	unsigned long lanIP;
private:
	
	virtual int GetMyMemSize();
};

///Type_UState_CallUserFailed
struct SIPCCMsg_UState_CallUserFailed : public SIPCCMsg_UState
{
	SIPCCMsg_UState_CallUserFailed();
	~SIPCCMsg_UState_CallUserFailed()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		userName = "";
	}
	
	string userName;
	int failedCause;
	
private:
	
	virtual int GetMyMemSize();
};

///UState_PreConference
struct SIPCCMsg_UState_PreConference : public SIPCCMsg_UState
{
	SIPCCMsg_UState_PreConference();
	~SIPCCMsg_UState_PreConference()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	};
	
	string presideParty;
	int presidePartyType;
	unsigned long presidePartyIP;
	unsigned short presidePartyPort;
	string otherJoinParty;
	int otherJoinPartyType;
	unsigned long otherJoinPartyIP;
	unsigned short otherJoinPartyPort;
	
private:
	virtual int GetMyMemSize();
};

///UState_Conference
struct SIPCCMsg_UState_Conference : public SIPCCMsg_UState
{
	SIPCCMsg_UState_Conference();
	~SIPCCMsg_UState_Conference()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	};
	
	string presideParty;
	int presidePartyType;
	string otherJoinParty;
	int otherJoinPartyType;
	
private:
	virtual int GetMyMemSize();
};

///Type_UState_GWLogoutConf
struct SIPCCMsg_UState_GWLogoutConf : public SIPCCMsg_UState			
{
	SIPCCMsg_UState_GWLogoutConf();
	~SIPCCMsg_UState_GWLogoutConf()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

	string GwName;
	string ComputerSymbol;

private:
	virtual int GetMyMemSize();
};

///Type_UState_USRegister
struct SIPCCMsg_UState_USRegister : public SIPCCMsg_UState
{
	SIPCCMsg_UState_USRegister();
	~SIPCCMsg_UState_USRegister()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}

	string ServerName;
	unsigned long ServerIp;
	unsigned short ServerPort;
private:
	virtual int GetMyMemSize();
};

///Type_UState_ConfirmConf
struct SIPCCMsg_UState_ConfirmConf : public SIPCCMsg_UState
{
	SIPCCMsg_UState_ConfirmConf();
	~SIPCCMsg_UState_ConfirmConf()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}

	string invokeID;
private:
	virtual int GetMyMemSize();
};

///Class_UState
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
///Class_File
struct SIPCCMsg_File : public SIPCCMessage
{
	SIPCCMsg_File();
	~SIPCCMsg_File()
	{
		ReleaseMemory();
	};
	
	virtual int GetMyMemSize(){return 0;}
	virtual int FillBuf(char*& thebuf){return 0;}
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0){}
	virtual void ReleaseMemory(){}
};

///Type_File_TransRequest
struct SIPCCMsg_File_TransRequest : public SIPCCMsg_File
{
	SIPCCMsg_File_TransRequest();
	~SIPCCMsg_File_TransRequest()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		//		if(FileName!=NULL)	delete FileName;	
		//		FileName = NULL;
		//		FileNameLen = 0;
	};
	
	//	void SetFileName(string filename)
	//	{
	//		int iFileNameLen = filename.length();
	//		this->FileNameLen = iFileNameLen + 1;
	//		this->FileName = new char[FileNameLen];
	//		memset(FileName, 0, FileNameLen);
	//		memcpy(FileName, filename.c_str(), FileNameLen);
	//	};
	//
	//	string GetFileName()
	//	{
	//		if(FileNameLen == 0)	return "";
	//		return string(FileName);
	//	};
public:
	int Seq;
private:
	//	char* FileName;
	//	int FileNameLen;
	virtual int GetMyMemSize();
};

///Type_File_TransRequestConf
struct SIPCCMsg_File_TransRequestConf : public SIPCCMsg_File
{
	SIPCCMsg_File_TransRequestConf();
	~SIPCCMsg_File_TransRequestConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		Result = 0;
	};
	
	unsigned char Result;	//0:拒绝；1:同意
	
private:
	virtual int GetMyMemSize();
};

///Type_File_TransReady
struct SIPCCMsg_File_TransReady : public SIPCCMsg_File
{
	SIPCCMsg_File_TransReady();
	~SIPCCMsg_File_TransReady()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	};
	
private:
	virtual int GetMyMemSize();
};

///Type_File_UnConnect
struct SIPCCMsg_File_UnConnect : public SIPCCMsg_File
{
	SIPCCMsg_File_UnConnect();
	~SIPCCMsg_File_UnConnect()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	};
	virtual int GetMyMemSize();
};

///Type_File_FileRequest
struct SIPCCMsg_File_FileRequest : public SIPCCMsg_File
{
	SIPCCMsg_File_FileRequest();
	~SIPCCMsg_File_FileRequest()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(FileName!=NULL)	delete FileName;	
		FileName = NULL;
		FileNameLen = 0;
	};
	
	void SetFileName(string filename)
	{
		int iFileNameLen = filename.length();
		this->FileNameLen = iFileNameLen + 1;
		this->FileName = new char[FileNameLen];
		memset(FileName, 0, FileNameLen);
		memcpy(FileName, filename.c_str(), iFileNameLen);
	};
	
	string GetFileName()
	{
		if(FileNameLen == 0)	return "";
		return string(FileName);
	};
	
	unsigned long FileSizeHigh;
	unsigned long FileSizeLow;
private:
	char* FileName;
	int FileNameLen;
	virtual int GetMyMemSize();
};

///Type_File_FileRequestConf
struct SIPCCMsg_File_FileRequestConf : public SIPCCMsg_File
{
	SIPCCMsg_File_FileRequestConf();
	~SIPCCMsg_File_FileRequestConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		Result = 0;
	};
	
	unsigned char Result;	//0:拒绝；1:同意
	
private:
	virtual int GetMyMemSize();
};

///Type_File_FileReceived
struct SIPCCMsg_File_FileReceived : public SIPCCMsg_File
{
	SIPCCMsg_File_FileReceived();
	~SIPCCMsg_File_FileReceived()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	};
	
private:
	virtual int GetMyMemSize();
};

///Type_File_FileStopped
struct SIPCCMsg_File_FileStopped : public SIPCCMsg_File
{
	SIPCCMsg_File_FileStopped();
	~SIPCCMsg_File_FileStopped()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	};
	
private:
	virtual int GetMyMemSize();
};

///Type_File_FileReceiveInfo
struct SIPCCMsg_File_FileReceiveInfo : public SIPCCMsg_File
{
	SIPCCMsg_File_FileReceiveInfo();
	~SIPCCMsg_File_FileReceiveInfo()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	};
	
	unsigned long PackCount;
	unsigned long ReceivedSize;
private:
	virtual int GetMyMemSize();
};
///Class_File
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
///Class_Record
struct SIPCCMsg_Record : public SIPCCMessage
{
	SIPCCMsg_Record();
	~SIPCCMsg_Record()
	{
		ReleaseMemory();
	};
	
	virtual int GetMyMemSize(){return 0;}
	virtual int FillBuf(char*& thebuf){return 0;}
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0){}
	virtual void ReleaseMemory(){}
};

///Type_Record_Login
struct SIPCCMsg_Record_Login : public SIPCCMsg_Record
{
	SIPCCMsg_Record_Login();
	~SIPCCMsg_Record_Login()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(agentID!=NULL)	delete agentID;
		agentID = NULL;
		agentIDLen = 0;
	}
	void SetAgentID(string agentid);
	string GetAgentID()
	{
		if(agentIDLen==0)	return "";
		return string(agentID);
	}
private:
	char* agentID;
	int agentIDLen;
	virtual int GetMyMemSize();
};

///Type_Record_LoginConf
struct SIPCCMsg_Record_LoginConf : public SIPCCMsg_Record
{
	SIPCCMsg_Record_LoginConf();
	~SIPCCMsg_Record_LoginConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		recIP = 0;
		recPort = 0;
	}
	
	unsigned long recIP;
	unsigned short recPort;
private:
	virtual int GetMyMemSize();
};

///Type_Record_StartRecord
struct SIPCCMsg_Record_StartRecord : public SIPCCMsg_Record
{
	SIPCCMsg_Record_StartRecord();
	~SIPCCMsg_Record_StartRecord()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(agentID!=NULL)	delete agentID;
		agentID = NULL;
		agentIDLen = 0;
		if(CTID!=NULL)	delete CTID;
		CTID = NULL;
		CTIDLen = 0;
		if(callerID!=NULL)	delete callerID;
		callerID = NULL;
		callerIDLen = 0;
		if(calleeID!=NULL)	delete calleeID;
		calleeID = NULL;
		calleeIDLen = 0;
		if(theComment!=NULL)	delete theComment;
		theComment = NULL;
		theCommentLen = 0;
	}
	void SetAgentID(string agentid);
	string GetAgentID()
	{
		if(agentIDLen==0)	return "";
		return string(agentID);
	}
	void SetCTID(string ctid);
	string GetCTID()
	{
		if(CTIDLen==0)	return "";
		return string(CTID);
	}
	void SetCallerID(string callerid);
	string GetCallerID()
	{
		if(callerIDLen==0)	return "";
		return string(callerID);
	}
	void SetCalleeID(string calleeid);
	string GetCalleeID()
	{
		if(calleeIDLen==0)	return "";
		return string(calleeID);
	}
	void SetTheComment(string thecomment);
	string GetTheComment()
	{
		if(theCommentLen==0)	return "";
		return string(theComment);
	}
	
private:
	char* agentID;
	int agentIDLen;
	char* CTID;
	int CTIDLen;
	char* callerID;
	int callerIDLen;
	char* calleeID;
	int calleeIDLen;
	char* theComment;
	int theCommentLen;
	
	virtual int GetMyMemSize();
};

///Type_Record_StopRecord
struct SIPCCMsg_Record_StopRecord : public SIPCCMsg_Record
{
	SIPCCMsg_Record_StopRecord();
	~SIPCCMsg_Record_StopRecord()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(agentID!=NULL)	delete agentID;
		agentID = NULL;
		agentIDLen = 0;
	}
	void SetAgentID(string agentid);
	string GetAgentID()
	{
		if(agentIDLen==0)	return "";
		return string(agentID);
	}
private:
	char* agentID;
	int agentIDLen;
	virtual int GetMyMemSize();
};

///Type_Record_StartRecordConf
struct SIPCCMsg_Record_StartRecordConf : public SIPCCMsg_Record
{
	SIPCCMsg_Record_StartRecordConf();
	~SIPCCMsg_Record_StartRecordConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
private:
	virtual int GetMyMemSize();
};

///Type_Record_StartTrunkP2ARecord
struct SIPCCMsg_Record_StartTrunkP2ARecord : public SIPCCMsg_Record
{
	SIPCCMsg_Record_StartTrunkP2ARecord();
	~SIPCCMsg_Record_StartTrunkP2ARecord()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{};
	
	string agentID;
	string CTID;
	string callerID;
	string calleeID;
	string theComment;
	
	string trunkDn;
	
	string managerId;
	string corpName;
	string extPhoneNo;   // 分机号码
	string recordFilePath;   // 录音文件目录名(苏州润迅的项目名)

	int callDirection;
	string nickName;
	string beginTime;

	string strSequence; // 用于重发的上层序号，形如"trunkDn_发送时间的秒数"

	string managerId2;
private:
	virtual int GetMyMemSize();
};

///Type_Record_StopRecord
struct SIPCCMsg_Record_StopTrunkP2ARecord : public SIPCCMsg_Record
{
	SIPCCMsg_Record_StopTrunkP2ARecord();
	~SIPCCMsg_Record_StopTrunkP2ARecord()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	string trunkDn;

	string beginTime;

	string strSequence; // 用于重发的上层序号，形如"trunkDn_发送时间的秒数"
private:
	virtual int GetMyMemSize();
};

///Type_Record_ACK   收到录音相关信令的回应
struct SIPCCMsg_Record_ACK : public SIPCCMsg_Record
{
	SIPCCMsg_Record_ACK(){
		msgType =Type_Record_ACK;
	};
	~SIPCCMsg_Record_ACK()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf)
	{
		thebuf = new char[GetMyMemSize()];
		int theBufContent = FillMsgHead(thebuf);

		//strSequence
		memcpy(thebuf+theBufContent, strSequence.c_str(), strSequence.length()+1);
		theBufContent += strSequence.length()+1;

		return theBufContent;
	}
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0)
	{
		string strMsg = "SIPCCMsg_Record_ACK";
		if ( !(VerifyTotalLen(HEAD_LEN, msgsize, strMsg, "MsgHead", ip, port)) ) {return;}
		int theBufContent = AnalyzeMsgHead(thebuf);

		strSequence = thebuf + theBufContent;
		if ( !(VerifyTotalLen(theBufContent+strSequence.length()+1, msgsize, strMsg, "strSequence.length()", ip, port)) ) {return;}
		if ( !(VerifyData(strSequence.length(), SEQUENCE_LEN, strMsg, "strSequence", ip, port)) ) {return;}
		theBufContent += strSequence.length()+1;
	}
	virtual void ReleaseMemory()
	{
	}

	string strSequence; 
private:
	virtual int GetMyMemSize()
	{
		int memSize = 2*sizeof(int);		//msgclass+msgtype
		memSize += strSequence.length()+1;	//strSequence
		return memSize;
	}
};
///Type_Record_StartTrunkP2PRecord
struct SIPCCMsg_Record_StartTrunkP2PRecord : public SIPCCMsg_Record
{
	SIPCCMsg_Record_StartTrunkP2PRecord();
	~SIPCCMsg_Record_StartTrunkP2PRecord()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{};
	
	string agentID;
	string CTID;
	string callerID;
	string calleeID;
	string theComment;
	
	string trunkDn;
private:
	virtual int GetMyMemSize();
};

///Type_Record_StopRecord
struct SIPCCMsg_Record_StopTrunkP2PRecord : public SIPCCMsg_Record
{
	SIPCCMsg_Record_StopTrunkP2PRecord();
	~SIPCCMsg_Record_StopTrunkP2PRecord()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	string trunkDn;
private:
	virtual int GetMyMemSize();
};

///Type_Record_LoadManageInfo
struct SIPCCMsg_Record_LoadManageInfo : public SIPCCMsg_Record
{
	SIPCCMsg_Record_LoadManageInfo();
	~SIPCCMsg_Record_LoadManageInfo()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
private:
	virtual int GetMyMemSize();
};

///Type_Record_LoadManageInfoConf
struct SIPCCMsg_Record_LoadManageInfoConf : public SIPCCMsg_Record
{
	SIPCCMsg_Record_LoadManageInfoConf();
	~SIPCCMsg_Record_LoadManageInfoConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	string info;
private:
	virtual int GetMyMemSize();
};

///Type_Record_AddRecCorp
struct SIPCCMsg_Record_AddRecCorp : public SIPCCMsg_Record
{
	SIPCCMsg_Record_AddRecCorp();
	~SIPCCMsg_Record_AddRecCorp()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	string managerId;
	string corpName;
	string realCalledNo;
private:
	virtual int GetMyMemSize();
};

///Type_Record_DelRecCorp
struct SIPCCMsg_Record_DelRecCorp : public SIPCCMsg_Record
{
	SIPCCMsg_Record_DelRecCorp();
	~SIPCCMsg_Record_DelRecCorp()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	string managerId;
private:
	virtual int GetMyMemSize();
};

///Type_Record_RecInfo2ACD
struct SIPCCMsg_Record_RecInfo2ACD : public SIPCCMsg_Record
{
	SIPCCMsg_Record_RecInfo2ACD();
	~SIPCCMsg_Record_RecInfo2ACD()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	string agentID;
	string invokeID;
	string fullPathFileName;

	string  managerId;
	string  connectPhoneNo;
private:
	virtual int GetMyMemSize();
};

///Class_Record
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
///Class_SmartRoute
struct SIPCCMsg_SmartRoute : public SIPCCMessage
{
	SIPCCMsg_SmartRoute();
	~SIPCCMsg_SmartRoute()
	{
		ReleaseMemory();
	};
	
	virtual int GetMyMemSize(){return 0;}
	virtual int FillBuf(char*& thebuf){return 0;}
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0){}
	virtual void ReleaseMemory(){}
};

///Type_SmartRoute_QueryUserStatus
struct SIPCCMsg_SmartRoute_QueryUserStatus : public SIPCCMsg_SmartRoute
{
	SIPCCMsg_SmartRoute_QueryUserStatus();
	~SIPCCMsg_SmartRoute_QueryUserStatus()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(userName!=NULL)	delete userName;
		userName = NULL;
		userNameLen = 0;
		if(theCorporation!=NULL) delete theCorporation;
		theCorporation = NULL;
		theCorporationLen = 0;
		if(routeDest!=NULL) delete routeDest;
		routeDest = NULL;
		routeDestLen = 0;
		userIP = 0;
		userPort = 0;
	}
	
	void SetUserName(string username);
	string GetUserName()
	{
		if(userNameLen==0)	return "";
		if ( !(VerifyData(userNameLen, USERNAME_LEN)) ) {return "";}
		return string(userName);
	}
	
	void SetTheCorporation(string thecorporation);
	string GetTheCorporation()
	{
		if(theCorporationLen==0)	return "";
		if ( !(VerifyData(theCorporationLen, CORPNAME_LEN)) ) {return "";}
		return string(theCorporation);
	}
	
	void SetRouteDest(string rotuedest);
	string GetRouteDest()
	{
		if(routeDestLen==0)	return "";
		if ( !(VerifyData(routeDestLen, ROUTEDEST_LEN)) ) {return "";}
		return string(routeDest);
	}
	
	unsigned long userIP;
	unsigned short userPort;
private:
	char* userName;
	int userNameLen;
	char* theCorporation;
	int theCorporationLen;
	char* routeDest;
	int routeDestLen;
	virtual int GetMyMemSize();
};

///Type_SmartRoute_QueryUserStatusConf
struct SIPCCMsg_SmartRoute_QueryUserStatusConf : public SIPCCMsg_SmartRoute
{
	SIPCCMsg_SmartRoute_QueryUserStatusConf();
	~SIPCCMsg_SmartRoute_QueryUserStatusConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(theCorporation!=NULL) delete theCorporation;
		theCorporation = NULL;
		theCorporationLen = 0;
		if(routeDest!=NULL) delete routeDest;
		routeDest = NULL;
		routeDestLen = 0;
		userIP = 0;
		userPort = 0;
	}
	
	void SetTheCorporation(string thecorporation);
	string GetTheCorporation()
	{
		if(theCorporationLen==0)	return "";
		return string(theCorporation);
	}
	
	void SetRouteDest(string rotuedest);
	string GetRouteDest()
	{
		if(routeDestLen==0)	return "";
		return string(routeDest);
	}
	
	int userStatus;
	unsigned long userIP;
	unsigned short userPort;
private:
	char* theCorporation;
	int theCorporationLen;
	char* routeDest;
	int routeDestLen;
	
	virtual int GetMyMemSize();
};

///Type_SmartRoute_LoadSmartRouteTactic
struct SIPCCMsg_SmartRoute_LoadSmartRouteTactic : public SIPCCMsg_SmartRoute
{
	SIPCCMsg_SmartRoute_LoadSmartRouteTactic();
	~SIPCCMsg_SmartRoute_LoadSmartRouteTactic()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
private:
	virtual int GetMyMemSize();
};

///Type_SmartRoute_BlackListTactic
struct SIPCCMsg_SmartRoute_BlackListTactic : public SIPCCMsg_SmartRoute
{
	SIPCCMsg_SmartRoute_BlackListTactic();
	~SIPCCMsg_SmartRoute_BlackListTactic()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(routeDest!=NULL)	delete routeDest;
		routeDest = NULL;
		routeDestLen = 0;
		if(theCorporation!=NULL) delete theCorporation;
		theCorporation = NULL;
		theCorporationLen = 0;
		theTactic = -1;
	}
	
	void SetRouteDest(string routedest);
	string GetRouteDest()
	{
		if(routeDestLen==0)	return "";
		return string(routeDest);
	}
	
	void SetTheCorporation(string thecorporation);
	string GetTheCorporation()
	{
		if(theCorporationLen==0)	return "";
		return string(theCorporation);
	}
	
	int theTactic;
private:
	char* theCorporation;
	int theCorporationLen;
	char* routeDest;
	int routeDestLen;
	virtual int GetMyMemSize();
};

///Type_SmartRoute_NewUserTactic
struct SIPCCMsg_SmartRoute_NewUserTactic : public SIPCCMsg_SmartRoute
{
	SIPCCMsg_SmartRoute_NewUserTactic();
	~SIPCCMsg_SmartRoute_NewUserTactic()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(routeDest!=NULL)	delete routeDest;
		routeDest = NULL;
		routeDestLen = 0;
		if(theCorporation!=NULL) delete theCorporation;
		theCorporation = NULL;
		theCorporationLen = 0;
		theTactic = -1;
	}
	
	void SetRouteDest(string routedest);
	string GetRouteDest()
	{
		if(routeDestLen==0)	return "";
		return string(routeDest);
	}
	
	void SetTheCorporation(string thecorporation);
	string GetTheCorporation()
	{
		if(theCorporationLen==0)	return "";
		return string(theCorporation);
	}
	
	int theTactic;
private:
	char* theCorporation;
	int theCorporationLen;
	char* routeDest;
	int routeDestLen;
	virtual int GetMyMemSize();
};

///Type_SmartRoute_OldUserTactic
struct SIPCCMsg_SmartRoute_OldUserTactic : public SIPCCMsg_SmartRoute
{
	SIPCCMsg_SmartRoute_OldUserTactic();
	~SIPCCMsg_SmartRoute_OldUserTactic()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(routeDest!=NULL)	delete routeDest;
		routeDest = NULL;
		routeDestLen = 0;
		if(theCorporation!=NULL) delete theCorporation;
		theCorporation = NULL;
		theCorporationLen = 0;
		theTactic = -1;
	}
	
	void SetRouteDest(string routedest);
	string GetRouteDest()
	{
		if(routeDestLen==0)	return "";
		return string(routeDest);
	}
	
	void SetTheCorporation(string thecorporation);
	string GetTheCorporation()
	{
		if(theCorporationLen==0)	return "";
		return string(theCorporation);
	}
	
	int theTactic;
private:
	char* theCorporation;
	int theCorporationLen;
	char* routeDest;
	int routeDestLen;
	virtual int GetMyMemSize();
};

///Type_SmartRoute_RouteTactic
struct SIPCCMsg_SmartRoute_RouteTactic : public SIPCCMsg_SmartRoute
{
	SIPCCMsg_SmartRoute_RouteTactic();
	~SIPCCMsg_SmartRoute_RouteTactic()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(theCorporation!=NULL) delete theCorporation;
		theCorporation = NULL;
		theCorporationLen = 0;
		if(routeDest!=NULL)	delete routeDest;
		routeDest = NULL;
		routeDestLen = 0;
		theTactic = -1;
		acdServerIP = 0;
		acdServerPort = 0;
	}
	void SetTheCorporation(string thecorporation);
	string GetTheCorporation()
	{
		if(theCorporationLen==0)	return "";
		return string(theCorporation);
	}
	void SetRouteDest(string routedest);
	string GetRouteDest()
	{
		if(routeDestLen==0)	return "";
		return string(routeDest);
	}
	
	int theTactic;
	unsigned long acdServerIP;
	unsigned short acdServerPort;
private:
	char* theCorporation;
	int theCorporationLen;
	char* routeDest;
	int routeDestLen;
	virtual int GetMyMemSize();
};

//Class_SmartRoute
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
///Class_DataCollection
struct SIPCCMsg_DataCollection : public SIPCCMessage
{
	SIPCCMsg_DataCollection();
	~SIPCCMsg_DataCollection()
	{
		ReleaseMemory();
	};
	
	virtual int GetMyMemSize(){return 0;}
	virtual int FillBuf(char*& thebuf){return 0;}
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0){}
	virtual void ReleaseMemory(){}
};

///Type_Collect_RegisteConf
struct SIPCCMsg_Collect_RegisteConf : public SIPCCMsg_DataCollection
{
	SIPCCMsg_Collect_RegisteConf();
	~SIPCCMsg_Collect_RegisteConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}

	string Version;
	
	int MsgSeq;
	int SplitCount;

	string TableName;
	string FieldName;

	string InvokeID;
	
private:
	virtual int GetMyMemSize();
};

///Type_Collect_StatProcess
struct SIPCCMsg_Collect_StatProcess : public SIPCCMsg_DataCollection
{
	SIPCCMsg_Collect_StatProcess();
	~SIPCCMsg_Collect_StatProcess()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(statSQL!=NULL)	delete statSQL;
		statSQL = NULL;
		statSQLLen = 0;
		
		iMsgSeq = 0;
		iSplitCount = 0;
		iMsgIvokeID = "";
	}
	
	void  SetStatSQL(string statsql);
	string GetStatSQL()
	{
		if(statSQLLen == 0)	return "";
		if ( !(VerifyData(statSQLLen, STATSQL_LEN)) ) {return "";}
		return string(statSQL);
	}
	
	int iMsgSeq;
	int iSplitCount;
	string iMsgIvokeID;
	int iMsgLevel;

	int iType; //0为默认，传出来的SQL可以直接执行，1为传送过来的是值
	string Version;
	string TableName;
	int bResend;

	string strStatSQL;
	string strManagerId;
private:
	char* statSQL;
	int statSQLLen; 
	virtual int GetMyMemSize();
};

///Type_Collect_StatProcessConf
struct SIPCCMsg_Collect_StatProcessConf : public SIPCCMsg_DataCollection
{
	SIPCCMsg_Collect_StatProcessConf()
	{
		msgType = Type_Collect_StatProcessConf;
		iMsgIvokeID = "";
		iSQLState = 0;
		lSec = 0;
	}
	~SIPCCMsg_Collect_StatProcessConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	string iMsgIvokeID;
	int iSQLState;
	unsigned long lSec;
private:
	virtual int GetMyMemSize();
};

//Type_Collect_BeatHeart
struct SIPCCMsg_Collect_BeatHeart : public SIPCCMsg_DataCollection
{
	SIPCCMsg_Collect_BeatHeart()
	{
		msgType = Type_Collect_BeatHeart;
	}
	~SIPCCMsg_Collect_BeatHeart()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf)
	{
		thebuf = new char[GetMyMemSize()];
		int theBufContent = FillMsgHead(thebuf);

		memmove(thebuf+theBufContent, &this->isFatherNode, sizeof(bool));
		theBufContent += sizeof(bool);

		return theBufContent;
	};
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0)
	{
		int theBufContent = AnalyzeMsgHead(thebuf);

		if(theBufContent == msgsize)
			return;

		memmove(&this->isFatherNode, thebuf+theBufContent, sizeof(bool));
		theBufContent += sizeof(bool);
	};
	virtual void ReleaseMemory()
	{};

	bool isFatherNode;
private:
	virtual int GetMyMemSize()
	{
		int memSize = 2*sizeof(int);		//msgclass+msgtype

		memSize += sizeof(bool);
		return memSize;
	}
};

///Type_Storage_Registe
struct SIPCCMsg_Storage_Registe : public SIPCCMsg_DataCollection
{
	SIPCCMsg_Storage_Registe();
	~SIPCCMsg_Storage_Registe()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	string Version;

private:
	virtual int GetMyMemSize();
};

///Type_Storage_UnRegiste
struct SIPCCMsg_Storage_UnRegiste : public SIPCCMsg_DataCollection
{
	SIPCCMsg_Storage_UnRegiste();
	~SIPCCMsg_Storage_UnRegiste()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
private:
	virtual int GetMyMemSize();
};

///Type_Client_GetDepartNAgentInfo
struct SIPCCMsg_Client_GetDepartNAgentInfo : SIPCCMsg_Client
{
	SIPCCMsg_Client_GetDepartNAgentInfo();
	~SIPCCMsg_Client_GetDepartNAgentInfo()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{		
		if(corporationName != NULL)	delete corporationName;
		corporationName = NULL;
		corporationNameLen = 0;
		if(theDepartment != NULL)	delete theDepartment;
		theDepartment = NULL;
		theDepartmentLen = 0;
	}
	void SetCorporationName(string corporationname);
	string GetCorporationName()
	{
		if(corporationNameLen==0)	return "";
		if ( !(VerifyData(corporationNameLen, CORPNAME_LEN)) ) {return "";}
		return string(corporationName);
	}
	void SetTheDepartment(string thedepartment);
	string GetTheDepartment()	
	{
		if(theDepartmentLen == 0)	return "";
		if ( !(VerifyData(theDepartmentLen, CORPNDEPT_LEN)) ) {return "";}
		return string(theDepartment);
	}
	int getMode;
	string invokeID;
private:
	char* corporationName;
	int corporationNameLen;
	char* theDepartment;
	int theDepartmentLen;
	virtual int GetMyMemSize();
};

///Type_Client_GetGroupRequest
struct SIPCCMsg_Client_GetGroupRequest : SIPCCMsg_Client
{
	SIPCCMsg_Client_GetGroupRequest();
	~SIPCCMsg_Client_GetGroupRequest()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{		
	}
	
	string invokeID;
	
private:
	virtual int GetMyMemSize();
};
///Class_Client
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
///Class_Gateway
struct SIPCCMsg_Gateway : public SIPCCMessage
{
	SIPCCMsg_Gateway();
	~SIPCCMsg_Gateway()
	{
		ReleaseMemory();
	};
	
	virtual int GetMyMemSize(){return 0;}
	virtual int FillBuf(char*& thebuf){return 0;}
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0){}
	virtual void ReleaseMemory(){}
};

///Type_Gateway_Login
struct SIPCCMsg_Gateway_Login : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_Login();
	~SIPCCMsg_Gateway_Login()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(gatewayName != NULL)	delete gatewayName;
		gatewayName = NULL;
		gatewayNameLen = 0;
		if(computerSymbol != NULL)	delete computerSymbol;
		computerSymbol = NULL;
		computerSymbolLen = 0;
		if(theAccount != NULL)	delete theAccount;
		theAccount = NULL;
		theAccountLen = 0;
		if(thePassword != NULL)	delete thePassword;
		thePassword = NULL;
		thePasswordLen = 0;
		
		trunkCount = 0;
		natType = 0;
	}
	void SetGatewayName(string gatewayname);
	string GetGatewayName()
	{
		if(gatewayNameLen==0)	return "";
		if ( !(VerifyData(gatewayNameLen, GWNAME_LEN)) ) {return "";}
		return string(gatewayName);
	}
	void SetComputerSymbol(string computersymbol);
	string GetComputerSymbol()
	{
		if(computerSymbolLen==0)	return "";
		if ( !(VerifyData(computerSymbolLen, COMSYMBOL_LEN)) ) {return "";}
		return string(computerSymbol);
	}
	void SetTheAccount(string theaccount);
	string GetTheAccount()
	{
		if(theAccountLen==0)	return "";
		if ( !(VerifyData(theAccountLen, ACCOUNT_LEN)) ) {return "";}
		return string(theAccount);
	}
	void SetThePassword(string thepassword);
	string GetThePassword()
	{
		if(thePasswordLen==0)	return "";
		if ( !(VerifyData(theAccountLen, PASSWORD_LEN)) ) {return "";}
		return string(thePassword);
	}
	
	int trunkCount;
	unsigned long lanIP;
	unsigned short lanPort;
	
	string gwPartNo;
	int     natType;
	unsigned long wanIP;
	unsigned short wanPort;
	int  ConferenceAgentCount;
	int  isProxyRegister;


private:
	char* gatewayName;
	int gatewayNameLen;
	char* computerSymbol;
	int computerSymbolLen;
	char* theAccount;
	int theAccountLen;
	char* thePassword;
	int thePasswordLen;
	virtual int GetMyMemSize();
public:
};
//////////////////////////////////////////////////////////////////////////
// 开始 新增消息网关使能置位 [12/25/2007 lixg]
///Type_Gateway_Valid
struct SIPCCMsg_Gateway_Valid : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_Valid();
	~SIPCCMsg_Gateway_Valid()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(gatewayName != NULL)	delete gatewayName;
		gatewayName = NULL;
		gatewayNameLen = 0;
		if(computerSymbol != NULL)	delete computerSymbol;
		computerSymbol = NULL;
		computerSymbolLen = 0;
		bValid = 0;
	}
	void SetGatewayName(string gatewayname);
	string GetGatewayName()
	{
		if(gatewayNameLen==0)	return "";
		if ( !(VerifyData(gatewayNameLen, GWNAME_LEN)) ) {return "";}
		return string(gatewayName);
	}
	void SetComputerSymbol(string computersymbol);
	string GetComputerSymbol()
	{
		if(computerSymbolLen==0)	return "";
		if ( !(VerifyData(computerSymbolLen, COMSYMBOL_LEN)) ) {return "";}
		return string(computerSymbol);
	}
	BYTE BValid() const { return bValid; }
	void BValid(BYTE val) { bValid = val; }
private:
	char* gatewayName;
	int gatewayNameLen;
	char* computerSymbol;
	int computerSymbolLen;
	BYTE bValid;	// 网关是否可用
	
	virtual int GetMyMemSize();
public:
};
// 结束 [12/25/2007 lixg]
//////////////////////////////////////////////////////////////////////////

///Type_Gateway_Logout
struct SIPCCMsg_Gateway_Logout : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_Logout();
	~SIPCCMsg_Gateway_Logout()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(gatewayName != NULL)	delete gatewayName;
		gatewayName = NULL;
		gatewayNameLen = 0;
		if(computerSymbol != NULL)	delete computerSymbol;
		computerSymbol = NULL;
		computerSymbolLen = 0;
		if(theAccount != NULL)	delete theAccount;
		theAccount = NULL;
		theAccountLen = 0;
		if(thePassword != NULL)	delete thePassword;
		thePassword = NULL;
		thePasswordLen = 0;
	}
	void SetGatewayName(string gatewayname);
	string GetGatewayName()
	{
		if(gatewayNameLen==0)	return "";
		if ( !(VerifyData(gatewayNameLen, GWNAME_LEN)) ) {return "";}
		return string(gatewayName);
	}
	void SetComputerSymbol(string computersymbol);
	string GetComputerSymbol()
	{
		if(computerSymbolLen==0)	return "";
		if ( !(VerifyData(computerSymbolLen, COMSYMBOL_LEN)) ) {return "";}
		return string(computerSymbol);
	}
	void SetTheAccount(string theaccount);
	string GetTheAccount()
	{
		if(theAccountLen==0)	return "";
		if ( !(VerifyData(theAccountLen, ACCOUNT_LEN)) ) {return "";}
		return string(theAccount);
	}
	void SetThePassword(string thepassword);
	string GetThePassword()
	{
		if(thePasswordLen==0)	return "";
		if ( !(VerifyData(thePasswordLen, PASSWORD_LEN)) ) {return "";}
		return string(thePassword);
	}
private:
	char* gatewayName;
	int gatewayNameLen;
	char* computerSymbol;
	int computerSymbolLen;
	char* theAccount;
	int theAccountLen;
	char* thePassword;
	int thePasswordLen;
	virtual int GetMyMemSize();
public:
};

///Type_Gateway_LoginConf
struct SIPCCMsg_Gateway_LoginConf : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_LoginConf();
	~SIPCCMsg_Gateway_LoginConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		bSucc = 0;
		HeartBeatServerIP = 0;
		HeartBeatServerPort = 0;
		HeartBeatServerBackupIP = 0;
		HeartBeatServerBackupPort = 0;
		TrunkDataDistributeServerIp=0;
	    TrunkDataDistributeServerPort=0;
		ServiceID=0;
		HeartBeatServerID=0;
		HeartBeatServerBackupID=0;

		recServerID = 0;
		recSymbol = "";
		recServerIP = "";
		recFilePath = "";
		recPathMode = 0;

		recServerID_Backup = 0;
		recSymbol_Backup = "";
		recServerIP_Backup = "";
		recFilePath_Backup = "";
		recPathMode_Backup = 0;
	}
	
	char bSucc;
	
	unsigned long HeartBeatServerIP;
	unsigned short HeartBeatServerPort;	
	unsigned long HeartBeatServerBackupIP;
	unsigned short HeartBeatServerBackupPort;
	unsigned long  TrunkDataDistributeServerIp;
	unsigned short TrunkDataDistributeServerPort;
 	int ServiceID;
	int         HeartBeatServerID;
	int        HeartBeatServerBackupID;

	int recServerID;
	string recSymbol;
	string recServerIP;
	string recFilePath;
	int recPathMode;

	int recServerID_Backup;
	string recSymbol_Backup;
	string recServerIP_Backup;
	string recFilePath_Backup;
	int recPathMode_Backup;
	int operationMode;			//默认为2，表示须有两个心跳服务；为0表示无心跳服务；

	int needProxyRegister;		//默认为0，表示网关可直接注册；为1表示网关需要代理注册；
	string gatewayName;
	string computerSymbol;


private:
	virtual int GetMyMemSize();
};

///Type_Gateway_LoadInfo
struct SIPCCMsg_Gateway_LoadInfo : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_LoadInfo();
	~SIPCCMsg_Gateway_LoadInfo()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
private:
	virtual int GetMyMemSize();
};

///Type_Gateway_SetBaseInfo
struct SIPCCMsg_Gateway_SetBaseInfo : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_SetBaseInfo();
	~SIPCCMsg_Gateway_SetBaseInfo()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(gatewayName != NULL)	delete gatewayName;
		gatewayName = NULL;
		gatewayNameLen = 0;
		if(theAccount != NULL)	delete theAccount;
		theAccount = NULL;
		theAccountLen = 0;
		if(thePassword != NULL)	delete thePassword;
		thePassword = NULL;
		thePasswordLen = 0;
	}
	void SetGatewayName(string gatewayname);
	string GetGatewayName()
	{
		if(gatewayNameLen==0)	return "";
		if ( !(VerifyData(gatewayNameLen, GWNAME_LEN)) ) {return "";}
		return string(gatewayName);
	}
	void SetTheAccount(string theaccount);
	string GetTheAccount()
	{
		if(theAccountLen==0)	return "";
		if ( !(VerifyData(theAccountLen, ACCOUNT_LEN)) ) {return "";}
		return string(theAccount);
	}
	void SetThePassword(string thepassword);
	string GetThePassword()
	{
		if(thePasswordLen==0)	return "";
		if ( !(VerifyData(thePasswordLen, PASSWORD_LEN)) ) {return "";}
		return string(thePassword);
	}
private:
	char* gatewayName;
	int gatewayNameLen;
	char* theAccount;
	int theAccountLen;
	char* thePassword;
	int thePasswordLen;
	virtual int GetMyMemSize();
};

///Type_Gateway_AddPrefixNoInfo
struct SIPCCMsg_Gateway_AddPrefixNoInfo : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_AddPrefixNoInfo();
	~SIPCCMsg_Gateway_AddPrefixNoInfo()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(gatewayName != NULL)	delete gatewayName;
		gatewayName = NULL;
		gatewayNameLen = 0;
		if(prefixList != NULL)	delete prefixList;
		prefixList = NULL;
		prefixListLen = 0;
	}
	void SetGatewayName(string gatewayname);
	string GetGatewayName()
	{
		if(gatewayNameLen==0)	return "";
		if ( !(VerifyData(gatewayNameLen, GWNAME_LEN)) ) {return "";}
		return string(gatewayName);
	}
	void SetPrefixList(string prefixlist);
	string GetPrefixList()
	{
		if(prefixListLen==0)	return "";
		if ( !(VerifyData(prefixListLen, PREFIXLIST_LEN)) ) {return "";}
		return string(prefixList);
	}

	string invokeID;
private:
	char* gatewayName;
	int gatewayNameLen;
	char* prefixList;
	int prefixListLen;
	virtual int GetMyMemSize();
};

///Type_Gateway_SetCorporationInfo
struct SIPCCMsg_Gateway_SetCorporationInfo : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_SetCorporationInfo();
	~SIPCCMsg_Gateway_SetCorporationInfo()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(gatewayName != NULL)	delete gatewayName;
		gatewayName = NULL;
		gatewayNameLen = 0;
		if(corporationName != NULL)	delete corporationName;
		corporationName = NULL;
		corporationNameLen = 0;
		if(phoneNo != NULL)	delete phoneNo;
		phoneNo = NULL;
		phoneNoLen = 0;
		callInLicence = 0;
		callOutLicence = 0;
	}
	void SetGatewayName(string gatewayname);
	string GetGatewayName()
	{
		if(gatewayNameLen==0)	return "";
		return string(gatewayName);
	}
	void SetCorporationName(string corporationname);
	string GetCorporationName()
	{
		if(corporationNameLen==0)	return "";
		return string(corporationName);
	}
	void SetPhoneNo(string phoneno);
	string GetPhoneNo()
	{
		if(phoneNoLen==0)	return "";
		return string(phoneNo);
	}
	int callInLicence;
	int callOutLicence;
private:
	char* gatewayName;
	int gatewayNameLen;
	char* corporationName;
	int corporationNameLen;
	char* phoneNo;
	int phoneNoLen;
	virtual int GetMyMemSize();
};

///Type_Gateway_DelCorporationInfo
struct SIPCCMsg_Gateway_DelCorporationInfo : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_DelCorporationInfo();
	~SIPCCMsg_Gateway_DelCorporationInfo()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(corporationName != NULL)	delete corporationName;
		corporationName = NULL;
		corporationNameLen = 0;
	}
	void SetCorporationName(string corporationname);
	string GetCorporationName()
	{
		if(corporationNameLen==0)	return "";
		if ( !(VerifyData(corporationNameLen, CORPNAME_LEN)) ) {return "";}
		return string(corporationName);
	}
	
private:
	char* corporationName;
	int corporationNameLen;
	virtual int GetMyMemSize();
};

///Type_Gateway_QueryGWConf
struct SIPCCMsg_Gateway_QueryGWConf : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_QueryGWConf();
	~SIPCCMsg_Gateway_QueryGWConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	string comSymbol;
	string gwName;
	string newPhoneNo;
	string gwPartNo;
	int	   dtmfEN;
	string agentID;
	string gwAreaCode;	// 网关所在地区号
	string failedCause;	//失败原因
	int    usedBackupTG;	//外呼是否使用了备份中继组，0为没有，1为有

	int calloutByIAD;
	string routeContent;
	int callerNoResult;
	string ManagerTel;//企业小号   

private:
	virtual int GetMyMemSize();
};

///Type_Gateway_CallInQuery
struct SIPCCMsg_Gateway_CallInQuery : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_CallInQuery();
	~SIPCCMsg_Gateway_CallInQuery()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(gatewayName != NULL)	delete gatewayName;
		gatewayName = NULL;
		gatewayNameLen = 0;
		if(computerSymbol != NULL) delete computerSymbol;
		computerSymbol = NULL;
		computerSymbolLen = 0;
		if(phoneNo != NULL)	delete phoneNo;
		phoneNo = NULL;
		phoneNoLen = 0;
		if(trunkNo != NULL)	delete trunkNo;
		trunkNo = NULL;
		trunkNoLen = 0;
	}
	void SetGatewayName(string gatewayname);
	string GetGatewayName()
	{
		if(gatewayNameLen==0)	return "";
		if ( !(VerifyData(gatewayNameLen, GWNAME_LEN)) ) {return "";}
		return string(gatewayName);
	}
	void SetComputerSymbol(string computersymbol);
	string GetComputerSymbol()
	{
		if(computerSymbolLen==0)	return "";
		if ( !(VerifyData(computerSymbolLen, COMSYMBOL_LEN)) ) {return "";}
		return string(computerSymbol);
	}
	void SetPhoneNo(string phoneno);
	string GetPhoneNo()
	{
		if(phoneNoLen==0)	return "";
		if ( !(VerifyData(phoneNoLen, PHONENO_LEN)) ) {return "";}
		return string(phoneNo);
	}
	void SetTrunkNo(string trunkno);
	string GetTrunkNo()
	{
		if(trunkNoLen==0)	return "";
		if ( !(VerifyData(trunkNoLen, TRUNKNO_LEN)) ) {return "";}
		return string(trunkNo);
	}
private:
	char* gatewayName;
	int gatewayNameLen;
	char* computerSymbol;
	int computerSymbolLen;
	char* phoneNo;
	int phoneNoLen;
	char* trunkNo;
	int trunkNoLen;
	virtual int GetMyMemSize();
};

///Type_Gateway_CallInQueryConf
struct SIPCCMsg_Gateway_CallInQueryConf : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_CallInQueryConf();
	~SIPCCMsg_Gateway_CallInQueryConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		bLicenceOK = 1;
		
		if(corporationName != NULL)	delete corporationName;
		corporationName = NULL;
		corporationNameLen = 0;
		if(trunkNo != NULL)	delete trunkNo;
		trunkNo = NULL;
		trunkNoLen = 0;
	}
	void SetTrunkNo(string trunkno);
	string GetTrunkNo()
	{
		if(trunkNoLen==0)	return "";
		return string(trunkNo);
	}
	void SetCorporationName(string corporationname);
	string GetCorporationName()
	{
		if(corporationNameLen==0)	return "";
		return string(corporationName);
	}
	
	char bLicenceOK;
private:
	char* trunkNo;
	int trunkNoLen;
	char* corporationName;
	int corporationNameLen;
	virtual int GetMyMemSize();
};

///Type_Gateway_SetTrunkState
struct SIPCCMsg_Gateway_SetTrunkState : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_SetTrunkState();
	~SIPCCMsg_Gateway_SetTrunkState()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(gatewayName != NULL)	delete gatewayName;
		gatewayName = NULL;
		gatewayNameLen = 0;
		if(computerSymbol != NULL)	delete computerSymbol;
		computerSymbol = NULL;
		computerSymbolLen = 0;
		if(corporationName != NULL)	delete corporationName;
		corporationName = NULL;
		corporationNameLen = 0;
	}
	void SetGatewayName(string gatewayname);
	string GetGatewayName()
	{
		if(gatewayNameLen==0)	return "";
		if ( !(VerifyData(gatewayNameLen, GWNAME_LEN)) ) {return "";}
		return string(gatewayName);
	}
	void SetComputerSymbol(string computersymbol);
	string GetComputerSymbol()
	{
		if(computerSymbolLen==0)	return "";
		if ( !(VerifyData(computerSymbolLen, COMSYMBOL_LEN)) ) {return "";}
		return string(computerSymbol);
	}
	void SetCorporationName(string corporationname);
	string GetCorporationName()
	{
		if(corporationNameLen==0)	return "";
		if ( !(VerifyData(corporationNameLen, CORPNAME_LEN)) ) {return "";}
		return string(corporationName);
	}
	
	bool bIsCallin;
	bool bIdle;
private:
	char* gatewayName;
	int gatewayNameLen;
	char* computerSymbol;
	int computerSymbolLen;
	char* corporationName;
	int corporationNameLen;
	virtual int GetMyMemSize();
};

///SIPCCMsg_Gateway_AgentTestNetConf
struct SIPCCMsg_Gateway_AgentTestNetConf : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_AgentTestNetConf();
	~SIPCCMsg_Gateway_AgentTestNetConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
private:
	virtual int GetMyMemSize();
};

///Type_Gateway_QueryGWLanInfoConf
struct SIPCCMsg_Gateway_QueryGWLanInfoConf : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_QueryGWLanInfoConf();
	~SIPCCMsg_Gateway_QueryGWLanInfoConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	string gwName;
	unsigned long lanIP;
	unsigned short lanPort;
private:
	virtual int GetMyMemSize();
};

///Type_Gateway_SyncTrunkState
struct SIPCCMsg_Gateway_SyncTrunkState : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_SyncTrunkState();
	~SIPCCMsg_Gateway_SyncTrunkState()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(gatewayName != NULL)	delete gatewayName;
		gatewayName = NULL;
		gatewayNameLen = 0;
		if(computerSymbol != NULL)	delete computerSymbol;
		computerSymbol = NULL;
		computerSymbolLen = 0;
		if(stateList != NULL) delete stateList;
		stateList = NULL;
		stateListLen = 0;
	}
	
	void SetGatewayName(string gatewayname);
	string GetGatewayName()
	{
		if(gatewayNameLen==0)	return "";
		if ( !(VerifyData(gatewayNameLen, GWNAME_LEN)) ) {return "";}
		return string(gatewayName);
	}
	
	void SetComputerSymbol(string computersymbol);
	string GetComputerSymbol()
	{
		if(computerSymbolLen==0)	return "";
		if ( !(VerifyData(computerSymbolLen, COMSYMBOL_LEN)) ) {return "";}
		return string(computerSymbol);
	}
	
	void SetStateList(string sStateList);
	string GetStateList()
	{
		if(stateListLen==0)	return "";
		if ( !(VerifyData(stateListLen, STATELIST_LEN)) ) {return "";}
		return string(stateList);
	}
	
private:
	virtual int GetMyMemSize();
	
	char* gatewayName;
	int gatewayNameLen;
	char* computerSymbol;
	int computerSymbolLen;
	char* stateList;
	int stateListLen;
};

///Type_Gateway_ReConnect
struct SIPCCMsg_Gateway_ReConnect : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_ReConnect();
	~SIPCCMsg_Gateway_ReConnect()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
private:
	virtual int GetMyMemSize();
};

///Type_Gateway_AgentTalkBegin
struct SIPCCMsg_Gateway_AgentTalkBegin : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_AgentTalkBegin();
	~SIPCCMsg_Gateway_AgentTalkBegin()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	char bAgentCallOut;
	string trunkPhoneNo;
	string agentName;
	string pstnPhoneNo;
	string curTime;
	string invokeID;
	unsigned long lanIp;
	unsigned long wanIp;
	string chargeMode;
	string corpName;
	
private:
	virtual int GetMyMemSize();
};

///Type_Gateway_AgentTalkEnd
struct SIPCCMsg_Gateway_AgentTalkEnd : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_AgentTalkEnd();
	~SIPCCMsg_Gateway_AgentTalkEnd()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	char bAgentCallOut;
	string trunkPhoneNo;
	string agentName;
	string pstnPhoneNo;
	string curTime;
	string invokeID;
	unsigned long lanIp;
	unsigned long wanIp;
	string chargeMode;
	string corpName;
	
private:
	virtual int GetMyMemSize();
};

///Type_Gateway_SetRecord
struct SIPCCMsg_Gateway_SetRecord : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_SetRecord();
	~SIPCCMsg_Gateway_SetRecord()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	char bSet;
	string agentName;
	
private:
	virtual int GetMyMemSize();
};

///Type_Gateway_SetRecordConf
struct SIPCCMsg_Gateway_SetRecordConf : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_SetRecordConf();
	~SIPCCMsg_Gateway_SetRecordConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	char bSucc;
	string oldAgent;
	string curAgent;
	
private:
	virtual int GetMyMemSize();
};

///Type_Gateway_GetTrunkState
struct SIPCCMsg_Gateway_GetTrunkState : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_GetTrunkState();
	~SIPCCMsg_Gateway_GetTrunkState()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
private:
	virtual int GetMyMemSize();
};

///Type_Gateway_GetTrunkStateConf
struct SIPCCMsg_Gateway_GetTrunkStateConf : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_GetTrunkStateConf();
	~SIPCCMsg_Gateway_GetTrunkStateConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	char bEnd;
	string StateString;
private:
	virtual int GetMyMemSize();
};

///Type_Gateway_ForceHangup
struct SIPCCMsg_Gateway_ForceHangup : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_ForceHangup();
	~SIPCCMsg_Gateway_ForceHangup()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	string TrunkDn;
private:
	virtual int GetMyMemSize();
};

///Type_Gateway_DisableSth
struct SIPCCMsg_Gateway_DisableSth : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_DisableSth();
	~SIPCCMsg_Gateway_DisableSth()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	char bDisable;
	string AgentName;
	string CalledNum;
private:
	virtual int GetMyMemSize();
};

///Type_Gateway_400CallBackCmd
struct SIPCCMsg_Gateway_400CallBackCmd : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_400CallBackCmd();
	~SIPCCMsg_Gateway_400CallBackCmd()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	string managerID;
	string corpName;
	string callBackPhoneNo;
	string managerDialNo;
private:
	virtual int GetMyMemSize();
};

///Type_Gateway_QueryAgentInfo
struct SIPCCMsg_Gateway_QueryAgentInfo : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_QueryAgentInfo();
	~SIPCCMsg_Gateway_QueryAgentInfo()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	string invokeID;
	string agentExtRealNo;
	
private:
	virtual int GetMyMemSize();
};

///Type_Gateway_IsAgentLogin
struct SIPCCMsg_Gateway_IsAgentLogin : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_IsAgentLogin();
	~SIPCCMsg_Gateway_IsAgentLogin()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	string agentID;
	
	int invokeType;
	string invokeId;

	string  connectPhoneNo;
	string  handleId;

private:
	virtual int GetMyMemSize();
};

///Type_Gateway_CallAgentExtFailed , wpAgent 直接外呼电话时回呼本机失败
struct SIPCCMsg_Gateway_CallAgentExtFailed : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_CallAgentExtFailed();
	~SIPCCMsg_Gateway_CallAgentExtFailed()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	string agentID;
	string  managerId;
	
private:
	virtual int GetMyMemSize();
};

///Type_Gateway_CallUserFailed_WpAgent
struct SIPCCMsg_Gateway_CallUserFailed_WpAgent : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_CallUserFailed_WpAgent();
	~SIPCCMsg_Gateway_CallUserFailed_WpAgent()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	string agentID;
	string  managerId;
	
private:
	virtual int GetMyMemSize();
};

///Type_Gateway_AgentExtCallerFailed, 此信令废弃
struct SIPCCMsg_Gateway_AgentExtCallerFailed : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_AgentExtCallerFailed();
	~SIPCCMsg_Gateway_AgentExtCallerFailed()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	string agentID;
	
private:
	virtual int GetMyMemSize();
};

///Type_Gateway_AgentExtCallSucc, wpAgent 呼叫用户成功
struct SIPCCMsg_Gateway_AgentExtCallSucc : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_AgentExtCallSucc();
	~SIPCCMsg_Gateway_AgentExtCallSucc()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	string agentID;
	string gwAgentLine;
	string gwUserLine;
	
	unsigned long gwAgentLineIp;
	unsigned short gwAgentLinePort;
	unsigned long gwUserLineIp;
	unsigned short gwUserLinePort;
	unsigned short gwCtrlPort;

	string  managerId;
private:
	virtual int GetMyMemSize();
};

///Type_Gateway_LoadDataConf
struct SIPCCMsg_Gateway_LoadDataConf : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_LoadDataConf();
	~SIPCCMsg_Gateway_LoadDataConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	string invokeID;
private:
	virtual int GetMyMemSize();
};

///Type_Gateway_ConfirmGWConf
struct SIPCCMsg_Gateway_ConfirmGWConf : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_ConfirmGWConf();
	~SIPCCMsg_Gateway_ConfirmGWConf()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}

	string invokeID;
	string resultContent;

	string GwName;
	string ComputerSymbol;
private:
	virtual int GetMyMemSize();
};

///Type_Gateway_HeartBeatConfirm
struct SIPCCMsg_Gateway_HeartBeatConfirm : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_HeartBeatConfirm();
	~SIPCCMsg_Gateway_HeartBeatConfirm()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}

	string invokeID;
	unsigned long localIP;
	unsigned short localPort;
	string GwName;
	string ComputerSymbol;
	int ServerType;		//0: SoftACDServer; 1: DataGwServer; 2: TollTransactionServer
	int isProxyRegister;	//默认为0，表示仅作为网关心跳服务；为1表示其作为网关代理服务；		





private:
	virtual int GetMyMemSize();
};

///Type_Gateway_GetHeartBeat
struct SIPCCMsg_Gateway_GetHeartBeat : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_GetHeartBeat();
	~SIPCCMsg_Gateway_GetHeartBeat()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		InvokeId = "";
		HeartBeatServerIP = 0;
		HeartBeatServerPort = 0;
		HeartBeatServerBackupIP = 0;
		HeartBeatServerBackupPort = 0;
		ServerID=0;
		ServerType=0;
		GatewayName="";
		ComputerSymbol="";

		
	}

	string InvokeId;
	unsigned long HeartBeatServerIP;
	unsigned short HeartBeatServerPort;
	unsigned long HeartBeatServerBackupIP;
	unsigned short HeartBeatServerBackupPort;
	 
	int  ServerID;
	int     ServerType;
	string  GatewayName;
	string  ComputerSymbol;

	
	
private:
	virtual int GetMyMemSize();
};

///Type_Gateway_GWLogoutConf
struct SIPCCMsg_Gateway_GWLogoutConf : public SIPCCMsg_Gateway			
{
	SIPCCMsg_Gateway_GWLogoutConf();
	~SIPCCMsg_Gateway_GWLogoutConf()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

	string GwName;
	string ComputerSymbol;

private:
	virtual int GetMyMemSize();
};

///Type_Gateway_GWMRegister
struct SIPCCMsg_Gateway_GWMRegister : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_GWMRegister();
	~SIPCCMsg_Gateway_GWMRegister()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}

	string ServerName;
	unsigned long ServerIp;
	unsigned short ServerPort;
private:
	virtual int GetMyMemSize();
};

///Type_Gateway_GWMConfirmConf
struct SIPCCMsg_Gateway_GWMConfirmConf : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_GWMConfirmConf();
	~SIPCCMsg_Gateway_GWMConfirmConf()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}

	string invokeID;
private:
	virtual int GetMyMemSize();
};

///Type_Gateway_LoadGWCorpInfo
struct SIPCCMsg_Gateway_LoadGWCorpInfo : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_LoadGWCorpInfo();
	~SIPCCMsg_Gateway_LoadGWCorpInfo()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}

	string ServerName;
private:
	virtual int GetMyMemSize();
};

///Class_Gateway
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
///Class_TextChat
struct SIPCCMsg_TextChat : public SIPCCMessage
{
	SIPCCMsg_TextChat();
	~SIPCCMsg_TextChat()
	{
		ReleaseMemory();
	};
	
	virtual int GetMyMemSize(){return 0;}
	virtual int FillBuf(char*& thebuf){return 0;}
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0){}
	virtual void ReleaseMemory(){}
};

///Type_Text_TextChat
struct SIPCCMsg_Text_TextChat : public SIPCCMsg_TextChat
{
	SIPCCMsg_Text_TextChat();
	~SIPCCMsg_Text_TextChat()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	};
	
	string Sender;
	string Receiver;
	string ChatWords;
	
private:
	virtual int GetMyMemSize();
};
///Class_Text

///////////////////////////////////////////////////////////////////////////
///Class_GwMonit
struct SIPCCMsg_GwMonit : public SIPCCMessage
{
	SIPCCMsg_GwMonit()
	{
		msgClass = Class_GwMonit;
	};
	
	~SIPCCMsg_GwMonit()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf) = 0;
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0) = 0;
	virtual void ReleaseMemory(){};
};

///Type_GwMonit_GetGwInfo
struct SIPCCMsg_GwMonit_GetGwInfo : public SIPCCMsg_GwMonit
{
	SIPCCMsg_GwMonit_GetGwInfo()
	{
		msgType = Type_GwMonit_GetGwInfo;
	};
	
	~SIPCCMsg_GwMonit_GetGwInfo()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	
	string GwName;
private:
	virtual int GetMyMemSize();
};

///Type_GwMonit_GetGwInfoConf
#pragma pack(1)

typedef struct 
{
	unsigned long Ip;
	unsigned short Port;
} IpPort;

typedef struct 
{
	int InLicence;
	int OutLicence;
} Licence;
#pragma pack()

struct SIPCCMsg_GwMonit_GetGwInfoConf : public SIPCCMsg_GwMonit
{
	SIPCCMsg_GwMonit_GetGwInfoConf()
	{
		msgType = Type_GwMonit_GetGwInfoConf;
	};
	
	~SIPCCMsg_GwMonit_GetGwInfoConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	
	void AddComputer(string sName, unsigned long iIp, unsigned short iPort);
	void AddCorporation(string sName, int iInLicence, int iOutLicence);
	
	map<string, IpPort> ComputerMap;
	map<string, Licence> LicenceMap;
private:
	virtual int GetMyMemSize();
};

///Type_GwMonit_RegMonit
struct SIPCCMsg_GwMonit_RegMonit : public SIPCCMsg_GwMonit
{
	SIPCCMsg_GwMonit_RegMonit()
	{
		msgType = Type_GwMonit_RegMonit;
	};
	
	~SIPCCMsg_GwMonit_RegMonit()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	
private:
	virtual int GetMyMemSize();
};

///Type_GwMonit_TrunkState
struct SIPCCMsg_GwMonit_TrunkState : public SIPCCMsg_GwMonit
{
	SIPCCMsg_GwMonit_TrunkState()
	{
		msgType = Type_GwMonit_TrunkState;
	};
	
	~SIPCCMsg_GwMonit_TrunkState()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	
	string ComputerName;
	string TrunkDN;
	int State;
	string CorproationName;
private:
	virtual int GetMyMemSize();
};
///Class_GwMonit
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
///Class_Redirect
struct SIPCCMsg_Redirect : public SIPCCMessage
{
	SIPCCMsg_Redirect()
	{
		msgClass = Class_Redirect;
	};
	
	~SIPCCMsg_Redirect()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf) = 0;
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0) = 0;
	virtual void ReleaseMemory(){};
};

///Type_Redirect_SearchPlatform
struct SIPCCMsg_Redirect_SearchPlatform : SIPCCMsg_Redirect
{
	SIPCCMsg_Redirect_SearchPlatform();
	~SIPCCMsg_Redirect_SearchPlatform()
	{
		ReleaseMemory();
	}
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	
	string managerID;
	string corpName;
	string agentID;//by hyj

	string loginRoute;
private:
	virtual int GetMyMemSize();
};

///Type_Redirect_SearchPlatformConf
struct SIPCCMsg_Redirect_SearchPlatformConf : SIPCCMsg_Redirect
{
	SIPCCMsg_Redirect_SearchPlatformConf();
	~SIPCCMsg_Redirect_SearchPlatformConf()
	{
		ReleaseMemory();
	}
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	
	string platformIP;
private:
	virtual int GetMyMemSize();
};

///Type_Redirect_GetPlatformList
struct SIPCCMsg_Redirect_GetPlatformList : SIPCCMsg_Redirect
{
	SIPCCMsg_Redirect_GetPlatformList();
	~SIPCCMsg_Redirect_GetPlatformList()
	{
		ReleaseMemory();
	}
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	
	string invokeID;
	
private:
	virtual int GetMyMemSize();
};

///Type_Redirect_GetPlatformListConf
struct SIPCCMsg_Redirect_GetPlatformListConf : SIPCCMsg_Redirect
{
	SIPCCMsg_Redirect_GetPlatformListConf();
	~SIPCCMsg_Redirect_GetPlatformListConf()
	{
		ReleaseMemory();
	}
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	
	string invokeID;
	string platformList;
	char bEnd;
private:
	virtual int GetMyMemSize();
};

///Type_Redirect_CorpRegister
struct SIPCCMsg_Redirect_CorpRegister : SIPCCMsg_Redirect
{
	SIPCCMsg_Redirect_CorpRegister();
	~SIPCCMsg_Redirect_CorpRegister()
	{
		ReleaseMemory();
	}
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	
	string managerID;
	string corpName;
	string platformIP;
	string agentDNS;
private:
	virtual int GetMyMemSize();
};

///Type_Redirect_GetCorpInfo
struct SIPCCMsg_Redirect_GetCorpInfo : SIPCCMsg_Redirect
{
	SIPCCMsg_Redirect_GetCorpInfo();
	~SIPCCMsg_Redirect_GetCorpInfo()
	{
		ReleaseMemory();
	}
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	
private:
	virtual int GetMyMemSize();
};

///Type_Redirect_GetCorpInfoConf
struct SIPCCMsg_Redirect_GetCorpInfoConf  : SIPCCMsg_Redirect
{
	SIPCCMsg_Redirect_GetCorpInfoConf();
	~SIPCCMsg_Redirect_GetCorpInfoConf()
	{
		ReleaseMemory();
	}
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	
	string corpInfoList;
	char bEnd;
private:
	virtual int GetMyMemSize();
};

///Type_Redirect_LoadCorpInfo
struct SIPCCMsg_Redirect_LoadCorpInfo  : SIPCCMsg_Redirect
{
	SIPCCMsg_Redirect_LoadCorpInfo();
	~SIPCCMsg_Redirect_LoadCorpInfo()
	{
		ReleaseMemory();
	}
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
private:
	virtual int GetMyMemSize();
};

///Type_Redirect_LoadCorpInfoConf
struct SIPCCMsg_Redirect_LoadCorpInfoConf  : SIPCCMsg_Redirect
{
	SIPCCMsg_Redirect_LoadCorpInfoConf();
	~SIPCCMsg_Redirect_LoadCorpInfoConf()
	{
		ReleaseMemory();
	}
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	
	string corpInfoList;
	char bEnd;
private:
	virtual int GetMyMemSize();
};

///Type_Redirect_LoadPlatformInfo
struct SIPCCMsg_Redirect_LoadPlatformInfo  : SIPCCMsg_Redirect
{
	SIPCCMsg_Redirect_LoadPlatformInfo();
	~SIPCCMsg_Redirect_LoadPlatformInfo()
	{
		ReleaseMemory();
	}
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
private:
	virtual int GetMyMemSize();
};

///Type_Redirect_LoadPlatformInfoConf
struct SIPCCMsg_Redirect_LoadPlatformInfoConf : SIPCCMsg_Redirect
{
	SIPCCMsg_Redirect_LoadPlatformInfoConf();
	~SIPCCMsg_Redirect_LoadPlatformInfoConf()
	{
		ReleaseMemory();
	}
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	
	string platformInfoList;
	char bEnd;
private:
	virtual int GetMyMemSize();
};

///Type_Redirect_AddCorpInfo
struct SIPCCMsg_Redirect_AddCorpInfo : SIPCCMsg_Redirect
{
	SIPCCMsg_Redirect_AddCorpInfo();
	~SIPCCMsg_Redirect_AddCorpInfo()
	{
		ReleaseMemory();
	}
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	
	string managerID;
	string corpName;
	string platformIP;
	string agentDNS;
private:
	virtual int GetMyMemSize();
};

///Type_Redirect_DelCorpInfo
struct SIPCCMsg_Redirect_DelCorpInfo : SIPCCMsg_Redirect
{
	SIPCCMsg_Redirect_DelCorpInfo();
	~SIPCCMsg_Redirect_DelCorpInfo()
	{
		ReleaseMemory();
	}
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	
	string managerID;
private:
	virtual int GetMyMemSize();
};

///Type_Redirect_AddPlatformInfo
struct SIPCCMsg_Redirect_AddPlatformInfo : SIPCCMsg_Redirect
{
	SIPCCMsg_Redirect_AddPlatformInfo();
	~SIPCCMsg_Redirect_AddPlatformInfo()
	{
		ReleaseMemory();
	}
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	
	string platformIP;
	string platformName;
private:
	virtual int GetMyMemSize();
};

///Type_Redirect_DelPlatformInfo
struct SIPCCMsg_Redirect_DelPlatformInfo : SIPCCMsg_Redirect
{
	SIPCCMsg_Redirect_DelPlatformInfo();
	~SIPCCMsg_Redirect_DelPlatformInfo()
	{
		ReleaseMemory();
	}
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	
	string platformIP;
private:
	virtual int GetMyMemSize();
};

///Class_Redirect
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
///Class_DlyStrategy
struct SIPCCMsg_DlyStrategy : public SIPCCMessage
{
	SIPCCMsg_DlyStrategy()
	{
		msgClass = Class_DlyStrategy;
	};
	
	~SIPCCMsg_DlyStrategy()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf) = 0;
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0) = 0;
	virtual void ReleaseMemory(){};
};

///Type_DlyStrategy_QueryStrategy
struct SIPCCMsg_DlyStrategy_QueryStrategy : SIPCCMsg_DlyStrategy
{
	SIPCCMsg_DlyStrategy_QueryStrategy();
	~SIPCCMsg_DlyStrategy_QueryStrategy()
	{
		ReleaseMemory();
	}
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	
	string agentPartNo;
	string gatewayPartNo;
	string calledPartNo;
	string GwLineDn;
private:
	virtual int GetMyMemSize();
};

///Type_DlyStrategy_QueryStrategyConf
struct SIPCCMsg_DlyStrategy_QueryStrategyConf : SIPCCMsg_DlyStrategy
{
	SIPCCMsg_DlyStrategy_QueryStrategyConf();
	~SIPCCMsg_DlyStrategy_QueryStrategyConf()
	{
		ReleaseMemory();
	}
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	
	int agent2GwDelay;	//-1 表示默认值
	int gw2CalledDelay;	//-1 表示默认值
	string GwLineDn;
private:
	virtual int GetMyMemSize();
};

///Type_DlyStrategy_AddStrategy
struct SIPCCMsg_DlyStrategy_AddStrategy : SIPCCMsg_DlyStrategy
{
	SIPCCMsg_DlyStrategy_AddStrategy();
	~SIPCCMsg_DlyStrategy_AddStrategy()
	{
		ReleaseMemory();
	}
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	
	int theType;	//0为 agent2GwDelay; 1为gw2CalledDelay
	string leftPartNo;
	string rightPartNo;
	int delayValue;
private:
	virtual int GetMyMemSize();
};

///Type_DlyStrategy_DelStrategy
struct SIPCCMsg_DlyStrategy_DelStrategy : SIPCCMsg_DlyStrategy
{
	SIPCCMsg_DlyStrategy_DelStrategy();
	~SIPCCMsg_DlyStrategy_DelStrategy()
	{
		ReleaseMemory();
	}
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	
	int theType;	//0为 agent2GwDelay; 1为gw2CalledDelay
	string leftPartNo;
	string rightPartNo;
private:
	virtual int GetMyMemSize();
};

///Type_DlyStrategy_LoadStrategy
struct SIPCCMsg_DlyStrategy_LoadStrategy : SIPCCMsg_DlyStrategy
{
	SIPCCMsg_DlyStrategy_LoadStrategy();
	~SIPCCMsg_DlyStrategy_LoadStrategy()
	{
		ReleaseMemory();
	}
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	
private:
	virtual int GetMyMemSize();
};

///Type_DlyStrategy_LoadStrategyConf
struct SIPCCMsg_DlyStrategy_LoadStrategyConf : SIPCCMsg_DlyStrategy
{
	SIPCCMsg_DlyStrategy_LoadStrategyConf();
	~SIPCCMsg_DlyStrategy_LoadStrategyConf()
	{
		ReleaseMemory();
	}
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	
	string strategyList;	//格式：type|partNo|delayValue
private:
	virtual int GetMyMemSize();
};

///Type_DlyStrategy_GetStrategy
struct SIPCCMsg_DlyStrategy_GetStrategy : SIPCCMsg_DlyStrategy
{
	SIPCCMsg_DlyStrategy_GetStrategy();
	~SIPCCMsg_DlyStrategy_GetStrategy()
	{
		ReleaseMemory();
	}
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	
private:
	virtual int GetMyMemSize();
};

///Type_DlyStrategy_GetStrategyConf
struct SIPCCMsg_DlyStrategy_GetStrategyConf : SIPCCMsg_DlyStrategy
{
	SIPCCMsg_DlyStrategy_GetStrategyConf();
	~SIPCCMsg_DlyStrategy_GetStrategyConf()
	{
		ReleaseMemory();
	}
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	
	string strategyList;	//格式：type|partNo|delayValue
	char bEnd;
private:
	virtual int GetMyMemSize();
};

///Class_DlyStrategy
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
///Class_TollQuery
struct SIPCCMsg_TollQuery : public SIPCCMessage
{
	SIPCCMsg_TollQuery();
	~SIPCCMsg_TollQuery()
	{
		ReleaseMemory();
	};
	
	virtual int GetMyMemSize(){return 0;}
	virtual int FillBuf(char*& thebuf){return 0;}
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0){}
	virtual void ReleaseMemory(){}
};

///Type_TollQuery_TollQuery
struct SIPCCMsg_TollQuery_TollQuery : public SIPCCMsg_TollQuery
{
	SIPCCMsg_TollQuery_TollQuery();
	~SIPCCMsg_TollQuery_TollQuery()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	string AgentName;
	string ChargeType;
	string PhoneNum;
	string Managerid;
	
private:
	virtual int GetMyMemSize();
};

enum TollQuery_Error
{
	TollQuery_Error_NoError,
		TollQuery_Error_AgentIsEmpty,
		TollQuery_Error_DbConnFail,
		TollQuery_Error_DbQueryFail,
		TollQuery_Error_AccountNoExist,
		TollQuery_Error_ServerBusy,
		
		TollQuery_Error_ManageridNoError,
		TollQuery_Error_ManageridIsEmpty,
};

///Type_TollQuery_TollQueryConf
struct SIPCCMsg_TollQuery_TollQueryConf : public SIPCCMsg_TollQuery
{
	SIPCCMsg_TollQuery_TollQueryConf();
	~SIPCCMsg_TollQuery_TollQueryConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	int ErrorCode;
	int UsableTime;
	
	double LeftMoney;
	int	ValidDay;
private:
	virtual int GetMyMemSize();
};

///Type_TollQuery_GwTollQuery
struct SIPCCMsg_TollQuery_GwTollQuery : public SIPCCMsg_TollQuery
{
	SIPCCMsg_TollQuery_GwTollQuery();
	~SIPCCMsg_TollQuery_GwTollQuery()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	string AgentName;
	string InvokeId;
	
private:
	virtual int GetMyMemSize();
};

///Type_TollQuery_GwTollQueryConf
struct SIPCCMsg_TollQuery_GwTollQueryConf : public SIPCCMsg_TollQuery
{
	SIPCCMsg_TollQuery_GwTollQueryConf();
	~SIPCCMsg_TollQuery_GwTollQueryConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	int ErrorCode;
	int UsableTime;
	string InvokeId;
private:
	virtual int GetMyMemSize();
};
///Class_TollQuery
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
///Class_SMS
struct SIPCCMsg_SMS : public SIPCCMessage
{
	SIPCCMsg_SMS();
	~SIPCCMsg_SMS()
	{
		ReleaseMemory();
	};
	
	virtual int GetMyMemSize(){return 0;}
	virtual int FillBuf(char*& thebuf){return 0;}
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0){}
	virtual void ReleaseMemory(){}
};

///Type_SMS_AddLinkman
struct SIPCCMsg_SMS_AddLinkman : public SIPCCMsg_SMS
{
	SIPCCMsg_SMS_AddLinkman();
	~SIPCCMsg_SMS_AddLinkman()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	string AgentName;
	string LinkManName;
	string PhoneNum;
	string Description;
	
private:
	virtual int GetMyMemSize();
};

///Type_SMS_DelLinkMan
struct SIPCCMsg_SMS_DelLinkman : public SIPCCMsg_SMS
{
	SIPCCMsg_SMS_DelLinkman();
	~SIPCCMsg_SMS_DelLinkman()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	string AgentName;
	string LinkManName;
private:
	virtual int GetMyMemSize();
};

///Type_SMS_ModifyLinkman
struct SIPCCMsg_SMS_ModifyLinkman : public SIPCCMsg_SMS
{
	SIPCCMsg_SMS_ModifyLinkman();
	~SIPCCMsg_SMS_ModifyLinkman()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	string AgentName;
	string LinkManName;
	string PhoneNum;
	string Description;
	
private:
	virtual int GetMyMemSize();
};
// 增加企业
/*
SIPCCMsg_SMS_AddCorp:public SIPCCMsg_SMS {
SIPCCMsg_SMS_AddCorp();
~SIPCCMsg_SMS_AddCorp() {
ReleaseMemory();
};

  virtual int FillBuf(char*& thebuf);
  virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
  virtual void ReleaseMemory()
  {
  }
  
	private:
	virtual int GetMyMemSize();
	}
	// 删除企业
	SIPCCMsg_SMS_DelCorp:public SIPCCMsg_SMS {
	}
*/
///Type_SMS_Send
struct SIPCCMsg_SMS_Send : public SIPCCMsg_SMS
{
	SIPCCMsg_SMS_Send();
	~SIPCCMsg_SMS_Send()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	string AgentName; // 座席id
	string PhoneNum; // 手机号码-多个
	string Text; // 短信内容
	unsigned short m_uPhoneCount; // 手机号码个数
	string m_strManagerID;
	string m_strSPNumber; // 扩展号码
	string m_strShort; // 公司简称
private:
	virtual int GetMyMemSize();
};

///Type_SMS_SendConf
struct SIPCCMsg_SMS_SendConf : public SIPCCMsg_SMS
{
	SIPCCMsg_SMS_SendConf();
	~SIPCCMsg_SMS_SendConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	char bSucc;
	string PhoneNum;
	string m_PSucc;
	string m_strManagerID;
	string m_sAgentID;
	string m_sText;
private:
	virtual int GetMyMemSize();
};

///Type_SMS_QueryLinkmanList
struct SIPCCMsg_SMS_QueryLinkmanList : public SIPCCMsg_SMS
{
	SIPCCMsg_SMS_QueryLinkmanList();
	~SIPCCMsg_SMS_QueryLinkmanList()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	string AgentName;
private:
	virtual int GetMyMemSize();
};

///Type_SMS_QueryLinkmanListConf
struct SIPCCMsg_SMS_QueryLinkmanListConf : public SIPCCMsg_SMS
{
	SIPCCMsg_SMS_QueryLinkmanListConf();
	~SIPCCMsg_SMS_QueryLinkmanListConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	string ID;
	string LinkManName;
	string PhoneNum;
	string Description;
	
private:
	virtual int GetMyMemSize();
};
// Type_SMS_OperServerLogin
struct SIPCCMsg_SMS_OperServerLogin: public SIPCCMsg_SMS {
	SIPCCMsg_SMS_OperServerLogin();
	~SIPCCMsg_SMS_OperServerLogin() {
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory() {
	}
	string managerID;
	string corName;
private:
	virtual int GetMyMemSize();
};
// Type_SMS_OperServerLoginConf,
struct SIPCCMsg_SMS_OperServerLoginConf: public SIPCCMsg_SMS {
	SIPCCMsg_SMS_OperServerLoginConf();
	~SIPCCMsg_SMS_OperServerLoginConf() {
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory() {
	}
	bool bLoginSuccess;
private:
	virtual int GetMyMemSize();
};
// Type_SMS_OperServerLogout,
struct SIPCCMsg_SMS_OperServerLogout: public SIPCCMsg_SMS {
	SIPCCMsg_SMS_OperServerLogout();
	~SIPCCMsg_SMS_OperServerLogout() {
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory() {
	}
	string managerID;
	string corName;
private:
	virtual int GetMyMemSize();
};
// Type_SMS_OperServerLogoutConf,
struct SIPCCMsg_SMS_OperServerLogoutConf: public SIPCCMsg_SMS {
	SIPCCMsg_SMS_OperServerLogoutConf();
	~SIPCCMsg_SMS_OperServerLogoutConf() {
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory() {
	}
	bool bLogoutSuccess;
private:
	virtual int GetMyMemSize();
};
// Type_SMS_Recved,
struct SIPCCMsg_SMS_Recved: public SIPCCMsg_SMS {
	SIPCCMsg_SMS_Recved();
	~SIPCCMsg_SMS_Recved() {
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory() {
	}
	string m_strPhoneNum;
	string m_strManagerID;
	string m_sText;
	string m_sTime;
private:
	virtual int GetMyMemSize();
};
// Type_SMS_RecvedConf,
struct SIPCCMsg_SMS_RecvedConf: public SIPCCMsg_SMS {
	SIPCCMsg_SMS_RecvedConf();
	~SIPCCMsg_SMS_RecvedConf() {
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory() {
	}
	bool m_bSuccess;
private:
	virtual int GetMyMemSize();
};
///Class_SMS
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
///Class_Toll
struct SIPCCMsg_Toll : public SIPCCMessage
{
	SIPCCMsg_Toll();
	~SIPCCMsg_Toll()
	{
		ReleaseMemory();
	};
	
	virtual int GetMyMemSize(){return 0;}
	virtual int FillBuf(char*& thebuf){return 0;}
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0){}
	virtual void ReleaseMemory(){};
};

///Type_Toll_400TrunkConnected
struct SIPCCMsg_Toll_400TrunkConnected : public SIPCCMsg_Toll
{
	SIPCCMsg_Toll_400TrunkConnected();
	~SIPCCMsg_Toll_400TrunkConnected()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	string invokeID;
	string curTime;
	string callerNo;
	string RealNo_400;
	string trunkNo;
private:
	virtual int GetMyMemSize();
};

///Type_Toll_400TrunkDisconnected
struct SIPCCMsg_Toll_400TrunkDisconnected : public SIPCCMsg_Toll
{
	SIPCCMsg_Toll_400TrunkDisconnected();
	~SIPCCMsg_Toll_400TrunkDisconnected()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	string invokeID;
	string curTime;
	string callerNo;
	string RealNo_400;
	string trunkNo;
private:
	virtual int GetMyMemSize();
};

///Type_Toll_400P2PTalkBegin
struct SIPCCMsg_Toll_400P2PTalkBegin : public SIPCCMsg_Toll
{
	SIPCCMsg_Toll_400P2PTalkBegin();
	~SIPCCMsg_Toll_400P2PTalkBegin()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	string invokeID;
	string curTime;
	string callerNo;
	string RealNo_400;
	string calledNo;
	string callerTrunkNo;
	string calledTrunkNo;
private:
	virtual int GetMyMemSize();
};

///Type_Toll_400P2PTalkEnd
struct SIPCCMsg_Toll_400P2PTalkEnd : public SIPCCMsg_Toll
{
	SIPCCMsg_Toll_400P2PTalkEnd();
	~SIPCCMsg_Toll_400P2PTalkEnd()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	string invokeID;
	string curTime;
	string callerNo;
	string RealNo_400;
	string calledNo;
	string callerTrunkNo;
	string calledTrunkNo;
private:
	virtual int GetMyMemSize();
};

///Type_Toll_AgentTransP2PTalkBegin
struct SIPCCMsg_Toll_AgentTransP2PTalkBegin : public SIPCCMsg_Toll
{
	SIPCCMsg_Toll_AgentTransP2PTalkBegin();
	~SIPCCMsg_Toll_AgentTransP2PTalkBegin()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	string invokeID;
	string agentID;
	string curTime;
	string preNo;
	string transNo;
	string preTrunkNo;
	string transTrunkNo;
	string chargeMode;
private:
	virtual int GetMyMemSize();
};

///Type_Toll_AgentTransP2PTalkEnd
struct SIPCCMsg_Toll_AgentTransP2PTalkEnd : public SIPCCMsg_Toll
{
	SIPCCMsg_Toll_AgentTransP2PTalkEnd();
	~SIPCCMsg_Toll_AgentTransP2PTalkEnd()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	string invokeID;
	string agentID;
	string curTime;
	string preNo;
	string transNo;
	string preTrunkNo;
	string transTrunkNo;
	string chargeMode;
private:
	virtual int GetMyMemSize();
};

///Type_Toll_400CBPreTalkBegin
struct SIPCCMsg_Toll_400CBPreTalkBegin : public SIPCCMsg_Toll
{
	SIPCCMsg_Toll_400CBPreTalkBegin();
	~SIPCCMsg_Toll_400CBPreTalkBegin()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	string invokeID;
	string curTime;
	string callbackNo;
	string managerID;
	string trunkNo;
private:
	virtual int GetMyMemSize();
};

///Type_Toll_400CBPreTalkEnd
struct SIPCCMsg_Toll_400CBPreTalkEnd : public SIPCCMsg_Toll
{
	SIPCCMsg_Toll_400CBPreTalkEnd();
	~SIPCCMsg_Toll_400CBPreTalkEnd()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	string invokeID;
	string curTime;
	string callbackNo;
	string managerID;
	string trunkNo;
private:
	virtual int GetMyMemSize();
};

///Type_Toll_400CBTransTalkBegin
struct SIPCCMsg_Toll_400CBTransTalkBegin : public SIPCCMsg_Toll
{
	SIPCCMsg_Toll_400CBTransTalkBegin();
	~SIPCCMsg_Toll_400CBTransTalkBegin()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	string invokeID;
	string curTime;
	string callbackNo;
	string transNo;
	string managerID;
	string trunkNo;
private:
	virtual int GetMyMemSize();
};

///Type_Toll_400CBTransTalkEnd
struct SIPCCMsg_Toll_400CBTransTalkEnd : public SIPCCMsg_Toll
{
	SIPCCMsg_Toll_400CBTransTalkEnd();
	~SIPCCMsg_Toll_400CBTransTalkEnd()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	string invokeID;
	string curTime;
	string callbackNo;
	string transNo;
	string managerID;
	string trunkNo;
private:
	virtual int GetMyMemSize();
};

///Type_Toll_TollInfo
struct SIPCCMsg_Toll_TollInfo : public SIPCCMsg_Toll
{
	SIPCCMsg_Toll_TollInfo();
	~SIPCCMsg_Toll_TollInfo()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	int InfoType;
	string InvokeId;
	string BeginTime;
	string EndTime;
	string Content1;
	string Content2;

	string sTimeStamp;
private:
	virtual int GetMyMemSize();
};

///Type_Toll_TollInfoAck
struct SIPCCMsg_Toll_TollInfoAck : public SIPCCMsg_Toll
{
	SIPCCMsg_Toll_TollInfoAck();
	~SIPCCMsg_Toll_TollInfoAck()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	int InfoType;
	string InvokeId;

	string sTimeStamp;
private:
	virtual int GetMyMemSize();
};

struct SIPCCMsg_Toll_UniversalInfo : public SIPCCMsg_Toll
{
	SIPCCMsg_Toll_UniversalInfo();
	~SIPCCMsg_Toll_UniversalInfo()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	string m_sInvokeID;
	string m_sCurTime;
	int m_iCallDirection;
	string m_sAgentID;
	string m_sCorpName;
	string m_sFirstNo;
	string m_sFirstTrunkDn;
	string m_sSecondNo;
	string m_sSecondTrunkDn;
	string m_sWanIp;
	string m_sLanIp;
	string m_sPresideTrunkDn;
	string m_sPresidePhoneNo;
	int m_iTollType;
	int m_iTollOperType;
private:
	virtual int GetMyMemSize();
};

//Type_Toll_TollTransation
struct SIPCCMsg_Toll_TollTransation : public SIPCCMsg_Toll
{
	SIPCCMsg_Toll_TollTransation();
	~SIPCCMsg_Toll_TollTransation()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	string transation;
private:
	virtual int GetMyMemSize();
};



///Class_Toll
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
///Class_PhoneSearch
struct SIPCCMsg_PhoneSearch : public SIPCCMessage
{
	SIPCCMsg_PhoneSearch();
	~SIPCCMsg_PhoneSearch()
	{
		ReleaseMemory();
	};
	
	virtual int GetMyMemSize(){return 0;}
	virtual int FillBuf(char*& thebuf){return 0;}
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0){}
	virtual void ReleaseMemory(){};
};

///Type_PhoneSearch_IncomingCall
struct SIPCCMsg_PhoneSearch_IncomingCall : public SIPCCMsg_PhoneSearch
{
	SIPCCMsg_PhoneSearch_IncomingCall();
	~SIPCCMsg_PhoneSearch_IncomingCall()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	string invokeID;
	string trunkNo;
	string callerNo;
	string calledNo;
private:
	virtual int GetMyMemSize();
};

///Type_PhoneSearch_IncomingCallConf
struct SIPCCMsg_PhoneSearch_IncomingCallConf : public SIPCCMsg_PhoneSearch
{
	SIPCCMsg_PhoneSearch_IncomingCallConf();
	~SIPCCMsg_PhoneSearch_IncomingCallConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	string invokeID;
	string trunkNo;
	string managerID;
	char bIsInnerCall;
private:
	virtual int GetMyMemSize();
};

///Type_PhoneSearch_ExtNoInfo
struct SIPCCMsg_PhoneSearch_ExtNoInfo : public SIPCCMsg_PhoneSearch
{
	SIPCCMsg_PhoneSearch_ExtNoInfo();
	~SIPCCMsg_PhoneSearch_ExtNoInfo()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	string invokeID;
	string managerID;
	string extNo;
	string corpName;
	string manageConnectNo;
private:
	virtual int GetMyMemSize();
};

///Type_PhoneSearch_ExtNoInfoConf
struct SIPCCMsg_PhoneSearch_ExtNoInfoConf : public SIPCCMsg_PhoneSearch
{
	SIPCCMsg_PhoneSearch_ExtNoInfoConf();
	~SIPCCMsg_PhoneSearch_ExtNoInfoConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	string invokeID;
	string managerID;
	string realNoList;
	string agentId;
private:
	virtual int GetMyMemSize();
};

///Type_PhoneSearch_400CallIn
struct SIPCCMsg_PhoneSearch_400CallIn : public SIPCCMsg_PhoneSearch
{
	SIPCCMsg_PhoneSearch_400CallIn();
	~SIPCCMsg_PhoneSearch_400CallIn()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	string managerID;
	string callBackPhoneNo;
private:
	virtual int GetMyMemSize();
};

//Type_PhoneSearch_QueryAgentInfoConf
struct SIPCCMsg_PhoneSearch_QueryAgentInfoConf : public SIPCCMsg_PhoneSearch
{
	SIPCCMsg_PhoneSearch_QueryAgentInfoConf();
	~SIPCCMsg_PhoneSearch_QueryAgentInfoConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	string invokeID;
	string agentID;
	string corpDepartName;
private:
	virtual int GetMyMemSize();
};

//Type_PhoneSearch_QueryBlackList
struct SIPCCMsg_PhoneSearch_QueryBlackList : public SIPCCMsg_PhoneSearch
{
	SIPCCMsg_PhoneSearch_QueryBlackList();
	~SIPCCMsg_PhoneSearch_QueryBlackList()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		invokeID = "";
		agentPhoneNo = "";
		extNo = "";
		customerPhoneNo = "";
		managerID = "";
	}
	
	string invokeID;
	string agentPhoneNo;
	string extNo;
	string customerPhoneNo;
	string managerID;
	string managerCalledNo;
private:
	virtual int GetMyMemSize();
};

//Type_PhoneSearch_QueryBlackListConf
struct SIPCCMsg_PhoneSearch_QueryBlackListConf : public SIPCCMsg_PhoneSearch
{
	SIPCCMsg_PhoneSearch_QueryBlackListConf();
	~SIPCCMsg_PhoneSearch_QueryBlackListConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		bBlacklist = 0;
	}
	
	string invokeID;
	char bBlacklist;
private:
	virtual int GetMyMemSize();
};

//Type_PhoneSearch_GetWaitingMusic
struct SIPCCMsg_PhoneSearch_GetWaitingMusic : public SIPCCMsg_PhoneSearch
{
	SIPCCMsg_PhoneSearch_GetWaitingMusic();
	~SIPCCMsg_PhoneSearch_GetWaitingMusic()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		invokeId = "";
		callee = "";
		deptname = "";
	}

	string invokeId;
	string callee;
	string deptname;

private:
	virtual int GetMyMemSize();
};

//Type_PhoneSearch_GetWaitingMusicConf
struct SIPCCMsg_PhoneSearch_GetWaitingMusicConf : public SIPCCMsg_PhoneSearch
{
	SIPCCMsg_PhoneSearch_GetWaitingMusicConf();
	~SIPCCMsg_PhoneSearch_GetWaitingMusicConf()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		invokeId = "";
		musicPath = "";
	}

	string invokeId;
	string musicPath;
private:
	virtual int GetMyMemSize();
};
///Class_PhoneSearch
///////////////////////////////////////////////////////////////////////////

///Type_UState_RingAgentExt
struct SIPCCMsg_UState_RingAgentExt : public SIPCCMsg_UState
{
	SIPCCMsg_UState_RingAgentExt();
	~SIPCCMsg_UState_RingAgentExt()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(agentID!=NULL)	delete agentID;
		agentID = NULL;
		agentIDLen = 0;
		if(uuiData!=NULL)	delete uuiData;
		uuiData = NULL;
		uuiDataLen = 0;
		if(callID!=NULL)	delete callID;
		callID = NULL;
		callIDLen = 0;
		if(corporationName != NULL)	delete corporationName;
		corporationName = NULL;
		corporationNameLen = 0;
	}
	void SetAgentID(string agentid);
	string GetAgentID()
	{
		if(agentIDLen==0)	return "";
		return string(agentID);
	}
	void SetUUIData(string uuidata);
	string GetUUIData()	
	{
		if(uuiDataLen==0)	return "";
		return string(uuiData);
	}
	void SetCallID(string callid);
	string GetCallID()
	{
		if(callIDLen==0)	return "";
		return string(callID);
	}
	void SetCorporationName(string corporationname);
	string GetCorporationName()
	{
		if(corporationNameLen==0)	return "";
		return string(corporationName);
	}
	
	string callerNoForSend;	
	int callerPartyType;
	
	string ipPhoneNo_User;
	char IsOutCall;

	string  managerId;
public:
	string gatewayName;

	string computerSymbol;

private:
	char* agentID;
	int agentIDLen;
	char* uuiData;
	int uuiDataLen;
	char* callID;	//座席过早挂机
	int callIDLen;
	char* corporationName;
	int corporationNameLen;
	virtual int GetMyMemSize();
};

///Type_UState_RingAgentExt2
struct SIPCCMsg_UState_RingAgentExt2 : public SIPCCMsg_UState
{
	SIPCCMsg_UState_RingAgentExt2();
	~SIPCCMsg_UState_RingAgentExt2()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(agentID!=NULL)	delete agentID;
		agentID = NULL;
		agentIDLen = 0;
		if(uuiData!=NULL)	delete uuiData;
		uuiData = NULL;
		uuiDataLen = 0;
		if(callID!=NULL)	delete callID;
		callID = NULL;
		callIDLen = 0;
		if(corporationName != NULL)	delete corporationName;
		corporationName = NULL;
		corporationNameLen = 0;
	}
	void SetAgentID(string agentid);
	string GetAgentID()
	{
		if(agentIDLen==0)	return "";
		return string(agentID);
	}
	void SetUUIData(string uuidata);
	string GetUUIData()	
	{
		if(uuiDataLen==0)	return "";
		return string(uuiData);
	}
	void SetCallID(string callid);
	string GetCallID()
	{
		if(callIDLen==0)	return "";
		return string(callID);
	}
	void SetCorporationName(string corporationname);
	string GetCorporationName()
	{
		if(corporationNameLen==0)	return "";
		return string(corporationName);
	}
	
	string callerNoForSend;	
	int callerPartyType;
	
	string invokeID;
	int usableTime;
	string userName;
	
	unsigned long lanIp;
	unsigned long wanIp;
	
	int outDialType;
	
	string  callTransID;

	string  managerId;
	string gatewayName;

	string computerSymbol;
private:
	char* agentID;
	int agentIDLen;
	char* uuiData;
	int uuiDataLen;
	char* callID;	//座席过早挂机
	int callIDLen;
	char* corporationName;
	int corporationNameLen;
	virtual int GetMyMemSize();
};

///Type_Gateway_RingAgentExtConf
struct SIPCCMsg_Gateway_RingAgentExtConf : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_RingAgentExtConf();
	~SIPCCMsg_Gateway_RingAgentExtConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		ipNo_AgentExt = "";
		agentID = "";
		bCallFailed = 1;
		calledNo = "";
		invokeID = "";
		outDialType = OutDialType_Normal;
		primarySourceIp=0;
		primarySourcePort=0;
	}
	
	int failedCause;
	char bCallFailed;
	string invokeID;
	int outDialType;
	string ipNo_AgentExt;
	string agentID;
	string calledNo;
	
	string CalledAgentID;
	string calledAgentLineNo;
	unsigned long calledAgentLineIp;
	unsigned short calledAgentLinePort;
	
	string  managerId;
	string  connectPhoneNo;



    unsigned long primarySourceIp;		//保存发送信令的softacd构件所在服务器地址PORT 直接转化
    unsigned short primarySourcePort;    

	virtual int GetMyMemSize();
};

///Type_Gateway_RingAgentExtFailed
struct SIPCCMsg_Gateway_RingAgentExtFailed : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_RingAgentExtFailed();
	~SIPCCMsg_Gateway_RingAgentExtFailed()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		ipNo_AgentExt = "";
		agentID = "";
		calledNo = "";
		outDialType = OutDialType_Normal;
	}
	
	int failedCause;
	int outDialType;
	string ipNo_AgentExt;
	string agentID;
	string calledNo;
	
	string  managerId;
	string  connectPhoneNo;
	string  handleId;

	virtual int GetMyMemSize();
};

//Type_Gateway_AgentAnswerCall
struct SIPCCMsg_Gateway_AgentAnswerCall : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_AgentAnswerCall();
	~SIPCCMsg_Gateway_AgentAnswerCall()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		ipNo_AgentExt = "";
		agentID = "";
		outDialType = OutDialType_RingAgentExt;
	}
	
	string ipNo_AgentExt;
	string agentID;
	int outDialType;
	int calledOperType;
	
	string agentLineNo;
	unsigned long agentLineIp;
	unsigned short agentLinePort;
	
	string userLineNo;
	unsigned long userLineIp;
	unsigned short userLinePort;
	
	string wpAgentID;
	
	string  managerId;
	string  connectPhoneNo;
	string  handleId;

	virtual int GetMyMemSize();
};

///Type_Gateway_AgentHangupCall
struct SIPCCMsg_Gateway_AgentHangupCall : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_AgentHangupCall();
	~SIPCCMsg_Gateway_AgentHangupCall()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		ipNo_AgentExt = "";
		agentID = "";
		outDialType = OutDialType_RingAgentExt;
	}
	
	string ipNo_AgentExt;
	string agentID;
	int outDialType;

	string  managerId;
	string  connectPhoneNo;
	string  handleId;

	virtual int GetMyMemSize();
};

struct SIPCCMsg_Gateway_UserHangupCall : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_UserHangupCall();
	~SIPCCMsg_Gateway_UserHangupCall()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		userLineNo = "";
		agentID = "";
		outDialType = OutDialType_RingAgentExt;
	}
	
	string userLineNo;
	string agentID;
	int outDialType;

	string  managerId;
	string  connectPhoneNo;
	string  handleId;

	virtual int GetMyMemSize();
};
///Type_ACD_StopRingAgentExt
struct SIPCCMsg_ACD_StopRingAgentExt : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_StopRingAgentExt();
	~SIPCCMsg_ACD_StopRingAgentExt()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		ipNo_AgentExt = "";
		agentID = "";
		primarySourceIp=0;
		primarySourcePort=0;
	}
	
	string ipNo_AgentExt;
	string agentID;

	string  handleId;
	string  userName;

	 unsigned long primarySourceIp;		//保存发送信令的softacd构件所在服务器地址PORT 有值转化
    unsigned short primarySourcePort;    

     
	virtual int GetMyMemSize();
};

///Type_Gateway_StopRingAgentExtConf
struct SIPCCMsg_Gateway_StopRingAgentExtConf : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_StopRingAgentExtConf();
	~SIPCCMsg_Gateway_StopRingAgentExtConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		ipNo_AgentExt = "";
		agentID = "";
	}
	
	string ipNo_AgentExt;
	string agentID;

	string  managerId;
	string  connectPhoneNo;
	string  handleId;

	virtual int GetMyMemSize();
};

///Type_Gateway_CancelRingAgentExt
struct SIPCCMsg_Gateway_CancelRingAgentExt : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_CancelRingAgentExt();
	~SIPCCMsg_Gateway_CancelRingAgentExt()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		agentID = "";
	}
	
	string agentID;

	string  managerId;
	string  connectPhoneNo;

	virtual int GetMyMemSize();
};

///Type_Wap_CallOut
struct SIPCCMsg_Wap_CallOut : public SIPCCMsg_Wap
{
	SIPCCMsg_Wap_CallOut();
	~SIPCCMsg_Wap_CallOut()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	};
	
	string localPhone;
	string targetPhone;
	int targetType;
	string corpName;
	string deptName;
	string agentId;
	string CallTransID;
	virtual int GetMyMemSize();
};

///Type_Client_WebPSTNDial
struct SIPCCMsg_Client_WebPSTNDial : public SIPCCMsg_Client
{
	SIPCCMsg_Client_WebPSTNDial();
	~SIPCCMsg_Client_WebPSTNDial()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	};
	
	string agentID;
	string corpName;
	string agentPhoneNo;
	string userPhoneNo;
	string deptName;
	string managerDialNo;
	string CallTransID;
	string managerId;
	string computerSymbol;
	char NeedReturnClient;
	string handleId;		//操作唯一标识
	string userData;		//WebService   标识 picc userData 不空的+WebService
	virtual int GetMyMemSize();
};

///Type_ACD_AddCorpNDeptInfo
struct SIPCCMsg_ACD_AddCorpNDeptInfo : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_AddCorpNDeptInfo();
	~SIPCCMsg_ACD_AddCorpNDeptInfo()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	};
	
	string corpName;
	string deptName;
	virtual int GetMyMemSize();
};

///Type_Toll_SMS
struct SIPCCMsg_Toll_SMS : public SIPCCMsg_Toll
{
	SIPCCMsg_Toll_SMS();
	~SIPCCMsg_Toll_SMS()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	};
	
	string invokeId;
	string managerId;
	int sendCount;
	virtual int GetMyMemSize();
};

///Type_Toll_SMSAck
struct SIPCCMsg_Toll_SMSAck : public SIPCCMsg_Toll
{
	SIPCCMsg_Toll_SMSAck();
	~SIPCCMsg_Toll_SMSAck()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	};
	
	string invokeId;
	virtual int GetMyMemSize();
};

///Type_Gateway_UnAnsweredCall
struct SIPCCMsg_Gateway_UnAnsweredCall : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_UnAnsweredCall();
	~SIPCCMsg_Gateway_UnAnsweredCall()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	};
	
	string manageId;
	string corpName;
	string key;
	string extNo;
	string customerNo;
	string time;
	string calledNo;
	string sessionID;
	string hangupTime;
	string invokeId;
	virtual int GetMyMemSize();
};

///Type_ACD_SetClientAgentState
struct SIPCCMsg_ACD_SetClientAgentState : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_SetClientAgentState();
	~SIPCCMsg_ACD_SetClientAgentState()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	};
	
	int agentState;
	string gwAgentLine;
	string gwUserLine;
	string transedAgentID;
	string transedGwAgentLine;
	
	unsigned long gwAgentLineIp;
	unsigned short gwAgentLinePort;
	unsigned long gwUserLineIp;
	unsigned short gwUserLinePort;
	
	int operType;
	
	virtual int GetMyMemSize();	
};

///Type_Client_WebPSTNAgentHoldCall
struct SIPCCMsg_Client_WebPSTNAgentHoldCall : public SIPCCMsg_Client
{
	SIPCCMsg_Client_WebPSTNAgentHoldCall();
	~SIPCCMsg_Client_WebPSTNAgentHoldCall()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	};
	
	string agentID;
	string gwAgentLine;
	string gwUserLine;
	
	virtual int GetMyMemSize();	
};

///Type_Client_WebPSTNAgentUnHoldCall
struct SIPCCMsg_Client_WebPSTNAgentUnHoldCall : public SIPCCMsg_Client
{
	SIPCCMsg_Client_WebPSTNAgentUnHoldCall();
	~SIPCCMsg_Client_WebPSTNAgentUnHoldCall()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	};
	
	string agentID;
	string gwAgentLine;
	string gwUserLine;
	
	virtual int GetMyMemSize();	
};

///Type_UState_WebPSTNAgentHoldCall
struct SIPCCMsg_UState_WebPSTNAgentHoldCall : public SIPCCMsg_UState
{
	SIPCCMsg_UState_WebPSTNAgentHoldCall();
	~SIPCCMsg_UState_WebPSTNAgentHoldCall()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	};
	
	string agentID;
	string gwAgentLine;
	string gwUserLine;
public:
	string gatewayName;

	string computerSymbol;
	string handleId;
	
	virtual int GetMyMemSize();	
};

///Type_UState_WebPSTNAgentUnHoldCall
struct SIPCCMsg_UState_WebPSTNAgentUnHoldCall : public SIPCCMsg_UState
{
	SIPCCMsg_UState_WebPSTNAgentUnHoldCall();
	~SIPCCMsg_UState_WebPSTNAgentUnHoldCall()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	};
	
	string agentID;
	string gwAgentLine;
	string gwUserLine;
	
	virtual int GetMyMemSize();	

public:
	string gatewayName;
	string computerSymbol;
};

///Type_UState_WebPSTNAgentHoldCallConf
struct SIPCCMsg_UState_WebPSTNAgentHoldCallConf : public SIPCCMsg_UState
{
	SIPCCMsg_UState_WebPSTNAgentHoldCallConf();
	~SIPCCMsg_UState_WebPSTNAgentHoldCallConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	};
	
	char bHoldSucc;
public:
	string gatewayName;
	string computerSymbol;
	string handleId;

	virtual int GetMyMemSize();	
};

///Type_ACD_CallAnswered_WebPstnAgent
struct SIPCCMsg_ACD_CallAnswered_WebPstnAgent : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_CallAnswered_WebPstnAgent();
	~SIPCCMsg_ACD_CallAnswered_WebPstnAgent()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	};
	
	string gwAgentLine;
	string otherAgentID;
	
	virtual int GetMyMemSize();	
};

///Type_Client_WpAgentTrans2VoipAgent
struct SIPCCMsg_Client_WpAgentTrans2VoipAgent : public SIPCCMsg_Client
{
	SIPCCMsg_Client_WpAgentTrans2VoipAgent();
	~SIPCCMsg_Client_WpAgentTrans2VoipAgent()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
public:
	int otherPartyType;
	string theParty;
	string presideAgent;
	string otherParty;
	string wpAgentLineNo;
	
	virtual int GetMyMemSize();
};

///Type_UState_WpAgentTrans2VoipAgent
struct SIPCCMsg_UState_WpAgentTrans2VoipAgent : public SIPCCMsg_UState
{
	SIPCCMsg_UState_WpAgentTrans2VoipAgent();
	~SIPCCMsg_UState_WpAgentTrans2VoipAgent()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
public:
	int otherPartyType;
	string theParty;
	string presideAgent;
	string otherParty;
	string wpAgentLineNo;

	string gatewayName;
	string computerSymbol;

	virtual int GetMyMemSize();
};

///Type_ACD_CallReleased_WpAgent
struct SIPCCMsg_ACD_CallReleased_WpAgent : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_CallReleased_WpAgent();
	~SIPCCMsg_ACD_CallReleased_WpAgent()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
public:
	string userLineNo;
	string agentLineNo;

	string  handleId;
	
	virtual int GetMyMemSize();
};

///Type_Gateway_CallAgentConf, 其他座席呼叫 wpAgent 确认，通知 wpAgent的 lineNo/IP/Port 等信息
struct SIPCCMsg_Gateway_CallAgentConf : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_CallAgentConf();
	~SIPCCMsg_Gateway_CallAgentConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
public:
	char bCallFailed;
	string invokeID;
	string calledNo;
	string originAgentID;
	string CalledAgentID;
	string originAgentLineNo;
	string calledAgentLineNo;
	unsigned long originAgentIp;
	unsigned short originAgentPort;
	unsigned long calledAgentLineIp;
	unsigned short calledAgentLinePort;

	string  managerId;
	string  connectPhoneNo;
	
	virtual int GetMyMemSize();
};

///Type_ACD_RingWpAgentExtFailed
struct SIPCCMsg_ACD_RingWpAgentExtFailed : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_RingWpAgentExtFailed();
	~SIPCCMsg_ACD_RingWpAgentExtFailed()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	virtual int GetMyMemSize();
};

///Type_Gateway_CallAgentFailed, 其他座席呼叫wpAgent 硬话机失败
struct SIPCCMsg_Gateway_CallAgentFailed : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_CallAgentFailed();
	~SIPCCMsg_Gateway_CallAgentFailed()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
public:
	char bCallFailed;
	string calledNo;
	string originAgentID;
	string CalledAgentID;
	string originAgentLineNo;
	string calledAgentLineNo;
	unsigned long originAgentIp;
	unsigned short originAgentPort;
	unsigned long calledAgentLineIp;
	unsigned short calledAgentLinePort;
	int failedCause;
	
	string  managerId;
	string  connectPhoneNo;
	string  handleId;

	virtual int GetMyMemSize();
};

///Type_ACD_CallWpAgentConf
struct SIPCCMsg_ACD_CallWpAgentConf : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_CallWpAgentConf();
	~SIPCCMsg_ACD_CallWpAgentConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
public:
	char bCallFailed;
	string invokeID;
	string wpAgentID;
	string wpAgentLineNo;
	unsigned long wpAgentLineIp;
	unsigned short wpAgentLinePort;
	unsigned long lanIp;
	
	virtual int GetMyMemSize();
};

struct SIPCCMsg_ACD_TransferCall_WpAgent : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_TransferCall_WpAgent();
	~SIPCCMsg_ACD_TransferCall_WpAgent()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(presideAgent!=NULL)	delete presideAgent;	
		presideAgent = NULL;
		presideAgentLen = 0;
		if(otherParty!=NULL)	delete otherParty;	
		otherParty = NULL;
		otherPartyLen = 0;
	}
	
	void SetPresideAgent(string presideagent);
	string GetPresideAgent()
	{
		if(presideAgentLen == 0)			return "";
		return string(presideAgent);
	}
	void SetOtherParty(string otherparty);
	string GetOtherParty()
	{
		if(otherPartyLen == 0)			return "";
		return string(otherParty);
	}
public:
	int otherPartyType;
	char* presideAgent;
	int presideAgentLen;
	char* otherParty;
	int otherPartyLen;
	string wpAgentID;
	string wpAgentLineNo;
	
	virtual int GetMyMemSize();
};

struct SIPCCMsg_ACD_BeforeTransferCall_WpAgent : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_BeforeTransferCall_WpAgent();
	~SIPCCMsg_ACD_BeforeTransferCall_WpAgent()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(presideAgent!=NULL)	delete presideAgent;	
		presideAgent = NULL;
		presideAgentLen = 0;
		if(otherParty!=NULL)	delete otherParty;	
		otherParty = NULL;
		otherPartyLen = 0;
	}
	
	void SetPresideAgent(string presideagent);
	string GetPresideAgent()
	{
		if(presideAgentLen == 0)			return "";
		return string(presideAgent);
	}
	void SetOtherParty(string otherparty);
	string GetOtherParty()
	{
		if(otherPartyLen == 0)			return "";
		return string(otherParty);
	}
public:
	int otherPartyType;
	char* presideAgent;
	int presideAgentLen;
	char* otherParty;
	int otherPartyLen;
	string wpAgentID;
	string wpAgentLineNo;
	
	virtual int GetMyMemSize();
};

///Type_ACD_CallWpAgentExtFailed
struct SIPCCMsg_ACD_CallWpAgentExtFailed : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_CallWpAgentExtFailed();
	~SIPCCMsg_ACD_CallWpAgentExtFailed()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
public:
	string wpAgentID;
	
	virtual int GetMyMemSize();
};

///Type_PhoneSearch_QueryTestKeyword
struct SIPCCMsg_PhoneSearch_QueryTestKeyword : public SIPCCMsg_PhoneSearch
{
	SIPCCMsg_PhoneSearch_QueryTestKeyword();
	~SIPCCMsg_PhoneSearch_QueryTestKeyword()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
public:
	string managerSign;
	string invokeId;
	
	virtual int GetMyMemSize();
};

///Type_PhoneSearch_QueryTestKeywordConf
struct SIPCCMsg_PhoneSearch_QueryTestKeywordConf : public SIPCCMsg_PhoneSearch
{
	SIPCCMsg_PhoneSearch_QueryTestKeywordConf();
	~SIPCCMsg_PhoneSearch_QueryTestKeywordConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
public:
	string testKeyWord;
	string invokeId;
	
	virtual int GetMyMemSize();
};

///Type_Gateway_CallCleared
struct SIPCCMsg_Gateway_CallCleared : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_CallCleared();
	~SIPCCMsg_Gateway_CallCleared()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
public:
	string userLineNo;
	string agentid;
	
	virtual int GetMyMemSize();
};

//Type_Client_EchoRemoveCtrl
struct SIPCCMsg_Client_EchoRemoveCtrl : public SIPCCMsg_Client
{
	SIPCCMsg_Client_EchoRemoveCtrl();
	~SIPCCMsg_Client_EchoRemoveCtrl()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};
	
	string gwLineNo;
	char allow;
private:
	virtual int GetMyMemSize();
};

//Type_UState_EchoRemoveCtrl
struct SIPCCMsg_UState_EchoRemoveCtrl : public SIPCCMsg_UState
{
	SIPCCMsg_UState_EchoRemoveCtrl();
	~SIPCCMsg_UState_EchoRemoveCtrl()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};
	
	string gwLineNo;
	char allow;
public:
	string gatewayName;

	string computerSymbol;
private:
	virtual int GetMyMemSize();
};

///Type_PhoneSearch_QueryManagerId
struct SIPCCMsg_PhoneSearch_QueryManagerId : public SIPCCMsg_PhoneSearch
{
	SIPCCMsg_PhoneSearch_QueryManagerId();
	~SIPCCMsg_PhoneSearch_QueryManagerId()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
public:
	string managerSign;
	string telephone_Real;
	string invokeId;
	
	virtual int GetMyMemSize();
};

///Type_PhoneSearch_QueryManagerIdConf
struct SIPCCMsg_PhoneSearch_QueryManagerIdConf : public SIPCCMsg_PhoneSearch
{
	SIPCCMsg_PhoneSearch_QueryManagerIdConf();
	~SIPCCMsg_PhoneSearch_QueryManagerIdConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
public:
	string managerId;
	string invokeId;
	
	virtual int GetMyMemSize();
};

//////////////////////////////////////////////////////////////////////////
///Class_DataRoute
struct SIPCCMsg_DataRoute : public SIPCCMessage
{
	SIPCCMsg_DataRoute() {	msgClass = Class_DataRoute;	}
	~SIPCCMsg_DataRoute()
	{
		ReleaseMemory();
	};
	
	virtual int GetMyMemSize(){return 0;}
	virtual int FillBuf(char*& thebuf){return 0;}
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0){}
	virtual void ReleaseMemory(){}
};

///Type_DataRoute_QueryTransServerConf
struct SIPCCMsg_DataRoute_QueryTransServerConf : public SIPCCMsg_DataRoute
{
	SIPCCMsg_DataRoute_QueryTransServerConf() {	msgType = Type_DataRoute_QueryTransServerConf;	}
	~SIPCCMsg_DataRoute_QueryTransServerConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
public:
	char bQuerySucc;
	unsigned long dataTransIP;
	unsigned short dataTransPort;
private:
	virtual int GetMyMemSize();
};
//////////////////////////////////////////////////////////////////////////
///Class_DataTrans
struct SIPCCMsg_DataTrans : public SIPCCMessage
{
	SIPCCMsg_DataTrans() {	msgClass = Class_DataTrans;	}
	~SIPCCMsg_DataTrans()
	{
		ReleaseMemory();
	};
	
	virtual int GetMyMemSize(){return 0;}
	virtual int FillBuf(char*& thebuf){return 0;}
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0){}
	virtual void ReleaseMemory(){}
};

///Type_DataTrans_Register
struct SIPCCMsg_DataTrans_Register : public SIPCCMsg_DataTrans
{
	SIPCCMsg_DataTrans_Register() {	msgType = Type_DataTrans_Register;	}
	~SIPCCMsg_DataTrans_Register()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
public:
	unsigned long dataTransIP;
	int type;		//备用
	int capacity;
	
private:
	virtual int GetMyMemSize();
};

//Type_DataTrans_UnRegister
struct SIPCCMsg_DataTrans_UnRegister : public SIPCCMsg_DataTrans
{
	SIPCCMsg_DataTrans_UnRegister() {	msgType = Type_DataTrans_UnRegister;	}
	~SIPCCMsg_DataTrans_UnRegister()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
public:
	unsigned long dataTransIP;
private:
	virtual int GetMyMemSize();
};

///Type_DataTrans_StartTrans
struct SIPCCMsg_DataTrans_StartTrans : public SIPCCMsg_DataTrans
{
	SIPCCMsg_DataTrans_StartTrans();
	~SIPCCMsg_DataTrans_StartTrans()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
public:
	string agentId;
	unsigned long gwLineIp;
	unsigned short gwLinePort;
	
	virtual int GetMyMemSize();
};

///Type_DataTrans_StartTransConf
struct SIPCCMsg_DataTrans_StartTransConf : public SIPCCMsg_DataTrans
{
	SIPCCMsg_DataTrans_StartTransConf();
	~SIPCCMsg_DataTrans_StartTransConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
public:
	int channelIndex;
	unsigned short port;
	
	virtual int GetMyMemSize();
};

///Type_DataTrans_StopTrans
struct SIPCCMsg_DataTrans_StopTrans : public SIPCCMsg_DataTrans
{
	SIPCCMsg_DataTrans_StopTrans();
	~SIPCCMsg_DataTrans_StopTrans()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
public:
	int channelIndex;
	
	virtual int GetMyMemSize();
};

struct SIPCCMsg_Client_GetTalkingAgent : public SIPCCMsg_Client
{
	SIPCCMsg_Client_GetTalkingAgent();
	~SIPCCMsg_Client_GetTalkingAgent()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
public:
	string Group;
	string invokeID;
	
	virtual int GetMyMemSize();
};

struct SIPCCMsg_ACD_GetTalkingAgentConf : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_GetTalkingAgentConf();
	~SIPCCMsg_ACD_GetTalkingAgentConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
public:
	string theList;
	char bEnd;
	string invokeID;
	
	virtual int GetMyMemSize();
};

struct SIPCCMsg_Client_MonitRequest : public SIPCCMsg_Client
{
	SIPCCMsg_Client_MonitRequest();
	~SIPCCMsg_Client_MonitRequest()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
public:
	unsigned long ip;
	unsigned short port;
	string agentName;
	
	string agentName_Src;
	string agentName_Dest;
	
	virtual int GetMyMemSize();
};

struct SIPCCMsg_Client_MonitRequestConf : public SIPCCMsg_Client
{
	SIPCCMsg_Client_MonitRequestConf();
	~SIPCCMsg_Client_MonitRequestConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
public:
	char bAllow;
	//	unsigned long ip;
	//	unsigned short port;
	string agentName_Src;
	string agentName_Dest;
	char bSucc;
	string CallId;
	
	virtual int GetMyMemSize();
};

struct SIPCCMsg_Client_StopMonit : public SIPCCMsg_Client
{
	SIPCCMsg_Client_StopMonit();
	~SIPCCMsg_Client_StopMonit()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
public:
	string agentName;
	
	string agentName_Src;
	string agentName_Dest;
	string trunkDn;
	
	virtual int GetMyMemSize();
};
// begin---libh 2007/12/28
struct SIPCCMsg_Gateway_GetDeptQueueNum : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_GetDeptQueueNum();
	~SIPCCMsg_Gateway_GetDeptQueueNum()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
public:
	string invokeId;
	string m_ssDeptName;
	string m_ssCorpName;
	
	string  connectPhoneNo;
	string  handleId;

	virtual int GetMyMemSize();
};

struct SIPCCMsg_ACD_GetDeptQueueNumConf : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_GetDeptQueueNumConf();
	~SIPCCMsg_ACD_GetDeptQueueNumConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
public:
	string invokeId;
	string m_ssDeptName;
	unsigned short m_uCount;

	string  handleId;
	
	virtual int GetMyMemSize();
};

struct SIPCCMsg_Gateway_GetAgentState : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_GetAgentState();
	~SIPCCMsg_Gateway_GetAgentState()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
public:
	string invokeId;
	string m_ssAgentName;
	
	string  connectPhoneNo;
	string  handleId;

	virtual int GetMyMemSize();
};

struct SIPCCMsg_ACD_GetAgentStateConf : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_GetAgentStateConf();
	~SIPCCMsg_ACD_GetAgentStateConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
public:
	string invokeId;
	string m_ssAgentName;
	string m_ssState;

	string  handleId;
	
	virtual int GetMyMemSize();
};
// end---libh 2007/12/28
//////////////////////////////////////////////////////////////////////////
///  Class_Alert
struct SIPCCMsg_Alert : public SIPCCMessage
{
	SIPCCMsg_Alert()
	{
		this->msgClass = Class_Alert;
	}
	~SIPCCMsg_Alert()
	{
		ReleaseMemory();
	};
	
	virtual int GetMyMemSize(){return 0;}
	virtual int FillBuf(char*& thebuf){return 0;}
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0){}
	virtual void ReleaseMemory(){}
};

struct SIPCCMsg_Alert_NotifyInfo : public SIPCCMsg_Alert
{
	SIPCCMsg_Alert_NotifyInfo();
	~SIPCCMsg_Alert_NotifyInfo()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){}
	
public:
	int notifyType;					//报警类型：录音硬盘告警
	string notifyDescription;		//报警描述
	int notifyMode;					//报警模式：电话
	string notifyInfo;				//相关信息：如电话号码，以 | 分隔
	
	
	virtual int GetMyMemSize();
};

///Type_Gateway_GetGetwayInfo
struct SIPCCMsg_Gateway_GetGetwayInfo : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_GetGetwayInfo();
	~SIPCCMsg_Gateway_GetGetwayInfo()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
private:
	virtual int GetMyMemSize();
};

///Type_Gateway_GetGetwayInfoConf
struct SIPCCMsg_Gateway_GetGetwayInfoConf : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_GetGetwayInfoConf();
	~SIPCCMsg_Gateway_GetGetwayInfoConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	string GetwayInfoString;
private:
	virtual int GetMyMemSize();
};

///Type_Gateway_AddRecordForTH
struct SIPCCMsg_Gateway_AddRecordForTH : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_AddRecordForTH();
	~SIPCCMsg_Gateway_AddRecordForTH()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	string phoneNo;
private:
	virtual int GetMyMemSize();
};

///Type_Gateway_DelRecordForTH
struct SIPCCMsg_Gateway_DelRecordForTH : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_DelRecordForTH();
	~SIPCCMsg_Gateway_DelRecordForTH()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	string phoneNo;
private:
	virtual int GetMyMemSize();
};

///Type_Gateway_DelAllRecordForTH
struct SIPCCMsg_Gateway_DelAllRecordForTH : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_DelAllRecordForTH();
	~SIPCCMsg_Gateway_DelAllRecordForTH()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	string phoneNo;
private:
	virtual int GetMyMemSize();
};

struct SIPCCMsg_ACD_MonitRequest : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_MonitRequest();
	~SIPCCMsg_ACD_MonitRequest()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
public:
	string agentName_Src;
	string agentName_Dest;
	string trunkDn;
	
	virtual int GetMyMemSize();
};

struct SIPCCMsg_ACD_MonitRequestConf : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_MonitRequestConf();
	~SIPCCMsg_ACD_MonitRequestConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
public:
	string agentName_Src;
	string agentName_Dest;
	char bSucc;
	string trunkDn;
	string CallId;
	unsigned long ip;
	unsigned short port;
	
	virtual int GetMyMemSize();
};

struct SIPCCMsg_Client_MediaRequest_Monit : public SIPCCMsg_Client
{
	SIPCCMsg_Client_MediaRequest_Monit();
	~SIPCCMsg_Client_MediaRequest_Monit()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
public:
	string agentName_Src;
	string agentName_Dest;
	int seq;
	
	virtual int GetMyMemSize();
};

struct SIPCCMsg_ACD_MediaRequest_Monit : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_MediaRequest_Monit();
	~SIPCCMsg_ACD_MediaRequest_Monit()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
public:
	string agentName_Src;
	string agentName_Dest;
	int seq;
	
	virtual int GetMyMemSize();
};

struct SIPCCMsg_Client_MediaReady_Monit : public SIPCCMsg_Client
{
	SIPCCMsg_Client_MediaReady_Monit();
	~SIPCCMsg_Client_MediaReady_Monit()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
public:
	string agentName_Src;
	string agentName_Dest;
	
	virtual int GetMyMemSize();
};

struct SIPCCMsg_ACD_MediaReady_Monit : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_MediaReady_Monit();
	~SIPCCMsg_ACD_MediaReady_Monit()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
public:
	string agentName_Src;
	string agentName_Dest;
	
	virtual int GetMyMemSize();
};

struct SIPCCMsg_ACD_StopMonit : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_StopMonit();
	~SIPCCMsg_ACD_StopMonit()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
public:
	string agentName_Src;
	string agentName_Dest;
	string trunkDn;
	
	virtual int GetMyMemSize();
};

struct SIPCCMsg_DataRoute_QueryTransServer_IP : public SIPCCMsg_DataRoute
{
	SIPCCMsg_DataRoute_QueryTransServer_IP();
	~SIPCCMsg_DataRoute_QueryTransServer_IP()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
public:
	string callId;
	
	virtual int GetMyMemSize();
};

struct SIPCCMsg_DataRoute_QueryTransServerConf_IP : public SIPCCMsg_DataRoute
{
	SIPCCMsg_DataRoute_QueryTransServerConf_IP();
	~SIPCCMsg_DataRoute_QueryTransServerConf_IP()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
public:
	string callId;
	unsigned long transServerIp;
	unsigned short transServerPort;
	
	virtual int GetMyMemSize();
};

struct SIPCCMsg_DataTrans_StartTrans_IP : public SIPCCMsg_DataTrans
{
	SIPCCMsg_DataTrans_StartTrans_IP();
	~SIPCCMsg_DataTrans_StartTrans_IP()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
public:
	string callId;
	
	virtual int GetMyMemSize();
};

struct SIPCCMsg_DataTrans_StartTransConf_IP : public SIPCCMsg_DataTrans
{
	SIPCCMsg_DataTrans_StartTransConf_IP();
	~SIPCCMsg_DataTrans_StartTransConf_IP()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
public:
	string callId;
	int channelIndex;
	unsigned short port;
	
	virtual int GetMyMemSize();
};

struct SIPCCMsg_DataTrans_StopTrans_IP : public SIPCCMsg_DataTrans
{
	SIPCCMsg_DataTrans_StopTrans_IP();
	~SIPCCMsg_DataTrans_StopTrans_IP()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
public:
	string callId;
	int channelIndex;
	
	virtual int GetMyMemSize();
};

struct SIPCCMsg_Gateway_GetDeptWaitingAgentNum : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_GetDeptWaitingAgentNum();
	~SIPCCMsg_Gateway_GetDeptWaitingAgentNum()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
public:
	string invokeId;
	string m_ssDeptName;
	string m_ssCorpName;
	
	string  connectPhoneNo;
	string  handleId;

	virtual int GetMyMemSize();
};

struct SIPCCMsg_ACD_GetDeptWaitingAgentNumConf : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_GetDeptWaitingAgentNumConf();
	~SIPCCMsg_ACD_GetDeptWaitingAgentNumConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
public:
	string invokeId;
	unsigned short  m_uCount;

	string  handleId;
	
	virtual int GetMyMemSize();
};

struct SIPCCMsg_Client_SendDtmf : public SIPCCMsg_Client
{
	SIPCCMsg_Client_SendDtmf();
	~SIPCCMsg_Client_SendDtmf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
public:
	char dtmf;
	int seq;
	
	virtual int GetMyMemSize();
};

struct SIPCCMsg_Client_ReceiveDtmf : public SIPCCMsg_Client
{
	SIPCCMsg_Client_ReceiveDtmf();
	~SIPCCMsg_Client_ReceiveDtmf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
public:
	int seq;
	int count;
	
	virtual int GetMyMemSize();
};
struct SIPCCMsg_ACD_DelDepartment : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_DelDepartment();
	~SIPCCMsg_ACD_DelDepartment()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
public:
	string corpName;
	string deptName;
	
	virtual int GetMyMemSize();
};

struct SIPCCMsg_Client_GetTrunkCount : public SIPCCMsg_Client
{
	SIPCCMsg_Client_GetTrunkCount();
	~SIPCCMsg_Client_GetTrunkCount()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	string invokeID;
	
public:
	
	virtual int GetMyMemSize();
};

struct SIPCCMsg_Gateway_GetTrunkCountConf : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_GetTrunkCountConf();
	~SIPCCMsg_Gateway_GetTrunkCountConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
public:
	int count;
	int free;
	
	virtual int GetMyMemSize();
};

struct SIPCCMsg_ACD_SetTalkSpan : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_SetTalkSpan();
	~SIPCCMsg_ACD_SetTalkSpan()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
public:
	string dept;
	int span;
	int caseId;
	
	virtual int GetMyMemSize();
};

struct SIPCCMsg_ACD_SetAgentCount : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_SetAgentCount();
	~SIPCCMsg_ACD_SetAgentCount()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
public:
	string dept;
	int count;
	int free;
	string callLen;
	
	virtual int GetMyMemSize();
};

struct SIPCCMsg_Client_SetOutDialResult : public SIPCCMsg_Client
{
	SIPCCMsg_Client_SetOutDialResult();
	~SIPCCMsg_Client_SetOutDialResult()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
public:
	string tag;
	int result;
	string dailTime;
	
	virtual int GetMyMemSize();
};

struct SIPCCMsg_Client_SetOutdialCase : public SIPCCMsg_Client
{
	SIPCCMsg_Client_SetOutdialCase();
	~SIPCCMsg_Client_SetOutdialCase()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
public:
	string corp;
	string dept;
	string agent;
	int talkNProcessSpan;
	int caseId;
	
	virtual int GetMyMemSize();
};
// 开始 [3/2/2009 lixg]
struct SIPCCMsg_Client_SendStrMsg:public SIPCCMsg_Client
{
	SIPCCMsg_Client_SendStrMsg()
	{
		msgType = Type_Client_SendStrMsg;
		destAgents = "";
		msgContent = "";
		theSender = "";
	}
	~SIPCCMsg_Client_SendStrMsg()
	{
		ReleaseMemory();
	}
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
public:
	string destAgents;	// 格式 1@1.com|1@2.com|...
	string msgContent;
	string theSender;
	
	virtual int GetMyMemSize()
	{
		int memSize = 2*sizeof(int);	// msgclass+msgtype
		memSize += destAgents.length() + 1;	// destAgents	
		memSize += msgContent.length() + 1;	// msgContent	
		memSize += theSender.length() + 1;	// theSender
		
		return memSize;
	}
};
struct SIPCCMsg_ACD_SendStrMsg:public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_SendStrMsg()
	{
		msgType = Type_ACD_SendStrMsg;
		msgContent = "";
		theSender = "";
	}
	~SIPCCMsg_ACD_SendStrMsg()
	{
		ReleaseMemory();
	}
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
public:
	string msgContent;
	string theSender;
	
	virtual int GetMyMemSize()
	{
		int memSize = 2*sizeof(int);	// msgclass+msgtype
		memSize += msgContent.length() + 1;	// msgContent	
		memSize += theSender.length() + 1;	// theSender
		
		return memSize;
	}
};
// 结束 [3/2/2009 lixg]
struct SIPCCMsg_Gateway_GetDeptOverflow : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_GetDeptOverflow();
	~SIPCCMsg_Gateway_GetDeptOverflow()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
public:
	string invokeId;
	string m_ssDeptName;
	string m_ssCorpName;
	
	string  connectPhoneNo;
	string  handleId;

	virtual int GetMyMemSize();
};

struct SIPCCMsg_ACD_GetDeptOverflowConf : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_GetDeptOverflowConf();
	~SIPCCMsg_ACD_GetDeptOverflowConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
public:
	string invokeId;
	int timeoutValue;		//溢出超时时限
	string overFlowDest;	//溢出目的地
	int overFlowDestType;	//溢出类型(0:技能组 1:手机群 2:IVR 3:分机 4:指定电话)

	string  handleId;
	
	virtual int GetMyMemSize();
};

// begin---yany 2008/11/20
///Type_PhoneSearch_QueryDelieverNo
struct SIPCCMsg_PhoneSearch_QueryDelieverNo : public SIPCCMsg_PhoneSearch
{
	SIPCCMsg_PhoneSearch_QueryDelieverNo();
	~SIPCCMsg_PhoneSearch_QueryDelieverNo()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
public:
	string managerId;
	string computerSymbol;
	string invokeId;
	
	virtual int GetMyMemSize();
};

///Type_PhoneSearch_QueryDelieverNoConf
struct SIPCCMsg_PhoneSearch_QueryDelieverNoConf : public SIPCCMsg_PhoneSearch
{
	SIPCCMsg_PhoneSearch_QueryDelieverNoConf();
	~SIPCCMsg_PhoneSearch_QueryDelieverNoConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
public:
	string connectPhoneNo;
	string invokeId;
	
	virtual int GetMyMemSize();
};
// end---yany 2008/11/20

// begin---yany 2009/09/01
///Type_PhoneSearch_GetCallTarget
struct SIPCCMsg_PhoneSearch_GetCallTarget : public SIPCCMsg_PhoneSearch
{
	SIPCCMsg_PhoneSearch_GetCallTarget();
	~SIPCCMsg_PhoneSearch_GetCallTarget()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
public:
	string managerId;
	string caller;
	string callee;
	string invokeId;
	
	virtual int GetMyMemSize();
};

///Type_PhoneSearch_GetCallTargetConf
struct SIPCCMsg_PhoneSearch_GetCallTargetConf : public SIPCCMsg_PhoneSearch
{
	SIPCCMsg_PhoneSearch_GetCallTargetConf();
	~SIPCCMsg_PhoneSearch_GetCallTargetConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
public:
	string keyword;
	string invokeId;
	
	virtual int GetMyMemSize();
};
// end---yany 2009/09/01

///////////////////////////////////////////////////////////////////////////
///Class_OutDial
struct SIPCCMsg_OutDial : public SIPCCMessage
{
	SIPCCMsg_OutDial(){msgClass = Class_OutDial;};
	~SIPCCMsg_OutDial()
	{
		ReleaseMemory();
	};
	
	virtual int GetMyMemSize(){return 0;}
	virtual int FillBuf(char*& thebuf){return 0;}
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0){}
	virtual void ReleaseMemory(){}
};

///Type_OutDial_SetAgentCount
struct SIPCCMsg_OutDial_SetAgentCount : public SIPCCMsg_OutDial
{
	SIPCCMsg_OutDial_SetAgentCount();
	~SIPCCMsg_OutDial_SetAgentCount()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
public:
	int GroupId;
	string GroupName;
	int WorkAgentCount;
	int FreeAgentCount;
	
	virtual int GetMyMemSize();
};

///Type_OutDial_DialCmd
struct SIPCCMsg_OutDial_DialCmd : public SIPCCMsg_OutDial
{
	SIPCCMsg_OutDial_DialCmd();
	~SIPCCMsg_OutDial_DialCmd()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
public:
	int TaskId;
	int PhoneId;
	int DialSeq;
	string CalleeNum;
	string CallerForSend;
	string TransDest;
	string UuiData_Task;
	string UuiData_Phone;
	string Url;
	string UuiData_managerid;
	
	virtual int GetMyMemSize();
};

///Type_OutDial_DialResult
struct SIPCCMsg_OutDial_DialResult : public SIPCCMsg_OutDial
{
	SIPCCMsg_OutDial_DialResult();
	~SIPCCMsg_OutDial_DialResult()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
public:
	int TaskId;
	int PhoneId;
	int DialSeq;
	char IsSucc;
	int ResultCode;
	string InvokeId;
	
	virtual int GetMyMemSize();
};

///Type_OutDial_AnalyzeResult
struct SIPCCMsg_OutDial_AnalyzeResult : public SIPCCMsg_OutDial
{
	SIPCCMsg_OutDial_AnalyzeResult();
	~SIPCCMsg_OutDial_AnalyzeResult()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
public:
	int TaskId;
	int PhoneId;
	int DialSeq;
	int ResultCode;
	
	virtual int GetMyMemSize();
};

///Type_OutDial_TransResult
struct SIPCCMsg_OutDial_TransResult : public SIPCCMsg_OutDial
{
	SIPCCMsg_OutDial_TransResult();
	~SIPCCMsg_OutDial_TransResult()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
public:
	int TaskId;
	int PhoneId;
	int DialSeq;
	char IsSucc;
	string AgentName;
	
	virtual int GetMyMemSize();
};

///Type_OutDial_EndTalk
struct SIPCCMsg_OutDial_EndTalk : public SIPCCMsg_OutDial
{
	SIPCCMsg_OutDial_EndTalk();
	~SIPCCMsg_OutDial_EndTalk()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
public:
	int TaskId;
	int PhoneId;
	int DialSeq;
	string AgentName;
	
	virtual int GetMyMemSize();
};

///Type_OutDial_EndProcess
struct SIPCCMsg_OutDial_EndProcess : public SIPCCMsg_OutDial
{
	SIPCCMsg_OutDial_EndProcess();
	~SIPCCMsg_OutDial_EndProcess()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
public:
	int TaskId;
	int PhoneId;
	int DialSeq;
	string AgentName;
	
	virtual int GetMyMemSize();
};

///Type_OutDial_GwLineSynchronize
struct SIPCCMsg_OutDial_GwLineSynchronize : public SIPCCMsg_OutDial
{
	SIPCCMsg_OutDial_GwLineSynchronize();
	~SIPCCMsg_OutDial_GwLineSynchronize()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
public:
	int GwId;
	int AllLineCount;
	int FreeLineCount;
	string GwName;
	
	virtual int GetMyMemSize();
};

///Type_OutDial_TaskStateCtrl
struct SIPCCMsg_OutDial_TaskStateCtrl : public SIPCCMsg_OutDial
{
	SIPCCMsg_OutDial_TaskStateCtrl();
	~SIPCCMsg_OutDial_TaskStateCtrl()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
public:
	string TaskId;
	int StateCode;
	
	virtual int GetMyMemSize();
};

///Type_OutDial_SetMaxBotherRate
struct SIPCCMsg_OutDial_SetMaxBotherRate : public SIPCCMsg_OutDial
{
	SIPCCMsg_OutDial_SetMaxBotherRate();
	~SIPCCMsg_OutDial_SetMaxBotherRate()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
public:
	string TaskId;
	double AllowValue;
	
	virtual int GetMyMemSize();
};

///Type_OutDial_SetForecastIntensity
struct SIPCCMsg_OutDial_SetForecastIntensity : public SIPCCMsg_OutDial
{
	SIPCCMsg_OutDial_SetForecastIntensity();
	~SIPCCMsg_OutDial_SetForecastIntensity()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
public:
	int InvokeId;
	string TaskId;
	int Intensity;
	
	virtual int GetMyMemSize();
};

///Type_OutDial_SetForecastIntensityConf
struct SIPCCMsg_OutDial_SetForecastIntensityConf : public SIPCCMsg_OutDial
{
	SIPCCMsg_OutDial_SetForecastIntensityConf();
	~SIPCCMsg_OutDial_SetForecastIntensityConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
public:
	int InvokeId;
	string TaskId;
	int Intensity;
	
	virtual int GetMyMemSize();
};

//Type_OutDial_ResultStorage

struct SIPCCMsg_OutDial_ResultStorage : public SIPCCMsg_OutDial
{
	SIPCCMsg_OutDial_ResultStorage();
	~SIPCCMsg_OutDial_ResultStorage()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
public:
	string StorageType;
	string InvokeId;
	string StrResult;
	
	virtual int GetMyMemSize();
};

//Type_OutDial_TaskStatus,
struct SIPCCMsg_OutDial_TaskStatus : public SIPCCMsg_OutDial
{
	SIPCCMsg_OutDial_TaskStatus();
	~SIPCCMsg_OutDial_TaskStatus()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
public:
	string TaskID;
	char bQuery;
	int TaskTatus;
	int AnalysisID;
	virtual int GetMyMemSize();
};

//Type_OutDial_TaskStatusConf,
struct SIPCCMsg_OutDial_TaskStatusConf : public SIPCCMsg_OutDial
{
	SIPCCMsg_OutDial_TaskStatusConf();
	~SIPCCMsg_OutDial_TaskStatusConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
public:
	string TaskID;
	char bQuery;
	int TaskTatus;
	int AnalysisID;
	virtual int GetMyMemSize();
};

///////////////////////////////////////////////////////////////////////////
///Class_Notify
struct SIPCCMsg_Notify : public SIPCCMessage
{
	SIPCCMsg_Notify();
	~SIPCCMsg_Notify()
	{
		ReleaseMemory();
	};
	
	virtual int GetMyMemSize(){return 0;}
	virtual int FillBuf(char*& thebuf){return 0;}
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0){}
	virtual void ReleaseMemory(){}
};

struct SIPCCMsg_Notify_ErrorOccurred : public SIPCCMsg_Notify
{
	SIPCCMsg_Notify_ErrorOccurred();
	~SIPCCMsg_Notify_ErrorOccurred()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
public:
	int errorType;
	
	virtual int GetMyMemSize();
};

// 函数调用的头
struct SIPCCMsg_OCXFuncHead : public SIPCCMessage
{
	SIPCCMsg_OCXFuncHead()
	{
		msgClass = Class_FuncCall;
	};
	~SIPCCMsg_OCXFuncHead()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	// 序列化
	int FillOurBuf(char* thebuf);
	int ReadOurBuf(char* thebuf, int msgsize);
	// 填充字符串
	static int FillString(char* thebuf, const string& str);
	static int GetString(char* thebuf, string& str);
public:
	string invokeId;	
	virtual int GetMyMemSize();
};

// 函数调用的头
struct SIPCCMsg_OCXHeartSend : public SIPCCMsg_HeartBeat
{
	SIPCCMsg_OCXHeartSend()
	{
		msgClass = Class_OCXHeart;
		msgType = Type_OCXHeart_Send;
	};
	virtual ~SIPCCMsg_OCXHeartSend()
	{
		ReleaseMemory();
	};
};

struct SIPCCMsg_OCXHeartResp : public SIPCCMsg_HeartBeatResponse
{
	SIPCCMsg_OCXHeartResp()
	{
		msgClass = Class_OCXHeart;
		msgType = Type_OCXHeart_Resp;
		
	};
	~SIPCCMsg_OCXHeartResp()
	{
		ReleaseMemory();
	};
};



///Class_Notify
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
/// Class_Autodetector
struct SIPCCMsg_Autodetector : public SIPCCMessage
{
	SIPCCMsg_Autodetector()
	{msgClass = Class_Autodetector;}
	~SIPCCMsg_Autodetector()
	{
		ReleaseMemory();
	};
	
	virtual int GetMyMemSize(){return 0;}
	virtual int FillBuf(char*& thebuf){return 0;}
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0){}
	virtual void ReleaseMemory(){};
};
///Type_Autodetector_Logon
struct SIPCCMsg_Autodetector_Logon : public SIPCCMsg_Autodetector
{
	SIPCCMsg_Autodetector_Logon()
	{
		msgType = Type_Autodetector_Logon;
	}
	~SIPCCMsg_Autodetector_Logon()
	{
		ReleaseMemory();
	}
	virtual int FillBuf(char*& thebuf){
		thebuf = new char[GetMyMemSize()];
		int theBufContent = FillMsgHead(thebuf);
		
		memcpy(thebuf+theBufContent, name.c_str(), name.length() + 1);
		theBufContent += name.length() + 1;
		
		return theBufContent;
	}
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0){
		int theBufContent = AnalyzeMsgHead(thebuf);
		
		name = thebuf + theBufContent;
		theBufContent += name.length()+1;
	}
	virtual void ReleaseMemory()
	{
	}
	
	string name;
private:
	virtual int GetMyMemSize(){
		int memSize = 2*sizeof(int);		//msgclass+msgtype
		memSize += name.length()+1;
		
		return memSize;
	}
};
///Type_Autodetector_LogonACK
struct SIPCCMsg_Autodetector_LogonACK : public SIPCCMsg_Autodetector
{
	SIPCCMsg_Autodetector_LogonACK()
	{
		msgType = Type_Autodetector_LogonACK;
	}
	~SIPCCMsg_Autodetector_LogonACK()
	{
		ReleaseMemory();
	}
	virtual int FillBuf(char*& thebuf){
		thebuf = new char[GetMyMemSize()];
		int theBufContent = FillMsgHead(thebuf);
		
		return theBufContent;
	}
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0){
		int theBufContent = AnalyzeMsgHead(thebuf);
		
	}
	virtual void ReleaseMemory()
	{
	}
	
private:
	virtual int GetMyMemSize(){
		int memSize = 2*sizeof(int);		//msgclass+msgtype
		
		return memSize;
	}
};
struct SIPCCMsg_Autodetector_heartbeat : public SIPCCMsg_Autodetector
{
	SIPCCMsg_Autodetector_heartbeat()
	{
		msgType = Type_Autodetector_Heartbeat;
	}
	~SIPCCMsg_Autodetector_heartbeat()
	{
		ReleaseMemory();
	}
	virtual int FillBuf(char*& thebuf){
		thebuf = new char[GetMyMemSize()];
		int theBufContent = FillMsgHead(thebuf);
		
		memcpy(thebuf+theBufContent, name.c_str(), name.length() + 1);
		theBufContent += name.length() + 1;
		
		return theBufContent;
	}
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0){
		int theBufContent = AnalyzeMsgHead(thebuf);
		
		name = thebuf + theBufContent;
		theBufContent += name.length()+1;
	}
	virtual void ReleaseMemory()
	{
	}
	
	string name;
private:
	virtual int GetMyMemSize(){
		int memSize = 2*sizeof(int);		//msgclass+msgtype
		memSize += name.length()+1;
		
		return memSize;
	}
};
struct SIPCCMsg_Autodetector_heartbeatACK : public SIPCCMsg_Autodetector
{
	SIPCCMsg_Autodetector_heartbeatACK()
	{
		msgType = Type_Autodetector_HeartbeatACK;
	}
	~SIPCCMsg_Autodetector_heartbeatACK()
	{
		ReleaseMemory();
	}
	virtual int FillBuf(char*& thebuf){
		thebuf = new char[GetMyMemSize()];
		int theBufContent = FillMsgHead(thebuf);
		
		return theBufContent;
	}
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0){
		int theBufContent = AnalyzeMsgHead(thebuf);
	}
	virtual void ReleaseMemory()
	{
	}
	
private:
	virtual int GetMyMemSize(){
		int memSize = 2*sizeof(int);		//msgclass+msgtype
		return memSize;
	}
};

enum eReason{reason_invalidate, reason_disappearing, reason_crash};
struct SIPCCMsg_Autodetector_reportError : public SIPCCMsg_Autodetector
{
	SIPCCMsg_Autodetector_reportError()
	{
		msgType = Type_Autodetector_ReportError;
		eRea = reason_invalidate;
	}
	~SIPCCMsg_Autodetector_reportError()
	{
		ReleaseMemory();
	}
	virtual int FillBuf(char*& thebuf){
		thebuf = new char[GetMyMemSize()];
		int theBufContent = FillMsgHead(thebuf);
		memcpy(thebuf+theBufContent, name.c_str(), name.length() + 1);
		theBufContent += name.length() + 1;
		
		memcpy(thebuf+theBufContent, processName.c_str(), processName.length() + 1);
		theBufContent += processName.length() + 1;
		
		memcpy(thebuf+theBufContent, &eRea, sizeof(eRea));
		theBufContent += sizeof(eRea);
		return theBufContent;
	}
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0){
		int theBufContent = AnalyzeMsgHead(thebuf);
		
		name = thebuf + theBufContent;
		theBufContent += name.length()+1;
		
		processName = thebuf + theBufContent;
		theBufContent += processName.length()+1;
		
		memcpy(&eRea, thebuf+theBufContent, sizeof(eRea));
		theBufContent += sizeof(eRea);
	}
	virtual void ReleaseMemory()
	{
	}
	string name;
	string processName;
	eReason eRea; 
private:
	virtual int GetMyMemSize(){
		int memSize = 2*sizeof(int);		//msgclass+msgtype
		memSize += name.length()+1;
		memSize += processName.length()+1;
		memSize += sizeof(eRea);
		return memSize;
	}
};

struct SIPCCMsg_Autodetector_RebootProc : public SIPCCMsg_Autodetector
{
	SIPCCMsg_Autodetector_RebootProc()
	{
		msgType = Type_Autodetector_RebootProc;
	}
	~SIPCCMsg_Autodetector_RebootProc()
	{
		ReleaseMemory();
	}
	virtual int FillBuf(char*& thebuf){
		thebuf = new char[GetMyMemSize()];
		int theBufContent = FillMsgHead(thebuf);
		
		memcpy(thebuf+theBufContent, processName.c_str(), processName.length() + 1);
		theBufContent += processName.length() + 1;
		
		return theBufContent;
	}
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0){
		int theBufContent = AnalyzeMsgHead(thebuf);
		
		processName = thebuf + theBufContent;
		theBufContent += processName.length()+1;
	}
	virtual void ReleaseMemory()
	{
	}
	string processName;
private:
	virtual int GetMyMemSize(){
		int memSize = 2*sizeof(int);		//msgclass+msgtype
		memSize += processName.length()+1;
		return memSize;
	}
};
enum eResult {invalidate, noFile, success, noItem};
struct SIPCCMsg_Autodetector_RebootProcACK : public SIPCCMsg_Autodetector
{
	SIPCCMsg_Autodetector_RebootProcACK()
	{
		msgType = Type_Autodetector_RebootProcACK;
		eRes = invalidate;
	}
	~SIPCCMsg_Autodetector_RebootProcACK()
	{
		ReleaseMemory();
	}
	virtual int FillBuf(char*& thebuf){
		thebuf = new char[GetMyMemSize()];
		int theBufContent = FillMsgHead(thebuf);
		memcpy(thebuf+theBufContent, name.c_str(), name.length() + 1);
		theBufContent += name.length() + 1;
		
		memcpy(thebuf+theBufContent, processName.c_str(), processName.length() + 1);
		theBufContent += processName.length() + 1;
		
		memcpy(thebuf+theBufContent, &eRes, sizeof(eRes));
		theBufContent += sizeof(eRes);
		return theBufContent;
	}
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0){
		int theBufContent = AnalyzeMsgHead(thebuf);
		
		name = thebuf + theBufContent;
		theBufContent += name.length()+1;
		
		processName = thebuf + theBufContent;
		theBufContent += processName.length()+1;
		
		memcpy(&eRes, thebuf+theBufContent, sizeof(eRes));
		theBufContent += sizeof(eRes);
	}
	virtual void ReleaseMemory()
	{
	}
	string name;
	string processName;
	eResult eRes; 
private:
	virtual int GetMyMemSize(){
		int memSize = 2*sizeof(int);		//msgclass+msgtype
		memSize += name.length()+1;
		memSize += processName.length()+1;
		memSize += sizeof(eRes);
		return memSize;
	}
};
// svrStatMonitor
enum eStates {States_normal, States_invalidate,States_unStartup,States_haveErrorLog, States_blooey, States_discontinuous};
struct SIPCCMsg_Autodetector_ReportCompStat : public SIPCCMsg_Autodetector
{
	SIPCCMsg_Autodetector_ReportCompStat()
	{
		msgType = Type_Autodetector_ReportCompStat;
		eSta = States_invalidate;
	}
	~SIPCCMsg_Autodetector_ReportCompStat()
	{
		ReleaseMemory();
	}
	virtual int FillBuf(char*& thebuf){
		thebuf = new char[GetMyMemSize()];
		int theBufContent = FillMsgHead(thebuf);
		memcpy(thebuf+theBufContent, strCompName.c_str(), strCompName.length() + 1);
		theBufContent += strCompName.length() + 1;
		
		memcpy(thebuf+theBufContent, strVersion.c_str(), strVersion.length() + 1);
		theBufContent += strVersion.length() + 1;
		
		memcpy(thebuf+theBufContent, &eSta, sizeof(eSta));
		theBufContent += sizeof(eSta);
		
		memcpy(thebuf+theBufContent, strProcessName.c_str(), strProcessName.length() + 1);
		theBufContent += strProcessName.length() + 1;
		
		memcpy(thebuf+theBufContent, strMachine.c_str(), strMachine.length() + 1);
		theBufContent += strMachine.length() + 1;
		return theBufContent;
	}
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0){
		int theBufContent = AnalyzeMsgHead(thebuf);
		
		strCompName = thebuf + theBufContent;
		theBufContent += strCompName.length()+1;
		
		strVersion = thebuf + theBufContent;
		theBufContent += strVersion.length()+1;
		
		memcpy(&eSta, thebuf+theBufContent, sizeof(eSta));
		theBufContent += sizeof(eSta);
		
		strProcessName = thebuf + theBufContent;
		theBufContent += strProcessName.length()+1;
		
		strMachine = thebuf + theBufContent;
		theBufContent += strMachine.length()+1;
	}
	virtual void ReleaseMemory()
	{
	}
	string strCompName;
	string strVersion;
	eStates eSta;
	string strProcessName;
	string strMachine; 
private:
	virtual int GetMyMemSize(){
		int memSize = 2*sizeof(int);		//msgclass+msgtype
		memSize += strCompName.length()+1;
		memSize += strVersion.length()+1;
		memSize += sizeof(eSta);
		memSize += strProcessName.length()+1;
		memSize += strMachine.length()+1;
		return memSize;
	}
};
struct SIPCCMsg_Autodetector_heartbeatFromComp : public SIPCCMsg_Autodetector
{
	SIPCCMsg_Autodetector_heartbeatFromComp()
	{
		msgType = Type_Autodetector_heartbeatFromComp;
	}
	~SIPCCMsg_Autodetector_heartbeatFromComp()
	{
		ReleaseMemory();
	}
	virtual int FillBuf(char*& thebuf){
		thebuf = new char[GetMyMemSize()];
		int theBufContent = FillMsgHead(thebuf);
		
		memcpy(thebuf+theBufContent, name.c_str(), name.length() + 1);
		theBufContent += name.length() + 1;
		
		memcpy(thebuf+theBufContent, version.c_str(), version.length() + 1);
		theBufContent += version.length() + 1;
		
		return theBufContent;
	}
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0){
		int theBufContent = AnalyzeMsgHead(thebuf);
		
		name = thebuf + theBufContent;
		theBufContent += name.length()+1;
		
		version = thebuf + theBufContent;
		theBufContent += version.length()+1;
	}
	virtual void ReleaseMemory()
	{
	}
	
	string name;
	string version;
private:
	virtual int GetMyMemSize(){
		int memSize = 2*sizeof(int);		//msgclass+msgtype
		memSize += name.length()+1;
		memSize += version.length()+1;
		
		return memSize;
	}
};
struct SIPCCMsg_Autodetector_Log : public SIPCCMsg_Autodetector
{
	SIPCCMsg_Autodetector_Log()
	{
		msgType = Type_Autodetector_Log;
	}
	~SIPCCMsg_Autodetector_Log()
	{
		ReleaseMemory();
	}
	virtual int FillBuf(char*& thebuf){
		thebuf = new char[GetMyMemSize()];
		int theBufContent = FillMsgHead(thebuf);
		
		memcpy(thebuf+theBufContent, name.c_str(), name.length() + 1);
		theBufContent += name.length() + 1;
		
		memcpy(thebuf+theBufContent, text.c_str(), text.length() + 1);
		theBufContent += text.length() + 1;
		
		return theBufContent;
	}
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0){
		int theBufContent = AnalyzeMsgHead(thebuf);
		
		name = thebuf + theBufContent;
		theBufContent += name.length()+1;
		
		text = thebuf + theBufContent;
		theBufContent += text.length()+1;
	}
	virtual void ReleaseMemory()
	{
	}
	
	string name;
	string text;
private:
	virtual int GetMyMemSize(){
		int memSize = 2*sizeof(int);		//msgclass+msgtype
		memSize += name.length()+1;
		memSize += text.length()+1;
		
		return memSize;
	}
};

struct SIPCCMsg_Autodetector_Subscribe : public SIPCCMsg_Autodetector
{
	SIPCCMsg_Autodetector_Subscribe()
	{
		msgType = Type_Autodetector_Subscribe;
	}
	~SIPCCMsg_Autodetector_Subscribe()
	{
		ReleaseMemory();
	}
	virtual int FillBuf(char*& thebuf)
	{
		thebuf = new char[GetMyMemSize()];
		int theBufContent = FillMsgHead(thebuf);
		
		memcpy(thebuf+theBufContent, path.c_str(), path.length() + 1);
		theBufContent += path.length() + 1;
		
		return theBufContent;
	}
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0)
	{
		int theBufContent = AnalyzeMsgHead(thebuf);
		
		path = thebuf + theBufContent;
		theBufContent += path.length()+1;
	}
	virtual void ReleaseMemory()
	{
	}
	
	string path;
private:
	virtual int GetMyMemSize()
	{
		int memSize = 2*sizeof(int);		//msgclass+msgtype
		memSize += path.length()+1;
		return memSize;
	}
};

struct SIPCCMsg_Autodetector_SubscribeResp : public SIPCCMsg_Autodetector
{
	SIPCCMsg_Autodetector_SubscribeResp()
	{
		msgType = Type_Autodetector_Subscribe_Resp;
	}
	~SIPCCMsg_Autodetector_SubscribeResp()
	{
		ReleaseMemory();
	}
	virtual int FillBuf(char*& thebuf)
	{
		thebuf = new char[GetMyMemSize()];
		int theBufContent = FillMsgHead(thebuf);
		
		memcpy(thebuf+theBufContent, path.c_str(), path.length() + 1);
		theBufContent += path.length() + 1;
		// 包含详细信息
		memcpy(thebuf+theBufContent, &isInfo, sizeof(isInfo));
		theBufContent += sizeof(isInfo);
		
		memcpy(thebuf+theBufContent, node.c_str(), node.length() + 1);
		theBufContent += node.length() + 1;
		
		return theBufContent;
	}
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0)
	{
		int theBufContent = AnalyzeMsgHead(thebuf);
		
		path = thebuf + theBufContent;
		theBufContent += path.length()+1;
		// 包含详细信息
		isInfo = *(bool*)(thebuf + theBufContent);
		theBufContent += sizeof(bool);
		node = thebuf + theBufContent;
		theBufContent += node.length()+1;
	}
	virtual void ReleaseMemory()
	{
	}
	
	string path;
	// 是否叶子节点
	bool isInfo;
	string node;
private:
	virtual int GetMyMemSize()
	{
		int memSize = 2*sizeof(int);		//msgclass+msgtype
		memSize += path.length()+1;
		memSize += sizeof(isInfo);
		memSize += node.length()+1;
		return memSize;
	}
};

struct SIPCCMsg_Autodetector_SubscribeData : public SIPCCMsg_Autodetector
{
	SIPCCMsg_Autodetector_SubscribeData()
	{
		msgType = Type_Autodetector_Subscribe_Data;
	}
	~SIPCCMsg_Autodetector_SubscribeData()
	{
		ReleaseMemory();
	}
	virtual int FillBuf(char*& thebuf)
	{
		thebuf = new char[GetMyMemSize()];
		int theBufContent = FillMsgHead(thebuf);
		
		memcpy(thebuf+theBufContent, path.c_str(), path.length() + 1);
		theBufContent += path.length() + 1;
		// status
		memcpy(thebuf+theBufContent, &status, sizeof(status));
		theBufContent += sizeof(status);
		// 包含详细信息
		memcpy(thebuf+theBufContent, &isInfo, sizeof(isInfo));
		theBufContent += sizeof(isInfo);
		// 功能
		memcpy(thebuf+theBufContent, function.c_str(), function.length() + 1);
		theBufContent += function.length() + 1;
		// 版本
		memcpy(thebuf+theBufContent, version.c_str(), version.length() + 1);
		theBufContent += version.length() + 1;
		// 备注
		memcpy(thebuf+theBufContent, remark.c_str(), remark.length() + 1);
		theBufContent += remark.length() + 1;
		// 日志
		byte nSize = arrlog.size();
		memcpy(thebuf+theBufContent, &nSize, sizeof(nSize));
		theBufContent += sizeof(nSize);
		for(int i = 0; i < nSize; i++)
		{
			memcpy(thebuf+theBufContent, arrlog[i].c_str(), arrlog[i].length() + 1);	
			theBufContent += arrlog[i].length()+1;
		}// for(		
		return theBufContent;
	}
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0)
	{
		int theBufContent = AnalyzeMsgHead(thebuf);
		
		path = thebuf + theBufContent;
		theBufContent += path.length()+1;
		// status
		status = *(int*)(thebuf + theBufContent);
		theBufContent += sizeof(int);
		// 包含详细信息
		isInfo = *(bool*)(thebuf + theBufContent);
		theBufContent += sizeof(bool);
		// function
		function = thebuf + theBufContent;
		theBufContent += function.length()+1;
		// 版本
		version = thebuf + theBufContent;
		theBufContent += version.length()+1;
		// 备注
		remark = thebuf + theBufContent;
		theBufContent += remark.length()+1;
		// 日志
		byte nSize = *(byte*)(thebuf + theBufContent);
		arrlog.clear();
		theBufContent += sizeof(byte);
		for(int i = 0; i < nSize; i++)
		{
			string strLog = thebuf + theBufContent;
			theBufContent += strLog.length()+1;
			arrlog.push_back(strLog);
		}// for
	}
	virtual void ReleaseMemory()
	{
	}
	
	string path;
	// 状态
	int status;
	// 是否叶子节点
	bool isInfo;
	// 功能
	string function;
	// 版本
	string version;
	// 备注
	string remark;
	// 日志
	vector<string> arrlog;
	
private:
	virtual int GetMyMemSize()
	{
		int memSize = 2*sizeof(int);		//msgclass+msgtype
		memSize += path.length()+1;
		memSize += sizeof(status);
		memSize += sizeof(isInfo);
		
		memSize += function.length()+1;
		memSize += version.length()+1;
		memSize += remark.length()+1;
		// log数据
		byte nSize = arrlog.size();
		memSize += sizeof(nSize);
		for(int i = 0; i < nSize; i++)
		{
			memSize += arrlog[i].length()+1;
		}// for(
		return memSize;
	}
};

struct SIPCCMsg_Autodetector_Unsubscri : public SIPCCMsg_Autodetector_Subscribe
{
	SIPCCMsg_Autodetector_Unsubscri()
	{
		msgType = Type_Autodetector_Unsubscri;
	}
	~SIPCCMsg_Autodetector_Unsubscri()
	{
		ReleaseMemory();
	}
};

struct SIPCCMsg_Autodetector_UnsubscriResp : public SIPCCMsg_Autodetector
{
	SIPCCMsg_Autodetector_UnsubscriResp()
	{
		msgType = Type_Autodetector_Unsubscri_Resp;
	}
	~SIPCCMsg_Autodetector_UnsubscriResp()
	{
		ReleaseMemory();
	}
	virtual int FillBuf(char*& thebuf)
	{
		thebuf = new char[GetMyMemSize()];
		int theBufContent = FillMsgHead(thebuf);
		
		memcpy(thebuf+theBufContent, path.c_str(), path.length() + 1);
		theBufContent += path.length() + 1;
		
		memcpy(thebuf+theBufContent, &result, sizeof(result));
		theBufContent += sizeof(result);
		
		return theBufContent;
	}
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0)
	{
		int theBufContent = AnalyzeMsgHead(thebuf);
		
		path = thebuf + theBufContent;
		theBufContent += path.length()+1;
		
		result = *(byte*)(thebuf + theBufContent);
		theBufContent += sizeof(byte);
	}
	virtual void ReleaseMemory()
	{
	}
	
	string path;
	byte result;
private:
	virtual int GetMyMemSize()
	{
		int memSize = 2*sizeof(int);		//msgclass+msgtype
		memSize += path.length()+1;
		memSize += sizeof(result);
		return memSize;
	}
};



struct SIPCCMsg_OCXService : public SIPCCMessage
{
	SIPCCMsg_OCXService(){msgClass = Class_OCXService;};
	~SIPCCMsg_OCXService()
	{
		ReleaseMemory();
	};
	
	virtual int GetMyMemSize(){return 0;}
	virtual int FillBuf(char*& thebuf){return 0;}
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0){}
	virtual void ReleaseMemory(){}
};

struct SIPCCMsg_OCXService_SubTrans : public SIPCCMsg_OCXService
{
	SIPCCMsg_OCXService_SubTrans();
	~SIPCCMsg_OCXService_SubTrans()
	{
		ReleaseMemory();
	};
	
	virtual int GetMyMemSize();
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){}
public:
	// 包ID
	unsigned int PackID;
	// 当前包数
	unsigned char NowNum;
	// 总包数
	unsigned char TotNum;
	// 数据长度
	unsigned short DataLen;
	// 数据内容
	char DataBuf[1000];
	
};

struct SIPCCMsg_Gateway_GetDeptLoginAgentNum : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_GetDeptLoginAgentNum();
	~SIPCCMsg_Gateway_GetDeptLoginAgentNum()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
public:
	string invokeId;
	string m_ssDeptName;
	string m_ssCorpName;

	string  connectPhoneNo;
	string  handleId;
	
	virtual int GetMyMemSize();
};

struct SIPCCMsg_ACD_GetDeptLoginAgentNumConf : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_GetDeptLoginAgentNumConf();
	~SIPCCMsg_ACD_GetDeptLoginAgentNumConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
public:
	string invokeId;
	unsigned short  m_uCount;

	string  handleId;
	
	virtual int GetMyMemSize();
};

// 开始 [10/10/2009 lixg]
///Class_Operator
struct SIPCCMsg_Operator : public SIPCCMessage
{
	SIPCCMsg_Operator();
	~SIPCCMsg_Operator()
	{
		ReleaseMemory();
	};
	
	virtual int GetMyMemSize(){return 0;}
	virtual int FillBuf(char*& thebuf){return 0;}
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0){}
	virtual void ReleaseMemory(){};
};
enum eNoticeType
{
	Notice_All,		// 所有在线座席，或者所有正在登录
		Notice_Company,	// 某个公司所有在线座席，或者所有正在登录
		Notice_Agents	// 某个座席，或某几个座席。
};
struct SIPCCMsg_Operator2ACD_SendStrMsg : public SIPCCMsg_Operator
{
	SIPCCMsg_Operator2ACD_SendStrMsg();
	~SIPCCMsg_Operator2ACD_SendStrMsg()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf)
	{
		thebuf = new char[GetMyMemSize()];
		int theBufContent = FillMsgHead(thebuf);
		
		memmove(thebuf+theBufContent, &this->eNT, sizeof(this->eNT));
		theBufContent += sizeof(this->eNT);
		
		memcpy(thebuf+theBufContent, strCompany.c_str(), strCompany.length()+1);
		theBufContent += strCompany.length()+1;
		
		memcpy(thebuf+theBufContent, destAgents.c_str(), destAgents.length()+1);
		theBufContent += destAgents.length()+1;
		
		memcpy(thebuf+theBufContent, theSender.c_str(), theSender.length()+1);
		theBufContent += theSender.length()+1;
		
		memcpy(thebuf+theBufContent, msgContent.c_str(), msgContent.length()+1);
		theBufContent += msgContent.length()+1;
		
		return theBufContent;
	}
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0)
	{
		string strMsg = "SIPCCMsg_Operator2ACD_SendStrMsg";
		if ( !(VerifyTotalLen(HEAD_LEN, msgsize, strMsg, "MsgHead", ip, port, g_bIsACDServer)) ) {return;}
		int theBufContent = AnalyzeMsgHead(thebuf);
		
		if ( !(VerifyTotalLen(theBufContent+ sizeof(this->eNT), msgsize, strMsg, "eNT", ip, port, g_bIsACDServer)) ) {return;}
		memmove(&this->eNT, thebuf+theBufContent, sizeof(this->eNT));
		theBufContent += sizeof(this->eNT);
		
		strCompany = thebuf + theBufContent;
		if ( !(VerifyTotalLen(theBufContent+strCompany.length()+1, msgsize, strMsg, "strCompany.length()", ip, port, g_bIsACDServer)) ) {return;}
		if ( !(VerifyData(strCompany.length(), CORPNAME_LEN, strMsg, "strCompany", ip, port, g_bIsACDServer)) ) {return;}
		theBufContent += strCompany.length()+1;
		
		destAgents = thebuf + theBufContent;
		if ( !(VerifyTotalLen(theBufContent+destAgents.length()+1, msgsize, strMsg, "destAgents.length()", ip, port, g_bIsACDServer)) ) {return;}
		if ( !(VerifyData(destAgents.length(), DESTAGENTS_LEN, strMsg, "destAgents", ip, port, g_bIsACDServer)) ) {return;}
		theBufContent += destAgents.length()+1;
		
		theSender = thebuf + theBufContent;
		if ( !(VerifyTotalLen(theBufContent+theSender.length()+1, msgsize, strMsg, "theSender.length()", ip, port, g_bIsACDServer)) ) {return;}
		if ( !(VerifyData(theSender.length(), SENDER_LEN, strMsg, "theSender", ip, port, g_bIsACDServer)) ) {return;}
		theBufContent += theSender.length()+1;
		
		msgContent = thebuf + theBufContent;
		if ( !(VerifyTotalLen(theBufContent+msgContent.length()+1, msgsize, strMsg, "msgContent.length()", ip, port, g_bIsACDServer)) ) {return;}
		if ( !(VerifyData(msgContent.length(), MSGCONTENT_LEN, strMsg, "msgContent", ip, port, g_bIsACDServer)) ) {return;}
		theBufContent += msgContent.length()+1;
	};
	virtual void ReleaseMemory()
	{
	}
	
public:
	eNoticeType	eNT;// 所有在线座席、某个企业、某个座席。
	string strCompany;
	string destAgents;	//		格式 1@1.com|1@2.com|
	string theSender;
	string msgContent;
	
	virtual int GetMyMemSize()
	{
		int memSize = 2*sizeof(int);		//msgclass+msgtype
		
		memSize += sizeof(eNoticeType);
		memSize += strCompany.length()+1;
		memSize += destAgents.length()+1;
		memSize += theSender.length()+1;
		memSize += msgContent.length()+1;
		
		return memSize;
	}
};
struct SIPCCMsg_Operator2Login_SendStrMsg : public SIPCCMsg_Operator
{
	SIPCCMsg_Operator2Login_SendStrMsg();
	~SIPCCMsg_Operator2Login_SendStrMsg()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf)
	{
		thebuf = new char[GetMyMemSize()];
		int theBufContent = FillMsgHead(thebuf);
		
		memmove(thebuf+theBufContent, &this->eNT, sizeof(this->eNT));
		theBufContent += sizeof(this->eNT);
		
		memcpy(thebuf+theBufContent, strCompany.c_str(), strCompany.length()+1);
		theBufContent += strCompany.length()+1;
		
		memcpy(thebuf+theBufContent, destAgents.c_str(), destAgents.length()+1);
		theBufContent += destAgents.length()+1;
		
		memcpy(thebuf+theBufContent, theSender.c_str(), theSender.length()+1);
		theBufContent += theSender.length()+1;
		
		memcpy(thebuf+theBufContent, msgContent.c_str(), msgContent.length()+1);
		theBufContent += msgContent.length()+1;
		
		memmove(thebuf+theBufContent, &this->tBeginTime, sizeof(this->tBeginTime));
		theBufContent += sizeof(this->tBeginTime);
		
		memmove(thebuf+theBufContent, &this->tEndTime, sizeof(this->tEndTime));
		theBufContent += sizeof(this->tEndTime);
		
		return theBufContent;
	}
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0)
	{
		int theBufContent = AnalyzeMsgHead(thebuf);
		
		memmove(&this->eNT, thebuf+theBufContent, sizeof(this->eNT));
		theBufContent += sizeof(this->eNT);
		
		strCompany = thebuf + theBufContent;
		theBufContent += strCompany.length()+1;
		
		destAgents = thebuf + theBufContent;
		theBufContent += destAgents.length()+1;
		
		theSender = thebuf + theBufContent;
		theBufContent += theSender.length()+1;
		
		msgContent = thebuf + theBufContent;
		theBufContent += msgContent.length()+1;
		
		memmove(&this->tBeginTime, thebuf+theBufContent, sizeof(this->tBeginTime));
		theBufContent += sizeof(this->tBeginTime);
		
		memmove(&this->tEndTime, thebuf+theBufContent, sizeof(this->tEndTime));
		theBufContent += sizeof(this->tEndTime);
	};
	virtual void ReleaseMemory()
	{
	}
	
public:
	eNoticeType	eNT;// 所有在线座席、某个企业、某个座席。
	string strCompany;
	string destAgents;	//		格式 1@1.com|1@2.com|
	string theSender;
	string msgContent;
	
	unsigned int tBeginTime;
	unsigned int tEndTime;
	
	virtual int GetMyMemSize()
	{
		int memSize = 2*sizeof(int);		//msgclass+msgtype
		
		memSize += sizeof(eNoticeType);
		memSize += strCompany.length()+1;
		memSize += destAgents.length()+1;
		memSize += theSender.length()+1;
		memSize += msgContent.length()+1;
		
		memSize += sizeof(tBeginTime);
		memSize += sizeof(tEndTime);
		return memSize;
	}
};

struct SIPCCMsg_Operator2Login_GetStrMsg : public SIPCCMsg_Operator
{
	SIPCCMsg_Operator2Login_GetStrMsg();
	~SIPCCMsg_Operator2Login_GetStrMsg()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf)
	{
		thebuf = new char[GetMyMemSize()];
		int theBufContent = FillMsgHead(thebuf);
		
		memmove(thebuf+theBufContent, &this->nInvokeId, sizeof(this->nInvokeId));
		theBufContent += sizeof(this->nInvokeId);
		
		return theBufContent;
	}
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0)
	{
		int theBufContent = AnalyzeMsgHead(thebuf);
		memmove(&this->nInvokeId, thebuf+theBufContent, sizeof(this->nInvokeId));
		theBufContent += sizeof(this->nInvokeId);
		
	};
	virtual void ReleaseMemory()
	{
	}
	
public:
	int nInvokeId;	// 由服务状态监控服务端来产生。（简化为socketid了）
	virtual int GetMyMemSize()
	{
		int memSize = 2*sizeof(int);		//msgclass+msgtype
		memSize += sizeof(nInvokeId);
		
		return memSize;
	}
};

struct SIPCCMsg_Login_GetStrMsgRes : public SIPCCMsg_Operator
{
	SIPCCMsg_Login_GetStrMsgRes();
	~SIPCCMsg_Login_GetStrMsgRes()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf)
	{
		thebuf = new char[GetMyMemSize()];
		int theBufContent = FillMsgHead(thebuf);
		
		memmove(thebuf+theBufContent, &this->nInvokeId, sizeof(this->nInvokeId));
		theBufContent += sizeof(this->nInvokeId);
		memmove(thebuf+theBufContent, &this->nStrMsgId, sizeof(this->nStrMsgId));
		theBufContent += sizeof(this->nStrMsgId);
		memmove(thebuf+theBufContent, &this->eNT, sizeof(this->eNT));
		theBufContent += sizeof(this->eNT);
		
		memcpy(thebuf+theBufContent, strCompany.c_str(), strCompany.length()+1);
		theBufContent += strCompany.length()+1;
		
		memcpy(thebuf+theBufContent, destAgents.c_str(), destAgents.length()+1);
		theBufContent += destAgents.length()+1;
		
		memcpy(thebuf+theBufContent, theSender.c_str(), theSender.length()+1);
		theBufContent += theSender.length()+1;
		
		memcpy(thebuf+theBufContent, msgContent.c_str(), msgContent.length()+1);
		theBufContent += msgContent.length()+1;
		
		memmove(thebuf+theBufContent, &this->tBeginTime, sizeof(this->tBeginTime));
		theBufContent += sizeof(this->tBeginTime);
		
		memmove(thebuf+theBufContent, &this->tEndTime, sizeof(this->tEndTime));
		theBufContent += sizeof(this->tEndTime);
		return theBufContent;
	}
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0)
	{
		int theBufContent = AnalyzeMsgHead(thebuf);
		
		memmove(&this->nInvokeId, thebuf+theBufContent, sizeof(this->nInvokeId));
		theBufContent += sizeof(this->nInvokeId);
		memmove(&this->nStrMsgId, thebuf+theBufContent, sizeof(this->nStrMsgId));
		theBufContent += sizeof(this->nStrMsgId);
		memmove(&this->eNT, thebuf+theBufContent, sizeof(this->eNT));
		theBufContent += sizeof(this->eNT);
		
		strCompany = thebuf + theBufContent;
		theBufContent += strCompany.length()+1;
		
		destAgents = thebuf + theBufContent;
		theBufContent += destAgents.length()+1;
		
		theSender = thebuf + theBufContent;
		theBufContent += theSender.length()+1;
		
		msgContent = thebuf + theBufContent;
		theBufContent += msgContent.length()+1;
		
		memmove(&this->tBeginTime, thebuf+theBufContent, sizeof(this->tBeginTime));
		theBufContent += sizeof(this->tBeginTime);
		
		memmove(&this->tEndTime, thebuf+theBufContent, sizeof(this->tEndTime));
		theBufContent += sizeof(this->tEndTime);
		
	};
	virtual void ReleaseMemory()
	{
	}
	
public:
	int nInvokeId;	// 由服务状态监控服务端来产生。（简化为socketid了）
	int nStrMsgId;
	eNoticeType	eNT;
	string strCompany;
	string destAgents; // 格式 1@1.com|1@2.com|...
	string theSender;
	string msgContent;
	
	unsigned int tBeginTime;	// 发布的开始时间
	unsigned int tEndTime;	// 停止发布的时间
	
	virtual int GetMyMemSize()
	{
		int memSize = 2*sizeof(int);		//msgclass+msgtype
		memSize += sizeof(nInvokeId);
		memSize += sizeof(nStrMsgId);
		memSize += sizeof(eNoticeType);
		memSize += strCompany.length()+1;
		memSize += destAgents.length()+1;
		memSize += theSender.length()+1;
		memSize += msgContent.length()+1;
		
		memSize += sizeof(tBeginTime);
		memSize += sizeof(tEndTime);
		return memSize;
	}
};

struct SIPCCMsg_Operator2Login_CancelStrMsg : public SIPCCMsg_Operator
{
	SIPCCMsg_Operator2Login_CancelStrMsg();
	~SIPCCMsg_Operator2Login_CancelStrMsg()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf)
	{
		thebuf = new char[GetMyMemSize()];
		int theBufContent = FillMsgHead(thebuf);
		
		memmove(thebuf+theBufContent, &this->nStrMsgId, sizeof(this->nStrMsgId));
		theBufContent += sizeof(this->nStrMsgId);
		
		return theBufContent;
	}
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0)
	{
		int theBufContent = AnalyzeMsgHead(thebuf);
		memmove(&this->nStrMsgId, thebuf+theBufContent, sizeof(this->nStrMsgId));
		theBufContent += sizeof(this->nStrMsgId);
		
	};
	virtual void ReleaseMemory()
	{
	}
	
public:
	int nStrMsgId;
	virtual int GetMyMemSize()
	{
		int memSize = 2*sizeof(int);		//msgclass+msgtype
		memSize += sizeof(nStrMsgId);
		
		return memSize;
	}
};
// 结束 [10/10/2009 lixg]

struct SIPCCMsg_Gateway_TrunkStat : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_TrunkStat();
	~SIPCCMsg_Gateway_TrunkStat()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	string ComputerSymbol;
	string GwName;
	int GroupId;
	string StartTime;
	string EndTime;
	string Stat;		//状态1Id;状态1字符串;次数;时长|状态2Id; 状态2字符串;次数;时长。。。。。。
	
private:
	virtual int GetMyMemSize();
};

struct SIPCCMsg_Gateway_TrunkSeizeRate : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_TrunkSeizeRate();
	~SIPCCMsg_Gateway_TrunkSeizeRate()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	string ComputerSymbol;
	string GwName;
	int LineCount;
	int MaxSeizeCount;
	string StartTime;
	string EndTime;
	string GroupSeize;	//组1;线数;最大占用数|组2;线数;最大占用数。。。。。。
	
private:
	virtual int GetMyMemSize();
};

struct SIPCCMsg_Gateway_CallInStat : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_CallInStat();
	~SIPCCMsg_Gateway_CallInStat()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	string ComputerSymbol;
	string GwName;
	string CalleeNum;
	int Times;
	int TotalSpan;
	string StartTime;
	string EndTime;
	
	int HookTimes;
	
	int MaxSeizeCount;
	
private:
	virtual int GetMyMemSize();
};

struct SIPCCMsg_Gateway_CallInOutStat : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_CallInOutStat();
	~SIPCCMsg_Gateway_CallInOutStat()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}

	string ComputerSymbol;
	string GwName;
	string CalleeNum;
	int Times;
	int TotalSpan;
	string StartTime;
	string EndTime;

	int HookTimes;

	int MaxSeizeCount;

private:
	virtual int GetMyMemSize();
};

struct SIPCCMsg_Gateway_CallOutStat : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_CallOutStat();
	~SIPCCMsg_Gateway_CallOutStat()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	string ComputerSymbol;
	string GwName;
	string ManagerId;
	int Times;
	int TotalSpan;
	string StartTime;
	string EndTime;
	
	int HookTimes;
	
	int MaxSeizeCount;
	
private:
	virtual int GetMyMemSize();
};

// Type_Gateway_NotifyTrunkState
struct SIPCCMsg_Gateway_NotifyTrunkState : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_NotifyTrunkState();
	~SIPCCMsg_Gateway_NotifyTrunkState()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}

	string ComputerSymbol;
	string GwName;
	string LineNo;
	int GroupId;
	int CallDirection;
	int LastState;
	int NewState;
	string CallKey;
	time_t newStatetime;
    int MappingName;
	operator const string(){
		ostringstream oss;
		oss << "ComputerSymbol=" << ComputerSymbol << ","
			<< "GwName=" << GwName << ","
			<< "LineNo=" << LineNo << ","
			<< "GroupId=" << GroupId << ","
			<< "CallDirection=" << CallDirection << ","
			<< "LastState=" << LastState << ","
			<< "NewState=" << NewState << ","
			<< "CallKey=" << CallKey<<","
			<< "MappingName="<<MappingName;
		return oss.str();
	};
private:
	virtual int GetMyMemSize();
};

///////////////////////////////////////////////////////////////////////////
///Class_Monitor
struct SIPCCMsg_Monitor : public SIPCCMessage
{
	SIPCCMsg_Monitor();
	~SIPCCMsg_Monitor()
	{
		ReleaseMemory();
	};
	
	virtual int GetMyMemSize(){return 0;}
	virtual int FillBuf(char*& thebuf){return 0;}
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0){}
	virtual void ReleaseMemory(){}
};
// Type_Monitor_SrvLogin
struct SIPCCMsg_Monitor_SrvLogin : public SIPCCMsg_Monitor
{
	SIPCCMsg_Monitor_SrvLogin();
	~SIPCCMsg_Monitor_SrvLogin()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	int m_iCmd; // 注册注销
	char m_szIP[20];  // 服务器ip
	unsigned short m_uPort;  // 服务器端口
	unsigned short m_uCliNum;  // 服务器客户端连接数
	unsigned short m_uDK;  // 带宽单位M
	unsigned short m_uAgentNum;  // 最大连接座席数
	unsigned short m_uAgentCNum; // 当前座席连接数
	unsigned short m_uTrunkNum;  // 最大连接中继数
	unsigned short m_uTCNum; // 当前中继连接数
	string m_sSrvCode; // 服务器编码

	int iLoginType;  //LoginType 类型：1-向父端登录注册 2-向CCenter服务注册
	
private:
	virtual int GetMyMemSize();
};
// Type_Monitor_SrvLoginConf
struct SIPCCMsg_Monitor_SrvLoginConf : public SIPCCMsg_Monitor
{
	SIPCCMsg_Monitor_SrvLoginConf();
	~SIPCCMsg_Monitor_SrvLoginConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	bool m_bSucc;
	int iLoginType;  //LoginType 类型：1-向父端登录注册 2-向CCenter服务注册
private:
	virtual int GetMyMemSize();
};

// Type_Monitor_SrvLogout
struct SIPCCMsg_Monitor_SrvLogout : public SIPCCMsg_Monitor
{
	SIPCCMsg_Monitor_SrvLogout();
	~SIPCCMsg_Monitor_SrvLogout()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	int m_iCmd; // 注册注销
	char m_szIP[20];  // 服务器ip
	unsigned short m_uPort;  // 服务器端口
	string m_sSrvCode; // 服务器编码

	
private:
	virtual int GetMyMemSize();
};

// Type_Monitor_SrvLogoutConf
struct SIPCCMsg_Monitor_SrvLogoutConf : public SIPCCMsg_Monitor
{
	SIPCCMsg_Monitor_SrvLogoutConf();
	~SIPCCMsg_Monitor_SrvLogoutConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	bool m_bSucc;
	
private:
	virtual int GetMyMemSize();
};

// Type_Monitor_UpdateCliCount
struct SIPCCMsg_Monitor_UpdateCliCount : public SIPCCMsg_Monitor
{
	SIPCCMsg_Monitor_UpdateCliCount();
	~SIPCCMsg_Monitor_UpdateCliCount()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	unsigned short m_uCliCount;
	
private:
	virtual int GetMyMemSize();
};

// Type_Client_NotifyAgentLogin
struct SIPCCMsg_Client_NotifyAgentLogin : public SIPCCMsg_Client
{
	SIPCCMsg_Client_NotifyAgentLogin();
	~SIPCCMsg_Client_NotifyAgentLogin()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){}
	
	string agentName;
	string managerID;
	string corpName;
	string departmentName;
	
private:
	virtual int GetMyMemSize();
};

// Type_OutDial_HeartBeat
struct SIPCCMsg_OutDial_HeartBeat : public SIPCCMsg_OutDial
{
	SIPCCMsg_OutDial_HeartBeat();
	~SIPCCMsg_OutDial_HeartBeat()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){}
	
	string GatewayId;
	
private:
	virtual int GetMyMemSize();
};

// Type_OutDial_ToGw
struct SIPCCMsg_OutDial_ToGw : public SIPCCMsg_OutDial
{
	SIPCCMsg_OutDial_ToGw();
	~SIPCCMsg_OutDial_ToGw()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){}
	
	string GatewayId;
	string Message;
	
private:
	virtual int GetMyMemSize();
};

// Type_OutDial_FromGw
struct SIPCCMsg_OutDial_FromGw : public SIPCCMsg_OutDial
{
	SIPCCMsg_OutDial_FromGw();
	~SIPCCMsg_OutDial_FromGw()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){}
	
	string GatewayId;
	string Message;
	
private:
	virtual int GetMyMemSize();
};

// 开始 [6/1/2010 lixg]
///Class_Log
struct SIPCCMsg_Log : public SIPCCMessage
{
	SIPCCMsg_Log();
	~SIPCCMsg_Log()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf)
	{
		thebuf = new char[GetMyMemSize()];
		int theBufContent = FillMsgHead(thebuf);
		
		memcpy(thebuf+theBufContent, strComponent.c_str(), strComponent.length()+1);
		theBufContent += strComponent.length()+1;
		
		memcpy(thebuf+theBufContent, strLogType.c_str(), strLogType.length()+1);
		theBufContent += strLogType.length()+1;
		
		memcpy(thebuf+theBufContent, msgContent.c_str(), msgContent.length()+1);
		theBufContent += msgContent.length()+1;
		
		return theBufContent;
	}
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0)
	{
		int theBufContent = AnalyzeMsgHead(thebuf);
		
		strComponent = thebuf + theBufContent;
		theBufContent += strComponent.length()+1;
		
		strLogType = thebuf + theBufContent;
		theBufContent += strLogType.length()+1;
		
		msgContent = thebuf + theBufContent;
		theBufContent += msgContent.length()+1;
	};
	virtual void ReleaseMemory()
	{
	}
	
public:
	string strComponent; // 发送方构件名(发送方填写)
	string strLogType;	 // 日志类型(发送方填写) 服务器会以	strComponent和strLogType作为日志文件的组成部分
	string msgContent;	 // 内容
	
	virtual int GetMyMemSize()
	{
		int memSize = 2*sizeof(int);		//msgclass+msgtype
		memSize += strComponent.length()+1;
		memSize += strLogType.length()+1;
		memSize += msgContent.length()+1;
		
		return memSize;
	}
};

struct SIPCCMsg_Client_WpAgentHanupCall : public SIPCCMsg_Client
{
	SIPCCMsg_Client_WpAgentHanupCall();
	~SIPCCMsg_Client_WpAgentHanupCall()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	string agentID;
	string gwAgentLine;
	string gwUserLine;
	
private:
	virtual int GetMyMemSize();
};

struct SIPCCMsg_UState_WpAgentHanupCall : public SIPCCMsg_UState
{
	SIPCCMsg_UState_WpAgentHanupCall();
	~SIPCCMsg_UState_WpAgentHanupCall()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	string agentID;
	string gwAgentLine;
	string gwUserLine;

	string gatewayName;

	string computerSymbol;
	
private:
	virtual int GetMyMemSize();
};

struct SIPCCMsg_UState_WpAgentHanupCallConf : public SIPCCMsg_UState
{
	SIPCCMsg_UState_WpAgentHanupCallConf();
	~SIPCCMsg_UState_WpAgentHanupCallConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	string agentID;
	
private:
	virtual int GetMyMemSize();
};

struct SIPCCMsg_Gateway_WpAgent_LineNo : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_WpAgent_LineNo();
	~SIPCCMsg_Gateway_WpAgent_LineNo()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	string agentID;
	string gwAgentLine;
	string gwUserLine;

	string managerId;
	string connectPhoneNo;
	
private:
	virtual int GetMyMemSize();
};

struct SIPCCMsg_ACD_WpAgent_LineNo : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_WpAgent_LineNo();
	~SIPCCMsg_ACD_WpAgent_LineNo()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	string agentID;
	string gwAgentLine;
	string gwUserLine;
	
private:
	virtual int GetMyMemSize();
};

struct SIPCCMsg_Gateway_WpAgentRelease : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_WpAgentRelease();
	~SIPCCMsg_Gateway_WpAgentRelease()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	
	string agentID;

	string managerId;
	string connectPhoneNo;
	
private:
	virtual int GetMyMemSize();
};

struct SIPCCMsg_Gateway_WebPSTNDialConf : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_WebPSTNDialConf();
	~SIPCCMsg_Gateway_WebPSTNDialConf()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}

	string agentID;
	string comSymbol;
	string gwName;
	string newUserPhoneNo;
	string newAgentPhoneNo;
	string gwPartNo;
	int	   dtmfEN;
	string handleId;		//操作唯一标识
	


private:
	virtual int GetMyMemSize();
};

/// Type_Client_WpAgentMakeCall
struct SIPCCMessage_Client_WpAgentMakeCall : public SIPCCMsg_Client
{
	SIPCCMessage_Client_WpAgentMakeCall();
	~SIPCCMessage_Client_WpAgentMakeCall()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}

	string agentID;
	string CorpName;
	string UUIData;
	string callerNoForSend;
	string outdialPrefixNo;
	string AgentLineNo;
	unsigned long agentLineIp;
	unsigned short agentLinePort;
	string theParty;
	int thePartyType;
	string otherParty;
	int otherPartyType;
	char needPreConnect;
	char needPreRecord;  

private:
	virtual int GetMyMemSize();
};

/// Type_UState_WpAgentMakeCall
struct SIPCCMessage_UState_WpAgentMakeCall : public SIPCCMsg_UState
{
	SIPCCMessage_UState_WpAgentMakeCall();
	~SIPCCMessage_UState_WpAgentMakeCall()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}

	string agentID;
	string CorpName;
	string UUIData;
	string callerNoForSend;
	string outdialPrefixNo;
	string AgentLineNo;
	unsigned long agentLineIp;
	unsigned short agentLinePort;
	string theParty;
	int thePartyType;
	string otherParty;
	int otherPartyType;
	char needPreConnect;
	char needPreRecord;

	string gatewayName;

	string computerSymbol;

private:
	virtual int GetMyMemSize();
};

/// Type_Gateway_WpAgentCallAnswerred
struct SIPCCMsg_Gateway_WpAgentCallAnswerred : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_WpAgentCallAnswerred();
	~SIPCCMsg_Gateway_WpAgentCallAnswerred()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}

	string agentID;
	string gwAgentLineNo;
	string gwUserLineNo;
	unsigned long gwAgentLineIp;
	unsigned short gwAgentLinePort;
	unsigned long gwUserLineIp;
	unsigned short gwUserLinePort;
	string  managerId;

private:
	virtual int GetMyMemSize();
};

/// Type_ACD_ResetDataCollect
struct SIPCCMsg_ACD_ResetDataCollect : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_ResetDataCollect();
	~SIPCCMsg_ACD_ResetDataCollect()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}

	string curTime;

private:
	virtual int GetMyMemSize();
};

/// Type_ACD_ResetMonitor
struct SIPCCMsg_ACD_ResetMonitor : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_ResetMonitor();
	~SIPCCMsg_ACD_ResetMonitor()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}

	string curTime;

private:
	virtual int GetMyMemSize();
};

///////////////////////////////////////////////////////////////////////////
///Class_AreaCode
struct SIPCCMsg_AreaCode : public SIPCCMessage
{
	SIPCCMsg_AreaCode();
	~SIPCCMsg_AreaCode()
	{
		ReleaseMemory();
	};

	virtual int GetMyMemSize(){return 0;}
	virtual int FillBuf(char*& thebuf){return 0;}
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0){}
	virtual void ReleaseMemory(){}
};

///Type_AreaCode_AreaQuery
struct SIPCCMsg_AreaQuery : public SIPCCMsg_AreaCode
{
	SIPCCMsg_AreaQuery();
	~SIPCCMsg_AreaQuery()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}

	string strPhoneNum; // 12593|13718585618 必须有前缀，没有前缀可以使用 null|13718585618 形式
	string strInvokeId;

	int iOperationType;
	string managerid;
	string deptName;
	string agentName;

private:
	virtual int GetMyMemSize();
};

///Type_AreaCode_AreaAnswer
struct SIPCCMsg_AreaAnswer : public SIPCCMsg_AreaCode
{
	SIPCCMsg_AreaAnswer();
	~SIPCCMsg_AreaAnswer()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}

	string strPhoneInfo;	// ProvinceName=北京|CityName=北京|ISPName=联通|Brand=如意通卡|AreaCode=010|IsPrefixResult=1
	//string limitVersion;	// 最低版本要求
	//string limitVersion_Ocx;// 客户端Ocx最低版本要求
	//string limitVersion_GUI;// 客户端GUI最低版本要求
	string strInvokeId;

	int iDialAuthorize;

private:
	virtual int GetMyMemSize();
};

///Type_OutDial_GwLogin
struct SIPCCMsg_OutDial_GwLogin : public SIPCCMsg_OutDial
{
	SIPCCMsg_OutDial_GwLogin();
	~SIPCCMsg_OutDial_GwLogin()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}

	int GwId;
	int LineCount;

private:
	virtual int GetMyMemSize();
};

///Type_Client_QueryNowVersion
struct SIPCCMsg_Client_QueryNowVersion : public SIPCCMsg_Client
{
	SIPCCMsg_Client_QueryNowVersion();
	~SIPCCMsg_Client_QueryNowVersion()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}

	string curVersion;		// 客户端当前版本
	string curVersion_Ocx;	// 客户端Ocx当前版本
	string curVersion_GUI;  // 客户端GUI当前版本
	string agentId;              
	string managerId;
	string lastLoginTime;

private:
	virtual int GetMyMemSize();
};

///Type_Client_UserReLoginStateSvr
struct SIPCCMsg_Client_UserReLoginStateSvr : public SIPCCMsg_Client
{
	SIPCCMsg_Client_UserReLoginStateSvr();
	~SIPCCMsg_Client_UserReLoginStateSvr()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		if(userName!=NULL)	delete userName;
		userName = NULL;
		userNameLen = 0;
		natType = NatType_Unknown;
	}
	void SetUserName(string userName);
	string GetUserName()	
	{
		if(userNameLen==0)	return "";
		if ( (userNameLen>USERNAME_LEN)||(userNameLen<0) ) return "";
		return string(userName);
	}

	int natType;
	unsigned long localIP;
	unsigned short localPort;
private:
	char* userName;
	int userNameLen; 

	virtual int GetMyMemSize();
};

///Type_AreaCode_QueryNowVersionConf
struct SIPCCMsg_AreaCode_QueryNowVersionConf : public SIPCCMsg_AreaCode
{
	SIPCCMsg_AreaCode_QueryNowVersionConf();
	~SIPCCMsg_AreaCode_QueryNowVersionConf()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}

	string limitVersion;         // 客户端Service最低版本要求
	string limitVersion_Ocx;     // 客户端Ocx最低版本要求
	string limitVersion_GUI;     // 客户端GUI最低版本要求
	char haveForceUpdatePower;   // 客户端是否具备强制自动更新权限

private:
	virtual int GetMyMemSize();
};

///Type_Gateway_IVRStat
struct SIPCCMsg_Gateway_IVRStat : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_IVRStat();
	~SIPCCMsg_Gateway_IVRStat()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}

	int nTime;               //当前时间(组合信令时的时间) 32位time_t
	string  strCallerId;     //客户号码
	string  strCalleeId;     //IVR号码
	string  strSessionId;    //会话ID
	string  strServiceName;  //业务名
	int     nStayTime;       //驻留时间 单位秒
	int     nEnterTime;      //进入时间 32位time_t
	int nLeaveTime;          //离开时间 32位time_t
private:
	virtual int GetMyMemSize();
public:
};
///////////////////////////////////////////////////////////////////////////
///Class_alarm
struct SIPCCMsg_alarm : public SIPCCMessage
{
	SIPCCMsg_alarm(){msgClass = Class_alarm;};
	~SIPCCMsg_alarm()
	{
		ReleaseMemory();
	};

	virtual int GetMyMemSize(){return 0;}
	virtual int FillBuf(char*& thebuf){return 0;}
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0){}
	virtual void ReleaseMemory(){}
};
enum enAlarmType{ 
	alarmTypeInvalid=0,
	alarmTypeSms=1,
};

///Type_alarm_alarmRequest
struct SIPCCMsg_alarmRequest : public SIPCCMsg_alarm
{
	SIPCCMsg_alarmRequest()
	{
		msgType = Type_alarm_alarmRequest;
		nLevel=alarmTypeInvalid;
		nComponentId = -1;
	};
	~SIPCCMsg_alarmRequest()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}

	string strComponentName;	// 构件名字
	int	nLevel;					// 级别
	int nErrorNo;				// 错误代码
	string strDescription;		// 错误描述
	int nComponentId;			// 构件id

private:
	virtual int GetMyMemSize();
};

//////////////////////////////////////////////////////////////////////////
// begin [5/31/2011 lixg]
///Class_AgentRecord
struct SIPCCMsg_AgentRecord : public SIPCCMessage
{
	SIPCCMsg_AgentRecord();
	~SIPCCMsg_AgentRecord()
	{
		ReleaseMemory();
	};

	virtual int GetMyMemSize(){return 0;}
	virtual int FillBuf(char*& thebuf){return 0;}
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0){}
	virtual void ReleaseMemory(){}
};

///Type_Record_AgentRecordQuertPort
struct SIPCCMsg_Record_AgentRecordQueryPort : public SIPCCMsg_AgentRecord
{
	SIPCCMsg_Record_AgentRecordQueryPort();
	~SIPCCMsg_Record_AgentRecordQueryPort()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{

	}

	string strInvokeID;				//呼叫事务ID
	int nSeq;						//同一个invokeID的计数标记
	string strPresideAgentAccount;		//主动方座席账号

	CAudioStreamDescription audioStreamDescription;
private:
	virtual int GetMyMemSize();
};
struct SIPCCMsg_Record_AgentRecordQueryPortConf : public SIPCCMsg_AgentRecord
{
	SIPCCMsg_Record_AgentRecordQueryPortConf();
	~SIPCCMsg_Record_AgentRecordQueryPortConf()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{

	}

	string strInvokeID;				//呼叫事务ID
	int nSeq;						//同一个invokeID的计数标记
	string strPresideAgentAccount;		//主动方座席账号
	int nPort;							//分配的port

	int	iResult;	//默认是0，表示不支持；1则表示支持
private:
	virtual int GetMyMemSize();
};
struct SIPCCMsg_Record_AgentRecordStart : public SIPCCMsg_AgentRecord
{
	SIPCCMsg_Record_AgentRecordStart();
	~SIPCCMsg_Record_AgentRecordStart()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{

	}

	string strInvokeID;				//呼叫事务ID
	int nSeq;						//同一个invokeID的计数标记
	string strPresideAgentAccount;		//主动方座席账号
	string strOpTalkingAgentAccount;	//被动席间通话的座席账号
	string strStartTime;					//席间通话开始时间
	string strRecServerSymbol;		//录音服务器标识
	string strPresideAgentNickname;	//主动方座席昵称
	string strOpTalkingAgentNickname;	//被动席间通话的座席昵称
	string strManagerid;	// 主动方坐席所在公司id
	string PresidePhoneNo;			//呼叫相关电话
	int RecordMode;					//录音模式

	int	iCallType;					//默认是0，即AgentToAgent；1为AgentToCClient；2为CClientToAgent；3为CClientToCClient；
	
private:
	virtual int GetMyMemSize();
};
struct SIPCCMsg_Record_AgentRecordStop : public SIPCCMsg_AgentRecord
{
	SIPCCMsg_Record_AgentRecordStop();
	~SIPCCMsg_Record_AgentRecordStop()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{

	}

	string strInvokeID;				//呼叫事务ID
	int nSeq;						//同一个invokeID的计数标记
	string stopTime;		
	string strPresideAgentAccount;
	bool callEstablished;
private:
	virtual int GetMyMemSize();
};
// end [5/31/2011 lixg]
//////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
///Class_alarm
struct SIPCCMsg_ServerProxy : public SIPCCMessage
{
	SIPCCMsg_ServerProxy(){msgClass = Class_ServerProxy;};
	~SIPCCMsg_ServerProxy()
	{
		ReleaseMemory();
	};

	virtual int GetMyMemSize(){return 0;}
	virtual int FillBuf(char*& thebuf){return 0;}
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0){}
	virtual void ReleaseMemory(){}
};


struct SIPCCMsg_ServerProxy_LoadServerInfo : public SIPCCMsg_ServerProxy
{
	SIPCCMsg_ServerProxy_LoadServerInfo();
	~SIPCCMsg_ServerProxy_LoadServerInfo()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{

	}
    string     InvokeID;//ID
	string     managerid;
	string     acdserverid;
	int        indexnum;
private:
	virtual int GetMyMemSize();
};

struct SamplerReportData
{
	string sSampleData;//格式：samplerid:counterid,countvalid,countvalType,time,countval,time,countval....;counterid,countvalid,countvalType,time,countval,time,countval....;
};

struct SIPCCMSG_SAMPLER : public SIPCCMessage
{
	SIPCCMSG_SAMPLER()
	{
		this->msgClass = Class_SAMPLER;
	}
	virtual ~SIPCCMSG_SAMPLER()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf){ return 0;}
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0){}
	virtual void ReleaseMemory(){}
	virtual int GetMyMemSize(){ return 0;}
	
};

struct SIPCCMSG_SAMPLER_REPORT : public SIPCCMSG_SAMPLER
{
	SIPCCMSG_SAMPLER_REPORT();
	virtual ~SIPCCMSG_SAMPLER_REPORT()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory();
	
	void SetSamplerRepData(const SamplerReportData& samplerRepData);
	SamplerReportData GetSamplerRepData();
private:
	virtual int GetMyMemSize();
	
public:
	SamplerReportData m_samplerRepData; 
};

struct SIPCCMSG_SAMPLER_NETDELAY : public SIPCCMSG_SAMPLER
{
	SIPCCMSG_SAMPLER_NETDELAY();
	virtual ~SIPCCMSG_SAMPLER_NETDELAY()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory();
	
private:
	virtual int GetMyMemSize();
	
public:
	SamplerReportData m_samplerRepData; 
	ULONG m_uTimeSendClinet,m_uTimeRecClinet,m_uTimeSendSrv,m_uTimeRecSrv;
	int m_nId;
};

struct SamplerData
{
	string strategy;   //格式：坐席id，客户端标识samplerid：指标（cpu）counterid,countervalid，策略（间隔多长时间进行此指标的采集），采集时间间隔，报告时间间隔；下一指标。。。
};

struct SIPCCMSG_ACD_SAMPLER_Query : public SIPCCMSG_SAMPLER
{
	SIPCCMSG_ACD_SAMPLER_Query();
	virtual ~SIPCCMSG_ACD_SAMPLER_Query()
	{
		ReleaseMemory();
	};	
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory();
	
	void SetSamplerData(const SamplerData& samplerData);
	void GetSamplerData(SamplerData& samplerData);
	
private:
	virtual int GetMyMemSize();
	
public:
	SamplerData m_samplerData;
};

struct SIPCCMSG_ACD_SAMPLER_Agreed : public SIPCCMSG_SAMPLER
{
	SIPCCMSG_ACD_SAMPLER_Agreed();
	virtual ~SIPCCMSG_ACD_SAMPLER_Agreed()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory();
	
	void SetSamplerData(const SamplerData& samplerData);
	void GetSamplerData(SamplerData& samplerData);
	
private:
	virtual int GetMyMemSize();
	
public:
	SamplerData m_samplerData;
};

struct SIPCCMSG_SAMPLER_Query : public SIPCCMSG_SAMPLER
{
	SIPCCMSG_SAMPLER_Query();
	virtual ~SIPCCMSG_SAMPLER_Query()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory();
	
	void SetSamplerData(const SamplerData& samplerData);
	void GetSamplerData(SamplerData& samplerData);
	
private:
	virtual int GetMyMemSize();
	
public:
	SamplerData m_samplerData;
};

struct SIPCCMSG_SAMPLER_Agreed : public SIPCCMSG_SAMPLER
{
	SIPCCMSG_SAMPLER_Agreed();
	virtual ~SIPCCMSG_SAMPLER_Agreed()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory();
	
	void SetSamplerData(const SamplerData& samplerData);
	void GetSamplerData(SamplerData& samplerData);
	
private:
	virtual int GetMyMemSize();
	
public:
	SamplerData m_samplerData;
};

struct SIPCCMSG_OutDial_SetOutdialGroup : public SIPCCMsg_OutDial
{
	SIPCCMSG_OutDial_SetOutdialGroup();
	virtual ~SIPCCMSG_OutDial_SetOutdialGroup()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();

public:
	string GroupName;
};

///////////////////////////////////////////////////////////////////////////
///Call Control
struct SIPCCMsg_CallControl : public SIPCCMessage
{
	SIPCCMsg_CallControl(){msgClass = Class_CallControl;};
	~SIPCCMsg_CallControl()
	{
		ReleaseMemory();
	};

	virtual int GetMyMemSize(){return 0;}
	virtual int FillBuf(char*& thebuf){return 0;}
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0){}
	virtual void ReleaseMemory(){}
};


struct SIPCCMsg_CallControl_RegisterGateway : public SIPCCMsg_CallControl
{
	string gateway_name;		//注册的网关名
	//unsigned int expire_time;	

	SIPCCMsg_CallControl_RegisterGateway(){
		msgType = Type_CallControl_GetTrunkGroupSetting;
	};

	~SIPCCMsg_CallControl_RegisterGateway()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};

struct SIPCCMsg_CallControl_SetTrunkSetting : public SIPCCMsg_CallControl
{
	string gateway_name;	
	map<string,unsigned int> trunk_setting;

	SIPCCMsg_CallControl_SetTrunkSetting(){
		msgType = Type_CallControl_SetTrunkGroupSetting;
	};

	~SIPCCMsg_CallControl_SetTrunkSetting()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){
		//trunk_setting will release its storage
	};

private:
	virtual int GetMyMemSize();
};

struct SIPCCMsg_CallControl_KeepAlive : public SIPCCMsg_CallControl
{
	string gateway_name;	

	SIPCCMsg_CallControl_KeepAlive(){
		msgType = Type_CallControl_KeepAlive;
	};

	~SIPCCMsg_CallControl_KeepAlive()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};

struct SIPCCMsg_CallControl_CallDetail : public SIPCCMsg_CallControl
{
	string src_gateway_name;
	string called_number;
	string calling_number;
	string orig_time;
	
	SIPCCMsg_CallControl_CallDetail(){
		msgType = Type_CallControl_CallDetail;
	};

	~SIPCCMsg_CallControl_CallDetail()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};

struct SIPCCMSG_OutDial_ExitOutDial : public SIPCCMsg_OutDial
{
	SIPCCMSG_OutDial_ExitOutDial()
	{
		msgType = Type_OutDial_ExitOutDial;
	};

	virtual ~SIPCCMSG_OutDial_ExitOutDial()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();

public:
	string AgentId;
};

struct SIPCCMSG_OutDial_JoinOutDial : public SIPCCMsg_OutDial
{
	SIPCCMSG_OutDial_JoinOutDial()
	{
		msgType = Type_OutDial_JoinOutDial;
	};

	virtual ~SIPCCMSG_OutDial_JoinOutDial()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();

public:
	string AgentId;
};

struct SIPCCMSG_SysManage_MoveAgent : public SIPCCMsg_SysManage
{
	SIPCCMSG_SysManage_MoveAgent()
	{
		msgType = Type_SysManage_MoveAgent;
	};

	virtual ~SIPCCMSG_SysManage_MoveAgent()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();

public:
	string DeptmentId;
	string AgentList;
	string IsOutdial;
};

struct SIPCCMSG_ACD_SwitchDept : public SIPCCMsg_ACD
{
	SIPCCMSG_ACD_SwitchDept()
	{
		msgType = Type_ACD_SwitchDept;
	};

	virtual ~SIPCCMSG_ACD_SwitchDept()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();

public:
	string Corp;
	string Dept;
	int IsOutdial;
};

struct SIPCCMsg_DIDControl : public SIPCCMessage
{
	SIPCCMsg_DIDControl()
	{
		msgClass = Class_DIDControl;
	};

	~SIPCCMsg_DIDControl()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf) = 0;
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0) = 0;
	virtual void ReleaseMemory(){};
};


struct SIPCCMsg_DIDControl_QueryGatewayConfig : public SIPCCMsg_CallControl
{
	string gateway_name;	

	SIPCCMsg_DIDControl_QueryGatewayConfig(){
		msgType = Type_DIDControl_QueryGatewayConfig;
	};

	~SIPCCMsg_DIDControl_QueryGatewayConfig()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};

struct SIPCCMsg_DIDControl_Response : public SIPCCMsg_CallControl
{
	int				_size;
	unsigned int	_seq;	//_seq begins at 0 end at -1 , recving -1 means this is last
	vector<string>	_did_num;
	//vector<string>	_corp_name;
	vector<string>	_tts_stg;
	
	SIPCCMsg_DIDControl_Response(){
		msgType = Type_DIDControl_Response;
	};

	~SIPCCMsg_DIDControl_Response()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){
		//trunk_setting will release its storage
	};

private:
	virtual int GetMyMemSize();
};

struct SIPCCMsg_DIDControl_QueryDIDConfig : public SIPCCMsg_CallControl
{
	string _did_num;	

	SIPCCMsg_DIDControl_QueryDIDConfig(){
		msgType = Type_DIDControl_QueryGatewayConfig;
	};

	~SIPCCMsg_DIDControl_QueryDIDConfig()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};

///////////////////////////////////////////////////////////////////////////
///OneKeySwitch
struct SIPCCMsg_OneKeySwitch : public SIPCCMessage
{
	SIPCCMsg_OneKeySwitch(){msgClass = Class_OneKeySwitch;};
	~SIPCCMsg_OneKeySwitch()
	{
		ReleaseMemory();
	};

	virtual int GetMyMemSize(){return 0;}
	virtual int FillBuf(char*& thebuf){return 0;}
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0){}
	virtual void ReleaseMemory(){}
};

struct SIPCCMsg_OneKeySwitch_HeartBeatRegister : public SIPCCMsg_OneKeySwitch		//心跳服务注册
{
	string ServerName;
	unsigned long ServerIp;
	unsigned short ServerPort;
	int ServerType;		//0:用户端;1:网关

	SIPCCMsg_OneKeySwitch_HeartBeatRegister(){
		msgType = Type_OneKeySwitch_HeartBeatRegister;
	};

	~SIPCCMsg_OneKeySwitch_HeartBeatRegister()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};

struct SIPCCMsg_OneKeySwitch_GetServerHeartBeatServer : public SIPCCMsg_OneKeySwitch		//获取网关心跳服务
{
	string InvokeId;
	bool IsCtrl;

	SIPCCMsg_OneKeySwitch_GetServerHeartBeatServer(){
		msgType = Type_OneKeySwitch_GetServerHeartBeatServer;
	};

	~SIPCCMsg_OneKeySwitch_GetServerHeartBeatServer()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};

struct SIPCCMsg_OneKeySwitch_GetServerHeartBeatServerConf : public SIPCCMsg_OneKeySwitch	//获取网关心跳服务回应
{
	string InvokeId;
	map<string, pair<unsigned long, unsigned short> > ServerList;

	SIPCCMsg_OneKeySwitch_GetServerHeartBeatServerConf(){
		msgType = Type_OneKeySwitch_GetServerHeartBeatServerConf;
	};

	~SIPCCMsg_OneKeySwitch_GetServerHeartBeatServerConf()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};

struct SIPCCMsg_OneKeySwitch_GetClientHeartBeatServer : public SIPCCMsg_OneKeySwitch		//获取坐席心跳服务
{
	string InvokeId;
	bool IsCtrl;

	SIPCCMsg_OneKeySwitch_GetClientHeartBeatServer(){
		msgType = Type_OneKeySwitch_GetClientHeartBeatServer;
	};

	~SIPCCMsg_OneKeySwitch_GetClientHeartBeatServer()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};

struct SIPCCMsg_OneKeySwitch_GetClientHeartBeatServerConf : public SIPCCMsg_OneKeySwitch	//获取坐席心跳服务回应
{
	string InvokeId;
	map<string, pair<unsigned long, unsigned short> > ServerList;

	SIPCCMsg_OneKeySwitch_GetClientHeartBeatServerConf(){
		msgType = Type_OneKeySwitch_GetClientHeartBeatServerConf;
	};

	~SIPCCMsg_OneKeySwitch_GetClientHeartBeatServerConf()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};

struct SIPCCMsg_OneKeySwitch_ServerHeartBeat : public SIPCCMsg_OneKeySwitch			//网关心跳
{
	string GwName;
	string ComputerSymbol;
	int ServerType;		//0: SoftACDServer; 1: DataGwServer; 2: TollTransactionServer
	unsigned long GwManagerServerIp;	//此处酌情添加
	int ServiceID;


	int Service1ID;			//顺序填写与发送方相关构件信息
	int Service1Type;
	int Service2ID;
	int Service2Type;
	int Service3ID;
	int Service3Type;
	int Service4ID;
	int Service4Type;
	unsigned long sendtime;
	int isProxyRegister;			//默认为0，表示仅作为网关心跳服务；为1表示其作为网关主代理服							//务；为2作为网关备份代理服务；

	SIPCCMsg_OneKeySwitch_ServerHeartBeat(){
		msgType = Type_OneKeySwitch_ServerHeartBeat;
		GwName="";
		ComputerSymbol="";
		GwManagerServerIp=0;
		ServiceID=0;

		Service1ID=0;			//顺序填写与发送方相关构件信息
		Service1Type=0;
		Service2ID=0;
		Service2Type=0;
		Service3ID=0;
		Service3Type=0;
		Service4ID=0;
		Service4Type=0;
		sendtime=0;
		isProxyRegister=0;
	};

	~SIPCCMsg_OneKeySwitch_ServerHeartBeat()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};

struct SIPCCMsg_OneKeySwitch_ClientHeartBeat : public SIPCCMsg_OneKeySwitch			//坐席心跳
{
	string AgentName;//维一值
	string ManagerId;
	string AcdServerId;  //废弃
	unsigned long AcdServerIp;//废弃
	unsigned short AcdServerPort;//废弃
	bool GetConf;


	int ACDServerID;
	int UStateServerID;
	int GWManageServerID;
	int AreaCodeServerID;


	SIPCCMsg_OneKeySwitch_ClientHeartBeat(){
		msgType = Type_OneKeySwitch_ClientHeartBeat;
		ACDServerID=0;
	    UStateServerID=0;
	    GWManageServerID=0;
	    AreaCodeServerID=0;
	};

	~SIPCCMsg_OneKeySwitch_ClientHeartBeat()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};

struct SIPCCMsg_OneKeySwitch_ClientHeartBeatConf : public SIPCCMsg_OneKeySwitch			//坐席心跳
{
	string ServerName;

	SIPCCMsg_OneKeySwitch_ClientHeartBeatConf(){
		msgType = Type_OneKeySwitch_ClientHeartBeatConf;
	};

	~SIPCCMsg_OneKeySwitch_ClientHeartBeatConf()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};

struct SIPCCMsg_OneKeySwitch_GetGwList : public SIPCCMsg_OneKeySwitch			//坐席心跳
{
	string InvokeId;

	SIPCCMsg_OneKeySwitch_GetGwList(){
		msgType = Type_OneKeySwitch_GetGwList;
	};

	~SIPCCMsg_OneKeySwitch_GetGwList()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};

struct SIPCCMsg_OneKeySwitch_GetGwListConf : public SIPCCMsg_OneKeySwitch			//坐席心跳
{
	string InvokeId;
	string GwName;
	string ComputerSymbol;
	unsigned long GwManagerServerIp;

	SIPCCMsg_OneKeySwitch_GetGwListConf(){
		msgType = Type_OneKeySwitch_GetGwListConf;
	};

	~SIPCCMsg_OneKeySwitch_GetGwListConf()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};

struct SIPCCMsg_OneKeySwitch_GetAcdList : public SIPCCMsg_OneKeySwitch			//坐席心跳
{
	string InvokeId;

	SIPCCMsg_OneKeySwitch_GetAcdList(){
		msgType = Type_OneKeySwitch_GetAcdList;
	};

	~SIPCCMsg_OneKeySwitch_GetAcdList()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};

struct SIPCCMsg_OneKeySwitch_GetAcdListConf : public SIPCCMsg_OneKeySwitch			//坐席心跳
{
	string InvokeId;
	string AcdServerId;
	unsigned long AcdServerIp;
	unsigned short AcdServerPort;
	vector<string> ManagerIdList;

	SIPCCMsg_OneKeySwitch_GetAcdListConf(){
		msgType = Type_OneKeySwitch_GetAcdListConf;
	};

	~SIPCCMsg_OneKeySwitch_GetAcdListConf()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};

struct SIPCCMsg_OneKeySwitch_SwitchCenter_Ctrl : public SIPCCMsg_OneKeySwitch			//坐席心跳
{
	string InvokeId;
	unsigned long UStateServerIp;
	unsigned short UStateServerPort;
	unsigned long GwmanagerServerIp;
	unsigned short GwmanagerServerPort;
	unsigned long DataCenterServerIp;
	unsigned short DataCenterServerPort;
	unsigned long ACDServerIp;
	unsigned short ACDServerPort;
	unsigned long ProxyServerIp;
	unsigned short ProxyServerPort;
	unsigned long TollServerIp;
	unsigned short TollServerPort;
	unsigned long GuideServerIp;
	unsigned short GuideServerPort;

	unsigned long MonitiorServerIp;
	unsigned short MonitiorServerPort;

	SIPCCMsg_OneKeySwitch_SwitchCenter_Ctrl(){
		msgType = Type_OneKeySwitch_SwitchCenter_Ctrl;
	};

	~SIPCCMsg_OneKeySwitch_SwitchCenter_Ctrl()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};

struct SIPCCMsg_OneKeySwitch_SwitchAcd_Ctrl : public SIPCCMsg_OneKeySwitch			//坐席心跳
{
	string InvokeId;
	string ManagerId; 
	string AcdServerId;//废弃
	unsigned long AcdServerIp;
	unsigned short AcdServerPort;

	string AcdServerIp_Old;			//用于描述原ACDServer的内网IP  //废弃
	string AcdServerIP_New;		//用于描述新ACDServer的内网IP//废弃
	string AcdServerWanIP_New;	//用于描述新ACDServer的公网IP//废弃

	int ServiceID_Old;	            //（managerid=””）	//用于描述原ACDServer的ServiceID
    int ServiceID_New;					   //用于描述新ACDServer的ServiceID

     int IsReload;							//当SIPCCMsg_SysManage_SwitchAcdConf返回不全时，重新发送		0表示首次申请，1表示收取申请回应完整，2表示收取申请回应不完整
    int indexnum;//转化序号
	SIPCCMsg_OneKeySwitch_SwitchAcd_Ctrl(){
		msgType = Type_OneKeySwitch_SwitchAcd_Ctrl;
		ServiceID_Old=0;
		ServiceID_New=0;
		IsReload=0;
		indexnum=0;

	};

	~SIPCCMsg_OneKeySwitch_SwitchAcd_Ctrl()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};

struct SIPCCMsg_OneKeySwitch_SwitchRedirect_Ctrl : public SIPCCMsg_OneKeySwitch			//坐席心跳
{
	string InvokeId;
	unsigned long ServerIp;
	unsigned short ServerPort;

	SIPCCMsg_OneKeySwitch_SwitchRedirect_Ctrl(){
		msgType = Type_OneKeySwitch_SwitchRedirect_Ctrl;
	};

	~SIPCCMsg_OneKeySwitch_SwitchRedirect_Ctrl()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};

struct SIPCCMsg_OneKeySwitch_SwitchCenter : public SIPCCMsg_OneKeySwitch			//坐席心跳
{
	string InvokeId;
	unsigned long UStateServerIp;
	unsigned short UStateServerPort;
	unsigned long GwmanagerServerIp;
	unsigned short GwmanagerServerPort;
	unsigned long DataCenterServerIp;
	unsigned short DataCenterServerPort;
	unsigned long ACDServerIp;
	unsigned short ACDServerPort;
	unsigned long ProxyServerIp;
	unsigned short ProxyServerPort;
	unsigned long TollServerIp;
	unsigned short TollServerPort;
	unsigned long GuideServerIp;
	unsigned short GuideServerPort;

	unsigned long MonitiorServerIp;
	unsigned short MonitiorServerPort;


	SIPCCMsg_OneKeySwitch_SwitchCenter(){
		msgType = Type_OneKeySwitch_SwitchCenter;
	};

	~SIPCCMsg_OneKeySwitch_SwitchCenter()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};

struct SIPCCMsg_OneKeySwitch_SwitchAcd : public SIPCCMsg_OneKeySwitch			//坐席心跳
{
	string InvokeId;
	string AcdServerId;
	unsigned long AcdServerIp;
	unsigned short AcdServerPort;
	int ServiceID;

	SIPCCMsg_OneKeySwitch_SwitchAcd()
	{
		msgType = Type_OneKeySwitch_SwitchAcd;
		InvokeId="";
	    AcdServerId="";
	    AcdServerIp=0;
	    AcdServerPort=0;
	    ServiceID=0;
	};

	~SIPCCMsg_OneKeySwitch_SwitchAcd()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};

struct SIPCCMsg_OneKeySwitch_SwitchRedirect : public SIPCCMsg_OneKeySwitch			//坐席心跳
{
	string InvokeId;
	unsigned long ServerIp;
	unsigned short ServerPort;

	SIPCCMsg_OneKeySwitch_SwitchRedirect(){
		msgType = Type_OneKeySwitch_SwitchRedirect;
	};

	~SIPCCMsg_OneKeySwitch_SwitchRedirect()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};

///Type_OneKeySwitch_UserLoginStateSvrConf
struct SIPCCMsg_OneKeySwitch_UserLoginStateSvrConf : public SIPCCMsg_OneKeySwitch			
{
	SIPCCMsg_OneKeySwitch_UserLoginStateSvrConf();
	~SIPCCMsg_OneKeySwitch_UserLoginStateSvrConf()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

	string GwName;
	string ComputerSymbol;
	int resultCode;		//0表示注册信息不全（分包丢失引起），1表示注册信息齐全

	string ServerName;
	int ServiceType;
	int ServiceID; 
    string handleId;

	unsigned long originalIP;

	unsigned short originalPort;

private:
	virtual int GetMyMemSize();
};

///Type_OneKeySwitch_ConfirmGW
struct SIPCCMsg_OneKeySwitch_ConfirmGW : public SIPCCMsg_OneKeySwitch		
{
	SIPCCMsg_OneKeySwitch_ConfirmGW();
	~SIPCCMsg_OneKeySwitch_ConfirmGW()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

	string GwName;
	string ComputerSymbol;
	string InvokeId;

private:
	virtual int GetMyMemSize();
};

///Type_OneKeySwitch_HeartBeatConfirmConf
struct SIPCCMsg_OneKeySwitch_HeartBeatConfirmConf : public SIPCCMsg_OneKeySwitch
{
	SIPCCMsg_OneKeySwitch_HeartBeatConfirmConf();
	~SIPCCMsg_OneKeySwitch_HeartBeatConfirmConf()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}

	string invokeID;

	int ServiceID;
private:
	virtual int GetMyMemSize();
};

///Type_OneKeySwitch_GetHeartBeatConf
struct SIPCCMsg_OneKeySwitch_GetHeartBeatConf : public SIPCCMsg_OneKeySwitch
{
	SIPCCMsg_OneKeySwitch_GetHeartBeatConf();
	~SIPCCMsg_OneKeySwitch_GetHeartBeatConf()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		InvokeId = "";
		HeartBeatServerIP = 0;
		HeartBeatServerPort = 0;
		HeartBeatServerBackupIP = 0;
		HeartBeatServerBackupPort = 0;
		
		HeartBeatServerID=0;
		HeartBeatServerBackupID=0;
		
	}

	string InvokeId;
	unsigned long HeartBeatServerIP;
	unsigned short HeartBeatServerPort;
	unsigned long HeartBeatServerBackupIP;
	unsigned short HeartBeatServerBackupPort;

	int         ServiceID;
    int          ServiceType;//（类型） 来时有值根据标识

	int        HeartBeatServerID;
	int        HeartBeatServerBackupID;
    int        operationMode;//默认为2，表示须有两个心跳服务；为0表示无心跳服务；

private:
	virtual int GetMyMemSize();
};

///Type_OneKeySwitch_GWLogout
struct SIPCCMsg_OneKeySwitch_GWLogout : public SIPCCMsg_OneKeySwitch			
{
	SIPCCMsg_OneKeySwitch_GWLogout();
	~SIPCCMsg_OneKeySwitch_GWLogout()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

	string GwName;
	string ComputerSymbol;

private:
	virtual int GetMyMemSize();
};

///Type_OneKeySwitch_RegisterConf
struct SIPCCMsg_OneKeySwitch_RegisterConf : public SIPCCMsg_OneKeySwitch
{
	SIPCCMsg_OneKeySwitch_RegisterConf();
	~SIPCCMsg_OneKeySwitch_RegisterConf()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}

	string ServerName;
private:
	virtual int GetMyMemSize();
};

///Type_OneKeySwitch_GWLogin
struct SIPCCMsg_OneKeySwitch_GWLogin : public SIPCCMsg_OneKeySwitch
{
	SIPCCMsg_OneKeySwitch_GWLogin();
	~SIPCCMsg_OneKeySwitch_GWLogin()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

	string gwName;
	string computerSymbol;
	int trunkCount;
	unsigned long lanIP;
	unsigned short lanPort;
	string gwPartNo;
	int natType;
	unsigned long natIP;
	unsigned short natPort;
	int ConferenceAgentCount;

	unsigned long natIP_backup;			//网关备份代理服务的公网IP
	unsigned short natPort_backup;		//网关备份代理服务的端口号
	int isProxyRegister;					//默认为0表示网关直接登录；为1表示网关代理登陆；

private:
	virtual int GetMyMemSize();
};

///Type_OneKeySwitch_UserLogin
struct SIPCCMsg_OneKeySwitch_UserLogin : public SIPCCMsg_OneKeySwitch
{
	SIPCCMsg_OneKeySwitch_UserLogin();
	~SIPCCMsg_OneKeySwitch_UserLogin()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		natType = NatType_Unknown;
	}

	int natType;
	unsigned long localIP;
	unsigned short localPort;
	string GwName;
	string ComputerSymbol;
	string allUserName;
	int	indexNum;
	unsigned long natIP;
	unsigned short natPort;

	string handleId;

	int totalIndex;

private:
	virtual int GetMyMemSize();
};

///Type_OneKeySwitch_GetUSnGWMConf
struct SIPCCMsg_OneKeySwitch_GetUSnGWMConf : public SIPCCMsg_OneKeySwitch
{
	SIPCCMsg_OneKeySwitch_GetUSnGWMConf();
	~SIPCCMsg_OneKeySwitch_GetUSnGWMConf()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		InvokeId = "";
		UStateServerIp = 0;
		UStateServerPort = 0;
		GWManageServerIp = 0;
		GWManageServerPort = 0;
	}

	string InvokeId;
	unsigned long UStateServerIp;
	unsigned short UStateServerPort;
	unsigned long GWManageServerIp;
	unsigned short GWManageServerPort;
private:
	virtual int GetMyMemSize();
};

///Type_OneKeySwitch_LoadGWInfo
struct SIPCCMsg_OneKeySwitch_LoadGWInfo : public SIPCCMsg_OneKeySwitch
{
	SIPCCMsg_OneKeySwitch_LoadGWInfo();
	~SIPCCMsg_OneKeySwitch_LoadGWInfo()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}

	string ServerName;
	string GatewayID;
private:
	virtual int GetMyMemSize();
};

///Type_OneKeySwitch_ServerHeartBeatConf
struct SIPCCMsg_OneKeySwitch_ServerHeartBeatConf : public SIPCCMsg_OneKeySwitch
{
	SIPCCMsg_OneKeySwitch_ServerHeartBeatConf();
	~SIPCCMsg_OneKeySwitch_ServerHeartBeatConf()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}

	int resultCode;
	int ServiceID;
	unsigned long sendtime;
private:
	virtual int GetMyMemSize();
};

///Type_OneKeySwitch_Synchronization
struct SIPCCMsg_OneKeySwitch_Synchronization : public SIPCCMsg_OneKeySwitch
{
	SIPCCMsg_OneKeySwitch_Synchronization();
	~SIPCCMsg_OneKeySwitch_Synchronization()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}

	string invokeID;
private:
	virtual int GetMyMemSize();
};

///Type_OneKeySwitch_USRegister
struct SIPCCMsg_OneKeySwitch_USRegister : public SIPCCMsg_OneKeySwitch
{
	SIPCCMsg_OneKeySwitch_USRegister();
	~SIPCCMsg_OneKeySwitch_USRegister()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

	string ServerName;
	unsigned long ServerIp;
	unsigned short ServerPort;

private:
	virtual int GetMyMemSize();
};

///Type_OneKeySwitch_GWMRegister
struct SIPCCMsg_OneKeySwitch_GWMRegister : public SIPCCMsg_OneKeySwitch
{
	SIPCCMsg_OneKeySwitch_GWMRegister();
	~SIPCCMsg_OneKeySwitch_GWMRegister()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

	string ServerName;
	unsigned long ServerIp;
	unsigned short ServerPort;

private:
	virtual int GetMyMemSize();
};

///Type_OneKeySwitch_GWLoginConf
struct SIPCCMsg_OneKeySwitch_GWLoginConf : public SIPCCMsg_OneKeySwitch			
{
	SIPCCMsg_OneKeySwitch_GWLoginConf();
	~SIPCCMsg_OneKeySwitch_GWLoginConf()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

	string             GwName;
	string             ComputerSymbol;
	string             ServerName;
		
	int               ServiceType;
	int               ServiceID;;


private:
	virtual int GetMyMemSize();
};


struct SIPCCMsg_Licence_Query : public SIPCCMessage
{
	SIPCCMsg_Licence_Query()
	{
		this->msgClass = Class_License;
		this->msgType = Type_Licence_Query;

		LicenceType = -1;
		ServerName = "";
		queryTag ="";
		sysTime = 0;

		countValue = 0;
		bStartQuery = false;
	};

	~SIPCCMsg_Licence_Query()
	{
		ReleaseMemory();
	};

	virtual int GetMyMemSize();
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{

	}

	int LicenceType;
	string ServerName;
	string queryTag;
		
	time_t sysTime;

	long countValue;
	bool bStartQuery;
};


struct SIPCCMsg_Licence_QueryConf : public SIPCCMessage
{
	SIPCCMsg_Licence_QueryConf()
	{
		this->msgClass = Class_License;
		this->msgType = Type_Licence_QueryConf;

		queryTag = "-1";
		LicenceConfirmPassed = '0';
		FailedCause = 1;
	};

	~SIPCCMsg_Licence_QueryConf()
	{
		ReleaseMemory();
	};

	virtual int GetMyMemSize();
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}

	string queryTag;
	char LicenceConfirmPassed;  //(返回值类型：=0验证失败，=1成功)
	int  FailedCause;			//(1表示ServerName或ServerIP验证失败，2代表count已经超出。对于InfobirdACD只要LicenceConfirmPassed=0，即立即停止运行；
								///对于ACDServer若FailedCause =1，则立即停止运行；若FailedCause=2，则后续坐席不允许再登录，直到ACDServer重起才能复位)
};

///Type_OneKeySwitch_SetTrunkDeviecList
struct SIPCCMsg_OneKeySwitch_SetTrunkDeviecList : public SIPCCMsg_OneKeySwitch			
{
	SIPCCMsg_OneKeySwitch_SetTrunkDeviecList();
	~SIPCCMsg_OneKeySwitch_SetTrunkDeviecList()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

	string GwName;
	string ComputerSymbol;
	string TrunkGroupDN;
	string TrunkDeviceListStart;
	string TrunkDeviceListEnd;
	char bCanSelected;	//0为TrunkDeviceListStart到TrunkDeviceListEnd之间的线不可用于外拨，1为可用于外拨；

private:
	virtual int GetMyMemSize();
};

///Type_Gateway_SetTrunkDeviecListConf
struct SIPCCMsg_Gateway_SetTrunkDeviecListConf : public SIPCCMsg_Gateway			
{
	SIPCCMsg_Gateway_SetTrunkDeviecListConf();
	~SIPCCMsg_Gateway_SetTrunkDeviecListConf()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

	string GwName;
	string ComputerSymbol;
	char bSucc;	//0为设置失败，1为设置成功；

private:
	virtual int GetMyMemSize();
};
////////////////////////////////////////////////////////////////////////////////////////////////////////
struct GCTIConnectionID
{
		
		UINT	callID;// 呼叫ID		
		string	deviceID;//设备ID
		GCTIConnectionID() {callID = 0; deviceID="";}
		GCTIConnectionID(const UINT  &callID_In, const string  deviceID_In):
		callID(callID_In), deviceID(deviceID_In)
		{}
};
//GCTI
struct SIPCCMsg_GlobolctiEngine : public SIPCCMessage
{
	SIPCCMsg_GlobolctiEngine()
	{
		msgClass = Class_GCTI;
	};

	~SIPCCMsg_GlobolctiEngine()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf) = 0;
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0) = 0;
	virtual void ReleaseMemory(){};
};
//Type_GCTI_MonitorDevice
struct SIPCCMsg_GCTI_MonitorDevice  : public SIPCCMsg_GlobolctiEngine
{
	string          InvokeId;
	unsigned int    uInvokeId;
	string			monitorQueue;
	string			monitorEvent;
	string          monitoredDevice;
	

	SIPCCMsg_GCTI_MonitorDevice()
	{
		msgType = Type_GCTI_MonitorDevice;
		InvokeId="";
		uInvokeId=0;
		monitorQueue="";
		monitorEvent="";
		monitoredDevice="";
	};

	~SIPCCMsg_GCTI_MonitorDevice()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
//Type_GCTI_GCTI_AnswerCall
struct SIPCCMsg_GCTI_AnswerCall  : public SIPCCMsg_GlobolctiEngine
{
	 string               InvokeId;
	 unsigned int         uInvokeId;
	 GCTIConnectionID     alertingCall;

	SIPCCMsg_GCTI_AnswerCall()
	{
		msgType = Type_GCTI_GCTI_AnswerCall;
		InvokeId="";
		uInvokeId=0;
	};

	~SIPCCMsg_GCTI_AnswerCall()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
//Type_GCTI_GCTI_MakeCall
struct  SIPCCMsg_GCTI_MakeCall: public SIPCCMsg_GlobolctiEngine
{
    string             InvokeId;	
	unsigned int       uInvokeId;
    string	          callingDevice;
	string	          calledDevice;  // problem here!!!(phoneNo_t type is not same as deviceID_t)
	string		      PrivateData;	
    string            userData; 

	 SIPCCMsg_GCTI_MakeCall()
	 {
		msgType = Type_GCTI_GCTI_MakeCall;
		InvokeId="";	
	    uInvokeId=0;
        callingDevice="";
	    calledDevice="";  
	     PrivateData="";	
         userData=""; 
	};

	~ SIPCCMsg_GCTI_MakeCall()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
//Type_GCTI_ClearConnection
struct   SIPCCMsg_GCTI_ClearConnection: public SIPCCMsg_GlobolctiEngine
{
    string              InvokeId;
	unsigned int       uInvokeId;
    GCTIConnectionID    call;
    bool			     ForTimeout;		//是否因为超时引起
	bool			     FromSoftacd;	//是否由Softacd发起

	 SIPCCMsg_GCTI_ClearConnection()
	 {
		msgType = Type_GCTI_ClearConnection;
	};

	~ SIPCCMsg_GCTI_ClearConnection()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
//Type_GCTI_IVRReturnTransferToAgent
struct   SIPCCMsg_GCTI_IVRReturnTransferToAgent: public SIPCCMsg_GlobolctiEngine
{
    string              InvokeId;
	unsigned int        uInvokeId;

    GCTIConnectionID    activeCall;
   	string		        agentDevice;
	string			    privateData;

	 SIPCCMsg_GCTI_IVRReturnTransferToAgent()
	 {
		msgType = Type_GCTI_IVRReturnTransferToAgent;
	};

	~ SIPCCMsg_GCTI_IVRReturnTransferToAgent()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
//Type_GCTI_HoldCall
struct   SIPCCMsg_GCTI_HoldCall: public SIPCCMsg_GlobolctiEngine
{
    string              InvokeId;
	unsigned int        uInvokeId;
    GCTIConnectionID    activeCall;

    string waitMusic;//libh 2007/10/08
	string transedDevice;	//yany 2008/08/25
	string NeedTrunkPreCon;
	string NeedCallerInfo;
	string CallerInfo;
	string NeedTransferInfo;
	string TransferInfo;
	string CallerPlayTimes;
	string TransferPlayTimes;
	string CallerNeedReturnIVR;
	string TransferNeedReturnIVR;
	string NeedHoldnWait;		//是否询问用户需要继续等待
	string PromptTimes;			//提示次数
	string PromptMusicPath;		//提示音文件路径

	 SIPCCMsg_GCTI_HoldCall()
	 {
		msgType = Type_GCTI_HoldCall;
	};

	~ SIPCCMsg_GCTI_HoldCall()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
//Type_GCTI_MonitorConfEvent
struct   SIPCCMsg_GCTI_MonitorConfEvent: public SIPCCMsg_GlobolctiEngine
{
    string              InvokeId;		
   unsigned int         monitorCrossRefID;
   unsigned int         uinvokeID;

   

	 SIPCCMsg_GCTI_MonitorConfEvent()
	 {
		msgType = Type_GCTI_MonitorConfEvent;
	};

	~ SIPCCMsg_GCTI_MonitorConfEvent()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
//Type_GCTI_MakeCallConfEvent
struct   SIPCCMsg_GCTI_MakeCallConfEvent: public SIPCCMsg_GlobolctiEngine
{
	string               InvokeId;		
	GCTIConnectionID     newCall;
	string               ivrStationDN;
	unsigned int         uinvokeID;


	 SIPCCMsg_GCTI_MakeCallConfEvent()
	 {
		msgType = Type_GCTI_MakeCallConfEvent;
	};

	~ SIPCCMsg_GCTI_MakeCallConfEvent()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
//Type_GCTI_UniversalFailureConfEvent
struct   SIPCCMsg_GCTI_UniversalFailureConfEvent: public SIPCCMsg_GlobolctiEngine
{
	string               InvokeId;		
	unsigned int         uinvokeID;
	int                  error;


	 SIPCCMsg_GCTI_UniversalFailureConfEvent()
	 {
		msgType = Type_GCTI_UniversalFailureConfEvent;
	};

	~ SIPCCMsg_GCTI_UniversalFailureConfEvent()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};

//Type_GCTI_GCTI_DeliveredEvent;
struct   SIPCCMsg_GCTI_DeliveredEvent: public SIPCCMsg_GlobolctiEngine
{
	string               InvokeId;
	unsigned int          monitorCrossRefID_t;
	GCTIConnectionID			alertingConnection;
	GCTIConnectionID			originatingConnection;
	string				trunkGroupDevice;
	string				lastRedirectionDevice;
	string				callerNo;
	string				calledNo;
	string				privateData;
	int     		   localConnectionState;
	int  				cause;


	 SIPCCMsg_GCTI_DeliveredEvent()
	 {
		msgType = Type_GCTI_DeliveredEvent;
		localConnectionState=0;
        cause=0;
	};

	~ SIPCCMsg_GCTI_DeliveredEvent()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
///Type_GCTI_EstablishedEvent;
struct   SIPCCMsg_GCTI_EstablishedEvent: public SIPCCMsg_GlobolctiEngine
{
	string               InvokeId;
	unsigned int          monitorCrossRefID_t;

	GCTIConnectionID			establishedConnection;	
	GCTIConnectionID			originatingConnection;
	string				        answeringAgent;			// 用于填充座席ID
	int 		                localConnectionState;
	int 				        cause;



	 SIPCCMsg_GCTI_EstablishedEvent()
	 {
		msgType = Type_GCTI_EstablishedEvent;
		localConnectionState=0;
        cause=0;
	};

	~ SIPCCMsg_GCTI_EstablishedEvent()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
//Type_GCTI_NetworkReachedEvent;
struct   SIPCCMsg_GCTI_NetworkReachedEvent: public SIPCCMsg_GlobolctiEngine
{
	string                 InvokeId;
	unsigned int          monitorCrossRefID_t;

	GCTIConnectionID			outBoundConnection;	
	GCTIConnectionID			originatingConnection;
	string				        calledNo;			// 用于填充座席ID
	int 		                localConnectionState;
	int 				        cause;




	 SIPCCMsg_GCTI_NetworkReachedEvent()
	 {
		msgType = Type_GCTI_NetworkReachedEvent;
		localConnectionState=0;
        cause=0;
	};

	~ SIPCCMsg_GCTI_NetworkReachedEvent()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
//Type_GCTI_ServiceInitiatedEvent;
struct   SIPCCMsg_GCTI_ServiceInitiated: public SIPCCMsg_GlobolctiEngine
{
	string               InvokeId;
	unsigned int          monitorCrossRefID_t;

	GCTIConnectionID			initiatedConnection;
	int 		                localConnectionState;
	int 				        cause;





	 SIPCCMsg_GCTI_ServiceInitiated()
	 {
		msgType = Type_GCTI_ServiceInitiatedEvent;
		localConnectionState=0;
        cause=0;
	};

	~ SIPCCMsg_GCTI_ServiceInitiated()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
//Type_GCTI_HeldEvent;
struct   SIPCCMsg_GCTI_HeldEvent: public SIPCCMsg_GlobolctiEngine
{
	string                         InvokeId;
	unsigned int                   monitorCrossRefID_t;

	GCTIConnectionID			   heldConnection;
	string                         holdDevice;
	int 		                   localConnectionState;
	int 				           cause;



	 SIPCCMsg_GCTI_HeldEvent()
	 {
		msgType = Type_GCTI_HeldEvent;
		localConnectionState=0;
        cause=0;
	};

	~ SIPCCMsg_GCTI_HeldEvent()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
//Type_GCTI_RetrievedEvent;
struct   SIPCCMsg_GCTI_RetrievedEvent: public SIPCCMsg_GlobolctiEngine
{
	string                         InvokeId;
	unsigned int                   monitorCrossRefID_t;

	GCTIConnectionID			   retrievedConnection;
	string                         retrievingDevice;
	int 		                   localConnectionState;
	int 				           cause;
	
	 SIPCCMsg_GCTI_RetrievedEvent()
	 {
		msgType = Type_GCTI_RetrievedEvent;
		localConnectionState=0;
        cause=0;
	};

	~ SIPCCMsg_GCTI_RetrievedEvent()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
//Type_GCTI_TransferredEvent;
struct   SIPCCMsg_GCTI_TransferredEvent: public SIPCCMsg_GlobolctiEngine
{
	string                         InvokeId;
	unsigned int                   monitorCrossRefID_t;

	UINT				           callID;
	string				           transferringDevice;
	string				           transferredDevice;	// 被转移到的设备
	int 		                   localConnectionState;
	int 				           cause;
	int                            listsize;
	list<GCTIConnectionID>		  transferConnections;
	
	 SIPCCMsg_GCTI_TransferredEvent()
	 {
		msgType = Type_GCTI_TransferredEvent;
		localConnectionState=0;
        cause=0;
		transferringDevice="";
		transferredDevice="";

	};

	~ SIPCCMsg_GCTI_TransferredEvent()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
//Type_GCTI_ConnectionClearedEvent;
struct   SIPCCMsg_GCTI_ConnectionClearedEvent: public SIPCCMsg_GlobolctiEngine
{
	string                         InvokeId;
	unsigned int                   monitorCrossRefID_t;

	GCTIConnectionID			   droppedConnection;
	string			               releasingDevice;
	
	int 		                   localConnectionState;
	int 				           cause;
	
	 SIPCCMsg_GCTI_ConnectionClearedEvent()
	 {
		msgType = Type_GCTI_ConnectionClearedEvent;
		monitorCrossRefID_t=0;
		localConnectionState=0;		
        cause=0;
		

	};

	~ SIPCCMsg_GCTI_ConnectionClearedEvent()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
//Type_GCTI_FailedEvent;
struct   SIPCCMsg_GCTI_FailedEvent: public SIPCCMsg_GlobolctiEngine
{
	string                         InvokeId;
	unsigned int                   monitorCrossRefID_t;

	GCTIConnectionID			   failingConnection;
	string			               callingDevice;
	
	int 		                   localConnectionState;
	int 				           cause;




	
	 SIPCCMsg_GCTI_FailedEvent()
	 {
		msgType = Type_GCTI_FailedEvent;
		monitorCrossRefID_t=0;
		localConnectionState=0;
        cause=0;
		

	};

	~ SIPCCMsg_GCTI_FailedEvent()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
//Type_GCTI_OriginatedEvent
struct   SIPCCMsg_GCTI_OriginatedEvent: public SIPCCMsg_GlobolctiEngine
{
	string                         InvokeId;
	unsigned int                   monitorCrossRefID_t;

	GCTIConnectionID			   originatedConnection;
	string			               calledNo;
	
	int 		                   localConnectionState;
	int 				           cause;




	
	 SIPCCMsg_GCTI_OriginatedEvent()
	 {
		msgType = Type_GCTI_OriginatedEvent;
		monitorCrossRefID_t=0;
		localConnectionState=0;
        cause=0;
		

	};

	~ SIPCCMsg_GCTI_OriginatedEvent()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
//Type_GCTI_ForceHangupEvent;
struct   SIPCCMsg_GCTI_ForceHangupEvent: public SIPCCMsg_GlobolctiEngine
{
	string                         InvokeId;
	unsigned int                   monitorCrossRefID_t;


	string				          deviceID;			// 用于填充座席ID
	bool                           IsForce;

	
	 SIPCCMsg_GCTI_ForceHangupEvent()
	 {
		msgType = Type_GCTI_ForceHangupEvent;
		monitorCrossRefID_t=0;
	
		

	};

	~ SIPCCMsg_GCTI_ForceHangupEvent()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
//Type_GCTI_SetAgentEvent;
struct   SIPCCMsg_GCTI_SetAgentEvent: public SIPCCMsg_GlobolctiEngine
{
	string                         InvokeId;
	unsigned int                   monitorCrossRefID_t;


	string 				deviceID;			// 用于填充座席ID
	string              agentID;
	
	 SIPCCMsg_GCTI_SetAgentEvent()
	 {
		msgType = Type_GCTI_SetAgentEvent;
		monitorCrossRefID_t=0;
	
		

	};

	~ SIPCCMsg_GCTI_SetAgentEvent()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
//Type_GCTI_TransferredToIVREvent;
struct   SIPCCMsg_GCTI_TransferredToIVREvent: public SIPCCMsg_GlobolctiEngine
{
	string                         InvokeId;
	unsigned int                   monitorCrossRefID_t;


	UINT		   	callID;
	string			transferringDevice;
	string			transferredDevice;
	string			privateData;
    int 		    localConnectionState;
	int 			cause;


	
	 SIPCCMsg_GCTI_TransferredToIVREvent()
	 {
		msgType = Type_GCTI_TransferredToIVREvent;
		callID=0;
		monitorCrossRefID_t=0;
		localConnectionState=0;
        cause=0;
	
		

	};

	~ SIPCCMsg_GCTI_TransferredToIVREvent()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
//Type_GCTI_ResetHoldCall;
struct   SIPCCMsg_GCTI_ResetHoldCall: public SIPCCMsg_GlobolctiEngine
{
	string                         InvokeId;
	unsigned int                   monitorCrossRefID_t;


	string       	ReHoldDevice;


	
	 SIPCCMsg_GCTI_ResetHoldCall()
	 {
		msgType = Type_GCTI_ResetHoldCall;		
		monitorCrossRefID_t=0;
		
	
		

	};

	~ SIPCCMsg_GCTI_ResetHoldCall()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
//Type_GCTI_DriverMediaPlay;
struct   SIPCCMsg_GCTI_DriverMediaPlay: public SIPCCMsg_GlobolctiEngine
{
	string            InvokeId;
	unsigned int      uInvokeId;

	string    		channelID;
	int         	channelType;
	string			playContent;
	bool			canBeKeyBreak;
	int				loopCount;		// < 0 : 循环播放
	int         	mediaSender;
	string          dtmfString;

	
	 SIPCCMsg_GCTI_DriverMediaPlay()
	 {
		   msgType = Type_GCTI_DriverMediaPlay;
	
		   InvokeId="";
		   uInvokeId=0;
		   channelID="";
		   channelType=0;
		   playContent="";
		   canBeKeyBreak=false;
		   loopCount=0;		// < 0 : 循环播放
		   mediaSender=0;
		   dtmfString="";


	};

	~ SIPCCMsg_GCTI_DriverMediaPlay()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
struct GCTISASRGrammar
{
	int 	        grammarType;
	string			grammarName;	// 在static grammar时有效, dynamic grammar时不用
	string			grammarFileName;// 在static grammar时不用
};
//Type_GCTI_DriverMediaPlayWithASR;
struct   SIPCCMsg_GCTI_DriverMediaPlayWithASR: public SIPCCMsg_GlobolctiEngine
{
	string               InvokeId;//0
   unsigned int          uInvokeId;//0
	string			     channelID;//1
	int      		     channelType;//2
	int					 workMode;	//3		// 语音识别系统工作模式；0立即识别，1文件识别
	int					 bargeInMode;//4		// 立即识别工作模式下的打断模式；0不可打断，1立即打断，2结果打断

	int					 acceptDtmf;//5			// 是否接收Dtmf 打断，0不接收，1接收
	int					 maxDigitNum;//6	// 接收Dtmf最大数
	int					 maxReceiveTime;//7		// 接收Dtmf第一位及按键间隔的最长时间(unit: 1/10 second)

	string				playContent;//8		// 播放提示语的内容 (TTS字符串或者语音文件名); workMode=1的时候，为语音文件名
	int					playLoopCount;//9		// 播放循环次数
	
	// 参数
	int					maxBeginSilence;//10	// 开始最长静音(0-6000[5000]ms)
	int					maxEndSilence; //11	// 结束最长静音(800-5000[1200]ms)
	int					maxSpeech; 	//12		// 最长话音(1000-15000[5000]ms)
	int					confidenceThreshold;//13// 识别阀值(0-100[30]) 
	int					bargeinThreshold;//14 	// 打断阀值(0-100[40]) 
	int					pruningThreshold;//15 	// 精度阀值(300-5000 [2000]）

	int					nBest; 	//16			// 返回识别结果最大数(1-100[1])
	int					speechType; //17		// 语音类型,统一采用 a law .pcm(8k 8byte)
	int                 listsize;//18
	
	list<GCTISASRGrammar>		grammarList;		// 1~N个文法




	 SIPCCMsg_GCTI_DriverMediaPlayWithASR()
	 {
		msgType = Type_GCTI_DriverMediaPlayWithASR;
		InvokeId="";
		uInvokeId=0;
		
	};

	~ SIPCCMsg_GCTI_DriverMediaPlayWithASR()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
//Type_GCTI_DriverMediaRecord;
struct   SIPCCMsg_GCTI_DriverMediaRecord: public SIPCCMsg_GlobolctiEngine
{
	string               InvokeId;
	unsigned int         uInvokeId;

	string			     channelID;
	int      		     channelType;
	string			     recordFileName;
	int				     maxRecordTime;	
	bool			     bAttach;


	 SIPCCMsg_GCTI_DriverMediaRecord()
	 {
		msgType = Type_GCTI_DriverMediaRecord;
		InvokeId="";
		uInvokeId=0;
		channelID="";
		channelType=0;
		recordFileName="";
		maxRecordTime=0;	
		bAttach=false;

		
	};

	~ SIPCCMsg_GCTI_DriverMediaRecord()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
//Type_GCTI_DriverMediaSendDTMF;
struct   SIPCCMsg_GCTI_DriverMediaSendDTMF: public SIPCCMsg_GlobolctiEngine
{
	string               InvokeId;
	unsigned int         uInvokeId;

	string			     channelID;
	int      		     channelType;
	string			     DTMFstring;
	

	 SIPCCMsg_GCTI_DriverMediaSendDTMF()
	 {
		msgType = Type_GCTI_DriverMediaSendDTMF;
		InvokeId="";
		uInvokeId=0;
		channelID="";
		channelType=0;
		

		
	};

	~ SIPCCMsg_GCTI_DriverMediaSendDTMF()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
//Type_GCTI_DriverMediaReceiveDTMF;
struct   SIPCCMsg_GCTI_DriverMediaReceiveDTMF: public SIPCCMsg_GlobolctiEngine
{
	string               InvokeId;
	unsigned int       uInvokeId;
   
	string			     channelID;
	int      		     channelType;
	int				     maxDigitNum;
	int				     maxReceiveTime;	// unit: 1/10 second


	 SIPCCMsg_GCTI_DriverMediaReceiveDTMF()
	 {
		msgType = Type_GCTI_DriverMediaReceiveDTMF;
		InvokeId="";
		uInvokeId=0;
		channelID="";
		channelType=0;
		maxDigitNum=0;
		maxReceiveTime=0;	// unit: 1/10 second


		
	};

	~ SIPCCMsg_GCTI_DriverMediaReceiveDTMF()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
//Type_GCTI_DriverMediaSendFax;
struct   SIPCCMsg_GCTI_DriverMediaSendFax: public SIPCCMsg_GlobolctiEngine
{
	string               InvokeId;
	unsigned int         uInvokeId;

	string			     channelID;
	int      		     channelType;
	string               faxFileName;

	 SIPCCMsg_GCTI_DriverMediaSendFax()
	 {
		msgType = Type_GCTI_DriverMediaSendFax;
		InvokeId="";
		uInvokeId=0;
		channelID="";
		channelType=0;
		faxFileName="";

		
	};

	~ SIPCCMsg_GCTI_DriverMediaSendFax()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
//Type_GCTI_DriverMediaReceiveFax;
struct   SIPCCMsg_GCTI_DriverMediaReceiveFax: public SIPCCMsg_GlobolctiEngine
{
	string               InvokeId;	
   unsigned int          uInvokeId;


	string			     channelID;
	int      		     channelType;
	string               faxFileName;

	 SIPCCMsg_GCTI_DriverMediaReceiveFax()
	 {
		msgType = Type_GCTI_DriverMediaReceiveFax;
		InvokeId="";
		uInvokeId=0;
		channelID="";
		channelType=0;
		faxFileName="";

		
	};

	~ SIPCCMsg_GCTI_DriverMediaReceiveFax()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
//Type_GCTI_DriverMediaCLRBuf;
struct   SIPCCMsg_GCTI_DriverMediaCLRBuf: public SIPCCMsg_GlobolctiEngine
{
	string               InvokeId;
	unsigned int         uInvokeId;

	string			     channelID;
	int      		     channelType;
	

	 SIPCCMsg_GCTI_DriverMediaCLRBuf()
	 {
		msgType = Type_GCTI_DriverMediaCLRBuf;
		InvokeId="";
		uInvokeId=0;
		channelID="";		
		channelType=0;
		

		
	};

	~ SIPCCMsg_GCTI_DriverMediaCLRBuf()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
//Type_GCTI_DriverMediaStopWork;
struct  SIPCCMsg_GCTI_DriverMediaStopWork: public SIPCCMsg_GlobolctiEngine
{
	string               InvokeId;
	unsigned int         uInvokeId;

	string			     channelID;
	int      		     channelType;
	int                  mediaSender;
	

	 SIPCCMsg_GCTI_DriverMediaStopWork()
	 {
		msgType = Type_GCTI_DriverMediaStopWork;
		channelID="";
		uInvokeId=0;
		channelType=0;
		mediaSender=0;
		
		
	};

	~ SIPCCMsg_GCTI_DriverMediaStopWork()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
//Type_GCTI_DriverSetCostStatus;
struct  SIPCCMsg_GCTI_DriverSetCostStatus: public SIPCCMsg_GlobolctiEngine
{
	string               InvokeId;
	unsigned int         uInvokeId;

	string			     channelID;
	int      		     channelType;
	bool                 CanCost;
	

	 SIPCCMsg_GCTI_DriverSetCostStatus()
	 {
		msgType = Type_GCTI_DriverSetCostStatus;
		channelID="";
		uInvokeId=0;
		channelType=0;
		CanCost=false;		
		
	};

	~ SIPCCMsg_GCTI_DriverSetCostStatus()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
//Type_GCTI_TransferCall;
struct   SIPCCMsg_GCTI_TransferCall: public SIPCCMsg_GlobolctiEngine
{
	string                      InvokeId;
	unsigned int                uinvokeId;
	GCTIConnectionID			heldCall;
	GCTIConnectionID			activeCall;



	 SIPCCMsg_GCTI_TransferCall()
	 {
		msgType = Type_GCTI_DeliveredEvent;
		InvokeId="";
        uinvokeId=0;
	};

	~ SIPCCMsg_GCTI_TransferCall()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
///

struct SIPCCMsg_Board : public SIPCCMessage
{
	SIPCCMsg_Board()
	{
		msgClass = Class_Board;
	};

	~SIPCCMsg_Board()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf) = 0;
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0) = 0;
	virtual void ReleaseMemory(){};
};
//Type_Board_DriverConnectConfEvent;
struct   SIPCCMsg_Board_DriverConnectConfEvent: public SIPCCMsg_Board
{
	string                      InvokeId;
	unsigned int                uinvokeId;   


	 SIPCCMsg_Board_DriverConnectConfEvent()
	 {
		msgType = Type_Board_DriverConnectConfEvent;
		InvokeId="";
        uinvokeId=0;
	};

	~ SIPCCMsg_Board_DriverConnectConfEvent()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
//Type_Board_DriverDisconnectConfEvent;
struct   SIPCCMsg_Board_DriverDisconnectConfEvent: public SIPCCMsg_Board
{
	string                      InvokeId;
	unsigned int                uinvokeId;
   


	 SIPCCMsg_Board_DriverDisconnectConfEvent()
	 {
		msgType = Type_Board_DriverDisconnectConfEvent;
		InvokeId="";
        uinvokeId=0;
	};

	~ SIPCCMsg_Board_DriverDisconnectConfEvent()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	private:
	virtual int GetMyMemSize();
};
//Type_Board_DriverTrunkOffHookConfEvent;
struct   SIPCCMsg_Board_DriverTrunkOffHookConfEvent: public SIPCCMsg_Board
{
	string                      InvokeId;
	unsigned int                uinvokeId;
   


	 SIPCCMsg_Board_DriverTrunkOffHookConfEvent()
	 {
		msgType = Type_Board_DriverConnectConfEvent;
		InvokeId="";
        uinvokeId=0;
	};

	~ SIPCCMsg_Board_DriverTrunkOffHookConfEvent()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
//Type_Board_DriverTrunkOnHookConfEvent;
struct   SIPCCMsg_Board_DriverTrunkOnHookConfEvent: public SIPCCMsg_Board
{
	string                      InvokeId;
	unsigned int                uinvokeId;
	string                      channelID;
   


	 SIPCCMsg_Board_DriverTrunkOnHookConfEvent()
	 {
		msgType = Type_Board_DriverTrunkOnHookConfEvent;
		InvokeId="";
        uinvokeId=0;
	};

	~ SIPCCMsg_Board_DriverTrunkOnHookConfEvent()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
//Type_Board_DriverTrunkResetConfEvent;
struct   SIPCCMsg_Board_DriverTrunkResetConfEvent: public SIPCCMsg_Board
{
	string                      InvokeId;
	unsigned int                uinvokeId;
	


	 SIPCCMsg_Board_DriverTrunkResetConfEvent()
	 {
		msgType = Type_Board_DriverTrunkResetConfEvent;
		InvokeId="";
        uinvokeId=0;
	};

	~ SIPCCMsg_Board_DriverTrunkResetConfEvent()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
//Type_Board_DriverConferenceDestroyConfEvent;
struct   SIPCCMsg_Board_DriverConferenceDestroyConfEvent: public SIPCCMsg_Board
{
	string                      InvokeId;
	unsigned int                uinvokeId;
	


	 SIPCCMsg_Board_DriverConferenceDestroyConfEvent()
	 {
		msgType = Type_Board_DriverConferenceDestroyConfEvent;
		InvokeId="";
        uinvokeId=0;
	};

	~ SIPCCMsg_Board_DriverConferenceDestroyConfEvent()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
//Type_Board_DriverUniversalFailureConfEvent;
struct  SIPCCMsg_Board_DriverUniversalFailureConfEvent :public SIPCCMsg_Board
{
	string                      InvokeId;
	unsigned int                uinvokeId;
	


	 SIPCCMsg_Board_DriverUniversalFailureConfEvent()
	 {
		msgType = Type_Board_DriverUniversalFailureConfEvent;
		InvokeId="";
        uinvokeId=0;
	};

	~ SIPCCMsg_Board_DriverUniversalFailureConfEvent()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
//Type_Board_DriverReportTrunkStateEvent;
struct  SIPCCMsg_Board_DriverReportTrunkStateEvent:public SIPCCMsg_Board
{
	string                      InvokeId;
	unsigned int                uinvokeId;
	string		                channelID;
     int                    	channelType;

	int                         status;


	 SIPCCMsg_Board_DriverReportTrunkStateEvent()
	 {
		msgType = Type_Board_DriverReportTrunkStateEvent;
		InvokeId="";
        uinvokeId=0;
	};

	~ SIPCCMsg_Board_DriverReportTrunkStateEvent()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
//Type_Board_DriverInBoundCallEvent;
struct  SIPCCMsg_Board_DriverInBoundCallEvent:public SIPCCMsg_Board
{
	string                      InvokeId;
	unsigned int                uinvokeId;

	string		                channelID;
     int                    	channelType;

	string	callerNo;
	string	calledNo;
	string privateData;

	 SIPCCMsg_Board_DriverInBoundCallEvent()
	 {
		msgType = Type_Board_DriverInBoundCallEvent;
		InvokeId="";
        uinvokeId=0;
		callerNo="";
		calledNo="";
		privateData="";


	};

	~ SIPCCMsg_Board_DriverInBoundCallEvent()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
//Type_Board_DriverUserHangupEvent;
struct  SIPCCMsg_Board_DriverUserHangupEvent:public SIPCCMsg_Board
{
	string                      InvokeId;
	unsigned int                uinvokeId;
	string		                channelID;
     int                    	channelType;

	

	 SIPCCMsg_Board_DriverUserHangupEvent()
	 {
		msgType = Type_Board_DriverUserHangupEvent;
		InvokeId="";
        uinvokeId=0;
		


	};

	~ SIPCCMsg_Board_DriverUserHangupEvent()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
//Type_Board_DriverDialRingingEvent;
struct  SIPCCMsg_Board_DriverDialRingingEvent:public SIPCCMsg_Board
{
	string                      InvokeId;
	unsigned int                uinvokeId;
	string		                channelID;
     int                    	channelType;

	

	 SIPCCMsg_Board_DriverDialRingingEvent()
	 {
		msgType = Type_Board_DriverDialRingingEvent;
		InvokeId="";
        uinvokeId=0;
		


	};

	~ SIPCCMsg_Board_DriverDialRingingEvent()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
//Type_Board_DriverDialSuccessEvent;
struct  SIPCCMsg_Board_DriverDialSuccessEvent:public SIPCCMsg_Board
{
	string                      InvokeId;
	unsigned int                uinvokeId;
	string		                channelID;
     int                    	channelType;
	string                     strLocalIP;
	string                       strVoiceSamplePath;

	 SIPCCMsg_Board_DriverDialSuccessEvent()
	 {
		msgType = Type_Board_DriverDialSuccessEvent;
		InvokeId="";
        uinvokeId=0;

	};

	~ SIPCCMsg_Board_DriverDialSuccessEvent()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
//Type_Board_DriverDialSuccessTollEvent;
struct  SIPCCMsg_Board_DriverDialSuccessTollEvent:public SIPCCMsg_Board
{
	string                      InvokeId;
	unsigned int                uinvokeId;
	string		                channelID;
     int                    	channelType;
	
	 SIPCCMsg_Board_DriverDialSuccessTollEvent()
	 {
		msgType = Type_Board_DriverDialSuccessTollEvent;
		InvokeId="";
        uinvokeId=0;

	};

	~ SIPCCMsg_Board_DriverDialSuccessTollEvent()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
//Type_Board_DriverTrunkSeizedEvent;
struct  SIPCCMsg_Board_DriverTrunkSeizedEvent:public SIPCCMsg_Board
{
	string                      InvokeId;
	unsigned int                uinvokeId;
	string		                channelID;
     int                    	channelType;
	
	 SIPCCMsg_Board_DriverTrunkSeizedEvent()
	 {
		msgType = Type_Board_DriverTrunkSeizedEvent;
		InvokeId="";
        uinvokeId=0;

	};

	~ SIPCCMsg_Board_DriverTrunkSeizedEvent()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
//Type_Board_DriverFailedEvent;
struct  SIPCCMsg_Board_DriverFailedEvent:public SIPCCMsg_Board
{
	string                      InvokeId;
	unsigned int                uinvokeId;
	string		                channelID;
     int                    	channelType;
	 int                         error;
	string                     strLocalIP;
	string                       strVoiceSamplePath;

	 SIPCCMsg_Board_DriverFailedEvent()
	 {
		msgType = Type_Board_DriverFailedEvent;
		InvokeId="";
        uinvokeId=0;

	};

	~ SIPCCMsg_Board_DriverFailedEvent()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
//Type_Board_DriverMediaEvent;
struct  SIPCCMsg_Board_DriverMediaEvent:public SIPCCMsg_Board
{
	string                      InvokeId;
	unsigned int                uinvokeId;
	string		                channelID;
     int                    	channelType;

	int		                    mediaSender;
	int		                    oprType;
	int	                        cause;
	string				        content;


	 SIPCCMsg_Board_DriverMediaEvent()
	 {
		msgType = Type_Board_DriverMediaEvent;
		InvokeId="";
        uinvokeId=0;

	};

	~ SIPCCMsg_Board_DriverMediaEvent()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
///Type_GCTI_AgentTransferToIVR
struct SIPCCMsg_GCTI_AgentTransferToIVR  : public SIPCCMsg_GlobolctiEngine
{
	 string               InvokeId;
	 unsigned int         uInvokeId;

	GCTIConnectionID	 activeCall;
	bool			     bWaitReturn; // 是否等待该呼叫从IVR返回?				
	string			     privateData;


	SIPCCMsg_GCTI_AgentTransferToIVR()
	{
		msgType = Type_GCTI_AgentTransferToIVR;
		InvokeId="";
		uInvokeId=0;
	};

	~SIPCCMsg_GCTI_AgentTransferToIVR()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
//Type_GCTI_AlternateCall;
struct   SIPCCMsg_GCTI_AlternateCall: public SIPCCMsg_GlobolctiEngine
{
	string                      InvokeId;
	unsigned int                uinvokeId;
	GCTIConnectionID			otherCall;
	GCTIConnectionID			activeCall;



	 SIPCCMsg_GCTI_AlternateCall()
	 {
		msgType = Type_GCTI_AlternateCall;
		InvokeId="";
        uinvokeId=0;
	};

	~ SIPCCMsg_GCTI_AlternateCall()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
///
///Type_GCTI_ClearCall
struct SIPCCMsg_GCTI_ClearCall  : public SIPCCMsg_GlobolctiEngine
{
	 string               InvokeId;
	 unsigned int         uInvokeId;

	GCTIConnectionID	 call;


	SIPCCMsg_GCTI_ClearCall()
	{
		msgType = Type_GCTI_ClearCall;
		InvokeId="";
		uInvokeId=0;
	};

	~SIPCCMsg_GCTI_ClearCall()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
//Type_GCTI_ReconnectCall;
struct   SIPCCMsg_GCTI_ReconnectCall: public SIPCCMsg_GlobolctiEngine
{
	string                      InvokeId;
	unsigned int                uinvokeId;
	GCTIConnectionID			heldCall;
	GCTIConnectionID			activeCall;



	 SIPCCMsg_GCTI_ReconnectCall()
	 {
		msgType =Type_GCTI_ReconnectCall;
		InvokeId="";
        uinvokeId=0;
	};

	~ SIPCCMsg_GCTI_ReconnectCall()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
//Type_GCTI_RejectCall
struct SIPCCMsg_GCTI_RejectCal  : public SIPCCMsg_GlobolctiEngine
{
	 string               InvokeId;
	 unsigned int         uInvokeId;

	GCTIConnectionID	 call;


	SIPCCMsg_GCTI_RejectCal()
	{
		msgType = Type_GCTI_RejectCall;
		InvokeId="";
		uInvokeId=0;
	};

	~SIPCCMsg_GCTI_RejectCal()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
///Type_GCTI_RetrieveCall
struct SIPCCMsg_GCTI_RetrieveCall  : public SIPCCMsg_GlobolctiEngine
{
	 string               InvokeId;
	 unsigned int         uInvokeId;

	GCTIConnectionID	 heldCall;


	SIPCCMsg_GCTI_RetrieveCall()
	{
		msgType = Type_GCTI_RetrieveCall;
		InvokeId="";
		uInvokeId=0;
	};

	~SIPCCMsg_GCTI_RetrieveCall()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
//Type_GCTI_MonitorStop;
struct   SIPCCMsg_GCTI_MonitorStop: public SIPCCMsg_GlobolctiEngine
{
	string                         InvokeId;
	 unsigned int                   uInvokeId;
	 unsigned int                   monitorCrossRefID_t;


	
	 SIPCCMsg_GCTI_MonitorStop()
	 {
		msgType = Type_GCTI_MonitorStop;
		monitorCrossRefID_t=0;
	
		

	};

	~ SIPCCMsg_GCTI_MonitorStop()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
//Type_GCTI_SnapshotDevice;
struct   SIPCCMsg_GCTI_SnapshotDevice: public SIPCCMsg_GlobolctiEngine
{
	string                         InvokeId;
	 unsigned int                   uInvokeId;
	string                          device;


	
	 SIPCCMsg_GCTI_SnapshotDevice()
	 {
		msgType = Type_GCTI_SnapshotDevice;
		

	};

	~ SIPCCMsg_GCTI_SnapshotDevice()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
//Type_Inner_AlertingRequest
struct   SIPCCMsg_Inner_AlertingRequest: public SIPCCMsg_GlobolctiEngine
{
    string              InvokeId;	  
   unsigned int         uinvokeID;
   
	string    	srcDeviceID;
	string 	    destDeviceID;
	UINT	    callID;
	int    	    cause;

   

	 SIPCCMsg_Inner_AlertingRequest()
	 {
		msgType = Type_Inner_AlertingRequest;
	};

	~ SIPCCMsg_Inner_AlertingRequest()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
//Type_Inner_MakeCallRequest
struct   SIPCCMsg_Inner_MakeCallRequest: public SIPCCMsg_GlobolctiEngine
{
    string              InvokeId;	  
   unsigned int         uinvokeID;
   
	string    	srcDeviceID;
	string 	    destDeviceID;
	UINT	    callID;
	string      userData;

   

	 SIPCCMsg_Inner_MakeCallRequest()
	 {
		msgType = Type_Inner_MakeCallRequest;
	};

	~ SIPCCMsg_Inner_MakeCallRequest()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
//Type_Inner_TimerEvent
struct   SIPCCMsg_Inner_TimerEvent: public SIPCCMsg_GlobolctiEngine
{
    string              InvokeId;	  
   unsigned int         uinvokeID;
   
	unsigned int         timerID;

   

	 SIPCCMsg_Inner_TimerEvent()
	 {
		msgType = Type_Inner_TimerEvent;
	};

	~ SIPCCMsg_Inner_TimerEvent()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
//Type_SIPCCMsg_Bord_DriverConnect
struct   SIPCCMsg_Bord_DriverConnect: public SIPCCMsg_GlobolctiEngine
{
    string              InvokeId;	  
   unsigned int         uinvokeID;
   
	string 		channel1_ID;
	int 	    channel1_Type;
	string 		channel2_ID;
	int 	    channel2_Type;
	int 	    connectType;
   

	 SIPCCMsg_Bord_DriverConnect()
	 {
		msgType = Type_Bord_DriverConnect;
	};

	~ SIPCCMsg_Bord_DriverConnect()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
//Type_Bord_DriverDisconnect
struct   SIPCCMsg_Bord_DriverDisconnect: public SIPCCMsg_GlobolctiEngine
{
    string              InvokeId;	  
   unsigned int         uinvokeID;
   
	string 		channel1_ID;
	int 	    channel1_Type;
	string 		channel2_ID;
	int 	    channel2_Type;
	
   

	 SIPCCMsg_Bord_DriverDisconnect()
	 {
		msgType = Type_Bord_DriverDisconnect;
	};

	~ SIPCCMsg_Bord_DriverDisconnect()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
//Type_Bord_DriverDial
struct   SIPCCMsg_Bord_DriverDial: public SIPCCMsg_GlobolctiEngine
{
    string              InvokeId;	  
   unsigned int         uinvokeID;

   string		  channelID;//1
	int 	      channelType;//2
	string 		  calledNo;	//3
	int				maxRingCount;//4
	int 		     dialerType;//5	
	string		     msiChannelID;//6 当dialerType==Agent时，先连接中继与MSI，再进行外拨
	string			privateData;//7
	
	string			callerNoForSend;//8

	string			privateData_OutDial;//9taskid_Province_City_Isp_Brand_phoneid

	string		    LowLevelPrefixNo;//10当外拨号码中有前缀，且前缀仅用于底层拨号，不用于上层路由计费，将此
									 //前缀置于此处

	 SIPCCMsg_Bord_DriverDial()
	 {
		msgType = Type_Bord_DriverDial;
	};

	~ SIPCCMsg_Bord_DriverDial()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
//Type_Bord_TrunkOnHook
struct   SIPCCMsg_Bord_DriverTrunkOffHook: public SIPCCMsg_GlobolctiEngine
{
    string              InvokeId;	  
   unsigned int         uinvokeID;

    string		  channelID;//1
	int 	      channelType;//2
	 SIPCCMsg_Bord_DriverTrunkOffHook()
	 {
		msgType = Type_Bord_DriverTrunkOffHook;
	};

	~ SIPCCMsg_Bord_DriverTrunkOffHook()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};


//Type_Bord_DriverTrunkOnHook
struct   SIPCCMsg_Bord_DriverTrunkOnHook: public SIPCCMsg_GlobolctiEngine
{
    string              InvokeId;	  
   unsigned int         uinvokeID;

   string		  channelID;//1
	int 	      channelType;//2
	
	 SIPCCMsg_Bord_DriverTrunkOnHook()
	 {
		msgType = Type_Bord_DriverTrunkOnHook;
	};

	~ SIPCCMsg_Bord_DriverTrunkOnHook()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
//Type_Bord_DriverTrunkReset
struct   SIPCCMsg_Bord_DriverTrunkReset: public SIPCCMsg_GlobolctiEngine
{
    string              InvokeId;	  
   unsigned int         uinvokeID;

   string		  channelID;//1
	int 	      channelType;//2
	
	 SIPCCMsg_Bord_DriverTrunkReset()
	 {
		msgType = Type_Bord_DriverTrunkReset;
	};

	~ SIPCCMsg_Bord_DriverTrunkReset()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};

//Type_Bord_DriverEchoRemoveCtrl
struct   SIPCCMsg_Bord_DriverEchoRemoveCtrl: public SIPCCMsg_GlobolctiEngine
{
    string              InvokeId;	  
   unsigned int         uinvokeID;

   string		  channelID;//1
	int 	      channelType;//2
	bool          allow;
	
	 SIPCCMsg_Bord_DriverEchoRemoveCtrl()
	 {
		msgType = Type_Bord_DriverEchoRemoveCtrl;
	};

	~ SIPCCMsg_Bord_DriverEchoRemoveCtrl()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};

//Type_Bord_DriverAddRecordForTH
struct   SIPCCMsg_Bord_DriverAddRecordForTH: public SIPCCMsg_GlobolctiEngine
{
    string              InvokeId;	  
   unsigned int         uinvokeID;

   string		phoneNo;
	
	 SIPCCMsg_Bord_DriverAddRecordForTH()
	 {
		msgType = Type_Bord_DriverAddRecordForTH;
	};

	~ SIPCCMsg_Bord_DriverAddRecordForTH()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};

//Type_Bord_DriverDelRecordForTH
struct   SIPCCMsg_Bord_DriverDelRecordForTH: public SIPCCMsg_GlobolctiEngine
{
    string              InvokeId;	  
   unsigned int         uinvokeID;

   string		phoneNo;
	
	 SIPCCMsg_Bord_DriverDelRecordForTH()
	 {
		msgType = Type_Bord_DriverAddRecordForTH;
	};

	~ SIPCCMsg_Bord_DriverDelRecordForTH()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};

//Type_Bord_DriverDelAllRecordForTH
struct   SIPCCMsg_Bord_DriverDelAllRecordForTH: public SIPCCMsg_GlobolctiEngine
{
    string              InvokeId;	  
   unsigned int         uinvokeID;

  
	
	 SIPCCMsg_Bord_DriverDelAllRecordForTH()
	 {
		msgType = Type_Bord_DriverAddRecordForTH;
	};

	~ SIPCCMsg_Bord_DriverDelAllRecordForTH()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
// 连接结构
struct GCTISConnection
{
	/// 连接ID
	GCTIConnectionID		connectionID;
	/// 连接状态
	int 	state;
	/// 连接类型
	int 		connType;

public:
	GCTISConnection() {state = 0;}
	GCTISConnection(const UINT  &callID_In, const string deviceID_In, int  state_In, int connType_In=2/*ConnectionType_Full*/):
	  state(state_In), connType(connType_In)
	{connectionID.callID = callID_In; connectionID.deviceID = deviceID_In;}
	
	GCTISConnection(const GCTIConnectionID &connID, int  state_In, int  connType_In=2/*ConnectionType_Full(*/):  
	  connectionID(connID), state(state_In), connType(connType_In)
	{}
};

typedef list<GCTISConnection> GCTIConnectionList;
//Type_GCTI_Meaage
struct   SIPCCMsg_GCTI_Message: public SIPCCMsg_GlobolctiEngine
{
	string                InvokeId;	  
	unsigned int          uinvokeID;
	string                context;//内容
	string                strorigin;//来源填写（Board，统一CTI队列，Session, Softacd)


	
	 SIPCCMsg_GCTI_Message()
	 {
		msgType = Type_GCTI_Meaage;
		InvokeId="";
		uinvokeID=0;
	};

	~ SIPCCMsg_GCTI_Message()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
//Type_Session_Meaage
struct   SIPCCMsg_Session_Message: public SIPCCMsg_GlobolctiEngine
{
	string               InvokeId;	  
	unsigned int         uinvokeID;
	string               context;
	string               strType;
	string               strorigin;//来源填写（Board，统一CTI队列，Session,GCTI)
	string               sSender;
	string               sReceiver;

	
	 SIPCCMsg_Session_Message()
	 {
		msgType = Type_Session_Meaage;
		InvokeId="";		
		uinvokeID=0;
		context="";
		strType="";
		strorigin="";
		sSender="";
		sReceiver="";
	};

	~ SIPCCMsg_Session_Message()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
///Type_SysManage_SwitchAcdConf
struct SIPCCMsg_SysManage_SwitchAcdConf : public SIPCCMsg_SysManage
{


	string InvokeId;
	string ManagerId;
	string AcdServerId;
	unsigned long AcdServerIp;
	unsigned short AcdServerPort;
	char      bLoadFinished;	 //0为加载失败，1为加载成功



	int ServiceID;							//描述ACDServer的ServiceID
	int OldServiceID;						//描述原ACDServer的ServiceID
	int ManagerCount;						//切换到新ACDServer下的企业总数
	int indexNum;							//分包使用的编号以1开始，如无分包处理则为0

	SIPCCMsg_SysManage_SwitchAcdConf()
	{
		 msgType = Type_SysManage_SwitchAcdConf;
		 ServiceID =0;
		 ManagerCount =0;
		 indexNum = 0;
	}
	~SIPCCMsg_SysManage_SwitchAcdConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};
	

private:	
     virtual int GetMyMemSize();
	
};
//Type_SysManage_AddTDDistributeServer
struct SIPCCMsg_SysManage_AddTDDistributeServer : public SIPCCMsg_SysManage
{


	string   serverName;
	unsigned long lanIP;
	unsigned short lanPort;
	unsigned long wanIP;
	unsigned short wanPort;
	int           serviceid; 

	SIPCCMsg_SysManage_AddTDDistributeServer()
	{
		 msgType = Type_SysManage_AddTDDistributeServer;
		 
		 serverName="";
		 lanIP=0;
		 lanPort=0;
		 wanIP=0;
		 wanPort=0;
		 serviceid=0;
	}
	~SIPCCMsg_SysManage_AddTDDistributeServer()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
    virtual void ReleaseMemory(){};
	

private:	
    virtual int GetMyMemSize();
	
};

//Type_SysManage_AddGWtoTDDS
struct SIPCCMsg_SysManage_AddGWtoTDDS : public SIPCCMsg_SysManage
{


	string gwName;
	string computerSymbol;
	string serverName;
	int      serviceid; 


	SIPCCMsg_SysManage_AddGWtoTDDS()
	{
		 msgType = Type_SysManage_AddGWtoTDDS;		 
		 gwName="";
		 computerSymbol="";
		 serverName="";
		 serviceid=0;
	
		
	}
	~SIPCCMsg_SysManage_AddGWtoTDDS()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};
	

private:	
    virtual int GetMyMemSize();
	
};

//Type_TrunkData_DSLoadInfo
struct SIPCCMsg_TrunkData_DSLoadInfo : public SIPCCMsg_SysManage
{

	
	string serverName;
	int      serviceid;


	SIPCCMsg_TrunkData_DSLoadInfo()
	{
		 msgType = Type_TrunkData_DSLoadInfo; 
		
		 serverName="";
		 serviceid=0;
		
	}
	~SIPCCMsg_TrunkData_DSLoadInfo()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};
	

private:	
    virtual int GetMyMemSize();
	
};
//Type_SysManage_AddTDCollectServer
struct SIPCCMsg_SysManage_AddTDCollectServer : public SIPCCMsg_SysManage
{


	
	string serverName;
	int serverType;			//（1为网关中继信息采集服务，2为企业中继信息采集服务）
 	unsigned long lanIP;
	unsigned short lanPort;
	unsigned long wanIP;
	unsigned short wanPort;
	int      serviceid;



	SIPCCMsg_SysManage_AddTDCollectServer()
	{
		 msgType = Type_SysManage_AddTDCollectServer;		 
		
		 serverName="";
		 serverType=0;
		 lanIP=0;
		 lanPort=0;
		 wanIP=0;
		 wanPort=0;
		 serviceid=0;

		
	}
	~SIPCCMsg_SysManage_AddTDCollectServer()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};
	

private:	
    virtual int GetMyMemSize();
	
};
//Type_SysManage_AddComptoTDCS
struct SIPCCMsg_SysManage_AddComptoTDCS : public SIPCCMsg_SysManage
{


	string    managerid;
	string    serverName;
	int       serviceid;



	SIPCCMsg_SysManage_AddComptoTDCS()
	{
		 msgType = Type_SysManage_AddComptoTDCS;
		 managerid="";
		 serverName="";
		 serviceid=0;
		
		
	}
	~SIPCCMsg_SysManage_AddComptoTDCS()
	{
		ReleaseMemory();
	};	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};
	

private:	
    virtual int GetMyMemSize();
	
};
//Type_SysManage_AddGWtoTDCS
struct SIPCCMsg_SysManage_AddGWtoTDCS : public SIPCCMsg_SysManage
{


	string gwName;
	string computerSymbol;
	string serverName;
	int      serviceid;


	SIPCCMsg_SysManage_AddGWtoTDCS()
	{
		 msgType = Type_SysManage_AddGWtoTDCS;
		 gwName="";
		 computerSymbol="";
		 serverName="";
		 serviceid=0;

		
	}
	~SIPCCMsg_SysManage_AddGWtoTDCS()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};
	

private:	
    virtual int GetMyMemSize();
	
};


//Type_SysManage_AddComptoConnNo
struct SIPCCMsg_SysManage_AddComptoConnNo : public SIPCCMsg_SysManage
{


	string managerid;
	string connectPhoneNoList;		//接入号用分号隔开



	SIPCCMsg_SysManage_AddComptoConnNo()
	{
		 msgType = Type_SysManage_AddComptoConnNo;
		 managerid="";
		 connectPhoneNoList="";
		 

		
	}
	~SIPCCMsg_SysManage_AddComptoConnNo()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};
	

private:	
    virtual int GetMyMemSize();
	
};
// Type_TrunkData_NotifyTrunkState
struct   SIPCCMsg_TrunkData_NotifyTrunkState : public SIPCCMsg_Gateway
{
	SIPCCMsg_TrunkData_NotifyTrunkState()
	{
	
		msgType = Type_TrunkData_NotifyTrunkState;

		ComputerSymbol = "";
		GwName = "";
		LineNo = "";
		GroupId = -1;
		CallDirection = -1;
		LastState = 0;
		NewState = 0;
		managerid = "";
		newStatetime = 0;
		MappingName=0;
	
	}
	~SIPCCMsg_TrunkData_NotifyTrunkState()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}

	string ComputerSymbol;
	string GwName;
	string LineNo;
	int GroupId;
	int CallDirection;
	int LastState;
	int NewState;
	string managerid;
	time_t newStatetime;
	int MappingName;

private:
	virtual int GetMyMemSize();
};

struct SIPCCMsg_OutDial_CheckAlive : public SIPCCMsg_OutDial
{
	SIPCCMsg_OutDial_CheckAlive()
	{
		msgType = Type_OutDial_CheckAlive;
	}
	~SIPCCMsg_OutDial_CheckAlive()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}

	string GwName;
private:
	virtual int GetMyMemSize();
};

struct SIPCCMsg_OutDial_CheckAliveConf : public SIPCCMsg_OutDial
{
	SIPCCMsg_OutDial_CheckAliveConf()
	{
		msgType = Type_OutDial_CheckAliveConf;
	}
	~SIPCCMsg_OutDial_CheckAliveConf()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}

	string GwName;
private:
	virtual int GetMyMemSize();
};

//////////////////////////////////////////////////////////////////////////
//caodt 2012-08-22 时间同步服务器　
//////////////////////////////////////////////////////////////////////////
struct SIPCCMsg_Timer_Synchronization : public SIPCCMessage
{
	string currentDate;		//请求方发信令时间，精确到毫秒；
	int ServiceLevel;		//时间同步服务器级别，最高等级为0，数字越大级别越低；

	SIPCCMsg_Timer_Synchronization()
	{
		msgClass = Class_Timer;
		msgType = Type_Timer_Synchronization;
		ServiceLevel = 0;
	}
	~SIPCCMsg_Timer_Synchronization()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};


private:	
	virtual int GetMyMemSize();
};

struct SIPCCMsg_Timer_SynchronizationConf : public SIPCCMessage
{
	string currentDate;		//响应方发信令时间，精确到毫秒；
	int millisecond;		//接收信令后，响应方与请求方的时间差；

	SIPCCMsg_Timer_SynchronizationConf()
	{
		msgClass = Class_Timer;
		msgType = Type_Timer_SynchronizationConf;
	}
	~SIPCCMsg_Timer_SynchronizationConf()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};


private:	
	virtual int GetMyMemSize();
};

struct SIPCCMsg_Client_ConferenceCall : public SIPCCMsg_Client{
	SIPCCMsg_Client_ConferenceCall():
		SIPCCMsg_Client(Class_Client,Type_Client_ConferenceCall),
		held_device_dn(""),
		preside_device_dn(""),
		active_device_dn("")		
		{};

	~SIPCCMsg_Client_ConferenceCall(){
		ReleaseMemory();
	};

	int FillBuf(char*& thebuf);
	void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	void ReleaseMemory();
	
	std::string	held_device_dn;	
	//char		held_device_type;
	
	std::string	preside_device_dn;	
	//char		preside_device_type;

	std::string	active_device_dn;
	//char		active_device_type;

private:	
	virtual int GetMyMemSize();
};

struct SIPCCMsg_Client_ConferenceCallConf : public SIPCCMsg_Client{
	SIPCCMsg_Client_ConferenceCallConf():
		SIPCCMsg_Client(Class_Client,Type_Client_ConferenceCall),
		is_success(false),
		conference_call_id("")		
	{
		/*held_device_address.sin_family = AF_INET;
		conference_device_address.sin_family = AF_INET;
		active_device_address.sin_family = AF_INET;*/
	};


	~SIPCCMsg_Client_ConferenceCallConf(){
		ReleaseMemory();
	};

	int			FillBuf(char*& thebuf);
	void		AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	void		ReleaseMemory();

	bool		is_success;

	//此call_id为控制中心范畴内的call_id
	//不是网关范畴的call_id或invoke_id
	//此call_id只用来满足控制中心T_Toll_Universal表需求
	std::string	conference_call_id;	

	std::string	held_device_dn;
	std::string	preside_device_dn;
	std::string	active_device_dn;

	IpPort	held_device_address;
	IpPort	preside_device_address;
	IpPort	active_device_address;	
private:	
	virtual int GetMyMemSize();
};

struct SIPCCMsg_Client_ConferenceCallEnd : public SIPCCMsg_Client{
	SIPCCMsg_Client_ConferenceCallEnd():
SIPCCMsg_Client(Class_Client,Type_Client_ConferenceCallEnd),
conference_call_id("")
{

};


~SIPCCMsg_Client_ConferenceCallEnd(){
	ReleaseMemory();
};

int			FillBuf(char*& thebuf);
void		AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
void		ReleaseMemory();


std::string	conference_call_id;


private:	
	virtual int GetMyMemSize();
};
// add code by hyj
//Type_OneKeySwitch_ServiceRegister
struct  SIPCCMsg_OneKeySwitch_ServiceRegister : public SIPCCMsg_OneKeySwitch			
{
	string  ServerName;
    int ServerType;//（1-50 控制中心，100以网关,每种类型有一组）
	unsigned long wanIP;
	unsigned short wanPort;
	unsigned long lanIP;
	unsigned short lanPort;
	int ServerID;


	SIPCCMsg_OneKeySwitch_ServiceRegister()
	{

		msgType = Type_OneKeySwitch_ServiceRegister;

		ServerName="";
		ServerType=0;
		wanIP=0;
		wanPort=0;
		lanIP=0;
		lanPort=0;
		ServerID=0;
		
	};

	~SIPCCMsg_OneKeySwitch_ServiceRegister()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
//Type_OneKeySwitch_ServiceRegisterConf
struct  SIPCCMsg_OneKeySwitch_ServiceRegisterConf : public SIPCCMsg_OneKeySwitch			
{
	unsigned long HeartBeatServerIp;
	unsigned short HeartBeatServerPort;
	unsigned long HeartBeatServerBackupIp;
	unsigned short HeartBeatServerBackupIPort;
	int  ServiceID;////注册成功时返回服务ID，否者为空
	int  ServiceType;////注册成功时返回服务ID，否者为空

	int Service1ID;//begin未定
	int Service1Type;
	unsigned long service1IP;
	unsigned short service1Port;
	int Service2ID;
	int Service2Type;
	unsigned long service2IP;
	unsigned short service2Port;// end 未定


	int         HeartBeatServerID;
	int        HeartBeatServerBackupID;
	int        operationMode;			//默认为2，表示须有两个心跳服务；为0表示无心跳服务；

	SIPCCMsg_OneKeySwitch_ServiceRegisterConf()
	{

		msgType = Type_OneKeySwitch_ServiceRegisterConf;

		HeartBeatServerIp=0;
		HeartBeatServerPort=0;
		HeartBeatServerBackupIp=0;
		HeartBeatServerBackupIPort=0;
		ServiceID=0;
		Service1ID=0;//begin未定
		Service1Type=0;
		service1IP=0;
		service1Port=0;
		Service2ID=0;
		Service2Type=0;
		service2IP=0;
		service2Port=0;// end 未定
		HeartBeatServerID=0;
		HeartBeatServerBackupID=0;
		operationMode=2;

		
	};

	~SIPCCMsg_OneKeySwitch_ServiceRegisterConf()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};

//Type_OneKeySwitch_ServiceConfirm
struct  SIPCCMsg_OneKeySwitch_ServiceConfirm : public SIPCCMsg_OneKeySwitch			
{
	string         InvokeId;
	int            ServiceID;
	int            ServiceType;
	unsigned long  serviceWanIP;
	unsigned long  serviceLanIP;
	unsigned short servicePort;

	SIPCCMsg_OneKeySwitch_ServiceConfirm()
	{

		msgType = Type_OneKeySwitch_ServiceConfirm;
		InvokeId="";
		ServiceID=0;
		ServiceType=0;
		serviceWanIP=0;
		serviceLanIP=0;
		servicePort=0;

	
	};

	~SIPCCMsg_OneKeySwitch_ServiceConfirm()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
//Type_OneKeySwitch_ServiceConfirmConf
struct  SIPCCMsg_OneKeySwitch_ServiceConfirmConf : public SIPCCMsg_OneKeySwitch			
{
	string         InvokeId;
	int            ServiceID;
	int            ServiceType;
	

	SIPCCMsg_OneKeySwitch_ServiceConfirmConf()
	{

		msgType = Type_OneKeySwitch_ServiceConfirmConf;
		InvokeId="";
		ServiceID=0;
        ServiceType=0;
		

	
	};

	~SIPCCMsg_OneKeySwitch_ServiceConfirmConf()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};

///Type_OneKeySwitch_GetHeartBeat
struct SIPCCMsg_OneKeySwitch_GetHeartBeat : public SIPCCMsg_OneKeySwitch
{
	SIPCCMsg_OneKeySwitch_GetHeartBeat();
	~SIPCCMsg_OneKeySwitch_GetHeartBeat()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		InvokeId = "";
		HeartBeatServerIP = 0;
		HeartBeatServerPort = 0;
		HeartBeatServerBackupIP = 0;
		HeartBeatServerBackupPort = 0;
		ServiceID=0;
        ServiceType=0;
	}

	string InvokeId;
	unsigned long HeartBeatServerIP;
	unsigned short HeartBeatServerPort;
	unsigned long HeartBeatServerBackupIP;
	unsigned short HeartBeatServerBackupPort;
	int ServiceID;
    int ServiceType;

private:
	virtual int GetMyMemSize();
};
//Type_OneKeySwitch_GetService
struct    SIPCCMsg_OneKeySwitch_GetService : public SIPCCMsg_OneKeySwitch			
{
	string            InvokeId; 
	int               ServiceID;//（自已）
	int               ServiceType;//（自已）
	int               GetServiceCount; //（第一次，第二次要几个，如果有取就是需要重新分配）
	int               Service1ID;
	int               Service1Type;
	unsigned long     service1IP;
	unsigned short    service1Port;
	int               Service2ID;
	int               Service2Type;
	unsigned long     service2IP;
	unsigned short    service2Port;
	int               Service3ID;
	int               Service3Type;
	unsigned long     service3IP;
	unsigned short    service3Port;
	int               Service4ID;
	int               Service4Type;
	unsigned long     service4IP;
	unsigned short    service4Port;

	string	serviceInfoList;

	SIPCCMsg_OneKeySwitch_GetService()
	{

		msgType = Type_OneKeySwitch_GetService;
		InvokeId=""; 
		ServiceID=0;//（自已）
		ServiceType=0;//（自已）
		GetServiceCount=0; //（第一次，第二次要几个，如果有取就是需要重新分配）
		Service1ID=0;
		Service1Type=0;
		service1IP=0;
		service1Port=0;
		Service2ID=0;
		Service2Type=0;
		service2IP=0;
		service2Port=0;
		Service3ID=0;
		Service3Type=0;
		service3IP=0;
		service3Port=0;
		Service4ID=0;
		Service4Type=0;
		service4IP=0;
		service4Port=0;

		serviceInfoList = "";
	};

	~SIPCCMsg_OneKeySwitch_GetService()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};

//Type_OneKeySwitch_GetServiceConf
struct   	SIPCCMsg_OneKeySwitch_GetServiceConf : public SIPCCMsg_OneKeySwitch			
{
	string            InvokeId; 
	
	int               SendServiceCount; //（第一次，第二次要几个，如果有取就是需要重新分配）
	int               Service1ID;
	int               Service1Type;
	unsigned long     service1IP;
	unsigned short    service1Port;
	int               Service2ID;
	int               Service2Type;
	unsigned long     service2IP;
	unsigned short    service2Port;
	int               Service3ID;
	int               Service3Type;
	unsigned long     service3IP;
	unsigned short    service3Port;
	int               Service4ID;
	int               Service4Type;
	unsigned long     service4IP;
	unsigned short    service4Port;

	string	serviceInfoList;

	SIPCCMsg_OneKeySwitch_GetServiceConf()
	{

		msgType = Type_OneKeySwitch_GetServiceConf;
		InvokeId=""; 
		
		SendServiceCount=0; //（第一次，第二次要几个，如果有取就是需要重新分配）
		Service1ID=0;
		Service1Type=0;
		service1IP=0;
		service1Port=0;
		Service2ID=0;
		Service2Type=0;
		service2IP=0;
		service2Port=0;
		Service3ID=0;
		Service3Type=0;
		service3IP=0;
		service3Port=0;
		Service4ID=0;
		Service4Type=0;
		service4IP=0;
		service4Port=0;

		serviceInfoList = "";
	};

	~SIPCCMsg_OneKeySwitch_GetServiceConf()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
//Type_OneKeySwitch_ServiceTimeout
struct   	SIPCCMsg_OneKeySwitch_ServiceTimeout : public SIPCCMsg_OneKeySwitch			
{
	
	int               ServiceType;
	int               ServiceID;
	int               SelfServiceType;
	int               SelfServiceID;
	
	string gatewayName;

	string computerSymbol;
	
	SIPCCMsg_OneKeySwitch_ServiceTimeout()
	{

		msgType = Type_OneKeySwitch_ServiceTimeout;
		
		ServiceType=0;
	
		ServiceID=0;
		gatewayName="";
		computerSymbol="";
		SelfServiceType=0;
		SelfServiceID=0;
		
	
	};

	~SIPCCMsg_OneKeySwitch_ServiceTimeout()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
//Type_OneKeySwitch_SynchronizationRegister
struct  SIPCCMsg_OneKeySwitch_SynchronizationRegister : public SIPCCMsg_OneKeySwitch			
{
	string  ServerName;
    int       ServerType;//（1-50 控制中心，100以网关,每种类型有一组）
	unsigned long wanIP;
	unsigned short wanPort;
	unsigned long lanIP;
	unsigned short lanPort;
	int ServerID;
	string InvokeId;
	int   needproxy;


	SIPCCMsg_OneKeySwitch_SynchronizationRegister()
	{

		msgType = Type_OneKeySwitch_SynchronizationRegister;

		ServerName="";
		ServerType=0;
		wanIP=0;
		wanPort=0;
		lanIP=0;
		lanPort=0;
		ServerID=0;
		InvokeId="";
		needproxy=0;
		
	};

	~SIPCCMsg_OneKeySwitch_SynchronizationRegister()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
//
//Type_OneKeySwitch_SynchronizationRegisterConf
struct  SIPCCMsg_OneKeySwitch_SynchronizationRegisterConf : public SIPCCMsg_OneKeySwitch			
{
	string InvokeId;


	SIPCCMsg_OneKeySwitch_SynchronizationRegisterConf()
	{

		msgType = Type_OneKeySwitch_SynchronizationRegisterConf;
	
		InvokeId="";
		
	};

	~SIPCCMsg_OneKeySwitch_SynchronizationRegisterConf()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
//
//Type_OneKeySwitch_LoadRegisterInfo
struct  SIPCCMsg_OneKeySwitch_LoadRegisterInfo : public SIPCCMsg_OneKeySwitch			
{
	string InvokeId;


	SIPCCMsg_OneKeySwitch_LoadRegisterInfo()
	{

		msgType = Type_OneKeySwitch_LoadRegisterInfo;
	
		InvokeId="";
		
	};

	~SIPCCMsg_OneKeySwitch_LoadRegisterInfo()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
//Type_SysManage_AddRegisterInfo
struct  SIPCCMsg_SysManage_AddRegisterInfo : public SIPCCMsg_OneKeySwitch			
{
	string  InvokeId;
	int     ServiceID;
	string  ServerName;
	int     ServerType;
	unsigned long wanIP;
	unsigned short wanPort;
	unsigned long lanIP;
	unsigned short lanPort;
	char bLoad;			//0为删除，1为加载
	int  operationMode;	//默认为2，表示须有两个心跳服务；为0表示无心跳服务；
	int  needProxyRegister;		//默认为0，表示网关可直接注册；为1表示网关需要代理注册；



	SIPCCMsg_SysManage_AddRegisterInfo()
	{

		msgType = Type_SysManage_AddRegisterInfo;
		InvokeId="";
		ServiceID=0;
		ServerName="";
		ServerType=0;
		wanIP=0;
		wanPort=0;
	    lanIP=0;
		lanPort=0;
		bLoad=1;			//0为删除，1为加载
		operationMode=2;
		needProxyRegister=0;

		
	};

	~SIPCCMsg_SysManage_AddRegisterInfo()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
//Type_OneKeySwitch_AddRegisterInfoConf
struct  SIPCCMsg_OneKeySwitch_AddRegisterInfoConf : public SIPCCMsg_OneKeySwitch			
{
	string InvokeId;
	char   bLoad;


	SIPCCMsg_OneKeySwitch_AddRegisterInfoConf()
	{

		msgType = Type_OneKeySwitch_AddRegisterInfoConf;
	
		InvokeId="";
		bLoad=1;			//0为删除，1为加载
		
	};

	~SIPCCMsg_OneKeySwitch_AddRegisterInfoConf()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};

///Type_Client_ConferenceStart
struct SIPCCMsg_Client_ConferenceStart : public SIPCCMsg_Client
{
	SIPCCMsg_Client_ConferenceStart();
	~SIPCCMsg_Client_ConferenceStart()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

	string firstName;
	string firstLineNo;
	string thirdName;
	int conferenceType;
	string managerid;			//公司ID

private:
	virtual int GetMyMemSize();
};

///Type_ACD_ConferenceStart
struct SIPCCMsg_ACD_ConferenceStart : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_ConferenceStart();
	~SIPCCMsg_ACD_ConferenceStart()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

	string firstName;              //主控方座席ID
	string firstLineNo;            ////第一外线UserName
	unsigned short ConferencePort;	//会议端口
    string thePartyLineNo;	//本方座席对应的ConferenceAgent编号
	string theOtherPartyLineNo;	//另一方座席对应的ConferenceAgent编号

private:
	virtual int GetMyMemSize();
};

///Type_UState_ConferenceStart
struct SIPCCMsg_UState_ConferenceStart : public SIPCCMsg_UState
{
	SIPCCMsg_UState_ConferenceStart();
	~SIPCCMsg_UState_ConferenceStart()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

	string firstName;
	string firstLineNo;
	string thirdName;
	int conferenceType;
    string managerid;			//公司ID

	string gatewayName;

	string computerSymbol;

private:
	virtual int GetMyMemSize();
};

///Type_Client_ConferenceEnd
struct SIPCCMsg_Client_ConferenceEnd : public SIPCCMsg_Client
{
	SIPCCMsg_Client_ConferenceEnd();
	~SIPCCMsg_Client_ConferenceEnd()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

	string firstName;
	string firstLineNo;
	string thirdName;
	int conferenceType;
	string managerid;			//公司ID

private:
	virtual int GetMyMemSize();
};

///Type_ACD_ConferenceEnd
struct SIPCCMsg_ACD_ConferenceEnd : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_ConferenceEnd();
	~SIPCCMsg_ACD_ConferenceEnd()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

	string firstName;
	string firstLineNo;

private:
	virtual int GetMyMemSize();
};

///Type_UState_ConferenceEnd
struct SIPCCMsg_UState_ConferenceEnd : public SIPCCMsg_UState
{
	SIPCCMsg_UState_ConferenceEnd();
	~SIPCCMsg_UState_ConferenceEnd()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

	string firstName;
	string firstLineNo;
	string thirdName;
	int conferenceType;
	string managerid;			//公司ID


	string gatewayName;

	string computerSymbol;

private:
	virtual int GetMyMemSize();
};
struct SIPCCMsg_SysManage_GetServerList : public SIPCCMsg_OneKeySwitch		//获取坐席心跳服务
{
	int ServerType;

	SIPCCMsg_SysManage_GetServerList()
	{
		msgType = Type_SysManage_GetServerList;
		ServerType=0;
	};

	~SIPCCMsg_SysManage_GetServerList()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
////////////////////////////////
struct SIPCCMsg_SysManage_GetServerListConf : public SIPCCMsg_OneKeySwitch	//获取坐席心跳服务回应
{
	string InvokeId;
	map<string, pair<unsigned long, unsigned short> > ServerList;

	SIPCCMsg_SysManage_GetServerListConf(){
		msgType = Type_SysManage_GetServerListConf;
	};

	~SIPCCMsg_SysManage_GetServerListConf()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};

//Type_OneKeySwitch_ServiceRegister
struct  SIPCCMsg_OneKeySwitch_HotAddService : public SIPCCMsg_OneKeySwitch			
{
	string  ServerName;
    int ServerType;//（1-50 控制中心，100以网关,每种类型有一组）
	unsigned long wanIP;
	unsigned short wanPort;
	unsigned long lanIP;
	unsigned short lanPort;
	int ServerID;


	SIPCCMsg_OneKeySwitch_HotAddService()
	{

		msgType = Type_OneKeySwitch_HotAddService;

		ServerName="";
		ServerType=0;
		wanIP=0;
		wanPort=0;
		lanIP=0;
		lanPort=0;
		ServerID=0;
		
	};

	~SIPCCMsg_OneKeySwitch_HotAddService()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};

///////////////////////////////////////////////////////////////////////////
///Class_CID
struct SIPCCMsg_CID : public SIPCCMessage
{
	SIPCCMsg_CID(){msgClass = Class_CID;};
	~SIPCCMsg_CID()
	{
		ReleaseMemory();
	};

	virtual int GetMyMemSize(){return 0;}
	virtual int FillBuf(char*& thebuf){return 0;}
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0){}
	virtual void ReleaseMemory(){}
};

struct SIPCCMsg_CID_DialCmd : public SIPCCMsg_CID
{
	SIPCCMsg_CID_DialCmd()
	{
		msgType = Type_CID_DialCmd;
	}
	~SIPCCMsg_CID_DialCmd()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}

	int TaskId;
	int PhoneId;
	string TrunkGroupNum;
	string CalleeNum;
	string CallerForSend;
	string ManagerId;
	string UuiData_Task;
	string UuiData_Phone;
	string OriginalCallee;
private:
	virtual int GetMyMemSize();
};

struct SIPCCMsg_CID_Result : public SIPCCMsg_CID
{
	SIPCCMsg_CID_Result()
	{
		msgType = Type_CID_Result;
	}
	~SIPCCMsg_CID_Result()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}

	int TaskId;
	int PhoneId;
	string DialTime;
	string DialEndTime;
	bool IsDialSucc;
	int DialFailCause;
	string TalkEndTime;
	bool ExistKey;
	string InvokeId;

	string LogString;
private:
	virtual int GetMyMemSize();
};
//conference
struct  SIPCCMsg_Gateway_ConferenceStartConf : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_ConferenceStartConf()
	{
	   msgType = Type_Gateway_ConferenceStartConf;
	   firstName="";
	   firstLineNo="";
	   thirdName="";
	   conferenceType=0;
	   managerid="";
	   bSucc=1;
	   firstConferencePort=0;
	   secondConferencePort=0;
	   firstPartyLineNo="";
	   secondPartyLineNo="";
	   
	
	}
	~SIPCCMsg_Gateway_ConferenceStartConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		
	}
public:
	string firstName;			//主控方座席ID
    string firstLineNo;		//第一外线UserName
	string thirdName;		//第三参会方，如果是座席就填座席ID，如果是中继就填UserName
	int conferenceType;		//三方类型，1表示两座席一外线，2表示一座席两外线，3表示一座席一外线，4表示两外线，5表示两座席；
	string managerid;			//公司ID
	char bSucc;				//三方会议申请成功与否
	unsigned short firstConferencePort;		//第一会议端口
	unsigned short secondConferencePort;	//第二会议端口
    string firstPartyLineNo;		//主控方座席对应的ConferenceAgent编号
    string secondPartyLineNo;	//参会方座席对应的ConferenceAgent编号
	virtual int GetMyMemSize();
public:
};
///
struct  SIPCCMsg_ACD_ConferenceStartConf : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_ConferenceStartConf()
	{
	   msgType = Type_ACD_ConferenceStartConf;
	   firstName="";
	   firstLineNo="";
	   thirdName="";
	   conferenceType=0;
	   managerid="";
	   bSucc=1;
	   ConferencePort=0;
	   thePartyLineNo="";
	   theOtherPartyLineNo="";
	   
	   
	
	}
	~SIPCCMsg_ACD_ConferenceStartConf()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		
	}
public:
	string firstName;			//主控方座席ID
    string firstLineNo;		//第一外线UserName
	string thirdName;		//第三参会方，如果是座席就填座席ID，如果是中继就填UserName
	int conferenceType;		//三方类型，1表示两座席一外线，2表示一座席两外线，3表示一座席一外线，4表示两外线，5表示两座席；
	string managerid;			//公司ID
	char bSucc;				//三方会议申请成功与否
	unsigned short ConferencePort;		//议端口
    string thePartyLineNo;	//本方座席对应的ConferenceAgent编号
	string theOtherPartyLineNo;	//另一方座席对应的ConferenceAgent编号

	virtual int GetMyMemSize();
public:
};
///
struct  SIPCCMsg_Gateway_UserLeaveConference : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_UserLeaveConference()
	{
	   msgType = Type_Gateway_UserLeaveConference;
	   leaveUserName="";
	   initiateAgentName="";
	   joinName="";
	   conferenceType=0;
	   managerid="";
	   
	
	}
	~SIPCCMsg_Gateway_UserLeaveConference()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		
	}
public:
	string   leaveUserName;	//离开会议的座席名
	string  initiateAgentName;  //主控方座席ID
	string  joinName;//剩余参会方，如果是座席就填座席ID，如果是中继就填UserName
	int    conferenceType;		//剩余参会方，如果是座席就填座席ID，如果是中继就填UserName
	string managerid;			//公司ID

	virtual int GetMyMemSize();
public:
};
//
struct  SIPCCMsg_ACD_UserLeaveConference : public  SIPCCMsg_ACD
{
	SIPCCMsg_ACD_UserLeaveConference()
	{
	   msgType = Type_ACD_UserLeaveConference;
	   leaveUserName="";
	   initiateAgentName="";
	   joinName="";
	   conferenceType=0;
	   managerid="";
	   
	
	}
	~SIPCCMsg_ACD_UserLeaveConference()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		
	}
public:
	string   leaveUserName;	//离开会议的座席名
	string  initiateAgentName;  //主控方座席ID
	string  joinName;//剩余参会方，如果是座席就填座席ID，如果是中继就填UserName
	int    conferenceType;		//剩余参会方，如果是座席就填座席ID，如果是中继就填UserName
	string managerid;			//公司ID

	virtual int GetMyMemSize();
public:
};

//
struct  SIPCCMsg_Record_StartConferenceRecord : public   SIPCCMsg_Record
{
	SIPCCMsg_Record_StartConferenceRecord()
	{
		msgType = Type_Record_StartConferenceRecord;
		conferenceRoomID="";
		conferenceID=0;
		firstName="";
		firstNickname="";
		secondName="";
		secondNickname="";
		thirdName="";
		thirdNickname="";
		conferenceType=0;
		managerid="";
		corpName="";
		recordFilePath="";
		beginTime="";
	}
	~SIPCCMsg_Record_StartConferenceRecord()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		
	}
public:
	string CTID;//通话记录的invokeid
	string conferenceRoomID;//会议室phoneNo（ConferenceConfig.xml文件中配置）
	int conferenceID;//会议ID（网关内唯一）
	string firstName;//主控方AgentID
	string firstNickname;//主控方座席昵称
	string secondName;//第二参会方，座席就填AgentID，中继就填DN
	string secondNickname;//第二参会方，座席就填座席昵称，中继就填电话号码
	string thirdName;//第三参会方，座席就填AgentID，中继就填DN
	string thirdNickname;//第三参会方，座席就填座席昵称，中继就填电话号码
	int conferenceType;//三方类型，1表示两座席一外线，2表示一座席两外线；
	string managerid;//企业ID
	string corpName;//企业名称
	string recordFilePath;//录音文件存放路径
	string beginTime;//录音开始时间
	virtual int GetMyMemSize();
public:
};

//
struct  SIPCCMsg_Record_StopConferenceRecord : public   SIPCCMsg_Record
{
	SIPCCMsg_Record_StopConferenceRecord()
	{
		msgType = Type_Record_StopConferenceRecord;
		conferenceRoomID="";
		conferenceID=0;	
		
	}
	~SIPCCMsg_Record_StopConferenceRecord()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		
	}
public:
	string CTID;//通话记录的invokeid
	string conferenceRoomID;//会议室phoneNo（ConferenceConfig.xml文件中配置）
	int conferenceID;//会议ID（网关内唯一）
	virtual int GetMyMemSize();
public:
};
//
///Type_OneKeySwitch_GWLoginConf
struct SIPCCMsg_OneKeySwitch_GWLogOutConf : public SIPCCMsg_OneKeySwitch			
{
	SIPCCMsg_OneKeySwitch_GWLogOutConf();
	~SIPCCMsg_OneKeySwitch_GWLogOutConf()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

	string GwName;
	string ComputerSymbol;
	string ServerName;
		
	int               ServiceType;
	int               ServiceID;;


private:
	virtual int GetMyMemSize();
};

struct SIPCCMsg_CID_CheckAlive : public SIPCCMsg_OutDial
{
	SIPCCMsg_CID_CheckAlive()
	{
		msgType = Type_CID_CheckAlive;
	}
	~SIPCCMsg_CID_CheckAlive()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}

	int Id;
	int GwCode;
	unsigned long GwIp;
	unsigned short GwPort;
	unsigned long SendTime;
private:
	virtual int GetMyMemSize();
};

struct SIPCCMsg_CID_CheckAliveConf : public SIPCCMsg_OutDial
{
	SIPCCMsg_CID_CheckAliveConf()
	{
		msgType = Type_CID_CheckAliveConf;
	}
	~SIPCCMsg_CID_CheckAliveConf()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}

	int Id;
	unsigned long CenterIp;
	unsigned short CenterPort;
	int GwCode;
	unsigned long GwIp;
	unsigned short GwPort;
	unsigned long SendTime;
private:
	virtual int GetMyMemSize();
};
//
struct SIPCCMsg_OneKeySwitch_SwitchService_Ctrl : public SIPCCMsg_OneKeySwitch			//切换服务
{
	string            InvokeId;
	string            ManagerId; 

	unsigned long   ServerIp;
	unsigned short  ServerPort;

	int            ServiceID_Old;	           
    int            ServiceID_New;
	        

    int            ServiceType;						//用于描述服务的类型
	string          gatewayName;
	string         computerSymbol;         

	SIPCCMsg_OneKeySwitch_SwitchService_Ctrl()
	{
		msgType = Type_OneKeySwitch_SwitchService_Ctrl;
		InvokeId="";
		ManagerId="";
		ServerIp=0;
		ServerPort=0;
		ServiceID_Old=0;	           
		ServiceID_New=0;
		ServiceType=0;	
		gatewayName="";
		computerSymbol="";

	};

	~SIPCCMsg_OneKeySwitch_SwitchService_Ctrl()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
//
//
struct SIPCCMsg_OneKeySwitch_SwitchService_CtrlConf : public SIPCCMsg_OneKeySwitch			//切换服务
{
	string            InvokeId;
	
	SIPCCMsg_OneKeySwitch_SwitchService_CtrlConf()
	{
		msgType = Type_OneKeySwitch_SwitchService_CtrlConf;
		InvokeId="";
	

	};

	~SIPCCMsg_OneKeySwitch_SwitchService_CtrlConf()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};

//
//
struct SIPCCMsg_OneKeySwitch_SwitchService : public SIPCCMsg_OneKeySwitch			//切换服务
{
	string            InvokeId;
	

	unsigned long   ServerIp;
	unsigned short  ServerPort;

	int            ServiceID;	           
   
	        

    int            ServiceType;						//用于描述服务的类型

	SIPCCMsg_OneKeySwitch_SwitchService()
	{
		msgType = Type_OneKeySwitch_SwitchService;
		InvokeId="";
		
		ServerIp=0;
		ServerPort=0;
		ServiceID=0;	           
		
		ServiceType=0;	

	};

	~SIPCCMsg_OneKeySwitch_SwitchService()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};

struct SIPCCMsg_OneKeySwitch_SwitchServiceConf : public SIPCCMsg_OneKeySwitch			//切换服务
{
	string            InvokeId;
	
	SIPCCMsg_OneKeySwitch_SwitchServiceConf()
	{
		msgType = Type_OneKeySwitch_SwitchServiceConf;
		InvokeId="";
	

	};

	~SIPCCMsg_OneKeySwitch_SwitchServiceConf()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};

//Type_Gateway_SubscribeTGStatus
struct  SIPCCMsg_Gateway_SubscribeTGStatus : public SIPCCMsg_Gateway			
{

	int            ServiceID; 
    int            ServiceType;					

	 SIPCCMsg_Gateway_SubscribeTGStatus()
	{
		msgType = Type_Gateway_SubscribeTGStatus;		
		ServiceID=0;   
		ServiceType=0;	

	};

	~ SIPCCMsg_Gateway_SubscribeTGStatus()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
//
//Type_TrunkData_NotifyTGStatus
struct  SIPCCMsg_TrunkData_NotifyTGStatus : public SIPCCMsg_Gateway			
{

	string ComputerSymbol;
	string GwName;
	int MappingName;
	int Occupancy;			

	 SIPCCMsg_TrunkData_NotifyTGStatus()
	{
		msgType = Type_TrunkData_NotifyTGStatus;		
		ComputerSymbol="";
		GwName="";
		 MappingName=0;
		 Occupancy=0;	

	};

	~ SIPCCMsg_TrunkData_NotifyTGStatus()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

private:
	virtual int GetMyMemSize();
};
//Type_SysManage_AddDeptTGRoute
struct SIPCCMsg_SysManage_AddDeptTGRoute : public SIPCCMsg_SysManage
{

	string corpName;
	string deptName;
	string deptAreaCode;
	string tgName;
	int CMLocalLevel;		//默认为0
	int CMLongLevel;		//默认为0
	int CULocalLevel;		//默认为0
	int CULongLevel;		//默认为0
	int CTLocalLevel;		//默认为0
	int CTLongLevel;		//默认为0

	string gwName;
	string computerSymbol;
	string mappingName;

	string invokeID;

	SIPCCMsg_SysManage_AddDeptTGRoute()
	{
	  msgType = Type_SysManage_AddDeptTGRoute;
	  corpName="";
	  deptName="";
	  deptAreaCode="";
	  tgName="";
	  CMLocalLevel=0;		//默认为0
	  CMLongLevel=0;		//默认为0
	  CULocalLevel=0;		//默认为0
	  CULongLevel=0;		//默认为0
	  CTLocalLevel=0;		//默认为0
	  CTLongLevel=0;		//默认为0
	
	  gwName="";
	  computerSymbol="";
	  mappingName="";

	  invokeID = "";
	}
	~SIPCCMsg_SysManage_AddDeptTGRoute()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}
	


private:
	virtual int GetMyMemSize();
};

//Type_SysManage_DelDeptTGRoute
struct SIPCCMsg_SysManage_DelDeptTGRoute : public SIPCCMsg_SysManage
{
	string corpName;
	string deptName;
	string operators;
	string invokeID;

	SIPCCMsg_SysManage_DelDeptTGRoute()
	{
		msgType = Type_SysManage_DelDeptTGRoute;
		corpName="";
		deptName="";
		operators="";
		invokeID = "";
	}
	~SIPCCMsg_SysManage_DelDeptTGRoute()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}

private:
	virtual int GetMyMemSize();
};
///Type_Gateway_UnAnsweredCall
struct SIPCCMsg_UnAnsweredAgentCall : public SIPCCMsg_Gateway
{
	SIPCCMsg_UnAnsweredAgentCall()
	{
	   msgType =Type_UnAnsweredAgentCall;
	   manageId="";
	   Keyword="";
	   ExtNo="";
	   CustomerNo="";
	   calledNo="";
	   TransBeginTime="";
	  hangupTime="" ;
	  ErrorType=0;
	  invokeId="";
	  CallType=0;

	
	};
	~SIPCCMsg_UnAnsweredAgentCall()
	{
		ReleaseMemory();
	};
	
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	};
	
	string manageId;
	string Keyword;
	string ExtNo;
	string CustomerNo;
	string calledNo;
	string TransBeginTime;
	string hangupTime ;
	int  ErrorType;
	string invokeId;
	int     CallType;
	virtual int GetMyMemSize();
};

///Type_DataTrans_SwitchPort
struct SIPCCMsg_DataTrans_SwitchPort : public SIPCCMsg_DataTrans
{
	SIPCCMsg_DataTrans_SwitchPort();
	~SIPCCMsg_DataTrans_SwitchPort()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}

public:
	int channelIndex;

	virtual int GetMyMemSize();
};

///Type_DataTrans_SwitchPortConf
struct SIPCCMsg_DataTrans_SwitchPortConf : public SIPCCMsg_DataTrans
{
	SIPCCMsg_DataTrans_SwitchPortConf();
	~SIPCCMsg_DataTrans_SwitchPortConf()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}

public:
	int ResultCode; //1成功，0失败，其他预留

	virtual int GetMyMemSize();
};

//Type_SysManage_AddGWIADG
struct SIPCCMsg_SysManage_AddGWIADG : public SIPCCMsg_SysManage
{
	SIPCCMsg_SysManage_AddGWIADG();
	~SIPCCMsg_SysManage_AddGWIADG()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}

	string IADGName;
	string IADGAreaCode;
	string gwName;
	string corpName;
	string mappingName;

	string invokeID;

private:
	virtual int GetMyMemSize();
};

//Type_SysManage_DelGWIADG
struct SIPCCMsg_SysManage_DelGWIADG : public SIPCCMsg_SysManage
{
	SIPCCMsg_SysManage_DelGWIADG();
	~SIPCCMsg_SysManage_DelGWIADG()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}

	string IADGName;
	string corpName;

	string invokeID;

private:
	virtual int GetMyMemSize();
};

//Type_SysManage_AddIAD
struct SIPCCMsg_SysManage_AddIAD : public SIPCCMsg_SysManage
{
	SIPCCMsg_SysManage_AddIAD();
	~SIPCCMsg_SysManage_AddIAD()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}

	string IADGName;
	string IADName;
	string corpName;

	string invokeID;

private:
	virtual int GetMyMemSize();
};

//Type_SysManage_DelIAD
struct SIPCCMsg_SysManage_DelIAD : public SIPCCMsg_SysManage
{
	SIPCCMsg_SysManage_DelIAD();
	~SIPCCMsg_SysManage_DelIAD()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}

	string IADGName;
	string IADName;
	string corpName;

	string invokeID;

private:
	virtual int GetMyMemSize();
};
//Type_OneKeySwitch_SynchronizationTimeout
struct SIPCCMsg_OneKeySwitch_SynchronizationTimeout : public SIPCCMsg_OneKeySwitch
{
	SIPCCMsg_OneKeySwitch_SynchronizationTimeout();
	~SIPCCMsg_OneKeySwitch_SynchronizationTimeout()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}

	string InvokeId;
	int  ServiceID;
	string GwName;
    string ComputerSymbol;
	int ServiceType;

private:
	virtual int GetMyMemSize();
};
//Type_OneKeySwitch_SynchronizationTimeoutConf
struct SIPCCMsg_OneKeySwitch_SynchronizationTimeoutConf : public SIPCCMsg_OneKeySwitch
{
	SIPCCMsg_OneKeySwitch_SynchronizationTimeoutConf();
	~SIPCCMsg_OneKeySwitch_SynchronizationTimeoutConf()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}

	string InvokeId;
	int bTimeout;
private:
	virtual int GetMyMemSize();
};

//Type_SysManage_AddSkillGroup
struct SIPCCMsg_SysManage_AddSkillGroup : public SIPCCMsg_SysManage
{
	SIPCCMsg_SysManage_AddSkillGroup();
	~SIPCCMsg_SysManage_AddSkillGroup()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}

	string managerid;
	string SGId;
	string SGName;
	string invokeID;
	string	generalConfiguration;		//通用配置项，配置项间用分号“；”分割；


private:
	virtual int GetMyMemSize();
};

//Type_SysManage_DelSkillGroup
struct SIPCCMsg_SysManage_DelSkillGroup : public SIPCCMsg_SysManage
{
	SIPCCMsg_SysManage_DelSkillGroup();
	~SIPCCMsg_SysManage_DelSkillGroup()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}

	string SGId;
	string SGName;
	string invokeID;

private:
	virtual int GetMyMemSize();
};

//Type_OneKeySwitch_SyncHeatBeatRelation
struct SIPCCMsg_OneKeySwitch_SyncHeatBeatRelation : public SIPCCMsg_SysManage
{
	SIPCCMsg_OneKeySwitch_SyncHeatBeatRelation();
	~SIPCCMsg_OneKeySwitch_SyncHeatBeatRelation()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}

	int    serverid;   
    int     servertype;//服务类型

	string GatewayName;//为以前网关兼容
	string ComputerSymbol;//;//为以前网关兼容
	int  HeatBeatID1;
	int   HeatBeatID2;
	int     Type;// (  0=网关，1=控制中心)

private:
	virtual int GetMyMemSize();
};

//Type_OneKeySwitch_SyncHeatBeatRelation
struct SIPCCMsg_OneKeySwitch_SyncHeatBeatRelationConfirm : public SIPCCMsg_SysManage
{
	SIPCCMsg_OneKeySwitch_SyncHeatBeatRelationConfirm();
	~SIPCCMsg_OneKeySwitch_SyncHeatBeatRelationConfirm()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}

	int    serverid;   
	int     servertype;//服务类型
	
private:
	virtual int GetMyMemSize();
};

//Type_OneKeySwitch_SyncHeatBeatRelationConfirmconf
struct  SIPCCMsg_OneKeySwitch_SyncHeatBeatRelationConfirmconf : public SIPCCMsg_SysManage
{
	 SIPCCMsg_OneKeySwitch_SyncHeatBeatRelationConfirmconf();
	~ SIPCCMsg_OneKeySwitch_SyncHeatBeatRelationConfirmconf()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}

	int    serverid;   
	int     servertype;//服务类型

	string GatewayName;//为以前网关兼容
	string ComputerSymbol;//;//为以前网关兼容
	int   HeatBeatID1;
	int   HeatBeatID2;
	int     Type;// (  0=网关，1=控制中心)

private:
	virtual int GetMyMemSize();
};

//Type_OneKeySwitch_GetServerHeartBeatServerInfo
struct  SIPCCMsg_OneKeySwitch_GetServerHeartBeatServerInfo : public SIPCCMsg_SysManage
{
	SIPCCMsg_OneKeySwitch_GetServerHeartBeatServerInfo();
	~ SIPCCMsg_OneKeySwitch_GetServerHeartBeatServerInfo()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}

	int    serverid;   
	int     servertype;//服务类型

	string GatewayName;//为以前网关兼容
	string ComputerSymbol;//;//为以前网关兼容	
	int     Type;// (  0=网关，1=控制中心)

private:
	virtual int GetMyMemSize();
};

//Type_OneKeySwitch_GetServerHeartBeatServerInfoConf
struct  SIPCCMsg_OneKeySwitch_GetServerHeartBeatServerInfoConf : public SIPCCMsg_SysManage
{
	SIPCCMsg_OneKeySwitch_GetServerHeartBeatServerInfoConf();
	~ SIPCCMsg_OneKeySwitch_GetServerHeartBeatServerInfoConf()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}

	long      HeatBeatServerIP1;
	int       HeatBeatServerPort1;
	long      HeatBeatServerIP2;
	int       HeatBeatServerPort2;

private:
	virtual int GetMyMemSize();
};

//Type_SysManage_AddBanCall
struct SIPCCMsg_SysManage_AddBanCall : public SIPCCMsg_SysManage
{
	SIPCCMsg_SysManage_AddBanCall();
	~SIPCCMsg_SysManage_AddBanCall()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}

	string corpName;
	string deptName;
	string startTime;
	string endTime;
	string invokeID;

private:
	virtual int GetMyMemSize();
};

//Type_SysManage_DelBanCall
struct SIPCCMsg_SysManage_DelBanCall : public SIPCCMsg_SysManage
{
  SIPCCMsg_SysManage_DelBanCall();
	~SIPCCMsg_SysManage_DelBanCall()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}

	string corpName;
	string deptName;
	string invokeID;

private:
	virtual int GetMyMemSize();
};
//Type_SysManage_AddAreaBan
struct SIPCCMsg_SysManage_AddAreaBan : public SIPCCMsg_SysManage
{
	SIPCCMsg_SysManage_AddAreaBan();
	~SIPCCMsg_SysManage_AddAreaBan()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}

	string corpName;
	string tgName;
	string callerNoForSend;
	string calleeAreaCode;
	int    calleeType;//类型
	string  ManagerTel; //企业小号

	string invokeID;

private:
	virtual int GetMyMemSize();
};

//Type_SysManage_DelAreaBan
struct SIPCCMsg_SysManage_DelAreaBan : public SIPCCMsg_SysManage
{
	SIPCCMsg_SysManage_DelAreaBan();
	~SIPCCMsg_SysManage_DelAreaBan()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}

	string corpName;
	string tgName;
	string callerNoForSend;

	string invokeID;
	
private:
	virtual int GetMyMemSize();
};

//client net information capture
struct SIPCCMsg_ClientCapture:public SIPCCMessage
{
	SIPCCMsg_ClientCapture();
	~SIPCCMsg_ClientCapture()
	{
		ReleaseMemory();
	};

	virtual int GetMyMemSize(){return 0;}
	virtual int FillBuf(char*& thebuf){return 0;}
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0){}
	virtual void ReleaseMemory(){}

public:
	string strAgentId;
	int iLineNo;
};

//Type_ClientCapture_SessionEnd
struct SIPCCMsg_ClientCapture_SessionEnd:public SIPCCMsg_ClientCapture
{
	SIPCCMsg_ClientCapture_SessionEnd();
	~SIPCCMsg_ClientCapture_SessionEnd()
	{ReleaseMemory();}

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		strAgentId="";
		iLineNo=-1;
	}


private:
	virtual int GetMyMemSize();
};

//Type_ClientCapture_SRSend
struct SIPCCMsg_ClientCapture_SRSend:public SIPCCMsg_ClientCapture
{
	SIPCCMsg_ClientCapture_SRSend();
	~SIPCCMsg_ClientCapture_SRSend()
	{
		ReleaseMemory();
	}

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		strAgentId="";
		int iLineNo=-1;
		srSendTime=0;
		srRecvTime=0;
	}

	LONGLONG srSendTime;
	LONGLONG srRecvTime;
private:
	virtual int GetMyMemSize();
};

//Type_ClientCapture_RRSend
struct SIPCCMsg_ClientCapture_RRSend:public SIPCCMsg_ClientCapture 
{
	SIPCCMsg_ClientCapture_RRSend();
	~SIPCCMsg_ClientCapture_RRSend()
	{
		ReleaseMemory();
	}

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		strAgentId="";
		iLineNo=-1;
		srSendTime=0;
		rrRecvTime=0;
		srDelayTime=0;
	}

	LONGLONG srSendTime;
	LONGLONG rrRecvTime;
	LONGLONG srDelayTime;
private:
	virtual int GetMyMemSize();
};

//Type_ClientCapture_GetRtpStatistics
struct SIPCCMsg_ClientCapture_GetRtpStatistics:public SIPCCMsg_ClientCapture
{
	SIPCCMsg_ClientCapture_GetRtpStatistics();
	~SIPCCMsg_ClientCapture_GetRtpStatistics()
	{ReleaseMemory();}

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
		strAgentId="";
		iLineNo=-1;
	}


private:
	virtual int GetMyMemSize();
};
//Type_WebService_QueryCalloutInfo
struct SIPCCMsg_WebService_QueryCalloutInfo : public SIPCCMsg_PhoneSearch
{
	SIPCCMsg_WebService_QueryCalloutInfo();
	~SIPCCMsg_WebService_QueryCalloutInfo()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}

	string agentId;			//座席工号
	string handleId;		//操作唯一标识
private:
	virtual int GetMyMemSize();
};
//
//Type_WebService_QueryCalloutInfoConf
struct SIPCCMsg_WebService_QueryCalloutInfoConf : public SIPCCMsg_PhoneSearch
{
	SIPCCMsg_WebService_QueryCalloutInfoConf();
	~SIPCCMsg_WebService_QueryCalloutInfoConf()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}

	string corpName;		//公司名称

	string managerid;

	string deptName;		//技能组名称

	string agentRealNo;	//座席绑定电话号码

	string handleId;		//操作唯一标识

private:
	virtual int GetMyMemSize();
};

//Type_WebService_HangupCall
struct SIPCCMsg_WebService_HangupCall : public SIPCCMsg_ACD
{
	SIPCCMsg_WebService_HangupCall();
	~SIPCCMsg_WebService_HangupCall()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}

	string agentId;

	string station;

	string operationTime;

	string event;

	int hangpuCallType;		//1为座席挂断，2为客户挂断

	string ucid;				//invokeid
private:
	virtual int GetMyMemSize();
};

//Type_WebService_RecordInfo
struct SIPCCMsg_WebService_RecordInfo : public SIPCCMsg_Record
{
	SIPCCMsg_WebService_RecordInfo();
	~SIPCCMsg_WebService_RecordInfo()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}

	string agentId;

	string station;

	string operationTime;

	string event;

	string recordId;			//invokeid

	int RecordType;			   //1是录音开始，2是录音结束；
private:
	virtual int GetMyMemSize();
};

//Type_WebService_DialingCall
struct SIPCCMsg_WebService_DialingCall : public SIPCCMsg_ACD
{
	SIPCCMsg_WebService_DialingCall();
	~SIPCCMsg_WebService_DialingCall()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}

	string ani;				//主叫号码

	string dnis;				//被叫号码

	string ucid;				//invokeid

	int director;				//呼叫方向，0是呼入，1是呼出

	string agentId;				//座席工号

	string station;				//分机

	string operationTime;		//操作时间

	string event;				//事件

	string userData;
private:
	virtual int GetMyMemSize();
};
//Type_WebService_RingingCall
struct SIPCCMsg_WebService_RingingCall : public SIPCCMsg_ACD
{
	SIPCCMsg_WebService_RingingCall();
	~SIPCCMsg_WebService_RingingCall()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}

	string ani;				//主叫号码

	string dnis;				//被叫号码

	string ucid;				//invokeid

	int director;				//呼叫方向，0是呼入，1是呼出

	string ivrTrack;			//IVR按键轨迹

	string agentId;				//座席工号

	string station;				//分机

	string operationTime;		//操作时间

	string event;				//事件
private:
	virtual int GetMyMemSize();
};


//Type_WebService_TalkingCall
struct SIPCCMsg_WebService_TalkingCall : public SIPCCMsg_ACD
{
	SIPCCMsg_WebService_TalkingCall();
	~SIPCCMsg_WebService_TalkingCall()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}

	string ani;				//主叫号码

	string dnis;				//被叫号码

	string ucid;				//invokeid

	string agentId;				//座席工号

	string station;				//分机

	string operationTime;		//操作时间

	string event;				//事件
private:
	virtual int GetMyMemSize();
};

///Type_SysManage_AddRecInfo
struct SIPCCMsg_SysManage_AddRecInfo : public SIPCCMsg_SysManage
{
	SIPCCMsg_SysManage_AddRecInfo();
	~SIPCCMsg_SysManage_AddRecInfo()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}

	string gwName;
	string computerSymbol;

	int recServerID;
	string recSymbol;
	string recServerIP;
	string recFilePath;
	int recPathMode;

	int recServerID_Backup;
	string recSymbol_Backup;
	string recServerIP_Backup;
	string recFilePath_Backup;
	int recPathMode_Backup;

	string invokeID;

private:
	virtual int GetMyMemSize();
};

///Type_SysManage_DelRecInfo
struct SIPCCMsg_SysManage_DelRecInfo : public SIPCCMsg_SysManage
{
	SIPCCMsg_SysManage_DelRecInfo();
	~SIPCCMsg_SysManage_DelRecInfo()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}

	string gwName;
	string computerSymbol;

	string invokeID;

private:
	virtual int GetMyMemSize();
};

///Type_Gateway_InsertDateOperation
struct SIPCCMsg_Gateway_InsertDateOperation : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_InsertDateOperation();
	~SIPCCMsg_Gateway_InsertDateOperation()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	};

	string tableName;
	string fieldNameList;
	string valueNameList;

	virtual int GetMyMemSize();
};

//voice recognition
struct SIPCCMsg_VoiceRecognition:public SIPCCMessage
{
	SIPCCMsg_VoiceRecognition();
	~SIPCCMsg_VoiceRecognition()
	{
		ReleaseMemory();
	};

	virtual int GetMyMemSize(){return 0;}
	virtual int FillBuf(char*& thebuf){return 0;}
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0){}
	virtual void ReleaseMemory(){}

public:
	string strInvokeId;
};

struct SIPCCMsg_VoiceRecognition_RequestRec:public SIPCCMsg_VoiceRecognition
{
	SIPCCMsg_VoiceRecognition_RequestRec();
	~SIPCCMsg_VoiceRecognition_RequestRec()
	{
		ReleaseMemory();
	};

	virtual int GetMyMemSize();
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0 , unsigned short port=0);
	virtual void ReleaseMemory(){};

	string strRecFile;//带全路径的录音文件名
	string strKeywords;//关键字列表，格式:1=kw1|2=kw2|
};

struct SIPCCMsg_VoiceRecognition_ResponseRec:public SIPCCMsg_VoiceRecognition
{
	SIPCCMsg_VoiceRecognition_ResponseRec();
	~SIPCCMsg_VoiceRecognition_ResponseRec(){ReleaseMemory();};

	virtual int GetMyMemSize();
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0 , unsigned short port=0);
	virtual void ReleaseMemory(){};

	//	int retKwId;//关键字ID
	string strRetKwCount;//关键字次数(格式：1=5;2=1;3=2;)，表示标识为1的关键字出现了5次...
};

struct SIPCCMsg_VoiceRecognition_AudioPacket:public SIPCCMsg_VoiceRecognition
{
	SIPCCMsg_VoiceRecognition_AudioPacket();
	~SIPCCMsg_VoiceRecognition_AudioPacket(){ReleaseMemory();};

	virtual int GetMyMemSize();
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

	int lineNo;//线号
	bool endPacket;//是否最后一个包
	int packetSeq;//包序号
	int audioLength;//包长度
	string audioData;//包数据
};

// add code by hyj n2014-1-6
struct SIPCCMsg_WebService_InterfaceToMessage: public SIPCCMsg_ACD
{
	SIPCCMsg_WebService_InterfaceToMessage();
	~SIPCCMsg_WebService_InterfaceToMessage(){ReleaseMemory();};

	virtual int GetMyMemSize();
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0 , unsigned short port=0);
	virtual void ReleaseMemory(){};
  
	int interfaceType;			    //接口类型

	string interfaceContent;		//拼好的XML格式的接口参数

	string handleId;

	string  agentId;                //座席名称
};
//
struct SIPCCMsg_WebService_InterfaceToMessageConf: public SIPCCMsg_ACD
{
	SIPCCMsg_WebService_InterfaceToMessageConf();
	~SIPCCMsg_WebService_InterfaceToMessageConf(){ReleaseMemory();};

	virtual int GetMyMemSize();
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0 , unsigned short port=0);
	virtual void ReleaseMemory(){};
	string handleId;
         
};


//
struct SIPCCMsg_WebService_HeartBeat: public SIPCCMsg_ACD
{
	SIPCCMsg_WebService_HeartBeat();
	~SIPCCMsg_WebService_HeartBeat(){ReleaseMemory();};

	virtual int GetMyMemSize();
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0 , unsigned short port=0);
	virtual void ReleaseMemory(){};
	string handleId;

	string agentId;		//Client WebService正在服务的座席名

	string lanIP_Client;		//Client WebService的内网IP

	string wanIP_Client;	//Client WebService的公网IP

	string port_Client;		//Client WebService的UDP使用端口号
};
//
//
struct SIPCCMsg_WebService_HeartBeatConf: public SIPCCMsg_ACD
{
	SIPCCMsg_WebService_HeartBeatConf();
	~SIPCCMsg_WebService_HeartBeatConf(){ReleaseMemory();};

	virtual int GetMyMemSize();
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0 , unsigned short port=0);
	virtual void ReleaseMemory(){};
	string handleId;
	
};

///SIPCCMsg_ACD_SMSInfo
struct SIPCCMsg_ACD_SMSInfo : public SIPCCMsg_ACD
{
 
	SIPCCMsg_ACD_SMSInfo();
	~SIPCCMsg_ACD_SMSInfo(){ReleaseMemory();};

	virtual int GetMyMemSize();
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0 , unsigned short port=0);
	virtual void ReleaseMemory(){};

	string sHandleId;
	string sChannelType;
	int iNonsync;				//默认为0
	int iEventType;			//默认为-1
	string sManagerid;
	string sAgentid;
	string sMobilePhoneNo;
	string sCallId;

};
///SIPCCMsg_PhoneSearch_SMSInfoConf
struct SIPCCMsg_PhoneSearch_SMSInfoConf : public SIPCCMsg_ACD
{

	SIPCCMsg_PhoneSearch_SMSInfoConf();
	~SIPCCMsg_PhoneSearch_SMSInfoConf(){ReleaseMemory();};

	virtual int GetMyMemSize();
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0 , unsigned short port=0);
	virtual void ReleaseMemory(){};

	string sHandleId;
	int bSucc;			//0表示保存Redis失败，1表示成功；

};

///Type_ACD_RefreshSkillGroupConf
struct SIPCCMsg_ACD_RefreshSkillGroupConf : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_RefreshSkillGroupConf();
	~SIPCCMsg_ACD_RefreshSkillGroupConf()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0 , unsigned short port=0);
	virtual void ReleaseMemory()
	{
	};

	string sInvokeId;
	string sSGId;
	int bLoad;			//0表示删除操作，1表示新增操作；

private:
	virtual int GetMyMemSize();

};

///Type_ACD_NotifyACDLicenceConf
struct SIPCCMsg_ACD_NotifyACDLicenceConf : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_NotifyACDLicenceConf();
	~SIPCCMsg_ACD_NotifyACDLicenceConf()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0 , unsigned short port=0);
	virtual void ReleaseMemory()
	{
	};

	string sInvokeId;

private:
	virtual int GetMyMemSize();

};

///Type_Guide_RefreshKeywordConf
struct SIPCCMsg_Guide_RefreshKeywordConf : public SIPCCMsg_Guide
{
	SIPCCMsg_Guide_RefreshKeywordConf();
	~SIPCCMsg_Guide_RefreshKeywordConf()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0 , unsigned short port=0);
	virtual void ReleaseMemory()
	{
	};

	string sInvokeId;
	string sKeyword;
	int bLoad;			//0表示删除操作，1表示新增操作；

private:
	virtual int GetMyMemSize();

};

///Type_ServerProxy_LoadServerInfoConfConf
struct SIPCCMsg_ServerProxy_LoadServerInfoConfConf : public SIPCCMsg_ServerProxy
{
	SIPCCMsg_ServerProxy_LoadServerInfoConfConf();
	~SIPCCMsg_ServerProxy_LoadServerInfoConfConf()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0 , unsigned short port=0);
	virtual void ReleaseMemory()
	{
	};

	string sInvokeId;
	string sManagerId;
	int bLoad;			//0表示删除操作，1表示新增操作；

private:
	virtual int GetMyMemSize();

};

///Type_OneKeySwitch_RefreshGatewayInfoConf
struct SIPCCMsg_OneKeySwitch_RefreshGatewayInfoConf : public SIPCCMsg_OneKeySwitch
{
	SIPCCMsg_OneKeySwitch_RefreshGatewayInfoConf();
	~SIPCCMsg_OneKeySwitch_RefreshGatewayInfoConf()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0 , unsigned short port=0);
	virtual void ReleaseMemory()
	{
	};

	string sInvokeId;
	string sGatewayName;
	int bLoad;			//0表示删除操作，1表示新增操作；

private:
	virtual int GetMyMemSize();

};

///Type_OneKeySwitch_RefreshRegisterInfoConf
struct SIPCCMsg_OneKeySwitch_RefreshRegisterInfoConf : public SIPCCMsg_OneKeySwitch
{
	SIPCCMsg_OneKeySwitch_RefreshRegisterInfoConf();
	~SIPCCMsg_OneKeySwitch_RefreshRegisterInfoConf()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0 , unsigned short port=0);
	virtual void ReleaseMemory()
	{
	};

	string sInvokeId;
	int iServiceId;
	int bLoad;			//0表示删除操作，1表示新增操作；

private:
	virtual int GetMyMemSize();

};

///Type_Gateway_UnAnsweredCallConf
struct SIPCCMsg_Gateway_UnAnsweredCallConf : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_UnAnsweredCallConf();
	~SIPCCMsg_Gateway_UnAnsweredCallConf()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	};
	string invokeId;
	virtual int GetMyMemSize();
};

///Type_UnAnsweredAgentCallConf
struct SIPCCMsg_UnAnsweredAgentCallConf : public SIPCCMsg_Gateway
{
	SIPCCMsg_UnAnsweredAgentCallConf()
	{
		msgType =Type_UnAnsweredAgentCallConf;

		invokeId="";



	};
	~SIPCCMsg_UnAnsweredAgentCallConf()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	};


	string invokeId;	
	virtual int GetMyMemSize();
};

///Type_Gateway_InsertDateOperationConf
struct SIPCCMsg_Gateway_InsertDateOperationConf : public SIPCCMsg_Gateway
{
	SIPCCMsg_Gateway_InsertDateOperationConf()
	{
		msgType =Type_Gateway_InsertDateOperationConf;

		invokeId="";

	}
	~SIPCCMsg_Gateway_InsertDateOperationConf()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	};

	string invokeId;

	virtual int GetMyMemSize();
};

///SIPCCMsg_Record_AgentTestStartRecord
struct SIPCCMsg_Record_AgentTestStartRecord : public SIPCCMsg_Record
{

	SIPCCMsg_Record_AgentTestStartRecord();
	~SIPCCMsg_Record_AgentTestStartRecord(){ReleaseMemory();};

	virtual int GetMyMemSize();
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

	string invokeID;					//呼叫事务
	int cSeq;					//同一个invokeID的计数标记
	string PresideAgentAccount;					//主动方座席账号
};

///SIPCCMsg_Record_AgentTestStartRecordConf
struct SIPCCMsg_Record_AgentTestStartRecordConf : public SIPCCMsg_Record
{

	SIPCCMsg_Record_AgentTestStartRecordConf();
	~SIPCCMsg_Record_AgentTestStartRecordConf(){ReleaseMemory();};

	virtual int GetMyMemSize();
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

	string invokeID;					//呼叫事务
	int cSeq;					//同一个invokeID的计数标记
	string PresideAgentAccount;					//主动方座席账号
};

///SIPCCMsg_Record_AgentTestStartPlayback
struct SIPCCMsg_Record_AgentTestStartPlayback : public SIPCCMsg_Record
{

	SIPCCMsg_Record_AgentTestStartPlayback();
	~SIPCCMsg_Record_AgentTestStartPlayback(){ReleaseMemory();};

	virtual int GetMyMemSize();
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

	string invokeID;					//呼叫事务
	int cSeq;					//同一个invokeID的计数标记
	string PresideAgentAccount;					//主动方座席账号
};

///SIPCCMsg_Record_AgentTestStartPlaybackConf
struct SIPCCMsg_Record_AgentTestStartPlaybackConf : public SIPCCMsg_Record
{

	SIPCCMsg_Record_AgentTestStartPlaybackConf();
	~SIPCCMsg_Record_AgentTestStartPlaybackConf(){ReleaseMemory();};

	virtual int GetMyMemSize();
	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

	string invokeID;					//呼叫事务
	int cSeq;					//同一个invokeID的计数标记
	string PresideAgentAccount;					//主动方座席账号
};

///Type_Client_SendErrCodeInfo
struct SIPCCMsg_Client_SendErrCodeInfo : public SIPCCMsg_Client
{
	SIPCCMsg_Client_SendErrCodeInfo();
	~SIPCCMsg_Client_SendErrCodeInfo()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

	int errcode;
	string managerid;
	string agentname;

private:
	virtual int GetMyMemSize();
};

///Type_SysManage_LoadGWCorpInfoConf
struct SIPCCMsg_SysManage_LoadGWCorpInfoConf : public SIPCCMsg_SysManage 
{
	SIPCCMsg_SysManage_LoadGWCorpInfoConf();
	~SIPCCMsg_SysManage_LoadGWCorpInfoConf()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

	string invokeId;

private:
	virtual int GetMyMemSize();
};

///Type_SysManage_LoadConfigInfoConf
struct SIPCCMsg_SysManage_LoadConfigInfoConf : public SIPCCMsg_SysManage 
{
	SIPCCMsg_SysManage_LoadConfigInfoConf();
	~SIPCCMsg_SysManage_LoadConfigInfoConf()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};

	string invokeId;

private:
	virtual int GetMyMemSize();
};
///////////////////////////////////////////////////////////////////////////
///Class_TTS
struct SIPCCMsg_TTS : public SIPCCMessage
{
	SIPCCMsg_TTS(){msgClass = Class_TTS;};
	~SIPCCMsg_TTS()
	{
		ReleaseMemory();
	};

	virtual int GetMyMemSize(){return 0;}
	virtual int FillBuf(char*& thebuf){return 0;}
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0){}
	virtual void ReleaseMemory(){}
};

///Type_TTS_Request
struct SIPCCMsg_TTS_Request : public SIPCCMsg_TTS
{
	string sInvokeId;
	int nIndex;
	int nType;
	string sRequestText;

	SIPCCMsg_TTS_Request()
	{
		sInvokeId = "";
		msgType = Type_TTS_Request;
		nIndex = 0;
		nType = 0;
		sRequestText = "";
	};
	~SIPCCMsg_TTS_Request()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};
private:	
	virtual int GetMyMemSize();
};

struct SIPCCMsg_TTS_Result : public SIPCCMsg_TTS
{
	string sInvokeId;
	int nIndex;
	int nType;
	string sPathFileName;
	bool    bSuccess;

	SIPCCMsg_TTS_Result()
	{
		sInvokeId = "";
		msgType = Type_TTS_Result;
		nIndex = 0;
		nType = 0;
		sPathFileName = "";
		bSuccess = false;
	};
	~SIPCCMsg_TTS_Result()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};
private:	
	virtual int GetMyMemSize();
};

struct SIPCCMsg_TTS_Cancel : public SIPCCMsg_TTS
{
	string sInvokeId;
	int nIndex;

	SIPCCMsg_TTS_Cancel()
	{		
		msgType = Type_TTS_Cancel;
		sInvokeId = "";
		nIndex = 0;
	};
	~SIPCCMsg_TTS_Cancel()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory(){};
private:	
	virtual int GetMyMemSize();
};

///Type_SysManage_AgentInfoChange
struct SIPCCMsg_SysManage_AgentInfoChange : public SIPCCMsg_SysManage
{
	SIPCCMsg_SysManage_AgentInfoChange();
	~SIPCCMsg_SysManage_AgentInfoChange()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual void ReleaseMemory()
	{
	}

	string agentName;
	int cause;
private:
	virtual int GetMyMemSize();
};

///Type_Redirect_GetService
struct SIPCCMsg_Redirect_GetService : public SIPCCMsg_Redirect
{
	SIPCCMsg_Redirect_GetService();
	~SIPCCMsg_Redirect_GetService()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0 , unsigned short port=0);
	virtual void ReleaseMemory()
	{
	};

	int serviceType;
	string domainName;
	string queryServiceList;
	string identifyingCode;
	string netPath;

private:
	virtual int GetMyMemSize();

};

///Type_Redirect_GetServiceConf
struct SIPCCMsg_Redirect_GetServiceConf : public SIPCCMsg_Redirect
{
	SIPCCMsg_Redirect_GetServiceConf();
	~SIPCCMsg_Redirect_GetServiceConf()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0 , unsigned short port=0);
	virtual void ReleaseMemory()
	{
	};

	string serviceList;
	string redisList;
	string netPath;

private:
	virtual int GetMyMemSize();

};

///Class_CClient
struct SIPCCMsg_CClient : public SIPCCMessage
{
	SIPCCMsg_CClient()
	{
		msgClass = Class_CClient;
	};

	~SIPCCMsg_CClient()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf) = 0;
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0) = 0;
	virtual void ReleaseMemory(){};
};

///Type_CClient_Login
struct SIPCCMsg_CClient_Login : public SIPCCMsg_CClient
{
	SIPCCMsg_CClient_Login();
	~SIPCCMsg_CClient_Login()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0 , unsigned short port=0);
	virtual void ReleaseMemory()
	{
	};

	string account;
	string password;

private:
	virtual int GetMyMemSize();

};

///Type_CClient_HeartBeat
struct SIPCCMsg_CClient_HeartBeat : public SIPCCMsg_CClient
{
	SIPCCMsg_CClient_HeartBeat();
	~SIPCCMsg_CClient_HeartBeat()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0 , unsigned short port=0);
	virtual void ReleaseMemory()
	{
	};

	string account;

	int curState;

private:
	virtual int GetMyMemSize();

};

///Type_CClient_CMakeCall
struct SIPCCMsg_CClient_CMakeCall : public SIPCCMsg_CClient
{
	SIPCCMsg_CClient_CMakeCall();
	~SIPCCMsg_CClient_CMakeCall()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0 , unsigned short port=0);
	virtual void ReleaseMemory()
	{
	};

	string account;
	string targetName;
	int targetType;
	string callerNoForSend;
	string uuiDate;

private:
	virtual int GetMyMemSize();

};

///Type_CClient_CallArrived
struct SIPCCMsg_CClient_CallArrived : public SIPCCMsg_CClient
{
	SIPCCMsg_CClient_CallArrived();
	~SIPCCMsg_CClient_CallArrived()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0 , unsigned short port=0);
	virtual void ReleaseMemory()
	{
	};

	string callID;
	string callerName;
	string calledName;
	string calledNickname;
	string netPath;

	CAudioStreamDescription audioStreamDescription;

private:
	virtual int GetMyMemSize();

};

///Type_CClient_CallAnswered
struct SIPCCMsg_CClient_CallAnswered : public SIPCCMsg_CClient
{
	SIPCCMsg_CClient_CallAnswered();
	~SIPCCMsg_CClient_CallAnswered()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0 , unsigned short port=0);
	virtual void ReleaseMemory()
	{
	};

	string callID;
	string callerName;
	string calledName;
	string netPath;

private:
	virtual int GetMyMemSize();

};

///Type_CClient_HangupCall
struct SIPCCMsg_CClient_HangupCall : public SIPCCMsg_CClient
{
	SIPCCMsg_CClient_HangupCall();
	~SIPCCMsg_CClient_HangupCall()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0 , unsigned short port=0);
	virtual void ReleaseMemory()
	{
	};

	string account;
	string targetName;
	int targetType;
	string callID;

private:
	virtual int GetMyMemSize();

};

///Type_CClient_HangupCallConf
struct SIPCCMsg_CClient_HangupCallConf : public SIPCCMsg_CClient
{
	SIPCCMsg_CClient_HangupCallConf();
	~SIPCCMsg_CClient_HangupCallConf()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0 , unsigned short port=0);
	virtual void ReleaseMemory()
	{
	};

	string callID;
	string account;
	int result;
	
private:
	virtual int GetMyMemSize();

};

///Type_Login_CCLoginConf
struct SIPCCMsg_Login_CCLoginConf : public SIPCCMsg_Login
{
	SIPCCMsg_Login_CCLoginConf();
	~SIPCCMsg_Login_CCLoginConf()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0 , unsigned short port=0);
	virtual void ReleaseMemory()
	{
	};

	string cause;
	int loginResult;

private:
	virtual int GetMyMemSize();

};

///Class_CProxy
struct SIPCCMsg_CProxy : public SIPCCMessage
{
	SIPCCMsg_CProxy()
	{
		msgClass = Class_CProxy;
	};

	~SIPCCMsg_CProxy()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf) = 0;
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0) = 0;
	virtual void ReleaseMemory(){};
};

///Type_CProxy_HeartBeatConf
struct SIPCCMsg_CProxy_HeartBeatConf : public SIPCCMsg_CProxy
{
	SIPCCMsg_CProxy_HeartBeatConf();
	~SIPCCMsg_CProxy_HeartBeatConf()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0 , unsigned short port=0);
	virtual void ReleaseMemory()
	{
	};

	string account;

private:
	virtual int GetMyMemSize();

};

///Type_CProxy_CMakeCallConf
struct SIPCCMsg_CProxy_CMakeCallConf : public SIPCCMsg_CProxy
{
	SIPCCMsg_CProxy_CMakeCallConf();
	~SIPCCMsg_CProxy_CMakeCallConf()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0 , unsigned short port=0);
	virtual void ReleaseMemory()
	{
	};

	string account;
	int result;
	string cause;

private:
	virtual int GetMyMemSize();

};

///Type_CProxy_CMakeCall
struct SIPCCMsg_CProxy_CMakeCall : public SIPCCMsg_CProxy
{
	SIPCCMsg_CProxy_CMakeCall();
	~SIPCCMsg_CProxy_CMakeCall()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0 , unsigned short port=0);
	virtual void ReleaseMemory()
	{
	};

	string account;
	string targetName;
	int targetType;
	string callerNoForSend;
	string uuiDate;
	string netPath;
	string targetPosition;

private:
	virtual int GetMyMemSize();

};

///Type_CProxy_CallDelivered
struct SIPCCMsg_CProxy_CallDelivered : public SIPCCMsg_CProxy
{
	SIPCCMsg_CProxy_CallDelivered();
	~SIPCCMsg_CProxy_CallDelivered()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0 , unsigned short port=0);
	virtual void ReleaseMemory()
	{
	};

	string callID;
	string callerName;
	string keyword;
	string uuiDate;
	string netPath;

private:
	virtual int GetMyMemSize();

};

///Type_CProxy_CallArrived
struct SIPCCMsg_CProxy_CallArrived : public SIPCCMsg_CProxy
{
	SIPCCMsg_CProxy_CallArrived();
	~SIPCCMsg_CProxy_CallArrived()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0 , unsigned short port=0);
	virtual void ReleaseMemory()
	{
	};

	string callID;
	string callerName;
	string calledName;
	string calledNickname;
	string netPath;

private:
	virtual int GetMyMemSize();

};

///Type_CProxy_CallAnswered
struct SIPCCMsg_CProxy_CallAnswered : public SIPCCMsg_CProxy
{
	SIPCCMsg_CProxy_CallAnswered();
	~SIPCCMsg_CProxy_CallAnswered()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0 , unsigned short port=0);
	virtual void ReleaseMemory()
	{
	};

	string callID;
	string callerName;
	string calledName;

private:
	virtual int GetMyMemSize();

};

///Type_CProxy_CallStart
struct SIPCCMsg_CProxy_CallStart : public SIPCCMsg_CProxy
{
	SIPCCMsg_CProxy_CallStart();
	~SIPCCMsg_CProxy_CallStart()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0 , unsigned short port=0);
	virtual void ReleaseMemory()
	{
	};

	string callID;
	string callerName;
	string netPath;

private:
	virtual int GetMyMemSize();

};

///Type_CProxy_QueryGW
struct SIPCCMsg_CProxy_QueryGW : public SIPCCMsg_CProxy
{
	SIPCCMsg_CProxy_QueryGW();
	~SIPCCMsg_CProxy_QueryGW()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0 , unsigned short port=0);
	virtual void ReleaseMemory()
	{
	};

	string callerName;
	string callerNoForSend;

	string sPrefix;		//座席拨号前缀
	string sPhoneNum;   //座席呼叫号码，未组合前缀的号码
	string sAreaCode;   //区位码服务器上匹配的结果。如果此值为空，就代表区位码服务器没有找到匹配结果或者客户端没有收到区位码服务器匹配结果
	int iMatchResult;   //0代表区位码服务器匹配结果是依据前缀得出的，1代表区位码服务器匹配结果是依据座席呼叫号码得出的。

private:
	virtual int GetMyMemSize();

};

///Type_CProxy_CMakeCall2
struct SIPCCMsg_CProxy_CMakeCall2 : public SIPCCMsg_CProxy
{
	SIPCCMsg_CProxy_CMakeCall2();
	~SIPCCMsg_CProxy_CMakeCall2()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0 , unsigned short port=0);
	virtual void ReleaseMemory()
	{
	};

	string callID;
	string account;
	string targetName;
	int targetType;
	string uuiDate;
	string nickname;
	string callerNoForSend;
	string invokeID;
	string netPath;
	string targetPosition;

private:
	virtual int GetMyMemSize();

};

///Type_CProxy_HangupCall
struct SIPCCMsg_CProxy_HangupCall : public SIPCCMsg_CProxy
{
	SIPCCMsg_CProxy_HangupCall();
	~SIPCCMsg_CProxy_HangupCall()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0 , unsigned short port=0);
	virtual void ReleaseMemory()
	{
	};

	string account;
	string targetName;
	int targetType;
	string callID;

private:
	virtual int GetMyMemSize();

};

///Type_CProxy_HangupCallConf
struct SIPCCMsg_CProxy_HangupCallConf : public SIPCCMsg_CProxy
{
	SIPCCMsg_CProxy_HangupCallConf();
	~SIPCCMsg_CProxy_HangupCallConf()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0 , unsigned short port=0);
	virtual void ReleaseMemory()
	{
	};

	string callID;
	string account;

private:
	virtual int GetMyMemSize();

};

///Type_CProxy_CallHanguped
struct SIPCCMsg_CProxy_CallHanguped : public SIPCCMsg_CProxy
{
	SIPCCMsg_CProxy_CallHanguped();
	~SIPCCMsg_CProxy_CallHanguped()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0 , unsigned short port=0);
	virtual void ReleaseMemory()
	{
	};

	string callID;
	string account;
	string userName;

private:
	virtual int GetMyMemSize();

};

///Type_SysManage_RefreshRedis
struct SIPCCMsg_SysManage_RefreshRedis : public SIPCCMsg_SysManage
{
	SIPCCMsg_SysManage_RefreshRedis();
	~SIPCCMsg_SysManage_RefreshRedis()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0 , unsigned short port=0);
	virtual void ReleaseMemory()
	{
	};

	string invokeId;
	string ACDServerList;
	string corpList;
	int forceRefresh;

private:
	virtual int GetMyMemSize();

};

///Type_SysManage_RefreshRedisConf
struct SIPCCMsg_SysManage_RefreshRedisConf : public SIPCCMsg_SysManage
{
	SIPCCMsg_SysManage_RefreshRedisConf();
	~SIPCCMsg_SysManage_RefreshRedisConf()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0 , unsigned short port=0);
	virtual void ReleaseMemory()
	{
	};

	string invokeId;

private:
	virtual int GetMyMemSize();

};

//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
///////////////////////////////////////////////////////////////////////////
///Class_RouteSelect

enum E_EouteSelect_Type
{
	E_EouteSelect_Server = 1,
	E_EouteSelect_Gateway,
	E_EouteSelect_Agent,
	E_EouteSelect_Ctrl,
};

struct SIPCCMsg_RouteSelect : public SIPCCMessage
{
	SIPCCMsg_RouteSelect(){msgClass = Class_RouteSelect;};
	~SIPCCMsg_RouteSelect()
	{
	};

	virtual int GetMyMemSize(){return 0;}
	virtual int FillBuf(char*& thebuf){return 0;}
	virtual void AnalyzeBuf(char* thebuf, int msgsize,unsigned long ip=0, unsigned short port=0){}
};

//struct SIPCCMsg_RouteSelect_Register : public SIPCCMsg_RouteSelect
//{
//	SIPCCMsg_RouteSelect_Register()
//	{
//		msgType = Type_RouteSelect_Register;
//	}
//	~SIPCCMsg_RouteSelect_Register()
//	{
//	};
//
//	virtual int FillBuf(char*& thebuf);
//	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
//	virtual int GetMyMemSize();
//
//	int InvokeId;
//	int Id;
//	int Type;
//	unsigned long Ip;
//	unsigned short MainPort;
//	unsigned short TestPort;
//};



//struct SIPCCMsg_RouteSelect_AddGw : public SIPCCMsg_RouteSelect
//{
//	SIPCCMsg_RouteSelect_AddGw()
//	{
//		msgType = Type_RouteSelect_AddGw;
//	}
//	~SIPCCMsg_RouteSelect_AddGw()
//	{
//	};
//
//	virtual int FillBuf(char*& thebuf);
//	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
//	virtual int GetMyMemSize();
//
//	int Id;
//	int Type;
//	unsigned long Ip;
//	unsigned short MainPort;
//	unsigned short TestPort;
//};
//
//struct SIPCCMsg_RouteSelect_RegisterConf : public SIPCCMsg_RouteSelect
//{
//	SIPCCMsg_RouteSelect_RegisterConf()
//	{
//		msgType = Type_RouteSelect_RegisterConf;
//	}
//	~SIPCCMsg_RouteSelect_RegisterConf()
//	{
//	};
//
//	virtual int FillBuf(char*& thebuf);
//	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
//	virtual int GetMyMemSize();
//
//	int InvokeId;
//	map<int, S_RouteSelect_Node> OtherServerMap;
//	map<int, S_RouteSelect_Node> GatewayMap;
//};

struct S_RouteSelect_TestReportNode
{
	int LocalId;
	int DestId;
	int Type;
	double LostRate;
	int DelayAvg;
	double DelayVariance;
};

//struct SIPCCMsg_RouteSelect_NetTestReport : public SIPCCMsg_RouteSelect
//{
//	SIPCCMsg_RouteSelect_NetTestReport()
//	{
//		msgType = Type_RouteSelect_NetTestReport;
//	}
//	~SIPCCMsg_RouteSelect_NetTestReport()
//	{
//	};
//
//	virtual int FillBuf(char*& thebuf);
//	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
//	virtual int GetMyMemSize();
//
//	int InvokeId;
//	int Id;
//	map<int, S_RouteSelect_TestReportNode> ReportMap;
//};
//
//struct SIPCCMsg_RouteSelect_NetTestReportConf : public SIPCCMsg_RouteSelect
//{
//	SIPCCMsg_RouteSelect_NetTestReportConf()
//	{
//		msgType = Type_RouteSelect_NetTestReportConf;
//	}
//	~SIPCCMsg_RouteSelect_NetTestReportConf()
//	{
//	};
//
//	virtual int FillBuf(char*& thebuf);
//	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
//	virtual int GetMyMemSize();
//
//	int InvokeId;
//};

struct SIPCCMsg_RouteSelect_RouteSelect : public SIPCCMsg_RouteSelect
{
	SIPCCMsg_RouteSelect_RouteSelect()
	{
		msgType = Type_RouteSelect_RouteSelect;
	}
	~SIPCCMsg_RouteSelect_RouteSelect()
	{
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual int GetMyMemSize();

	int InvokeId;
	string CallId;
	int DestGwId;
	map<int, S_RouteSelect_TestReportNode> ReportMap;
};

struct SIPCCMsg_RouteSelect_RouteSelectConf : public SIPCCMsg_RouteSelect
{
	SIPCCMsg_RouteSelect_RouteSelectConf()
	{
		msgType = Type_RouteSelect_RouteSelectConf;
	}
	~SIPCCMsg_RouteSelect_RouteSelectConf()
	{
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual int GetMyMemSize();

	int InvokeId;
	list<S_RouteSelect_Node> RouteList; // 2015-7-15
};

struct SIPCCMsg_RouteSelect_RouteRequest : public SIPCCMsg_RouteSelect
{
	SIPCCMsg_RouteSelect_RouteRequest()
	{
		msgType = Type_RouteSelect_RouteRequest;
	}
	~SIPCCMsg_RouteSelect_RouteRequest()
	{
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual int GetMyMemSize();

	int InvokeId;
	int DestType;
	string CallId;
	unsigned long GwIp;
	unsigned short GwPort;
	list<S_RouteSelect_Node> OtherServerList;
};

struct SIPCCMsg_RouteSelect_RouteRequestConf : public SIPCCMsg_RouteSelect
{
	SIPCCMsg_RouteSelect_RouteRequestConf()
	{
		msgType = Type_RouteSelect_RouteRequestConf;
	}
	~SIPCCMsg_RouteSelect_RouteRequestConf()
	{
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual int GetMyMemSize();

	int InvokeId;
	int Succ;
	int ChannelId;
	unsigned short Port;
};

struct SIPCCMsg_RouteSelect_RouteStop : public SIPCCMsg_RouteSelect
{
	SIPCCMsg_RouteSelect_RouteStop()
	{
		msgType = Type_RouteSelect_RouteStop;
	}
	~SIPCCMsg_RouteSelect_RouteStop()
	{
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual int GetMyMemSize();

	int InvokeId;
	int ChannelId;
	list<S_RouteSelect_Node> OtherServerList;
};

struct SIPCCMsg_RouteSelect_RouteStopConf : public SIPCCMsg_RouteSelect
{
	SIPCCMsg_RouteSelect_RouteStopConf()
	{
		msgType = Type_RouteSelect_RouteStopConf;
	}
	~SIPCCMsg_RouteSelect_RouteStopConf()
	{
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0, unsigned short port=0);
	virtual int GetMyMemSize();

	int InvokeId;
};
//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH

///Type_ACD_CHangupCallConf
struct SIPCCMsg_ACD_CHangupCallConf : public SIPCCMsg_ACD
{
	SIPCCMsg_ACD_CHangupCallConf();
	~SIPCCMsg_ACD_CHangupCallConf()
	{
		ReleaseMemory();
	};

	virtual int FillBuf(char*& thebuf);
	virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip=0 , unsigned short port=0);
	virtual void ReleaseMemory()
	{
	};

	string callID;
	string agentName;
	string keyword;

	string account;

private:
	virtual int GetMyMemSize();

};


///Type_FileTransfer
struct SIPCCMsg_FileTransfer : public SIPCCMessage
{
public:
    SIPCCMsg_FileTransfer();

	unsigned short InfoLen;
	
    virtual int FillBuf(char*& thebuf);
    virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip = 0, unsigned short port = 0);
    virtual int GetMyMemSize();
};

///Type_FileTransfer_UploadRequest
struct SIPCCMsg_FileTransfer_UploadRequest : public SIPCCMsg_FileTransfer
{
public:
    SIPCCMsg_FileTransfer_UploadRequest();
	
    string agentID;
    string description;
    string address;
	
    virtual int FillBuf(char*& thebuf);
    virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip = 0, unsigned short port = 0);
    virtual int GetMyMemSize();
};

///Type_FileTransfer_StartUpload
struct SIPCCMsg_FileTransfer_StartUpload : public SIPCCMsg_FileTransfer
{
public:
    SIPCCMsg_FileTransfer_StartUpload();
	
    string agentID;
    string fileName;
    uint64_t fileSize;
    uint64_t createTime;
    uint64_t lastModifyTime;
	
    virtual int FillBuf(char*& thebuf);
    virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip = 0, unsigned short port = 0);
    virtual int GetMyMemSize();
};

///Type_FileTransfer_UploadCompleted;
struct SIPCCMsg_FileTransfer_UploadCompleted : public SIPCCMsg_FileTransfer
{
public:
    SIPCCMsg_FileTransfer_UploadCompleted();
	
    virtual int FillBuf(char*& thebuf);
    virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip = 0, unsigned short port = 0);
    virtual int GetMyMemSize();
};

///Type_FileTransfer_FileData
struct SIPCCMsg_FileTransfer_FileData : public SIPCCMsg_FileTransfer
{
public:
	SIPCCMsg_FileTransfer_FileData();
	
	unsigned int dataLen;
	
    virtual int FillBuf(char*& thebuf);
    virtual void AnalyzeBuf(char* thebuf, int msgsize, unsigned long ip = 0, unsigned short port = 0);
    virtual int GetMyMemSize();
};
