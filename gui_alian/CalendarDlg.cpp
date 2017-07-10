// CalendarDlg.cpp : implementation file
//

#include "stdafx.h"
#include "icservingagentclient.h"
#include "CalendarDlg.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CLocalInfoBasic g_localinfo;
extern CAgentStaticArchive g_AgentStatic;
extern CMainFrame *g_pMainFrame;
/////////////////////////////////////////////////////////////////////////////
// CCalendarDlg dialog
CCalendarDlg::CCalendarDlg(CWnd* pParent /*=NULL*/)
	: CBkDialog(CCalendarDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCalendarDlg)
		// NOTE: the ClassWizard will add member initialization here
	m_bUpdatedData = FALSE;
	//}}AFX_DATA_INIT
	m_brushBack.CreateSolidBrush(RGB(250, 250, 250));
}


void CCalendarDlg::DoDataExchange(CDataExchange* pDX)
{
	CBkDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCalendarDlg)
	DDX_Control(pDX, IDC_STATIC_PARK_COUNT, m_staticParkCount);
	DDX_Control(pDX, IDC_STATIC_OUTDIAL_COUNT, m_staticOutdialCount);
	DDX_Control(pDX, IDC_STATIC_AVG_PROCESS_TIMELENGTH, m_staticAvgProcessTimelength);
	DDX_Control(pDX, IDC_STATIC_AVG_CALL_TIMELENGTH, m_staticAvgCallTimelength);
//	DDX_Control(pDX, IDC_CALENDAR_NOW, m_calendarNow);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCalendarDlg, CBkDialog)
	//{{AFX_MSG_MAP(CCalendarDlg)
	ON_WM_NCHITTEST()
	ON_WM_CTLCOLOR()
	ON_MESSAGE(WM_UPDATE_TODAY_STATIC, OnUpdateTodayStatic)
	ON_NOTIFY(NM_CLICK, IDC_CALENDAR_NOW+88, OnClickCalend)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCalendarDlg message handlers

BOOL CCalendarDlg::OnInitDialog() 
{
	CBkDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetBitmap(IDB_BMP_BG);

	CRect rectCalend;
	GetDlgItem(IDC_CALENDAR_NOW)->GetWindowRect(rectCalend);
	ScreenToClient(rectCalend);

	m_calendarNow.Create(NULL, 
		NULL, 
		 WS_CHILD | WS_VISIBLE | FMC_NOHIGHLIGHTTODAY | FMC_NO3DBORDER, 
		rectCalend, 
		this, 
		IDC_CALENDAR_NOW+88);

	m_calendarNow.SetSpecialDaysColor(RGB(192,0,0));
	m_calendarNow.SetHighlightToday(TRUE);
	m_calendarNow.SetDaysFont("Tahoma", 9, false, false, false, RGB(0,0,0));
	m_calendarNow.SetDaysOfWeekFont("宋体", 9 , TRUE, FALSE, false, RGB(0,0,255));
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

UINT CCalendarDlg::OnNcHitTest(CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
//	return HTCAPTION;
	return CBkDialog::OnNcHitTest(point);
}

HBRUSH CCalendarDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CBkDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	HBRUSH hbrDlg;
	
	if(nCtlColor==CTLCOLOR_STATIC)   
	{   
		hbrDlg=(HBRUSH)m_brushBack.GetSafeHandle();   
		pDC->SetBkColor(RGB(250, 250, 250));   
		pDC->SetTextColor(RGB(1, 1, 1));   
		return hbrDlg;   
	}   		
	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}


void CCalendarDlg::OnOK(){}
void CCalendarDlg::OnCancel(){}

BEGIN_EVENTSINK_MAP(CCalendarDlg, CBkDialog)
    //{{AFX_EVENTSINK_MAP(CCalendarDlg)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CCalendarDlg::OnClickCalend(NMHDR* pNMHDR, LRESULT* pResult)
{
	CLD_NMHDR* pCLDNMHDR = (CLD_NMHDR*)pNMHDR;
	
 	SYSTEMTIME systime;
	GetSystemTime(&systime);

	SYSTEMTIME dtNow = pCLDNMHDR->dt;

	CString str;
	str.Format("%d-%02d-%02d", dtNow.wYear, dtNow.wMonth, dtNow.wDay);
	CString strR = g_pMainFrame->m_pLoginDlg->m_AgentPanelOcx.GetBriefStatisticInfo(str);
	UpdatetatisticInfo((string)strR);
}

void CCalendarDlg::UpdatetatisticInfo(string& str)
{
	if (str == "")
		return;
				
	int iStart = str.find("#.#", 0);
	g_AgentStatic.OutDialCount = atoi(str.substr(0, iStart).c_str());
	iStart += 3;
	int iEnd = str.find("#.#", iStart);
	g_AgentStatic.AnswerCount = atoi(str.substr(iStart, iEnd - iStart).c_str());
	iStart = iEnd + 3;
	iEnd = str.find("#.#", iStart);
	g_AgentStatic.TalkTime = atoi(str.substr(iStart, iEnd - iStart).c_str());
	iStart = iEnd + 3;
	iEnd = str.find("#.#", iStart);
	g_AgentStatic.ParkCount = atoi(str.substr(iStart, iEnd - iStart).c_str());
	iStart = iEnd + 3;
	iEnd = str.find("#.#", iStart);
	g_AgentStatic.ParkTime = atoi(str.substr(iStart, iEnd - iStart).c_str());
	iStart = iEnd + 3;
	iEnd = str.find("#.#", iStart);
	g_AgentStatic.ProcessCount = atoi(str.substr(iStart, iEnd - iStart).c_str());
	iStart = iEnd + 3;
	g_AgentStatic.ProcessTime = atoi(str.substr(iStart).c_str());
				
	CString strTemp;
	if ((g_AgentStatic.AnswerCount + g_AgentStatic.OutDialCount) == 0 || (g_AgentStatic.TalkTime == 0))
		strTemp = "平均通话时长：0分0秒";	
	else
	{
		int iAvgTalkTimeLength = g_AgentStatic.TalkTime / (g_AgentStatic.AnswerCount + g_AgentStatic.OutDialCount) + 1;
		int iMinutes = iAvgTalkTimeLength / 60;
		strTemp.Format("平均通话时长：%d分%d秒", iMinutes, iAvgTalkTimeLength - iMinutes * 60);	
	}
	m_staticAvgCallTimelength.SetWindowText(strTemp);
	if (g_AgentStatic.ProcessCount == 0 || (g_AgentStatic.ProcessTime == 0))
		strTemp = "平均处理时长：0分0秒";	
	else
	{
		int iAvgProcessLength = g_AgentStatic.ProcessTime / g_AgentStatic.ProcessCount + 1;
		int iMinutes = iAvgProcessLength / 60;				
		strTemp.Format("平均处理时长：%d分%d秒", iMinutes, iAvgProcessLength - 60 * iMinutes);
	}
	m_staticAvgProcessTimelength.SetWindowText(strTemp);
	strTemp.Format("外拨%d次；接听%d次", g_AgentStatic.OutDialCount, g_AgentStatic.AnswerCount);
	m_staticOutdialCount.SetWindowText(strTemp);
	if (g_AgentStatic.ParkCount == 0)
		strTemp = "小休0次，共计0分钟";
	else
		strTemp.Format("小休%d次，共计%d分钟", g_AgentStatic.ParkCount, g_AgentStatic.ParkTime / 60 + 1);
	m_staticParkCount.SetWindowText(strTemp);

}


LRESULT CCalendarDlg::OnUpdateTodayStatic(WPARAM wParam, LPARAM lParam)
{
	CString strTime;
	COleDateTime time = COleDateTime::GetCurrentTime();
	m_calendarNow.SetDateSel(time, time);
	string str = g_pMainFrame->m_pLoginDlg->m_AgentPanelOcx.GetBriefStatisticInfo(strTime);
	UpdatetatisticInfo(str);
	return 0;
}
