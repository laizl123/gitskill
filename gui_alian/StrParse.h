// StrParse.h: interface for the CStrParse class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STRPARSE_H__CAFA14F0_A1F7_47F1_BEBD_DD4B8719CA7E__INCLUDED_)
#define AFX_STRPARSE_H__CAFA14F0_A1F7_47F1_BEBD_DD4B8719CA7E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CStrParse  
{
public:
	CStrParse();
	virtual ~CStrParse();
public:
	// ×Ö·û´®ºÏ²¢
	static void ParseArray(CStringArray& arrStr, char space, CString& str);
	static void ParseArray(CStringArray& arrStr, CString& space, CString& str);
	// ×Ö·û´®½âÎö
	static void ParseString(CString& str, char space, CStringArray& arrStr);
	static void ParseString(CString& str, CString& space, CStringArray& arrStr);
};

#endif // !defined(AFX_STRPARSE_H__CAFA14F0_A1F7_47F1_BEBD_DD4B8719CA7E__INCLUDED_)
