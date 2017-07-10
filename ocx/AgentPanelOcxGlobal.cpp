// AgentPanelOcxGlobal.cpp: implementation of the CAgentPanelOcxGlobal class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AgentPanelOcx.h"
#include <tlhelp32.h>
#include "AgentPanelOcxGlobal.h"

/************************************************************************/
//	得到应用程序的路径
/************************************************************************/
#include   <shlobj.h>
#pragma comment(lib, "shell32.lib")

CString GetDataFilesPath()
{
	CHAR szExePath[_MAX_PATH];
	memset(szExePath, 0, _MAX_PATH);
	SHGetSpecialFolderPath(NULL,szExePath,CSIDL_COMMON_DOCUMENTS,FALSE);
	strcat(szExePath, "\\Infobird");
	return szExePath;
}
CString GetMoudlePath()
{
	CHAR szExePath[_MAX_PATH];
	memset(szExePath, 0, _MAX_PATH);
	HMODULE hMoudle = AfxGetInstanceHandle();
	GetModuleFileName(hMoudle, szExePath,  _MAX_PATH);
	char* pPath = strrchr(szExePath, '\\');
	*pPath = '\0';
	return szExePath;
}

BOOL KillTheProcess(CString exeName)
{
	BOOL bKill = FALSE;
	HANDLE handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 info = { 0 };
	info.dwSize = sizeof(PROCESSENTRY32);
	if (Process32First(handle, &info))
	{
		do
		{
			CString strname = info.szExeFile;
			strname.MakeLower();
			exeName.MakeLower();
			if (strname != exeName)
				continue;
			HANDLE hp = OpenProcess(SYNCHRONIZE | PROCESS_TERMINATE, FALSE, info.th32ProcessID);
			TerminateProcess(hp, 0);
			CloseHandle(hp);
			bKill = TRUE;
		} while (Process32Next(handle, &info));
	}
	CloseHandle(handle);
	return bKill;
}

BOOL StartTheProcess(CString fileName, string s_port)
{

	DWORD status = GetFileAttributes(fileName);
	if (status == 0xffffffff
		|| (status & (FILE_ATTRIBUTE_DIRECTORY != 0)))
	{
		return FALSE;
	}

	HINSTANCE hInstance = ShellExecute(NULL, "Open", fileName, s_port.c_str(), NULL, SW_HIDE);
	if (hInstance){
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}


BOOL QueryProcessExsit(CString pExeName)
{
	CString exeName = pExeName;

	exeName.MakeLower();
	BOOL bRunning = FALSE;
	HANDLE handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 info = { 0 };
	info.dwSize = sizeof(PROCESSENTRY32);
	if (Process32First(handle, &info))
	{
		do
		{
			CString strname = info.szExeFile;
			strname.MakeLower();
			if (strname == exeName)
			{
				bRunning = TRUE;
				break;
			}
		} while (Process32Next(handle, &info));
	}
	CloseHandle(handle);
	return bRunning;
}
