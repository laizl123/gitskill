// CheckUpdate.cpp: implementation of the CCheckUpdate class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CheckUpdate.h"
#include <afxinet.h>
#include "resource.h"
#include "Spliter.h"
#include "Log.h"
#include "Environment.h"
extern CString g_strLogFilePath;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define DOWNLOAD_BUF_SIZE 512


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCheckUpdate::CCheckUpdate()
{
	nTerminate = 0; 
	nDownloaded = 0;
	m_sCurrentProductVer = GetProductVersion();
}

CCheckUpdate::~CCheckUpdate()
{
	
}

CString CCheckUpdate::GetNeedUpdateFileList(CString sVer)
{
	CString sArgumentsString;
	if (sVer == "") 
		sArgumentsString.Format("Action=Update&Ver=%s",GetProductVersion());
	else
		sArgumentsString.Format("Action=Update&Ver=%s",sVer);
	
	CString strResult("");
	
	CInternetSession iSession("use post",1,INTERNET_OPEN_TYPE_PRECONFIG);
	//	iSession.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT,0);
	CHttpFile* pFile= NULL;
	CHttpConnection * pConnection= NULL;
	try{
		pConnection= iSession.GetHttpConnection("www.infobird.net",(INTERNET_PORT)80,NULL,NULL);
		if(pConnection==NULL)
			return "";
		
		pFile=pConnection->OpenRequest(
			CHttpConnection::HTTP_VERB_POST,
			"update/update.dll",
			NULL,1,NULL,NULL,
			INTERNET_FLAG_EXISTING_CONNECT|INTERNET_FLAG_TRANSFER_ASCII|INTERNET_FLAG_RELOAD|INTERNET_FLAG_DONT_CACHE);
		if(pFile==NULL) 
		{
			pConnection->Close();
			delete pConnection;
			return "";
		}
		
		CString strHeaders=_T("Accept: */*\r\n"
			"Content-Type:"
			"application/x-www-form-urlencoded"
			"\r\n");
		if(pFile->SendRequest(strHeaders,(LPVOID)sArgumentsString.LockBuffer(),sArgumentsString.GetLength()))
		{
			CString strtemp;			
			while(pFile->ReadString(strtemp))
				strResult+=strtemp;			
		}
		sArgumentsString.UnlockBuffer();
		
		pFile->Close();
		delete pFile;
		pFile= NULL;
		
		pConnection->Close();
		delete pConnection;
		pConnection= NULL;
		
		iSession.Close();
	}
	catch(...)
	{
		if (pConnection)
		{
			pConnection->Close();
			delete pConnection;
		}
		if (pFile)
		{
			pFile->Close();
			delete pFile;
		}
		return "";
	}
	if (strResult.Find("<!DOCTYPE HTML",0) != -1) 
		return "";
	
	return strResult;
}

int CCheckUpdate::HttpRequest(LPCTSTR szHost, UINT nPort, LPCTSTR szRequestFile, 
							  LPCTSTR szArgument, CString& sResult, 
							  typeStatusCallBack pfc, HWND hWnd)
{
	CIBInternetSession iSession("ICServingAgentClinet",1,INTERNET_OPEN_TYPE_PRECONFIG);
	if(pfc)
	{
		iSession.EnableStatusCallback();
		iSession.SetStatusCallBackFunc(pfc);
	}
	CHttpFile* pFile= NULL;
	CHttpConnection * pConnection= NULL;
	//	iSession.OnStatusCallback()
	
	CString tmpResult;
	
	try{
		pConnection= iSession.GetHttpConnection(szHost,(INTERNET_PORT)nPort,NULL,NULL);
		if(pConnection==NULL)
			return -1;
		pFile=pConnection->OpenRequest(
			CHttpConnection::HTTP_VERB_POST,
			szRequestFile,
			NULL,1,NULL,NULL,
			INTERNET_FLAG_EXISTING_CONNECT|INTERNET_FLAG_TRANSFER_ASCII|INTERNET_FLAG_RELOAD|INTERNET_FLAG_DONT_CACHE);
		if(pFile==NULL) 
		{
			pConnection->Close();
			delete pConnection;
			return -1;
		}
		
		CString strHeaders=_T("Accept: */*\r\n"
			"Content-Type:"
			"application/x-www-form-urlencoded"
			"\r\n");
		if(pFile->SendRequest(strHeaders,(LPVOID)szArgument,lstrlen(szArgument)))
		{
			CHAR strtemp[1024];
			memset(strtemp,0,1024);
			while(pFile->ReadString(strtemp,1024))
				tmpResult+=strtemp;			
		}
		
		pFile->Close();
		delete pFile;
		pFile= NULL;
		
		pConnection->Close();
		delete pConnection;
		pConnection= NULL;
		
		iSession.Close();
	}
	catch(...)
	{
		if (pConnection)
		{
			pConnection->Close();
			delete pConnection;
		}
		if (pFile)
		{
			pFile->Close();
			delete pFile;
		}
		return CHECK_ERROR;
	}
	sResult = tmpResult;
	return 1;
}

bool CCheckUpdate::GetWhatsNew(LPSTR szWhatNews, int iMaxLen,typeStatusCallBack pfc, HWND hWnd)
{
	////   http://update.infobird.com:8080/Disco_Update_Host/updateFiles/whatnew.txt
	CString strResult("");
	CString sHost = ConvertHostName2IP(DEFUPDATEURL);
	CString sRequestFile("Disco_Update_Host/updateFiles/whatnew.txt");
	CString sArguments("");
	UINT nPort = 8080;
	if(CCheckUpdate::HttpRequest(sHost,nPort,sRequestFile,sArguments,strResult,pfc) == 1)
	{
		CLog::DirectWriteFile((string)g_strLogFilePath, "Infobird_GUI.log", "CCheckUpdate::GetWhatsNew strResult=" + (string)strResult);	
		if (strResult == "" || strResult.GetLength() >= 1000)
		{
			strcpy(szWhatNews,"1.增强启通宝客户端稳定性");
			return true;
		}

		strcpy(szWhatNews,strResult.LockBuffer());
		strResult.UnlockBuffer();
	}
	else
	{
		return false;
	}
	return true;
}

UINT CCheckUpdate::CheckNewVersion(CString sVer, lpDISCOUPDATE pDiscoupdate,typeStatusCallBack pfc, HWND hWnd)
{
	/////  http://update.infobird.com:8080/Disco_Update_Host/Update?r=update
	if(!pDiscoupdate)
		return CHECK_ERROR;
	
	if(sVer=="")
		sVer = CCheckUpdate::GetProductVersion();
	
	CString strResult("");
	CString sRequestFile("Disco_Update_Host/Update");
	CString sArguments("r=update");
	UINT nPort = 8080;
	int nUpdateType = CHECK_NOT_UPDATE;
	if(CCheckUpdate::HttpRequest(ConvertHostName2IP(DEFUPDATEURL),nPort,sRequestFile,sArguments,strResult ,pfc) == 1)
	{
		CLog::DirectWriteFile((string)g_strLogFilePath, "Infobird_GUI.log", "CCheckUpdate::CheckNewVersion strResult=" + (string)strResult);	

		CSpliter strSp(strResult.LockBuffer(),"|",":");
		CString x(strSp[3][1].c_str());
		lstrcpy(pDiscoupdate->szPatchFile, strSp[3][1].c_str());
		nUpdateType = strSp[0][1] == "" ? CHECK_ERROR : 
		(IsNewVersion(strSp[0][1],string(sVer))? 
			(atoi(strSp[1][1].c_str())?MUST_NEED_UPDATE:CHECK_NEED_UPDATE) : 
		CHECK_NOT_UPDATE	);
		
		if(strSp.GetSize() >= 5)
			pDiscoupdate->bClearRegistry = (atoi(strSp[4][1].c_str())) ? true:false;
		else
			pDiscoupdate->bClearRegistry = false;
	}
	else
		nUpdateType = CHECK_ERROR;
	
	if(nUpdateType == MUST_NEED_UPDATE || nUpdateType== CHECK_NEED_UPDATE)
		CCheckUpdate::GetWhatsNew(pDiscoupdate->szWhatsnew, lstrlen(pDiscoupdate->szWhatsnew));
	pDiscoupdate->nUpdateType = nUpdateType;
	
	return nUpdateType;
}

bool CCheckUpdate::IsNewVersion(string checkedVersion, string standardVersion)
{
	CSpliter s1( checkedVersion, "." );
	CSpliter s2( standardVersion, "." );
	int i1 = 0, i2 = 0;
	while ( s1[i1] != "" )
	{
		i1++;
	}
	while ( s2[i2] != "" )
	{
		i2++;
	}
	
	if ( i1 > i2 )
	{
		return true;
	}
	else if ( i1 < i2 )
	{
		return false;
	}
	
	for ( int i = 0; i < i1; i++ )
	{
		if ( atoi( s1[i].c_str() ) > atoi( s2[i].c_str() ) )
		{
			return true;
		}
		else if ( atoi( s1[i].c_str() ) < atoi( s2[i].c_str() ) )
		{
			return false;
		}
	}
	
	return false;
}



UINT CCheckUpdate::CheckNewVision(CString sVer,CString sFileName)
{
	CString sArgumentsString;
	CString sFileArgument("");
	if (sFileName != "") 
		sFileArgument.Format("&FileName=%s",sFileName);
	
	if (sVer == "") 
		sArgumentsString.Format("Action=Check&Ver=%s%s",GetProductVersion(),sFileArgument);
	else
		sArgumentsString.Format("Action=Check&Ver=%s%s",sVer,sFileArgument);
	
	CString strResult("");
	CInternetSession iSession("use post",1,INTERNET_OPEN_TYPE_PRECONFIG);
	//	iSession.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT,0);
	CHttpFile* pFile= NULL;
	CHttpConnection * pConnection= NULL;
	try{
		//		pConnection= iSession.GetHttpConnection("192.168.2.120",(INTERNET_PORT)80,NULL,NULL);
		pConnection= iSession.GetHttpConnection("www.infobird.net",(INTERNET_PORT)80,NULL,NULL);
		if(pConnection==NULL)
			return CHECK_ERROR;
		
		pFile=pConnection->OpenRequest(
			CHttpConnection::HTTP_VERB_POST,
			"update/update.dll",
			NULL,1,NULL,NULL,
			INTERNET_FLAG_EXISTING_CONNECT|INTERNET_FLAG_TRANSFER_ASCII|INTERNET_FLAG_RELOAD|INTERNET_FLAG_DONT_CACHE);
		if(pFile==NULL) 
		{
			pConnection->Close();
			delete pConnection;
			return CHECK_ERROR;
		}
		
		CString strHeaders=_T("Accept: */*\r\n"
			"Content-Type:"
			"application/x-www-form-urlencoded"
			"\r\n");
		if(pFile->SendRequest(strHeaders,(LPVOID)sArgumentsString.LockBuffer(),sArgumentsString.GetLength()))
		{
			CString strtemp;			
			while(pFile->ReadString(strtemp))
				strResult+=strtemp;
			
		}
		sArgumentsString.UnlockBuffer();
		
		pFile->Close();
		delete pFile;
		pFile= NULL;
		
		pConnection->Close();
		delete pConnection;
		pConnection= NULL;
		
		iSession.Close();
	}
	catch(...)
	{
		if (pConnection)
		{
			pConnection->Close();
			delete pConnection;
		}
		if (pFile)
		{
			pFile->Close();
			delete pFile;
		}
		return CHECK_ERROR;
	}
	
	if(strResult.GetLength() == 0 || strResult.GetLength() > 3)
		return CHECK_ERROR;
	
    UINT iResult = atoi(strResult);
	
	if (iResult == CHECK_NEED_UPDATE) 
		return CHECK_NEED_UPDATE;
	else if(iResult == MUST_NEED_UPDATE) 
		return MUST_NEED_UPDATE;
	else if(iResult == CHECK_NOT_UPDATE) 
		return CHECK_NOT_UPDATE;
	
	return CHECK_NOT_UPDATE;
}

CString CCheckUpdate::GetProductVersion(HMODULE hModule, CString sNode)
{
	HMODULE hLib = NULL;
	if (hModule == NULL) 
		hLib = AfxGetResourceHandle();
	else
		hLib = hModule;
	
	HRSRC hVersion = FindResource( hLib, 
		MAKEINTRESOURCE(VS_VERSION_INFO), RT_VERSION );
	CString csRet;
	CString csEntry = sNode;
	if (hVersion != NULL)
	{
		HGLOBAL hGlobal = LoadResource( hLib, hVersion ); 
		if ( hGlobal != NULL)  
		{  
			
			LPVOID versionInfo  = LockResource(hGlobal);  
			if (versionInfo != NULL)
			{
				DWORD vLen,langD;
				BOOL retVal;    
				
				LPVOID retbuf=NULL;
				
				static char fileEntry[256];
				
				sprintf(fileEntry,_T("\\VarFileInfo\\Translation"));
				retVal = VerQueryValue(versionInfo,fileEntry,&retbuf,(UINT *)&vLen);
				if (retVal && vLen==4) 
				{
					memcpy(&langD,retbuf,4);            
					sprintf(fileEntry, _T("\\StringFileInfo\\%02X%02X%02X%02X\\%s"),
						(langD & 0xff00)>>8,langD & 0xff,(langD & 0xff000000)>>24, 
						(langD & 0xff0000)>>16, csEntry);            
				}
				else 
					sprintf(fileEntry, _T("\\StringFileInfo\\%04X04B0\\%s"), 
					GetUserDefaultLangID(), csEntry);
				
				if (VerQueryValue(versionInfo,fileEntry,&retbuf,(UINT *)&vLen)) 
					csRet = (char*)retbuf;
			}
		}
		
		UnlockResource( hGlobal );  
		FreeResource( hGlobal );  
	}
	csRet.Replace(_T(","),_T("."));
	csRet.Replace(_T(" "),_T(""));
	return csRet;
}


CString CCheckUpdate::GetProductTitle()
{
	HMODULE hLib = AfxGetResourceHandle();//((CMediaAgentDemoApp*)AfxGetApp())->GetDefaultHinstance();
	TCHAR szTitle[MAX_PATH],szTitleVer[MAX_PATH];
	LoadString(AfxGetResourceHandle(),IDS_TITLE,szTitle,MAX_PATH);
	LoadString(hLib,IDS_VERSION,szTitleVer,MAX_PATH);
	CString sResult;
	sResult.Format(_T("%s%s"),szTitle,szTitleVer);
	return sResult;
}


CString CCheckUpdate::GetFileVersion(CString sFileName)
{
	HMODULE hMod = NULL;
	BOOL bNeedFree = FALSE;
	if(sFileName != "")
	{
		hMod = ::LoadLibrary(sFileName);
		bNeedFree = TRUE;
	}
	else 
		hMod  = AfxGetResourceHandle();
	if(hMod == NULL)
		return "";
	CString sVer = GetProductVersion(hMod,"FileVersion");
	if(bNeedFree)
		FreeLibrary(hMod);
	return sVer;
}
