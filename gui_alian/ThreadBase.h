// ThreadBase.h: interface for the ThreadBase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_THREADBASE_H__C105D5D4_64E6_4909_9D59_43D5CE95D162__INCLUDED_)
#define AFX_THREADBASE_H__C105D5D4_64E6_4909_9D59_43D5CE95D162__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ThreadBase  
{
public:
	ThreadBase();
	virtual ~ThreadBase();
public:
	bool IsRun();
	virtual void Start();
	virtual void Stop(DWORD dwTimeOut = INFINITE);
protected:
	bool m_bRun;
	HANDLE m_hThread;
	static DWORD WINAPI ThreadProc(LPVOID lpThis);
	virtual DWORD Run() = 0;
	string m_sThreadName;
};

#endif // !defined(AFX_THREADBASE_H__C105D5D4_64E6_4909_9D59_43D5CE95D162__INCLUDED_)
