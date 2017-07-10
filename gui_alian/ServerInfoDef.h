// ServerInfoDef.h: interface for the ServerInfoDef class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SERVERINFODEF_H__00F66660_7841_416F_A980_731A371056E3__INCLUDED_)
#define AFX_SERVERINFODEF_H__00F66660_7841_416F_A980_731A371056E3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ServerInfoDef  
{
public:
	ServerInfoDef(){};
	virtual ~ServerInfoDef(){};
public:
	const static unsigned short Port_LoginServer;
	const static unsigned short Port_GuideServer;
	const static unsigned short Port_ACDServer;
	const static unsigned short Port_RelayServer;
	const static unsigned short Port_CheckNatServerA;
	const static unsigned short Port_CheckNatServerB;
	
	const static unsigned short Port_DataCollectServer;
	const static unsigned short Port_SysManageServer;
	const static unsigned short Port_TransmitServer;

	const static unsigned short Port_UStateServer;
	const static unsigned short Port_RecordServer;
	const static unsigned short Port_SmartRouteServer;
	const static unsigned short Port_SmartRouteDataServer;
	const static unsigned short Port_GatewayManageServer;
	const static unsigned short Port_GatewayManageDataServer;
	
	const static unsigned short Port_TextChatServer;
	const static unsigned short Port_RedirectServer;
	const static unsigned short Port_DlyStrategyServer;
	const static unsigned short Port_TollServer;
	const static unsigned short Port_EchoServer;
	const static unsigned short Port_TollQueryServer;
	const static unsigned short Port_PhoneBookServer;
	const static unsigned short Port_CallTransCtrlServer;
	const static unsigned short Port_PhoneNoCtrlServer;
	const static unsigned short Port_TollTransationServer;
	const static unsigned short Port_RecCtrlServer;
	const static unsigned short Port_SMSServer;
	const static unsigned short Port_DataRouteServer;

	static char* Local_IP_LoginServer;
	static char* Local_IP_GuideServer;
	static char* Local_IP_ACDServer;
	static char* Local_IP_RelayServer;
	static char* Local_IP_CheckNatServerA;
	static char* Local_IP_CheckNatServerB;
	static char* Local_IP_DataCollectServer;
	static char* Local_IP_SysManageServer;
	static char* Local_IP_DataRouteServer;
};

#endif // !defined(AFX_SERVERINFODEF_H__00F66660_7841_416F_A980_731A371056E3__INCLUDED_)
