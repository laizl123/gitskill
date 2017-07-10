// StrParse.cpp: implementation of the CStrParse class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "StrParse.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStrParse::CStrParse()
{

}

CStrParse::~CStrParse()
{

}

/************************************************************************/
// 字符串合并
/************************************************************************/
void CStrParse::ParseArray(CStringArray& arrStr, char space, CString& str)
{
	CString strSpace = space;
	// 序列化
	ParseArray(arrStr, strSpace, str);
}

void CStrParse::ParseArray(CStringArray& arrStr,
						   CString& space,
						   CString& str)
{
	CString strData;
	// 序列化
	int nSize = arrStr.GetSize();
	for(int i = 0; i < nSize; i++)
	{
		CString strTemp = arrStr.GetAt(i);
		strData += strTemp;
		if(i < nSize-1)
		{
			strData += space;
		}
	}// for(
	str = strData;	
}

/************************************************************************/
// 字符串解析
/************************************************************************/
void CStrParse::ParseString(CString& str, char space, CStringArray& arrStr)
{
	CString strSpace = space;
	ParseString(str, strSpace, arrStr);
}

void CStrParse::ParseString(CString& str,
							CString& space,
							CStringArray& arrStr)
{
	int nBgn = 0;
	int nEnd = 0;
	int nLen = str.GetLength();
	// 数据解析
	arrStr.RemoveAll();
	while(nBgn < nLen)
	{
		nEnd = str.Find(space, nBgn);
		if(nEnd == -1)
		{
			nEnd = nLen;
		}
		CString strData = str.Mid(nBgn, nEnd - nBgn);
		if(strData.IsEmpty() == FALSE)
		{
			arrStr.Add(strData);
		}
		// 开头前移
		nBgn = nEnd + space.GetLength();
	}// while(
}
