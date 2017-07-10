// CUDPSocket.h: interface for the CMySocket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYSOCKET_H__D6C8EC53_3FF4_452A_9232_1B97E0CC2CC8__INCLUDED_)
#define AFX_MYSOCKET_H__D6C8EC53_3FF4_452A_9232_1B97E0CC2CC8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Winsock.h"

#include <string>
using namespace std;

class CUDPSocket  
{
public:
	int GetRecvBufDataSize();
	static void DirectAnalyzeCreditData(SOCKET* sock, const char *buf, int size, bool bsend, unsigned long ip, unsigned short port, int realSize);

	int m_iRecvFailedCount;
	int GetPort();
	int ReceiveData(char*& msg, int size, string& errInfo);
	static int g_iRefs;
	bool SendData(unsigned long ip, unsigned short port, char *msg, int size, string &errInfo);
	bool SendData(string ip, int port, char* msg, int size, string& errInfo);
	int ReceiveData(char*& msg, int size, unsigned long& ip, unsigned short& port, string& errInfo);
	void Release();
	bool Init(int localPort, int recvbufSize, int sendbufSize, string& errInfo);
	CUDPSocket();
	virtual ~CUDPSocket();

private:
	SOCKET m_mySocket;
	void SetParams(int localPort, int recvbufSize, int sendbufSize);
	bool PrepareForUse(string& errInfo);
	int m_iLocalPort;
	int m_iRecvBufSize;
	int m_iSendBufSize;
};

#endif // !defined(AFX_MYSOCKET_H__D6C8EC53_3FF4_452A_9232_1B97E0CC2CC8__INCLUDED_)
