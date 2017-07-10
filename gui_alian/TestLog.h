// TestLog1.h: interface for the CTestLog class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTLOG1_H__22D68D84_A822_4EC1_AF57_2861A707AD95__INCLUDED_)
#define AFX_TESTLOG1_H__22D68D84_A822_4EC1_AF57_2861A707AD95__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Log.h"

class CTestLog : public CLog  
{
public:
	void MakeLog(string logContent);
	static DWORD WINAPI ThreadTestLog(LPVOID lp);
	static void destroy();
	static CTestLog* GetInstance();
	void init(string directory, string fileName);
	void MakeLog(string logType, string logID, string devID, string logContent);
	virtual ~CTestLog();
protected:
	CTestLog();
private:
	static CTestLog* _TestLog;
};

#endif // !defined(AFX_TESTLOG1_H__22D68D84_A822_4EC1_AF57_2861A707AD95__INCLUDED_)
