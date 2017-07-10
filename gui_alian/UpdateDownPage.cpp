// UpdateDownPage.cpp : implementation file
//

#include "stdafx.h"
#include "Environment.h"
#include "ICServingAgentClient.h"
#include "UpdateDownPage.h"
#include "FilePack.h"
#include "GlobalOperation.h"
#include "iniFile.h"
#include "UpdatePropertySheet.h"
#include "Resources.h"
#include "DynamicResource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUpdateDownPage property page
const char* szTempPathExp = "%s\\Infobird\\Update";
string szTempPath = CreateTempPath();

string CreateTempPath()
{
	char szPath[MAX_PATH];
	GetTempPath(MAX_PATH,szPath);
	CString sExtractPath;
	sExtractPath.Format(szTempPathExp,szPath);
	CreateMultipleLevelDirectory(string(sExtractPath));
	return string(sExtractPath);
}

DWORD CreateUpdateProcess(LPSTR tcsParam)
{

	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory( &si, sizeof(si) );
	si.cb          = sizeof(si);
	si.dwFlags     = STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_HIDE;
	ZeroMemory( &pi , sizeof(pi) );

//	_stprintf(tcsParam, _T), tcsCmd, tcsExename);
	if(!CreateProcess(NULL,
		tcsParam,
		NULL,
		NULL,
		FALSE,
		CREATE_SUSPENDED,
		NULL,
		NULL,
		&si,
		&pi))
	{
		return GetLastError();
	}
	
	// heigthen priority of the current process
	SetPriorityClass(GetCurrentProcess(),
			REALTIME_PRIORITY_CLASS);
		SetThreadPriority(GetCurrentThread(),
			THREAD_PRIORITY_TIME_CRITICAL);    
	
	// set file attribute to normal 
	//SetFileAttributes(tcsExename, FILE_ATTRIBUTE_NORMAL);
	
	// depress priority of command process, then start it
	SetPriorityClass(pi.hProcess, IDLE_PRIORITY_CLASS);
	ResumeThread(pi.hThread);

	return 0;
}

BOOL RunUpdate(SHELLEXECUTEINFO* pSei)
{
	
	TCHAR szModule [MAX_PATH],
		szComspec[MAX_PATH];
	
	// get file path names:
	if((GetModuleFileName(0,szModule,MAX_PATH)!=0) &&
		(GetShortPathName(szModule,szModule,MAX_PATH)!=0) &&
		(GetEnvironmentVariable("COMSPEC",szComspec,MAX_PATH)!=0))
	{	
		// increase resource allocation to program
		SetPriorityClass(GetCurrentProcess(),
			REALTIME_PRIORITY_CLASS);
		SetThreadPriority(GetCurrentThread(),
			THREAD_PRIORITY_TIME_CRITICAL);
		
		// invoke command shell
		if(ShellExecuteEx(pSei)) 
		{
			// suppress command shell process until program exits
			HANDLE hd = GetCurrentProcess();
			BOOL xxx = SetPriorityClass(pSei->hProcess,IDLE_PRIORITY_CLASS);
			xxx = SetProcessPriorityBoost(pSei->hProcess,TRUE);
			
			// notify explorer shell of deletion
			SHChangeNotify(SHCNE_DELETE,SHCNF_PATH,szModule,0);
			return TRUE;
		}
		else // if error, normalize allocation
		{
			SetPriorityClass(GetCurrentProcess(),
				NORMAL_PRIORITY_CLASS);
			SetThreadPriority(GetCurrentThread(),
				THREAD_PRIORITY_NORMAL);
		}
	}
	
	return FALSE;
}




IMPLEMENT_DYNCREATE(CUpdateDownPage, CPropertyPage)

CUpdateDownPage::CUpdateDownPage() : CPropertyPage(CUpdateDownPage::IDD)
{
	//{{AFX_DATA_INIT(CUpdateDownPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_bForceUpdate = FALSE;
	m_pUpdateThread = NULL;
	m_iFullSize = 0;
	m_iCurrentSize = 0;

	m_sUpdateFilePack = "";
	m_bTerminateThread = TRUE;
	m_bClearReg = FALSE;
}

CUpdateDownPage::~CUpdateDownPage()
{
}

void CUpdateDownPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUpdateDownPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUpdateDownPage, CPropertyPage)
	//{{AFX_MSG_MAP(CUpdateDownPage)
	ON_MESSAGE(WM_GET_DOWN_INFO,OnGetDownInfo)
	ON_MESSAGE(WM_DOWNLOAD_FINISH,OnDownloadFinish)
	ON_MESSAGE(WM_DOWNLOAD_ERROR,OnDownloadError)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUpdateDownPage message handlers
BOOL CUpdateDownPage::OnSetActive() 
{
	HBITMAP bmBg = CResources::GetImageResource(CDynamicResource::s_ImageUpdateBg);
	if(bmBg != NULL)
	{
		CStatic* p =  (CStatic*)GetDlgItem(IDC_STATIC_BG);
		p->SetBitmap(bmBg);
	}

	CPropertySheet* pParent= (CPropertySheet*)GetParent();
	if(pParent)
	{		
		if(m_bForceUpdate)
		{			
			pParent->SetWizardButtons( PSWIZB_DISABLEDFINISH  );
			pParent->GetDlgItem(ID_WIZBACK)->ShowWindow(SW_HIDE);
			pParent->GetDlgItem(ID_WIZBACK)->EnableWindow(FALSE);
	//		pParent->GetDlgItem(IDCANCEL)->EnableWindow(FALSE);
			pParent->GetDlgItem(IDCANCEL)->SetWindowText("取消(&C)");
		}
		else
		{
			pParent->SetWizardButtons( PSWIZB_DISABLEDFINISH  );
		//	pParent->GetDlgItem(ID_WIZBACK)->ShowWindow(SW_SHOW);
		//	pParent->GetDlgItem(ID_WIZBACK)->EnableWindow();
		}
	}

	m_pUpdateThread = AfxBeginThread(CUpdateDownPage::ThreadDownSingleFile,this,THREAD_PRIORITY_NORMAL);
	SetTimer(Update_TimeOut_TimerID,10*1000,NULL);
	return CPropertyPage::OnSetActive();
}

UINT CUpdateDownPage::ThreadDownSingleFile(LPVOID pParam)
{
	UINT uRet = 0;
    CUpdateDownPage* lpthis = (CUpdateDownPage*)pParam;
	uRet = lpthis->func_Dwonload();
	return uRet;
}



UINT CUpdateDownPage::func_Dwonload()
{
	///// http://update.infobird.com:8080/Disco_Update_Host/updateFiles/Update.UPC.Cab
	CreateMultipleLevelDirectory(GetAppPath()+"update");
	m_sUpdateFilePack.Format("%supdate\\%s",GetAppPath().c_str(),m_sUpdateFileName);
	m_DownFile.m_wFileID = m_DownFile.GenFileID();
	m_DownFile.RegisterNotifyWindow(0,this->GetSafeHwnd(),WM_GET_DOWN_INFO);	//这里注册通知窗口和消息

	CString sHttpFile;
	sHttpFile.Format("http://%s:8080/Disco_Update_Host/updateFiles/%s", ConvertHostName2IP(DEFUPDATEURL), m_sUpdateFileName);
	int uRet  = m_DownFile.DownLoadFile(sHttpFile, m_sUpdateFilePack);
	if ( uRet == DOWNLOAD_FINISH )
		PostMessage(WM_DOWNLOAD_FINISH);
	else if(uRet == DOWNLOAD_ERROR)
		PostMessage(WM_DOWNLOAD_ERROR);
	
    return uRet;
}

LRESULT CUpdateDownPage::OnDownloadError(WPARAM wParam,LPARAM lParam)
{
	if(MessageBox("无法下载更新包！！\r\n请检查网络是否正常！\r\n是否重试更新？（是/否）", 
		"自动更新错误", MB_YESNO|MB_ICONERROR) == IDYES)
	{
		m_DownFile.DownContinue();
		ExitThread();
		if(!m_pUpdateThread)
			m_pUpdateThread = AfxBeginThread(CUpdateDownPage::ThreadDownSingleFile,
				this,THREAD_PRIORITY_NORMAL);
		return 1;
	}

	::SendMessage(GetParent()->GetSafeHwnd(), WM_DESTROYWIZARD,WIZDOWNLOAD_ERROR,0);
	return 0;
}

LRESULT CUpdateDownPage::OnGetDownInfo(WPARAM wParam,LPARAM lParam)
{
	DWORD dwMsg = LOWORD(wParam);
	switch(dwMsg) {
	case DOWNLOAD_CONNECT_STEP_1:
	case DOWNLOAD_CONNECT_STEP_2:
	case DOWNLOAD_CONNECT_STEP_3:
		{
			m_bTerminateThread = TRUE;
		}
		break;
	case DOWNLOAD_CONNECT_STEP_4:
		{
			m_bTerminateThread = FALSE;
			KillTimer(Update_TimeOut_TimerID);
		}
		break;
	case NOTIFY_MSG_LOW_WPARAM_FULLSIZE:
		{
			m_iFullSize = lParam;
			CProgressCtrl* pProgress = (CProgressCtrl*)GetDlgItem(IDC_PROGRESS);
			pProgress->SetRange32(0,10000);
		}
		break;
	case NOTIFY_MSG_LOW_WPARAM_CURRENTSIZE:
		{
			m_iCurrentSize = lParam;
		}
		break;
	case NOTIFY_MSG_LOW_WPARAM_DOWNSIZE:
		{
			double iDownSize = m_iCurrentSize+lParam;
			CString sShowMsg;
			sShowMsg.Format(" 正在下载更新文件中...  %5d kb/%5d kb",int(iDownSize/1024),m_iFullSize/1024);
			SetDlgItemText(IDC_SHOW_MSG_BAR,sShowMsg);
			double percent;
			percent = m_iFullSize==0?0:(double)(iDownSize*100)/(double)m_iFullSize;
			CProgressCtrl* pProgress = (CProgressCtrl*)GetDlgItem(IDC_PROGRESS);
			sShowMsg.Format(" 下载进度：%3.0f%%",percent);
			CString iPercent;
			iPercent.Format("%0.2f",percent*100);
			pProgress->SetPos(::atoi(iPercent));
			SetDlgItemText(IDC_STATIC_SPEED,sShowMsg);
		}
		break;
	case NOTIFY_MSG_LOW_WPARAM_DOWNSPEED:
		{
			int iSpeed = lParam;
			CString sSpeed;
			sSpeed.Format(" 下载速率：%4d kb/sec",iSpeed);
			SetDlgItemText(IDC_STATIC_KBSEC,sSpeed);
		}
		break;
	case NOTIFY_MSG_WPARAM_DOWN_FINISH:
		{
			CString sShowMsg;
			sShowMsg.Format(" 准备更新中，请稍候...  ");
			SetDlgItemText(IDC_SHOW_MSG_BAR,sShowMsg);
			CPropertySheet* pParent= (CPropertySheet*)GetParent();
			if(pParent)
			{
				pParent->GetDlgItem(IDCANCEL)->EnableWindow(FALSE);
			}
		}
		break;
	default:
		break;
	}
	return 0;
}

LRESULT CUpdateDownPage::OnDownloadFinish(WPARAM wParam,LPARAM lParam)
{
	//释放文件到临时文件准备更新
	CUpdatePack pack;
	CString sIniFileName;
	if(!pack.LoadPack(m_sUpdateFilePack))
	{
		AfxMessageBox("读取更新包失败。\n更新失败");
		CPropertySheet* pParent= (CPropertySheet*)GetParent();
		pParent->SetWizardButtons( PSWIZB_FINISH  );
		return 0;
	}
	if(!pack.ExtractPack(szTempPath.c_str(),sIniFileName))
	{
		AfxMessageBox("打开更新包失败！！\n可能更新包不完整。\n更新失败");
		CPropertySheet* pParent= (CPropertySheet*)GetParent();
		pParent->SetWizardButtons( PSWIZB_FINISH  );
		return 0;
	}

	///释放完毕
	///更改INI文件
	CIniFile inifile;
	inifile.SetPath(string(sIniFileName));
	inifile.ReadFile();
	inifile.SetValueB("Update","regreset",m_bClearReg);
	inifile.WriteFile();

	CString sSourceFile,sTargerFile, sUpdateParam;
	sSourceFile.Format("%s\\Update.exe",szTempPath.c_str());
	sTargerFile.Format("%s\\Update.exe",GetAppPath().c_str());

	CFileFind ff;
	if(!ff.FindFile(sSourceFile))
	{
		AfxMessageBox("更新包不完整，更新失败");
		ff.Close();
		CPropertySheet* pParent= (CPropertySheet*)GetParent();
		pParent->SetWizardButtons( PSWIZB_FINISH  );
		return 0;
	}
	::CopyFileEx(sSourceFile,sTargerFile,NULL,NULL,FALSE,COPY_FILE_RESTARTABLE);

	CHAR szShortTempPath[MAX_PATH],szShortTargerPath[MAX_PATH];
	GetShortPathName(szTempPath.c_str(),szShortTempPath,MAX_PATH);
	GetShortPathName(GetAppPath().c_str(),szShortTargerPath,MAX_PATH); 
	//////////////////////////////////////////////////////////////////////////
	///   by dido     08/02/05
	sUpdateParam.Format(" Update %u %s %s", GetCurrentProcessId(), szShortTempPath, szShortTargerPath);
	HINSTANCE hResult = ShellExecute(NULL, NULL, sTargerFile, sUpdateParam.LockBuffer(), NULL, SW_SHOW);
	if (hResult < (HINSTANCE)32)
		AfxMessageBox("Running Update.exe error!");
	//////////////////////////////////////////////////////////////////////////
	
/*	SHELLEXECUTEINFO sei;
	sei.cbSize       = sizeof(sei);
	sei.hwnd         = 0;
	sei.lpVerb       = "Open";
	sei.lpFile       = sTargerFile;
	sei.lpParameters = sUpdateParam;
	sei.lpDirectory  = 0;
	sei.nShow        = SW_NORMAL;
	sei.fMask        = SEE_MASK_NOCLOSEPROCESS;
	RunUpdate(&sei);
*/
/*	
	TCHAR tcsExename[MAX_PATH];
	TCHAR tcsParam[MAX_PATH * 2];
	TCHAR tcsCmd[MAX_PATH];
	HANDLE hProcess = NULL;
	*/
	::SendMessage(GetParent()->GetSafeHwnd(), WM_DESTROYWIZARD,WIZDOWNLOAD_FINISH,0);
	return 0; 
}

BOOL CUpdateDownPage::OnKillActive() 
{
	m_DownFile.DownloadHalt();
	if(m_pUpdateThread)
	{
		if(WaitForSingleObject(m_pUpdateThread->m_hThread, 30000) == WAIT_TIMEOUT)
		{
			m_pUpdateThread->ExitInstance();
			m_pUpdateThread = NULL;
		}
	}

	return CPropertyPage::OnKillActive();
}
DWORD CUpdateDownPage::ExitThread()
{
	m_DownFile.DownloadHalt();
	if(m_pUpdateThread && m_pUpdateThread->m_hThread)
	{
		DWORD dwResult = WaitForSingleObject(m_pUpdateThread->m_hThread, 30000);
		if(dwResult == WAIT_TIMEOUT)
		{
			DWORD dwExitCode = m_pUpdateThread->ExitInstance();
			m_pUpdateThread = NULL;
			return dwExitCode;
		}
		m_pUpdateThread = NULL;
	}
	return 0;
}

DWORD CUpdateDownPage::SuspendThread()
{
	if(m_pUpdateThread && m_pUpdateThread->m_hThread)
		return m_pUpdateThread->SuspendThread();
	return 0xFFFFFFFF;
}

DWORD CUpdateDownPage::ResumeThread()
{
	if(m_pUpdateThread && m_pUpdateThread->m_hThread)
		return m_pUpdateThread->ResumeThread();
	return 0xFFFFFFFF;
}

void CUpdateDownPage::OnTimer(UINT nIDEvent) 
{
	if(Update_TimeOut_TimerID == nIDEvent)
	{
		if(m_pUpdateThread && m_bTerminateThread)
		{
			m_DownFile.DownloadHalt();
			TerminateThread(m_pUpdateThread->m_hThread, 5555);
			DWORD dwResult = WaitForSingleObject(m_pUpdateThread->m_hThread, 2000);
			if(dwResult == WAIT_TIMEOUT)
			{
				DWORD dwExitCode = m_pUpdateThread->ExitInstance();
				m_pUpdateThread = NULL;
			}
		}
		PostMessage(WM_DOWNLOAD_ERROR);
		KillTimer(Update_TimeOut_TimerID);
	}
	CPropertyPage::OnTimer(nIDEvent);
}