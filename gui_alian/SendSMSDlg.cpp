// SendSMSDlg.cpp : implementation file
//

#include "stdafx.h"
#include "icservingagentclient.h"
#include "SendSMSDlg.h"
#include "MainFrm.h"

#include "Resources.h"
#include "DynamicResource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define IDS_SMSCONTENT_INI _T("请在这里输入短信内容")
extern PRODUCT_VER_INFO g_tagProductVerInfo;

/////////////////////////////////////////////////////////////////////////////
// CSendSMSDlg dialog
CSendSMSDlg::CSendSMSDlg(CWnd* pParent /*=NULL*/)
	: CBkDialog(CSendSMSDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSendSMSDlg)
	m_sSendNumber = _T("");
	m_sSMSContent = "";
	//}}AFX_DATA_INIT
}


void CSendSMSDlg::DoDataExchange(CDataExchange* pDX)
{
	CBkDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSendSMSDlg)
	DDX_Control(pDX, IDC_BTN_SEND, m_btnOK);
	DDX_Control(pDX, IDC_BTN_CANCEL, m_btnCancel);
	DDX_Text(pDX, IDC_SEND_NUMBER, m_sSendNumber);
	DDX_Text(pDX, IDC_SMS_CONTENT, m_sSMSContent);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSendSMSDlg, CBkDialog)
	//{{AFX_MSG_MAP(CSendSMSDlg)
	ON_MESSAGE(WM_SMS_SENDSUCCES, OnSMSSendSuccess)
	ON_MESSAGE(WM_SMS_SENDFAILED, OnSMSSendFailed)
	ON_WM_COPYDATA()
	ON_EN_SETFOCUS(IDC_SMS_CONTENT, OnSetfocusSmsContent)
	ON_EN_KILLFOCUS(IDC_SMS_CONTENT, OnKillfocusSmsContent)
	ON_WM_NCHITTEST()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_SEND, OnBtnSend)
	ON_BN_CLICKED(IDC_BTN_CANCEL, OnBtnCancel)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSendSMSDlg message handlers

void CSendSMSDlg::OnOK() 
{
	if(m_sSendNumber.Find("|") != -1)
	{
		CString sTitle = CResources::GetTextResource(CDynamicResource::s_TextErrorTitle);
		if(sTitle == "")
		{
			if (g_tagProductVerInfo.nVersionType & VerType_IPCC)
				sTitle = "错误--讯鸟座席端";
			else
				sTitle = "错误--启通宝";
		}
		
		_MyMsgBox(sTitle, "接收号码填写有误", MB_OK);
		
		return;
	}
	
	if(m_sSMSContent.GetLength() >= 400)
	{
		CString sTitle = CResources::GetTextResource(CDynamicResource::s_TextErrorTitle);
		if(sTitle == "")
		{
			if (g_tagProductVerInfo.nVersionType & VerType_IPCC)
				sTitle = "错误--讯鸟座席端";
			else
				sTitle = "错误--启通宝";
		}
		
		_MyMsgBox(sTitle, "短信内容长度不能超过400字符(200汉字)", MB_OK);

		return;
	}

	CString sReceiver = m_sSendNumber;
	CString sContent = m_sSMSContent;
	sReceiver.Replace(",","|");
	sReceiver.Replace("，", "|");
	
	CMainFrame* pFrame = (CMainFrame*)GetParent();
	pFrame->m_pLoginDlg->m_AgentPanelOcx.ActionSendSMS(sReceiver, sContent);

	m_btnOK.EnableWindow(FALSE);
}


LRESULT CSendSMSDlg::OnSMSSendSuccess(WPARAM wParam,LPARAM lParam)
{
	CString sTime = COleDateTime::GetCurrentTime().Format("%H:%M:%S");
	CString sTemp;
	sTemp.Format("%s 发送短信成功！\n",	sTime);
	
	CString sTitle = CResources::GetTextResource(CDynamicResource::s_TextTipTitle);
	if(sTitle == "")
	{
		if (g_tagProductVerInfo.nVersionType & VerType_IPCC)
			sTitle = "提示--讯鸟座席端";
		else
			sTitle = "提示--启通宝";
	}
	
	_MyMsgBox(sTitle, sTemp, MB_OK);


	m_btnOK.EnableWindow(TRUE);
	return 1;
}

LRESULT CSendSMSDlg::OnSMSSendFailed(WPARAM wParam,LPARAM lParam)
{
	CString sTime = COleDateTime::GetCurrentTime().Format("%H:%M:%S");
	CString sTemp;
	sTemp.Format("%s 发送短信是失败！\n", sTime);

	CString sTitle = CResources::GetTextResource(CDynamicResource::s_TextTipTitle);
	if(sTitle == "")
	{
		if (g_tagProductVerInfo.nVersionType & VerType_IPCC)
			sTitle = "提示--讯鸟座席端";
		else
			sTitle = "提示--启通宝";
	}
	
	_MyMsgBox(sTitle, sTemp, MB_OK);

	m_btnOK.EnableWindow(TRUE);
	return 1;
}

void CSendSMSDlg::OnCancel(){}

BOOL CSendSMSDlg::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct) 
{
	switch(pCopyDataStruct->dwData) 
	{
	case WM_SMS_SENDFAILEDNUM:
		{
			CString sResult,sTemp;
			CString sFileNum = (LPCSTR)pCopyDataStruct->lpData;
			CString sTime = COleDateTime::GetCurrentTime().Format("%H:%M:%S");
			sTemp.Format("%s 发送短信是失败\n 失败号码: %s\n",
				sTime,sFileNum);

			CString sTitle = CResources::GetTextResource(CDynamicResource::s_TextTipTitle);
			if(sTitle == "")
			{
				if (g_tagProductVerInfo.nVersionType & VerType_IPCC)
					sTitle = "提示--讯鸟座席端";
				else
					sTitle = "提示--启通宝";
			}
			_MyMsgBox(sTitle, sTemp, MB_OK);
		}
		break;
	default:
		break;
	}
	return CBkDialog::OnCopyData(pWnd, pCopyDataStruct);
}

void CSendSMSDlg::OnSetfocusSmsContent() 
{
/*
	CString sContent;
	GetDlgItem(IDC_SMS_CONTENT)->GetWindowText(sContent);
	if(sContent == IDS_SMSCONTENT_INI)
		GetDlgItem(IDC_SMS_CONTENT)->SetWindowText("");
*/
}

void CSendSMSDlg::OnKillfocusSmsContent() 
{
/*
	CString sContent;
	GetDlgItem(IDC_SMS_CONTENT)->GetWindowText(sContent);
	if(sContent == "")
		GetDlgItem(IDC_SMS_CONTENT)->SetWindowText(IDS_SMSCONTENT_INI);	
*/
}

void CSendSMSDlg::SetPhoneNum(CString sendnum)
{
	if(m_sSendNumber.Right(1) == "," || m_sSendNumber.Right(1) == "," || m_sSendNumber== "")
	{			
		m_sSendNumber = m_sSendNumber+ sendnum;
	}
	else
	{
		m_sSendNumber = m_sSendNumber+ "," + sendnum;
	}

	GetDlgItem(IDC_SEND_NUMBER)->SetWindowText(m_sSendNumber);
}


BOOL CSendSMSDlg::OnInitDialog() 
{
	CBkDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetBitmap(IDB_BMP_BG);
//	SetTimer(14, 500, 0);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

UINT CSendSMSDlg::OnNcHitTest(CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	return HTCAPTION;
}


HBRUSH CSendSMSDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CBkDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if (CTLCOLOR_STATIC == nCtlColor)
	{
		hbr = (HBRUSH)GetStockObject(NULL_BRUSH);//对于static来说，使用空刷子
		pDC->SetBkMode(TRANSPARENT);
	}	

	if (pWnd->GetDlgCtrlID() == IDC_STATIC_SMS_TITLE)
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

void CSendSMSDlg::OnBtnSend() 
{
	// TODO: Add your control notification handler code here
	UpdateData();

	CString sTitle = CResources::GetTextResource(CDynamicResource::s_TextTipTitle);
	if(sTitle == "")
	{
		if (g_tagProductVerInfo.nVersionType & VerType_IPCC)
			sTitle = "提示--讯鸟座席端";
		else
			sTitle = "提示--启通宝";
	}

	if (m_sSendNumber == "")
	{
		
		_MyMsgBox(sTitle, "发送短信对象不能为空!", MB_OK);
		return;
	}

	if (m_sSMSContent == "")
	{
		_MyMsgBox(sTitle, "发送短信内容不能为空!", MB_OK);
		return;
	}

	OnOK();
}

void CSendSMSDlg::OnBtnCancel() 
{
	// TODO: Add your control notification handler code here
	ShowWindow(SW_HIDE);
}

void CSendSMSDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
/*
	if (nIDEvent == 14)
	{
		CString strPhoneNum, strSMSResult;
		GetDlgItem(IDC_SEND_NUMBER)->GetWindowText(strPhoneNum);
		GetDlgItem(IDC_SMS_CONTENT)->GetWindowText(strSMSResult);
		if (strSMSResult == "" || strPhoneNum == "")
		{
			m_btnOK.EnableWindow(FALSE);
		}
		else
		{
			m_btnOK.EnableWindow(TRUE);
		}
	}
*/	
	CBkDialog::OnTimer(nIDEvent);
}
