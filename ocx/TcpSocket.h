// TcpSocket.h: interface for the CTcpSocket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TCPSOCKET_H__9273844F_7C01_4959_8FA8_D0D4BC58E60C__INCLUDED_)
#define AFX_TCPSOCKET_H__9273844F_7C01_4959_8FA8_D0D4BC58E60C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Winsock.h"
#include <string>
using namespace std;

class CTcpSocket  
{
public:
	CTcpSocket();
	virtual ~CTcpSocket();
// Data
protected:
	SOCKET m_Socket;
	bool m_bIsListener;
	int m_iError;
// Method
private:
	bool Init();
public:
	bool Listen(unsigned short iPort);
	bool Accept(CTcpSocket & o_ConnectedSock);
	bool Accept1(CTcpSocket & o_ConnectedSock);
	bool Connect(string i_strIP, unsigned short i_uPort);
	int Receive(char* o_szBuf, int i_iMaxSize, long i_lTimeSec=0);
	int Send(char* i_Buf, int i_iLen);
	void Release();
	int GetTCPError();
	void MakePacket( char *&o_pBuf, int &o_iLen, char *i_pBuf, int i_iLen);
//protected:
	
};

#endif // !defined(AFX_TCPSOCKET_H__9273844F_7C01_4959_8FA8_D0D4BC58E60C__INCLUDED_)
