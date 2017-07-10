// ThreadBase.cpp: implementation of the ThreadBase class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ThreadBase.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ThreadBase::ThreadBase()
{
	m_bRun = false;
	m_hThread = NULL;
	m_sThreadName = "None";
}

ThreadBase::~ThreadBase()
{
	TRACE( " -->  [ThreadBase] Tread Exit: [%s] <-- \n", m_sThreadName.c_str());
	Stop();
	TRACE( " -->  [ThreadBase] Tread Stop OK : [%s] <-- \n", m_sThreadName.c_str());
}

void ThreadBase::Start()
{
	m_bRun = true;
	m_hThread = CreateThread( NULL, 0, ThreadProc, this, 0, NULL );
}

void ThreadBase::Stop(DWORD dwTimeOut)
{
	if ( m_hThread == NULL )
		return;

	m_bRun = false;
	if ( IsRun() )
	{
		DWORD dwRet = WaitForSingleObject( m_hThread, dwTimeOut );
		if ( dwRet == WAIT_TIMEOUT )
		{
			TerminateThread( m_hThread, 1997 );
		}
	}
	CloseHandle( m_hThread );
	m_hThread = NULL;
}

DWORD WINAPI ThreadBase::ThreadProc(LPVOID lpThis)
{
	srand( GetCurrentThreadId() * GetTickCount() );
	ThreadBase* pThis = (ThreadBase*)lpThis;
	TRACE(" --> TreadName=[%s] Start <--\n", pThis->m_sThreadName.c_str());
	DWORD dwRet = pThis->Run();
	TRACE(" --> TreadName=[%s] end <--\n", pThis->m_sThreadName.c_str());
	pThis->m_bRun = false;
	return dwRet;
}

bool ThreadBase::IsRun()
{
	DWORD dwExitCode;
	GetExitCodeThread( m_hThread, &dwExitCode );
	return dwExitCode == STILL_ACTIVE;
}
