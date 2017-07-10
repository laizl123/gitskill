// TextChatChildDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ICServingAgentClient.h"
#include "TextChatDlg.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTextChatDlg dialog
CTextChatDlg::CTextChatDlg(CWnd* pParent /*=NULL*/)
: CBkDialog(CTextChatDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTextChatDlg)
	//}}AFX_DATA_INIT
	m_nPageToLine = 0;
}


void CTextChatDlg::DoDataExchange(CDataExchange* pDX)
{
	CBkDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTextChatDlg)
	DDX_Control(pDX, IDC_BTN_SEND, m_btnSend);
	DDX_Control(pDX, IDC_BTN_CANCEL, m_btnCancel);
	DDX_Control(pDX, IDC_TEXTCHAT_SAY, m_OleTextChatSay);
	DDX_Control(pDX, IDC_TEXTCHAT_HIS, m_OleTextChatHistory);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTextChatDlg, CBkDialog)
//{{AFX_MSG_MAP(CTextChatDlg)
ON_EN_CHANGE(IDC_TEXTCHAT_SAY, OnChangeTextchatSay)
ON_WM_CTLCOLOR()
ON_WM_NCHITTEST()
ON_BN_CLICKED(IDC_BTN_SEND, OnBtnSend)
ON_BN_CLICKED(IDC_BTN_CANCEL, OnBtnCancel)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CTextChatDlg message handlers

BOOL CTextChatDlg::OnInitDialog() 
{
	CBkDialog::OnInitDialog();
	SetBitmap(IDB_BMP_BG);
	
	m_OleTextChatSay.SetEventMask(m_OleTextChatSay.GetEventMask() | ENM_CHANGE);	
	m_OleTextChatHistory.SetReadOnly();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CTextChatDlg::PutChatContent(CString sChater, CString sChatContent, BOOL bSysmsg, BOOL bClearSay, BOOL bLocalAgentChat)
{
	if (!IsWindowVisible())
	{
		ShowWindow(SW_SHOW);	
	}
	
	int iFirstLine = m_OleTextChatHistory.GetLineCount();
	int iLength = m_OleTextChatHistory.GetWindowTextLength();

	if(iFirstLine != 1)
	{
		m_OleTextChatHistory.SetSel(-1, -1);
		m_OleTextChatHistory.ReplaceSel("\n"+sChater);			
	}
	else
	{
		m_OleTextChatHistory.SetSel(-1, -1);
		m_OleTextChatHistory.ReplaceSel(sChater);
	}
	
	int iNewLength = m_OleTextChatHistory.GetWindowTextLength();
	
	m_OleTextChatHistory.SetSel(-1, -1);
	m_OleTextChatHistory.ReplaceSel("\n   " + sChatContent);

	m_OleTextChatHistory.SetSel(iLength, iNewLength);
	CHARFORMAT cf;
	cf.cbSize		= sizeof(CHARFORMAT);
	cf.dwMask		= CFM_COLOR | CFM_UNDERLINE | CFM_BOLD | CFE_ITALIC;
	cf.dwEffects	= (unsigned long)~( CFE_AUTOCOLOR | CFE_UNDERLINE | CFM_STRIKEOUT | CFE_ITALIC | CFE_BOLD);  // | CFE_BOLD
	//	cf.dwEffects	|= CFE_ITALIC;
	if (bSysmsg)
		cf.crTextColor	= RGB(245, 0, 0);
	else if (bLocalAgentChat)
		cf.crTextColor = RGB(6, 150, 6);
	else
		cf.crTextColor = RGB(0, 0, 255);
	m_OleTextChatHistory.SetSelectionCharFormat(cf); 
	m_OleTextChatHistory.HideSelection(TRUE, FALSE);
	
	m_OleTextChatHistory.SetSel(-1, -1);
	cf.cbSize		= sizeof(CHARFORMAT);
	cf.dwMask		= CFM_COLOR | CFM_UNDERLINE | CFM_BOLD | CFM_ITALIC;
	cf.dwEffects	= (unsigned long)~( CFE_ITALIC | CFE_AUTOCOLOR | CFE_UNDERLINE | CFE_STRIKEOUT | CFE_BOLD);
	//cf.dwEffects	|= CFE_ITALIC;
	cf.crTextColor	= RGB(0, 0, 0);
	m_OleTextChatHistory.SetSelectionCharFormat(cf); 
	m_OleTextChatHistory.HideSelection(TRUE, FALSE);

	int iMin, iMax;
	m_OleTextChatHistory.GetScrollRange(SB_VERT, &iMin, &iMax);
	if(iMax > iMin)
	{		
		m_OleTextChatHistory.SendMessage(WM_VSCROLL, SB_BOTTOM, 0);
	}
	
	if(bClearSay)
	{
		m_OleTextChatSay.SetSel(0, -1);
		m_OleTextChatSay.ReplaceSel("");
		m_OleTextChatSay.SetFocus();		
	}
	OnChangeTextchatSay();
}

void CTextChatDlg::OnChangeTextchatSay() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CBkDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	CString sWord;
	m_OleTextChatSay.GetWindowText(sWord);
	if(!sWord.IsEmpty())
		m_btnSend.EnableWindow(TRUE);
	else
		m_btnSend.EnableWindow(FALSE);
}

void CTextChatDlg::OnOK(){}
void CTextChatDlg::OnCancel(){}

BOOL CTextChatDlg::PreTranslateMessage(MSG* pMsg) 
{	
	if(pMsg->message == WM_KEYDOWN)	
	{
		if(pMsg->hwnd == m_OleTextChatSay.GetSafeHwnd() 
			&& pMsg->wParam == VK_RETURN)
		{
			//GetKeyState(VK_CONTROL)&0x80
			return AfxGetMainWnd()->PreTranslateMessage(pMsg);
		}
	}
	
	return CBkDialog::PreTranslateMessage(pMsg);	
}

HBRUSH CTextChatDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CBkDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if(nCtlColor==CTLCOLOR_STATIC)   
	{   
		hbr = (HBRUSH)GetStockObject(NULL_BRUSH);//对于static来说，使用空刷子
		pDC->SetBkMode(TRANSPARENT);
	}
	
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_TEXTCHAT_TITLE)
	{
		CFont font;
		LOGFONT lf;
		memset(&lf, 0, sizeof(LOGFONT));       // zero out structure
		lf.lfHeight = 15;
		lf.lfWeight = FW_BOLD;
		strcpy(lf.lfFaceName, "宋体");        // request a face name "Arial"
		VERIFY(font.CreateFontIndirect(&lf));  // create the font
		
		pDC->SelectObject(&font);
	}
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

UINT CTextChatDlg::OnNcHitTest(CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	return HTCAPTION;
}

void CTextChatDlg::OnBtnSend() 
{
	// TODO: Add your control notification handler code here
	//->PostMessage(WM_MY_SEND_CHAT);
	((CMainFrame *)AfxGetMainWnd())->OnSendChat();
}

void CTextChatDlg::OnBtnCancel() 
{
	// TODO: Add your control notification handler code here
	ShowWindow(SW_HIDE);
}