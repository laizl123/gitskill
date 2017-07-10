// PrivilegeAdjust.cpp: implementation of the CPrivilegeAdjust class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ICServingAgentClient.h"
#include "PrivilegeAdjust.h"
#include "PrivilegeDlg.h"
#include "Environment.h"
#include "MainFrm.h"
#include "Log.h"

#include "Lm.h"
#include "Tlhelp32.h" 
#include "SHLWAPI.h"
#pragma comment(lib, "Shlwapi.lib")
#pragma comment(lib, "Netapi32.lib")
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPrivilegeAdjust::CPrivilegeAdjust()
{
	//m_strUser = "";
	//m_strPwd = "";
}

CPrivilegeAdjust::~CPrivilegeAdjust()
{

}

BOOL CPrivilegeAdjust::IsHasPrivilege()
{
	WCHAR szUser[MAX_PATH] = L"\0";	
	// 当前用户
	DWORD nLen = MAX_PATH-1;
	GetUserNameW(szUser, &nLen);
	return IsHasPrivilege(szUser);
}

BOOL CPrivilegeAdjust::IsHasPrivilege(LPCWSTR szUser)
{
	CStringArray arrPrivilege;
	// 得到操作系统版本	
	OSVERSIONINFO version;
	memset(&version, 0, sizeof(version));   
	version.dwOSVersionInfoSize = sizeof(version);   

	BOOL b = ::GetVersionEx(&version);
	if(version.dwMajorVersion < 5)
	{
		return TRUE;
	}
	else if(version.dwMajorVersion == 5)
	{
		// XP Administrator和PowerUser权限
		arrPrivilege.Add("Administrators");
		arrPrivilege.Add("Power Users");
	}
	else
	{
		// Vista Administrator权限
		arrPrivilege.Add("Administrators");
	}
	
	// 得到用户权限
	LPBYTE lpBuf = NULL;   
	DWORD dwEntriesRead = 0, dwTotalEntries = 0;   
	NET_API_STATUS nasRet = 0;      
	
	nasRet = NetUserGetLocalGroups(NULL, szUser, 0, LG_INCLUDE_INDIRECT,   
		&lpBuf, MAX_PREFERRED_LENGTH, &dwEntriesRead, &dwTotalEntries);   
	if(NERR_Success == nasRet || ERROR_MORE_DATA == nasRet)   
	{   
		LPLOCALGROUP_USERS_INFO_0 lpLui = (LPLOCALGROUP_USERS_INFO_0)lpBuf;   
		for(DWORD dwIdx = 0; dwIdx < dwEntriesRead; dwIdx++, lpLui++)   
		{   
			// 本地group  
			CString strGroup = lpLui->lgrui0_name; 
			int nSize = arrPrivilege.GetSize();
			for(int i = 0; i < nSize; i++)
			{
				if(arrPrivilege.ElementAt(i) == strGroup)
				{
					NetApiBufferFree(lpBuf);
					return TRUE;
				}
			}// for(			
		}// for(   
		NetApiBufferFree(lpBuf);     
	}  
	else
	{
		return TRUE;
	}
	return FALSE;
}

// 得到有权限的用户
void CPrivilegeAdjust::GetPrivilegeUser(CStringArray& arrUser)
{
	// 得到所有用户
	ULONG lIndex = 0;
	ULONG lIndex2 = 0;
	ULONG lRetEntries = 0;
	NET_DISPLAY_USER* pnetUsers;
	NET_API_STATUS netStatus;
	do 
	{
		// Because of the potentially many users on a system, this function
		netStatus = NetQueryDisplayInformation(NULL, 1, lIndex, 20000,
			1024, &lRetEntries, (PVOID*) &pnetUsers);
		if((netStatus != ERROR_MORE_DATA) && (netStatus != NERR_Success)) 
		{
			break;
		}
		
		for(lIndex2 = 0; lIndex2 < lRetEntries; lIndex2++) 
		{
			DWORD dwFlags = pnetUsers[lIndex2].usri1_flags;
			if((dwFlags & UF_ACCOUNTDISABLE) != UF_ACCOUNTDISABLE &&  (dwFlags & UF_LOCKOUT) != UF_LOCKOUT)
			{
				if(IsHasPrivilege(pnetUsers[lIndex2].usri1_name) == TRUE)
				{
					CString strUser = pnetUsers[lIndex2].usri1_name;
					arrUser.Add(strUser);
				}//
			}
		}// for		
		// Start enumeration where we left off
		lIndex = pnetUsers[lIndex2 - 1].usri1_next_index;
		// Free the buffer
		NetApiBufferFree(pnetUsers);
   }while (netStatus == ERROR_MORE_DATA);
}

// 提升用户权限
BOOL CPrivilegeAdjust::SetThreadPrivilege(CString& strUser, CString& strPswd)
{
	// 枚举当前用户
	HANDLE hToken = NULL;
	if(LogonUser(strUser.GetBuffer(0), NULL, strPswd.GetBuffer(0), LOGON32_LOGON_INTERACTIVE, LOGON32_PROVIDER_DEFAULT, &hToken) == FALSE)
	{
		return FALSE;
	}
	BOOL bRet = ImpersonateLoggedOnUser(hToken);
	CloseHandle(hToken);
	return bRet;
}

// 得到和保存用户权限
BOOL CPrivilegeAdjust::GetPrivilegeInfo(CString& strUser, CString& strPswd)
{
	// 从注册表读入
	HKEY hkey = NULL;
	CString strKey = "Software\\Infobird\\ICServingAgentClient\\privilege";
	if(RegOpenKeyEx(HKEY_CURRENT_USER, strKey, 0, KEY_ALL_ACCESS, &hkey) != ERROR_SUCCESS)
		return FALSE;

	char szData[MAX_PATH] = "\0";
	DWORD lDataLen = MAX_PATH;
	DWORD dwType = REG_SZ;
	if(RegQueryValueEx(hkey, "User", NULL, &dwType, (BYTE*)szData, &lDataLen) != ERROR_SUCCESS)
	{
		RegCloseKey(hkey);
		return FALSE;
	}
	strUser = szData;
	// 密码
	if(RegQueryValueEx(hkey, "Pswd", NULL, &dwType, (BYTE*)szData, &lDataLen) != ERROR_SUCCESS)
	{
		RegCloseKey(hkey);
		return FALSE;
	}
	strPswd = szData;
	RegCloseKey(hkey);
	return TRUE;	
}

BOOL CPrivilegeAdjust::SavePrivilegeInfo(CString& strUser, CString& strPswd)
{
	// 写入注册表
	HKEY hkey = NULL;
	CString strKey = "Software\\Infobird\\ICServingAgentClient\\privilege";
	
	if(RegOpenKeyEx(HKEY_CURRENT_USER, strKey, 0, KEY_ALL_ACCESS, &hkey) != ERROR_SUCCESS)
	{
		if(RegCreateKey(HKEY_CURRENT_USER, strKey, &hkey) != ERROR_SUCCESS)
		{
			return FALSE;
		}
	}
	// 修改
	BOOL b = RegSetValueEx(hkey, "User", NULL, REG_SZ, (BYTE*)strUser.GetBuffer(0), strUser.GetLength());
	b = RegSetValueEx(hkey, "Pswd", NULL, REG_SZ, (BYTE*)strPswd.GetBuffer(0), strPswd.GetLength());
	RegCloseKey(hkey);
	return TRUE;
}

BOOL CPrivilegeAdjust::AdjustPrivilege()
{
	if(IsHasPrivilege() == TRUE)
		return TRUE;
	// 得到用户名和密码
	CString strUser, strPswd;
	GetPrivilegeInfo(strUser, strPswd);
	if(strUser.IsEmpty() == FALSE && SetThreadPrivilege(strUser, strPswd) == TRUE)
	{
		return TRUE;
	}
	// 得到用户
	CStringArray arrUser;
	GetPrivilegeUser(arrUser);
	if(arrUser.GetSize() == 0)
	{
		return FALSE;
	}

	// 读取配置文件，确认是否有本地帐号和密码
	CEnvironment& env = CEnvironment::Instance();
	CString strIniFile = GetDataFilesPath() + "\\Config.ini";
	env.LoadEnvironmentFromFile(strIniFile);
	strUser = env.m_strUser.c_str();
	strPswd = env.m_strPwd.c_str();
	if ( strUser.IsEmpty() && strPswd.IsEmpty() )
	{
		// 
		CPrivilegeDlg dlg;
		dlg.m_arrPrivUser.Copy(arrUser);
		while(dlg.DoModal() == IDOK)
		{
			if(SetThreadPrivilege(dlg.m_strUserName, dlg.m_strPassword) == FALSE)
			{
				_MyMsgBox("配置", "提升用户权限失败", MB_OK);
				continue;
			}
			SavePrivilegeInfo(dlg.m_strUserName, dlg.m_strPassword);
			
			env.m_strUser = dlg.m_strUserName;
			env.m_strPwd = dlg.m_strPassword;

			env.SaveEnvironmentToFile(strIniFile);
			((CMainFrame *)AfxGetMainWnd())->m_pLoginDlg->m_AgentPanelOcx.ActionUpdateSettings();
			return TRUE;
		}
	}
	else
	{
		if(SetThreadPrivilege(strUser, strPswd) == FALSE)
		{
			_MyMsgBox("配置", "提升用户权限失败", MB_OK);
			return FALSE;
		}
		SavePrivilegeInfo(strUser, strPswd);
		return TRUE;
	}	

	return  FALSE;
}
