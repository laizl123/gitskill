// stdafx.cpp : source file that includes just the standard includes
//	ICServingAgentClient.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"


/************************************************************************/
//	得到应用程序的路径
/************************************************************************/
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