// UpdatePropertySheet.cpp : implementation file
//

#include "stdafx.h"
#include "ICServingAgentClient.h"
#include "UpdatePropertySheet.h"

#include "UpdateDownPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUpdatePropertySheet

IMPLEMENT_DYNAMIC(CUpdatePropertySheet, CPropertySheet)

CUpdatePropertySheet::CUpdatePropertySheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
//	m_psh.dwFlags |= PSH_WIZARD97;
	m_bForceUpdate = FALSE;
}

CUpdatePropertySheet::CUpdatePropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
//	m_psh.dwFlags |= PSH_WIZARD97;
	m_bForceUpdate = FALSE;
}

CUpdatePropertySheet::~CUpdatePropertySheet()
{
}


BEGIN_MESSAGE_MAP(CUpdatePropertySheet, CPropertySheet)
	//{{AFX_MSG_MAP(CUpdatePropertySheet)
	ON_WM_SYSCOMMAND()
	ON_MESSAGE(WM_DESTROYWIZARD,OnDestroyWizard)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUpdatePropertySheet message handlers

BOOL CUpdatePropertySheet::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
	if(nID == IDCANCEL && CN_COMMAND == nCode)
	{
		if(1 == GetActiveIndex())
		{
			CUpdateDownPage* pActivePage = NULL;
			
			pActivePage =  (CUpdateDownPage*)GetActivePage();
			pActivePage->SuspendThread();
			if(MessageBox("�������������£��������������ܸ��ȶ��������ʵķ���\n\n������Ҫ��ֹ�����𣿣���/��",
				"��ʾ",MB_YESNO|MB_ICONINFORMATION) == IDNO)
			{	
				
				pActivePage->ResumeThread();
				return TRUE;
			}
			pActivePage->ResumeThread();
			pActivePage->ExitThread();	
		}
		else
		{
			if(m_bForceUpdate)
			{
				if(MessageBox("��⵽��Ҫ����\n���ȡ���п����޷�����ʹ��\n��������� ��һ�� �������¡�\n\n������Ҫ��ֹ���³����𣿣���/��", 
					"��ʾ",
					MB_YESNO|MB_ICONWARNING) == IDNO)
					return TRUE;
			}
			else
			{
				if(MessageBox("�������������£��������������ܸ��ȶ��������ʵķ���\n\n��ȷ����ֹ���³����𣿣���/��",
					"��ʾ",MB_YESNO|MB_ICONINFORMATION) == IDNO)
				{	
					return TRUE;
				}
			}
		}	
	}	
	return CPropertySheet::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

void CUpdatePropertySheet::OnSysCommand(UINT nID, LPARAM lParam) 
{
	if (nID == SC_CLOSE)
	{
		return;
	}	
	CPropertySheet::OnSysCommand(nID, lParam);
}

LRESULT CUpdatePropertySheet::OnDestroyWizard(WPARAM wParam, LPARAM lParam)
{
	EndDialog(wParam  );
	return 1;
}
