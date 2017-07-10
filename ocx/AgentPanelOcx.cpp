// AgentPanelOcx.cpp : Implementation of CAgentPanelOcxApp and DLL registration.

#include "stdafx.h"
#include "AgentPanelOcx.h"

#include "AgentPanelOcxCtl.h"
#include <winsock.h>
#include <objsafe.h>
#include "cathelp.h"
#include "log.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CAgentPanelOcxApp NEAR theApp;
const GUID CDECL BASED_CODE _tlid =
		{ 0x2b831ceb, 0xd284, 0x4587, { 0x87, 0xdc, 0xc, 0x7f, 0x1b, 0x3c, 0x9, 0xfe } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;
CString g_sAutoTransferNum = "";
BOOL g_bIsSuper = FALSE;
BOOL g_bIsMasterSuper = FALSE;
CString g_strCorp = "";
CString g_strDepartment = "";
CString g_strManagerID = "";
CString g_strAccount = "";
short g_iClientState = 0;
CWnd *g_pMainFrame = NULL;
int g_iSuperAgentType = 0;
CString g_strLogFilePath = "";
CString g_strLogFilePathLocal = "";
////////////////////////////////////////////////////////////////////////////
// CAgentPanelOcxApp::InitInstance - DLL initialization

BOOL CAgentPanelOcxApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();
	if (bInit)
	{
		// TODO: Add your own module initialization code here.
		CTime timeNow = CTime::GetCurrentTime();
		CString strLogDate;
		strLogDate.Format("%s\\log\\%d-%02d-%02d\\", GetDataFilesPath(), timeNow.GetYear(), timeNow.GetMonth(), timeNow.GetDay());
		g_strLogFilePath = strLogDate;
		strLogDate.Format("%s\\log\\%d-%02d-%02d\\", GetMoudlePath(), timeNow.GetYear(), timeNow.GetMonth(), timeNow.GetDay());
		g_strLogFilePathLocal = strLogDate;
	
		// sock初始化
		WSADATA wsaData;	
		WSAStartup(MAKEWORD(2, 2), &wsaData);		
	}
	
	return bInit;
}


////////////////////////////////////////////////////////////////////////////
// CAgentPanelOcxApp::ExitInstance - DLL termination

int CAgentPanelOcxApp::ExitInstance()
{
	// TODO: Add your own module termination code here.
	return COleControlModule::ExitInstance();
}


/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
	HRESULT hr = NOERROR;
	AFX_MANAGE_STATE(_afxModuleAddrThis);
	
	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);
	
	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);
	
	return hr;
}


/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
	HRESULT hr = NOERROR;
	
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);
	
	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);
	
	return hr;
}
