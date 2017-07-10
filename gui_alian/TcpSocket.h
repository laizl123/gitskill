// TcpSocket.h: interface for the CTcpSocket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TCPSOCKET_H__9273844F_7C01_4959_8FA8_D0D4BC58E60C__INCLUDED_)
#define AFX_TCPSOCKET_H__9273844F_7C01_4959_8FA8_D0D4BC58E60C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Winsock.h"

class CTcpSocket  
{
public:
	CTcpSocket();
	virtual ~CTcpSocket();
	bool Listen(unsigned short iPort);
	bool Accept(CTcpSocket* pConnectedSock);
	bool Connect(unsigned int iIp, unsigned short iPort);
	bool Connect(string sIp, unsigned short iPort);
	int Receive(char* buf, int iMaxSize);
	bool Send(char* buf, int iLen);
	void Release();
//protected:
	SOCKET m_Socket;
	bool m_bIsListener;
};

#endif // !defined(AFX_TCPSOCKET_H__9273844F_7C01_4959_8FA8_D0D4BC58E60C__INCLUDED_)
