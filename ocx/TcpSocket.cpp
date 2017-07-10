// TcpSocket.cpp: implementation of the CTcpSocket class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TcpSocket.h"

#pragma comment(lib, "ws2_32.lib")

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTcpSocket::CTcpSocket()
{
	m_Socket = 0;
	m_bIsListener = false;
	if(m_Socket==0||m_Socket==INVALID_SOCKET)
		Init();
}

CTcpSocket::~CTcpSocket()
{
	if ( m_Socket ) {
		shutdown( m_Socket, 2 );
		closesocket( m_Socket );
		WSACleanup();
	}
}

bool CTcpSocket::Init() 
{
	WSADATA wsaData;
	if ( WSAStartup( MAKEWORD(2, 2), &wsaData ) != 0 )
		return false;
	m_Socket = socket( AF_INET, SOCK_STREAM, 0 );
	if ( m_Socket == INVALID_SOCKET )
		return false;
	
	// add
	/*
	unsigned long ul=1;   
	int   ret   =   ioctlsocket(m_Socket, FIONBIO, &ul);   
	if(ret==SOCKET_ERROR)     
		return false;
	// end*/

	return true;
}

bool CTcpSocket::Listen(unsigned short iPort)
{
//	WSADATA wsaData;

	try {
/*		if ( WSAStartup( MAKEWORD(2, 2), &wsaData ) != 0 )
			return false;

		m_Socket = socket( AF_INET, SOCK_STREAM, 0 );

		if ( m_Socket == INVALID_SOCKET )
			return false;*/
//		Init();

		sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_port = htons( iPort );
		addr.sin_addr.s_addr = htonl( INADDR_ANY );
		if ( bind( m_Socket, (sockaddr*)&addr, sizeof(sockaddr) ) == SOCKET_ERROR )
			return false;
		
		// + [5/25/2009 lixg]
		linger lin={1, 0};
		if (setsockopt(m_Socket, SOL_SOCKET, SO_LINGER, (const char *)&lin, sizeof(lin)) == SOCKET_ERROR) 
		{
			return false;		
		}

		if ( listen( m_Socket, SOMAXCONN ) == SOCKET_ERROR )
			return false;

		m_bIsListener = true;
		return true;
	}
	catch(...)
	{
		return false;
	}
}

bool CTcpSocket::Accept(CTcpSocket & o_ConnectedSock)
{
	try {
/*		sockaddr_in addr;
		int iAddrLen = sizeof(sockaddr);
		SOCKET newSock = accept( m_Socket, (sockaddr*)&addr, &iAddrLen );
		if ( newSock != INVALID_SOCKET ) {
			o_ConnectedSock.m_Socket = newSock;
			return true;
		}*/
		fd_set fdRead;
		int iRet;

		timeval time;
		time.tv_sec = 1;//0
		time.tv_usec = 50;

		FD_ZERO( &fdRead );
		FD_SET( m_Socket, &fdRead );
		iRet=select( 0, &fdRead, NULL, NULL , &time );

		if ( iRet > 0 ) {
			sockaddr_in addr;
			int iAddrLen = sizeof(sockaddr);
			SOCKET newSock = accept( m_Socket, (sockaddr*)&addr, &iAddrLen );
			if ( newSock != INVALID_SOCKET )
			{
				o_ConnectedSock.m_Socket = newSock;
				return true;
			}
		}
		m_iError=WSAGetLastError();
	} catch (...) {
	}

	return false;
}

bool CTcpSocket::Accept1(CTcpSocket & o_ConnectedSock)
{
	try {
		sockaddr_in addr;
		int iAddrLen = sizeof(sockaddr);
		SOCKET newSock = accept( m_Socket, (sockaddr*)&addr, &iAddrLen );
		if ( newSock != INVALID_SOCKET ) {
			o_ConnectedSock.m_Socket = newSock;
			return true;
		}
/*		fd_set fdRead;
		int iRet;

		timeval time;
		time.tv_sec = 1;//0
		time.tv_usec = 50;

		FD_ZERO( &fdRead );
		FD_SET( m_Socket, &fdRead );
		iRet=select( 0, &fdRead, NULL, NULL , &time );

		if ( iRet > 0 ) {
			sockaddr_in addr;
			int iAddrLen = sizeof(sockaddr);
			SOCKET newSock = accept( m_Socket, (sockaddr*)&addr, &iAddrLen );
			if ( newSock != INVALID_SOCKET )
			{
				o_ConnectedSock.m_Socket = newSock;
				return true;
			}
		}*/
		m_iError=WSAGetLastError();
	} catch (...) {
	}

	return false;
}

int CTcpSocket::Receive(char* o_szBuf, int i_iMaxSize, long i_lTimeSec)
{
	try {
		fd_set fdRead;
		int iRet;
		timeval time;
		time.tv_sec = i_lTimeSec;//0
		time.tv_usec = 50;

		int iLen = 0;
		int iRecv=-7;
		char *pBuf=o_szBuf;

		while (1 ) { //select( 0, &fdset, NULL, NULL , &time ) > 0 
			FD_ZERO( &fdRead );
			FD_SET( m_Socket, &fdRead );
			iRet=select( 0, &fdRead, NULL, NULL , &time );// > 0
			if(iRet>0) { // 
				if(!FD_ISSET(m_Socket, &fdRead))
					break;
				iRecv = recv( m_Socket, pBuf, i_iMaxSize, 0 );// -
				if ( iRecv > 0 ) { //!= SOCKET_ERROR
					iLen += iRecv;
					pBuf += iRecv;
					i_iMaxSize -= iRecv;

					if ( i_iMaxSize <= 0 ) {
						break;
					}
				} else {
					break;
				}
			} else {
				break;
			}
		}
		
		return iLen > 0 ? iLen : iRecv;//-1
	} catch (...) {
		return -1;
	}
}

int CTcpSocket::Send(char* i_Buf, int i_iLen)
{
	try {
//		char *pBuf=NULL;;//=new char[i_iLen+sizeof(int)+1];
//		memset(pBuf,0,sizeof(i_iLen+sizeof(int)+1));
//		memcpy(pBuf,&i_iLen,sizeof(i_iLen));
//		memcpy(pBuf+sizeof(int),i_Buf,i_iLen);
//		MakePacket( pBuf, i_Buf, i_iLen);
		int i = send( m_Socket, i_Buf, i_iLen, 0 );
//		delete pBuf[];
//		pBuf=NULL;
		return i;
	} catch (...) {
	}
	m_iError=WSAGetLastError();

	return false;
}

bool CTcpSocket::Connect(string i_strIP, unsigned short i_uPort)
{
	try { // 增加select处理
/*		char szIP[50];
		memset(szIP,0,sizeof(szIP));
		strcpy(szIP, i_strIP);*/
//		char* szT=strdup(i_strIP.c_str()); 
		sockaddr_in addr;
		addr.sin_addr.S_un.S_addr=inet_addr(i_strIP.c_str());
		addr.sin_family=AF_INET;
		addr.sin_port=htons(i_uPort); //lj shit
		int i = ::connect( m_Socket, (sockaddr *)&addr, sizeof(addr));
		if (i!=SOCKET_ERROR) {
			return true;
		}
	} catch (...) {
		;
	}
	int m_iError=WSAGetLastError();
	return false;
}

void CTcpSocket::Release()
{
	shutdown( m_Socket, 2 );
	closesocket( m_Socket );
//	WSACleanup();
	m_Socket = 0;
	if(m_Socket==0||m_Socket==INVALID_SOCKET)
		Init();
}

int CTcpSocket::GetTCPError()
{
	return m_iError;
}

void CTcpSocket::MakePacket( char *&o_pBuf,int &o_iLen, char *i_pBuf, int i_iLen) {
	o_pBuf=new char[i_iLen+sizeof(int)+1];
	memset(o_pBuf,0,i_iLen+sizeof(int)+1);
	memcpy(o_pBuf,&i_iLen,sizeof(i_iLen));
	memcpy(o_pBuf+sizeof(int),i_pBuf,i_iLen);
	o_iLen=i_iLen+sizeof(int);
}
