// CreditUDPThread.cpp: implementation of the CCreditUDPThread class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AgentPanelOcx.h"
#include "CreditUDPThread.h"
#include "IPCCMessage.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include "Log.h"
extern CString g_strLogFilePath;


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCreditUDPThread::CCreditUDPThread()
{
	m_uLocalPort = 0;
	m_bSendHeart = FALSE;
}

CCreditUDPThread::~CCreditUDPThread()
{

}


BOOL CCreditUDPThread::InitInstance()
{
	

	string sErrInfo;
	CString sMsg("");
	CString sErrMsg("");
	while(m_bStopThread == FALSE)
	{
		char* msg = NULL;
		
		unsigned long theIp;
		unsigned short thePort;
		int iRet = -1;

		//CLog::DirectWriteFile((string)g_strLogFilePath, "Infobird_ocx.log", "before ReceiveData");
		if(m_bSendHeart == TRUE)
		{
			m_pSockHandle->HandleHeartTimeOut();
		}

		iRet = m_CreditUDP.ReceiveData(msg,1024,theIp,thePort,sErrInfo, 500);
		if(0 == iRet)
		{
			Sleep(10);
			continue;
		}
		
		if(-1 == iRet)
		{
			Sleep(10);
			continue;	
		}
		if (msg == NULL){
			continue;
		}
			
		//处理消息
		m_ipcc_IP = theIp;
		m_ipcc_Port = thePort;
		DisposeMainSockMsg(msg, iRet, theIp, thePort);
		delete[] msg;
	}
	return FALSE;
}

int CCreditUDPThread::ExitInstance()
{
	m_hThread = 0;        
	m_nThreadID = 0;
	m_bStopThread = FALSE;
	return CWinThread::ExitInstance();

}

// 发送数据
void CCreditUDPThread::SendUDPData(char* szData, int len)
{
	string strErr;
	m_CreditUDP.SendData(m_ipcc_IP, m_ipcc_Port, szData, len, strErr);
}

///处理消息
bool CCreditUDPThread::DisposeMainSockMsg(char* pmsg, int msgsize, unsigned long ip, unsigned short port)
{
	CIPCCMsgExchanger msgExchanger;
	
	__EIPCCMsgClass msgClass;
	__EIPCCMsgType msgType;
	msgExchanger.GetMsgHeader(pmsg, msgsize, msgClass, msgType);
	

	//stringstream ss;
	//ss<<"DisposeMainSockMsg msgClass="<<msgClass <<" msgType ="<<msgType;
	//CLog::DirectWriteFile((string)g_strLogFilePath,"Infobird_ocx.log",(string)ss.str());


	if(msgClass == Class_EndEgn)
	{
		TRACE(" --> CMainConsole Mainthread end <--\n");
		return false;
	}

	if(msgClass != Class_FuncEvent)
	{
		//CLog::DirectWriteFile((string)g_strLogFilePath,"Infobird_ocx.log","xxx");
		m_pSockHandle->HandleRecvMsg(pmsg, msgsize);
		//CLog::DirectWriteFile((string)g_strLogFilePath,"Infobird_ocx.log","xxx2");
	}
	else if(m_pMessageWnd != NULL)
	{
		//CLog::DirectWriteFile((string)g_strLogFilePath,"Infobird_ocx.log","yyy");
		char* pData = new char[msgsize];
		memcpy(pData, pmsg, msgsize);
		m_pMessageWnd->PostMessage(WM_SOCKMSG, (WPARAM)pData, (LPARAM)msgsize);
		//CLog::DirectWriteFile((string)g_strLogFilePath,"Infobird_ocx.log","yyy2");
	}
	return true;
}