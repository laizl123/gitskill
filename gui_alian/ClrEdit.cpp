// ClrEdit.cpp : implementation file
//

#include "stdafx.h"
#include "icservingagentclient.h"
#include "ClrEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClrEdit

CClrEdit::CClrEdit()
{
	m_hBakBrush = CreateSolidBrush(RGB(255,255,255)); 
}

CClrEdit::~CClrEdit()
{
	if(m_hBakBrush != NULL)
		DeleteObject(m_hBakBrush);
}


BEGIN_MESSAGE_MAP(CClrEdit, CEdit)
	//{{AFX_MSG_MAP(CClrEdit)
	ON_WM_CTLCOLOR_REFLECT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClrEdit message handlers

HBRUSH CClrEdit::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	// TODO: Change any attributes of the DC here
	pDC->SetTextColor(RGB(0, 0, 0));
	// TODO: Return a non-NULL brush if the parent's handler should not be called
	return m_hBakBrush;
}
