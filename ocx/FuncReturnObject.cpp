// FuncReturnObject.cpp: implementation of the CFuncReturnObject class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AgentPanelOcx.h"
#include "FuncReturnObject.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFuncReturnObject::CFuncReturnObject()
{
	// FUNCTION ID
	m_nFuncdispID = 0;
	m_hMsgWnd = NULL;
	// 事件
	m_hWaitEvent = NULL;
}

CFuncReturnObject::~CFuncReturnObject()
{

}

const CFuncReturnObject& CFuncReturnObject::operator=(const CFuncReturnObject& info)
{
	// FUNCTION ID
	m_nFuncdispID = info.m_nFuncdispID;
	// 序列号
	m_nSeqenceID = info.m_nSeqenceID;
	m_hMsgWnd = info.m_hMsgWnd;
	// 事件
	m_hWaitEvent = info.m_hWaitEvent;
	m_varReturn = info.m_varReturn;
	return *this;
}	
CFuncReturnObject::CFuncReturnObject(const CFuncReturnObject& info)
{
	*this = info;
}
