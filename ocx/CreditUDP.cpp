// CreditUDP.cpp: implementation of the CCreditUDP class.
//
//////////////////////////////////////////////////////////////////////
//#define CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>
#include "stdafx.h"
#include "CreditUDP.h"
#include "GlobalOperation.h"
#include "log.h"

#ifdef OPTION_CRYPT
#include "Rijndael.h"
#endif
//#define _CRTDBG_MAP_ALLOC 
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
unsigned int IPPORT_MAX_TIMEOUT = 10000;
long g_iSourceIp=0;
long g_iSourcePort=0;
CCreditUDP::CCreditUDP()
{
	hSendEvent[0]=NULL;
	hSendEvent[1]=NULL;
	hRecvEvent=NULL;
	m_bHaveReleased = true;
	hSendThread = NULL;
	hRecvThread = NULL;
}

CCreditUDP::~CCreditUDP()
{
	Release();
}

BOOL CCreditUDP::Init(int UDPPort,int nSendBufSize,int RecvBufSize,string eventTag,bool SendHart,string& strErrInfo,bool bUseCredit)
{
	//	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	bStopThread = !bUseCredit;
	ConnectVector.reserve(1024);
	m_bHaveReleased = false;
	bSendHart=SendHart;
	bCreditUDP=bUseCredit;
	sLocalIP="";
	nLocalPort=0;
	BOOL iFlag=m_UDPSocket.Init(UDPPort,RecvBufSize,nSendBufSize,strErrInfo);
	sLocalIP = GetLocalIP();
	nLocalPort=UDPPort;
	//  InitializeCriticalSection(&hSendLock);
	InitializeCriticalSection(&hRecvLock);
	InitializeCriticalSection(&hSendMapLock);
	InitializeCriticalSection(&hReceiveMapLock);
	InitializeCriticalSection(&hVecLock);
	m_sEventTag = eventTag;
	string sSendEvent1 = eventTag;	sSendEvent1 += "_SendEvent1";
	string sSendEvent2 = eventTag;	sSendEvent2 += "_SendEvent2";	
	string sRecvEvent = eventTag;	sRecvEvent += "_RecvEvent";	
	
	hSendEvent[0]=CreateEvent(NULL,FALSE,FALSE,sSendEvent1.c_str());
	hSendEvent[1]=CreateEvent(NULL,FALSE,FALSE,sSendEvent2.c_str());
    hRecvEvent=CreateEvent(NULL,FALSE,FALSE,sRecvEvent.c_str());
	
	if ( bCreditUDP )
	{
		hSendThread=CreateThread(0,0,SendProc,this,0,NULL);
		hRecvThread=CreateThread(0,0,RecvProc,this,0,NULL);
	}
	return iFlag;
}

void CCreditUDP::SetHartOption(string sIP,int nPort,bool bSendHartFlag)
{
	SendKey key;
	key.IP = ::ConvertIP( sIP );
	key.Port = ::ConvertPort( nPort );
	EnterCriticalSection(&hSendMapLock);
	if ( m_SendMap.find( key ) != m_SendMap.end() )
	{
		m_SendMap[ key ]->bSendHart = bSendHartFlag;
	}
	LeaveCriticalSection(&hSendMapLock);
}

bool CCreditUDP::SendHartPack(SendKey& key, SendStruct* pSendStruct)
{
	if( !pSendStruct->bSendHart )
		return false;
	int i = GetTickCount();
	if( (i-HARTTIME) < pSendStruct->nHartTime )
		return false;
	pSendStruct->nHartTime = i;
	string sErr = "";
	bool bFlag = m_UDPSocket.SendData( key.IP, key.Port, "HartPack", 8, sErr );
	return bFlag;
}

bool CCreditUDP::SendUDPData(UDPStruct*buf)
{
	if(buf==NULL) {return false;}
	else
	{
		if(buf->nDataSize > 1000)	//此处避免发送视频数据
			return true;
		
		string errorInfo;
		int nbufSize=buf->nDataSize+sizeof(UDPStruct)-sizeof(char*);
		char* buffer=new char[nbufSize];
		memcpy(buffer,buf,sizeof(UDPStruct)-sizeof(char*));
		memcpy(buffer+sizeof(UDPStruct)-sizeof(char*),buf->data,buf->nDataSize);
		//		bool bFlag=m_UDPSocket.SendData(buf->strDestIP,buf->nDestPort,buffer,nbufSize,errorInfo);
//		bool bFlag=m_UDPSocket.SendData(buf->DestIP,buf->DestPort,buffer,nbufSize,errorInfo);
		bool bFlag = InnerSendUdpData(buf->DestIP,buf->DestPort,buffer,nbufSize);
		delete buffer;
		return bFlag;
	}
}

int CCreditUDP::SendData(unsigned long IP,unsigned short Port,char*data,int nSize,string& errorInfo,int nReSendCount,bool bWait,int iTimeOut)
{
	//hqh 2017.4.26 hqh 修复外呼时关闭GUI时锁对象被销毁的bug
	if (m_bHaveReleased == true){
		return -1;
	}


	//	string sIP;
	//	int nPort;
	//	inet_longTostring(IP,Port,sIP,nPort);
	if (IP <= 0 || Port <=0 || Port > 65535)
		return -1;
	if( bCreditUDP )
	{
		UDPStruct* pSendBuf=new UDPStruct(nSize);
		//		memcpy( pSendBuf->strDestIP, sIP.c_str(), sIP.size() );
		//		pSendBuf->nDestPort = nPort;
		pSendBuf->DestIP = IP;
		pSendBuf->DestPort = Port;
		pSendBuf->nReSend = nReSendCount;
		memcpy( pSendBuf->data, data, nSize );	
		
		//		EnterCriticalSection(&hSendLock);
		EnterCriticalSection(&hSendMapLock);
		SendKey key( IP, Port );
		SendStruct* pSendStruct = NULL;
		if ( m_SendMap.find(key) != m_SendMap.end() )
		{
			pSendStruct = m_SendMap[ key ];
			pSendBuf->nSeq = ++( pSendStruct->nSequence );
		}
		else
		{
			pSendStruct = new SendStruct;
			pSendStruct->bSendHart=bSendHart;
			pSendBuf->nSeq = 0;
			m_SendMap[ key ] = pSendStruct;
		}
		pSendStruct->SendQueue.push( new SendBuf(pSendBuf, bWait) );
		int iSeq = pSendBuf->nSeq;
		LeaveCriticalSection(&hSendMapLock);
		//		LeaveCriticalSection(&hSendLock);
		
		AddToConnectVec( key );
		SetEvent(hSendEvent[0]);
		
		if ( bWait )
		{
			ostringstream sEvent;
			sEvent.str("");
			sEvent << m_sEventTag << "ACKReceived" << IP << Port << iSeq;
			HANDLE hEvent = CreateEvent(NULL,FALSE,FALSE,sEvent.str().c_str());
			WaitForSingleObject( hEvent, iTimeOut );
			CloseHandle( hEvent );
		}
		return nSize;
	}
	else
	{
		string errorInfo;
		if(m_UDPSocket.SendData(IP,Port,data,nSize,errorInfo))
			return nSize;
		else
			return -1;
	}
}

bool CCreditUDP::SetOption(bool bUSECreditUDP)
{
	if ( bUSECreditUDP == bCreditUDP)
	{
		return true;
	}
	
	if(!bUSECreditUDP)
	{
		Release( false );
	}
	else 
	{
		if(hRecvThread==NULL)
			hRecvThread=CreateThread(NULL,0,RecvProc,this,0,NULL);
		if(hSendThread==NULL)
            hSendThread=CreateThread(NULL,0,SendProc,this,0,NULL);
	}
	
	bCreditUDP=bUSECreditUDP;
	return true;
}

void CCreditUDP::ClearConnectVec()
{
	EnterCriticalSection(&hVecLock);
	ConnectVector.clear();
	LeaveCriticalSection(&hVecLock);
}

DWORD WINAPI CCreditUDP::SendProc(LPVOID lp)
{
//	TRACE("CCreditUDP::SendProc start\n");
	CCreditUDP* pThis=(CCreditUDP*)lp;
	DWORD dw = pThis->SendProcRun();
//	TRACE("CCreditUDP::SendProc end\n");
	return dw;
}

BOOL CCreditUDP::SendAckData(UDPStruct* pRecvBuf)
{
	string errInfo;
	UDPStruct* pSendBuf=new UDPStruct(0);			
	//	  memcpy(pSendBuf->strDestIP,pRecvBuf->strSourceIP,15);
	//	  pSendBuf->nDestPort=pRecvBuf->nSourcePort;
	//	  memcpy(pSendBuf->strSourceIP,pRecvBuf->strDestIP,15);
	//	  pSendBuf->nSourcePort=pRecvBuf->nDestPort;
	pSendBuf->DestIP = pRecvBuf->SourceIP;
	pSendBuf->DestPort = pRecvBuf->SourcePort;
	pSendBuf->SourceIP = pRecvBuf->DestIP;
	pSendBuf->SourcePort = pRecvBuf->DestPort;
	pSendBuf->nSeq=pRecvBuf->nSeq;
	pSendBuf->nAck=1;
//	m_UDPSocket.SendData(pSendBuf->DestIP,pSendBuf->DestPort,(char*)pSendBuf,sizeof(UDPStruct)-sizeof(char*),errInfo);
	InnerSendUdpData(pSendBuf->DestIP,pSendBuf->DestPort,(char*)pSendBuf,sizeof(UDPStruct)-sizeof(char*));
	delete pSendBuf;
	return TRUE;
}

int CCreditUDP::ReceiveData(char*&sData,int nDataSize,unsigned long& ip,unsigned short& port,string& errorInfo,int nDeferTime)
{
	RealData* pRealData=NULL;
	int nSize,i;
	DWORD dEventFlag=0;
	if(!bCreditUDP) 
		return m_UDPSocket.ReceiveData(sData,nDataSize,ip,port,errorInfo);
	
	while(!bStopThread)   //使用可靠UDP。
	{	
		EnterCriticalSection(&hRecvLock);
		if( !m_ReceiveQueue.empty() )
		{
			pRealData = m_ReceiveQueue.front();
			if(pRealData!=NULL)
			{
				ip=pRealData->m_ip;
				port=pRealData->m_port;
				nSize=pRealData->m_nSize;
				sData=new char[nSize];
				memcpy(sData,pRealData->m_data,nSize);
				delete pRealData;
				m_ReceiveQueue.pop();
				LeaveCriticalSection(&hRecvLock);
				return nSize;
			}
			m_ReceiveQueue.pop();
		}
		LeaveCriticalSection(&hRecvLock);
		
        dEventFlag=WaitForSingleObject(hRecvEvent,50);	 
		if (dEventFlag==WAIT_TIMEOUT)
		{
			if(bStopThread)		//为了解决切换数据引起的数据堆积
				return -1;
			
			nDeferTime-=50;
			if(nDeferTime>0)
				continue;
			
			sData=NULL;
			nDataSize=-1;
			char ch[30];
			i=sprintf(ch,"超时返回！");
			ch[i]=0;
			errorInfo=ch;
			return -1;
		}
	}
	return 0;
}

DWORD WINAPI CCreditUDP::RecvProc(LPVOID lp)
{
	CCreditUDP* pThis=(CCreditUDP*)lp;
	DWORD dw = pThis->RecvProcRun();
	return dw;
}

bool CCreditUDP::Release(bool bReleaseSock)
{
	if(m_bHaveReleased)
		return true;
	m_bHaveReleased = true;
	
	bStopThread=true;
	
	if ( hSendThread || hRecvThread )
	{
		DWORD dExitCode;
		HANDLE hThreads[2];
		hThreads[0] = hRecvThread;
		hThreads[1] = hSendThread;
		string strErr = "";
		m_UDPSocket.SendData(sLocalIP, nLocalPort, "", 0, strErr);
		SetEvent( hSendEvent[0] );
		dExitCode=WaitForMultipleObjects( 2, hThreads, TRUE, 1000 );
		if( dExitCode==WAIT_TIMEOUT )
		{
			GetExitCodeThread( hSendThread, &dExitCode );
			if( dExitCode==STILL_ACTIVE )
			{
				TerminateThread( hSendThread, 1997 );
			}
			GetExitCodeThread( hRecvThread, &dExitCode );
			if( dExitCode==STILL_ACTIVE )
			{
				TerminateThread( hRecvThread, 1999 );
			}
		}
		
		CloseHandle(hRecvThread);
		CloseHandle(hSendThread);
		hRecvThread=NULL;
		hSendThread=NULL;
	}
	
	if ( bCreditUDP )
	{
		//		EnterCriticalSection( &hSendLock );
		EnterCriticalSection( &hRecvLock );
		
		EnterCriticalSection( &hSendMapLock );
		for( SendMap::iterator itSend = m_SendMap.begin(); itSend != m_SendMap.end(); itSend++ )
		{
			SendCloseMsg( itSend->first.IP, itSend->first.Port );
			delete itSend->second;
		}
		m_SendMap.clear();
		LeaveCriticalSection( &hSendMapLock );
		
		EnterCriticalSection( &hReceiveMapLock );
		for ( ReceiveMap::iterator itRecv = m_ReceiveMap.begin(); itRecv != m_ReceiveMap.end(); itRecv++ )
		{
			SendCloseMsg( itRecv->first.IP, itRecv->first.Port );
			delete itRecv->second;
		}
		m_ReceiveMap.clear();
		LeaveCriticalSection( &hReceiveMapLock );
		
		while ( !m_ReceiveQueue.empty() )
		{
			delete m_ReceiveQueue.front();
			m_ReceiveQueue.pop();
		}
		
		LeaveCriticalSection(&hRecvLock);
		//		LeaveCriticalSection(&hSendLock);
		
		ClearConnectVec();
	}
    
	if ( bReleaseSock )
	{
		m_UDPSocket.Release();
		
		CloseHandle(hSendEvent[0]);
		CloseHandle(hSendEvent[1]);
		CloseHandle(hRecvEvent);
		DeleteCriticalSection(&hVecLock);
		DeleteCriticalSection(&hSendMapLock);
		DeleteCriticalSection(&hReceiveMapLock);
		//		DeleteCriticalSection(&hSendLock);
		DeleteCriticalSection(&hRecvLock);
	}
	else
	{
		m_bHaveReleased = false;
	}
	
	return true;
}

bool CCreditUDP::IsCreditData(const char *buf, int size)
{
	//判断是否 CreditUDP 消息
	if( size < CREDIT_UDP_VER_LEN )
		return false;
	return memcmp( buf, CREDIT_UDP_VER, CREDIT_UDP_VER_LEN ) == 0;
}

void CCreditUDP::DirectSendData(unsigned long ip, unsigned short port, char *data, int len)
{
	string errorInfo;
	if ( bCreditUDP )
	{
		InnerSendUdpData(ip,port,data,len);
	}
	else
	{
		m_UDPSocket.SendData(ip,port,data,len,errorInfo);
	}
}

int CCreditUDP::GetRecvBufDataSize()
{
	return m_UDPSocket.GetRecvBufDataSize();
}

unsigned short CCreditUDP::GetPort()
{
	return m_UDPSocket.GetPort();
}

DWORD CCreditUDP::RecvProcRun()
{
	string sErrInfo = "";
    char* buf = NULL;
	UDPStruct* pRecvBuf;
	int iRecvSize = 2009;
	int iReceivedSize = 0;
	unsigned long iSourceIp = 0;
	unsigned short iSourcePort = 0;
	int iClearTime = GetTickCount();
	while( !m_bHaveReleased && !bStopThread )
	{
		iReceivedSize = m_UDPSocket.ReceiveData( buf, iRecvSize, iSourceIp, iSourcePort, sErrInfo );  
		
		if(iReceivedSize>0)
		{
			g_iSourceIp=iSourceIp;
            g_iSourcePort=iSourcePort;
		}

		if ( bStopThread )
		{
			if ( iReceivedSize >= 0)
				delete buf;
			return 0;
		}
		
		if( iReceivedSize <= 0 )
		{
			if ( GetTickCount() - iClearTime >= 50 )
			{
				iClearTime = GetTickCount();
				EnterCriticalSection( &hReceiveMapLock );
				vector<ReceiveKey> vecTemp;
				for( ReceiveMap::iterator iter = m_ReceiveMap.begin(); iter != m_ReceiveMap.end(); iter++ )
				{
					if ( GetTickCount() - iter->second->LastTime >= IPPORT_MAX_TIMEOUT )
					{
						vecTemp.push_back( iter->first );
					}
				}
				for ( vector<ReceiveKey>::iterator iterVec = vecTemp.begin(); iterVec != vecTemp.end(); iterVec++ )
				{
					SendCloseMsg( (*iterVec).IP, (*iterVec).Port );
					delete m_ReceiveMap[ *iterVec ];
					m_ReceiveMap.erase( *iterVec );
				}
				LeaveCriticalSection( &hReceiveMapLock );
			}
			
			continue;
		}
		
#ifdef OPTION_CRYPT
		if ( g_bCryptCudp )
		{
			short iLen = (short)( *((short*)( buf + iReceivedSize - 2 ) ) );
			if ( ( iLen > iReceivedSize - 2 ) || ( iLen < iReceivedSize - 2 - 16 ) )
			{
				delete buf;
				continue;
			}
			unsigned char* bufDec = new unsigned char[2048];
			CRijndael::Decrypt( (unsigned char*)buf, iReceivedSize - 2, bufDec, g_CudpCryptKey );
			delete buf;
			buf = (char*)bufDec;
			iReceivedSize = iLen;
		}
#endif
		
		if( !IsCreditData( buf, iReceivedSize ) )
		{
			delete buf;
			continue;
		}
		
		pRecvBuf = new UDPStruct(0);
		memcpy( pRecvBuf, buf, sizeof(UDPStruct) - sizeof(char*) );
		
		if( pRecvBuf->nDataSize > 1500 )
		{
			delete pRecvBuf;
			delete buf;
			continue;
		}
		if( pRecvBuf->nDataSize > 0)
		{
			pRecvBuf->data = new char[ pRecvBuf->nDataSize ];
			memcpy( pRecvBuf->data, buf+sizeof(UDPStruct) - sizeof(char*),
				pRecvBuf->nDataSize);
		}
		delete buf;
		
		//		string strIp = ::ConvertNatIP2HostIP( iSourceIp );
		//		memcpy( pRecvBuf->strSourceIP, strIp.c_str(), strIp.size() );
		//		pRecvBuf->nSourcePort = ::ConvertNatPort2HostPort( iSourcePort );
		pRecvBuf->SourceIP = iSourceIp;
		pRecvBuf->SourcePort = iSourcePort;
		
		if( pRecvBuf->nAck == 0 )       //收到数据包
		{  
			SendAckData( pRecvBuf );
			EnterCriticalSection(&hReceiveMapLock);
			if( ExistRecvSeq( pRecvBuf ) )
			{
				delete pRecvBuf;
				LeaveCriticalSection(&hReceiveMapLock);
				continue;
			}
			LeaveCriticalSection(&hReceiveMapLock);
			
			RealData* pRealData=new RealData(iSourceIp,iSourcePort,pRecvBuf->data,pRecvBuf->nDataSize);
			
			EnterCriticalSection(&hRecvLock);
			m_ReceiveQueue.push( pRealData );
			LeaveCriticalSection(&hRecvLock);
			
			delete pRecvBuf;
			SetEvent(hRecvEvent);	
		}
		else if( pRecvBuf->nAck == 1 )        //收到确认包。
		{
			bool bNeedSetEvent = false;
			SendKey key = GetSendKey( pRecvBuf, true );
			//			EnterCriticalSection(&hSendLock);
			EnterCriticalSection(&hSendMapLock);
			if( m_SendMap.find( key ) != m_SendMap.end() ) 
			{
				SendStruct* pSendStruct = m_SendMap[ key ];
				if ( !pSendStruct->SendQueue.empty() )
				{
					bNeedSetEvent = true;
					SendBuf* pTemp = pSendStruct->SendQueue.front();
					
					if ( pTemp->Buf->nSeq == pRecvBuf->nSeq )
					{
						if ( pTemp->NeedEvent )
						{
							ostringstream sEvent;
							sEvent.str("");
							sEvent << m_sEventTag << "ACKReceived" << iSourceIp << iSourcePort << pRecvBuf->nSeq;
							HANDLE hEvent = CreateEvent(NULL,FALSE,FALSE,sEvent.str().c_str());
							SetEvent( hEvent );
							CloseHandle( hEvent );
						}
						delete pTemp;
						pSendStruct->SendQueue.pop();
					}
				}
			}
			LeaveCriticalSection(&hSendMapLock);
			//			LeaveCriticalSection(&hSendLock);
			delete pRecvBuf;
			
			AddToConnectVec( key );
			SetEvent(hSendEvent[1]);
		}  				                
		else if( pRecvBuf->nAck == 2 )    //收到关闭连接消息。
		{
			SendKey sendKey = GetSendKey( pRecvBuf, true );
			ReceiveKey receiveKey = GetReceiveKey( pRecvBuf );
			EnterCriticalSection( &hSendMapLock );
			if ( m_SendMap.find( sendKey ) != m_SendMap.end() )
			{
				delete m_SendMap[ sendKey ];
				m_SendMap.erase( sendKey );
			}
			LeaveCriticalSection( &hSendMapLock );
			
			EnterCriticalSection( &hReceiveMapLock );
			if ( m_ReceiveMap.find( receiveKey ) != m_ReceiveMap.end() )
			{
				delete m_ReceiveMap[ receiveKey ];
				m_ReceiveMap.erase( receiveKey );
			}
			LeaveCriticalSection( &hReceiveMapLock );
			delete pRecvBuf;
		}
		
	}
	return 0;
}

bool CCreditUDP::ExistRecvSeq( UDPStruct* pUDPStruct )
{
	int iSeq = pUDPStruct->nSeq;
	int iCount = pUDPStruct->nSendCount;
	ReceiveKey key = GetReceiveKey( pUDPStruct );
	if ( m_ReceiveMap.find(key) != m_ReceiveMap.end() )
	{
		ReceiveStruct* pReceiveStruct = m_ReceiveMap[ key ];
		
		bool bRet = false;
		if ( pReceiveStruct->nSequence == iSeq )
		{
			if ( ( iSeq == 0 ) && ( ( GetTickCount() - pReceiveStruct->LastTime ) > 2000 ) )
			{
				
				bRet = false;
			}
			else
			{
				bRet = true;
			}
		}
		else if ( ( pReceiveStruct->nSequence < iSeq ) || ( iSeq == 0 ) )
		{
			pReceiveStruct->nSequence = iSeq;
			bRet = false;
		}
		else
		{
			bRet = true;
		}
		pReceiveStruct->LastTime = GetTickCount();
		return bRet;
	}
	else
	{
		ReceiveStruct* pReceiveStruct = new ReceiveStruct;
		pReceiveStruct->nSequence = iSeq;
		m_ReceiveMap[ key ] = pReceiveStruct;
		return false;
	}
	return false;
}

ReceiveKey CCreditUDP::GetReceiveKey(UDPStruct *pUDPStruct)
{
	//	unsigned long iSourceIP = ::ConvertIP( pUDPStruct->strSourceIP );
	//	unsigned short iSourcePort = ::ConvertPort( pUDPStruct->nSourcePort );
	//	unsigned short iDestPort = ::ConvertPort( pUDPStruct->nDestPort );
	return ReceiveKey( pUDPStruct->SourceIP, pUDPStruct->SourcePort, pUDPStruct->DestPort );
}

SendKey CCreditUDP::GetSendKey( UDPStruct* pUDPStruct, bool bReceived )
{
	//	string sIP = bReceived ? pUDPStruct->strSourceIP : pUDPStruct->strDestIP;
	//	unsigned short iPort = bReceived ? pUDPStruct->nSourcePort : pUDPStruct->nDestPort;
	//	unsigned long iIP = ::ConvertIP( sIP );
	//	iPort = ::ConvertPort( iPort );
	unsigned long iIP = bReceived ? pUDPStruct->SourceIP : pUDPStruct->DestIP;
	unsigned short iPort = bReceived ? pUDPStruct->SourcePort : pUDPStruct->DestPort;
	return SendKey( iIP, iPort );
}

void CCreditUDP::AddToConnectVec(IpPortPair pairIpPort)
{
	EnterCriticalSection(&hVecLock);
	ConnectVector.push_back(pairIpPort);
	LeaveCriticalSection(&hVecLock);
}

DWORD CCreditUDP::SendProcRun()
{
	vector<IpPortPair> vec;
	int nTimeInterval=0,nTimeTemp=0;
	nTimeInterval=GetTickCount();
	while( !m_bHaveReleased && !bStopThread )
	{	
		vec.clear();
		DWORD iRet = WaitForMultipleObjects( 2, hSendEvent, FALSE, TIME_REPEATSEND );
		
		if( m_bHaveReleased || bStopThread )
			return 0;
		
		if( iRet != WAIT_TIMEOUT )
		{
			EnterCriticalSection( &hVecLock );
			nTimeTemp = GetTickCount();
			if( nTimeTemp - nTimeInterval > 100 )
			{
				iRet = WAIT_TIMEOUT;
				nTimeInterval = nTimeTemp;
			}
			else
			{
				if ( ConnectVector.size() > 0 )
				{
					vec = ConnectVector;
				}
			}
			ConnectVector.clear();
			LeaveCriticalSection( &hVecLock );
		}
		
		EnterCriticalSection( &hSendMapLock );
		if( m_SendMap.size() >= 1 )
		{
			//			EnterCriticalSection( &hSendLock );
			if( iRet != WAIT_TIMEOUT )
			{
				for( vector<IpPortPair>::iterator iter = vec.begin(); iter!=vec.end(); iter++ )
				{
					if ( m_SendMap.find( *iter ) != m_SendMap.end() )
					{
						SendDataFunc( *iter, m_SendMap[ *iter ] );
					}
				}
				vec.clear();
			}
			else
			{
				vector<SendKey> vecTemp;
				for( SendMap::iterator iter = m_SendMap.begin(); iter != m_SendMap.end(); iter++ )
				{
					SendDataFunc( SendKey(iter->first), iter->second );
					if ( GetTickCount() - iter->second->LastTime >= IPPORT_MAX_TIMEOUT )
					{
						vecTemp.push_back( iter->first );
					}
				}
				for ( vector<SendKey>::iterator iterVec = vecTemp.begin(); iterVec != vecTemp.end(); iterVec++ )
				{
					SendCloseMsg( (*iterVec).IP, (*iterVec).Port );
					delete m_SendMap[ *iterVec ];
					m_SendMap.erase( *iterVec );
				}
			}
			//			LeaveCriticalSection(&hSendLock);
		}
		LeaveCriticalSection(&hSendMapLock);	
	}
	return 0;
}

void CCreditUDP::SendDataFunc( SendKey& key, SendStruct* pSendStruct)
{
	if ( pSendStruct->SendQueue.empty() )
	{
		return;
	}
	UDPStruct* pBuffer = pSendStruct->SendQueue.front()->Buf;
	SendHartPack( key, pSendStruct );   //发送心跳包。
	SendUDPData( pBuffer );
	pBuffer->nSendCount++;
	if((pBuffer->nSendCount>=pBuffer->nReSend)&&(pBuffer->nReSend>0))
	{
		delete pSendStruct->SendQueue.front();
		pSendStruct->SendQueue.pop();
	}
	pSendStruct->LastTime = GetTickCount();
}

void CCreditUDP::SendCloseMsg(unsigned long ip, unsigned short port)
{
	UDPStruct buffer(0);
	buffer.nAck = 2;
	//	string sIP = ::ConvertNatIP2HostIP( ip );
	//	memcpy( buffer.strDestIP, sIP.c_str(), sIP.size() );
	//	buffer.nDestPort = ConvertPort( port );
	buffer.DestIP = ip;
	buffer.DestPort = port;
//	string sErr = "";
//	m_UDPSocket.SendData( ip, port, (char*)&buffer, sizeof(UDPStruct), sErr );
	InnerSendUdpData( ip, port, (char*)&buffer, sizeof(UDPStruct) );
}

CUDPSocket* CCreditUDP::GetUdpSock()
{
	return &m_UDPSocket;
}

int CCreditUDP::GetCurrentSeq(unsigned long ip, unsigned short port)
{
	SendKey key(ip, port);
	int iRet = 0;
	EnterCriticalSection( &hSendMapLock );
	if( m_SendMap.find( key ) != m_SendMap.end() ) 
	{
		SendStruct* pSendStruct = m_SendMap[ key ];
		iRet = pSendStruct->nSequence;
	}
	LeaveCriticalSection(&hSendMapLock);
	return iRet;
}

bool CCreditUDP::InnerSendUdpData(unsigned long iIp, unsigned short iPort, char* pData, int iLen)
{
	string errinfo;
	bool bRet;
#ifdef OPTION_CRYPT
	if ( g_bCryptCudp )
	{
		unsigned char* pDataEnc = new unsigned char[iLen + 2 + 16];
		short iLenEnc = CRijndael::Encrypt( (unsigned char*)pData, iLen, pDataEnc, g_CudpCryptKey );
		memcpy( pDataEnc + iLenEnc, &iLen, 2 );
		bRet = m_UDPSocket.SendData(iIp,iPort,(char*)pDataEnc,iLenEnc + 2,errinfo);
		delete pDataEnc;
	}
	else
	{
		bRet = m_UDPSocket.SendData(iIp,iPort,pData,iLen,errinfo);
	}
#else
	bRet = m_UDPSocket.SendData(iIp,iPort,pData,iLen,errinfo);
#endif
	return bRet;
}