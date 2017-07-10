#include "stdafx.h"
#include "singleinstancelock.h"

#include "Resources.h"
#include "DynamicResource.h"

extern PRODUCT_VER_INFO g_tagProductVerInfo;

SingleInstanceLock::SingleInstanceLock()
{
	// Set our default values
	m_hMutex = NULL;
}

SingleInstanceLock::~SingleInstanceLock()
{
	if ( m_hMutex != NULL ) {
		ReleaseMutex( m_hMutex );
	}
}

BOOL SingleInstanceLock::Create( LPCSTR szApplicationLockName, BOOL bUseClassName, 
								LPCSTR szWindowsName,UINT iShowMode )
{
	// Add the word 'Class' to the end
	m_strClassName = szApplicationLockName;

	// Create the mutex
	m_hMutex = CreateMutex( NULL, FALSE, m_strClassName );
	// Check for errors
	if ( GetLastError() == ERROR_ALREADY_EXISTS ) {
		// Reset our mutext handle (just in case)
		m_hMutex = NULL;
		// The mutex already exists, which means an instance is already
		// running. Find the app and pop it up
		LPCTSTR szClassName= NULL;
		if (bUseClassName)
		{
			szClassName= m_strClassName;
		}

//找到了已经存在的事例也不主动将其激活
//		HWND hWnd = FindWindowEx( NULL, NULL, szClassName, szWindowsName );
//		if ( hWnd != NULL ) {
//			ShowWindow( hWnd, iShowMode );
//			BringWindowToTop( hWnd );
//			SetForegroundWindow( hWnd );
//		}

		// Return failure
		return FALSE;
	}

	// Register the unique window class name so others can find it.
	WNDCLASS wndcls;    memset(&wndcls, 0, sizeof(WNDCLASS));
	wndcls.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
	wndcls.lpfnWndProc = AfxWndProc;
	wndcls.hInstance = AfxGetInstanceHandle();
	wndcls.hIcon = NULL;
	wndcls.hCursor = LoadCursor( wndcls.hInstance, IDC_ARROW );
	wndcls.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
	wndcls.lpszMenuName = NULL;//You may need to fix this
	wndcls.lpszClassName = m_strClassName; // my class name
	// Register name, exit if it fails
	if(!AfxRegisterClass(&wndcls)) 
	{
		CString sTitle = CResources::GetTextResource(CDynamicResource::s_TextTipTitle);
		if(sTitle == "")
		{
			if (g_tagProductVerInfo.nVersionType & VerType_IPCC)
				sTitle = "提示--讯鸟座席端";
			else
				sTitle = "提示--启通宝";
		}

		_MyMsgBox(sTitle, _T("无法注册窗口类!"), MB_OK);
		
		return FALSE;
	}

	// Return success
	return TRUE;
}

