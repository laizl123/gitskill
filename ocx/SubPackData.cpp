// SubPackData.cpp: implementation of the CSubPackData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "agentpanelocx.h"
#include "SubPackData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSubPackData::CSubPackData()
{
	// °üºÅ
	m_nPackID = 0;
	m_nTotNum = 1;
	m_nNowNum = 1;
	m_pMsgData = NULL;
	m_nMsgLen = 0;

}

CSubPackData::~CSubPackData()
{
	if(m_pMsgData != NULL)
	{
		delete [] m_pMsgData;
		m_pMsgData = NULL;
	}
}
