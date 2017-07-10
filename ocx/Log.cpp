// Log.cpp: implementation of the CLog class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include <string>
#include <iostream>
#include <sstream>
#include <deque>

#include "GlobalOperation.h"
#include "Log.h"
using namespace std;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern CString g_strLogFilePathLocal;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLog::CLog()
{
	this->m_bMakeLog = false;
	InitializeCriticalSection(&m_LogQueueLock);
}

CLog::~CLog()
{
	DeleteCriticalSection(&m_LogQueueLock);
}

void CLog::StopMakeLog()
{
	this->m_bMakeLog = false;
}

void CLog::ResumeMakeLog()
{
	this->m_bMakeLog = true;
}

void CLog::DirectWriteFile(string path, string fileName, string msg)
{
	if(fileName.empty() || msg.empty())
 		return;

	::CreateMultipleLevelDirectory(path);
 
	string sPath(path);
	if(sPath.length()>1 && sPath[sPath.length()-1]!='\\')
		sPath += "\\";
 	string sFileName(sPath + fileName);

	string sLog = GetLocalTime() + " " + msg;

 	FILE * fp;
 	if(fp = fopen(sFileName.c_str(),"a"))
 	{
 		fprintf(fp,"%s\r\n", sLog.c_str());
 		fclose(fp);
 	}
}

void CLog::AddLogToQueue(string log)
{
	::EnterCriticalSection(&m_LogQueueLock);
	this->m_LogQueue.push_back(log);
	::LeaveCriticalSection(&m_LogQueueLock);

	SetEvent(this->m_LogEvent);
}

BOOL CLog::GetLogFromQueue(string &log)
{
	::EnterCriticalSection(&m_LogQueueLock);
	string sLog("");

	if(this->m_LogQueue.size() <= 0)
	{
		::LeaveCriticalSection(&m_LogQueueLock);
		return false;
	}

	sLog = this->m_LogQueue.front();
	this->m_LogQueue.pop_front();

	if(sLog.empty())
	{
		::LeaveCriticalSection(&m_LogQueueLock);
		return false;
	}

	log = sLog;
	::LeaveCriticalSection(&m_LogQueueLock);

	return true;
}

void CLog::release()
{
	this->m_bIsStop = true;
	SetEvent(this->m_LogEvent);

	::WaitForSingleObject(this->m_StopThreadEvent,2000);
}

string CLog::GetLocalTime()
{
	ostringstream strStream;
	SYSTEMTIME t1;
	::GetLocalTime(&t1);
	strStream.str("");

	char year[5];
	char month[3];
	char day[3];
	char hour[3];
	char minute[3];
	char second[3];
	memset(year, 0, 5);
	memset(month, 0, 3);
	memset(day, 0, 3);
	memset(hour, 0, 3);
	memset(minute, 0, 3);
	memset(second, 0, 3);

	sprintf(year, "%4d", t1.wYear);
	sprintf(month, "%02d", t1.wMonth);
	sprintf(day, "%02d", t1.wDay);
	sprintf(hour, "%02d", t1.wHour);
	sprintf(minute, "%02d", t1.wMinute);
	sprintf(second, "%02d", t1.wSecond);

	strStream << year << "-" << month << "-" << day << " ";
	strStream << hour << ":" << minute << ":" << second;

	string sTime = strStream.str();

	return sTime;
}
