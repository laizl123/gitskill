// CheckUpdate.h: interface for the CCheckUpdate class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHECKUPDATE_H__B63C4DB7_547E_4423_9156_0CAE799B50B2__INCLUDED_)
#define AFX_CHECKUPDATE_H__B63C4DB7_547E_4423_9156_0CAE799B50B2__INCLUDED_

#include "IBInternetSession.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define CHECK_NEED_UPDATE		0x01
#define CHECK_NOT_UPDATE		0x02
#define MUST_NEED_UPDATE		0x03
#define CHECK_ERROR				0xFF


#define WM_CHECK_VERSION_STEP	WM_USER+932

#define CHECK_NEW_VERSION_START	0x01
#define CHECK_NEW_VERSION_END	0x02


typedef struct tagDISCOUPDATE{
	int nUpdateType;
	LPSTR szWhatsnew;
	LPSTR szPatchFile;
	bool bClearRegistry;
}DISCOUPDATE, *lpDISCOUPDATE;

class CCheckUpdate  
{
public:
	CCheckUpdate();
	virtual ~CCheckUpdate();
public:
	static CString GetProductVersion(HMODULE hModule=NULL, CString sNode="ProductVersion");
	static UINT CheckNewVision(CString sVer="",CString sFileName="");
	static UINT CheckNewVersion(CString sVer, lpDISCOUPDATE pDiscoupdate, typeStatusCallBack pfc=NULL, HWND hWnd=NULL);
	static CString GetNeedUpdateFileList(CString sVer="");
public:
	static CString GetFileVersion(CString sFileName="");
	static CString GetProductTitle();
	static bool IsNewVersion(string checkedVersion, string standardVersion);
	static bool GetWhatsNew(LPSTR szWhatNews, int iMaxLen, typeStatusCallBack pfc=NULL , HWND hWnd=NULL);
	static int HttpRequest(LPCTSTR szHost, UINT nPort, LPCTSTR szRequestFile, LPCTSTR szArgument, CString& sResult, typeStatusCallBack pfc=NULL, HWND hWnd=NULL);

	CString m_sCurrentProductVer;
	int nTerminate; 
	int nDownloaded;
	
};

#endif // !defined(AFX_CHECKUPDATE_H__B63C4DB7_547E_4423_9156_0CAE799B50B2__INCLUDED_)
