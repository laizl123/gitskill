// SmsSendModule.h: interface for the CSmsSendModule class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SMSSENDMODULE_H__C0D3A75E_3C6A_4D5D_82F8_B2459E52EA73__INCLUDED_)
#define AFX_SMSSENDMODULE_H__C0D3A75E_3C6A_4D5D_82F8_B2459E52EA73__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//
//phone=158********|136********|&msg=短信内容&ManagerID=3423424& AgentName=abc@adda.com&SPNum=3412432&&Short=中国人企

#include "tcpsocket.h"

struct ThreadParam
{
	CString lpSMSParam;
	void* lpThis;
	HWND hWnd;
};

class CSmsSendModule  
{
public:
	virtual ~CSmsSendModule();

public:
	CString AnalyseHttpReturn(char *pRes, unsigned int nResSize);
	static CSmsSendModule* Instance();
	bool SendSMS(LPCTSTR receive, LPCTSTR content,
		LPCTSTR managerid, LPCTSTR agentanme, LPCTSTR agentpwd,
		LPCTSTR sp, LPCTSTR corpname, HWND hwnd=NULL);


	static DWORD WINAPI ThreadFunction(LPVOID lpThis);
	void ThreadMain(ThreadParam* pParam);
private:
	int HttpRequest(LPCTSTR szHost, UINT nPort, LPCTSTR szRequestFile, 
							  LPCTSTR szArgument, CString& sResult, 
							  HWND hWnd=NULL);

	void GetResult(CString sValue, CString& sResult);

	//////////////////////////////////////////////////////////////////////////
	char  m_buf[10240];
	int         m_cbOut;
	CTcpSocket m_Socket;
	void MakeHttp(CString &i_strData);
	int StuffString( const CString& );
	int StuffString( UINT uId );
	int StuffStatus( UINT uMsg );
	int StuffError( UINT uMsg );
	int StuffHeader( CString strName, CString strValue );
	int StuffHeader( CString strName, int nValue );
	void MakeHttpBody(string& bodyContent);
	CString GetHttpDate( LPFILETIME pft = NULL );
	//////////////////////////////////////////////////////////////////////////

protected:
	CSmsSendModule();
	void Relese();
	static CSmsSendModule* __Module;
};

#endif // !defined(AFX_SMSSENDMODULE_H__C0D3A75E_3C6A_4D5D_82F8_B2459E52EA73__INCLUDED_)
