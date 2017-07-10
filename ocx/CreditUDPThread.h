// CreditUDPThread.h: interface for the CCreditUDPThread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CREDITUDPTHREAD_H__CA878EDD_8886_4AB7_BE90_94C37A538523__INCLUDED_)
#define AFX_CREDITUDPTHREAD_H__CA878EDD_8886_4AB7_BE90_94C37A538523__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "CreditUDP.h"
#include "SockHandle.h"
#include "ServerThread.h"

class CCreditUDPThread : public CServerThread  
{
public:
	CCreditUDPThread();
	virtual ~CCreditUDPThread();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServerThread)
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

public:
	// 
	BOOL m_bSendHeart;
	// 
	CCreditUDP		m_CreditUDP;
	// ���ض˿�
	UINT			m_uLocalPort;
	// ���ͽ��յ�ַ
	unsigned long   m_ipcc_IP;
	unsigned short  m_ipcc_Port;
	CSockHandle*	m_pSockHandle;
	
	// ��������
	void SendUDPData(char* szData, int len);
	bool DisposeMainSockMsg(char* pmsg, int msgsize, unsigned long ip, unsigned short port);	///������Ϣ

};

#endif // !defined(AFX_CREDITUDPTHREAD_H__CA878EDD_8886_4AB7_BE90_94C37A538523__INCLUDED_)
