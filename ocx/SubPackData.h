// SubPackData.h: interface for the CSubPackData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SUBPACKDATA_H__2047BB14_19CD_4AEB_84D4_7BB238A28B78__INCLUDED_)
#define AFX_SUBPACKDATA_H__2047BB14_19CD_4AEB_84D4_7BB238A28B78__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSubPackData  
{
public:
	CSubPackData();
	virtual ~CSubPackData();
public:
	// °üºÅ
	int m_nPackID;
	int m_nTotNum;
	int m_nNowNum;
	int m_nMsgLen;
	char* m_pMsgData;

};

#endif // !defined(AFX_SUBPACKDATA_H__2047BB14_19CD_4AEB_84D4_7BB238A28B78__INCLUDED_)
