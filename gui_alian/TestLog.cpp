// TestLog1.cpp: implementation of the CTestLog class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GlobalOperation.h"
#include "TestLog.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CTestLog* CTestLog::_TestLog = 0;

CTestLog::CTestLog()
{
	this->m_bMakeLog = false;
}

CTestLog::~CTestLog()
{
	::DeleteCriticalSection(&this->m_LogQueueLock);
	::CloseHandle(m_LogEvent);
}

void CTestLog::MakeLog(string logType, string logID, string devID, string logContent)
{
	if(!this->m_bMakeLog)
		return;

	string sTime = this->GetLocalTime();

	ostringstream strStream;
	strStream.str("");
	strStream << sTime << ",";
	strStream << logType << ",";
	strStream << logID << ",";
	strStream << devID << ",";
	strStream << logContent;

	string sMsg = strStream.str();

	AddLogToQueue(sMsg);
	
	return;
}

void CTestLog::init(string directory, string fileName)
{
	this->m_bMakeLog = true;

	this->m_sDirectory = directory;
	this->m_sFileName = fileName;

	if(this->m_sFileName.empty())
	{
		this->m_bMakeLog = false;
		return;
	}

	if(!this->m_sDirectory.empty())
	{
		if(this->m_sDirectory[m_sDirectory.length()-1] != '\\')
			this->m_sDirectory += "\\";
	}

	::InitializeCriticalSection(&this->m_LogQueueLock);
	m_LogEvent = ::CreateEvent(NULL, false, false, "Event_TestLog");
	m_StopThreadEvent = ::CreateEvent(NULL, false, false, "Event_StopTestLogThread");

	//AfxBeginThread(CTestLog::ThreadTestLog,this);
	HANDLE hThread; 
	DWORD dwThreadId = 1;
	hThread = CreateThread( 
			NULL,                        // default security attributes 
			0,                           // use default stack size  
			ThreadTestLog,               // thread function 
			this,						 // argument to thread function 
			0,                           // use default creation flags 
			&dwThreadId); 
}

CTestLog* CTestLog::GetInstance()
{
	if(0 == _TestLog)
		_TestLog = new CTestLog();
	
	return _TestLog;
}

void CTestLog::destroy()
{
	if (_TestLog != NULL)
	{
		delete _TestLog;
		_TestLog = NULL;
	}
}

DWORD WINAPI CTestLog::ThreadTestLog(LPVOID lp)
{
	CTestLog* pTestLog = (CTestLog*)lp;

	string sFilename,sNewFilename,sRealFilename;
	FILE * fp;

	string tempEventData;
	pTestLog->m_bIsStop = false;
	int retval;
	string sFullDirectory("");
	int iSleepTag = 0;
	while(!pTestLog->m_bIsStop)
	{
		retval = ::WaitForSingleObject(pTestLog->m_LogEvent,1000);
		if(pTestLog->m_bIsStop)
			break;
		while(1)
		{
			if(!pTestLog->GetLogFromQueue(tempEventData))
				break;
			if(pTestLog->m_bIsStop)
				break;
			if(!pTestLog->m_sDirectory.empty())
			{
				sFullDirectory = pTestLog->m_sDirectory;
				sFullDirectory += tempEventData.substr(0,10);
				sFullDirectory += "\\";
			}
			else
				sFullDirectory = GetAppPath();
			CreateMultipleLevelDirectory(sFullDirectory);

			sRealFilename = "";
			sRealFilename += sFullDirectory;
			sRealFilename += pTestLog->m_sFileName;
			if(sRealFilename.length()>4 && sRealFilename.compare(0,4,".txt")==0)
				sRealFilename = sRealFilename.substr(0, sRealFilename.length()-4);
			
			sRealFilename += "_";
			sRealFilename += tempEventData.substr(11,2);
			sRealFilename += ".txt";
			int iCount = 0;
			while(iCount < 10)
			{
				if(fp = fopen(sRealFilename.c_str(),"a"))
				{
					fprintf(fp,"%s\r\n",tempEventData.c_str());
					fclose(fp);
					break;
				}
				Sleep(100);
				iCount++;
			}
			iSleepTag++;
			if ( iSleepTag >= 10 )
			{
				iSleepTag = 0;
				Sleep(1);
			}
		}
	}

	//发送事件通知主线程本线程已经结束
	SetEvent(pTestLog->m_StopThreadEvent);

	ExitThread(0);
	return 1;	
}

void CTestLog::MakeLog(string logContent)
{
	string s = this->GetLocalTime();

	ostringstream ostream;
	ostream.str("");
	ostream << s << " " << logContent;

	AddLogToQueue(ostream.str());
}
