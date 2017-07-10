#include "stdafx.h"
#include "WorkMateWindow.h"


CWorkMateWindow::CWorkMateWindow()
{
}


CWorkMateWindow::~CWorkMateWindow()
{
    int i = 0;
}

DuiLib::tString CWorkMateWindow::GetSkinFile()
{
    return _T("workmate.xml");
}

void CWorkMateWindow::Init()
{
    CBaseWindow::Init();

    if(m_pInfoBtn)
        {
            m_pInfoBtn->SetVisible(false);
        }

    if(m_pMaxSysBtn)
        {
            m_pMaxSysBtn->SetVisible(false);
        }
}
