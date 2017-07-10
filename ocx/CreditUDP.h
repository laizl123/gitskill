// CreditUDP.h: interface for the CCreditUDP class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CREDITUDP_H__53CEFDEB_45B1_420B_AFA1_0313E5D80498__INCLUDED_)
#define AFX_CREDITUDP_H__53CEFDEB_45B1_420B_AFA1_0313E5D80498__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include <map>
#include <queue>

#include "UDPSocket.h"
#define  BESEND  0
#define  SENDING 1
#define  AFSEND  2
#define  TIME_REPEATSEND 100
#define  CLOSECOUNT 10
#define  HARTTIME 1500
#define  CREDIT_UDP_VER ("CreditUDP0001")
#define  CREDIT_UDP_VER_LEN 13

typedef struct _CreUDPStruct
{
	char CreUDPHead[CREDIT_UDP_VER_LEN];
	int nSeq;          //包序号。
	int nAck;         //是否是确认包。0：否；1：确认包。2：终止连接。
	int nSendCount;   //已发送次数。
	int nReSend;      //重发次数。0：不断重发。
// 	char strSourceIP[16];
	unsigned long SourceIP;
//	int nSourcePort;
	unsigned short SourcePort;
//	char strDestIP[16];
	unsigned long DestIP;
//	int nDestPort;
	unsigned short DestPort;
	int nDataSize;
    char* data;
	_CreUDPStruct(int nSize)
	{
		strcpy(CreUDPHead,CREDIT_UDP_VER);
	  nSeq=0;
	  nAck=0;
	  nSendCount=0;
	  nReSend=0;
//	  ZeroMemory(strSourceIP,16);
//	  nSourcePort=0;
//	  ZeroMemory(strDestIP,16);
//	  nDestPort=0;
	  SourceIP = 0;
	  SourcePort = 0;
	  DestIP = 0;
	  DestPort = 0;
	  nDataSize=nSize;
	  if(nSize>0)
	  {
		if(nSize>1400)
		   nSize=1400;
	    data=new char[nSize];
	    ZeroMemory(data,nSize);
	  }
	  else
		data=NULL;
	}
	~_CreUDPStruct()
	{
		if (data!=NULL)
		{
			delete data;
			data = NULL;
		}
	}
}UDPStruct;

typedef struct _RealData
{
	unsigned long m_ip;
	unsigned short m_port;
	char* m_data;
	int m_nSize;

	_RealData(unsigned long ip,
	unsigned short port,
	char* data,
	int nSize)
	{
		m_ip=ip;
		m_port=port;
		m_data=new char[nSize];
		memcpy(m_data,data,nSize);
		m_nSize=nSize;
	}
	~_RealData()
	{
		if (m_data != NULL)
		{
			delete m_data;
			m_data = NULL;
		}
	}
}RealData;
typedef struct _HartPack
{
	char Head[9];
	_HartPack()
	{
		memset(Head,0,9);
		memcpy(Head,"HartPack",8);
	}
}HartPack;

struct SendBuf
{
	UDPStruct* Buf;
	bool NeedEvent;
	SendBuf(UDPStruct* buf, bool bNeedEvent = false)
	{
		Buf = buf;
		NeedEvent = bNeedEvent;
	};
	~SendBuf()
	{
		delete Buf;
	};
};

struct SendStruct
{
	int nSequence;
	int nHartTime;
	bool bSendHart;
	unsigned long LastTime;
	queue<SendBuf*>  SendQueue;
	SendStruct()
	{
		bSendHart = true;
		nSequence = 0;
		nHartTime = GetTickCount();
		LastTime = GetTickCount();
	};
	~SendStruct()
	{
		while ( !SendQueue.empty() )
		{
			delete SendQueue.front();
			SendQueue.pop();
		}
	};
};

struct ReceiveStruct
{
	int nSequence;
	unsigned long LastTime;
	ReceiveStruct()
	{
		nSequence = 0;
		LastTime = GetTickCount();
	};

	~ReceiveStruct()
	{
	};
};

struct ReceiveKey
{
	unsigned long IP;
	unsigned short Port;
	unsigned short DestPort;

	ReceiveKey()
	{
		IP = 0;
		Port = 0;
		DestPort = 0;
	};

	ReceiveKey(unsigned long iP,unsigned short port,unsigned short destPort)
	{
		IP = iP;
		Port = port;
		DestPort = destPort;
	};

	bool operator<(const ReceiveKey& src) const
	{
		if ( IP < src.IP )
		{
			return true;
		}
		else if ( IP > src.IP )
		{
			return false;
		}

		if ( Port < src.Port )
		{
			return true;
		}
		else if ( Port > src.Port )
		{
			return false;
		}

		return DestPort < src.DestPort;
	};
};

struct SendKey
{
	unsigned long IP;
	unsigned short Port;

	SendKey()
	{
		IP = 0;
		Port = 0;
	};

	SendKey(unsigned long iP,unsigned short port)
	{
		IP = iP;
		Port = port;
	};

	bool operator<(const SendKey& src) const
	{
		if ( IP < src.IP )
		{
			return true;
		}
		else if ( IP > src.IP )
		{
			return false;
		}

		return Port < src.Port;
	}
};
typedef SendKey IpPortPair;


class CCreditUDP  
{
private:
	bool bStopThread;
    typedef map<SendKey,SendStruct*> SendMap;
	SendMap m_SendMap;
	typedef map<ReceiveKey,ReceiveStruct*> ReceiveMap;
	ReceiveMap m_ReceiveMap;
	CRITICAL_SECTION hSendMapLock;
	CRITICAL_SECTION hReceiveMapLock;
	queue<RealData*> m_ReceiveQueue;
	vector<IpPortPair> ConnectVector;
// 	CRITICAL_SECTION hSendLock;
	CRITICAL_SECTION hRecvLock;
	CRITICAL_SECTION hVecLock;
	HANDLE hSendEvent[2];
	HANDLE hRecvEvent;
	CUDPSocket m_UDPSocket;
public:
	CCreditUDP::CCreditUDP();
	CCreditUDP::~CCreditUDP();
private:
	void AddToConnectVec(IpPortPair pairIpPort);
	void ClearConnectVec();
	void SendDataFunc(SendKey& key, SendStruct* pSendStruct);
	bool SendUDPData(UDPStruct*buf);
	BOOL SendAckData(UDPStruct* pRecvBuf);
	bool SendHartPack(SendKey& key, SendStruct* pSendStruct);
	static DWORD WINAPI SendProc(LPVOID lp);
	static DWORD WINAPI RecvProc(LPVOID lp);
	bool ExistRecvSeq( UDPStruct* pUDPStruct );
	ReceiveKey GetReceiveKey( UDPStruct* pUDPStruct );
	SendKey GetSendKey( UDPStruct* pUDPStruct, bool bReceived );
	bool IsCreditData(const char* buf, int size);
public:
	CUDPSocket* GetUdpSock();
	unsigned short GetPort();
	int GetRecvBufDataSize();
	void DirectSendData(unsigned long ip, unsigned short port, char* data, int len);
	BOOL Init(int UDPPort,int nSendBufSize,int RecvBufSize,string eventTag,bool SendHart,string& strErrInfo,bool bUseCredit = true);
	int SendData(unsigned long IP,unsigned short Port,char*buffer,int nSize,string& errorInfo,int nReSendCount=10,bool bWait=false,int iTimeOut=500);
	int ReceiveData(char*&sData,int nDataSize,unsigned long& ip,unsigned short& port,string& errorInfo,int nDeferTime=5000);
	bool SetOption(bool bUSECreditUDP);
	bool Release(bool bReleaseSock = true);
	void SetHartOption(string sIP,int nPort,bool bSendHartFlag);
	int GetCurrentSeq(unsigned long ip, unsigned short port);
	
private:
	void SendCloseMsg(unsigned long ip, unsigned short port);
	DWORD SendProcRun();
	DWORD RecvProcRun();
	bool m_bHaveReleased;
	HANDLE hSendThread;
	HANDLE hRecvThread;
	bool bCreditUDP;
	bool bSendHart;
	string sLocalIP;
	int  nLocalPort;
	string m_sEventTag;
	bool InnerSendUdpData(unsigned long iIp, unsigned short iPort, char* pData, int iLen);
};

#endif // !defined(AFX_CREDITUDP_H__53CEFDEB_45B1_420B_AFA1_0313E5D80498__INCLUDED_)
