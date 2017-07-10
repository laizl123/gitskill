// GetTalkAgentDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GetTalkAgentDlg.h"
#include "Environment.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern int g_iSuperAgentType;
/////////////////////////////////////////////////////////////////////////////
// CGetTalkAgentDlg dialog

CGetTalkAgentDlg::CGetTalkAgentDlg(CWnd* pParent /*=NULL*/)
: CDialog(CGetTalkAgentDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGetTalkAgentDlg)
	// NOTE: the ClassWizard will add member initialization here
	m_pParent = pParent;
	//}}AFX_DATA_INIT
}

void CGetTalkAgentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGetTalkAgentDlg)
	DDX_Control(pDX, IDC_LIST_TALK_AGENT, m_TalkAgentTree);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGetTalkAgentDlg, CDialog)
//{{AFX_MSG_MAP(CGetTalkAgentDlg)
ON_BN_CLICKED(IDC_BTN_MONIT, OnBtnMonit)
ON_WM_NCHITTEST()
ON_WM_COPYDATA()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGetTalkAgentDlg message handlers
void CGetTalkAgentDlg::ClearTreeItem()
{
	m_ItemMap.clear();
	m_TalkAgentTree.DeleteAllItems();
}

void CGetTalkAgentDlg::OnBtnMonit() 
{
	// TODO: Add your control notification handler code here
	HTREEITEM hSelItem = m_TalkAgentTree.GetSelectedItem();
	if (m_TalkAgentTree.GetItemData(hSelItem) == (DWORD)dialDeparment)
	{
		::MessageBox(NULL, "请选择座席进行监听!", "提示", MB_OK);
		return;
	}
	MonitAgent(hSelItem);
}

BOOL CGetTalkAgentDlg::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct) 
{
	// TODO: Add your message handler code here and/or call default
	TalkAgentList* pTalkAgentList = (TalkAgentList*)pCopyDataStruct->lpData;
	if(pTalkAgentList->sTalkAgent.length() == 0)
		return TRUE;
	
	ClearTreeItem();
	
	if (g_iSuperAgentType == 3)
	{
		CSpliter split(pTalkAgentList->sTalkAgent, "|");
		int iSize = split.GetSize();
		for (int i = 0; i < iSize; i++)
		{
			CSpliter split2(split[i], ",");
			if (split2.GetSize() != 3)
			{
				continue;
			}
			
			string sAgent = split2[0];
			unsigned long iIp = atoi(split2[1].c_str());
			unsigned short iPort = atoi(split2[2].c_str());
			
			m_ItemMap[sAgent] = make_pair(iIp, iPort);
			m_TalkAgentTree.InsertItem(sAgent.c_str());
		}
	}
	else if (g_iSuperAgentType == 4)
	{
       // pTalkAgentList->sTalkAgent="电销五部/111,fanxp@infobird.com(樊雪平;0),2768283840,46212|电销三部/222,huyx@infobird.com(胡叶霞;0),1761650880,39904";
		
		CString strTalkAgent;
        strTalkAgent.Format("%s",pTalkAgentList->sTalkAgent.c_str());
        if(strTalkAgent.Find("/")!=-1)
		{
			CSpliter departsplit(pTalkAgentList->sTalkAgent, "|");
			HTREEITEM hDeparmentItem;	
			for(int i=0; i<departsplit.GetSize(); i++)
			{
				CSpliter agentsplit1(departsplit[i], ",");
				CSpliter agentsplit(agentsplit1[0],"/");
				
				if (agentsplit1.GetSize() != 4)
				{
					continue;
				}
				hDeparmentItem = FindItemByName(agentsplit[1].c_str());
				
				if(!hDeparmentItem)	
					hDeparmentItem = m_TalkAgentTree.InsertItem(agentsplit[1].c_str(),NULL,NULL,TVI_ROOT);
				m_TalkAgentTree.SetItemData(hDeparmentItem,(DWORD)dialDeparment);
					
				TVINSERTSTRUCT tvInsert;
				tvInsert.hParent = hDeparmentItem;
				tvInsert.hInsertAfter = NULL;
				tvInsert.item.mask = TVIF_TEXT;
				tvInsert.item.pszText = (char *)agentsplit1[1].c_str();
				HTREEITEM hCountry = m_TalkAgentTree.InsertItem(&tvInsert);
				m_TalkAgentTree.SetItemData(hCountry,(DWORD)dialAgent);
				m_TalkAgentTree.Expand(hDeparmentItem, TVE_EXPAND);
				
				string sAgent = agentsplit1[1];
				unsigned long iIp = atoi(agentsplit1[2].c_str());
				unsigned short iPort = atoi(agentsplit1[3].c_str());
				
				m_ItemMap[sAgent] = make_pair(iIp, iPort);
			}
		}
		else
		{
		CSpliter departsplit(pTalkAgentList->sTalkAgent, "|");
		HTREEITEM hDeparmentItem;	
		for(int i=0; i<departsplit.GetSize(); i++)
		{
			CSpliter agentsplit(departsplit[i], ",");
			if (agentsplit.GetSize() != 4)
			{
				continue;
			}
			hDeparmentItem = FindItemByName(agentsplit[0].c_str());
			if(!hDeparmentItem)	
				hDeparmentItem = m_TalkAgentTree.InsertItem(agentsplit[0].c_str(),NULL,NULL,TVI_ROOT);
			m_TalkAgentTree.SetItemData(hDeparmentItem,(DWORD)dialDeparment);
			
			TVINSERTSTRUCT tvInsert;
			tvInsert.hParent = hDeparmentItem;
			tvInsert.hInsertAfter = NULL;
			tvInsert.item.mask = TVIF_TEXT;
			tvInsert.item.pszText = (char *)agentsplit[1].c_str();
			HTREEITEM hCountry = m_TalkAgentTree.InsertItem(&tvInsert);
			m_TalkAgentTree.SetItemData(hCountry,(DWORD)dialAgent);
			m_TalkAgentTree.Expand(hDeparmentItem, TVE_EXPAND);
			
			string sAgent = agentsplit[1];
			unsigned long iIp = atoi(agentsplit[2].c_str());
			unsigned short iPort = atoi(agentsplit[3].c_str());
			
			m_ItemMap[sAgent] = make_pair(iIp, iPort);
			}
		}
	}
	else
	{	
		return CDialog::OnCopyData(pWnd, pCopyDataStruct);
	}
	
	m_TalkAgentTree.SetFocus();
	m_TalkAgentTree.SelectItem(m_TalkAgentTree.GetFirstVisibleItem());
	
	return CDialog::OnCopyData(pWnd, pCopyDataStruct);
}

void CGetTalkAgentDlg::MonitAgent(HTREEITEM& hTreeItem)
{
	if(!hTreeItem)
		return;
	
	CString str = m_TalkAgentTree.GetItemText(hTreeItem);
	map<string, pair<unsigned long, unsigned short> >::iterator it
		= m_ItemMap.find(string(str));
	if (it == m_ItemMap.end())
	{
		return;
	}
	
	COPYDATASTRUCT cds;
	MonitMessage msg;
	msg.sAgent = it->first;
	msg.iIp = it->second.first;
	msg.iPort = it->second.second;
	cds.dwData = MONITMESSAGE_COPYDATA_MSG;
	cds.cbData = sizeof(msg);
	cds.lpData = &msg;
	::SendMessage(m_pParent->GetSafeHwnd(), WM_COPYDATA, 0, (LPARAM)(LPVOID) &cds);
	
	ShowWindow(SW_HIDE);
}

HTREEITEM CGetTalkAgentDlg::FindItemByName(LPCSTR szItemName)
{
	HTREEITEM rootItem = m_TalkAgentTree.GetRootItem();
	
	if (m_TalkAgentTree.ItemHasChildren(rootItem))
	{
		HTREEITEM hNextItem;
		HTREEITEM hChildItem = m_TalkAgentTree.GetChildItem(rootItem);
		
		while (hChildItem != NULL)
		{
			CString sItem = m_TalkAgentTree.GetItemText(hChildItem);
			int iType = m_TalkAgentTree.GetItemData(hChildItem);
			if(sItem == szItemName && (iType == dialDeparment || iType == dialOtherDeparment))
				return hChildItem;
			
			
			hNextItem = m_TalkAgentTree.GetNextItem(hChildItem, TVGN_NEXT);
			hChildItem = hNextItem;			
		}
	}
	return NULL;
}

void CGetTalkAgentDlg::OnOK(){ ShowWindow(SW_HIDE); }
void CGetTalkAgentDlg::OnCancel(){ ShowWindow(SW_HIDE); }
LRESULT CGetTalkAgentDlg::OnNcHitTest(CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	
	return HTCAPTION;
}

