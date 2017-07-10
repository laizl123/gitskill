// TcpSocket.cpp: implementation of the CTcpSocket class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TcpSocket.h"
#include "GlobalOperation.h"

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
	m_Socket = NULL;
	m_bIsListener = false;
}

CTcpSocket::~CTcpSocket()
{
	if ( m_Socket )
	{
		shutdown( m_Socket, 2 );
		closesocket( m_Socket );
	}
}

bool CTcpSocket::Listen(unsigned short iPort)
{
	WSADATA wsaData;

	try
	{
		if ( WSAStartup( MAKEWORD(2, 2), &wsaData ) != 0 )
			return false;

		m_Socket = socket( AF_INET, SOCK_STREAM, 0 );

		if ( m_Socket == INVALID_SOCKET )
			return false;

		sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_port = htons( iPort );
		addr.sin_addr.s_addr = htonl( INADDR_ANY );
		if ( bind( m_Socket, (sockaddr*)&addr, sizeof(sockaddr) ) == SOCKET_ERROR )
			return false;

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

bool CTcpSocket::Accept(CTcpSocket* pConnectedSock)
{
	try
	{
		fd_set fdset;
		FD_ZERO( &fdset );
		FD_SET( m_Socket, &fdset );

		timeval time;
		time.tv_sec = 0;
		time.tv_usec = 50;

		if ( select( 0, &fdset, NULL, NULL , &time ) > 0 )
		{
			sockaddr_in addr;
			int iAddrLen = sizeof(sockaddr);
			SOCKET newSock = accept( m_Socket, (sockaddr*)&addr, &iAddrLen );
			if ( newSock != INVALID_SOCKET )
			{
				pConnectedSock->m_Socket = newSock;
				return true;
			}
		}
	}
	catch (...)
	{
	}

	return false;
}

int CTcpSocket::Receive(char* buf, int iMaxSize)
{
	try
	{
		fd_set fdset;
		FD_ZERO( &fdset );
		FD_SET( m_Socket, &fdset );

		timeval time;
		time.tv_sec = 0;
		time.tv_usec = 50;

		int iLen = 0;
		while ( select( 0, &fdset, NULL, NULL , &time ) > 0 )
		{
			int i = recv( m_Socket, buf, iMaxSize, 0 );
			if ( i != SOCKET_ERROR )
			{
				iLen += i;
				buf += i;
				iMaxSize -= i;

				if ( iMaxSize <= 0 )
				{
					break;
				}
			}
			else
			{
				break;
			}
			
			FD_ZERO( &fdset );
			FD_SET( m_Socket, &fdset );

			time.tv_sec = 0;
			time.tv_usec = 50;
		}
		
		return iLen > 0 ? iLen : -1;
	}
	catch (...)
	{
		return -1;
	}
}

bool CTcpSocket::Send(char* buf, int iLen)
{
	try
	{
		int i = send( m_Socket, buf, iLen, 0 );
		if ( i != SOCKET_ERROR )
		{
			return true;
		}
	}
	catch (...)
	{
	}

	return false;
}

void CTcpSocket::Release()
{
	closesocket( m_Socket );
	m_Socket = NULL;
}

bool CTcpSocket::Connect(unsigned int iIp, unsigned short iPort)
{
	WSADATA wsaData;

	try
	{
		if ( WSAStartup( MAKEWORD(2, 2), &wsaData ) != 0 )
			return false;

		m_Socket = socket( AF_INET, SOCK_STREAM, 0 );

		sockaddr_in addr;
		memset( &addr, 0, sizeof(sockaddr_in) );
		addr.sin_family = AF_INET;
		addr.sin_port = iPort;
		addr.sin_addr.s_addr = iIp;

		int i = connect( m_Socket, (sockaddr*)&addr, sizeof(sockaddr) );
		if ( i == -1 )
		{
			int ii = WSAGetLastError();
		}
		return i == 0;
	}
	catch(...)
	{
		return false;
	}
}

bool CTcpSocket::Connect(string sIp, unsigned short iPort)
{
	return Connect( ConvertIP(sIp), ConvertPort(iPort) );
}