// TextResource.h: interface for the CTextResource class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEXTRESOURCE_H__F074F1B1_A51C_4F12_9833_191E5A6C45C3__INCLUDED_)
#define AFX_TEXTRESOURCE_H__F074F1B1_A51C_4F12_9833_191E5A6C45C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <map>
#include <string>
using namespace std;

#include "ResourceItem.h"

struct stText
{
	UINT nIndex;
	CString sTextName;
	CString sText;
};


class CTextResource  : public CResourceItem  
{
public:
	CTextResource();
	virtual ~CTextResource();

public:
	virtual bool ReadResource(CXMLDOMInterface& Dom,IXMLDOMNode* pXMLNode);
	virtual void FreeResource();

	LPCSTR GetText(CString sTextName);

	//operator LPCTSTR() { return GetText(); }
	
	//operator CString () { return m_sText; }

public:
	map<string,stText> m_mapText;
};

#endif // !defined(AFX_TEXTRESOURCE_H__F074F1B1_A51C_4F12_9833_191E5A6C45C3__INCLUDED_)
