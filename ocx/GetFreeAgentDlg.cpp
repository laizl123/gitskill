// GetFreeAgentDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GetFreeAgentDlg.h"
#include "ConsoleMessageDef.h"
#include "GeTokenString.h"
#include "Environment.h"
#include "Log.h"

extern CString g_strAccount;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGetFreeAgentDlg dialog
CGetFreeAgentDlg::CGetFreeAgentDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGetFreeAgentDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGetFreeAgentDlg)
		// NOTE: the ClassWizard will add member initialization here
	m_pParent = pParent;
	//}}AFX_DATA_INIT
}


void CGetFreeAgentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGetFreeAgentDlg)
	DDX_Control(pDX, IDC_LIST_FREE_AGENT, m_FreeAgentTree);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGetFreeAgentDlg, CDialog)
	//{{AFX_MSG_MAP(CGetFreeAgentDlg)
	ON_BN_CLICKED(IDC_BTN_CALL, OnBtnCall)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_FREE_AGENT, OnDblclkListFreeAgent)
	ON_WM_COPYDATA()
	ON_NOTIFY(TVN_SELCHANGED, IDC_LIST_FREE_AGENT, OnSelchangedListFreeAgent)
	ON_NOTIFY(NM_CLICK, IDC_LIST_FREE_AGENT, OnClickListFreeAgent)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGetFreeAgentDlg message handlers

void CGetFreeAgentDlg::OnBtnCall() 
{
	HTREEITEM hSelItem = m_FreeAgentTree.GetSelectedItem();
	CallFreeAgent(hSelItem);
}

void CGetFreeAgentDlg::OnDblclkListFreeAgent(NMHDR* pNMHDR, LRESULT* pResult) 
{
/*
	*pResult = 0;

	CPoint pt = GetCurrentMessage()->pt;
	//转为客户区坐标
	m_FreeAgentTree.ScreenToClient(&pt);
	HTREEITEM hitem = m_FreeAgentTree.HitTest(pt);

	if(!hitem)
		return;

	CallFreeAgent(hitem);	
*/
}

BOOL CGetFreeAgentDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CGetFreeAgentDlg::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct) 
{
	FreeAgentList* pFreeAgentList = (FreeAgentList*)pCopyDataStruct->lpData;
	BOOL bEnd = (BOOL)pFreeAgentList->bEnd;
	
	if(pFreeAgentList->sFreeAgent.length() == 0)
		return TRUE;

	CStringArray DepartArray,AgentArray;
	CGeTokenString::Split(pFreeAgentList->sFreeAgent.c_str(),"|",DepartArray);
	CString sDepartment = pFreeAgentList->sDepartment.c_str();

	sDepartment =	sDepartment.Right( sDepartment.GetLength() - sDepartment.Find( "%^#" ) - 3 );

	HTREEITEM hCurrentGroupItem = NULL, hDeparmentItem = NULL;

	for(int i=0; i<DepartArray.GetSize(); i++)
	{
		CGeTokenString::Split(DepartArray.GetAt(i),",",AgentArray);
		
		if(AgentArray.GetSize() <= 0)
			continue;

		CString sArrayMember;	//部门
		sArrayMember = AgentArray.GetAt(0);
		sArrayMember.TrimLeft();
		sArrayMember.TrimRight();

		for(int j=0; j<AgentArray.GetSize(); j++)
		{			
			if(j==0)
			{				
				hDeparmentItem = FindItemByName(sArrayMember);
				if(!hDeparmentItem)	
					hDeparmentItem = m_FreeAgentTree.InsertItem(sArrayMember,NULL,NULL,TVI_ROOT);

				if(sArrayMember == sDepartment)
				{
					hCurrentGroupItem = hDeparmentItem;
					m_FreeAgentTree.SetItemData(hDeparmentItem,(DWORD)dialDeparment);
				}
				else
					m_FreeAgentTree.SetItemData(hDeparmentItem,(DWORD)dialOtherDeparment);
			}
			else
			{
				if(hDeparmentItem)
				{
					if(AgentArray.GetAt(j) == "")
						continue;

					CString strItemText = AgentArray.GetAt(j);
					int iFind = strItemText.Find("(");
					if (iFind != -1)
						strItemText = strItemText.Left(iFind);
					if (strItemText == g_strAccount)
						continue;

					HTREEITEM hItemAgent = m_FreeAgentTree.InsertItem(AgentArray.GetAt(j),NULL,NULL,hDeparmentItem);
					if(sArrayMember == sDepartment)
						m_FreeAgentTree.SetItemData(hItemAgent,(DWORD)dialAgent);
					else
						m_FreeAgentTree.SetItemData(hItemAgent,(DWORD)dialOtherAgent);
				}
			}
		}
	}
	if(bEnd)
	{
		m_FreeAgentTree.SetFocus();
		m_FreeAgentTree.SelectItem(m_FreeAgentTree.GetFirstVisibleItem());
	}

	return CDialog::OnCopyData(pWnd, pCopyDataStruct);
}

void CGetFreeAgentDlg::CallFreeAgent(HTREEITEM &hTreeItem)
{	
	if(!hTreeItem)
		return;

	int iIitemType = (int)m_FreeAgentTree.GetItemData(hTreeItem);
	CString str = m_FreeAgentTree.GetItemText(hTreeItem);
	int nPos = str.Find("(");
	if(nPos != -1)
		str = str.Left(nPos);
	switch(iIitemType) {
	case dialAgent:
		{
			COPYDATASTRUCT CallMessageCDS;
			CallMessage callmsg;	
			memset(callmsg.sCallTarger,0,sizeof(callmsg.sCallTarger));
			memcpy(callmsg.sCallTarger,str.LockBuffer(),str.GetLength());
			str.UnlockBuffer();
			callmsg.iCallType = dialAgent;
			
			CallMessageCDS.dwData = CALLMESSAGE_COPYDATA_MSG;          // function identifier
			CallMessageCDS.cbData = sizeof( callmsg );  // size of data
			CallMessageCDS.lpData = &callmsg;
			::SendMessage(m_pParent->GetSafeHwnd(),WM_COPYDATA,0,(LPARAM)(LPVOID)&CallMessageCDS);
		}
		break;
	case dialOtherAgent:
		{
			COPYDATASTRUCT CallMessageCDS;
			CallMessage callmsg;	
			memset(callmsg.sCallTarger,0,sizeof(callmsg.sCallTarger));
			memcpy(callmsg.sCallTarger,str.LockBuffer(),str.GetLength());
			str.UnlockBuffer();
			callmsg.iCallType = dialOtherAgent;
			
			CallMessageCDS.dwData = CALLMESSAGE_COPYDATA_MSG;          // function identifier
			CallMessageCDS.cbData = sizeof( callmsg );  // size of data
			CallMessageCDS.lpData = &callmsg;
			
			::SendMessage(m_pParent->GetSafeHwnd(),WM_COPYDATA,0,(LPARAM)(LPVOID)&CallMessageCDS);
		}
		break;
	case dialDeparment:
		{
			COPYDATASTRUCT CallMessageCDS;
			CallMessage callmsg;	
			memset(callmsg.sCallTarger,0,sizeof(callmsg.sCallTarger));
			memcpy(callmsg.sCallTarger,str.LockBuffer(),str.GetLength());
			str.UnlockBuffer();
			
			callmsg.iCallType = dialDeparment;
			CallMessageCDS.dwData = CALLMESSAGE_COPYDATA_MSG;          // function identifier
			CallMessageCDS.cbData = sizeof( callmsg );  // size of data
			CallMessageCDS.lpData = &callmsg;
			::SendMessage(m_pParent->GetSafeHwnd(),WM_COPYDATA,0,(LPARAM)(LPVOID)&CallMessageCDS);
		}
		break;
	case dialOtherDeparment:
		{
			COPYDATASTRUCT CallMessageCDS;
			CallMessage callmsg;	
			memset(callmsg.sCallTarger,0,sizeof(callmsg.sCallTarger));
			memcpy(callmsg.sCallTarger,str.LockBuffer(),str.GetLength());
			str.UnlockBuffer();
			
			callmsg.iCallType = dialOtherDeparment;
			CallMessageCDS.dwData = CALLMESSAGE_COPYDATA_MSG;          // function identifier
			CallMessageCDS.cbData = sizeof( callmsg );  // size of data
			CallMessageCDS.lpData = &callmsg;
			::SendMessage(m_pParent->GetSafeHwnd(),WM_COPYDATA,0,(LPARAM)(LPVOID)&CallMessageCDS);
		}
		break;
	default:
		break;
	}
	
	ShowWindow(SW_HIDE);
}

HTREEITEM CGetFreeAgentDlg::FindItemByName(LPCSTR szItemName)
{
	HTREEITEM rootItem = m_FreeAgentTree.GetRootItem();
	
	if (m_FreeAgentTree.ItemHasChildren(rootItem))
	{
		HTREEITEM hNextItem;
		HTREEITEM hChildItem = m_FreeAgentTree.GetChildItem(rootItem);
		
		while (hChildItem != NULL)
		{
			CString sItem = m_FreeAgentTree.GetItemText(hChildItem);
			int iType = m_FreeAgentTree.GetItemData(hChildItem);
			if(sItem == szItemName && (iType == dialDeparment || iType == dialOtherDeparment))
				return hChildItem;


			hNextItem = m_FreeAgentTree.GetNextItem(hChildItem, TVGN_NEXT);
			hChildItem = hNextItem;			
		}
	}
	return NULL;
}

void CGetFreeAgentDlg::OnSelchangedListFreeAgent(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	*pResult = 0;

	HTREEITEM hSelItem = m_FreeAgentTree.GetSelectedItem();

	if(!hSelItem)
		return;

	int iType = (int)m_FreeAgentTree.GetItemData(hSelItem);
	if (iType == dialAgent || iType == dialOtherAgent)
		return;
	
	m_FreeAgentTree.Expand(hSelItem,TVE_EXPAND);
/*
	HTREEITEM rootItem = m_FreeAgentTree.GetParentItem(hSelItem);
	
	if (m_FreeAgentTree.ItemHasChildren(rootItem))
	{
		HTREEITEM hNextItem;
		HTREEITEM hChildItem = m_FreeAgentTree.GetChildItem(rootItem);
		
		while (hChildItem != NULL)
		{
			int iType = m_FreeAgentTree.GetItemData(hChildItem);
			if((iType == Type_group || iType == Type_Other_group) && hSelItem != hChildItem)
			{
				m_FreeAgentTree.Expand(hChildItem,TVE_COLLAPSE);
			}

			hNextItem = m_FreeAgentTree.GetNextItem(hChildItem, TVGN_NEXT);
			hChildItem = hNextItem;			
		}
	}
*/
}


void CGetFreeAgentDlg::OnClickListFreeAgent(NMHDR* pNMHDR, LRESULT* pResult) 
{

	*pResult = 0;

	CPoint pt = GetCurrentMessage()->pt;
	//转为客户区坐标
	m_FreeAgentTree.ScreenToClient(&pt);
	HTREEITEM hitem = m_FreeAgentTree.HitTest(pt);

	if(!hitem)
		return;

	int iType = (int)m_FreeAgentTree.GetItemData(hitem);
	if (iType == dialAgent || iType == dialOtherAgent)
		return;


	HTREEITEM rootItem = m_FreeAgentTree.GetParentItem(hitem);
	
	if (m_FreeAgentTree.ItemHasChildren(rootItem))
	{
		HTREEITEM hNextItem;
		HTREEITEM hChildItem = m_FreeAgentTree.GetChildItem(rootItem);
		
		while (hChildItem != NULL)
		{
			int iType = m_FreeAgentTree.GetItemData(hChildItem);
			if((iType == dialDeparment || iType == dialOtherDeparment) && hitem != hChildItem)
			{
				m_FreeAgentTree.Expand(hChildItem,TVE_COLLAPSE);
			}

			hNextItem = m_FreeAgentTree.GetNextItem(hChildItem, TVGN_NEXT);
			hChildItem = hNextItem;			
		}
	}
}

void CGetFreeAgentDlg::ClearTreeItem()
{
	m_FreeAgentTree.DeleteAllItems();
}

void CGetFreeAgentDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	ClearTreeItem();
}


void CGetFreeAgentDlg::OnOK(){ ShowWindow(SW_HIDE); }
void CGetFreeAgentDlg::OnCancel(){ ShowWindow(SW_HIDE); }
