// UDPSocket.cpp: implementation of the CMySocket class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "UDPSocket.h"
#include "log.h"

#pragma comment(lib, "ws2_32.lib")

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
int CUDPSocket::g_iRefs = 0;

CUDPSocket::CUDPSocket()
{
}

CUDPSocket::~CUDPSocket()
{

}

bool CUDPSocket::Init(int localPort, int recvbufSize, int sendbufSize, string& errInfo)
{
	if (localPort<0  || localPort >65536){
			return false;
		}
		

	this->m_iRecvFailedCount = 0;
	WSADATA wsaData;

	try
	{
		if(g_iRefs == 0)
		{
			if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
			{
				//errInfo.Format("WSAStartup err,errcode=%d", WSAGetLastError());
				return false;
			}
		}

		g_iRefs++;

		this->SetParams(localPort,recvbufSize,sendbufSize);

		if(!this->PrepareForUse(errInfo))
		{
			this->Release();
			return false;
		}
	}
	catch(...)
	{
		return false;
	}

	return true;
}

void CUDPSocket::Release()
{
	try
	{
		closesocket(m_mySocket);
		g_iRefs--;
	}
	
	catch(...){}

	if(g_iRefs == 0)
	{
		try
		{
			WSACleanup();
		}
		catch(...){}
	}
}

void CUDPSocket::SetParams(int localPort, int recvbufSize, int sendbufSize)
{
	this->m_iLocalPort = localPort;
	this->m_iRecvBufSize = recvbufSize; // * 8;
	this->m_iSendBufSize = sendbufSize; // * 8;



}

bool CUDPSocket::PrepareForUse(string& errInfo)
{
	this->m_mySocket = socket(AF_INET, SOCK_DGRAM, 0);
	if (m_mySocket < 0)
	{
        return false;
	}

	sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(this->m_iLocalPort);
	local.sin_addr.s_addr = htonl(INADDR_ANY);
	int nResult=bind(m_mySocket,(sockaddr*)&local,sizeof(sockaddr));
	if(nResult==SOCKET_ERROR)
	{
		int aa = WSAGetLastError();
///		CString bbb;
//		bbb.Format("%d",aa);
//		closesocket(m_mySocket);
		return false;
	}

	int rcvtimeo = 50 ;
	if( setsockopt( m_mySocket , SOL_SOCKET , SO_RCVTIMEO , 
		(const char *)&rcvtimeo , sizeof(rcvtimeo) ) == SOCKET_ERROR)
	{
		return false;
	}

	int nrcvbuf = this->m_iRecvBufSize; 
	int err = setsockopt( 
		m_mySocket, 
		SOL_SOCKET, 
		SO_RCVBUF,//读缓冲 
		(char *)&nrcvbuf, 
		sizeof(nrcvbuf)); 
	if(err!=0)
	{
		//errInfo.Format("setsockopt(rcv) err,errcode=%d", WSAGetLastError());
		closesocket(m_mySocket);
		return false;
	}

	int nsndbuf = this->m_iSendBufSize;
	err = setsockopt( 
		m_mySocket, 
		SOL_SOCKET, 
		SO_SNDBUF,//写缓冲 
		(char *)&nsndbuf, 
		sizeof(nsndbuf)); 
	if(err!=0)
	{
		//errInfo.Format("setsockopt(snd) err,errcode=%d", WSAGetLastError());
		closesocket(m_mySocket);
		return false;
	}

    //获取端口号
	SOCKADDR_IN   sockAddr;
	int   iLen = sizeof(sockAddr);
	getsockname(m_mySocket, ( struct   sockaddr   * )&sockAddr, &iLen);
	m_iLocalPort = sockAddr.sin_port;
	return true;
}

int CUDPSocket::ReceiveData(char*& msg, int size, unsigned long& ip, unsigned short& port, string& errInfo)
{
	int ret = -1;
	char* pMsg = NULL;
	try
	{
		pMsg = new char[size];
		memset(pMsg,0,size);

		sockaddr_in sender;
		int dwSender = sizeof(sender);
		ret = recvfrom(this->m_mySocket, (char *)pMsg, size, 0, (sockaddr *)&sender, &dwSender);

		ip = sender.sin_addr.S_un.S_addr;
		port = sender.sin_port;

		if(-1 == ret)
		{
			m_iRecvFailedCount++;
			if(m_iRecvFailedCount > 30)
				Sleep(1);
			if(pMsg != NULL) delete pMsg;
			pMsg = NULL;

			return -1;
		}

		m_iRecvFailedCount=0;

		msg = pMsg;

//		DirectAnalyzeCreditData(&this->m_mySocket, msg, ret, 0, ip, port, ret);
	}
	catch(...)
	{
		if(pMsg != NULL) delete pMsg;
		pMsg = NULL;
		return -1;
	}

	return ret;
}

bool CUDPSocket::SendData(string ip, int port, char *msg, int size, string &errInfo)
{
	if(ip.empty())
		return false;

	if(port<0 || port>65535)
		return false;

	try
	{
		if(msg == NULL)
			return true;

		string sOppIP(ip);
		sockaddr_in server;
		server.sin_addr.S_un.S_addr = inet_addr(sOppIP.c_str());

		server.sin_family = AF_INET;
		server.sin_port = htons(port);

		int ret = sendto(this->m_mySocket,(const char*)msg, size, 0, (const sockaddr *)&server, sizeof(server));

		if(SOCKET_ERROR == ret)
		{
			return false;
		}
	}
	catch(...)
	{
		return false;
	}

	return true;
}

bool CUDPSocket::SendData(unsigned long ip, unsigned short port, char *msg, int size, string &errInfo)
{
	if(ip<0)
		return false;

	if(port<0 || port>65535)
		return false;

	try
	{
		if(msg == NULL)
			return true;

		sockaddr_in server;
		server.sin_addr.S_un.S_addr = ip;
		server.sin_family = AF_INET;
		server.sin_port = port;
		int ret = sendto(this->m_mySocket,(const char*)msg, size, 0, (const sockaddr *)&server, sizeof(server));

		if(-1 == ret)
		{
			//errInfo.Format("sendto err,errcode=%d", WSAGetLastError());
			return false;
		}
	}
	catch(...)
	{
		return false;
	}

	return true;
}

int CUDPSocket::ReceiveData(char *&msg, int size, string &errInfo)
{
	int ret = -1;

	char* pMsg = NULL;
	try
	{
		pMsg = new char[size];
		memset(pMsg,0,size);

		sockaddr_in sender;
		int dwSender = sizeof(sender);
		ret = recvfrom(this->m_mySocket, (char *)pMsg, size, 0, (sockaddr *)&sender, &dwSender);

		if(-1 == ret)
		{
			if(pMsg != NULL)
				delete pMsg;
			pMsg = NULL;
			//errInfo.Format("recvfrom err,errcode=%d", WSAGetLastError());
			return -1;
		}

		msg = pMsg;
	}
	catch(...)
	{
		if(pMsg != NULL)
				delete pMsg;
		pMsg = NULL;
		return -1;
	}

	return ret;
}

int CUDPSocket::GetPort()
{
	return this->m_iLocalPort;
}

void CUDPSocket::DirectAnalyzeCreditData(SOCKET* sock, const char *buf, int size, bool bsend, unsigned long ip, unsigned short port, int realSize)
{
	//不是数据包
	if(size<=9)
		return;

	int nAck=-1;
	memcpy(&nAck , buf+16, 4);
	if(nAck != 0)
		return;

	//是数据包

	//数据大小
	int msgsize = size - 72;

	int mclass;
	int mtype;
	memcpy(&mclass, buf+72, 4);
	memcpy(&mtype, buf+76, 4);
	if(mtype == Type_P2P_TestMsg)
		int xxxx = 1000;

	//信令数据
	char* pmsg = new char[msgsize];
	memcpy(pmsg, buf+72, msgsize);

	CIPCCMsgExchanger msgExchanger;

	__EIPCCMsgClass msgClass;
	__EIPCCMsgType msgType;
	msgExchanger.GetMsgHeader(pmsg, msgsize, msgClass, msgType);

	if(msgClass == Class_EndEgn)
	{
		delete pmsg;
		return;
	}

	delete pmsg;
}

int CUDPSocket::GetRecvBufDataSize()
{
	int iRet = -1;
	unsigned long iSize = -1;
	iRet = ioctlsocket(this->m_mySocket, FIONREAD, &iSize);
	if(iRet == 0)	//succ
		return iSize;

	return -1;
}
