// SmsSendModule.cpp: implementation of the CSmsSendModule class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SmsSendModule.h"
#include <afxinet.h>
#include "ConsoleMessageDef.h"
#include "Environment.h"

#include "base64.h"
#include "MD5.h"
#include "Spliter.h"
#include "Log.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CSmsSendModule* CSmsSendModule::__Module = NULL;

string SMSSend_URL = "";
UINT SMSSend_Port = 90;
UINT g_nReceiverCount = 0;
extern BOOL g_bMakelog;
//////////////////////////////////////////////////////////////////////////
#define CRLF    ("\r\n")
//////////////////////////////////////////////////////////////////////////

CSmsSendModule::CSmsSendModule()
{
	memset(m_buf, 0, 10240);
	m_cbOut = 0;
}

CSmsSendModule::~CSmsSendModule()
{
	Relese();
}

CSmsSendModule* CSmsSendModule::Instance()
{
	if(__Module == NULL)
	{
		__Module = new CSmsSendModule;
	}
	
	SMSSend_URL = CEnvironment::Instance().m_sSMSServerIP;
	if (SMSSend_URL == "")
		SMSSend_URL = "219.234.83.35";
	
	return __Module;
}

void CSmsSendModule::Relese()
{
	if(__Module != NULL)
		delete __Module;
	__Module = NULL;
}

bool CSmsSendModule::SendSMS(LPCTSTR receive, LPCTSTR content,
							 LPCTSTR managerid, LPCTSTR agentanme, LPCTSTR agentpwd,  LPCTSTR sp, LPCTSTR corpname, HWND hwnd)
{
	CString sUrlParam, sParam1,sParam2;
	CString sTime = COleDateTime::GetCurrentTime().Format("%Y%m%d%H%M%S");
	
	sParam1.Format("phone=%s&msg=%s&ManagerID=%s&SPNum=%s&Short=%s&NTime=%s",
		receive,content,managerid,sp,corpname,sTime);
	
	int iLen= sParam1.GetLength();
	iLen=(iLen+iLen/2)+5;
	char* szEncode=new char[iLen];
	int iRlt=Base64Encode(szEncode, sParam1);
	sParam1=szEncode;
	delete szEncode;
	
	sParam2.Format("%s|%s|%s",agentanme,agentpwd,sTime);
	
	MD5 md5;
	char ch[1024];
	bool b = md5.MD5Hash(sParam2, ch);
	sParam2 = ch;
	
	sUrlParam.Format("SMS@&@AgentName@=@%s@&@md5@=@%s@&@b64@=@%s", agentanme, sParam2, sParam1);
	
	//AgentName|密码|时间
	//时间格式：
	//年月日时分秒14位（如：20071026175727）
	ThreadParam* p = new ThreadParam;
	p->lpSMSParam = sUrlParam;
	p->lpThis = this;
	p->hWnd = hwnd;
	//////////////////////////////////////////////////////////////////////////
	//by dido 10/04/07
	CSpliter spliter(receive, "|");
	g_nReceiverCount = spliter.GetSize();
	//////////////////////////////////////////////////////////////////////////
	DWORD dwThreadID = 0;
	if(!CreateThread(NULL,0,ThreadFunction, p, 0, &dwThreadID))
		return false;
	return true;
}

DWORD WINAPI CSmsSendModule::ThreadFunction(LPVOID lpThis)
{
	ThreadParam* p = (ThreadParam*)lpThis;
	CSmsSendModule* lp = (CSmsSendModule*)p->lpThis;
	lp->ThreadMain(p);
	delete p;
	return 1;
}

void CSmsSendModule::ThreadMain(ThreadParam* pParam)
{
	CString sResult;
	if(HttpRequest(SMSSend_URL.c_str(),SMSSend_Port,"",pParam->lpSMSParam,sResult,pParam->hWnd) == 1)
	{
		GetResult(sResult,sResult);
		if(sResult.GetLength() == 1 && atoi(sResult) == 1)
		{
			if(IsWindow(pParam->hWnd))
				::PostMessage(pParam->hWnd,WM_SMS_SENDSUCCES,0,0);
		}
		else
		{
			COPYDATASTRUCT faildnumber;
			faildnumber.dwData = WM_SMS_SENDFAILEDNUM;
			faildnumber.cbData = sResult.GetLength()+1;
			faildnumber.lpData = (void*)sResult.GetBuffer(sResult.GetLength()+1);
			sResult.ReleaseBuffer();
			if(IsWindow(pParam->hWnd))
			{
				::SendMessage(pParam->hWnd, WM_COPYDATA,0, (LPARAM)(void*)&faildnumber);
				::PostMessage(pParam->hWnd,WM_SMS_SENDFAILED,0,0);
			}
		}
	}
	else
	{
		GetResult(sResult,sResult);
		if(IsWindow(pParam->hWnd))
			::PostMessage(pParam->hWnd,WM_SMS_SENDFAILED,0,0);		
	}
}

void CSmsSendModule::GetResult(CString sValue, CString& sResult)
{
	//1HTTP/1.1 200 OK
	//Server: MS-MFC-HttpSvr/1.0
	//Date: 
	//
	//1
	
	int nIndex = sValue.ReverseFind('\n');
	if(nIndex == -1)
	{
		sResult = sValue;
	}
	else
	{
		sResult = sValue.Right(sValue.GetLength() - nIndex - 1);
	}
}

// int CSmsSendModule::HttpRequest(LPCTSTR szHost, UINT nPort, LPCTSTR szRequestFile, 
// 								LPCTSTR szArgument, CString& sResult, 
// 								HWND hWnd)
// {
// 	CHttpFile* pFile= NULL;
// 	CHttpConnection * pConnection= NULL;
// 	CInternetSession iSession("use post",1,INTERNET_OPEN_TYPE_PRECONFIG);
// 	
// 	CString tmpResult;
// 	try
// 	{
// 		pConnection= iSession.GetHttpConnection(szHost,(INTERNET_PORT)nPort,NULL,NULL);
// 		if(pConnection==NULL)
// 			return -1;
// 
// 		pFile=pConnection->OpenRequest(
// 			CHttpConnection::HTTP_VERB_GET,
// 			szRequestFile,
// 			NULL,1,NULL,NULL,
// 			INTERNET_FLAG_EXISTING_CONNECT|INTERNET_FLAG_TRANSFER_ASCII|INTERNET_FLAG_RELOAD|INTERNET_FLAG_DONT_CACHE);
// 
// 		if(pFile==NULL) 
// 		{
// 			pConnection->Close();
// 			delete pConnection;
// 			return -1;
// 		}
// 
// 		CString strHeaders=_T("Accept: */*\r\n"
// 			"Content-Type:"
// 			"application/x-www-form-urlencoded"
// 			"\r\n");
// 
// 		if(pFile->SendRequest(strHeaders,(LPVOID)szArgument,lstrlen(szArgument)))
// 		{
// 			//	CString strtemp;		
// 			CHAR strtemp[1024];
// 			while(pFile->ReadString(strtemp,1024))
// 				tmpResult+=strtemp;			
// 		}
// 		pFile->Close();
// 		delete pFile;
// 		pFile= NULL;
// 		
// 		pConnection->Close();
// 		delete pConnection;
// 		pConnection= NULL;
// 		
// 		iSession.Close();
// 	}
// 	catch(...)
// 	{
// 		if (pConnection)
// 		{
// 			pConnection->Close();
// 			delete pConnection;
// 		}
// 		if (pFile)
// 		{
// 			pFile->Close();
// 			delete pFile;
// 		}
// 		return -1;
// 	}
// 	
// 	sResult = tmpResult;
// 	return 1;
// }

int CSmsSendModule::StuffString( const CString& strData )
{
	int nLen = strData.GetLength()*sizeof(TCHAR);
	// make sure there's enough room....
	if ( m_cbOut + nLen > sizeof(m_buf)/*sizeof(m_bufN)*/ ) { // error
		// error
	}
	// copy the data....
	MoveMemory( m_buf + m_cbOut, (LPCSTR)strData, nLen );
	m_cbOut += nLen;
	// return amount of space left....
	return (sizeof(m_buf) - m_cbOut);
}

void CSmsSendModule::MakeHttp(CString &i_strData)
{
	CString strVer1 = "GET /?";
	CString strData = i_strData;
	CString strVer2=" HTTP/1.1";
//	CString strStatus = "200 OK";
	CString strA="Accept: */*";
	CString strAL="Accept-Language: zh-cn";
	CString strUA="User-Agent:Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 5.1; Trident/4.0;(R1 1.3) .NET CLR 2.0.50727)";
	CString strAE="Accept-Encoding: gzip, deflate";
	CString strH="Host: 219.234.83.35:90";
	CString strConn="Connection: Keep-Alive";

	StuffString( strVer1 );
	StuffString( strData );
	StuffString( strVer2 );
	StuffString( CRLF );
	StuffString( strA );
	StuffString( CRLF );
	StuffString( strAL );
	StuffString( CRLF );
	StuffString( strUA );
	StuffString( CRLF );
	StuffString( strAE );
	StuffString( CRLF );
	StuffString( strH );
	StuffString( CRLF );
	StuffString( strConn );
	StuffString( CRLF );
//	StuffString("");
	StuffString( CRLF );

//	StuffHeader( "Server", strServer );

	// stuff the date....
//	StuffHeader( "Date", GetHttpDate() );

//	StuffString( CRLF );
}



int CSmsSendModule::StuffHeader( CString strName, CString strValue )
{
	StuffString( strName );
	StuffString( ": " );
	StuffString( strValue );
	return StuffString( CRLF );
}

void CSmsSendModule::MakeHttpBody(string& bodyContent)
{
	//this->EncodeMsg(bodyContent);
	StuffString( CString( bodyContent.c_str() ) );
}


CString CSmsSendModule::GetHttpDate( LPFILETIME pft )
{
	SYSTEMTIME st;
	if ( pft )
		FileTimeToSystemTime( pft, &st );
	else
		GetSystemTime( &st );

	CTime timeHttp( st );
/////	return timeHttp.Format( IDS_HTTPTIME );

	return "";
}


int CSmsSendModule::HttpRequest(LPCTSTR szHost, UINT nPort, LPCTSTR szRequestFile, 
								LPCTSTR szArgument, CString& sResult, 
								HWND hWnd)
{
	bool bSucc = false;
	bSucc = m_Socket.Connect(szHost, nPort);
	if(bSucc) 
	{
		CString strData = szArgument;
		MakeHttp(strData);
		int iLen=-1;
		iLen=m_Socket.Send((char*)m_buf,m_cbOut);
		m_cbOut=0;
		memset(m_buf, 0, sizeof(m_buf));
		if(iLen >= 0)
		{
			m_Socket.Receive(m_buf, sizeof(m_buf), 15 * (g_nReceiverCount + 1));
			sResult = AnalyseHttpReturn(m_buf, sizeof(m_buf));
			m_Socket.Release();
			return 1;
		}
		m_Socket.Release();
	}
	return -1;
}

CString CSmsSendModule::AnalyseHttpReturn(char *pRes, unsigned int nResSize)
{
	if (pRes == NULL)
	{
		return CString("超时未收到短信服务器返回信息!");
	}

	int nResultContentEnd = 0;
	int nResultContentStart = 0;
	for (; nResultContentEnd < nResSize;)
	{
		if (pRes[nResultContentEnd] == 0
			&& pRes[nResultContentEnd + 1] == 0
			&& pRes[nResultContentEnd + 2] == 0
			&& pRes[nResultContentEnd + 3] == 0
			&& pRes[nResultContentEnd + 4] == 0)	
			break;
		++nResultContentEnd;
	}

	if (nResultContentEnd == 0)
		return CString("短信服务器返回信息为空!");

	for (nResultContentStart = nResultContentEnd - 1; nResultContentStart > 0; --nResultContentStart)
	{
		if (pRes[nResultContentStart] == 10 || pRes[nResultContentStart] == 13)
		{
			break;
		}
	}

	CString strResult = "";
	if (pRes[nResultContentStart + 1])
	{
		strResult = &pRes[nResultContentStart + 1];
	}
	
	return strResult;
}
