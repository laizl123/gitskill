#if !defined(AFX_AGENTPANELOCXCTL_H__F5D81D23_B187_46F0_B7A0_B514AC8F7D1B__INCLUDED_)
#define AFX_AGENTPANELOCXCTL_H__F5D81D23_B187_46F0_B7A0_B514AC8F7D1B__INCLUDED_

#include "SockHandle.h"
#include <afxmt.h>
#include "IPCCMessage.h"
#include "CreditUDPThread.h"
#include "FuncReturnObject.h"
#include "GetFreeAgentDlg.h"
#include "GetTalkAgentDlg.h"
#include <objsafe.h>
#include "SubPackData.h"
#include "NewSettingsDlg.h"

class CAgentPanelOcxCtrl : public COleControl, public CSockHandle
{
	DECLARE_DYNCREATE(CAgentPanelOcxCtrl)
		
		// Constructor
public:
	CAgentPanelOcxCtrl();
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAgentPanelOcxCtrl)
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	virtual BOOL DestroyWindow();
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL
	
	// SOCKET
	CCreditUDPThread	m_AgentSock;
	// BEEP声音
	static DWORD WINAPI BeepThread(LPVOID lpThis);
	static void MyBeep(int nIndex, int freq, int dura);
	static BOOL m_bStopBeep;
	
	LRESULT OnSockMsg(WPARAM wParam, LPARAM lParam);
	
	virtual void HandleRecvMsg(char* data, int nlen);
	virtual void HandleHeartTimeOut();
	// 处理函数返回
	void HandleFuncReturn(char* data, int nlen);
	// 处理函数事件
	void HandleFuncEvent(char* data, int nlen);	
	// 处理心跳信息
	void HandleIPCCHeartBeat(char* data, int nlen);
	// 处理OCX和Service之间的通信
	void HandleOCXService(char* data, int nlen);

	void HandleSubTrans(SIPCCMsg_OCXService_SubTrans& sub);

	void SendHeartResp();//发送心跳回复

	// 重启
	BOOL m_bRestartSrv;
	// 保证正常退出不崩溃
	bool m_bInit;
	bool m_bDestroyWindow;
	bool m_bInitMsgRecv;
	
	// 等待函数返回
	CMapStringToPtr		m_mapFuncRtn;
	void AddFuncToWait(CFuncReturnObject& obj);
	BOOL WaitFuncReturn(CFuncReturnObject& obj);
	
	// 加锁
	CCriticalSection	m_LockMapFunc;
	
	// 处理事件返回
	void HandleeventOnLogin(char* data, int nlen);
	void HandleeventOnAgentLoginSucc(char* data, int nlen);
	void HandleeventOnAgentLoginFailed(char* data, int nlen);
	void HandleeventOnAgentLogoutConf(char* data, int nlen);
	void HandleeventOnAgentMakeCallConf(char* data, int nlen);
	void HandleeventOnClientStateChange(char* data, int nlen);
	void HandleeventOnCallDelivered(char* data, int nlen);
	void HandleeventOnSystemStatusInfo(char* data, int nlen);
	void HandleeventOnChatMsgDelivered(char* data, int nlen);
	void HandleeventOnQueueSize(char* data, int nlen);
	void HandleeventOnGetGroupInfo(char* data, int nlen);
	void HandleeventOnGetOneGroupFreeAgentInfo(char* data, int nlen);
	void HandleeventOnGetFullFreeAgentInfo(char* data, int nlen);
	void HandleeventOnGetFullTalkingAgentInfo(char* data, int nlen);
	void HandleeventOnAudioLostRate(char* data, int nlen);
	void HandleeventOnPreOutDialEnd(char* data, int nlen);
	void HandleeventOnUserLoginInfo(char* data, int nlen);
	void HandleeventOnAgentOutdialConf(char* data, int nlen);	
	void HandleeventOnACDSendStrMsg(char* data, int nlen);
	void HandleeventOnLoginSendStrMsg(char* data, int nlen);
	void HandleeventOnIVRReturnToAgentConf(char* data, int nlen);
	void HandleeventOnNotifyAgentLoginConf(char* data, int nlen);
	void HandleeventOnAddTalkToWebChat(char* data, int nlen);//hqh 2017.6.12 把多渠道消息独立出来
	// 处理函数
	void HandlereturnGetLoginManner(char* data, int nlen);
	void HandlereturnGetDeptment(char* data, int nlen);
	void HandlereturnGetCorp(char* data, int nlen);
	void HandlereturnGetCallType(char* data, int nlen);
	void HandlereturnGetCallFrom(char* data, int nlen);
	void HandlereturnGetPrivateData(char* data, int nlen);
	void HandlereturnGetRecInvokeID(char* data, int nlen);
	void HandlereturnGetClientState(char* data, int nlen);
	void HandlereturnGetLogonType(char* data, int nlen);
	void HandlereturnGetCallPartyType(char* data, int nlen);
	void HandlereturnGetAgentHasLogon(char* data, int nlen);
	void HandlereturnGetRoleInCompany(char* data, int nlen);
	void HandlereturnGetAgentAccount(char* data, int nlen); 
	void HandlereturnGetIsCCNUser(char* data, int nlen); 
	void HandlereturnGetAgentType(char* data, int nlen); 
	void HandlereturnGetIsHasSMS(char* data, int nlen); 
	void HandlereturnGetAgentExtNum(char* data, int nlen); 
	void HandlereturnGetAgentPhoneNo(char* data, int nlen); 
	void HandlereturnGetManagerID(char* data, int nlen);
	void HandlereturnGetIsSuperAgent(char* data, int nlen);
	void HandlereturnGetIsMasterSuperAgent(char* data, int nlen);
	void HandlereturnGetRemindTime(char* data, int nlen);
	void HandlereturnGetIsMonit(char* data, int nlen);
	void HandlereturnGetSMSParamsInfo(char* data, int nlen);
	void HandlereturnGetBriefStatisticInfo(char* data, int nlen);
	void HandlereturnGetIsCallFromACD(char* data, int nlen);
	void HandlereturnGetIsOutdailOpenUrl(char* data, int nlen);
	void HandlereturnGetIsCallInOpenUrl(char* data, int nlen);
	void HandlereturnGetIVRReturn(char* data, int nlen);
	void HandlereturnGetRecInvokePath(char* data, int nlen);
	void HandlereturnGetAgentID(char* data, int nlen);
	void HandlereturnGetParkReasons(char* data, int nlen);
	void HandlereturnGetIsOutDialMode(char* data, int nlen);
	// add by lh.wang date:2012.12.05
	void HandlereturnGetCanConference(char *data,int nlen);
	//end add
	// Implementation
protected:
	~CAgentPanelOcxCtrl();
	
	DECLARE_OLECREATE_EX(CAgentPanelOcxCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CAgentPanelOcxCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CAgentPanelOcxCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CAgentPanelOcxCtrl)		// Type name and misc status
		
		// Message maps
		//{{AFX_MSG(CAgentPanelOcxCtrl)
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	afx_msg LRESULT OnSMSSendSuccess(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnSMSSendFailed(WPARAM wParam,LPARAM lParam);	
	DECLARE_MESSAGE_MAP()
		
		// Dispatch maps
		//{{AFX_DISPATCH(CAgentPanelOcxCtrl)
	afx_msg void ActionLogon(LPCTSTR sAccount, LPCTSTR sPassword, short iLoginServerOpt, LPCTSTR sLoginServerHost);
	afx_msg void ActionLogon2(LPCTSTR sCorp, LPCTSTR sAccount, LPCTSTR sPassword, short iLoginServerOpt, LPCTSTR sLoginServerHost);
	afx_msg void ActionReset();
	afx_msg void ActionLogout();
	afx_msg void ActionLogonAgain();
	afx_msg void ActionCallDepartment(LPCTSTR sCallTarget);
	afx_msg void ActionCallAgent(LPCTSTR sCallTarget);
	afx_msg void ActionCallOtherAgent(LPCTSTR sCallTarget);
	afx_msg void ActionCallPstn(LPCTSTR sCallTarget);
	afx_msg void ActionCallExtNum(LPCTSTR sCallTarget);
	afx_msg void ActionCallOtherDepartment(LPCTSTR sCallTarget);
	afx_msg void ActionOnHook();
	afx_msg void ActionOffHook();
	afx_msg void ActionPark();
	afx_msg void ActionUnPark();
	afx_msg void ActionProcess();
	afx_msg void ActionUnProcess();
	afx_msg void ActionHold();
	afx_msg void ActionUnHold();
	afx_msg void ActionTransfer();
	afx_msg void ActionAutoTransfer();
	afx_msg void ActionStartMonit(LPCTSTR sAgentID, LPCTSTR sIP, LPCTSTR sPort);
	afx_msg void ActionStopMonit();
	afx_msg void ActionForceDisconnect(LPCTSTR sAgentID);
	afx_msg void ActionGetFullFreeAgentInfo();
	afx_msg void ActionGetGroupInfo();
	afx_msg void ActionGetOneGroupFreeAgentInfo(LPCTSTR sGroupName);
	afx_msg void ActionGetTalkingAgent();
	afx_msg void ActionSendDTMF(short iDTMFCode);
	afx_msg void ActionChangePassword(LPCTSTR sAccount, LPCTSTR sOldPassword, LPCTSTR sNewPassword);
	afx_msg void ActionChangeEarphoneVolume(short iNewVolume);
	afx_msg void ActionChangeMicVolume(short iNewVolume);
	afx_msg void ActionSendSMS(LPCTSTR sTargetNum, LPCTSTR sSMSContent);
	afx_msg void ActionSendChat(LPCTSTR sChatContent);
	afx_msg void ConfigPortSettings(BOOL bCustomizePort, long lAgentPort, long lAudioPort1, long lAudioPort2, BOOL bRequireTCPTransfer, BOOL bIsLanUser);
	afx_msg void ConfigRecSettings(BOOL bLocalRecord);
	afx_msg void ConfigOutDialSettings(BOOL bAutoOffhook, BOOL bOutDialMobileAddZero, LPCTSTR sAreaNum, LPCTSTR sOneKeyNum);
	afx_msg void ConfigSoundSettings(BOOL bMicAutoCtrl, BOOL bEchoRemove, BOOL bMicBostUp, BOOL bUsePCSpeaker);
	afx_msg short GetLoginManner();
	afx_msg BSTR GetDeptment();
	afx_msg BSTR GetCorp();
	afx_msg short GetCallType();
	afx_msg BSTR GetCallFrom();
	afx_msg BSTR GetPrivateData();
	afx_msg BSTR GetRecInvokeID();
	afx_msg short GetClientState();
	afx_msg short GetLogonType();
	afx_msg short GetCallPartyType();
	afx_msg BOOL GetAgentHasLogon();
	afx_msg BOOL Initialize(short iVersionType, LPCTSTR sVersionNum);
	afx_msg void Exit();
	afx_msg short GetRoleInCompany();
	afx_msg BSTR GetAgentAccount();
	afx_msg BOOL GetIsCCNUser();
	afx_msg short GetAgentType();
	afx_msg BOOL GetIsSMSEnabled();
	afx_msg BSTR GetAgentExtNum();
	afx_msg BSTR GetAgentPhoneNo();
	afx_msg BSTR GetManagerID();
	afx_msg BOOL GetIsSuperAgent();
	afx_msg BOOL GetIsMasterSuperAgent();
	afx_msg void ActionSendStrMsg(LPCTSTR sTargets, LPCTSTR sContent);
	afx_msg BSTR GetRemindTime();
	afx_msg void ActionSettings();
	afx_msg void ActionMonit();
	afx_msg void ActionAgentOutDial(LPCTSTR sCallTarget, short iCallType);
	afx_msg BOOL GetIsMonit();
	afx_msg BSTR GetSMSParamsInfo();
	afx_msg BSTR GetAllSettings();
	afx_msg BSTR GetBriefStatisticInfo(LPCTSTR sDayTime);
	afx_msg void ActionSaveBriefStatisticInfo();
	afx_msg void ActionSetMuteMode(BOOL bSetMute);
	afx_msg void ActionTransferToIVR(LPCTSTR sPrivateData, BOOL bUseDefaultTypes, LPCTSTR sLanguageType, LPCTSTR sOperationType, short iWorkingMode);
	afx_msg BSTR GetTransferToIVRParamsInfo();
	afx_msg BOOL GetIsCallFromACD();
	afx_msg void ActionUpdateSettings();
	afx_msg BOOL GetIsOutDialOpenURL();
	afx_msg short GetIVRReturn();
	afx_msg void SetProductVersion(short iVersionType, LPCTSTR sVersionNum);
	afx_msg BSTR GetRecInvokePath();
	afx_msg BSTR GetAgentID();
	afx_msg void SetOriginalData(LPCTSTR sOriginalData);
	afx_msg void ActionOutDial(LPCTSTR sCallTarget);
	afx_msg void SetSelectGroup(LPCTSTR sGroup);
	afx_msg void ActionAutoTransferEx(LPCTSTR sCallTarget);
	afx_msg void ActionOutDialWithRecSetting(LPCTSTR sTarget, LPCTSTR sRecPath);
	afx_msg void ActionOffHookWithRecSetting(LPCTSTR sRecPath);
	afx_msg BOOL GetIsCallInOpenURL();
	afx_msg BSTR GetParkReasons();
	afx_msg void SetParkReason(short iParkReasonID);
	afx_msg void SetCallerSendingInDialing(LPCTSTR sCaller);
	afx_msg void ActionJoinOutDialMode(BOOL bJoinOutDialMode);
	afx_msg BOOL GetIsOutDialMode();
	afx_msg BSTR GetMoudleFilePath();
	afx_msg void ActionSetMuteModeEx(long nDev, long nVolume, BOOL bSet);
	afx_msg void ActionStartConference();
	afx_msg void ActionEndConference();
	afx_msg BOOL GetCanConference();
	afx_msg void StopPlayAgentID();
	afx_msg void ActionACDAutoLogin();
	afx_msg void SetLogonMode(short nLoginMode);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
		
protected:
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	afx_msg LRESULT OnUpdateAllSettings(WPARAM wParam, LPARAM lParam);	
	
	// Event maps
	//{{AFX_EVENT(CAgentPanelOcxCtrl)
	void FireOnLogin(BOOL bSucc, short iState)
		{FireEvent(eventidOnLogin,EVENT_PARAM(VTS_BOOL  VTS_I2), bSucc, iState);}
	void FireOnAgentLoginSucc(BOOL bAgentExist, LPCTSTR sAgentId, short iClientState)
		{FireEvent(eventidOnAgentLoginSucc,EVENT_PARAM(VTS_BOOL  VTS_BSTR  VTS_I2), bAgentExist, sAgentId, iClientState);}
	void FireOnAgentLogoutConf(short iClientState)
		{FireEvent(eventidOnAgentLogoutConf,EVENT_PARAM(VTS_I2), iClientState);}
	void FireOnAgentMakeCallConf(short iCallingState)
		{FireEvent(eventidOnAgentMakeCallConf,EVENT_PARAM(VTS_I2), iCallingState);}
	void FireOnClientStateChange(short iClientState)
		{FireEvent(eventidOnClientStateChange,EVENT_PARAM(VTS_I2), iClientState);}
	void FireOnCallDelivered(LPCTSTR sCallID, LPCTSTR sCaller, LPCTSTR sCallee, LPCTSTR sOriginalData)
	{	FireEvent(eventidOnCallDelivered, EVENT_PARAM(VTS_BSTR  VTS_BSTR  VTS_BSTR  VTS_BSTR), sCallID, sCaller, sCallee, sOriginalData);	}
	void FireOnSystemStatusInfo(LPCTSTR sWords)
		{FireEvent(eventidOnSystemStatusInfo,EVENT_PARAM(VTS_BSTR), sWords);}
	void FireOnChatMsgDelivered(LPCTSTR sTalker, LPCTSTR sChatContent, BOOL bIsCallInfo)
		{FireEvent(eventidOnChatMsgDelivered,EVENT_PARAM(VTS_BSTR  VTS_BSTR  VTS_BOOL), sTalker, sChatContent, bIsCallInfo);}
	void FireOnQueueSize(long lQueueSize)
		{FireEvent(eventidOnQueueSize,EVENT_PARAM(VTS_I4), lQueueSize);}
	void FireOnGetGroupInfo(LPCTSTR sGroupList)
		{FireEvent(eventidOnGetGroupInfo,EVENT_PARAM(VTS_BSTR), sGroupList);}
	void FireOnGetOneGroupFreeAgentInfo(LPCTSTR sAgentList)
		{FireEvent(eventidOnGetOneGroupFreeAgentInfo,EVENT_PARAM(VTS_BSTR), sAgentList);}
	void FireOnGetFullFreeAgentInfo(LPCTSTR sAgentList)
		{FireEvent(eventidOnGetFullFreeAgentInfo,EVENT_PARAM(VTS_BSTR), sAgentList);}
	void FireOnGetFullTalkingAgentInfo(LPCTSTR sAgentList)
		{FireEvent(eventidOnGetFullTalkingAgentInfo,EVENT_PARAM(VTS_BSTR), sAgentList);}
	void FireOnAudioLostRate(LPCTSTR sRate)
		{FireEvent(eventidOnAudioLostRate,EVENT_PARAM(VTS_BSTR), sRate);}
	void FireOnAgentLoginFailed(LPCTSTR sFailingInfo)
		{FireEvent(eventidOnAgentLoginFailed,EVENT_PARAM(VTS_BSTR), sFailingInfo);}
	void FireOnServiceStateChange(short iServiceState)
		{FireEvent(eventidOnServiceStateChange,EVENT_PARAM(VTS_I2), iServiceState);}
	void FireOnPreOutDialEnd(LPCTSTR sInfo)
		{FireEvent(eventidOnPreOutDialEnd,EVENT_PARAM(VTS_BSTR), sInfo);}
	void FireOnUserLoginInfo(short iType, LPCTSTR sInfo)
		{FireEvent(eventidOnUserLoginInfo,EVENT_PARAM(VTS_I2  VTS_BSTR), iType, sInfo);}
	void FireOnAgentOutdialConf(LPCTSTR sCallID)
		{FireEvent(eventidOnAgentOutdialConf,EVENT_PARAM(VTS_BSTR), sCallID);}
	void FireOnACDSendStrMsg(LPCTSTR stheSender, LPCTSTR smsgContent)
		{FireEvent(eventidOnACDSendStrMsg,EVENT_PARAM(VTS_BSTR  VTS_BSTR), stheSender, smsgContent);}
	void FireOnLoginSendStrMsg(long nStrMsgId, LPCTSTR stheSender, LPCTSTR smsgContent)
		{FireEvent(eventidOnLoginSendStrMsg,EVENT_PARAM(VTS_I4  VTS_BSTR  VTS_BSTR), nStrMsgId, stheSender, smsgContent);}
	void FireOnIVRReturnToAgentConf(LPCTSTR sIVRPrivateData)
		{FireEvent(eventidOnIVRReturnToAgentConf,EVENT_PARAM(VTS_BSTR), sIVRPrivateData);}
	void FireOnNotifyAgentLoginConf(LPCTSTR sAgentLoginInfo)
		{FireEvent(eventidOnNotifyAgentLoginConf,EVENT_PARAM(VTS_BSTR), sAgentLoginInfo);}
	void FireOnAddTalkToWebChat(LPCTSTR sCallType, LPCTSTR sCaller, LPCTSTR sCallee, LPCTSTR sCallid, LPCTSTR sOriginalData, LPCTSTR sCallerType, LPCTSTR sKeyword) //hqh 2017.6.12 hqh 多渠道消息独立出来
		{FireEvent(eventidOnAddTalkToWebChat, EVENT_PARAM(VTS_BSTR  VTS_BSTR  VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR), sCallType, sCaller, sCallee, sCallid, sOriginalData, sCallerType, sKeyword);}
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()
		
		
		// Dispatch and event IDs
public:
	enum {
		//{{AFX_DISP_ID(CAgentPanelOcxCtrl)
		dispidActionLogon = 1L,
			dispidActionLogon2 = 2L,
			dispidActionReset = 3L,
			dispidActionLogout = 4L,
			dispidActionLogonAgain = 5L,
			dispidActionCallDepartment = 6L,
			dispidActionCallAgent = 7L,
			dispidActionCallOtherAgent = 8L,
			dispidActionCallPstn = 9L,
			dispidActionCallExtNum = 10L,
			dispidActionCallOtherDepartment = 11L,
			dispidActionOnHook = 12L,
			dispidActionOffHook = 13L,
			dispidActionPark = 14L,
			dispidActionUnPark = 15L,
			dispidActionProcess = 16L,
			dispidActionUnProcess = 17L,
			dispidActionHold = 18L,
			dispidActionUnHold = 19L,
			dispidActionTransfer = 20L,
			dispidActionAutoTransfer = 21L,
			dispidActionStartMonit = 22L,
			dispidActionStopMonit = 23L,
			dispidActionForceDisconnect = 24L,
			dispidActionGetFullFreeAgentInfo = 25L,
			dispidActionGetGroupInfo = 26L,
			dispidActionGetOneGroupFreeAgentInfo = 27L,
			dispidActionGetTalkingAgent = 28L,
			dispidActionSendDTMF = 29L,
			dispidActionChangePassword = 30L,
			dispidActionChangeEarphoneVolume = 31L,
			dispidActionChangeMicVolume = 32L,
			dispidActionSendSMS = 33L,
			dispidActionSendChat = 34L,
			dispidConfigPortSettings = 35L,
			dispidConfigRecSettings = 36L,
			dispidConfigOutDialSettings = 37L,
			dispidConfigSoundSettings = 38L,
			dispidGetLoginManner = 39L,
			dispidGetDeptment = 40L,
			dispidGetCorp = 41L,
			dispidGetCallType = 42L,
			dispidGetCallFrom = 43L,
			dispidGetPrivateData = 44L,
			dispidGetRecInvokeID = 45L,
			dispidGetClientState = 46L,
			dispidGetLogonType = 47L,
			dispidGetCallPartyType = 48L,
			dispidGetAgentHasLogon = 49L,
			dispidInitialize = 50L,
			dispidExit = 51L,
			dispidGetRoleInCompany = 52L,
			dispidGetAgentAccount = 53L,
			dispidGetIsCCNUser = 54L,
			dispidGetAgentType = 55L,
			dispidGetIsSMSEnabled = 56L,
			dispidGetAgentExtNum = 57L,
			dispidGetAgentPhoneNo = 58L,
			dispidGetManagerID = 59L,
			dispidGetIsSuperAgent = 60L,
			dispidGetIsMasterSuperAgent = 61L,
			dispidActionSendStrMsg = 62L,
			dispidGetRemindTime = 63L,
			dispidActionSettings = 64L,
			dispidActionMonit = 65L,
			dispidActionAgentOutDial = 66L,
			dispidGetIsMonit = 67L,
			dispidGetSMSParamsInfo = 68L,
			dispidGetAllSettings = 69L,
			dispidGetBriefStatisticInfo = 70L,
			dispidActionSaveBriefStatisticInfo = 71L,
			dispidActionSetMuteMode = 72L,
			dispidActionTransferToIVR = 73L,
			dispidGetTransferToIVRParamsInfo = 74L,
			dispidGetIsCallFromACD = 75L,
			dispidActionUpdateSettings = 76L,
			dispidGetIsOutDialOpenURL = 77L,
			dispidGetIVRReturn = 78L,
			dispidSetProductVersion = 79L,
			dispidGetRecInvokePath = 80L,
			dispidGetAgentID = 81L,
			dispidSetOriginalData = 82L,
			dispidActionOutDial = 83L,
			dispidSetSelectGroup = 84L,
			dispidActionAutoTransferEx = 85L,
			dispidActionOutDialWithRecSetting = 86L,
			dispidActionOffHookWithRecSetting = 87L,
			dispidGetIsCallInOpenURL = 88L,
			dispidGetParkReasons = 89L,
			dispidSetParkReason = 90L,
			dispidSetCallerSendingInDialing = 91L,
			dispidActionJoinOutDialMode = 92L,
			dispidGetIsOutDialMode = 93L,
			dispidGetMoudleFilePath = 94L,
			dispidActionSetMuteModeEx = 95L,
			dispidActionStartConference = 96L,
			dispidActionEndConference = 97L,
			dispidGetCanConference = 98L,
			dispidStopPlayAgentID = 99L,
			dispidActionACDAutoLogin = 100L,
			dispidSetLogonMode = 101L,
			eventidOnLogin = 1L,
			eventidOnAgentLoginSucc = 2L,
			eventidOnAgentLogoutConf = 3L,
			eventidOnAgentMakeCallConf = 4L,
			eventidOnClientStateChange = 5L,
			eventidOnCallDelivered = 6L,
			eventidOnSystemStatusInfo = 7L,
			eventidOnChatMsgDelivered = 8L,
			eventidOnQueueSize = 9L,
			eventidOnGetGroupInfo = 10L,
			eventidOnGetOneGroupFreeAgentInfo = 11L,
			eventidOnGetFullFreeAgentInfo = 12L,
			eventidOnGetFullTalkingAgentInfo = 13L,
			eventidOnAudioLostRate = 14L,
			eventidOnAgentLoginFailed = 15L,
			eventidOnServiceStateChange = 16L,
			eventidOnPreOutDialEnd = 17L,
			eventidOnUserLoginInfo = 18L,
			eventidOnAgentOutdialConf = 19L,
			eventidOnACDSendStrMsg = 20L,
			eventidOnLoginSendStrMsg = 21L,
			eventidOnIVRReturnToAgentConf = 22L,
			eventidOnNotifyAgentLoginConf = 23L,
			eventidOnAddTalkToWebChat = 24,//hqh 2017.6.12 多渠道独立出来
			//}}AFX_DISP_ID
	};
	
	
	void UpdateSettings();
	
private:
	BOOL m_bLogonSucc;
	CString m_sLoginServer;
	int m_iLoginServerOpt;
	CString m_sCorp;
	CSubPackData m_SubPackData;
	CString m_sSPNumber;
	CString m_sShortName;
	CString m_sManagerID;
	CString m_sPassword;
	CString m_sAccount;
	BOOL m_bTalkingAgentDlgShow;	
	BOOL m_bFreeAgentDlgShow;
	BOOL m_bMonit;
	CGetFreeAgentDlg* m_pCallTargerListDlg;
	CGetTalkAgentDlg* m_pMonitTargerListDlg;
	CNewSettingsDlg* m_pSettingsDlg;
	DWORD m_tLastRecvTime;//上一次收到Ipccserivce心跳的时间
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AGENTPANELOCXCTL_H__F5D81D23_B187_46F0_B7A0_B514AC8F7D1B__INCLUDED)
